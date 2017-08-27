/* 
 *  Copyright (c) 2017 Martin McDonough.  All rights reserved.
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
#include "serial.h"

#include "../platform/print.h"
#include "../platform/fatal.h"

#include <stdint.h>

/*****************************************************************************/
/* Note that none fo these functions can FATAL for any reason other than an
 * invalid mode, since FATAL uses many of these functions. We trust that the
 * FATAL funcs are correct enough to use the right mode, otherwise we could
 * infinite loop.
 */

#define OS216_WRITE_STRING(X, Y, MODE, LEN, MSG)\
    do{\
        OS216_Serial_PutString(LEN, MSG);\
        OS216_VGA_PutString(X, Y, MODE, LEN, MSG);\
    } while(0);

/*****************************************************************************/

static unsigned os216_print_x = 0, os216_print_y = 0;

/*****************************************************************************/

static unsigned os216_is_whitespace(char c){
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

/*****************************************************************************/

void OS216_PrintString(const char *msg){
    OS216_PC_PrintString(eOS216_PC_Normal, msg);
}

/*****************************************************************************/

void OS216_PrintChar(char c){
    OS216_PC_PrintChar(eOS216_PC_Normal, c);
}

/*****************************************************************************/

void OS216_Newline(void){
    OS216_PC_Newline(eOS216_PC_Normal);
}

/*****************************************************************************/

void OS216_NewScreen(void){
    OS216_PC_NewScreen(eOS216_PC_Normal);
}

/*****************************************************************************/

void OS216_ClearScreen(void){
    OS216_PC_ClearScreen(eOS216_PC_Normal);
}

/*****************************************************************************/

void OS216_PrintInteger(int i){
    OS216_PC_PrintInteger(eOS216_PC_Normal, i);
}

/*****************************************************************************/

void OS216_PrintAddress(void *p){
    OS216_PC_PrintAddress(eOS216_PC_Normal, p);
}

/*****************************************************************************/

void OS216_PC_PrintString(enum OS216_PC_PrintMode mode, const char *msg){
    if((int)mode >= eOS216_PC_NUM_MODES)
        OS216_FATAL("Invalid print color");
    while(*msg != '\0'){
        unsigned word_len = 0;
        while(!os216_is_whitespace(msg[word_len])){
            
            word_len++;
            
            if(msg[word_len] == '\0'){
                
                if(os216_print_x + word_len > os216_vga_w)
                    OS216_Newline();
                
                OS216_WRITE_STRING(os216_print_x, os216_print_y,
                    mode, word_len, msg);
                
                os216_print_x += word_len;
                
                return;
            }
        }
        
        if(word_len < os216_vga_w &&
            os216_print_x + word_len >= os216_vga_w){
            if(word_len == 0){
                while(os216_is_whitespace(*msg))
                    msg++;
                continue;
            }
            OS216_Newline();
        }
        else if(word_len == 0){
            if(os216_print_x >= os216_vga_w) {}
            else if(*msg == ' '){
                OS216_VGA_Clear(os216_print_x, os216_print_y, mode, 1);
                OS216_Serial_PutString(1, msg);
                os216_print_x++;
            }
            else if(*msg == '\t'){
                const unsigned n = (os216_print_x + 4 > os216_vga_w) ?
                    os216_vga_w - os216_print_x : 4;
                OS216_VGA_Clear(os216_print_x, os216_print_y, mode, n);
                os216_print_x += n;
                if(os216_print_x >= os216_vga_w){
                    os216_print_x = 0;
                    if(++os216_print_y >= os216_vga_h)
                        os216_print_y = 0;
                }
            }
            else if(*msg == '\n')
                OS216_PC_Newline(mode);
            msg++;
            continue;
        }
        else if(word_len >= os216_vga_w)
            OS216_PC_Newline(mode);
        
        OS216_WRITE_STRING(os216_print_x, os216_print_y, mode, word_len, msg);
        os216_print_x += word_len;
        msg+=word_len;
    }
}

/*****************************************************************************/

void OS216_PC_Newline(enum OS216_PC_PrintMode mode){
    
    const unsigned remaining = os216_vga_w - os216_print_x;
    
    if((int)mode >= eOS216_PC_NUM_MODES)
        OS216_FATAL("Invalid print color");
    
    OS216_VGA_Clear(os216_print_x, os216_print_y, mode, remaining);
    
    os216_print_x = 0;
    if(++os216_print_y >= os216_vga_h)
        os216_print_y = 0;
    OS216_VGA_ClearLine(os216_print_y, mode);
    
    {
        const char nl = '\n';
        OS216_Serial_PutString(1, &nl);
    }
}

/*****************************************************************************/

void OS216_PC_NewScreen(enum OS216_PC_PrintMode mode){
    if((int)mode >= eOS216_PC_NUM_MODES)
        OS216_FATAL("Invalid print color");
    os216_print_y = 0;
    os216_print_x = 0;
}

/*****************************************************************************/

void OS216_PC_ClearScreen(enum OS216_PC_PrintMode mode){
    unsigned i = 0;
    if((int)mode >= eOS216_PC_NUM_MODES)
        OS216_FATAL("Invalid print color");
    while(i < os216_vga_h)
        OS216_VGA_ClearLine(i++, mode);
    os216_print_y = 0;
    os216_print_x = 0;
}

/*****************************************************************************/

void OS216_PC_PrintChar(enum OS216_PC_PrintMode mode, char c){
    if((int)mode >= eOS216_PC_NUM_MODES)
        OS216_FATAL("Invalid print color");
    switch(c){
        case '\n':
            OS216_PC_Newline(mode);
            break;
        case '\t':
            while(os216_print_x < os216_vga_w && (os216_print_x & 2)){
                const char space = ' ';
                OS216_WRITE_STRING(os216_print_x++,
                    os216_print_y, mode, 1, &space);
            }
            break;
        default:
            if(os216_print_x >= os216_vga_w){
                /* os216_print_x shouldn't be greater than os216_vga_w. But we
                 * can't FATAL in here, since FATAL uses this function. Just
                 * put the print location at the end, forcing an empty newline.
                 */
                os216_print_x = os216_vga_w;
                OS216_PC_Newline(mode);
            }
            OS216_WRITE_STRING(os216_print_x++, os216_print_y, mode, 1, &c);
            break;
    }
}

/*****************************************************************************/

void OS216_PC_PrintInteger(enum OS216_PC_PrintMode mode, int n){
    char buffer[16];
    unsigned i = 0;
    
    if((int)mode >= eOS216_PC_NUM_MODES)
        OS216_FATAL("Invalid print color");
    
    if(n == 0){
        buffer[sizeof(buffer) - ++i] = '0';
    }
    else{
        const unsigned negate = n < 0;
        if(negate)
            n = -n;
        while(n && i < sizeof(buffer)){
            const int digit = n % 10;
            buffer[sizeof(buffer) - ++i] = digit + '0';
            n /= 10;
        }
        
        if(negate)
            buffer[sizeof(buffer) - ++i] = '-';
    }
    
    if(i + os216_print_x >= os216_vga_w)
        OS216_PC_Newline(mode);
    
    {
        const char *const str = buffer + (sizeof(buffer) - i);
        OS216_WRITE_STRING(os216_print_x, os216_print_y, mode, i, str);
        os216_print_x += i;
    }
}

/*****************************************************************************/

void OS216_PC_PrintAddress(enum OS216_PC_PrintMode mode, void *p){
    char buffer[2+(sizeof(void*)*8)] = {};
    
    uintptr_t n = (uintptr_t)p;
    unsigned i = 0;
    buffer[0] = '0';
    buffer[1] = 'x';
    
    if((int)mode >= eOS216_PC_NUM_MODES)
        OS216_FATAL("Invalid print color");
    
    while(i <= sizeof(buffer)-2){
        const int digit = n & 0x0F;
        buffer[sizeof(buffer) - i++] = (digit > 9) ? (digit + 'A' - 10) : (digit + '0');
        n >>= 4;
    }
    
    if(sizeof(buffer) + os216_print_x >= os216_vga_w)
        OS216_Newline();
    
    OS216_WRITE_STRING(os216_print_x, os216_print_y, mode, sizeof(buffer), buffer);
    os216_print_x += sizeof(buffer);
}

/*****************************************************************************/
