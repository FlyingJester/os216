/* Any copyright of this file is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

ENTRY(start)

SECTIONS{
    
    .text BLOCK(4K) : ALIGN(4K){
        *(.text)
    }
    
    .rodata BLOCK(4K) : ALIGN(4K){
        *(.rodata)
    }
    
    .data BLOCK(4K) : ALIGN(4K){
        *(.data)
    }
    
    .bss BLOCK(4K) : ALIGN(4K){
        *(COMMON)
        *(.bss)
    }
}
