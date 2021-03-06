/*
 * Copyright (c) 2017 Martin McDonough.  All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef OS216_STDLIB_ASSERT_H
#define OS216_STDLIB_ASSERT_H
#pragma once

#ifdef NDEBUG
#define assert(_)
#else
#define assert(_) (void)(_)
#endif

#endif /* OS216_STDLIB_CTYPE_H */
