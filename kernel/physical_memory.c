/* PCH must be first */
#include "malloc.h"
#include "assert.h"
#include "arch/memory.h"

#include "physical_memory.h"

struct OS216_PageRegion{
    bool alloced, mapped; /* Large is unused. */
    struct OS216_PageRegionInfo info;
    struct OS216_PageRegion *next;
} *regions = NULL;

void OS216_LockRegionAllocator(){
    /* TODO: When we get SMP! */
}

void OS216_UnlockRegionAllocator(){
    /* TODO: When we get SMP! */
}

struct OS216_PageRegion *OS216_AllocateRegion(unsigned min_length,
    struct OS216_PageRegion *hint){
    
    const unsigned page_size = OS216_GetPageSize();
    
    /* If it didn't divide evenly add one extra page. */
    const unsigned num_pages = (min_length / page_size) +
        ((min_length % page_size) ? 1 : 0);
    
    OS216_ASSERT(min_length > 0, "Invalid length");
    OS216_ASSERT(num_pages > 0, NULL);
    
    /* Initialize the physical memory region list if needed. */
    if(OS216_UNLIKELY(regions == NULL)){
        OS216_ASSERT(hint == NULL, "Invalid hint at initialization");
        regions = malloc(sizeof(struct OS216_PageRegion));
        regions->alloced = true;
        regions->mapped = false;
        regions->info.start = OS216_GetMappableStart();
        regions->info.num_pages = num_pages;
        
        /* The last region is the free space. */
        regions->next = malloc(sizeof(struct OS216_PageRegion));
        
        regions->next->alloced = false;
        regions->next->mapped = false;
        regions->next->info.start =
            regions->info.start + (num_pages * page_size);
        regions->next->info.num_pages =
            ((uint8_t*)0xFFFFFFFF - regions->next->info.start) / page_size;
        return regions;
    }
    else{
        /* Find the first open region we can use or split. */
        struct OS216_PageRegion *cur_region = hint ? hint : regions;
        /* Only mapped pages should escape */
        OS216_ASSERT(hint == NULL || hint->alloced == true, "Invalid hint");
        OS216_ASSERT(cur_region != NULL, "Invalid region base");
        do{
            const unsigned cur_pages = cur_region->info.num_pages;
            OS216_ASSERT(cur_pages > 0, "Invalid page count in region");
            if(cur_region->alloced)
                continue;
            
            if(cur_pages >= num_pages){
                /* We're willing to just let a single extra page slip in to
                 * avoid extra allocations. */
                if(cur_pages - num_pages > 1){
                    struct OS216_PageRegion *const next =
                        malloc(sizeof(struct OS216_PageRegion));
                    next->alloced = false;
                    next->mapped = false;
                    next->info.num_pages = cur_pages - num_pages;
                    next->info.start = cur_region->info.start +
                        (num_pages * page_size);
                    
                    cur_region->info.num_pages = num_pages;
                    next->next = cur_region->next;
                    cur_region->next = next;
                }
            }
            
            cur_region->alloced = true;
            OS216_ASSERT(cur_region->mapped == false,
                "Unallocated but mapped region found.");
            return cur_region;
        }while(OS216_LIKELY(cur_region = cur_region->next));
        
        if(hint != NULL && hint != regions)
            return OS216_AllocateRegion(min_length, NULL);
        
        OS216_FATAL("Out of physical memory!");
    }
}

struct OS216_PageRegionInfo *OS216_GetPageRegionInfo(
    struct OS216_PageRegion *region){
    return &region->info;
}

void OS216_MapPhysicalMemory(struct OS216_PageRegion *region, void *virt){
    region->mapped = true;
    /*OS216_MapPhysicalPages(region->info.start, region->info.num_pages, virt); */ (void)virt;
}

void OS216_FreeRegion(struct OS216_PageRegion *region){
    if(region->mapped){
/*        OS216_UnmapPhysicalPages(region->info.start, region->info.num_pages); */
        region->mapped = false;
    }
    
    /* TODO: We could atomically set this to avoid any locks here. */
    /* TODO: Merge with nearby free regions? */
    region->alloced = false;
}
