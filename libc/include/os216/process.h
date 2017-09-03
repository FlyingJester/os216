/*
 * Copyright (c) 2017 Martin McDonough.  All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef OS216_LIBC_PROCESS_H
#define OS216_LIBC_PROCESS_H
#pragma once

#include <os216/portdef.h>
#include <os216/sectiondef.h>

#include <stdint.h>
#include <stddef.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

enum OS216_EnumError OS216_CreateProcess(
    size_t num_sections,
    const struct OS216_SectionData *data,
    size_t entry_section,
    size_t entry_offset,
    OS216_Port *out_port);

enum OS216_EnumError OS216_KillProcess(OS216_Port port);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OS216_LIBC_PROCESS_H */
