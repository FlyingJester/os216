/*
 * Copyright (c) 2017 Martin McDonough.  All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef OS216_LIBC_PORT_H
#define OS216_LIBC_PORT_H
#pragma once

#include <os216/error.h>
#include <os216/portdef.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct OS216_Message{
    OS216_Port port;
    void *data;
    size_t size;
    bool is_signal;
};

/* if is_signal is false, then msg must be page aligned and size must be a
 * multiple of the page size */
enum OS216_Error OS216_SendMessage(const struct OS216_Message *msg);

#define OS216_INFINITE_WAIT (~((uint64_t)0))

enum OS216_Error OS216_Receive(uint64_t timeout,
    struct OS216_Message *out_msg);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OS216_LIBC_PORT_H */
