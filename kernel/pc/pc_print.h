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

#ifndef OS216_KERNEL_PC_PC_PRINT_H
#define OS216_KERNEL_PC_PC_PRINT_H
#pragma once

/*****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/

enum OS216_PC_PrintMode {
    eOS216_PC_Normal,
    eOS216_PC_Warning,
    eOS216_PC_Error,
    eOS216_PC_Fatal,
    eOS216_PC_NUM_MODES
};

/*****************************************************************************/

void OS216_PC_PrintString(enum OS216_PC_PrintMode mode, const char *msg);

/*****************************************************************************/

void OS216_PC_PrintChar(enum OS216_PC_PrintMode mode, char c);

/*****************************************************************************/

void OS216_PC_Newline(enum OS216_PC_PrintMode mode);

/*****************************************************************************/

void OS216_PC_NewScreen(enum OS216_PC_PrintMode mode);

/*****************************************************************************/

void OS216_PC_ClearScreen(enum OS216_PC_PrintMode mode);

/*****************************************************************************/

void OS216_PC_PrintInteger(enum OS216_PC_PrintMode mode, int i);

/*****************************************************************************/

void OS216_PC_PrintAddress(enum OS216_PC_PrintMode mode, void *p);

/*****************************************************************************/

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OS216_KERNEL_PC_PC_PRINT_H */
