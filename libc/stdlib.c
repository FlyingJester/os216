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
    const uint64_t max){
    
    uint64_t n = 0;
    
    char b2;
    
    if(base >= 10){
        if((b2 = 10) > base)
            b2 = base;
    }
    
next_char_iter:
    {
        unsigned char i;
        const unsigned char c = *str;
        if(c < '0' && c < 'a' && c < 'A')
            goto done;
        
        {
            if(base >= 10){
                if(c >= '0' && c <= b2){
                    i = c - '0';
                    goto found_val;
                }
            }
            if(base > 10){
                if(c >= 'a' && c <= 'a' + (unsigned char)(base - 10)){
                    i = c - 'a';
                    goto found_val;
                }
                if(c >= 'A' && c <= 'A' + (unsigned char)(base - 10)){
                    i = c - 'A';
                    goto found_val;
                }
            }
            goto done;
        }
        found_val:
        
        {
            const uint64_t val = (n * 10) + (i - '0');
            
            if(val > max)
                goto done;
            
            n = val;
        }
        
        str++;
        goto next_char_iter;
    }
done:
    
    end[0] = str;
    return n;
}

/*****************************************************************************/

#ifdef __GNUC__
__attribute__((always_inline))
#elif defined MSC_VER_
__forceinline
#endif
static unsigned get_base(const char **str){
    if(**str == '0'){
        const char c = *(str[0]++);
        if(c == 'x' || c == 'X'){
            str[0]++;
            return 16;
        }
        else if(c == 'b' || c == 'B'){
            str[0]++;
            return 2;
        }
        else{
            return 8;
        }
    }
    return 10;
}

/*****************************************************************************/

#ifdef __GNUC__
__attribute__((always_inline))
#elif defined MSC_VER_
__forceinline
#endif
static unsigned get_negate(const char * __restrict__ * __restrict__ str){
    const char c = **str;
    if(c == '-'){
        str[0]++;
        return 1;
    }
    else if(c == '+'){
        str[0]++;
    }
    
    return 0;
}

/*****************************************************************************/

#define A_TO_X(TYPE, SUFFIX)\
TYPE ato ## SUFFIX(const char *str){\
    const unsigned negate = get_negate(&str);\
    const unsigned base = get_base(&str);\
    const TYPE number = strton(str, NULL, base, ~((TYPE)0));\
    return ((negate) ? (-number) : (number));\
}

/*****************************************************************************/

A_TO_X(int, i)

/*****************************************************************************/

A_TO_X(long, l)

/*****************************************************************************/

A_TO_X(int64_t, ll)

/*****************************************************************************/

#define STR_TO_X(SIGNED_TYPE, UNSIGNED_TYPE, SUFFIX)\
UNSIGNED_TYPE strtou ## SUFFIX(const char *__restrict__ str,\
    const char **__restrict__ end,\
    unsigned base){\
    return strton(str, end, base, ~((UNSIGNED_TYPE)0));\
}\
\
SIGNED_TYPE strto ## SUFFIX(const char *__restrict__ str,\
    const char **__restrict__ end,\
    unsigned base){\
    const unsigned negate = get_negate(&str);\
    const SIGNED_TYPE number = strton(str, end, base, (~((UNSIGNED_TYPE)0))>>1);\
    return ((negate) ? (-number) : (number));\
}

/*****************************************************************************/

STR_TO_X(int64_t, uint64_t, ll)

/*****************************************************************************/

STR_TO_X(long, unsigned long, l)

/*****************************************************************************/

STR_TO_X(int, unsigned, i)

/*****************************************************************************/

void qsort(void *const ptr, const size_t count, const size_t size,
    int(*compare)(const void *, const void *)){
    
    /* Gnome sort for stupid...I mean, simple implementation. */
    
    unsigned at = 0;
    
    if(count == 0 || count == 1)
        return;
    
    while(at < count){
        unsigned char *const byte_ptr = ((unsigned char *)ptr) + (at * size),
            *const previous_byte_ptr = byte_ptr - size;
        if(at == 0 || compare(byte_ptr, previous_byte_ptr) < 0){
            at++;
        }
        else{
            unsigned i;
            for(i = 0; i < size; i++){
                const unsigned char byte = byte_ptr[i];
                byte_ptr[i] = previous_byte_ptr[i];
                previous_byte_ptr[i] = byte;
            }
            at--;
        }
    }
}
