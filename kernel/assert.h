/* 
 *  Copyright (c) 2017 Martin McDonough.  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 * 
 * - Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 * 
 * - Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 
 * - Products derived from this software may not be called "os216", nor may
 *     "216" appear in their name, without prior written permission of
 *     the copyright holders.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef OS216_KERNEL_ASSERT_H
#define OS216_KERNEL_ASSERT_H
#pragma once

/*****************************************************************************/

#include "platform/fatal.h"
#include "attributes.h"

/*****************************************************************************/

#ifdef NDEBUG
    #ifdef _MSC_VER && _MSC_VER >= 1700
        #define OS216_ASSERT(X, MSG) __assume(X)
    #else
        #define OS216_ASSERT(X, MSG) ((void)X)
    #endif
#else /* NDEBUG */
    #define OS216_ASSERT(X, MSG) do{ if(OS216_LIKELY(X)){} else{\
        const char *const _msg_ = MSG;\
        OS216_FATAL(_msg_ ? _msg_ : (#X) );\
    } } while(0)
#endif /* NDEBUG */

#endif /* OS216_KERNEL_ASSERT_H */
