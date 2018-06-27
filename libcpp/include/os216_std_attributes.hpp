// Copyright (c) 2017 Martin McDonough.  All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OS216_STDLIB_STD_ATTRIBUTES
#define OS216_STDLIB_STD_ATTRIBUTES
#pragma once

#ifndef OS216_MEMORY_PURE
#ifdef _MSC_VER
#define OS216_MEMORY_PURE __declspec(noalias)
#elif defined __GNUC__
#define OS216_MEMORY_PURE __attribute__((const))
#else
#define OS216_MEMORY_PURE
#endif
#endif

#if __cplusplus < 201103L
    #define OS216_LIBCPP_CONSTEXPR_CONSTRUCTOR
    #define OS216_LIBCPP_CONSTEXPR_FUNC OS216_MEMORY_PURE
    #define OS216_LIBCPP_CONSTEXPR_VALUE const
#else
    #define OS216_LIBCPP_CONSTEXPR_CONSTRUCTOR constexpr
    #define OS216_LIBCPP_CONSTEXPR_FUNC OS216_MEMORY_PURE constexpr
    #define OS216_LIBCPP_CONSTEXPR_VALUE constexpr
#endif

#endif // OS216_STDLIB_STD_ATTRIBUTES
