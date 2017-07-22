// No #pragma once in pch
#ifndef OS216_CPP_HPP
#define OS216_CPP_HPP

#include <stdint.h>
#include <stddef.h>

#include "malloc.h"

#include <new>

OS216_MALLOC_ATTR void *operator new(size_t size);
OS216_MALLOC_ATTR void *operator new[](size_t size);
void operator delete(void *mem);
void operator delete[](void *mem);

inline void *operator new(size_t, void *p) { return p; }
inline void *operator new[](size_t, void *p) { return p; }
inline void operator delete(void *, void *) { }
inline void operator delete[](void *, void *) { }

#endif // OS216_CPP_HPP
