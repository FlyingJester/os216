#pragma once

#include "../attributes.h"

#ifdef __cplusplus
extern "C" {
#endif

void OS216_InitSegmentation(void);

struct OS216_VMDirectory;
OS216_MEMORY_PURE unsigned OS216_GetPageSize();
OS216_MEMORY_PURE void *OS216_GetMappableStart();
OS216_MALLOC_ATTR struct OS216_VMDirectory *OS216_CreateNewVMDirectory(void);
void OS216_DestroyVMDirectory(struct OS216_VMDirectory *);
void OS216_SetVMDirectory(struct OS216_VMDirectory *);

#ifdef __cplusplus
} // extern "C"
#endif
