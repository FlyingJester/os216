/* 
 *  Copyright (c) 2015-2017 Martin McDonough.  All rights reserved.
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

#include "vga.h"

#include <stdint.h>

/*****************************************************************************/

const unsigned os216_vga_w = 80, os216_vga_h = 25;

/*****************************************************************************/

static uint16_t *const os216_vga_buffer = (uint16_t*)0xB8000;

/*****************************************************************************/

#define C0 ((12 | (8 << 4)) << 8)

/*****************************************************************************/

#define C1 ((6  | (8 << 4)) << 8)

/*****************************************************************************/

#define C2 ((4  | (8 << 4)) << 8)

/*****************************************************************************/

#define C3 (4 << 12)

/*****************************************************************************/

static const uint16_t os216_vga_colors[eOS216_PC_NUM_MODES] = {
    C0,
    C1,
    C2,
    C3,
};

/*****************************************************************************/

static const uint16_t os216_vga_space_color[eOS216_PC_NUM_MODES] = {
    C0 | ' ',
    C1 | ' ',
    C2 | ' ',
    C3 | ' ',
};

/*****************************************************************************/

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

/*****************************************************************************/

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

/*****************************************************************************/

void OS216_VGA_ClearLine(unsigned y, enum OS216_PC_PrintMode mode){
    uint16_t *character = os216_vga_buffer + (y * os216_vga_w);
    unsigned i = 0;
    const uint16_t c = os216_vga_space_color[(unsigned)mode];
    while(i < os216_vga_w)
        character[i++] = c;
}

/*****************************************************************************/
