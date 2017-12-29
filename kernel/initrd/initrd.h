/*
 * (C) Martin McDonough 2017-2018
 * Any copyright of this file is dedicated to the Public Domain
 * http://creativecommons.org/publicdomain/1.0/
 */
#ifndef OS216_KERNEL_INITRD_H
#define OS216_KERNEL_INITRD_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

unsigned OS216_GetRamDiskCount(void);
const char *OS216_GetRamDiskEntryName(unsigned i);
unsigned OS216_GetRamDiskEntrySize(unsigned i);
const void *OS216_GetRamDiskEntryData(unsigned i);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OS216_KERNEL_INITRD_H */
