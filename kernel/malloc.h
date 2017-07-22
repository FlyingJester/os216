/* No #pragma once in pch */
#ifndef OS216_MALLOC_H
#define OS216_MALLOC_H
#include <stdint.h>
#include <stddef.h>

#include "attributes.h"

#ifdef __cplusplus
extern "C" {
#endif

OS216_MALLOC_ATTR void *malloc(size_t amount);
OS216_MALLOC_ATTR void *calloc(size_t count, size_t amount);
void *realloc(void *mem, size_t new_amount);
void free(void *mem);

void OS216_InitKernelMemory(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OS216_MALLOC_H */
