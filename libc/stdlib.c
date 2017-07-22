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
