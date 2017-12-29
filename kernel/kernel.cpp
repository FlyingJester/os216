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

/* PCH must be first. */
#include "cpp.hpp"

#include "assert.h"
#include "execute.h"
#include "malloc.h"

#include "arch/interrupts.h"
#include "arch/memory.h"
#include "arch/timer.h"

#include "initrd/initrd.h"

#include "platform/bus.hpp"
#include "platform/fatal.h"
#include "platform/print.h"

#include <string.h>

/*****************************************************************************/

namespace os216 {

/*****************************************************************************/

static const char license_text1[] =
"Redistribution and use in source and binary forms, with or without "
"modification, are permitted provided that the following conditions are met:";

static const char license_text2[] =
" * Redistributions of source code must retain the above copyright notice, this\n"
"\tlist of conditions and the following disclaimer.\n"
"\n"
" * Redistributions in binary form must reproduce the above copyright notice,\n"
"\tthis list of conditions and the following disclaimer in the documentation\n"
"\tand/or other materials provided with the distribution.\n"
"\n"
" * Products derived from this software may not be called \"os216\", nor may\n"
"\t\"216\" appear in their name, without prior written permission of\n"
"\tthe copyright holders.";

static const char license_text3[] =
"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR "
"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, "
"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE "
"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER "
"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, "
"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE "
"SOFTWARE.";

/*****************************************************************************/

/*
static bool run_test_executable(){

    for(size_t i = 0; i < OS216_GetRamDiskCount(); i++){
        if(strcmp(OS216_GetRamDiskEntryName(i), "test") == 0){
            OS216_Execute((void*)OS216_GetRamDiskEntryData(i), OS216_GetRamDiskEntrySize(i));
            return true;
        }
    }
    return false;
}
*/

/*****************************************************************************/

static unsigned os216_tick = 0, os216_second = 0;

/*****************************************************************************/

void os216_timer_callback(){
    if(os216_tick++ % 100 == 0){
        OS216_NewScreen();
        OS216_PrintString("Tick: ");
        OS216_PrintInteger(os216_tick++);
        OS216_PrintString("\tSecond: ");
        OS216_PrintInteger(os216_second++);
        OS216_PrintString("\t\t\t\t");
    }
}

/*****************************************************************************/

extern "C"
void OS216_Main(){
    OS216_InitSegmentation();
    OS216_InitKernelMemory();
    // Set the timer frequency
    OS216_SetTimerInterrupt(os216_timer_callback);
    OS216_InitInterrupts();
    
   // OS216_SetTimerSpeed(100);

    OS216_VM_Initialize();
    
    std::vector<BusPointer> buses;
    EnumerateBuses(buses);
    
    OS216_ClearScreen();
    
    OS216_PrintString("\tOS 216 version 0.02\n"
        "    Copyright (c) 2016-2018 Martin McDonough\n\n");
    OS216_PrintString(license_text1);
    OS216_Newline();
    OS216_Newline();
    OS216_PrintString(license_text2);
    OS216_Newline();
    OS216_Newline();
    OS216_PrintString(license_text3);
    
    OS216_Newline();
}

/*****************************************************************************/

} // namespace os216
