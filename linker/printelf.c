#include "elf/elf.h"
#include "elf/elf_load.h"

#include <stdlib.h>
#include <stdio.h>

static void print_elf_header(const struct Zelda_Elf32_Header *header){

    char buffer[32];
    
#define ZELDA_PRINT_HEADER(WHAT, SIZE) do{\
    fputs(#WHAT ": ", stdout);\
    sprintf(buffer, "%i", (int)(header->WHAT));\
    fputs(buffer, stdout); fputc('\n', stdout);\
}while(0);

    ZELDA_ELF32_PROCESS_HEADER(ZELDA_PRINT_HEADER);
}

static const void *load_file(const char *file, unsigned *size){
    if(!file || !size){
        return NULL;
    }
    else{
        FILE * const that = fopen(file, "r");
        unsigned to = 0, capacity = 0x100;
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
                buffer = realloc(buffer, capacity);
            else
                buffer = malloc(capacity);
            to += fread(buffer+to, 1, capacity-to, that);
        }while(!feof(that));
        
        size[0] = to;
        fclose(that);
        return buffer;
    }
}

int main(int argc, char **argv){
    if(argc < 2)
        return EXIT_FAILURE;
    {
        unsigned size = 0;
        const void *const data = load_file(argv[1], &size);
        struct Zelda_Elf32_Header header;
        if(data == NULL){
            fputs("Could not open file ", stderr);
            fputs(argv[1], stderr); fputc('\n', stderr);
            return EXIT_FAILURE;
        }
        printf("Reading elf data for %s (%i bytes)\n", argv[1], size);
        
        if(Zelda_Elf32_LoadHeader(data, 0, size, &header) != 0){
            fputs("Error reading ELF file ", stderr);
            fputs(argv[1], stderr); fputc('\n', stderr);
            free((void*)data);
            return EXIT_FAILURE;
        }
        print_elf_header(&header);
        free((void*)data);
    }
    return EXIT_SUCCESS;
}
