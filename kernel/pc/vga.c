#include "vga.h"

#include <stdint.h>

const unsigned os216_vga_w = 80, os216_vga_h = 25;
static uint16_t *const os216_vga_buffer = (uint16_t*)0xB8000;

#define C0 ((12 | (8 << 4)) << 8)
#define C1 ((6  | (8 << 4)) << 8)
#define C2 ((4  | (8 << 4)) << 8)
#define C3 (4 << 12)

static const uint16_t os216_vga_colors[eOS216_PC_NUM_MODES] = {
    C0,
    C1,
    C2,
    C3,
};

static const uint16_t os216_vga_space_color[eOS216_PC_NUM_MODES] = {
    C0 | ' ',
    C1 | ' ',
    C2 | ' ',
    C3 | ' ',
};

void OS216_VGA_PutString(unsigned x,
    unsigned y,
    enum OS216_PC_PrintMode mode,
    unsigned n,
    const char *msg){
    uint16_t *character = os216_vga_buffer + x + (y * os216_vga_w);
    unsigned i = 0;
    const uint16_t color = os216_vga_colors[(unsigned)mode];
    while(i < n){
        character[i] = color | (uint16_t)msg[i];
        i++;
    }
}

void OS216_VGA_Clear(unsigned x,
    unsigned y,
    enum OS216_PC_PrintMode mode,
    unsigned n){
    uint16_t *character = os216_vga_buffer + x + (y * os216_vga_w);
    unsigned i = 0;
    const uint16_t c = os216_vga_space_color[(unsigned)mode];
    while(i < n)
        character[i++] = c;
}

void OS216_VGA_ClearLine(unsigned y, enum OS216_PC_PrintMode mode){
    uint16_t *character = os216_vga_buffer + (y * os216_vga_w);
    unsigned i = 0;
    const uint16_t c = os216_vga_space_color[(unsigned)mode];
    while(i < os216_vga_w)
        character[i++] = c;
}
