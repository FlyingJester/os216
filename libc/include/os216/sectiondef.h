/*
 * Copyright (c) 2017 Martin McDonough.  All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef OS216_LIBC_SECTIONDEF_H
#define OS216_LIBC_SECTIONDEF_H
#pragma once

#include <stdint.h>
#include <stddef.h>

/* The specifications of permissions are a bitmask. An enum is provided for
 * common values, but any combination of these are accepted.
 */
#define OS216_RD_SECTION (1<<0) /* Read permissions */
#define OS216_WR_SECTION (1<<1) /* Write permissions */
#define OS216_RW_SECTION (OS216_RD_SECTION|OS216_WR_SECTION)
#define OS216_EX_SECTION ((1<<2)|OS216_RD_SECTION) /* Execute permission */
#define OS216_WX_SECTION (OS216_EX_SECTION|OS216_WR_SECTION)

enum OS216_EnumSectionPermissions {
    OS216_eInvalidSectionPermissions,
    OS216_eReadOnlySectionPermissions = OS216_RD_SECTION,
    OS216_eReadWriteSectionPermissions = OS216_RW_SECTION,
    OS216_eExecuteSectionPermissions = OS216_EX_SECTION,
};

#define OS216_IN_SECTION ((1<<3)&0) /* Normal section, size and contents. */
#define OS216_UN_SECTION (1<<3) /* Only size is stored. */
#define OS216_ZR_SECTION (1<<4) /* Section will be zeroed out */
#define OS216_BSS_SECTION (OS216_UN_SECTION|OS216_ZR_SECTION)

enum OS216_SectionType {
    OS216_eRegularSectionType = OS216_IN_SECTION,
    OS216_eUninitializedSectionType = OS216_UN_SECTION,
    OS216_eZeroInitializedSectionType = OS216_ZR_SECTION,
    OS216_eBSSSectionType = OS216_BSS_SECTION,
};

struct OS216_SectionData{
    void *data;
    size_t size;
    uint16_t permission;
    uint16_t type;
};

#endif /* OS216_LIBC_SECTIONDEF_H */
