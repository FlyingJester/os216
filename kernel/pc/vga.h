/* 
 *  Copyright (c) 2015-2017 Martin McDonough.  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 * 
 * - Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 * 
 * - Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 
 * - Products derived from this software may not be called "os216", nor may
 *     "216" appear in their name, without prior written permission of
 *     the copyright holders.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef OS216_VGA_H
#define OS216_VGA_H
#pragma once

/*****************************************************************************/

#include "pc_print.h"

/*****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/

extern const unsigned os216_vga_w, os216_vga_h;

/*****************************************************************************/

void OS216_VGA_PutString(unsigned x,
    unsigned y,
    enum OS216_PC_PrintMode,
    unsigned n,
    const char *msg);

/*****************************************************************************/

void OS216_VGA_Clear(unsigned x,
    unsigned y,
    enum OS216_PC_PrintMode mode,
    unsigned n);

/*****************************************************************************/

void OS216_VGA_ClearLine(unsigned y, enum OS216_PC_PrintMode mode);

/*****************************************************************************/

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OS216_VGA_H */
