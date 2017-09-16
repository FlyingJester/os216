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

struct cli_file{
    unsigned char *data;
    unsigned len, index;
};

/*****************************************************************************/

void *cli_read(orl_file_id file_void, size_t len){
    struct cli_file *const file = (struct cli_file *)file_void;
    
    const unsigned at = file->index;
    
    if(OS216_UNLIKELY(at + len > file->len))
        return NULL;
    
    file->index += len;
    return file->data + at;
}

/*****************************************************************************/

long int cli_seek( orl_file_id file_void, long int amount, int whence){
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

void *cli_alloc(size_t size){
    return calloc(size, 1);
}

/*****************************************************************************/

void cli_free(void *data){
    free(data);
}

/*****************************************************************************/

static struct orl_funcs funcs = {
    cli_read,
    cli_seek,
    cli_alloc,
    cli_free
};

/*****************************************************************************/

bool OS216_Execute(void *data, size_t len){
    struct cli_file file;
    
    orl_handle handle = ORLInit(&funcs);
    
    file.data = data;
    file.len = len;
    file.index = 0;
    
    /* Check format. */
    const orl_file_format format = ORLFileIdentify(handle, &file);
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
    
    OS216_Newline();
    
    
    
    ORLFini(handle);
    return true;
}
