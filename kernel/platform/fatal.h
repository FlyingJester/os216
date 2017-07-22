#pragma once
#ifndef OS216_FATAL_H
#define OS216_FATAL_H

#include "../attributes.h"

#ifdef __cplusplus
extern "C" {
#endif

OS216_NORETURN void OS216_Fatal(const char *file, unsigned line_num,
    const char *function, const char *msg) __attribute__((cdecl));
#define OS216_FATAL(MSG) OS216_Fatal(__FILE__, __LINE__, __FUNCTION__, MSG)

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OS216_FATAL_H */
