#pragma once
#ifndef ZELDA_A_OUT_LOAD_H
#define ZELDA_A_OUT_LOAD_H

struct Zelda_AOut_Header{
    uint32_t endian_indicator;
    uint32_t text;
    uint32_t data;
    uint32_t bss;
    uint32_t syms;
    uint32_t entry;
    uint32_t text_relocation_table_size;
    uint32_t data_relocation_table_size;
};

#endif /* ZELDA_A_OUT_LOAD_H */
