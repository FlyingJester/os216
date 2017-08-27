/* Any copyright of this file is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

ENTRY(_OS216_AsmMain)

SECTIONS{
    /* Start at 1 MB */
    . = 1M;
    
    .mutliboot BLOCK(4K) : ALIGN(4K){
        *(.multiboot)
    }
    
    .init BLOCK(4K) : ALIGN(4K){
        *(.init)
        *(.other_init)
        crtend.o(.text)
    }
    
    .fini BLOCK(4K) : ALIGN(4K){
        *(.fini)
        *(.other_fini)
        crtbegin.o(.text)
    }

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
        *(.bootstrap_stack)
    }
}
