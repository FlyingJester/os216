/*
 * Copyright (c) 2017 Martin McDonough.  All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef OS216_STDLIB_STRING_H
#define OS216_STDLIB_STRING_H
#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/

char *strcpy(char *__restrict__ to, const char *__restrict__ from);

/*****************************************************************************/

char *strncpy(char *__restrict__ to, const char *__restrict__ from, size_t n);

/*****************************************************************************/

char *strlcpy(char *__restrict__ to, const char *__restrict__ from, size_t n);


/*****************************************************************************/

size_t strlen(const char *string);

/*****************************************************************************/

size_t strnlen(const char *string, size_t n);

/*****************************************************************************/

char *strcat(char *__restrict__ to, const char *__restrict__ from);

/*****************************************************************************/

char *strncat(char *__restrict__ to, const char *__restrict__ from, size_t n);

/*****************************************************************************/

char *strncat_s(char *__restrict__ to,
    size_t to_size,
    const char *__restrict__ from,
    size_t n);

/*****************************************************************************/

char *strlcat(char *__restrict__ to, const char *__restrict__ from, size_t n);

/*****************************************************************************/

int strcmp(const char *__restrict__ a, const char *__restrict__ b);

/*****************************************************************************/

int strncmp(const char *__restrict__ a, const char *__restrict__ b, size_t n);

/*****************************************************************************/

void *memcpy(void *__restrict__ dest, const void *__restrict__ src, size_t n);

/*****************************************************************************/

void *memset(void *dest, uint8_t val, size_t n);

/*****************************************************************************/

void *memchr(const void *ptr, int val, size_t n);

/*****************************************************************************/

int memcmp(const void *__restrict__ a, const void *__restrict__ b, size_t n);

/*****************************************************************************/

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OS216_STDLIB_CTYPE_H */
