/*
 * Copyright © 2018 Intel Corporation
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "anv_android.h"

VkResult
anv_image_from_gralloc(VkDevice device_h,
                       const VkImageCreateInfo *base_info,
                       const VkNativeBufferANDROID *gralloc_info,
                       const VkAllocationCallbacks *alloc,
                       VkImage *pImage)
{
   return VK_ERROR_EXTENSION_NOT_PRESENT;
}

uint64_t
anv_ahw_usage_from_vk_usage(const VkImageCreateFlags vk_create,
                            const VkImageUsageFlags vk_usage)
{
   return 0;
}

VkResult
anv_import_ahw_memory(VkDevice device_h,
                      struct anv_device_memory *mem,
                      const VkImportAndroidHardwareBufferInfoANDROID *info)
{
   return VK_ERROR_EXTENSION_NOT_PRESENT;
}

VkResult
anv_create_ahw_memory(VkDevice device_h,
                      struct anv_device_memory *mem,
                      const VkMemoryAllocateInfo *pAllocateInfo)
{
   return VK_ERROR_EXTENSION_NOT_PRESENT;
}

VkResult
anv_image_from_external(VkDevice device_h,
                        const VkImageCreateInfo *base_info,
                        const struct VkExternalMemoryImageCreateInfo *create_info,
                        const VkAllocationCallbacks *alloc,
                        VkImage *out_image_h)
{
   return VK_ERROR_EXTENSION_NOT_PRESENT;
}
