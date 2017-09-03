/*
 * Copyright (c) 2017 Martin McDonough.  All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef OS216_LIBC_MEMORY_H
#define OS216_LIBC_MEMORY_H
#pragma once

#include <os216/error.h>
#include <os216/sectiondef.h>

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t OS216_GetPageSize();

/* size must be a multiple of the page size. */
enum OS216_EnumError OS216_AllocateMemory(size_t size,
    enum OS216_EnumSectionPermissions permissions,
    void **out_mem);

/* size must be a multiple of the page size, and mem must be page-aligned. */
enum OS216_EnumError OS216_FreeMemory(size_t size, void *mem);

/* page must be page-aligned. */
enum OS216_EnumError OS216_GetPagePermissions(const void *page,
    intptr_t *out_permissions);

/* page must be page-aligned. */
enum OS216_EnumError OS216_SetPagePermissions(const void *page,
    enum OS216_EnumSectionPermissions permissions);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OS216_LIBC_MEMORY_H */
