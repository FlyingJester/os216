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

// PCH must be first
#include "cpp.hpp"

#include "syscall.hpp"

#include "platform/fatal.h"

#include <stdarg.h>

/*****************************************************************************/

static const unsigned num_syscalls = 3;

/*****************************************************************************/

void OS216_SysCall(unsigned arg0, ...){
    va_list args;
    va_start(args, arg0);
    const unsigned call_number = arg0;
    if(call_number >= num_syscalls)
        OS216_FATAL("Invalid syscall");
    
    switch(call_number){
        case 0:
            OS216_FATAL("nop syscall");
            break;
        case 1:
            {
                const int amount = va_arg(args, int);
                (void)amount;
            }
            OS216_FATAL("sbrk syscall");
            break;
        case 2:
            {
                const void *const address = va_arg(args, void*);
                const unsigned length = va_arg(args, unsigned);
                const int flags = va_arg(args, int);
                (void)address;
                (void)length;
                (void)flags;
            }
            OS216_FATAL("mprotect syscall");
            break;
        case 3:
            OS216_FATAL("die syscall");
            break;
    }
    
    va_end(args);
}

/*****************************************************************************/
