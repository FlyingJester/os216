#pragma once

#include "platform/fatal.h"
#include "attributes.h"

#ifdef NDEBUG
    #ifdef _MSC_VER && _MSC_VER >= 1700
        #define OS216_ASSERT(X, MSG) __assume(X)
    #else
        #define OS216_ASSERT(X, MSG) ((void)X)
    #endif
#else
    #define OS216_ASSERT(X, MSG) do{ if(OS216_LIKELY(X)){} else{\
        const char *const _msg_ = MSG;\
        OS216_FATAL(_msg_ ? _msg_ : (#X) );\
    } } while(0)
#endif
