/*
 * Copyright © 2016 Intel Corporation
 * Copyright © 2019 Google LLC
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
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "vk_format.h"

#include "vk_enum_defines.h"
#include "vk_enum_to_str.h"
#include "vk_util.h"

/* Note that for packed formats, VK_FORMAT_ lists channels from high to low
 * bits occupied by the channel, while MESA_FORMAT_* and PIPE_FORMAT_* are
 * low-to-high.
 *
 * Also, missing entries are zero-filled, which happens to be
 * PIPE_FORMAT_NONE.
 */
const enum pipe_format vk_format_map[] = {
   /* Missing R4G4 */
   [VK_FORMAT_R4G4B4A4_UNORM_PACK16] = PIPE_FORMAT_A4B4G4R4_UNORM,
   [VK_FORMAT_B4G4R4A4_UNORM_PACK16] = PIPE_FORMAT_A4R4G4B4_UNORM,
   [VK_FORMAT_R5G6B5_UNORM_PACK16] = PIPE_FORMAT_B5G6R5_UNORM,
   [VK_FORMAT_B5G6R5_UNORM_PACK16] = PIPE_FORMAT_R5G6B5_UNORM,
   [VK_FORMAT_R5G5B5A1_UNORM_PACK16] = PIPE_FORMAT_A1B5G5R5_UNORM,
   [VK_FORMAT_B5G5R5A1_UNORM_PACK16] = PIPE_FORMAT_A1R5G5B5_UNORM,
   [VK_FORMAT_A1R5G5B5_UNORM_PACK16] = PIPE_FORMAT_B5G5R5A1_UNORM,

   [VK_FORMAT_R8_UNORM] = PIPE_FORMAT_R8_UNORM,
   [VK_FORMAT_R8_SNORM] = PIPE_FORMAT_R8_SNORM,
   [VK_FORMAT_R8_USCALED] = PIPE_FORMAT_R8_USCALED,
   [VK_FORMAT_R8_SSCALED] = PIPE_FORMAT_R8_SSCALED,
   [VK_FORMAT_R8_UINT] = PIPE_FORMAT_R8_UINT,
   [VK_FORMAT_R8_SINT] = PIPE_FORMAT_R8_SINT,
   [VK_FORMAT_R8_SRGB] = PIPE_FORMAT_R8_SRGB,

   [VK_FORMAT_R8G8_UNORM] = PIPE_FORMAT_R8G8_UNORM,
   [VK_FORMAT_R8G8_SNORM] = PIPE_FORMAT_R8G8_SNORM,
   [VK_FORMAT_R8G8_USCALED] = PIPE_FORMAT_R8G8_USCALED,
   [VK_FORMAT_R8G8_SSCALED] = PIPE_FORMAT_R8G8_SSCALED,
   [VK_FORMAT_R8G8_UINT] = PIPE_FORMAT_R8G8_UINT,
   [VK_FORMAT_R8G8_SINT] = PIPE_FORMAT_R8G8_SINT,
   [VK_FORMAT_R8G8_SRGB] = PIPE_FORMAT_R8G8_SRGB,

   [VK_FORMAT_R8G8B8_UNORM] = PIPE_FORMAT_R8G8B8_UNORM,
   [VK_FORMAT_R8G8B8_SNORM] = PIPE_FORMAT_R8G8B8_SNORM,
   [VK_FORMAT_R8G8B8_USCALED] = PIPE_FORMAT_R8G8B8_USCALED,
   [VK_FORMAT_R8G8B8_SSCALED] = PIPE_FORMAT_R8G8B8_SSCALED,
   [VK_FORMAT_R8G8B8_UINT] = PIPE_FORMAT_R8G8B8_UINT,
   [VK_FORMAT_R8G8B8_SINT] = PIPE_FORMAT_R8G8B8_SINT,
   [VK_FORMAT_R8G8B8_SRGB] = PIPE_FORMAT_R8G8B8_SRGB,

   [VK_FORMAT_B8G8R8_UNORM] = PIPE_FORMAT_B8G8R8_UNORM,
   [VK_FORMAT_B8G8R8_SNORM] = PIPE_FORMAT_B8G8R8_SNORM,
   [VK_FORMAT_B8G8R8_USCALED] = PIPE_FORMAT_B8G8R8_USCALED,
   [VK_FORMAT_B8G8R8_SSCALED] = PIPE_FORMAT_B8G8R8_SSCALED,
   [VK_FORMAT_B8G8R8_UINT] = PIPE_FORMAT_B8G8R8_UINT,
   [VK_FORMAT_B8G8R8_SINT] = PIPE_FORMAT_B8G8R8_SINT,
   [VK_FORMAT_B8G8R8_SRGB] = PIPE_FORMAT_B8G8R8_SRGB,

   [VK_FORMAT_R8G8B8A8_UNORM] = PIPE_FORMAT_R8G8B8A8_UNORM,
   [VK_FORMAT_R8G8B8A8_SNORM] = PIPE_FORMAT_R8G8B8A8_SNORM,
   [VK_FORMAT_R8G8B8A8_USCALED] = PIPE_FORMAT_R8G8B8A8_USCALED,
   [VK_FORMAT_R8G8B8A8_SSCALED] = PIPE_FORMAT_R8G8B8A8_SSCALED,
   [VK_FORMAT_R8G8B8A8_UINT] = PIPE_FORMAT_R8G8B8A8_UINT,
   [VK_FORMAT_R8G8B8A8_SINT] = PIPE_FORMAT_R8G8B8A8_SINT,
   [VK_FORMAT_R8G8B8A8_SRGB] = PIPE_FORMAT_R8G8B8A8_SRGB,

   [VK_FORMAT_B8G8R8A8_UNORM] = PIPE_FORMAT_B8G8R8A8_UNORM,
   [VK_FORMAT_B8G8R8A8_SNORM] = PIPE_FORMAT_B8G8R8A8_SNORM,
   [VK_FORMAT_B8G8R8A8_USCALED] = PIPE_FORMAT_B8G8R8A8_USCALED,
   [VK_FORMAT_B8G8R8A8_SSCALED] = PIPE_FORMAT_B8G8R8A8_SSCALED,
   [VK_FORMAT_B8G8R8A8_UINT] = PIPE_FORMAT_B8G8R8A8_UINT,
   [VK_FORMAT_B8G8R8A8_SINT] = PIPE_FORMAT_B8G8R8A8_SINT,
   [VK_FORMAT_B8G8R8A8_SRGB] = PIPE_FORMAT_B8G8R8A8_SRGB,

   [VK_FORMAT_A8B8G8R8_UNORM_PACK32] = PIPE_FORMAT_RGBA8888_UNORM,
   [VK_FORMAT_A8B8G8R8_SNORM_PACK32] = PIPE_FORMAT_RGBA8888_SNORM,
   [VK_FORMAT_A8B8G8R8_USCALED_PACK32] = PIPE_FORMAT_RGBA8888_USCALED,
   [VK_FORMAT_A8B8G8R8_SSCALED_PACK32] = PIPE_FORMAT_RGBA8888_SSCALED,
   [VK_FORMAT_A8B8G8R8_UINT_PACK32] = PIPE_FORMAT_RGBA8888_UINT,
   [VK_FORMAT_A8B8G8R8_SINT_PACK32] = PIPE_FORMAT_RGBA8888_SINT,
   [VK_FORMAT_A8B8G8R8_SRGB_PACK32] = PIPE_FORMAT_RGBA8888_SRGB,

   [VK_FORMAT_A2R10G10B10_UNORM_PACK32] = PIPE_FORMAT_B10G10R10A2_UNORM,
   [VK_FORMAT_A2R10G10B10_SNORM_PACK32] = PIPE_FORMAT_B10G10R10A2_SNORM,
   [VK_FORMAT_A2R10G10B10_USCALED_PACK32] = PIPE_FORMAT_B10G10R10A2_USCALED,
   [VK_FORMAT_A2R10G10B10_SSCALED_PACK32] = PIPE_FORMAT_B10G10R10A2_SSCALED,
   [VK_FORMAT_A2R10G10B10_UINT_PACK32] = PIPE_FORMAT_B10G10R10A2_UINT,
   [VK_FORMAT_A2R10G10B10_SINT_PACK32] = PIPE_FORMAT_B10G10R10A2_SINT,

   [VK_FORMAT_A2B10G10R10_UNORM_PACK32] = PIPE_FORMAT_R10G10B10A2_UNORM,
   [VK_FORMAT_A2B10G10R10_SNORM_PACK32] = PIPE_FORMAT_R10G10B10A2_SNORM,
   [VK_FORMAT_A2B10G10R10_USCALED_PACK32] = PIPE_FORMAT_R10G10B10A2_USCALED,
   [VK_FORMAT_A2B10G10R10_SSCALED_PACK32] = PIPE_FORMAT_R10G10B10A2_SSCALED,
   [VK_FORMAT_A2B10G10R10_UINT_PACK32] = PIPE_FORMAT_R10G10B10A2_UINT,
   [VK_FORMAT_A2B10G10R10_SINT_PACK32] = PIPE_FORMAT_R10G10B10A2_SINT,

   [VK_FORMAT_R16_UNORM] = PIPE_FORMAT_R16_UNORM,
   [VK_FORMAT_R16_SNORM] = PIPE_FORMAT_R16_SNORM,
   [VK_FORMAT_R16_USCALED] = PIPE_FORMAT_R16_USCALED,
   [VK_FORMAT_R16_SSCALED] = PIPE_FORMAT_R16_SSCALED,
   [VK_FORMAT_R16_UINT] = PIPE_FORMAT_R16_UINT,
   [VK_FORMAT_R16_SINT] = PIPE_FORMAT_R16_SINT,
   [VK_FORMAT_R16_SFLOAT] = PIPE_FORMAT_R16_FLOAT,

   [VK_FORMAT_R16G16_UNORM] = PIPE_FORMAT_R16G16_UNORM,
   [VK_FORMAT_R16G16_SNORM] = PIPE_FORMAT_R16G16_SNORM,
   [VK_FORMAT_R16G16_USCALED] = PIPE_FORMAT_R16G16_USCALED,
   [VK_FORMAT_R16G16_SSCALED] = PIPE_FORMAT_R16G16_SSCALED,
   [VK_FORMAT_R16G16_UINT] = PIPE_FORMAT_R16G16_UINT,
   [VK_FORMAT_R16G16_SINT] = PIPE_FORMAT_R16G16_SINT,
   [VK_FORMAT_R16G16_SFLOAT] = PIPE_FORMAT_R16G16_FLOAT,

   [VK_FORMAT_R16G16B16_UNORM] = PIPE_FORMAT_R16G16B16_UNORM,
   [VK_FORMAT_R16G16B16_SNORM] = PIPE_FORMAT_R16G16B16_SNORM,
   [VK_FORMAT_R16G16B16_USCALED] = PIPE_FORMAT_R16G16B16_USCALED,
   [VK_FORMAT_R16G16B16_SSCALED] = PIPE_FORMAT_R16G16B16_SSCALED,
   [VK_FORMAT_R16G16B16_UINT] = PIPE_FORMAT_R16G16B16_UINT,
   [VK_FORMAT_R16G16B16_SINT] = PIPE_FORMAT_R16G16B16_SINT,
   [VK_FORMAT_R16G16B16_SFLOAT] = PIPE_FORMAT_R16G16B16_FLOAT,

   [VK_FORMAT_R16G16B16A16_UNORM] = PIPE_FORMAT_R16G16B16A16_UNORM,
   [VK_FORMAT_R16G16B16A16_SNORM] = PIPE_FORMAT_R16G16B16A16_SNORM,
   [VK_FORMAT_R16G16B16A16_USCALED] = PIPE_FORMAT_R16G16B16A16_USCALED,
   [VK_FORMAT_R16G16B16A16_SSCALED] = PIPE_FORMAT_R16G16B16A16_SSCALED,
   [VK_FORMAT_R16G16B16A16_UINT] = PIPE_FORMAT_R16G16B16A16_UINT,
   [VK_FORMAT_R16G16B16A16_SINT] = PIPE_FORMAT_R16G16B16A16_SINT,
   [VK_FORMAT_R16G16B16A16_SFLOAT] = PIPE_FORMAT_R16G16B16A16_FLOAT,

   [VK_FORMAT_R32_UINT] = PIPE_FORMAT_R32_UINT,
   [VK_FORMAT_R32_SINT] = PIPE_FORMAT_R32_SINT,
   [VK_FORMAT_R32_SFLOAT] = PIPE_FORMAT_R32_FLOAT,

   [VK_FORMAT_R32G32_UINT] = PIPE_FORMAT_R32G32_UINT,
   [VK_FORMAT_R32G32_SINT] = PIPE_FORMAT_R32G32_SINT,
   [VK_FORMAT_R32G32_SFLOAT] = PIPE_FORMAT_R32G32_FLOAT,

   [VK_FORMAT_R32G32B32_UINT] = PIPE_FORMAT_R32G32B32_UINT,
   [VK_FORMAT_R32G32B32_SINT] = PIPE_FORMAT_R32G32B32_SINT,
   [VK_FORMAT_R32G32B32_SFLOAT] = PIPE_FORMAT_R32G32B32_FLOAT,

   [VK_FORMAT_R32G32B32A32_UINT] = PIPE_FORMAT_R32G32B32A32_UINT,
   [VK_FORMAT_R32G32B32A32_SINT] = PIPE_FORMAT_R32G32B32A32_SINT,
   [VK_FORMAT_R32G32B32A32_SFLOAT] = PIPE_FORMAT_R32G32B32A32_FLOAT,

   [VK_FORMAT_R64_UINT] = PIPE_FORMAT_R64_UINT,
   [VK_FORMAT_R64_SINT] = PIPE_FORMAT_R64_SINT,
   [VK_FORMAT_R64_SFLOAT] = PIPE_FORMAT_R64_FLOAT,

   [VK_FORMAT_R64G64_UINT] = PIPE_FORMAT_R64G64_UINT,
   [VK_FORMAT_R64G64_SINT] = PIPE_FORMAT_R64G64_SINT,
   [VK_FORMAT_R64G64_SFLOAT] = PIPE_FORMAT_R64G64_FLOAT,

   [VK_FORMAT_R64G64B64_UINT] = PIPE_FORMAT_R64G64B64_UINT,
   [VK_FORMAT_R64G64B64_SINT] = PIPE_FORMAT_R64G64B64_SINT,
   [VK_FORMAT_R64G64B64_SFLOAT] = PIPE_FORMAT_R64G64B64_FLOAT,

   [VK_FORMAT_R64G64B64A64_UINT] = PIPE_FORMAT_R64G64B64A64_UINT,
   [VK_FORMAT_R64G64B64A64_SINT] = PIPE_FORMAT_R64G64B64A64_SINT,
   [VK_FORMAT_R64G64B64A64_SFLOAT] = PIPE_FORMAT_R64G64B64A64_FLOAT,

   [VK_FORMAT_B10G11R11_UFLOAT_PACK32] = PIPE_FORMAT_R11G11B10_FLOAT,
   [VK_FORMAT_E5B9G9R9_UFLOAT_PACK32] = PIPE_FORMAT_R9G9B9E5_FLOAT,

   [VK_FORMAT_D16_UNORM] = PIPE_FORMAT_Z16_UNORM,
   [VK_FORMAT_X8_D24_UNORM_PACK32] = PIPE_FORMAT_Z24X8_UNORM,
   [VK_FORMAT_D32_SFLOAT] = PIPE_FORMAT_Z32_FLOAT,
   [VK_FORMAT_S8_UINT] = PIPE_FORMAT_S8_UINT,
   [VK_FORMAT_D16_UNORM_S8_UINT] = PIPE_FORMAT_Z16_UNORM_S8_UINT,
   [VK_FORMAT_D24_UNORM_S8_UINT] = PIPE_FORMAT_Z24_UNORM_S8_UINT,
   [VK_FORMAT_D32_SFLOAT_S8_UINT] = PIPE_FORMAT_Z32_FLOAT_S8X24_UINT,

   [VK_FORMAT_BC1_RGB_UNORM_BLOCK] = PIPE_FORMAT_DXT1_RGB,
   [VK_FORMAT_BC1_RGB_SRGB_BLOCK] = PIPE_FORMAT_DXT1_SRGB,
   [VK_FORMAT_BC1_RGBA_UNORM_BLOCK] = PIPE_FORMAT_DXT1_RGBA,
   [VK_FORMAT_BC1_RGBA_SRGB_BLOCK] = PIPE_FORMAT_DXT1_SRGBA,
   [VK_FORMAT_BC2_UNORM_BLOCK] = PIPE_FORMAT_DXT3_RGBA,
   [VK_FORMAT_BC2_SRGB_BLOCK] = PIPE_FORMAT_DXT3_SRGBA,
   [VK_FORMAT_BC3_UNORM_BLOCK] = PIPE_FORMAT_DXT5_RGBA,
   [VK_FORMAT_BC3_SRGB_BLOCK] = PIPE_FORMAT_DXT5_SRGBA,
   [VK_FORMAT_BC4_UNORM_BLOCK] = PIPE_FORMAT_RGTC1_UNORM,
   [VK_FORMAT_BC4_SNORM_BLOCK] = PIPE_FORMAT_RGTC1_SNORM,
   [VK_FORMAT_BC5_UNORM_BLOCK] = PIPE_FORMAT_RGTC2_UNORM,
   [VK_FORMAT_BC5_SNORM_BLOCK] = PIPE_FORMAT_RGTC2_SNORM,
   [VK_FORMAT_BC6H_UFLOAT_BLOCK] = PIPE_FORMAT_BPTC_RGB_UFLOAT,
   [VK_FORMAT_BC6H_SFLOAT_BLOCK] = PIPE_FORMAT_BPTC_RGB_FLOAT,
   [VK_FORMAT_BC7_UNORM_BLOCK] = PIPE_FORMAT_BPTC_RGBA_UNORM,
   [VK_FORMAT_BC7_SRGB_BLOCK] = PIPE_FORMAT_BPTC_SRGBA,

   [VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK] = PIPE_FORMAT_ETC2_RGB8,
   [VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK] = PIPE_FORMAT_ETC2_SRGB8,
   [VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK] = PIPE_FORMAT_ETC2_RGB8A1,
   [VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK] = PIPE_FORMAT_ETC2_SRGB8A1,
   [VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK] = PIPE_FORMAT_ETC2_RGBA8,
   [VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK] = PIPE_FORMAT_ETC2_SRGBA8,
   [VK_FORMAT_EAC_R11_UNORM_BLOCK] = PIPE_FORMAT_ETC2_R11_UNORM,
   [VK_FORMAT_EAC_R11_SNORM_BLOCK] = PIPE_FORMAT_ETC2_R11_SNORM,
   [VK_FORMAT_EAC_R11G11_UNORM_BLOCK] = PIPE_FORMAT_ETC2_RG11_UNORM,
   [VK_FORMAT_EAC_R11G11_SNORM_BLOCK] = PIPE_FORMAT_ETC2_RG11_SNORM,

   [VK_FORMAT_ASTC_4x4_UNORM_BLOCK] = PIPE_FORMAT_ASTC_4x4,
   [VK_FORMAT_ASTC_4x4_SRGB_BLOCK] = PIPE_FORMAT_ASTC_4x4_SRGB,
   [VK_FORMAT_ASTC_5x4_UNORM_BLOCK] = PIPE_FORMAT_ASTC_5x4,
   [VK_FORMAT_ASTC_5x4_SRGB_BLOCK] = PIPE_FORMAT_ASTC_5x4_SRGB,
   [VK_FORMAT_ASTC_5x5_UNORM_BLOCK] = PIPE_FORMAT_ASTC_5x5,
   [VK_FORMAT_ASTC_5x5_SRGB_BLOCK] = PIPE_FORMAT_ASTC_5x5_SRGB,
   [VK_FORMAT_ASTC_6x5_UNORM_BLOCK] = PIPE_FORMAT_ASTC_6x5,
   [VK_FORMAT_ASTC_6x5_SRGB_BLOCK] = PIPE_FORMAT_ASTC_6x5_SRGB,
   [VK_FORMAT_ASTC_6x6_UNORM_BLOCK] = PIPE_FORMAT_ASTC_6x6,
   [VK_FORMAT_ASTC_6x6_SRGB_BLOCK] = PIPE_FORMAT_ASTC_6x6_SRGB,
   [VK_FORMAT_ASTC_8x5_UNORM_BLOCK] = PIPE_FORMAT_ASTC_8x5,
   [VK_FORMAT_ASTC_8x5_SRGB_BLOCK] = PIPE_FORMAT_ASTC_8x5_SRGB,
   [VK_FORMAT_ASTC_8x6_UNORM_BLOCK] = PIPE_FORMAT_ASTC_8x6,
   [VK_FORMAT_ASTC_8x6_SRGB_BLOCK] = PIPE_FORMAT_ASTC_8x6_SRGB,
   [VK_FORMAT_ASTC_8x8_UNORM_BLOCK] = PIPE_FORMAT_ASTC_8x8,
   [VK_FORMAT_ASTC_8x8_SRGB_BLOCK] = PIPE_FORMAT_ASTC_8x8_SRGB,
   [VK_FORMAT_ASTC_10x5_UNORM_BLOCK] = PIPE_FORMAT_ASTC_10x5,
   [VK_FORMAT_ASTC_10x5_SRGB_BLOCK] = PIPE_FORMAT_ASTC_10x5_SRGB,
   [VK_FORMAT_ASTC_10x6_UNORM_BLOCK] = PIPE_FORMAT_ASTC_10x6,
   [VK_FORMAT_ASTC_10x6_SRGB_BLOCK] = PIPE_FORMAT_ASTC_10x6_SRGB,
   [VK_FORMAT_ASTC_10x8_UNORM_BLOCK] = PIPE_FORMAT_ASTC_10x8,
   [VK_FORMAT_ASTC_10x8_SRGB_BLOCK] = PIPE_FORMAT_ASTC_10x8_SRGB,
   [VK_FORMAT_ASTC_10x10_UNORM_BLOCK] = PIPE_FORMAT_ASTC_10x10,
   [VK_FORMAT_ASTC_10x10_SRGB_BLOCK] = PIPE_FORMAT_ASTC_10x10_SRGB,
   [VK_FORMAT_ASTC_12x10_UNORM_BLOCK] = PIPE_FORMAT_ASTC_12x10,
   [VK_FORMAT_ASTC_12x10_SRGB_BLOCK] = PIPE_FORMAT_ASTC_12x10_SRGB,
   [VK_FORMAT_ASTC_12x12_UNORM_BLOCK] = PIPE_FORMAT_ASTC_12x12,
   [VK_FORMAT_ASTC_12x12_SRGB_BLOCK] = PIPE_FORMAT_ASTC_12x12_SRGB,

   /* Missing planes */

   /* Missing PVRTC */

   /* Missing ASTC SFLOAT */

   /* Missing more planes */
};

enum pipe_format
vk_format_to_pipe_format(enum VkFormat vkformat)
{
   if (vkformat >= ARRAY_SIZE(vk_format_map)) {
      switch (vkformat) {
      case VK_FORMAT_R10X6_UNORM_PACK16:
         return PIPE_FORMAT_R16_UNORM;
      case VK_FORMAT_R10X6G10X6_UNORM_2PACK16:
         return PIPE_FORMAT_R16G16_UNORM;
      case VK_FORMAT_G8B8G8R8_422_UNORM:
         return PIPE_FORMAT_G8B8_G8R8_UNORM;
      case VK_FORMAT_B8G8R8G8_422_UNORM:
         return PIPE_FORMAT_B8G8_R8G8_UNORM;
      case VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM:
         return PIPE_FORMAT_IYUV;
      case VK_FORMAT_G8_B8R8_2PLANE_420_UNORM:
         return PIPE_FORMAT_NV12;
      case VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM:
         return PIPE_FORMAT_Y8_U8_V8_422_UNORM;
      case VK_FORMAT_G8_B8R8_2PLANE_422_UNORM:
         return PIPE_FORMAT_Y8_U8V8_422_UNORM;
      case VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM:
         return PIPE_FORMAT_Y8_U8_V8_444_UNORM;
      case VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM:
         return PIPE_FORMAT_Y16_U16_V16_420_UNORM;
      case VK_FORMAT_G16_B16R16_2PLANE_420_UNORM:
         return PIPE_FORMAT_P016;
      case VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM:
         return PIPE_FORMAT_Y16_U16_V16_422_UNORM;
      case VK_FORMAT_G16_B16R16_2PLANE_422_UNORM:
         return PIPE_FORMAT_Y16_U16V16_422_UNORM;
      case VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM:
         return PIPE_FORMAT_Y16_U16_V16_444_UNORM;
      case VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16:
         return PIPE_FORMAT_P010;
      case VK_FORMAT_A4R4G4B4_UNORM_PACK16:
         return PIPE_FORMAT_B4G4R4A4_UNORM;
      case VK_FORMAT_A4B4G4R4_UNORM_PACK16:
         return PIPE_FORMAT_R4G4B4A4_UNORM;
      case VK_FORMAT_A8_UNORM_KHR:
         return PIPE_FORMAT_A8_UNORM;
      case VK_FORMAT_A1B5G5R5_UNORM_PACK16_KHR:
         return PIPE_FORMAT_R5G5B5A1_UNORM;
      default:
         return PIPE_FORMAT_NONE;
      }
   }

   /* Unpopulated entries in the table must be PIPE_FORMAT_NONE */
   STATIC_ASSERT(PIPE_FORMAT_NONE == 0);

   return vk_format_map[vkformat];
}

static const VkFormat formats[PIPE_FORMAT_COUNT] = {
#define MAP_FORMAT_NORM(FMT) \
   [PIPE_FORMAT_ ## FMT ## _UNORM] = VK_FORMAT_ ## FMT ## _UNORM, \
   [PIPE_FORMAT_ ## FMT ## _SNORM] = VK_FORMAT_ ## FMT ## _SNORM,

#define MAP_FORMAT_SCALED(FMT) \
   [PIPE_FORMAT_ ## FMT ## _USCALED] = VK_FORMAT_ ## FMT ## _USCALED, \
   [PIPE_FORMAT_ ## FMT ## _SSCALED] = VK_FORMAT_ ## FMT ## _SSCALED,

#define MAP_FORMAT_INT(FMT) \
   [PIPE_FORMAT_ ## FMT ## _UINT] = VK_FORMAT_ ## FMT ## _UINT, \
   [PIPE_FORMAT_ ## FMT ## _SINT] = VK_FORMAT_ ## FMT ## _SINT,

#define MAP_FORMAT_SRGB(FMT) \
   [PIPE_FORMAT_ ## FMT ## _SRGB] = VK_FORMAT_ ## FMT ## _SRGB,

#define MAP_FORMAT_FLOAT(FMT) \
   [PIPE_FORMAT_ ## FMT ## _FLOAT] = VK_FORMAT_ ## FMT ## _SFLOAT,

   // one component

   // 8-bits
   MAP_FORMAT_NORM(R8)
   MAP_FORMAT_SCALED(R8)
   MAP_FORMAT_INT(R8)
   MAP_FORMAT_SRGB(R8)
   // 16-bits
   MAP_FORMAT_NORM(R16)
   MAP_FORMAT_SCALED(R16)
   MAP_FORMAT_INT(R16)
   MAP_FORMAT_FLOAT(R16)
   // 32-bits
   MAP_FORMAT_INT(R32)
   MAP_FORMAT_FLOAT(R32)

   // two components

   // 8-bits
   MAP_FORMAT_NORM(R8G8)
   MAP_FORMAT_SCALED(R8G8)
   MAP_FORMAT_INT(R8G8)
   MAP_FORMAT_SRGB(R8G8)
   // 16-bits
   MAP_FORMAT_NORM(R16G16)
   MAP_FORMAT_SCALED(R16G16)
   MAP_FORMAT_INT(R16G16)
   MAP_FORMAT_FLOAT(R16G16)
   // 32-bits
   MAP_FORMAT_INT(R32G32)
   MAP_FORMAT_FLOAT(R32G32)

   // three components

   // 8-bits
   MAP_FORMAT_NORM(R8G8B8)
   MAP_FORMAT_SCALED(R8G8B8)
   MAP_FORMAT_INT(R8G8B8)
   MAP_FORMAT_SRGB(R8G8B8)
   MAP_FORMAT_NORM(B8G8R8)
   MAP_FORMAT_SCALED(B8G8R8)
   MAP_FORMAT_INT(B8G8R8)
   MAP_FORMAT_SRGB(B8G8R8)
   // 16-bits
   MAP_FORMAT_NORM(R16G16B16)
   MAP_FORMAT_SCALED(R16G16B16)
   MAP_FORMAT_INT(R16G16B16)
   MAP_FORMAT_FLOAT(R16G16B16)
   // 32-bits
   MAP_FORMAT_INT(R32G32B32)
   MAP_FORMAT_FLOAT(R32G32B32)

   // four components

   // 8-bits
   MAP_FORMAT_NORM(R8G8B8A8)
   MAP_FORMAT_SCALED(R8G8B8A8)
   MAP_FORMAT_INT(R8G8B8A8)
   MAP_FORMAT_NORM(B8G8R8A8)
   MAP_FORMAT_SCALED(B8G8R8A8)
   MAP_FORMAT_INT(B8G8R8A8)
   MAP_FORMAT_SRGB(B8G8R8A8)
   [PIPE_FORMAT_RGBA8888_SRGB] = VK_FORMAT_A8B8G8R8_SRGB_PACK32,
   // 16-bits
   MAP_FORMAT_NORM(R16G16B16A16)
   MAP_FORMAT_SCALED(R16G16B16A16)
   MAP_FORMAT_INT(R16G16B16A16)
   MAP_FORMAT_FLOAT(R16G16B16A16)
   // 32-bits
   MAP_FORMAT_INT(R32G32B32A32)
   MAP_FORMAT_FLOAT(R32G32B32A32)

   // other color formats
   [PIPE_FORMAT_A4B4G4R4_UNORM] = VK_FORMAT_R4G4B4A4_UNORM_PACK16,
   [PIPE_FORMAT_A4R4G4B4_UNORM] = VK_FORMAT_B4G4R4A4_UNORM_PACK16,
   [PIPE_FORMAT_B4G4R4A4_UNORM] = VK_FORMAT_A4R4G4B4_UNORM_PACK16,
   [PIPE_FORMAT_R4G4B4A4_UNORM] = VK_FORMAT_A4B4G4R4_UNORM_PACK16,
   [PIPE_FORMAT_B5G6R5_UNORM] = VK_FORMAT_R5G6B5_UNORM_PACK16,
   [PIPE_FORMAT_R5G6B5_UNORM] = VK_FORMAT_B5G6R5_UNORM_PACK16,

   [PIPE_FORMAT_A1B5G5R5_UNORM] = VK_FORMAT_R5G5B5A1_UNORM_PACK16,
   [PIPE_FORMAT_A1R5G5B5_UNORM] = VK_FORMAT_B5G5R5A1_UNORM_PACK16,
   [PIPE_FORMAT_B5G5R5A1_UNORM] = VK_FORMAT_A1R5G5B5_UNORM_PACK16,

   [PIPE_FORMAT_R11G11B10_FLOAT] = VK_FORMAT_B10G11R11_UFLOAT_PACK32,
   [PIPE_FORMAT_R9G9B9E5_FLOAT] = VK_FORMAT_E5B9G9R9_UFLOAT_PACK32,
   /* ARB_vertex_type_2_10_10_10 */
   [PIPE_FORMAT_R10G10B10A2_UNORM] = VK_FORMAT_A2B10G10R10_UNORM_PACK32,
   [PIPE_FORMAT_R10G10B10A2_SNORM] = VK_FORMAT_A2B10G10R10_SNORM_PACK32,
   [PIPE_FORMAT_B10G10R10A2_UNORM] = VK_FORMAT_A2R10G10B10_UNORM_PACK32,
   [PIPE_FORMAT_B10G10R10A2_SNORM] = VK_FORMAT_A2R10G10B10_SNORM_PACK32,
   [PIPE_FORMAT_R10G10B10A2_USCALED] = VK_FORMAT_A2B10G10R10_USCALED_PACK32,
   [PIPE_FORMAT_R10G10B10A2_SSCALED] = VK_FORMAT_A2B10G10R10_SSCALED_PACK32,
   [PIPE_FORMAT_B10G10R10A2_USCALED] = VK_FORMAT_A2R10G10B10_USCALED_PACK32,
   [PIPE_FORMAT_B10G10R10A2_SSCALED] = VK_FORMAT_A2R10G10B10_SSCALED_PACK32,
   [PIPE_FORMAT_R10G10B10A2_UINT] = VK_FORMAT_A2B10G10R10_UINT_PACK32,
   [PIPE_FORMAT_B10G10R10A2_UINT] = VK_FORMAT_A2R10G10B10_UINT_PACK32,
   [PIPE_FORMAT_B10G10R10A2_SINT] = VK_FORMAT_A2R10G10B10_SINT_PACK32,

   // depth/stencil formats
   [PIPE_FORMAT_Z32_FLOAT] = VK_FORMAT_D32_SFLOAT,
   [PIPE_FORMAT_Z32_FLOAT_S8X24_UINT] = VK_FORMAT_D32_SFLOAT_S8_UINT,
   [PIPE_FORMAT_Z16_UNORM] = VK_FORMAT_D16_UNORM,
   [PIPE_FORMAT_Z16_UNORM_S8_UINT] = VK_FORMAT_D16_UNORM_S8_UINT,
   [PIPE_FORMAT_Z24X8_UNORM] = VK_FORMAT_X8_D24_UNORM_PACK32,
   [PIPE_FORMAT_Z24_UNORM_S8_UINT] = VK_FORMAT_D24_UNORM_S8_UINT,
   [PIPE_FORMAT_S8_UINT] = VK_FORMAT_S8_UINT,

   // compressed formats
   [PIPE_FORMAT_DXT1_RGB] = VK_FORMAT_BC1_RGB_UNORM_BLOCK,
   [PIPE_FORMAT_DXT1_RGBA] = VK_FORMAT_BC1_RGBA_UNORM_BLOCK,
   [PIPE_FORMAT_DXT3_RGBA] = VK_FORMAT_BC2_UNORM_BLOCK,
   [PIPE_FORMAT_DXT5_RGBA] = VK_FORMAT_BC3_UNORM_BLOCK,
   [PIPE_FORMAT_DXT1_SRGB] = VK_FORMAT_BC1_RGB_SRGB_BLOCK,
   [PIPE_FORMAT_DXT1_SRGBA] = VK_FORMAT_BC1_RGBA_SRGB_BLOCK,
   [PIPE_FORMAT_DXT3_SRGBA] = VK_FORMAT_BC2_SRGB_BLOCK,
   [PIPE_FORMAT_DXT5_SRGBA] = VK_FORMAT_BC3_SRGB_BLOCK,

   [PIPE_FORMAT_RGTC1_UNORM] = VK_FORMAT_BC4_UNORM_BLOCK,
   [PIPE_FORMAT_RGTC1_SNORM] = VK_FORMAT_BC4_SNORM_BLOCK,
   [PIPE_FORMAT_RGTC2_UNORM] = VK_FORMAT_BC5_UNORM_BLOCK,
   [PIPE_FORMAT_RGTC2_SNORM] = VK_FORMAT_BC5_SNORM_BLOCK,
   [PIPE_FORMAT_BPTC_RGBA_UNORM] = VK_FORMAT_BC7_UNORM_BLOCK,
   [PIPE_FORMAT_BPTC_SRGBA] = VK_FORMAT_BC7_SRGB_BLOCK,
   [PIPE_FORMAT_BPTC_RGB_FLOAT] = VK_FORMAT_BC6H_SFLOAT_BLOCK,
   [PIPE_FORMAT_BPTC_RGB_UFLOAT] = VK_FORMAT_BC6H_UFLOAT_BLOCK,

   [PIPE_FORMAT_ETC1_RGB8] = VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK,
   [PIPE_FORMAT_ETC2_RGB8] = VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK,
   [PIPE_FORMAT_ETC2_SRGB8] = VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK,
   [PIPE_FORMAT_ETC2_RGB8A1] = VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK,
   [PIPE_FORMAT_ETC2_SRGB8A1] = VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK,
   [PIPE_FORMAT_ETC2_RGBA8] = VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK,
   [PIPE_FORMAT_ETC2_SRGBA8] = VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK,
   [PIPE_FORMAT_ETC2_R11_UNORM] = VK_FORMAT_EAC_R11_UNORM_BLOCK,
   [PIPE_FORMAT_ETC2_R11_SNORM] = VK_FORMAT_EAC_R11_SNORM_BLOCK,
   [PIPE_FORMAT_ETC2_RG11_UNORM] = VK_FORMAT_EAC_R11G11_UNORM_BLOCK,
   [PIPE_FORMAT_ETC2_RG11_SNORM] = VK_FORMAT_EAC_R11G11_SNORM_BLOCK,

   [PIPE_FORMAT_ASTC_4x4] = VK_FORMAT_ASTC_4x4_UNORM_BLOCK,
   [PIPE_FORMAT_ASTC_4x4_SRGB] = VK_FORMAT_ASTC_4x4_SRGB_BLOCK,
   [PIPE_FORMAT_ASTC_5x4] = VK_FORMAT_ASTC_5x4_UNORM_BLOCK,
   [PIPE_FORMAT_ASTC_5x4_SRGB] = VK_FORMAT_ASTC_5x4_SRGB_BLOCK,
   [PIPE_FORMAT_ASTC_5x5] = VK_FORMAT_ASTC_5x5_UNORM_BLOCK,
   [PIPE_FORMAT_ASTC_5x5_SRGB] = VK_FORMAT_ASTC_5x5_SRGB_BLOCK,
   [PIPE_FORMAT_ASTC_6x5] = VK_FORMAT_ASTC_6x5_UNORM_BLOCK,
   [PIPE_FORMAT_ASTC_6x5_SRGB] = VK_FORMAT_ASTC_6x5_SRGB_BLOCK,
   [PIPE_FORMAT_ASTC_6x6] = VK_FORMAT_ASTC_6x6_UNORM_BLOCK,
   [PIPE_FORMAT_ASTC_6x6_SRGB] = VK_FORMAT_ASTC_6x6_SRGB_BLOCK,
   [PIPE_FORMAT_ASTC_8x5] = VK_FORMAT_ASTC_8x5_UNORM_BLOCK,
   [PIPE_FORMAT_ASTC_8x5_SRGB] = VK_FORMAT_ASTC_8x5_SRGB_BLOCK,
   [PIPE_FORMAT_ASTC_8x6] = VK_FORMAT_ASTC_8x6_UNORM_BLOCK,
   [PIPE_FORMAT_ASTC_8x6_SRGB] = VK_FORMAT_ASTC_8x6_SRGB_BLOCK,
   [PIPE_FORMAT_ASTC_8x8] = VK_FORMAT_ASTC_8x8_UNORM_BLOCK,
   [PIPE_FORMAT_ASTC_8x8_SRGB] = VK_FORMAT_ASTC_8x8_SRGB_BLOCK,
   [PIPE_FORMAT_ASTC_10x5] = VK_FORMAT_ASTC_10x5_UNORM_BLOCK,
   [PIPE_FORMAT_ASTC_10x5_SRGB] = VK_FORMAT_ASTC_10x5_SRGB_BLOCK,
   [PIPE_FORMAT_ASTC_10x6] = VK_FORMAT_ASTC_10x6_UNORM_BLOCK,
   [PIPE_FORMAT_ASTC_10x6_SRGB] = VK_FORMAT_ASTC_10x6_SRGB_BLOCK,
   [PIPE_FORMAT_ASTC_10x8] = VK_FORMAT_ASTC_10x8_UNORM_BLOCK,
   [PIPE_FORMAT_ASTC_10x8_SRGB] = VK_FORMAT_ASTC_10x8_SRGB_BLOCK,
   [PIPE_FORMAT_ASTC_10x10] = VK_FORMAT_ASTC_10x10_UNORM_BLOCK,
   [PIPE_FORMAT_ASTC_10x10_SRGB] = VK_FORMAT_ASTC_10x10_SRGB_BLOCK,
   [PIPE_FORMAT_ASTC_12x10] = VK_FORMAT_ASTC_12x10_UNORM_BLOCK,
   [PIPE_FORMAT_ASTC_12x10_SRGB] = VK_FORMAT_ASTC_12x10_SRGB_BLOCK,
   [PIPE_FORMAT_ASTC_12x12] = VK_FORMAT_ASTC_12x12_UNORM_BLOCK,
   [PIPE_FORMAT_ASTC_12x12_SRGB] = VK_FORMAT_ASTC_12x12_SRGB_BLOCK,
};

VkFormat
vk_format_from_pipe_format(enum pipe_format format)
{
   return formats[format];
}

VkImageAspectFlags
vk_format_aspects(VkFormat format)
{
   switch (format) {
   case VK_FORMAT_UNDEFINED:
      return 0;

   case VK_FORMAT_S8_UINT:
      return VK_IMAGE_ASPECT_STENCIL_BIT;

   case VK_FORMAT_D16_UNORM_S8_UINT:
   case VK_FORMAT_D24_UNORM_S8_UINT:
   case VK_FORMAT_D32_SFLOAT_S8_UINT:
      return VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;

   case VK_FORMAT_D16_UNORM:
   case VK_FORMAT_X8_D24_UNORM_PACK32:
   case VK_FORMAT_D32_SFLOAT:
      return VK_IMAGE_ASPECT_DEPTH_BIT;

   case VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM:
   case VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM:
   case VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM:
   case VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16:
   case VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16:
   case VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16:
   case VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16:
   case VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16:
   case VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16:
   case VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM:
   case VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM:
   case VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM:
      return (VK_IMAGE_ASPECT_PLANE_0_BIT |
              VK_IMAGE_ASPECT_PLANE_1_BIT |
              VK_IMAGE_ASPECT_PLANE_2_BIT);

   case VK_FORMAT_G8_B8R8_2PLANE_420_UNORM:
   case VK_FORMAT_G8_B8R8_2PLANE_422_UNORM:
   case VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16:
   case VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16:
   case VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16:
   case VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16:
   case VK_FORMAT_G16_B16R16_2PLANE_420_UNORM:
   case VK_FORMAT_G16_B16R16_2PLANE_422_UNORM:
   case VK_FORMAT_G8_B8R8_2PLANE_444_UNORM_EXT:
   case VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16_EXT:
   case VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16_EXT:
   case VK_FORMAT_G16_B16R16_2PLANE_444_UNORM_EXT:
      return (VK_IMAGE_ASPECT_PLANE_0_BIT |
              VK_IMAGE_ASPECT_PLANE_1_BIT);

   default:
      return VK_IMAGE_ASPECT_COLOR_BIT;
   }
}

VkFormat
vk_format_get_plane_format(VkFormat format, unsigned plane_id)
{
   assert(plane_id < vk_format_get_plane_count(format));
   const struct vk_format_ycbcr_info *ycbcr_info =
      vk_format_get_ycbcr_info(format);
   if (ycbcr_info && ycbcr_info->n_planes > 1) {
      const struct vk_format_ycbcr_plane *plane_info = &ycbcr_info->planes[plane_id];
      return plane_info->format;
   } else {
      assert(vk_format_get_plane_count(format) == 1);
      return format;
   }
}

VkFormat
vk_format_get_aspect_format(VkFormat format, const VkImageAspectFlags aspect)
{
   assert(util_bitcount(aspect) == 1);
   assert(aspect & vk_format_aspects(format));

   switch (aspect) {
   case VK_IMAGE_ASPECT_COLOR_BIT:
      return format;
   case VK_IMAGE_ASPECT_DEPTH_BIT:
      return vk_format_depth_only(format);
   case VK_IMAGE_ASPECT_STENCIL_BIT:
      return vk_format_stencil_only(format);
   case VK_IMAGE_ASPECT_PLANE_0_BIT:
      return vk_format_get_plane_format(format, 0);
   case VK_IMAGE_ASPECT_PLANE_1_BIT:
      return vk_format_get_plane_format(format, 1);
   case VK_IMAGE_ASPECT_PLANE_2_BIT:
      return vk_format_get_plane_format(format, 2);
   default:
      unreachable("Cannot translate format aspect");
   }
}

void
vk_component_mapping_to_pipe_swizzle(VkComponentMapping mapping,
                                     unsigned char out_swizzle[4])
{
   VkComponentSwizzle swizzle[4] = { mapping.r, mapping.g, mapping.b, mapping.a };
   for (unsigned i = 0; i < 4; i++) {
      switch (swizzle[i]) {
      case VK_COMPONENT_SWIZZLE_R:
         out_swizzle[i] = PIPE_SWIZZLE_X;
         break;
      case VK_COMPONENT_SWIZZLE_G:
         out_swizzle[i] = PIPE_SWIZZLE_Y;
         break;
      case VK_COMPONENT_SWIZZLE_B:
         out_swizzle[i] = PIPE_SWIZZLE_Z;
         break;
      case VK_COMPONENT_SWIZZLE_A:
         out_swizzle[i] = PIPE_SWIZZLE_W;
         break;
      case VK_COMPONENT_SWIZZLE_IDENTITY:
         out_swizzle[i] = PIPE_SWIZZLE_X + i;
         break;
      case VK_COMPONENT_SWIZZLE_ZERO:
         out_swizzle[i] = PIPE_SWIZZLE_0;
         break;
      case VK_COMPONENT_SWIZZLE_ONE:
         out_swizzle[i] = PIPE_SWIZZLE_1;
         break;
      default:
         unreachable("unknown swizzle");
      }
   }
}

#define fmt_unsupported(__vk_fmt) \
   [VK_ENUM_OFFSET(__vk_fmt)] = { \
      .n_planes = 0, \
   }

#define y_plane(__plane_fmt, __ycbcr_swizzle, dhs, dvs) \
   { .format = __plane_fmt, \
     .has_chroma = false, \
     .denominator_scales = { dhs, dvs, }, \
     .ycbcr_swizzle = __ycbcr_swizzle, \
   }

#define c_plane(__plane_fmt, __ycbcr_swizzle, dhs, dvs) \
   { .format = __plane_fmt, \
     .has_chroma = true, \
     .denominator_scales = { dhs, dvs, }, \
     .ycbcr_swizzle = __ycbcr_swizzle, \
   }

#define ycbcr_fmt(__vk_fmt, __n_planes, ...) \
   [VK_ENUM_OFFSET(__vk_fmt)] = { \
      .n_planes = __n_planes, \
      .planes = { \
         __VA_ARGS__, \
      }, \
   }

#define YCBCR_SWIZ(x, y, z, w) { \
      VK_COMPONENT_SWIZZLE_##x, \
      VK_COMPONENT_SWIZZLE_##y, \
      VK_COMPONENT_SWIZZLE_##z, \
      VK_COMPONENT_SWIZZLE_##w, \
   }

static const struct vk_format_ycbcr_info ycbcr_infos[] = {
   ycbcr_fmt(VK_FORMAT_G8B8G8R8_422_UNORM, 1,
             y_plane(VK_FORMAT_G8B8G8R8_422_UNORM, YCBCR_SWIZ(R, G, B, ZERO), 1, 1)),
   ycbcr_fmt(VK_FORMAT_B8G8R8G8_422_UNORM, 1,
             y_plane(VK_FORMAT_B8G8R8G8_422_UNORM, YCBCR_SWIZ(R, G, B, ZERO), 1, 1)),
   ycbcr_fmt(VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM, 3,
             y_plane(VK_FORMAT_R8_UNORM, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R8_UNORM, YCBCR_SWIZ(B, ZERO, ZERO, ZERO), 2, 2),
             c_plane(VK_FORMAT_R8_UNORM, YCBCR_SWIZ(R, ZERO, ZERO, ZERO), 2, 2)),
   ycbcr_fmt(VK_FORMAT_G8_B8R8_2PLANE_420_UNORM, 2,
             y_plane(VK_FORMAT_R8_UNORM, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R8G8_UNORM, YCBCR_SWIZ(B, R, ZERO, ZERO), 2, 2)),
   ycbcr_fmt(VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM, 3,
             y_plane(VK_FORMAT_R8_UNORM, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R8_UNORM, YCBCR_SWIZ(B, ZERO, ZERO, ZERO), 2, 1),
             c_plane(VK_FORMAT_R8_UNORM, YCBCR_SWIZ(R, ZERO, ZERO, ZERO), 2, 1)),
   ycbcr_fmt(VK_FORMAT_G8_B8R8_2PLANE_422_UNORM, 2,
             y_plane(VK_FORMAT_R8_UNORM, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R8G8_UNORM, YCBCR_SWIZ(B, R, ZERO, ZERO), 2, 1)),
   ycbcr_fmt(VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM, 3,
             y_plane(VK_FORMAT_R8_UNORM, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R8_UNORM, YCBCR_SWIZ(B, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R8_UNORM, YCBCR_SWIZ(R, ZERO, ZERO, ZERO), 1, 1)),

   fmt_unsupported(VK_FORMAT_R10X6_UNORM_PACK16),
   fmt_unsupported(VK_FORMAT_R10X6G10X6_UNORM_2PACK16),
   fmt_unsupported(VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16),

   ycbcr_fmt(VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16, 1,
             y_plane(VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16, YCBCR_SWIZ(B, G, R, ZERO), 1, 1)),
   ycbcr_fmt(VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16, 1,
             y_plane(VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16, YCBCR_SWIZ(B, G, R, ZERO), 1, 1)),

   ycbcr_fmt(VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16, 3,
             y_plane(VK_FORMAT_R10X6_UNORM_PACK16, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R10X6_UNORM_PACK16, YCBCR_SWIZ(B, ZERO, ZERO, ZERO), 2, 2),
             c_plane(VK_FORMAT_R10X6_UNORM_PACK16, YCBCR_SWIZ(R, ZERO, ZERO, ZERO), 2, 2)),
   ycbcr_fmt(VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16, 2,
             y_plane(VK_FORMAT_R10X6_UNORM_PACK16, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R10X6G10X6_UNORM_2PACK16, YCBCR_SWIZ(B, R, ZERO, ZERO), 2, 2)),
   ycbcr_fmt(VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16, 3,
             y_plane(VK_FORMAT_R10X6_UNORM_PACK16, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R10X6_UNORM_PACK16, YCBCR_SWIZ(B, ZERO, ZERO, ZERO), 2, 1),
             c_plane(VK_FORMAT_R10X6_UNORM_PACK16, YCBCR_SWIZ(R, ZERO, ZERO, ZERO), 2, 1)),
   ycbcr_fmt(VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16, 2,
             y_plane(VK_FORMAT_R10X6_UNORM_PACK16, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R10X6G10X6_UNORM_2PACK16, YCBCR_SWIZ(B, R, ZERO, ZERO), 2, 1)),
   ycbcr_fmt(VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16, 3,
             y_plane(VK_FORMAT_R10X6_UNORM_PACK16, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R10X6_UNORM_PACK16, YCBCR_SWIZ(B, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R10X6_UNORM_PACK16, YCBCR_SWIZ(R, ZERO, ZERO, ZERO), 1, 1)),

   fmt_unsupported(VK_FORMAT_R12X4_UNORM_PACK16),
   fmt_unsupported(VK_FORMAT_R12X4G12X4_UNORM_2PACK16),
   fmt_unsupported(VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16),

   ycbcr_fmt(VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16, 1,
             y_plane(VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16, YCBCR_SWIZ(B, G, R, ZERO), 1, 1)),
   ycbcr_fmt(VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16, 1,
             y_plane(VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16, YCBCR_SWIZ(B, G, R, ZERO), 1, 1)),

   ycbcr_fmt(VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16, 3,
             y_plane(VK_FORMAT_R12X4_UNORM_PACK16, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R12X4_UNORM_PACK16, YCBCR_SWIZ(B, ZERO, ZERO, ZERO), 2, 2),
             c_plane(VK_FORMAT_R12X4_UNORM_PACK16, YCBCR_SWIZ(R, ZERO, ZERO, ZERO), 2, 2)),
   ycbcr_fmt(VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16, 2,
             y_plane(VK_FORMAT_R12X4_UNORM_PACK16, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R12X4G12X4_UNORM_2PACK16, YCBCR_SWIZ(B, R, ZERO, ZERO), 2, 2)),
   ycbcr_fmt(VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16, 3,
             y_plane(VK_FORMAT_R12X4_UNORM_PACK16, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R12X4_UNORM_PACK16, YCBCR_SWIZ(B, ZERO, ZERO, ZERO), 2, 1),
             c_plane(VK_FORMAT_R12X4_UNORM_PACK16, YCBCR_SWIZ(R, ZERO, ZERO, ZERO), 2, 1)),
   ycbcr_fmt(VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16, 2,
             y_plane(VK_FORMAT_R12X4_UNORM_PACK16, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R12X4G12X4_UNORM_2PACK16, YCBCR_SWIZ(B, R, ZERO, ZERO), 2, 1)),
   ycbcr_fmt(VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16, 3,
             y_plane(VK_FORMAT_R12X4_UNORM_PACK16, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R12X4_UNORM_PACK16, YCBCR_SWIZ(B, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R12X4_UNORM_PACK16, YCBCR_SWIZ(R, ZERO, ZERO, ZERO), 1, 1)),

   ycbcr_fmt(VK_FORMAT_G16B16G16R16_422_UNORM, 1,
             y_plane(VK_FORMAT_G16B16G16R16_422_UNORM, YCBCR_SWIZ(B, G, R, ZERO), 1, 1)),
   ycbcr_fmt(VK_FORMAT_B16G16R16G16_422_UNORM, 1,
             y_plane(VK_FORMAT_B16G16R16G16_422_UNORM, YCBCR_SWIZ(B, G, R, ZERO), 1, 1)),

   ycbcr_fmt(VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM, 3,
             y_plane(VK_FORMAT_R16_UNORM, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R16_UNORM, YCBCR_SWIZ(B, ZERO, ZERO, ZERO), 2, 2),
             c_plane(VK_FORMAT_R16_UNORM, YCBCR_SWIZ(R, ZERO, ZERO, ZERO), 2, 2)),
   ycbcr_fmt(VK_FORMAT_G16_B16R16_2PLANE_420_UNORM, 2,
             y_plane(VK_FORMAT_R16_UNORM, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R16G16_UNORM, YCBCR_SWIZ(B, R, ZERO, ZERO), 2, 2)),
   ycbcr_fmt(VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM, 3,
             y_plane(VK_FORMAT_R16_UNORM, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R16_UNORM, YCBCR_SWIZ(B, ZERO, ZERO, ZERO), 2, 1),
             c_plane(VK_FORMAT_R16_UNORM, YCBCR_SWIZ(R, ZERO, ZERO, ZERO), 2, 1)),
   ycbcr_fmt(VK_FORMAT_G16_B16R16_2PLANE_422_UNORM, 2,
             y_plane(VK_FORMAT_R16_UNORM, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R16G16_UNORM, YCBCR_SWIZ(B, R, ZERO, ZERO), 2, 1)),
   ycbcr_fmt(VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM, 3,
             y_plane(VK_FORMAT_R16_UNORM, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R16_UNORM, YCBCR_SWIZ(B, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R16_UNORM, YCBCR_SWIZ(R, ZERO, ZERO, ZERO), 1, 1)),
};

static const struct vk_format_ycbcr_info ycbcr_2plane_444_infos[] = {
   ycbcr_fmt(VK_FORMAT_G8_B8R8_2PLANE_444_UNORM_EXT, 2,
             y_plane(VK_FORMAT_R8_UNORM, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R8G8_UNORM, YCBCR_SWIZ(B, R, ZERO, ZERO), 1, 1)),

   ycbcr_fmt(VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16_EXT, 2,
             y_plane(VK_FORMAT_R10X6_UNORM_PACK16, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R10X6G10X6_UNORM_2PACK16, YCBCR_SWIZ(B, R, ZERO, ZERO), 1, 1)),

   ycbcr_fmt(VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16_EXT, 2,
             y_plane(VK_FORMAT_R12X4_UNORM_PACK16, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R12X4G12X4_UNORM_2PACK16, YCBCR_SWIZ(B, R, ZERO, ZERO), 1, 1)),

   ycbcr_fmt(VK_FORMAT_G16_B16R16_2PLANE_444_UNORM_EXT, 2,
             y_plane(VK_FORMAT_R16_UNORM, YCBCR_SWIZ(G, ZERO, ZERO, ZERO), 1, 1),
             c_plane(VK_FORMAT_R16G16_UNORM, YCBCR_SWIZ(B, R, ZERO, ZERO), 1, 1)),
};

const struct vk_format_ycbcr_info *
vk_format_get_ycbcr_info(VkFormat format)
{
   uint32_t enum_offset = VK_ENUM_OFFSET(format);
   uint32_t ext_number = VK_ENUM_EXTENSION(format);
   const struct vk_format_ycbcr_info *info;
   switch (ext_number) {
   case _VK_KHR_sampler_ycbcr_conversion_number:
      if (enum_offset >= ARRAY_SIZE(ycbcr_infos))
         return NULL;
      info = &ycbcr_infos[enum_offset];
      break;

   case _VK_EXT_ycbcr_2plane_444_formats_number:
      if (enum_offset >= ARRAY_SIZE(ycbcr_2plane_444_infos))
         return NULL;
      info = &ycbcr_2plane_444_infos[enum_offset];
      break;

   default:
      return NULL;
   }

   if (info->n_planes == 0)
      return NULL;

   return info;
}

static uint32_t
swizzled_color_component(const VkClearColorValue *color,
                         VkComponentSwizzle swizzle,
                         uint32_t comp, bool is_int)
{
   switch (swizzle) {
   case VK_COMPONENT_SWIZZLE_IDENTITY: return color->uint32[comp];
   case VK_COMPONENT_SWIZZLE_ZERO:     return 0;
   case VK_COMPONENT_SWIZZLE_ONE:      return is_int ? 1 : 0x3f800000;
   case VK_COMPONENT_SWIZZLE_R:        return color->uint32[0];
   case VK_COMPONENT_SWIZZLE_G:        return color->uint32[1];
   case VK_COMPONENT_SWIZZLE_B:        return color->uint32[2];
   case VK_COMPONENT_SWIZZLE_A:        return color->uint32[3];
   default: unreachable("Invalid component swizzle");
   }
}

VkClearColorValue
vk_swizzle_color_value(VkClearColorValue color,
                       VkComponentMapping swizzle, bool is_int)
{
   return (VkClearColorValue) { .uint32 = {
      swizzled_color_component(&color, swizzle.r, 0, is_int),
      swizzled_color_component(&color, swizzle.g, 1, is_int),
      swizzled_color_component(&color, swizzle.b, 2, is_int),
      swizzled_color_component(&color, swizzle.a, 3, is_int),
   }};
}
