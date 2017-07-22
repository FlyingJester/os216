#include "../platform/fatal.h"
#include "pc_print.h"
#include "vga.h"
#include <string.h>

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
