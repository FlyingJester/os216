#pragma once
#ifndef OS216_PHYSICAL_MEMORY
#define OS216_PHYSICAL_MEMORY

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "attributes.h"

#ifdef __cplusplus
extern "C" {
#endif

struct OS216_PageRegion;

struct OS216_PageRegionInfo{
    uint8_t *start; /* Linear address */
    unsigned short num_pages;
};

/* Lock must be acquired to call allocate or free. It's safe to call get info
 * on a region and examine its values without holding the lock. */
void OS216_LockRegionAllocator(void);
void OS216_UnlockRegionAllocator(void);

OS216_MALLOC_ATTR struct OS216_PageRegion *OS216_AllocateRegion(
    unsigned min_size,
    struct OS216_PageRegion *hint);

void OS216_MapPhysicalMemory(struct OS216_PageRegion *phys, void *virt);

void OS216_FreeRegion(struct OS216_PageRegion *handle);

OS216_NOT_NULL struct OS216_PageRegionInfo *OS216_GetPageRegionInfo(
    struct OS216_PageRegion *region);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OS216_PHYSICAL_MEMORY */
