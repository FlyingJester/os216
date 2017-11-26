/*
 * Copyright (c) 2017 Martin McDonough.  All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef OS216_STDLIB_STDIO_H
#define OS216_STDLIB_STDIO_H
#pragma once

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
    SEEK_SET,
    SEEK_CUR,
    SEEK_END
};

int sprintf(char *buffer, const char *format, ...);
int vsprintf(char *buffer, const char *format, va_list args);

int snprintf(char *buffer, size_t n, const char *format, ...);
int vsnprintf(char *buffer, size_t n, const char *format, va_list args);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* LIBORL_SUPPLIEMENT_STDIO_H */
 