/*
 * Copyright (c) 2017 Martin McDonough.  All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef OS216_STDLIB_STDLIB_H
#define OS216_STDLIB_STDLIB_H
#pragma once

#include <stdint.h>
#include <stddef.h>

/*****************************************************************************/

#ifndef NULL
#define NULL ((void*)0)
#endif

/*****************************************************************************/

int atoi(const char *c);

/*****************************************************************************/

long atol(const char *c);

/*****************************************************************************/

int64_t atoll(const char *c);

/*****************************************************************************/

uint64_t strtoull(const char *__restrict__ str,
    const char **__restrict__ end,
    unsigned base);

/*****************************************************************************/

int64_t strtoll(const char *__restrict__ str,
    const char **__restrict__ end,
    unsigned base);

/*****************************************************************************/

unsigned long strtoul(const char *__restrict__ str,
    const char **__restrict__ end,
    unsigned base);

/*****************************************************************************/

long strtol(const char *__restrict__ str,
    const char **__restrict__ end,
    unsigned base);

/*****************************************************************************/

unsigned strtoui(const char *__restrict__ str,
    const char **__restrict__ end,
    unsigned base);

/*****************************************************************************/

int strtoi(const char *__restrict__ str,
    const char **__restrict__ end,
    unsigned base);

/*****************************************************************************/

void qsort(void *ptr, size_t count, size_t size,
    int(*compare)(const void *, const void *));

#endif /* OS216_STDLIB_STDLIB_H */
