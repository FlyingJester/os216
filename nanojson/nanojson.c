/* Copyright (c) 2018 Martin McDonough.  All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "nanojson.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*****************************************************************************/

void NJ_FreeValue(struct NJ_Value *value){
    
    struct NJ_Value *extra;
    unsigned i, extra_size;
    
    switch(value->type){
        case NJ_ArrayType:
            extra = value->value.array.values;
            extra_size = value->value.array.len;
            break;
        case NJ_ObjectType:
            extra = value->value.object.values;
            extra_size = value->value.object.len;
            free(value->value.object.names);
            break;
        default:
            return;
    }
    
    for(i = 0; i < extra_size; i++){
        NJ_FreeValue(extra + i);
    }
    if(extra_size != 0)
        free(extra);
}

/*****************************************************************************/

unsigned NJ_ParseRoot(const char *string,
    unsigned len,
    struct NJ_Value *out_value){
    
    unsigned i = 0;
    while(i < len && isspace(string[i]))
        i++;
    
    if(string[i] == '{'){
        i++;
        NJ_ParseObject(string, len, &i, out_value);
        return NJ_OBJECT_TYPE;
    }
    else if(string[i] == '['){
        i++;
        NJ_ParseArray(string, len, &i, out_value);
        return NJ_ARRAY_TYPE;        
    }
    else{
        return 0;
    }
}

/*****************************************************************************/

unsigned NJ_ParseValue(const char *string,
    unsigned len,
    unsigned *i,
    struct NJ_Value *out_value){
    
    char c;
    
    while(*i < len && isspace(c = string[*i]))
        i[0]++;
    if(*i >= len)
        return 0;
    
    if(c == '{'){
        i[0]++;
        return NJ_ParseObject(string, len, i, out_value);
    }
    else if(c == '['){
        i[0]++;
        return NJ_ParseArray(string, len, i, out_value);
    }
    else if(isdigit(c)){
        out_value->type = NJ_NumberType;
        out_value->value.number = NJ_ParseNumber(string, len, i);
        return 0;
    }
    else if(c == '"'){
        const unsigned start = i[0]++;
        NJ_ParseString(string, len, i);
        out_value->value.string.len = (*i) - start;
        out_value->value.string.string = string + start;
        if(string[*i] != '"')
            return 1;
        i[0]++;
        return 0;
    }
    else if((*i) + 6 < len){
        if(memcmp(string + (*i), "true", 4) == 0){
            i[0]+=4;
            out_value->type = NJ_TrueType;
            return 0;
        }
        else if(memcmp(string + (*i), "false", 5) == 0){
            i[0]+=5;
            out_value->type = NJ_FalseType;
            return 0;
        }
    }

    return 1;
}

/*****************************************************************************/

unsigned NJ_ParseObject(const char *string,
    unsigned len,
    unsigned *i,
    struct NJ_Value *out_value){
    
    char c;
    unsigned cap = 8, num = 0;
    out_value->type = NJ_ObjectType;
    out_value->value.object.len = 0;
    
    while(*i < len && isspace(c = string[*i]))
        i[0]++;
    
    if(*i >= len)
        return 1;
    
    if(c == '}'){
        i[0]++;
        return 0;
    }
    
    out_value->value.object.names = malloc(sizeof(struct NJ_String) * cap);
    out_value->value.object.values = malloc(sizeof(struct NJ_Value) * cap);
    
    do{
        if(num >= cap){
            cap <<= 1;
            out_value->value.object.names =
                realloc(out_value->value.object.names,
                    sizeof(struct NJ_String) * cap);
            out_value->value.object.values =
                realloc(out_value->value.object.values,
                    sizeof(struct NJ_Value) * cap);
        }
        
        while(*i < len && isspace(c = string[*i]))
            i[0]++;
        if(*i >= len)
            return 1;
                
        if(string[*i] != '"')
            return 1;
        
        i[0]++;
        
        {
            const unsigned start = *i;
            NJ_ParseString(string, len, i);
            out_value->value.object.names[num].len = (*i) - start;
            out_value->value.object.names[num].string = string + start;
            
            if(string[*i] != '"')
                return 1;
            i[0]++;
        }
        
        while(*i < len && isspace(c = string[*i]))
            i[0]++;
        if(*i >= len)
            return 1;
        
        if(c != ':')
            return 1;
        
        i[0]++;
        
        while(*i < len && isspace(string[*i]))
            i[0]++;
        if(*i >= len)
            return 1;
        
        if(NJ_ParseValue(string, len, i, out_value->value.object.values + num))
            return 1;
        
        while(*i < len && isspace(c = string[*i]))
            i[0]++;
        if(*i >= len)
            return 1;
        
        num++;
        
        if(c == '}'){
            i[0]++;
            out_value->value.object.len = num;
            return 0;
        }
        else if(c == ','){
            i[0]++;
        }
        else{
            return 1;
        }
    }while(1);
}

/*****************************************************************************/

unsigned NJ_ParseArray(const char *string,
    unsigned len,
    unsigned *i,
    struct NJ_Value *out_value){
    
    char c;
    unsigned cap = 8, num = 0;
    out_value->type = NJ_ArrayType;
    out_value->value.array.len = 0;

    while(*i < len && isspace(c = string[*i]))
        i[0]++;
    if(*i >= len)
        return 1;
    
    if(string[*i] == ']'){
        i[0]++;
        return 0;
    }
    
    out_value->value.array.values = malloc(sizeof(struct NJ_Value) * cap);

    
    do{
        if(num >= cap){
            cap <<= 1;
            out_value->value.array.values =
                realloc(out_value->value.array.values,
                    sizeof(struct NJ_Value) * cap);
        }
        
        while(*i < len && isspace(c = string[*i]))
            i[0]++;
        if(*i >= len)
            return 1;
        
        if(NJ_ParseValue(string, len, i, out_value->value.array.values + num))
            return 1;
        
        while(*i < len && isspace(c = string[*i]))
            i[0]++;
        if(*i >= len)
            return 1;
        
        if(c == ']'){
            i[0]++;
            out_value->value.array.len = num;
            return 0;
        }
        else if(c == ','){
            i[0]++;
            num++;
        }
        else{
            return 1;
        }
        
    } while(1);

}

/*****************************************************************************/

float NJ_ParseNumber(const char *string, unsigned len, unsigned *i){
    long number;    
    {
        char *end;
        const char *const start = string + *i;
        number = strtol(start, &end, 10);
        const unsigned len = end - start;
        i[0] += len;
    }

    if(string[*i] == '.'){
        char *end;
        const char *const start = string + (*i) + 1;
        float fraction = strtol(start, &end, 10);
        const unsigned len = end - start;
        i[0] += len + 1;
        {
            unsigned n = 0;
            while(n++ < len)
                fraction *= 0.1;
        }
    }
    
    return number;
}

/*****************************************************************************/

void NJ_ParseString(const char *string, unsigned len, unsigned *i){
    while(*i < len && string[*i] != '"'){
        if(string[*i] == '\\')
            i[0]+=2;
        else
            i[0]++;
    }
}
