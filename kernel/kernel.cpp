#include "cpp.hpp"
#include "malloc.h"
#include "assert.h"
#include <cstring>

#include "platform/print.h"
#include "platform/fatal.h"
#include "platform/bus.hpp"

#include "arch/memory.h"
#include "arch/interrupts.h"

namespace os216 {

static const char license_text1[] =
"Redistribution and use in source and binary forms, with or without \
modification, are permitted provided that the following conditions are met:";

static const char license_text2[] =
" * Redistributions of source code must retain the above copyright notice, this\n\
\tlist of conditions and the following disclaimer.\n\
\n\
 * Redistributions in binary form must reproduce the above copyright notice,\n\
\tthis list of conditions and the following disclaimer in the documentation\n\
\tand/or other materials provided with the distribution.\n\
\n\
 * Products derived from this software may not be called \"os216\", nor may\n\
\t\"216\" appear in their name, without prior written permission of\n\
\tthe copyright holders.";

static const char license_text3[] =
"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR \
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, \
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE \
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER \
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, \
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE \
SOFTWARE.";

extern "C"
void OS216_Main(){
    OS216_InitSegmentation();
    OS216_InitKernelMemory();
    OS216_InitInterrupts();
    
    OS216_VM_Initialize();
    
    std::vector<BusPointer> buses;
    EnumerateBuses(buses);
    
    OS216_ClearScreen();
    
    OS216_PrintString("\tOS 216 version 0.01\n    Copyright (c) 2016-2017 Martin McDonough\n\n");
    OS216_PrintString(license_text1);
    OS216_Newline();
    OS216_Newline();
    OS216_PrintString(license_text2);
    OS216_Newline();
    OS216_Newline();
    OS216_PrintString(license_text3);
}

} // namespace os216
