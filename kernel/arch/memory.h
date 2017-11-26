#pragma once

#include "../attributes.h"

#ifdef __cplusplus
extern "C" {
#endif

void OS216_InitSegmentation(void);

OS216_MEMORY_PURE unsigned OS216_VM_GetPageSize();
OS216_MEMORY_PURE void *OS216_VM_GetMappableStart();

struct OS216_VMDirectory;

void OS216_VM_Enable();
OS216_MALLOC_ATTR struct OS216_VMDirectory *OS216_VM_CreateNewVMDirectory(void);

void OS216_VM_DestroyVMDirectory(struct OS216_VMDirectory *);
struct OS216_VMDirectory *OS216_VM_GetVMDirectory(void);
void OS216_VM_SetVMDirectory(struct OS216_VMDirectory *);

void *OS216_VM_PhysicalAddressToVirtualAddress(void*);
void *OS216_VM_VirtualAddressToPhysicalAddress(void*);

void *OS216_VM_MapPage(void *physical, void *dest);

void OS216_VM_Initialize();

#ifdef __cplusplus
} // extern "C"
#endif
