/*
 * Copyright 2017 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL VMWARE AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef VK_EXTENSIONS_H
#define VK_EXTENSIONS_H

#include <stdbool.h>


#define VK_INSTANCE_EXTENSION_COUNT 34

extern const VkExtensionProperties vk_instance_extensions[];

struct vk_instance_extension_table {
   union {
      bool extensions[VK_INSTANCE_EXTENSION_COUNT];
      struct {
         bool KHR_android_surface;
         bool KHR_device_group_creation;
         bool KHR_display;
         bool KHR_external_fence_capabilities;
         bool KHR_external_memory_capabilities;
         bool KHR_external_semaphore_capabilities;
         bool KHR_get_display_properties2;
         bool KHR_get_physical_device_properties2;
         bool KHR_get_surface_capabilities2;
         bool KHR_surface;
         bool KHR_surface_protected_capabilities;
         bool KHR_wayland_surface;
         bool KHR_win32_surface;
         bool KHR_xcb_surface;
         bool KHR_xlib_surface;
         bool EXT_acquire_drm_display;
         bool EXT_acquire_xlib_display;
         bool EXT_debug_report;
         bool EXT_debug_utils;
         bool EXT_direct_mode_display;
         bool EXT_directfb_surface;
         bool EXT_display_surface_counter;
         bool EXT_headless_surface;
         bool EXT_metal_surface;
         bool EXT_swapchain_colorspace;
         bool EXT_validation_features;
         bool EXT_validation_flags;
         bool FUCHSIA_imagepipe_surface;
         bool GGP_stream_descriptor_surface;
         bool MVK_ios_surface;
         bool MVK_macos_surface;
         bool NN_vi_surface;
         bool NV_external_memory_capabilities;
         bool QNX_screen_surface;
      };
   };
};


#define VK_DEVICE_EXTENSION_COUNT 229

extern const VkExtensionProperties vk_device_extensions[];

struct vk_device_extension_table {
   union {
      bool extensions[VK_DEVICE_EXTENSION_COUNT];
      struct {
        bool KHR_8bit_storage;
        bool KHR_16bit_storage;
        bool KHR_acceleration_structure;
        bool KHR_bind_memory2;
        bool KHR_buffer_device_address;
        bool KHR_copy_commands2;
        bool KHR_create_renderpass2;
        bool KHR_dedicated_allocation;
        bool KHR_deferred_host_operations;
        bool KHR_depth_stencil_resolve;
        bool KHR_descriptor_update_template;
        bool KHR_device_group;
        bool KHR_display_swapchain;
        bool KHR_draw_indirect_count;
        bool KHR_driver_properties;
        bool KHR_external_fence;
        bool KHR_external_fence_fd;
        bool KHR_external_fence_win32;
        bool KHR_external_memory;
        bool KHR_external_memory_fd;
        bool KHR_external_memory_win32;
        bool KHR_external_semaphore;
        bool KHR_external_semaphore_fd;
        bool KHR_external_semaphore_win32;
        bool KHR_format_feature_flags2;
        bool KHR_fragment_shading_rate;
        bool KHR_get_memory_requirements2;
        bool KHR_image_format_list;
        bool KHR_imageless_framebuffer;
        bool KHR_incremental_present;
        bool KHR_maintenance1;
        bool KHR_maintenance2;
        bool KHR_maintenance3;
        bool KHR_maintenance4;
        bool KHR_multiview;
        bool KHR_performance_query;
        bool KHR_pipeline_executable_properties;
        bool KHR_pipeline_library;
        bool KHR_portability_subset;
        bool KHR_present_id;
        bool KHR_present_wait;
        bool KHR_push_descriptor;
        bool KHR_ray_query;
        bool KHR_ray_tracing_pipeline;
        bool KHR_relaxed_block_layout;
        bool KHR_sampler_mirror_clamp_to_edge;
        bool KHR_sampler_ycbcr_conversion;
        bool KHR_separate_depth_stencil_layouts;
        bool KHR_shader_atomic_int64;
        bool KHR_shader_clock;
        bool KHR_shader_draw_parameters;
        bool KHR_shader_float16_int8;
        bool KHR_shader_float_controls;
        bool KHR_shader_integer_dot_product;
        bool KHR_shader_non_semantic_info;
        bool KHR_shader_subgroup_extended_types;
        bool KHR_shader_subgroup_uniform_control_flow;
        bool KHR_shader_terminate_invocation;
        bool KHR_shared_presentable_image;
        bool KHR_spirv_1_4;
        bool KHR_storage_buffer_storage_class;
        bool KHR_swapchain;
        bool KHR_swapchain_mutable_format;
        bool KHR_synchronization2;
        bool KHR_timeline_semaphore;
        bool KHR_uniform_buffer_standard_layout;
        bool KHR_variable_pointers;
        bool KHR_video_decode_queue;
        bool KHR_video_encode_queue;
        bool KHR_video_queue;
        bool KHR_vulkan_memory_model;
        bool KHR_win32_keyed_mutex;
        bool KHR_workgroup_memory_explicit_layout;
        bool KHR_zero_initialize_workgroup_memory;
        bool EXT_4444_formats;
        bool EXT_astc_decode_mode;
        bool EXT_blend_operation_advanced;
        bool EXT_buffer_device_address;
        bool EXT_calibrated_timestamps;
        bool EXT_color_write_enable;
        bool EXT_conditional_rendering;
        bool EXT_conservative_rasterization;
        bool EXT_custom_border_color;
        bool EXT_debug_marker;
        bool EXT_depth_clip_enable;
        bool EXT_depth_range_unrestricted;
        bool EXT_descriptor_indexing;
        bool EXT_device_memory_report;
        bool EXT_discard_rectangles;
        bool EXT_display_control;
        bool EXT_extended_dynamic_state;
        bool EXT_extended_dynamic_state2;
        bool EXT_external_memory_dma_buf;
        bool EXT_external_memory_host;
        bool EXT_filter_cubic;
        bool EXT_fragment_density_map;
        bool EXT_fragment_density_map2;
        bool EXT_fragment_shader_interlock;
        bool EXT_full_screen_exclusive;
        bool EXT_global_priority;
        bool EXT_global_priority_query;
        bool EXT_hdr_metadata;
        bool EXT_host_query_reset;
        bool EXT_image_drm_format_modifier;
        bool EXT_image_robustness;
        bool EXT_index_type_uint8;
        bool EXT_inline_uniform_block;
        bool EXT_line_rasterization;
        bool EXT_load_store_op_none;
        bool EXT_memory_budget;
        bool EXT_memory_priority;
        bool EXT_multi_draw;
        bool EXT_pageable_device_local_memory;
        bool EXT_pci_bus_info;
        bool EXT_physical_device_drm;
        bool EXT_pipeline_creation_cache_control;
        bool EXT_pipeline_creation_feedback;
        bool EXT_post_depth_coverage;
        bool EXT_primitive_topology_list_restart;
        bool EXT_private_data;
        bool EXT_provoking_vertex;
        bool EXT_queue_family_foreign;
        bool EXT_rgba10x6_formats;
        bool EXT_robustness2;
        bool EXT_sample_locations;
        bool EXT_sampler_filter_minmax;
        bool EXT_scalar_block_layout;
        bool EXT_separate_stencil_usage;
        bool EXT_shader_atomic_float;
        bool EXT_shader_atomic_float2;
        bool EXT_shader_demote_to_helper_invocation;
        bool EXT_shader_image_atomic_int64;
        bool EXT_shader_stencil_export;
        bool EXT_shader_subgroup_ballot;
        bool EXT_shader_subgroup_vote;
        bool EXT_shader_viewport_index_layer;
        bool EXT_subgroup_size_control;
        bool EXT_texel_buffer_alignment;
        bool EXT_texture_compression_astc_hdr;
        bool EXT_tooling_info;
        bool EXT_transform_feedback;
        bool EXT_validation_cache;
        bool EXT_vertex_attribute_divisor;
        bool EXT_vertex_input_dynamic_state;
        bool EXT_video_decode_h264;
        bool EXT_video_decode_h265;
        bool EXT_video_encode_h264;
        bool EXT_ycbcr_2plane_444_formats;
        bool EXT_ycbcr_image_arrays;
        bool AMD_buffer_marker;
        bool AMD_device_coherent_memory;
        bool AMD_display_native_hdr;
        bool AMD_draw_indirect_count;
        bool AMD_gcn_shader;
        bool AMD_gpu_shader_half_float;
        bool AMD_gpu_shader_int16;
        bool AMD_memory_overallocation_behavior;
        bool AMD_mixed_attachment_samples;
        bool AMD_negative_viewport_height;
        bool AMD_pipeline_compiler_control;
        bool AMD_rasterization_order;
        bool AMD_shader_ballot;
        bool AMD_shader_core_properties;
        bool AMD_shader_core_properties2;
        bool AMD_shader_explicit_vertex_parameter;
        bool AMD_shader_fragment_mask;
        bool AMD_shader_image_load_store_lod;
        bool AMD_shader_info;
        bool AMD_shader_trinary_minmax;
        bool AMD_texture_gather_bias_lod;
        bool ANDROID_external_memory_android_hardware_buffer;
        bool ANDROID_native_buffer;
        bool FUCHSIA_buffer_collection;
        bool FUCHSIA_external_memory;
        bool FUCHSIA_external_semaphore;
        bool GGP_frame_token;
        bool GOOGLE_decorate_string;
        bool GOOGLE_display_timing;
        bool GOOGLE_hlsl_functionality1;
        bool GOOGLE_user_type;
        bool HUAWEI_invocation_mask;
        bool HUAWEI_subpass_shading;
        bool IMG_filter_cubic;
        bool IMG_format_pvrtc;
        bool INTEL_performance_query;
        bool INTEL_shader_integer_functions2;
        bool NVX_binary_import;
        bool NVX_image_view_handle;
        bool NVX_multiview_per_view_attributes;
        bool NV_acquire_winrt_display;
        bool NV_clip_space_w_scaling;
        bool NV_compute_shader_derivatives;
        bool NV_cooperative_matrix;
        bool NV_corner_sampled_image;
        bool NV_coverage_reduction_mode;
        bool NV_dedicated_allocation;
        bool NV_dedicated_allocation_image_aliasing;
        bool NV_device_diagnostic_checkpoints;
        bool NV_device_diagnostics_config;
        bool NV_device_generated_commands;
        bool NV_external_memory;
        bool NV_external_memory_rdma;
        bool NV_external_memory_win32;
        bool NV_fill_rectangle;
        bool NV_fragment_coverage_to_color;
        bool NV_fragment_shader_barycentric;
        bool NV_fragment_shading_rate_enums;
        bool NV_framebuffer_mixed_samples;
        bool NV_geometry_shader_passthrough;
        bool NV_glsl_shader;
        bool NV_inherited_viewport_scissor;
        bool NV_mesh_shader;
        bool NV_ray_tracing;
        bool NV_ray_tracing_motion_blur;
        bool NV_representative_fragment_test;
        bool NV_sample_mask_override_coverage;
        bool NV_scissor_exclusive;
        bool NV_shader_image_footprint;
        bool NV_shader_sm_builtins;
        bool NV_shader_subgroup_partitioned;
        bool NV_shading_rate_image;
        bool NV_viewport_array2;
        bool NV_viewport_swizzle;
        bool NV_win32_keyed_mutex;
        bool QCOM_render_pass_shader_resolve;
        bool QCOM_render_pass_store_ops;
        bool QCOM_render_pass_transform;
        bool QCOM_rotated_copy_commands;
        bool VALVE_mutable_descriptor_type;
      };
   };
};

struct vk_physical_device;

#ifdef ANDROID
extern const struct vk_instance_extension_table vk_android_allowed_instance_extensions;
extern const struct vk_device_extension_table vk_android_allowed_device_extensions;
#endif

#endif /* VK_EXTENSIONS_H */
