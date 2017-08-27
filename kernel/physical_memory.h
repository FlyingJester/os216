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

#ifndef OS216_KERNEL_PHYSICAL_MEMORY
#define OS216_KERNEL_PHYSICAL_MEMORY
#pragma once

/*****************************************************************************/

#include "attributes.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/*****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/

struct OS216_PageRegion;

/*****************************************************************************/

struct OS216_PageRegionInfo{
    uint8_t *start; /* Linear address */
    unsigned short num_pages;
};

/*****************************************************************************/
/* Lock must be acquired to call allocate or free. It's safe to call get info
 * on a region and examine its values without holding the lock. */
void OS216_LockRegionAllocator(void);

/*****************************************************************************/

void OS216_UnlockRegionAllocator(void);

/*****************************************************************************/

OS216_MALLOC_ATTR struct OS216_PageRegion *OS216_AllocateRegion(
    unsigned min_size,
    struct OS216_PageRegion *hint);

/*****************************************************************************/

void OS216_MapPhysicalMemory(struct OS216_PageRegion *phys, void *virt);

void OS216_FreeRegion(struct OS216_PageRegion *handle);

/*****************************************************************************/

OS216_PURE struct OS216_PageRegionInfo *OS216_GetPageRegionInfo(
    struct OS216_PageRegion *region);

/*****************************************************************************/

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OS216_KERNEL_PHYSICAL_MEMORY */
