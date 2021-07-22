/*
 * Copyright (C) 2020 Collabora, Ltd.
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors (Collabora):
 *      Alyssa Rosenzweig <alyssa.rosenzweig@collabora.com>
 */

#ifndef __PAN_LOWER_FRAMEBUFFER_H
#define __PAN_LOWER_FRAMEBUFFER_H

#include "compiler/nir/nir.h"
#include "util/format/u_format.h"

/* NATIVE formats can use a typed load/store. PACK formats cannot but can use a
 * typed pack/unpack instruction. SOFTWARE formats are lowered */

enum pan_format_class {
        PAN_FORMAT_NATIVE,
        PAN_FORMAT_PACK,
        PAN_FORMAT_SOFTWARE
};

nir_alu_type pan_unpacked_type_for_format(const struct util_format_description *desc);
enum pan_format_class pan_format_class_load(const struct util_format_description *desc, unsigned quirks);
enum pan_format_class pan_format_class_store(const struct util_format_description *desc, unsigned quirks);

bool pan_lower_framebuffer(nir_shader *shader, const enum pipe_format *rt_fmts,
                           bool is_blend, unsigned quirks);

#endif
