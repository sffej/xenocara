/*
 * Copyright © Microsoft Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "dzn_private.h"

#include "spirv_to_dxil.h"
#include "nir_to_dxil.h"

#include "dxil_nir.h"
#include "dxil_nir_lower_int_samplers.h"
#include "dxil_validator.h"

static void
dzn_meta_compile_shader(dzn_device *device, nir_shader *nir,
                        D3D12_SHADER_BYTECODE *slot)
{
   dzn_instance *instance =
      container_of(device->vk.physical->instance, dzn_instance, vk);

   nir_shader_gather_info(nir, nir_shader_get_entrypoint(nir));

   if ((instance->debug_flags & DZN_DEBUG_NIR) &&
       (instance->debug_flags & DZN_DEBUG_INTERNAL))
      nir_print_shader(nir, stderr);

   struct nir_to_dxil_options opts = { .environment = DXIL_ENVIRONMENT_VULKAN };
   struct blob dxil_blob;
   bool ret = nir_to_dxil(nir, &opts, &dxil_blob);
   assert(ret);

   char *err;
   bool res = dxil_validate_module(instance->dxil_validator,
                                   dxil_blob.data,
                                   dxil_blob.size, &err);

   if ((instance->debug_flags & DZN_DEBUG_DXIL) &&
       (instance->debug_flags & DZN_DEBUG_INTERNAL)) {
      char *disasm = dxil_disasm_module(instance->dxil_validator,
                                        dxil_blob.data,
                                        dxil_blob.size);
      if (disasm) {
         fprintf(stderr,
                 "== BEGIN SHADER ============================================\n"
                 "%s\n"
                 "== END SHADER ==============================================\n",
                  disasm);
         ralloc_free(disasm);
      }
   }

   if ((instance->debug_flags & DZN_DEBUG_DXIL) &&
       (instance->debug_flags & DZN_DEBUG_INTERNAL) &&
       err) {
      fprintf(stderr,
            "== VALIDATION ERROR =============================================\n"
            "%s\n"
            "== END ==========================================================\n",
            err);
      ralloc_free(err);
   }
   assert(res);

   void *data;
   size_t size;
   blob_finish_get_buffer(&dxil_blob, &data, &size);
   slot->pShaderBytecode = data;
   slot->BytecodeLength = size;
}

#define DZN_META_INDIRECT_DRAW_MAX_PARAM_COUNT 4

static void
dzn_meta_indirect_draw_finish(dzn_device *device, enum dzn_indirect_draw_type type)
{
   dzn_meta_indirect_draw *meta = &device->indirect_draws[type];

   if (meta->root_sig)
      meta->root_sig->Release();

   if (meta->pipeline_state)
      meta->pipeline_state->Release();
}

static VkResult
dzn_meta_indirect_draw_init(dzn_device *device,
                            enum dzn_indirect_draw_type type)
{
   dzn_meta_indirect_draw *meta = &device->indirect_draws[type];
   dzn_instance *instance =
      container_of(device->vk.physical->instance, dzn_instance, vk);
   VkResult ret = VK_SUCCESS;

   glsl_type_singleton_init_or_ref();

   nir_shader *nir = dzn_nir_indirect_draw_shader(type);
   bool triangle_fan = type == DZN_INDIRECT_DRAW_TRIANGLE_FAN ||
                       type == DZN_INDIRECT_INDEXED_DRAW_TRIANGLE_FAN;
   uint32_t shader_params_size =
      triangle_fan ?
      sizeof(struct dzn_indirect_draw_triangle_fan_rewrite_params) :
      sizeof(struct dzn_indirect_draw_rewrite_params);

   uint32_t root_param_count = 0;
   D3D12_ROOT_PARAMETER1 root_params[DZN_META_INDIRECT_DRAW_MAX_PARAM_COUNT];

   root_params[root_param_count++] = D3D12_ROOT_PARAMETER1 {
      .ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS,
      .Constants = {
         .ShaderRegister = 0,
         .RegisterSpace = 0,
         .Num32BitValues = shader_params_size / 4,
      },
      .ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL,
   };

   root_params[root_param_count++] = D3D12_ROOT_PARAMETER1 {
      .ParameterType = D3D12_ROOT_PARAMETER_TYPE_SRV,
      .Descriptor = {
         .ShaderRegister = 1,
         .RegisterSpace = 0,
         .Flags = D3D12_ROOT_DESCRIPTOR_FLAG_NONE,
      },
      .ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL,
   };

   root_params[root_param_count++] = D3D12_ROOT_PARAMETER1 {
      .ParameterType = D3D12_ROOT_PARAMETER_TYPE_UAV,
      .Descriptor = {
         .ShaderRegister = 2,
         .RegisterSpace = 0,
         .Flags = D3D12_ROOT_DESCRIPTOR_FLAG_NONE,
      },
      .ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL,
   };


   if (triangle_fan) {
      root_params[root_param_count++] = D3D12_ROOT_PARAMETER1 {
         .ParameterType = D3D12_ROOT_PARAMETER_TYPE_UAV,
         .Descriptor = {
            .ShaderRegister = 3,
            .RegisterSpace = 0,
            .Flags = D3D12_ROOT_DESCRIPTOR_FLAG_NONE,
         },
         .ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL,
      };
   }

   assert(root_param_count <= ARRAY_SIZE(root_params));

   D3D12_VERSIONED_ROOT_SIGNATURE_DESC root_sig_desc = {
      .Version = D3D_ROOT_SIGNATURE_VERSION_1_1,
      .Desc_1_1 = {
         .NumParameters = root_param_count,
         .pParameters = root_params,
         .Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE,
      },
   };

   D3D12_COMPUTE_PIPELINE_STATE_DESC desc = {
      .Flags = D3D12_PIPELINE_STATE_FLAG_NONE,
   };

   meta->root_sig =
      dzn_device_create_root_sig(device, &root_sig_desc);
   if (!meta->root_sig) {
      ret = vk_error(instance, VK_ERROR_INITIALIZATION_FAILED);
      goto out;
   }

   desc.pRootSignature = meta->root_sig;
   dzn_meta_compile_shader(device, nir, &desc.CS);
   assert(desc.CS.pShaderBytecode);

   if (FAILED(device->dev->CreateComputePipelineState(&desc,
                                                      IID_PPV_ARGS(&meta->pipeline_state))))
      ret = vk_error(instance, VK_ERROR_INITIALIZATION_FAILED);

out:
   if (ret != VK_SUCCESS)
      dzn_meta_indirect_draw_finish(device, type);

   free((void *)desc.CS.pShaderBytecode);
   ralloc_free(nir);
   glsl_type_singleton_decref();

   return ret;
}

#define DZN_META_TRIANGLE_FAN_REWRITE_IDX_MAX_PARAM_COUNT 3

static void
dzn_meta_triangle_fan_rewrite_index_finish(dzn_device *device,
                                           enum dzn_index_type old_index_type)
{
   dzn_meta_triangle_fan_rewrite_index *meta =
      &device->triangle_fan[old_index_type];

   if (meta->root_sig)
      meta->root_sig->Release();
   if (meta->pipeline_state)
      meta->pipeline_state->Release();
   if (meta->cmd_sig)
      meta->cmd_sig->Release();
}

static VkResult
dzn_meta_triangle_fan_rewrite_index_init(dzn_device *device,
                                         enum dzn_index_type old_index_type)
{
   dzn_meta_triangle_fan_rewrite_index *meta =
      &device->triangle_fan[old_index_type];
   dzn_instance *instance =
      container_of(device->vk.physical->instance, dzn_instance, vk);
   VkResult ret = VK_SUCCESS;

   glsl_type_singleton_init_or_ref();

   uint8_t old_index_size = dzn_index_size(old_index_type);

   nir_shader *nir = dzn_nir_triangle_fan_rewrite_index_shader(old_index_size);

   uint32_t root_param_count = 0;
   D3D12_ROOT_PARAMETER1 root_params[DZN_META_TRIANGLE_FAN_REWRITE_IDX_MAX_PARAM_COUNT];

   root_params[root_param_count++] = D3D12_ROOT_PARAMETER1 {
      .ParameterType = D3D12_ROOT_PARAMETER_TYPE_UAV,
      .Descriptor = {
         .ShaderRegister = 1,
         .RegisterSpace = 0,
         .Flags = D3D12_ROOT_DESCRIPTOR_FLAG_NONE,
      },
      .ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL,
   };

   root_params[root_param_count++] = D3D12_ROOT_PARAMETER1 {
      .ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS,
      .Constants = {
         .ShaderRegister = 0,
         .RegisterSpace = 0,
         .Num32BitValues = sizeof(struct dzn_triangle_fan_rewrite_index_params) / 4,
      },
      .ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL,
   };

   if (old_index_type != DZN_NO_INDEX) {
      root_params[root_param_count++] = D3D12_ROOT_PARAMETER1 {
         .ParameterType = D3D12_ROOT_PARAMETER_TYPE_SRV,
         .Descriptor = {
            .ShaderRegister = 2,
            .RegisterSpace = 0,
            .Flags = D3D12_ROOT_DESCRIPTOR_FLAG_NONE,
         },
         .ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL,
      };
   }

   assert(root_param_count <= ARRAY_SIZE(root_params));

   D3D12_VERSIONED_ROOT_SIGNATURE_DESC root_sig_desc = {
      .Version = D3D_ROOT_SIGNATURE_VERSION_1_1,
      .Desc_1_1 = {
         .NumParameters = root_param_count,
         .pParameters = root_params,
         .Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE,
      },
   };

   D3D12_COMPUTE_PIPELINE_STATE_DESC desc = {
      .Flags = D3D12_PIPELINE_STATE_FLAG_NONE,
   };

   D3D12_INDIRECT_ARGUMENT_DESC cmd_args[] = {
      {
         .Type = D3D12_INDIRECT_ARGUMENT_TYPE_UNORDERED_ACCESS_VIEW,
         .UnorderedAccessView = {
            .RootParameterIndex = 0,
         },
      },
      {
         .Type = D3D12_INDIRECT_ARGUMENT_TYPE_CONSTANT,
         .Constant = {
            .RootParameterIndex = 1,
            .DestOffsetIn32BitValues = 0,
            .Num32BitValuesToSet = sizeof(struct dzn_triangle_fan_rewrite_index_params) / 4,
         },
      },
      {
         .Type = D3D12_INDIRECT_ARGUMENT_TYPE_DISPATCH,
      },
   };

   D3D12_COMMAND_SIGNATURE_DESC cmd_sig_desc = {
      .ByteStride = sizeof(struct dzn_indirect_triangle_fan_rewrite_index_exec_params),
      .NumArgumentDescs = ARRAY_SIZE(cmd_args),
      .pArgumentDescs = cmd_args,
   };

   assert((cmd_sig_desc.ByteStride & 7) == 0);

   meta->root_sig = dzn_device_create_root_sig(device, &root_sig_desc);
   if (!meta->root_sig) {
      ret = vk_error(instance, VK_ERROR_INITIALIZATION_FAILED);
      goto out;
   }


   desc.pRootSignature = meta->root_sig;
   dzn_meta_compile_shader(device, nir, &desc.CS);

   if (FAILED(device->dev->CreateComputePipelineState(&desc,
                                                      IID_PPV_ARGS(&meta->pipeline_state)))) {
      ret = vk_error(instance, VK_ERROR_INITIALIZATION_FAILED);
      goto out;
   }

   if (FAILED(device->dev->CreateCommandSignature(&cmd_sig_desc,
                                                  meta->root_sig,
                                                  IID_PPV_ARGS(&meta->cmd_sig))))
      ret = vk_error(instance, VK_ERROR_INITIALIZATION_FAILED);

out:
   if (ret != VK_SUCCESS)
      dzn_meta_triangle_fan_rewrite_index_finish(device, old_index_type);

   free((void *)desc.CS.pShaderBytecode);
   ralloc_free(nir);
   glsl_type_singleton_decref();

   return ret;
}

static const D3D12_SHADER_BYTECODE *
dzn_meta_blits_get_vs(dzn_device *device)
{
   dzn_meta_blits *meta = &device->blits;
   D3D12_SHADER_BYTECODE *out;

   mtx_lock(&meta->shaders_lock);

   if (meta->vs.pShaderBytecode == NULL) {
      nir_shader *nir = dzn_nir_blit_vs();

      NIR_PASS_V(nir, nir_lower_system_values);

      gl_system_value system_values[] = {
         SYSTEM_VALUE_FIRST_VERTEX,
         SYSTEM_VALUE_BASE_VERTEX,
      };

      NIR_PASS_V(nir, dxil_nir_lower_system_values_to_zero, system_values,
                ARRAY_SIZE(system_values));

      D3D12_SHADER_BYTECODE bc;

      dzn_meta_compile_shader(device, nir, &bc);
      meta->vs.pShaderBytecode =
         vk_alloc(&device->vk.alloc, bc.BytecodeLength, 8,
                  VK_SYSTEM_ALLOCATION_SCOPE_DEVICE);
      if (meta->vs.pShaderBytecode) {
         meta->vs.BytecodeLength = bc.BytecodeLength;
         memcpy((void *)meta->vs.pShaderBytecode, bc.pShaderBytecode, bc.BytecodeLength);
         out = &meta->vs;
      }
      free((void *)bc.pShaderBytecode);
      ralloc_free(nir);
   } else {
      out = &meta->vs;
   }

   mtx_unlock(&meta->shaders_lock);

   return &meta->vs;
}

static const D3D12_SHADER_BYTECODE *
dzn_meta_blits_get_fs(dzn_device *device,
                      const struct dzn_nir_blit_info *info)
{
   dzn_meta_blits *meta = &device->blits;
   D3D12_SHADER_BYTECODE *out = NULL;

   mtx_lock(&meta->shaders_lock);

   STATIC_ASSERT(sizeof(struct dzn_nir_blit_info) == sizeof(uint32_t));

   struct hash_entry *he =
      _mesa_hash_table_search(meta->fs, (void *)(uintptr_t)info->hash_key);

   if (!he) {
      nir_shader *nir = dzn_nir_blit_fs(info);

      if (info->out_type != GLSL_TYPE_FLOAT) {
         dxil_wrap_sampler_state wrap_state = {
            .is_int_sampler = 1,
            .is_linear_filtering = 0,
            .skip_boundary_conditions = 1,
         };
         dxil_lower_sample_to_txf_for_integer_tex(nir, &wrap_state, NULL, 0);
      }

      D3D12_SHADER_BYTECODE bc;

      dzn_meta_compile_shader(device, nir, &bc);

      out = (D3D12_SHADER_BYTECODE *)
         vk_alloc(&device->vk.alloc,
                  sizeof(D3D12_SHADER_BYTECODE) + bc.BytecodeLength, 8,
                  VK_SYSTEM_ALLOCATION_SCOPE_DEVICE);
      if (out) {
         out->pShaderBytecode = (void *)(out + 1);
         memcpy((void *)out->pShaderBytecode, bc.pShaderBytecode, bc.BytecodeLength);
         out->BytecodeLength = bc.BytecodeLength;
         _mesa_hash_table_insert(meta->fs, &info->hash_key, out);
      }
      free((void *)bc.pShaderBytecode);
      ralloc_free(nir);
   } else {
      out = (D3D12_SHADER_BYTECODE *)he->data;
   }

   mtx_unlock(&meta->shaders_lock);

   return out;
}

static void
dzn_meta_blit_destroy(dzn_device *device, dzn_meta_blit *blit)
{
   if (!blit)
      return;

   if (blit->root_sig)
      blit->root_sig->Release();
   if (blit->pipeline_state)
      blit->pipeline_state->Release();

   vk_free(&device->vk.alloc, blit);
}

static dzn_meta_blit *
dzn_meta_blit_create(dzn_device *device, const dzn_meta_blit_key *key)
{
   dzn_meta_blits *blits = &device->blits;
   dzn_meta_blit *blit = (dzn_meta_blit *)
      vk_zalloc(&device->vk.alloc, sizeof(*blit), 8,
                VK_SYSTEM_ALLOCATION_SCOPE_DEVICE);

   if (!blit)
      return NULL;

   D3D12_DESCRIPTOR_RANGE1 ranges[] = {
      {
         .RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
         .NumDescriptors = 1,
         .BaseShaderRegister = 0,
         .RegisterSpace = 0,
         .Flags = D3D12_DESCRIPTOR_RANGE_FLAG_DESCRIPTORS_STATIC_KEEPING_BUFFER_BOUNDS_CHECKS,
         .OffsetInDescriptorsFromTableStart = 0,
      },
   };

   D3D12_STATIC_SAMPLER_DESC samplers[] = {
      {
         .Filter = key->linear_filter ?
                   D3D12_FILTER_MIN_MAG_MIP_LINEAR :
                   D3D12_FILTER_MIN_MAG_MIP_POINT,
         .AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
         .AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
         .AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
         .MipLODBias = 0,
         .MaxAnisotropy = 0,
         .MinLOD = 0,
         .MaxLOD = D3D12_FLOAT32_MAX,
         .ShaderRegister = 0,
         .RegisterSpace = 0,
         .ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL,
      },
   };

   D3D12_ROOT_PARAMETER1 root_params[] = {
      {
         .ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE,
         .DescriptorTable = {
            .NumDescriptorRanges = ARRAY_SIZE(ranges),
            .pDescriptorRanges = ranges,
         },
         .ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL,
      },
      {
         .ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS,
         .Constants = {
            .ShaderRegister = 0,
            .RegisterSpace = 0,
            .Num32BitValues = 17,
         },
         .ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX,
      },
   };

   D3D12_VERSIONED_ROOT_SIGNATURE_DESC root_sig_desc = {
      .Version = D3D_ROOT_SIGNATURE_VERSION_1_1,
      .Desc_1_1 = {
         .NumParameters = ARRAY_SIZE(root_params),
         .pParameters = root_params,
         .NumStaticSamplers = ARRAY_SIZE(samplers),
         .pStaticSamplers = samplers,
         .Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE,
      },
   };

   D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {
      .SampleMask = key->resolve ? 1 : (1ULL << key->samples) - 1,
      .RasterizerState = {
         .FillMode = D3D12_FILL_MODE_SOLID,
         .CullMode = D3D12_CULL_MODE_NONE,
         .DepthClipEnable = TRUE,
      },
      .PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
      .SampleDesc = {
         .Count = key->resolve ? 1 : key->samples,
         .Quality = 0,
      },
      .Flags = D3D12_PIPELINE_STATE_FLAG_NONE,
   };

   struct dzn_nir_blit_info blit_fs_info = {
      .src_samples = key->samples,
      .loc = key->loc,
      .out_type = key->out_type,
      .sampler_dim = key->sampler_dim,
      .src_is_array = key->src_is_array,
      .resolve = key->resolve,
      .padding = 0,
   };

   blit->root_sig = dzn_device_create_root_sig(device, &root_sig_desc);
   if (!blit->root_sig) {
      dzn_meta_blit_destroy(device, blit);
      return NULL;
   }

   desc.pRootSignature = blit->root_sig;

   const D3D12_SHADER_BYTECODE *vs, *fs;

   vs = dzn_meta_blits_get_vs(device);
   if (!vs) {
      dzn_meta_blit_destroy(device, blit);
      return NULL;
   }

   desc.VS = *vs;
   assert(desc.VS.pShaderBytecode);

   fs = dzn_meta_blits_get_fs(device, &blit_fs_info);
   if (!fs) {
      dzn_meta_blit_destroy(device, blit);
      return NULL;
   }

   desc.PS = *fs;
   assert(desc.PS.pShaderBytecode);

   assert(key->loc == FRAG_RESULT_DATA0 ||
          key->loc == FRAG_RESULT_DEPTH ||
          key->loc == FRAG_RESULT_STENCIL);

   if (key->loc == FRAG_RESULT_DATA0) {
      desc.NumRenderTargets = 1;
      desc.RTVFormats[0] = key->out_format;
      desc.BlendState.RenderTarget[0].RenderTargetWriteMask = 0xf;
   } else {
      desc.DSVFormat = key->out_format;
      if (key->loc == FRAG_RESULT_DEPTH) {
         desc.DepthStencilState.DepthEnable = TRUE;
         desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
         desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS;
      } else {
         assert(key->loc == FRAG_RESULT_STENCIL);
         desc.DepthStencilState.StencilEnable = TRUE;
         desc.DepthStencilState.StencilWriteMask = 0xff;
         desc.DepthStencilState.FrontFace.StencilFailOp = D3D12_STENCIL_OP_REPLACE;
         desc.DepthStencilState.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_REPLACE;
         desc.DepthStencilState.FrontFace.StencilPassOp = D3D12_STENCIL_OP_REPLACE;
         desc.DepthStencilState.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;
         desc.DepthStencilState.BackFace = desc.DepthStencilState.FrontFace;
      }
   }

   if (FAILED(device->dev->CreateGraphicsPipelineState(&desc,
                                                       IID_PPV_ARGS(&blit->pipeline_state)))) {
      dzn_meta_blit_destroy(device, blit);
      return NULL;
   }

   return blit;
}

const dzn_meta_blit *
dzn_meta_blits_get_context(dzn_device *device,
                           const dzn_meta_blit_key *key)
{
   dzn_meta_blit *out = NULL;

   STATIC_ASSERT(sizeof(*key) == sizeof(uint64_t));

   mtx_lock(&device->blits.contexts_lock);

   out = (dzn_meta_blit *)
      _mesa_hash_table_u64_search(device->blits.contexts, key->u64);
   if (!out) {
      out = dzn_meta_blit_create(device, key);

      if (out)
         _mesa_hash_table_u64_insert(device->blits.contexts, key->u64, out);
   }

   mtx_unlock(&device->blits.contexts_lock);

   return out;
}

static void
dzn_meta_blits_finish(dzn_device *device)
{
   dzn_meta_blits *meta = &device->blits;

   vk_free(&device->vk.alloc, (void *)meta->vs.pShaderBytecode);

   if (meta->fs) {
      hash_table_foreach(meta->fs, he)
         vk_free(&device->vk.alloc, he->data);
      _mesa_hash_table_destroy(meta->fs, NULL);
   }

   if (meta->contexts) {
      hash_table_foreach(meta->contexts->table, he)
         dzn_meta_blit_destroy(device, (dzn_meta_blit *)he->data);
      _mesa_hash_table_u64_destroy(meta->contexts);
   }

   mtx_destroy(&meta->shaders_lock);
   mtx_destroy(&meta->contexts_lock);
}

static VkResult
dzn_meta_blits_init(dzn_device *device)
{
   dzn_instance *instance =
      container_of(device->vk.physical->instance, dzn_instance, vk);
   dzn_meta_blits *meta = &device->blits;

   mtx_init(&meta->shaders_lock, mtx_plain);
   mtx_init(&meta->contexts_lock, mtx_plain);

   meta->fs = _mesa_hash_table_create_u32_keys(NULL);
   if (!meta->fs) {
      dzn_meta_blits_finish(device);
      return vk_error(instance, VK_ERROR_OUT_OF_HOST_MEMORY);
   }

   meta->contexts = _mesa_hash_table_u64_create(NULL);
   if (!meta->contexts) {
      dzn_meta_blits_finish(device);
      return vk_error(instance, VK_ERROR_OUT_OF_HOST_MEMORY);
   }

   return VK_SUCCESS;
}

void
dzn_meta_finish(dzn_device *device)
{
   for (uint32_t i = 0; i < ARRAY_SIZE(device->triangle_fan); i++)
      dzn_meta_triangle_fan_rewrite_index_finish(device, (enum dzn_index_type)i);

   for (uint32_t i = 0; i < ARRAY_SIZE(device->indirect_draws); i++)
      dzn_meta_indirect_draw_finish(device, (enum dzn_indirect_draw_type)i);

   dzn_meta_blits_finish(device);
}

VkResult
dzn_meta_init(dzn_device *device)
{
   VkResult result = dzn_meta_blits_init(device);
   if (result != VK_SUCCESS)
      goto out;

   for (uint32_t i = 0; i < ARRAY_SIZE(device->indirect_draws); i++) {
      VkResult result =
         dzn_meta_indirect_draw_init(device, (enum dzn_indirect_draw_type)i);
      if (result != VK_SUCCESS)
         goto out;
   }

   for (uint32_t i = 0; i < ARRAY_SIZE(device->triangle_fan); i++) {
      VkResult result =
         dzn_meta_triangle_fan_rewrite_index_init(device, (enum dzn_index_type)i);
      if (result != VK_SUCCESS)
         goto out;
   }

out:
   if (result != VK_SUCCESS) {
      dzn_meta_finish(device);
      return result;
   }

   return VK_SUCCESS;
}
