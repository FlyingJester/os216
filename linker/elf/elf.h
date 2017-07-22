#pragma once

#include <stdint.h>

typedef uint32_t Zelda32_Addr;
typedef uint16_t Zelda32_Half;
typedef uint32_t Zelda32_Off;
typedef int32_t Zelda32_SignedWord;
typedef uint32_t Zelda32_Word;
typedef unsigned char Zelda32_UnsignedChar;

/*
 * ELF Header
 */

#define ZELDA_ELF32_IDENT_LEN 16

/* ELF file types */
#define ZELDA_ELF32_RELOCATABLE 1
#define ZELDA_ELF32_EXECUTABLE 2
#define ZELDA_ELF32_SHARED 3
#define ZELDA_ELF32_CORE 4

/* ELF machine types */
#define ZELDA_ELF32_SPARC 2
#define ZELDA_ELF32_386 3

/* ident elements */
#define ZELDA_ELF32_IDENT_INDEX_MAGIC0 0
#define ZELDA_ELF32_IDENT_INDEX_MAGIC1 1
#define ZELDA_ELF32_IDENT_INDEX_MAGIC2 2
#define ZELDA_ELF32_IDENT_INDEX_MAGIC3 3
#define ZELDA_ELF32_IDENT_INDEX_CLASS 4
#define ZELDA_ELF32_IDENT_INDEX_ENDIAN 5
#define ZELDA_ELF32_IDENT_INDEX_VERSION 6

/* ELF magic values */
#define ZELDA_ELF32_IDENT_MAGIC0 0x7F
#define ZELDA_ELF32_IDENT_MAGIC1 'E'
#define ZELDA_ELF32_IDENT_MAGIC2 'L'
#define ZELDA_ELF32_IDENT_MAGIC3 'F'

/* Class values */
#define ZELDA_ELF32_IDENT_CLASS_32_BIT 1
#define ZELDA_ELF32_IDENT_CLASS_64_BIT 2

/* Encoding/Endian values */
#define ZELDA_ELF32_IDENT_ENDIAN_LITTLE 1
#define ZELDA_ELF32_IDENT_ENDIAN_BIG 2

struct Zelda_Elf32_Header {
    Zelda32_UnsignedChar ident[ZELDA_ELF32_IDENT_LEN];
    Zelda32_Half type; /* Holds a file type */
    Zelda32_Half machine; /* Holds a machine type */
    Zelda32_Word version; /* Must be 1 */
    Zelda32_Addr entry; /* Entry point for the executable. */
    Zelda32_Off program_header_offset; /* Offset of the program header table */
    Zelda32_Off section_header_offset; /* Offset of the section header table */
    Zelda32_Word flags; /* Holds cpu-specific flags. Always zero for x86 */
    Zelda32_Half header_size; /* Size of this header in the file. */
    Zelda32_Half program_header_entry_size; /* Size of program headers */
    Zelda32_Half program_header_num; /* Num program header table entries */
    Zelda32_Half section_header_entry_size; /* Size of section headers */
    Zelda32_Half section_header_num; /* Num section header table entries */
    /* Section header entry associated with the section name string table */
    Zelda32_Half section_header_string_index;
};

/*
 * ELF Sections
 */

/* Reserved section header indices in symbols */
#define ZELDA_ELF32_SECTION_INDEX_LO_PROCESSOR 0xFF00
#define ZELDA_ELF32_SECTION_INDEX_HI_PROCESSOR 0xFF1F
#define ZELDA_ELF32_SECTION_INDEX_ABSOLUTE 0xFFF1 /* Location is absolute */
#define ZELDA_ELF32_SECTION_INDEX_COMMON 0xFFF2 /* Not-yet-allocated block */

#define ZELDA_ELF32_SECTION_TYPE_PROGRAM_BITS 1
#define ZELDA_ELF32_SECTION_TYPE_SYMBOL_TABLE 2
#define ZELDA_ELF32_SECTION_TYPE_STRING_TABLE 3
#define ZELDA_ELF32_SECTION_TYPE_RELOCATION_WITH_ADDEND 4
#define ZELDA_ELF32_SECTION_TYPE_HASH_TABLE 5
#define ZELDA_ELF32_SECTION_TYPE_DYNAMIC_LINK_INFO 6
#define ZELDA_ELF32_SECTION_TYPE_NOTE 7
#define ZELDA_ELF32_SECTION_TYPE_NO_BITS 8 /* Empty section */
#define ZELDA_ELF32_SECTION_TYPE_RELOLCATION_NO_ADDEND 9
#define ZELDA_ELF32_SECTION_TYPE_SHARED_LIBRARY 10 /* Reserved */
#define ZELDA_ELF32_SECTION_TYPE_DYNAMIC_SYMBOLS 11

#define ZELDA_ELF32_SECTION_FLAGS_WRITE 1
#define ZELDA_ELF32_SECTION_FLAGS_MEMORY 2
#define ZELDA_ELF32_SECTION_FLAGS_EXECUTABLE 4

/*
 * Link and Info meaning based on type:
 
 * ZELDA_ELF32_SECTION_TYPE_DYNAMIC_LINK_INFO: 
 *   link is the section header index of the string table used by this section
 * 
 * ZELDA_ELF32_SECTION_TYPE_HASH_TABLE:
 *   link is the section header index of the symbol table this section is for
 * 
 * ZELDA_ELF32_SECTION_TYPE_RELOCATION_WITH_ADDEND:
 * ZELDA_ELF32_SECTION_TYPE_RELOCATION_NO_ADDEND:
 *   link is the section header of the symbol table
 *   info is the section header this section is for
 * 
 * ZELDA_ELF32_SECTION_TYPE_SYMBOL_TABLE:
 * ZELDA_ELF32_SECTION_TYPE_DYNAMIC_SYMBOLS:
 *    link is the section header index of the string table used by this section
 *    info is one more than the symbol table index of the last local symbol
 */

struct Zelda_Elf32_SectionHeader {
    Zelda32_Word name_string_index;
    Zelda32_Word type;
    Zelda32_Word flags;
    Zelda32_Addr addr; /* The address of this section in the memory image */
    Zelda32_Off offset; /* Offset in the file to the start of the section */
    Zelda32_Word size; /* Size of the section in the file */
    Zelda32_Word link; /* Section header link index. Meaning depends on type */
    Zelda32_Word info;
    Zelda32_Word address_lignment; /* Alignment, 0/1 mean no align */
    Zelda32_Word entity_size;
};

/*
 * ELF Symbols
 */

#define ZELDA_ELF32_SYMBOL_BIND(X) (((X) >> 4) & 0x0F)
#define ZELDA_ELF32_SYMBOL_TYPE(X) ((X) & 0x0F)

#define ZELDA_ELF32_SYMBOL_BINDING_LOCAL 0 /* Translation-unit-local */
#define ZELDA_ELF32_SYMBOL_BINDING_GLOBAL 1
#define ZELDA_ELF32_SYMBOL_BINDING_WEAK 2
#define ZELDA_ELF32_SYMBOL_BINDING_CPU0 0x0D
#define ZELDA_ELF32_SYMBOL_BINDING_CPU1 0x0D
#define ZELDA_ELF32_SYMBOL_BINDING_CPU2 0x0F

#define ZELDA_ELF32_SYMBOL_TYPE_OBJECT 1
#define ZELDA_ELF32_SYMBOL_TYPE_FUNCTION 2
#define ZELDA_ELF32_SYMBOL_TYPE_SECTION 3
#define ZELDA_ELF32_SYMBOL_TYPE_FILE 4
#define ZELDA_ELF32_SYMBOL_TYPE_CPU0 0x0D
#define ZELDA_ELF32_SYMBOL_TYPE_CPU1 0x0D
#define ZELDA_ELF32_SYMBOL_TYPE_CPU2 0x0F

struct Zelda_Elf32_Symbol{
    Zelda32_Word name; /* String index of the symbol's name */
    /* In executable and shared files, holds an address. In relocatable files,
     * holds alignment constraints for a common symbol. */
    Zelda32_Addr value;
    Zelda32_Word size;
    Zelda32_UnsignedChar info; /* Holds the bindings and type. */
    Zelda32_UnsignedChar other; /* No meaning */
    Zelda32_Half section_header_index; /* see ZELDA_ELF32_SECTION_INDEX_* */
};

/*
 * ELF Relocations
 */

#define ZELDA_ELF32_RELOCATON_INFO_SYMBOL(X) (X >> 8)
#define ZELDA_ELF32_RELOCATON_INFO_TYPE(X) (X & 0xFF)

struct Zelda_Elf32_Relocation {
    Zelda32_Addr offset;
    Zelda32_Word info;
};

struct Zelda_Elf32_RelocationWithAddend {
    struct Zelda_Elf32_Relocation relocation;
    Zelda32_SignedWord addend;
};
