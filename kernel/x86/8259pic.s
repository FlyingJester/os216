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

%include "8259pic.inc"

section .text
align 4

nop_call:
    times 64 nop
    ret

global OS216_Setup8259Pic
OS216_Setup8259Pic:
    xor ecx, ecx
    xor eax, eax
    ; Save the PIC masks
    in al, pic_data(1)+1
    shl ax, 8
    in al, pic_data(2)+1
    mov cx, ax
    
    ; Delay...
    call nop_call
    
    ; Send init sequence to the PICs
    pic_cmd_out 1, 0x11
    pic_cmd_out 2, 0x11
    ; Set the interrupt vector offsets.
    pic_data_out 1, [esp+4]
    pic_data_out 2, [esp+8]
    ; Set the identity of PIC2 on PIC1
    pic_data_out 1, 4
    ; Set PIC2's identity
    pic_data_out 2, 2
    
    ; Set the mode (8086)
    pic_data_out 1, 0x01
    pic_data_out 2, 0x01
    
    ; Restore saved masks
    mov ax, cx
    xchg al, ah
    out pic_data(1)+1, al
    shr al, 8
    out pic_data(2)+1, al
    
    ; Delay...
    call nop_call
    ret

global OS216_Disable8259Pic
OS216_Disable8259Pic:
    mov al,0xFF
    out pic_data(1)+1, al
    out pic_data(2)+1, al
    call nop_call
    ret
