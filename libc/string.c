/*
 * Copyright (c) 2017 Martin McDonough.  All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
 
 #include "include/string.h"

/*****************************************************************************/

char *strcpy(char *__restrict__ to, const char *__restrict__ from){
    size_t i = 0;
    while(from[i] != '\0'){
        to[i] = from[i];
        i++;
    }
    to[i] = '\0';
    return to;
}

/*****************************************************************************/

char *strncpy(char *__restrict__ to, const char *__restrict__ from, size_t n){
    size_t i = 0;
    while(from[i] != '\0'){
        to[i] = from[i];
        if(++i > n)
            return to;
    }
    to[i] = '\0';
    return to;
}

/*****************************************************************************/

char *strlcpy(char *__restrict__ to, const char *__restrict__ from, size_t n){
    size_t i = 0;
    if(n == 0)
        return 0;
    while(from[i] != '\0'){
        to[i] = from[i];
        if(++i == n)
            break;
    }
    to[i] = '\0';
    return to;
}

/*****************************************************************************/

size_t strlen(const char *string){
    size_t i = 0;
    while(string[i] != '\0')
        i++;
    return i;
}

/*****************************************************************************/

size_t strnlen(const char *string, size_t n){
    size_t i = 0;
    while(i < n && string[i] != '\0')
        i++;
    return i;
}

/*****************************************************************************/

char *strcat(char *__restrict__ to, const char *__restrict__ from){
    size_t i = 0, e = 0;
    while(to[i] != '\0')
        i++;
    
    while(from[e] != '\0')
        to[i++] = from[e++];
    
    to[i] = '\0';
    return to;
}

/*****************************************************************************/

char *strncat(char *__restrict__ to, const char *__restrict__ from, size_t n){
    size_t i = 0, e = 0;
    while(to[i] != '\0')
        i++;
    
    while(from[e] != '\0'){
        to[i++] = from[e++];
        if(e >= n)
            return to;
    }
    to[i] = '\0';
    
    return to;
}

/*****************************************************************************/

char *strncat_s(char *__restrict__ to,
    size_t to_size,
    const char *__restrict__ from,
    size_t n){
    
    size_t i = 0, e = 0;
    
    if(to_size == 0)
        return to;
    
    while(i < to_size && to[i] != '\0')
        i++;
    
    while(i < to_size && from[e] != '\0'){
        to[i++] = from[e++];
        if(e >= n)
            return to;
    }
    
    to[i] = '\0';
    return to;
}

/*****************************************************************************/

char *strlcat(char *__restrict__ to, const char *__restrict__ from, size_t n){
    size_t i = 0, e = 0;
    while(to[i] != '\0')
        i++;
    
    while(from[e] != '\0'){
        if(e >= n){
            to[i] = '\0';
            return to;
        }
        to[i++] = from[e++];
    }
    to[i] = '\0';
    
    return to;
}

/*****************************************************************************/

int strcmp(const char *__restrict__ a, const char *__restrict__ b){
    int c;
    size_t i = 0;
    
    if(*a == '\0' || *b == '\0')
        return *a - *b;
    
    do{
        const int ac = a[i], bc = b[i];
        i++;
        c = ac - bc;
        if(ac == '\0' || bc == '\0')
            break;
        
    }while(c != 0);
    
    return c;
}

/*****************************************************************************/

int strncmp(const char *__restrict__ a, const char *__restrict__ b, size_t n){
    int c;
    size_t i = 0;
    
    if(n == 0)
        return 0;
    
    do{
        const int ac = a[i], bc = b[i];
        i++;
        c = ac - bc;
        if(ac == '\0' || bc == '\0')
            break;
        
    }while(i < n && c != 0);
    
    return c;
}

/*****************************************************************************/

void *memcpy(void *__restrict__ dest, const void *__restrict__ src, size_t n){
    size_t i = 0;
    while(i < n){
        ((uint8_t*)dest)[i] = ((uint8_t*)src)[i];
        i++;
    }
    return dest;
}

/*****************************************************************************/

void *memset(void *dest, uint8_t val, size_t n){
    size_t i = 0;
    while(i < n){
        ((uint8_t*)dest)[i] = val;
        i++;
    }

    return dest;
}

/*****************************************************************************/

void *memchr(const void *ptr, int val, size_t n){
    size_t i = 0;
    while(i < n){
        uint8_t *const at = ((uint8_t*)ptr) + i;
        if(*at == val)
            return at;
        i++;
    }
    return (void*)0;
}

/*****************************************************************************/

int memcmp(const void *__restrict__ av, const void *__restrict__ bv, size_t n){
    int c;
    size_t i = 0;
    const uint8_t *const a = av, *const b = bv;
    
    if(n == 0)
        return 0;
    
    do{
        const int ac = a[i], bc = b[i];
        i++;
        c = ac - bc;
    }while(i < n && c != 0);
    
    return c;
}

/*****************************************************************************/
