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

/* PCH must be first */
#include "malloc.h"

#include <string.h>
#include <stdio.h>

#include "platform/print.h"
#include "platform/fatal.h"

#include "execute.h"
#include "attributes.h"
#include "assert.h"
#include "physical_memory.h"

#include <orl.h>
#include <exeelf.h>

/* Currently uses liborl. Ultimately this should probably only do a.out or ELF,
 * but this requires writing a new executable loader. */

typedef void(*start_func)(void);

/*****************************************************************************/

void *OS216_ExeRead(orl_file_id file_void, size_t len);

/*****************************************************************************/

long int OS216_ExeSeek(orl_file_id file_void, long int amount, int whence);

/*****************************************************************************/

void *OS216_ExeRead(orl_file_id file_void, size_t len){
    struct cli_file *const file = (struct cli_file *)file_void;
    
    const unsigned at = file->index;
    
    if(OS216_UNLIKELY(at + len > file->len))
        return NULL;
    
    {
        void *const data = malloc(len);
        memcpy(data, file->data + at, len);
        file->index += len;
        return data;
    }
}

/*****************************************************************************/

long int OS216_ExeSeek( orl_file_id file_void, long int amount, int whence){
    struct cli_file *const file = (struct cli_file *)file_void;
    
    OS216_ASSERT(whence == SEEK_SET ||
        whence == SEEK_CUR,
        "Invalid seek whence.");
    
    if(whence == SEEK_SET){
        OS216_ASSERT(amount >= 0, "Seek before start in SEEK_SET");
        OS216_ASSERT(amount <= (long)file->len, "Seek after end in SEEK_SET");
        file->index = amount;
    }
    else if(whence == SEEK_CUR){
        OS216_ASSERT(amount >= 0 ||
            amount <= -((long)(file->index)),
            "Seek before start in SEEK_CUR");
        OS216_ASSERT(amount <= 0 ||
            file->index + (unsigned)amount <= file->len,
            "Seek after end in SEEK_CUR");
        file->index += amount;
    }
    
    return file->index;
}

/*****************************************************************************/

static orl_return os216_found_start;
static orl_symbol_value os216_start_value;
static orl_sec_handle os216_start_section;

/*****************************************************************************/

static orl_return os216_find_start(const orl_symbol_handle sym){
    const char *symname = ORLSymbolGetName(sym);
    if(strcmp(symname, "start") == 0){
        const orl_return symbol_value_ok =
            ORLSymbolGetValue(sym, &os216_start_value);
        OS216_ASSERT(symbol_value_ok == ORL_OKAY,
            "Cound not get symbol name");
        
        os216_start_section = ORLSymbolGetSecHandle(sym);
        
        os216_found_start = ORL_OKAY;
        return ORL_FALSE;
    }
    
    return ORL_TRUE;
}

/*****************************************************************************/

bool OS216_Execute(void *data, size_t len){
    struct cli_file file;
    struct orl_funcs funcs;
    orl_file_format format;
    orl_handle handle;
    orl_file_handle file_handle;
    
    file.data = data;
    file.len = len;
    file.index = 0;
    
    funcs.cli_alloc = malloc;
    funcs.cli_free = free;
    funcs.cli_read = OS216_ExeRead;
    funcs.cli_seek = OS216_ExeSeek;
    
    handle = ORLInit(&funcs);
    
    /* Check format. */
    format = ORLFileIdentify(handle, &file);
    
    if(format == ORL_UNRECOGNIZED_FORMAT){
        OS216_PrintString("Unrecognized executable format");
        goto exec_fail;
    }
    
    {
        file_handle = ORLFileInit(handle, &file, format);
        if(file_handle == NULL){
            OS216_PrintString("Could not parse file\n");
            goto exec_fail;
        }
        else{
            const orl_sec_handle symbol_table =
                ORLFileGetSymbolTable(file_handle);
            
            os216_found_start = ORL_FALSE;
            ORLSymbolSecScan(symbol_table, os216_find_start);
            if(os216_found_start != ORL_OKAY){
                OS216_PrintString("Could not find start symbol");
                goto exec_file_fail;
            }
            {
                unsigned char *contents;
                const orl_return get_contents_ok =
                    ORLSecGetContents(os216_start_section, &contents);
                start_func start;
                
                OS216_ASSERT(get_contents_ok == ORL_OKAY,
                    "Could not get executable section contents");
                
                start = (start_func)(contents + os216_start_value);
                
                start();
            }
        }
    }
    
    OS216_Newline();
    
    ORLFini(handle);
    return true;
    
exec_file_fail:
    ORLFileFini(file_handle);
exec_fail:
    ORLFini(handle);
    return false;
}
