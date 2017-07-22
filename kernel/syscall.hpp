#pragma once

#include "cpp.hpp"

#ifdef __GNUC__
#define OS216_CCALL extern "C" __attribute__((cdecl))
#else
#define OS216_CCALL extern "C" __cdecl
#endif
OS216_CCALL void OS216_SysCall(unsigned call_number, ...);
