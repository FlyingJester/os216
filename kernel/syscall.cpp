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

#include "process.hpp"
#include "schedule.hpp"

#include "platform/fatal.h"

#include <stdarg.h>

/*****************************************************************************/

typedef void (*os216_syscall_t)(va_list args);

/*****************************************************************************/

void os216_nop_syscall(va_list args){
    (void)args;
    OS216_FATAL("nop syscall");
}

/*****************************************************************************/

void os216_die_syscall(va_list args){
    (void)args;
    OS216_FATAL("die syscall");
}

/*****************************************************************************/

void os216_vm_allocate_syscall(va_list args){
    const void *const address = va_arg(args, void*);
    const unsigned length = va_arg(args, unsigned);
    const int flags = va_arg(args, int);
    (void)address;
    (void)length;
    (void)flags;
    OS216_FATAL("vm_allocate syscall");
}

/*****************************************************************************/

void os216_vm_deallocate_syscall(va_list args){
    const void *const address = va_arg(args, void*);
    const unsigned length = va_arg(args, unsigned);
    (void)address;
    (void)length;
    OS216_FATAL("vm_deallocate syscall");
}

/*****************************************************************************/

void os216_vm_protect_syscall(va_list args){
    const void *const address = va_arg(args, void*);
    const unsigned length = va_arg(args, unsigned);
    const int flags = va_arg(args, int);
    (void)address;
    (void)length;
    (void)flags;
    OS216_FATAL("vm_protect syscall");
}

/*****************************************************************************/
// Syscalls shared between driver and user programs
#define OS216_STD_SYSCALLS\
    os216_nop_syscall,\
    os216_die_syscall,\
    os216_vm_allocate_syscall,\
    os216_vm_deallocate_syscall,\
    os216_vm_protect_syscall

/*****************************************************************************/

static const os216_syscall_t os216_user_syscalls[] = {
    OS216_STD_SYSCALLS
};

/*****************************************************************************/

static const os216_syscall_t os216_driver_syscalls[] = {
    OS216_STD_SYSCALLS
};

/*****************************************************************************/

void OS216_SysCall(unsigned call_number, ...){
    va_list args;
    va_start(args, call_number);
    
    const os216::Process *const process = os216::CurrentProcess();
    
    const os216_syscall_t *syscalls;
    
    if(process != NULL && process->driver()){
        if(call_number >= sizeof(os216_driver_syscalls) / sizeof(*os216_driver_syscalls))
            OS216_FATAL("Invalid syscall number");
        syscalls = os216_driver_syscalls;
    }
    else{
        if(call_number >= sizeof(os216_user_syscalls) / sizeof(*os216_user_syscalls))
            OS216_FATAL("Invalid syscall number");
        syscalls = os216_user_syscalls;
    }
    
    syscalls[call_number](args);
    
    va_end(args);
}

/*****************************************************************************/
