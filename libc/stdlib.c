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

#include "include/stdlib.h"

/*****************************************************************************/

#ifdef __GNUC__
__attribute__((always_inline))
#elif defined MSC_VER_
__forceinline
#endif
static uint64_t strton(const char *__restrict__ str,
    const char **__restrict__ end,
    const unsigned base,
    const unsigned max){
    
    
    
}

/*****************************************************************************/

int atoi(const char *c){
    unsigned negate = 0, base = 10;
    
    if(*c == '-'){
        negate = 1;
        c++;
    }
    else if(*c == '+'){
        c++;
    }
    
    
    if(*c == '0'){
        c++;
        if(c == 'x' || c == 'X'){
            base = 16;
            c++;
        }
        else if(c == 'b' || c == 'B'){
            base = 2;
            c++;
        }
        else{
            base = 8;
        }
    }
    
    {
        const int number = strton(c, NULL, base, 0xFFFFFFFF);
    
        if(negate)
            return -number;
        else
            return number;
    }
}

/*****************************************************************************/

long atol(const char *c){
    
}

/*****************************************************************************/

int64_t atoll(const char *c){
    
}
unsigned long strtoul(const char *__restrict__ str,
    const char **__restrict__ end,
    unsigned base){
    return strton(str, end, base, 0xFFFFFFFFFFFFFFFFul);
}

/*****************************************************************************/

uint64_t strtoull(const char *__restrict__ str,
    const char **__restrict__ end,
    unsigned base){
    return strton(str, end, base, 0xFFFFFFFFFFFFFFFFull);
}

/*****************************************************************************/

void qsort(void *ptr, size_t count, size_t size,
    int(*compare)(const void *, const void *)){
    
#define GET_BYTE(X) (((uint8_t*)ptr)+(X*size))
#define GET_DWORD(X) (((unsigned*)ptr)+(X*size/sizeof(unsigned)))
    
    unsigned at = 0;
    while(at < count){
        if(at == 0 || compare(GET_BYTE(at), GET_BYTE(at-1)))
            at++;
        else{
            /* XOR Swap */
            unsigned i;
            for(i = 0; i < size; i++){
                GET(at)[i] ^= GET(at+1)[i];
                GET(at+1)[i] ^= GET(at)[i];
                GET(at)[i] ^= GET(at+1)[i];
            }
            at--;
        }
    }
}
