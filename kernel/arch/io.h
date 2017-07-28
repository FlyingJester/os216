#pragma once
#ifndef OS216_IO_H
#define OS216_IO_H

#ifdef __cplusplus
extern "C" {
#endif

void OS216_IOOut(unsigned byte, unsigned to, unsigned size);
void OS216_IOOut8(unsigned byte, unsigned to);
void OS216_IOOut16(unsigned byte, unsigned to);
void OS216_IOOut32(unsigned byte, unsigned to);

unsigned OS216_IOIn(unsigned from, unsigned size);
unsigned OS216_IOIn8(unsigned from);
unsigned OS216_IOIn16(unsigned from);
unsigned OS216_IOIn32(unsigned from);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OS216_IO_H */
