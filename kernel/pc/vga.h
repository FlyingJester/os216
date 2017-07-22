#pragma once
#ifndef OS216_VGA_H
#define OS216_VGA_H

#include "pc_print.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const unsigned os216_vga_w, os216_vga_h;

void OS216_VGA_PutString(unsigned x,
    unsigned y,
    enum OS216_PC_PrintMode,
    unsigned n,
    const char *msg);

void OS216_VGA_Clear(unsigned x,
    unsigned y,
    enum OS216_PC_PrintMode mode,
    unsigned n);

void OS216_VGA_ClearLine(unsigned y, enum OS216_PC_PrintMode mode);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OS216_VGA_H */
