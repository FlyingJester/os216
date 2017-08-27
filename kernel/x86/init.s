;  Copyright (c) 2015-2017 Martin McDonough.  All rights reserved.
; 
;  Redistribution and use in source and binary forms, with or without
;  modification, are permitted provided that the following conditions are met:
; 
; - Redistributions of source code must retain the above copyright notice,
;     this list of conditions and the following disclaimer.
; 
; - Redistributions in binary form must reproduce the above copyright notice,
;     this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
; 
; - Products derived from this software may not be called "os216", nor may
;     "216" appear in their name, without prior written permission of
;     the copyright holders.
; 
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
; FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
; IN THE SOFTWARE.

; Multiboot data
MBALIGN   equ 1
MEMINFO   equ 2
FLAGS     equ MBALIGN | MEMINFO
MAGIC     equ 0x1BADB002
CHECKSUM  equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .bootstrap_stack, nobits
align 4
stack_bottom:
resb 4096
stack_top:

section .text
align 4

; NASM implies GCC for us?
extern __cxa_finalize
extern _init
extern _fini
extern OS216_Main
extern OS216_Serial_Init

global _OS216_AsmMain
_OS216_AsmMain:
    cli
    mov esp, stack_top
    
    call _init
    call OS216_Serial_Init
    call OS216_Main
    
;    mov eax, 0
;    ud2
    
    ; We don't really need to clean up here, but we might as well.
    push dword 0
    call __cxa_finalize
    ; It probably doesn't matter if the stack is balanced, but...
    add esp, 4
    
    call _fini
    
.hang:
    cli
    hlt
    jmp .hang
