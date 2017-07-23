#pragma once
#ifndef OS216_IO_H
#define OS216_IO_H

#ifdef __cplusplus
extern "C" {
#endif

void OS216_IOOut(unsigned byte, unsigned to);
unsigned OS216_IOIn(unsigned from);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OS216_IO_H */
