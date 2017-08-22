#include "syscall.hpp"
#include "platform/fatal.h"

#include <stdarg.h>

static const unsigned num_syscalls = 3;

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
