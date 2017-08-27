/*
 * Copyright (c) 2017 Martin McDonough.  All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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
