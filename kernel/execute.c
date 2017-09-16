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

#include "execute.h"
#include "execute.h"
#include "attributes.h"
#include "assert.h"

#include <orl.h>

/* Currently uses liborl. Ultimately this should probably only do a.out or ELF,
 * but this requires writing a new executable loader. */

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
    
    file->index += len;
    return file->data + at;
}

/*****************************************************************************/

long int OS216_ExeSeek( orl_file_id file_void, long int amount, int whence){
    struct cli_file *const file = (struct cli_file *)file_void;
    
    OS216_ASSERT(whence == SEEK_SET ||
        whence == SEEK_CUR ||
        whence == SEEK_END,
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

static struct orl_funcs funcs = {
    OS216_ExeRead,
    OS216_ExeSeek,
    malloc,
    free
};

/*****************************************************************************/

bool OS216_Execute(void *data, size_t len){
    struct cli_file file;
    orl_file_format format;
    
    orl_handle handle = ORLInit(&funcs);
    
    file.data = data;
    file.len = len;
    file.index = 0;
    
    /* Check format. */
    format = ORLFileIdentify(handle, &file);
    
    switch(format){
        case ORL_ELF:
            OS216_PrintString("ELF file\n");
            break;
        case ORL_COFF:
            OS216_PrintString("COFF file");
            break;
        case ORL_OMF:
            OS216_PrintString("OMF file");
            break;
        case ORL_UNRECOGNIZED_FORMAT:
            OS216_PrintString("Unknown file\n");
            ORLFini(handle);
            return false;
    }
    
    {
        orl_file_handle file_handle = ORLFileInit(handle, &file, format);
        if(file_handle == NULL){
            OS216_PrintString("Could not parse file\n");
            ORLFini(handle);
            return false;
        }
        
        ORLFileFini(file_handle);
    }
    
    OS216_Newline();
    
    ORLFini(handle);
    return true;
}
