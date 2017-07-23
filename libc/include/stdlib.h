#pragma once
#ifndef OS216_STDLIB_STDLIB_H
#define OS216_STDLIB_STDLIB_H

#include <stdint.h>

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

unsigned long strtoul(const char *__restrict__ str,
    const char **__restrict__ end,
    unsigned base);

/*****************************************************************************/

uint64_t strtoull(const char *__restrict__ str,
    const char **__restrict__ end,
    unsigned base);

#endif /* OS216_STDLIB_STDLIB_H */
