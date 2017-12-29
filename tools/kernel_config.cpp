/* Copyright (c) 2018 Martin McDonough.  All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "nanojson/nanojson.h"

static void *buffer_file(const char *file, unsigned long *size){
    size[0] = 0;

    if(!file || !size){
        return NULL;
    }
    else{
        FILE * const that = fopen(file, "rb");
        unsigned long to = 0, capacity = 0x100;
        char *buffer = NULL;
        
        if(!that){
            fputs("[BufferFile] Could not open file ", stderr);
            fputs(file, stderr);
            fputc('\n', stderr);
            return NULL;
        }

        /* Load the file. */
        do{
            capacity <<= 1;
            if(buffer)
                buffer = (char*)realloc(buffer, capacity);
            else
                buffer = (char*)malloc(capacity);
            to += fread(buffer+to, 1, capacity-to, that);
        }while(!feof(that));

        size[0] = to;
        fclose(that);
        return buffer;
    }
}

static inline void driver(const NJ_Value &value){
    // For each base-level key:
    //    write out the name to DRIVERS in userland/drivers/driver_config.mk
    FILE *const base_output = fopen("userland/drivers/driver_config.mk", "wb");
    fputs("# THIS FILE IS AUTOGENERATED. DO NOT MODIFY DIRECTLY\n\n", base_output);
    fputs("DRIVERS=", base_output);
    
    assert(value.type == NJ_ObjectType);
    
    const NJ_Value *const base_values = value.value.object.values;
    const NJ_String *const base_names = value.value.object.names;
    const size_t base_len = value.value.object.len;
    
    for(size_t dir = 0; dir < base_len; dir++){
        fwrite(base_names[dir].string, base_names[dir].len, 1, base_output);
        fputc(' ', base_output);
        
        std::string path = "userland/drivers/";
        path.append(base_names[dir].string, base_names[dir].len);
        path += "/driver_config.mk";
        
        FILE *const top_output = fopen(path.c_str(), "wb");
        // Iterate twice, once to get the enabled drivers, and a second time recording all of them.
        assert(base_values[dir].type == NJ_ObjectType);
        const NJ_Object &dirval =  base_values[dir].value.object;
        fputs("# THIS FILE IS AUTOGENERATED. DO NOT MODIFY DIRECTLY\n\n", top_output);
        fputs("ENABLED_DRIVERS=", top_output);
        for(size_t drv = 0; drv < dirval.len; drv++){
            if(dirval.values[drv].type == NJ_TrueType){
                fwrite(dirval.names[drv].string, dirval.names[drv].len, 1, top_output);
                fputc(' ', top_output);
            }
        }
        fputc('\n', top_output);
        fputs("ALL_DRIVERS=", top_output);
        for(size_t drv = 0; drv < dirval.len; drv++){
            fwrite(dirval.names[drv].string, dirval.names[drv].len, 1, top_output);
            fputc(' ', top_output);
        }
        fputc('\n', top_output);
        fclose(top_output);
    }
    
    fputc('\n', base_output);
    fclose(base_output);
}

#if 0

static inline void driver(const NJ_Value &value){
    // We expect a two-tiered set of drivers, by class and then by name.
    // Every level-one has a property named "enabled", which defaults to
    // true if it's not found.
    assert(value.type == NJ_ObjectType);
    
    std::string path;
    for(size_t i = 0; i < value.value.object.len; i++){
        const NJ_String &string = value.value.object.names[i];
        path = "userland/drivers/";
        path.append(string.string, string.len);
        path += '/';
        
        // Base size, used to pop the path back to the base driver directory again.
        const size_t base_size = path.length();
        path += "driver_config.mk";
        
        FILE *const base_output = fopen(path.c_str(), "wb");
        fputs("# THIS FILE IS AUTOGENERATED. DO NOT MODIFY DIRECTLY\n\n", base_output);
        fputs("DRIVERS=", base_output);
        const NJ_Value *values = value.value.object.values;
        const NJ_String *names = value.value.object.names;
        for(size_t d = 0; d < value.value.object.len; d++){
            assert(values[d].type == NJ_ObjectType);
            path.resize(base_size);

            // Write this driver directory to the base
            fwrite(names[d].string, names[d].len, 1, base_output);
            fputc(' ', base_output);

            path.append(names[d].string, names[d].len);
            path += '/';
            const size_t top_size = path.size();
            path += "driver_config.mk";
            FILE *const top_output = fopen(path.c_str(), "wb");
            
            printf("Opening driver path %s\n", path.c_str());
            
            fputs("# THIS FILE IS AUTOGENERATED. DO NOT MODIFY DIRECTLY\n\n", base_output);
            fputs("ALL_DRIVERS=\n", base_output);
            fputs("ENABLED_DRIVERS=\n", base_output);
            
            for(size_t e = 0; e < values[d].value.object.len; e++){
                assert(values[d].value.object.values[e].type == NJ_TrueType ||
                    values[d].value.object.values[e].type == NJ_FalseType);
                const size_t top_len = values[d].value.object.names[e].len;
                const char *const top_string = values[d].value.object.names[e].string;

                printf("Opening driver path %s\n", path.c_str());
                
                fputs("ALL_DRIVERS+=", top_output);
                fwrite(top_string, top_len, 1, top_output);
                fputs(" \n", top_output);
                
                if(values[d].value.object.values[e].type == NJ_TrueType){
                    fputs("ENABLED_DRIVERS+=", top_output);
                    fwrite(top_string, top_len, 1, top_output);
                    fputs(" \n", top_output);
                }
            }
            fputc('\n', top_output);
            fclose(top_output);
        }
        
        fputc('\n', base_output);
        fclose(base_output);
    }
}

#endif

int main(int argc, char **argv){
    
    if(argc < 3 || strcmp(argv[2], "driver") != 0){
        puts("Usage: kconf <input_file> <mode>");
        puts("\tModes: driver");
        return EXIT_FAILURE;
    }
    
    unsigned long len;
    if(char *const src = (char*)buffer_file(argv[1], &len)){
        struct NJ_Value value;
        unsigned i = 0;
        if(NJ_ParseValue(src, len, &i, &value)){
            fputs("Could not parse input file ", stdout); puts(argv[1]);
            printf("DEBUG: %i\n", (int)i);
            return EXIT_FAILURE;
        }
        // Only mode right now is driver. Otherwise, we would check argv[2] here.
        driver(value);
        
        NJ_FreeValue(&value);
        free(src);
    }
    else{
        fputs("Could not open input file ", stdout); puts(argv[1]);
        return EXIT_FAILURE;
    }
}
