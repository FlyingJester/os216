/*
 * (C) Martin McDonough 2017-2018
 * Any copyright of this file is dedicated to the Public Domain
 * http://creativecommons.org/publicdomain/1.0/
 */

#include "initrd.h"
#include "rd_contents.inc"

/*****************************************************************************/

/* Simple enum to get the RD contents numbered. */
#define X(WHAT) e ## WHAT,
enum {
    #include "rd_macro.inc"
    OS216_RamDiskCount
};
#undef X

/*****************************************************************************/

/* Names of the RD contents */
#define X(WHAT) #WHAT ,
static const char *os216_ram_disk_entry_names[] = {
    #include "rd_macro.inc"
    ""
};
#undef X

/*****************************************************************************/

/* Sizes of the RD contents */
#define X(WHAT) sizeof(WHAT),
static unsigned os216_ram_disk_entry_sizes[] = {
    #include "rd_macro.inc"
    0
};
#undef X

/*****************************************************************************/

/* RD contents */
#define X(WHAT) (void*)WHAT,
static const void *os216_ram_disk_entry_data[] = {
    #include "rd_macro.inc"
    (void*)0
};
#undef X

/*****************************************************************************/

unsigned OS216_GetRamDiskCount(void){
    return OS216_RamDiskCount;
}

/*****************************************************************************/

const char *OS216_GetRamDiskEntryName(unsigned i){
    return os216_ram_disk_entry_names[i];
}

/*****************************************************************************/

unsigned OS216_GetRamDiskEntrySize(unsigned i){
    return os216_ram_disk_entry_sizes[i];
}

/*****************************************************************************/

const void *OS216_GetRamDiskEntryData(unsigned i){
    return os216_ram_disk_entry_data[i];
}
