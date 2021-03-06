/* 
 *  Copyright (c) 2016-2017 Martin McDonough.  All rights reserved.
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
 
#ifndef OS216_KERNEL_MALLOC_H
#define OS216_KERNEL_MALLOC_H
/* No #pragma once in pch */

/*****************************************************************************/

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "attributes.h"

/*****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/

OS216_MALLOC_ATTR void *malloc(size_t amount);

/*****************************************************************************/

OS216_MALLOC_ATTR void *calloc(size_t count, size_t amount);

/*****************************************************************************/

void *realloc(void *mem, size_t new_amount);

/*****************************************************************************/

void free(void *mem);

/*****************************************************************************/

void OS216_InitKernelMemory(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OS216_KERNEL_MALLOC_H */
