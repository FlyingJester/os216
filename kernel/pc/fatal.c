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

#include "../platform/fatal.h"
#include "pc_print.h"
#include "vga.h"
#include <string.h>

/*****************************************************************************/

void OS216_Fatal(const char *file, unsigned line_num, const char *function,
    const char *msg){
    
    unsigned i;
    OS216_PC_NewScreen(eOS216_PC_Fatal);
    for(i = 0; i < os216_vga_w; i++)
        OS216_PC_PrintChar(eOS216_PC_Fatal, '=');
    
    OS216_PC_PrintString(eOS216_PC_Fatal, file);
    OS216_PC_PrintChar(eOS216_PC_Fatal, ':');
    OS216_PC_PrintInteger(eOS216_PC_Fatal, line_num);
    OS216_PC_PrintChar(eOS216_PC_Fatal, '(');
    OS216_PC_PrintString(eOS216_PC_Fatal, function);
    OS216_PC_PrintChar(eOS216_PC_Fatal, ')');
    OS216_PC_Newline(eOS216_PC_Fatal);
    
    OS216_PC_PrintString(eOS216_PC_Fatal, msg);
    OS216_PC_Newline(eOS216_PC_Fatal);
    
    for(i = 0; i < os216_vga_w; i++)
        OS216_PC_PrintChar(eOS216_PC_Fatal, '=');
#ifdef __GNUC__
    __asm("cli\n\t"
        "hlt");
#elif (( defined _MSC_VER ) || ( defined __WATCOMC__ ) && ( defined _M_I86 )
    __asm {
        cli
        hlt
    }
#endif
hang: goto hang;
}
