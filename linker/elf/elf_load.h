#pragma once
#ifndef ZELDA_ELF_LOAD_H
#define ZELDA_ELF_LOAD_H

#include "elf.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ZELDA_ELF32_PROCESS_HEADER(ACTION)\
    do{\
        {\
            unsigned identi = 0;\
            for(identi = 0; identi != ZELDA_ELF32_IDENT_LEN; identi++){\
                ACTION(ident[identi], 1);\
            }\
        }\
        ACTION(type, sizeof(Zelda32_Half));\
        ACTION(machine, sizeof(Zelda32_Half));\
        ACTION(version, sizeof(Zelda32_Word));\
        ACTION(entry, sizeof(Zelda32_Addr));\
        ACTION(program_header_offset, sizeof(Zelda32_Off));\
        ACTION(section_header_offset, sizeof(Zelda32_Off));\
        ACTION(flags, sizeof(Zelda32_Word));\
        ACTION(header_size, sizeof(Zelda32_Half));\
        ACTION(program_header_entry_size, sizeof(Zelda32_Half));\
        ACTION(program_header_num, sizeof(Zelda32_Half));\
        ACTION(section_header_entry_size, sizeof(Zelda32_Half));\
        ACTION(section_header_num, sizeof(Zelda32_Half));\
        ACTION(section_header_string_index, sizeof(Zelda32_Half));\
    }while(0)

unsigned Zelda_Elf32_LoadHeader(const uint8_t *data,
    size_t i,
    size_t len,
    struct Zelda_Elf32_Header *out);

unsigned Zelda_Elf32_LoadSectionHeader(const uint8_t *data,
    size_t i,
    Zelda32_Half header_num, 
    const struct Zelda_Elf32_Header *header,
    struct Zelda_Elf32_SectionHeader *out);

#if ( ! defined OS216_NO_STDIO ) && ( ! defined OS216_KERNEL )

#include <stdio.h>

unsigned Zelda_Elf32_FileLoadHeader(FILE *file,
    struct Zelda_Elf32_Header *out);

unsigned Zelda_Elf32_FileLoadSectionHeader(FILE *file,
    Zelda32_Half header_num, 
    const struct Zelda_Elf32_Header *header,
    struct Zelda_Elf32_SectionHeader *out);

#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* ZELDA_ELF_LOAD_H */
