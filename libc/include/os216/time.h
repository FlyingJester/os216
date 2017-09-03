/*
 * Copyright (c) 2017 Martin McDonough.  All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef OS216_LIBC_TIME_H
#define OS216_LIBC_TIME_H
#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Gets the number of nanoseconds since some undefined but constant epoch. The
 * epoch may be different between different runs of the same program, but is
 * constant during the lifetime of the program.
 */
uint64_t OS216_GetNanoseconds();

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OS216_LIBC_TIME_H */
