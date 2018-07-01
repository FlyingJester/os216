/* 
 *  Copyright (c) 2017-2018 Martin McDonough.  All rights reserved.
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

#ifndef OS216_KERNEL_ATTRIBUTES_H
#define OS216_KERNEL_ATTRIBUTES_H
#pragma once

/*****************************************************************************/

#ifndef OS216_LIKELY
  #ifdef __GNUC__
    #define OS216_LIKELY(X) __builtin_expect(!!(X), 1)
  #else
    #define OS216_LIKELY(X) (!!(X))
  #endif
#endif

/*****************************************************************************/

#ifndef OS216_UNLIKELY
  #ifdef __GNUC__
    #define OS216_UNLIKELY(X) __builtin_expect(!!(X), 0)
  #else
    #define OS216_UNLIKELY(X) (!!(X))
  #endif
#endif

/*****************************************************************************/

#ifndef OS216_COLD
  #ifdef __GNUC__
    #define OS216_COLD __attribute__((cold))
  #else
    #define OS216_COLD
  #endif
#endif

/*****************************************************************************/

#ifndef OS216_NORETURN
  #ifdef __GNUC__
    #define OS216_NORETURN __attribute__((noreturn,cold))
  #elif defined _MSC_VER_
    #define OS216_NORETURN __declspec(noreturn)
  #endif
#endif

/*****************************************************************************/

#ifndef OS216_PURE
  #ifdef __GNUC__
    #define OS216_PURE __attribute__((pure))
  #elif defined _MSC_VER_
    #define OS216_PURE
  #endif
#endif

/*****************************************************************************/

#ifndef OS216_MEMORY_PURE
  #ifdef __GNUC__
    #define OS216_MEMORY_PURE __attribute__((const))
  #elif defined _MSC_VER_
    #define OS216_MEMORY_PURE
  #endif
#endif

/*****************************************************************************/

#ifndef OS216_MALLOC_ATTR
  #ifdef __GNUC__
    #define OS216_MALLOC_ATTR\
        __attribute__((malloc,returns_nonnull,warn_unused_result))
  #else
    #define OS216_MALLOC_ATTR __declspec(restrict)
  #endif
#endif

/*****************************************************************************/

#ifndef OS216_NOT_NULL
  #ifdef __GNUC__
    #define OS216_NOT_NULL __attribute__((returns_nonnull))
  #else
    #define OS216_NOT_NULL
  #endif
#endif

/*****************************************************************************/

#ifndef OS216_WARN_UNUSED_RESULT
  #ifdef __GNUC__
    #define OS216_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
  #else
    #define OS216_WARN_UNUSED_RESULT
  #endif
#endif


#if ( defined __GNUC__ ) && ( ( defined __x86_64__ ) || ( defined __i386 ) )
#define OS216_DOES_NOT_CLOBBER_REGISTERS\
    __attribute__((no_caller_saved_registers))
#else
#define OS216_DOES_NOT_CLOBBER_REGISTERS
#endif

/*****************************************************************************/

#if defined __cplusplus
    #if __cplusplus < 201103L
        #define OS216_CONSTEXPR_CONSTRUCTOR
        #define OS216_CONSTEXPR_FUNC OS216_MEMORY_PURE
        #define OS216_CONSTEXPR_VALUE const
    #else
        #define OS216_CONSTEXPR_CONSTRUCTOR constexpr
        #define OS216_CONSTEXPR_FUNC OS216_MEMORY_PURE constexpr
        #define OS216_CONSTEXPR_VALUE constexpr
    #endif
    #if __cplusplus >= 201103L
        #define OS216_OVERRIDE override
        #define OS216_FINAL final
    #elif  defined _MSC_VER && _MSC_VER >= 1700
        #define OS216_OVERRIDE override
        #define OS216_FINAL sealed
    #else
        #define OS216_OVERRIDE
        #define OS216_FINAL
    #endif
#endif /* __cplusplus */

#endif /* OS216_KERNEL_ATTRIBUTES_H */
