;  Copyright (c) 2017 Martin McDonough.  All rights reserved.
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

struc OS216_IDTEntry
    idt_entry_limit resw 1
    idt_entry_base  resd 1
endstruc

struc OS216_IDTDescriptor
    idt_offset0 resw 1
    idt_selector resw 1
    idt_unused resb 1
    idt_flags resb 1
    idt_offset1 resw 1
endstruc

%macro dummy_int 1
    push null_term
    push %1
    push DWORD 0
    push file_name
    call OS216_Fatal
%endmacro

; Dirties ebx. eax must contain the IDT
%macro os216_setup_interrupt 3 ; Address, Type, IRQ Number, selector
    ; Setup the offset.
    mov ebx, %1
    mov WORD [eax+idt_offset0+( %3 * OS216_IDTDescriptor_size )], bx
    shr ebx, 16
    mov WORD [eax+idt_offset1+( %3 * OS216_IDTDescriptor_size )], bx
    mov BYTE [eax+idt_flags+( %3 * OS216_IDTDescriptor_size )], %2
    mov WORD [eax+idt_selector+( %3 * OS216_IDTDescriptor_size)], 0x10 ; Set the code segment
%endmacro
