/* 
 *  Copyright (c) 2017 Martin McDonough.  All rights reserved.
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

#ifndef OS216_KERNEL_CPP_HPP
#define OS216_KERNEL_CPP_HPP
// No #pragma once in pch

/*****************************************************************************/

#include <stdint.h>
#include <stddef.h>

#include "malloc.h"

#include <new>

/*****************************************************************************/

OS216_MALLOC_ATTR void *operator new(size_t size);

/*****************************************************************************/

OS216_MALLOC_ATTR void *operator new[](size_t size);

/*****************************************************************************/

void operator delete(void *mem);

/*****************************************************************************/

void operator delete[](void *mem);

/*****************************************************************************/

inline void *operator new(size_t, void *p) { return p; }

/*****************************************************************************/

inline void *operator new[](size_t, void *p) { return p; }

/*****************************************************************************/

inline void operator delete(void *, void *) { } // placement delete, doesn't free

/*****************************************************************************/

inline void operator delete[](void *, void *) { } // placement delete, doesn't free

/*****************************************************************************/

#endif // OS216_KERNEL_CPP_HPP
