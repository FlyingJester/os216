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

#ifndef OS216_STDLIB_STDLIB_H
#define OS216_STDLIB_STDLIB_H
#pragma once

#include <stdint.h>
#include <stddef.h>

/*****************************************************************************/

#ifndef NULL
#define NULL ((void*)0)
#endif

/*****************************************************************************/

int atoi(const char *c);

/*****************************************************************************/

long atol(const char *c);

/*****************************************************************************/

int64_t atoll(const char *c);

/*****************************************************************************/

unsigned long strtoul(const char *__restrict__ str,
    const char **__restrict__ end,
    unsigned base);

/*****************************************************************************/

uint64_t strtoull(const char *__restrict__ str,
    const char **__restrict__ end,
    unsigned base);

/*****************************************************************************/

void qsort(void *ptr, size_t count, size_t size,
    int(*compare)(const void *, const void *));

#endif /* OS216_STDLIB_STDLIB_H */
