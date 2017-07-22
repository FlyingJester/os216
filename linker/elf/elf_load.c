#include "elf_load.h"


unsigned Zelda_Elf32_LoadHeader(const uint8_t *data,
    size_t i,
    size_t len,
    struct Zelda_Elf32_Header *out){
    
#define ZELDA_LOAD_FROM_MEM(TO, SIZE) do{\
    unsigned n = 0;\
    out->TO = 0;\
    out->TO = 0;\
    while(1){\
        out->TO |= data[i++];\
        if(i >= len)\
            return -1;\
        if(++n >= SIZE)\
            break;\
        out->TO <<= 8;\
    }\
}while(0);
    
    ZELDA_ELF32_PROCESS_HEADER(ZELDA_LOAD_FROM_MEM);
    return 0;
}

#if ( ! defined OS216_NO_STDIO ) && ( ! defined OS216_KERNEL )



#endif
