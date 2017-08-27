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

/* PCH must be first. */
#include "malloc.h"

#include "string.h"

#include "platform/fatal.h"
#include "platform/print.h"

/*
 * The heap is divided into two sections, the large and small heap.
 *
 * The small heap consists of 512 byte frames, each with a bitmap at the start
 * indicating used sections of the frame. Every allocation has a 16-bit entry
 * at the start (two bytes before the address returned by malloc).
 * The bitmap is 64 bits long. Every bit of the bitmap equates to a single 64
 * bit section of the frame. So, 64 * (64 / sizeof(uint64_t)) = 512 bytes for
 * the frame.
 * This is a tiny bit wasteful, as 16 bits aren't entirely needed for entries.
 * We could limit entries to 255 bytes to make the size one byte, or use a UTF
 * like encoding of length so that only entries with a size greater than, for
 * instance, 128 would need two bytes to represent). The frame could also be
 * eight bytes bigger anyway, as the bitmap includes an always used entry for
 * itself.
 *
 * The large heap is tracked solely by a singly-linked list of
 * OS216_KernelLargeHeapData structures. Each structure contains a 'used' flag,
 * a size, and the next element in the list. These structures are allocated
 * from the small heap. To determine a starting location of a large heap entry
 * the sizes of all previous entries must be summed up.
 * This could be improved by keeping a link to the last freed element, or if no
 * element is free (or the next free element is unknown) the first element.
 * This would reduce seek times, although given the relatively small size of
 * the large heap this is probably not that important.
 */

#define OS216_LARGE_PAGE_SIZE 4096

/*****************************************************************************/

#define OS216_SMALL_PAGE_SIZE (64 * 8)

/*****************************************************************************/

#define OS216_NUM_LARGE_HEAP_PAGES 32

/*****************************************************************************/

#define OS216_NUM_SMALL_HEAP_PAGES 256

/*****************************************************************************/

static uint8_t OS216_KernelLargeHeap[OS216_LARGE_PAGE_SIZE *
    OS216_NUM_LARGE_HEAP_PAGES];

/*****************************************************************************/

static uint8_t OS216_KernelSmallHeap[OS216_SMALL_PAGE_SIZE *
    OS216_NUM_SMALL_HEAP_PAGES];

/*****************************************************************************/

#define OS216_LARGE_HEAP_OBJECT_SIZE OS216_PAGE_SIZE

/*****************************************************************************/

OS216_COLD
void OS216_InitKernelMemory(void){
    unsigned i;
    for(i = 0; i < OS216_NUM_SMALL_HEAP_PAGES; i++){
        uint64_t *const bitmap_addr =
            (uint64_t*)(OS216_KernelSmallHeap + (i * OS216_SMALL_PAGE_SIZE));
        bitmap_addr[0] = 1;
    }
}

/*****************************************************************************/
/* Heap datas are always stored strictly ascending */
struct OS216_KernelLargeHeapData{
    unsigned char used;
    unsigned short size;
    struct OS216_KernelLargeHeapData *next;
};

/*****************************************************************************/

static struct OS216_KernelLargeHeapData os216_kernel_large_heap_data = {
    1, 0, (void*)0
};

/*****************************************************************************/

static uint64_t os216_small_get_needed_bitmask(uint32_t amount, unsigned *out_bit_shift){
    /* Size is the 16-bit size entry, followed by the number of 8-byte
     * parts we need. Add one when anything is lost by the shift. */
    const uint16_t size = 2 + (amount >> 3) + ((amount & 0x07) ? 1 : 0);
    
    /* TODO: inline asm to check if bitmap even has enough bits to
     * allow needed, using the popcount. */
    
    /* needed will have size bits set in a row. We will & that with the
     * bitmap at various shifts to find a location that has enough
     * parts open in a row.
     */
    uint64_t needed = 1 << size;
    needed--;
    out_bit_shift[0] = size;
    return needed;
}

/*****************************************************************************/

OS216_MALLOC_ATTR static void *large_malloc(size_t amount){
    /* At is the current count. We have to sum the data's sizes to know
     * what address they indicate, since they only store their sizes and
     * are stored in a strictly ascending order. pocket_size is the current
     * size of unused pages. pocket_data is the data starting the current
     * pocket. */
    unsigned at = 0, pocket_size = 0, pocket_at = 0;
    struct OS216_KernelLargeHeapData *data = &os216_kernel_large_heap_data,
        *pocket_data = (void*)0;
os216_malloc_find_frame:
    
    if(!data->used){
        if(data->size >= amount){
            data->used = 1;
            return OS216_KernelLargeHeap + at;
        }
        else{
            if(pocket_data){
                pocket_size += data->size;
                if(pocket_size >= amount){
                    const struct OS216_KernelLargeHeapData *next =
                        pocket_data->next;
                    pocket_data->next = data->next;
                    pocket_data->used = 1;
                    pocket_data->size = pocket_size;
                    while(next != data){
                        void *const destroy = (void*)next;
                        next = next->next;
                        free(destroy);
                    }
                    return OS216_KernelLargeHeap + pocket_at;
                }
            }
            else{
                pocket_size = data->size;
                pocket_data = data;
                pocket_at = at;
            }
        }
    }
    else{
        pocket_data = (void*)0;
        pocket_size = 0;
    }
    
    at += data->size;
    if(data->next){
        data = data->next;
        goto os216_malloc_find_frame;
    }
    else{
        struct OS216_KernelLargeHeapData *const next_data =
            malloc(sizeof(struct OS216_KernelLargeHeapData));
        
        next_data->size = amount;
        next_data->used = 1;
        next_data->next = (void*)0;
        data->next = next_data;
        
        return OS216_KernelLargeHeap + at;
    }
}

/*****************************************************************************/

OS216_MALLOC_ATTR static void *small_malloc(size_t amount){
    unsigned i;
    for(i = 0; OS216_LIKELY(i < OS216_NUM_SMALL_HEAP_PAGES); i++){
        uint8_t *const bitmap_addr =
            OS216_KernelSmallHeap + (i * OS216_SMALL_PAGE_SIZE);
         /* Same as OS216_KernelSmallHeap + (i * OS216_PAGE_SIZE); */
        
        /* or by one to mark the bitmap. */
        const uint64_t bitmap = *((uint64_t*)bitmap_addr);
        
        /* Find a slot in the bitmap with `size' empty bits in a row. Start
         * at 1 because we know the first entry is taken by the bitmap. */
        unsigned amount_bit_shift;
        
        /* Always shift by one extra, to offset for the bitmap itself. */
        uint64_t needed = os216_small_get_needed_bitmask(amount, &amount_bit_shift) << 1;
        unsigned extra_shift = 1; 
        
        if(OS216_UNLIKELY((bitmap & 1) != 1)){
            OS216_FATAL("Heap corruption detected: bitmap has invalid identity bit");
        }
        
        /* Search for a stretch of empty bits in a row that match needed. */
        while((bitmap & needed) != 0 && (amount_bit_shift + extra_shift < 64)){
            needed <<= 1;
            extra_shift++;
        }
        
        /* No open slots. Check next page. */
        if(amount_bit_shift + extra_shift == 64)
            continue;
        
        /* There was room here. */
        ((uint64_t*)bitmap_addr)[0] |= needed;
        
        /* n is the first part of the page we can use. Add the size entry. */
        uint16_t *const size_addr =
            (uint16_t*)(bitmap_addr + (extra_shift << 3));
        size_addr[0] = amount;
        return size_addr+1;
    }
    OS216_FATAL("Out of kernel memory!");
    return (void*)0;
}

/*****************************************************************************/

OS216_MALLOC_ATTR void *malloc(size_t amount){
    if(OS216_UNLIKELY(amount == 0))
        return (void*)0;
    else if(amount >= (OS216_SMALL_PAGE_SIZE >> 1))
        return large_malloc(amount);
    else
        return small_malloc(amount);
}

/*****************************************************************************/

OS216_MALLOC_ATTR void *calloc(size_t count, size_t amount){
    uint8_t *const data = malloc(count * amount);
    unsigned i;
    for(i = 0; i < count * amount; i++){
        data[i] = 0;
    }
    return data;
}

/*****************************************************************************/

OS216_MEMORY_PURE unsigned is_small(const void *mem);
unsigned is_small(const void *mem){
    const uintptr_t small_heap_start = (uintptr_t)OS216_KernelSmallHeap,
        small_heap_end = small_heap_start + sizeof(OS216_KernelSmallHeap);
    return ((uintptr_t)mem >= small_heap_start && (uintptr_t)mem <= small_heap_end);
}

/*****************************************************************************/

OS216_MEMORY_PURE unsigned is_large(const void *mem);
unsigned is_large(const void *mem){
    const uintptr_t large_heap_start = (uintptr_t)OS216_KernelLargeHeap,
        large_heap_end = large_heap_start + sizeof(OS216_KernelLargeHeap);
    return ((uintptr_t)mem >= large_heap_start && (uintptr_t)mem <= large_heap_end);
}

/*****************************************************************************/

void *realloc(void *mem, size_t new_amount){
    (void)mem;
    (void)new_amount;
    OS216_FATAL("realloc not implemented yet!");
    return mem;
}

/*****************************************************************************/

static void small_free(void *given_addr){
    /* Watcom doesn't like negative indices */
    const void *mem = (((uint16_t*)given_addr)-1);
    const uint16_t amount = *((uint16_t*)mem);
    
    /* Determine the frame this memory is from. */
    const uintptr_t mem_i = (uintptr_t)mem,
        /* Heap data. */
        small_heap_start = (uintptr_t)OS216_KernelSmallHeap,
        small_heap_end = small_heap_start + sizeof(OS216_KernelSmallHeap),
        heap_offset = small_heap_start & 0x00000FFF,
        /* Use alignment to allow bitshifts to determine the frame number. */
        small_heap_align = small_heap_start - heap_offset,
        mem_i_align = mem_i - heap_offset,
        frame_number = (mem_i_align  / OS216_SMALL_PAGE_SIZE) -
            (small_heap_align / OS216_SMALL_PAGE_SIZE),
        /* -2 for the size entry */
        mem_frame_offset = (mem_i - small_heap_start) & 0x00000FFF;
    
    unsigned amount_bit_shift;
    uint64_t needed = os216_small_get_needed_bitmask(amount, &amount_bit_shift);
    
    if(OS216_UNLIKELY(amount == 0))
        OS216_FATAL("Heap corruption detected: zero-length entry in small heap");
    
    if(OS216_UNLIKELY(mem_frame_offset & 0x07))
        OS216_FATAL("Heap corruption detected: unaligned free call in small heap");
    
    /* Bitsift needed by the offset into the frame */
    needed <<= (mem_frame_offset >> 3);
    
    /* The bitmap is the first 64 bits of
     * OS216_KernelSmallHeap + (frame_number * OS216_SMALL_PAGE_SIZE) */
    uint64_t *const bitmap_addr =
        (uint64_t*)(((uint8_t *)OS216_KernelSmallHeap) +
            (frame_number * OS216_SMALL_PAGE_SIZE));
    
    if(OS216_UNLIKELY((uintptr_t)bitmap_addr > small_heap_end))
        OS216_FATAL("Heap corruption detected: Invalid bitmap size in allocator frame");
    
    if(OS216_UNLIKELY((bitmap_addr[0] & needed) != needed))
        OS216_FATAL("Heap corruption detected: bitmap does not match entry in small heap");
    
    /* Clear this section of the bitmap. */
    bitmap_addr[0] &= ~needed;
}

/*****************************************************************************/

static void large_free(void *mem){
    const uintptr_t mem_i = (uintptr_t)mem;
    struct OS216_KernelLargeHeapData *data =
        os216_kernel_large_heap_data.next;
    uintptr_t at = (uintptr_t)OS216_KernelLargeHeap;
    while(OS216_LIKELY(data)){
        if(at == mem_i){
            if(OS216_UNLIKELY(data->used == 0)){
                OS216_FATAL("Heap corruption detected: double free in large heap");
            }
            data->used = 0;
            return;
        }
        at += data->size;
        data = data->next;
    }
    OS216_FATAL("Heap corruption detected: invalid free call in large heap");
    return;
}

/*****************************************************************************/

void free(void *mem){
    if(mem == (void*)0){
        return;
    }
    else if(is_small(mem)){
        small_free(mem);
    }
    else if(OS216_LIKELY(is_large(mem))){
        large_free(mem);
    }
    else{
        OS216_FATAL("Memory is not in the small or large kernel heap.");
    }
}

/*****************************************************************************/
