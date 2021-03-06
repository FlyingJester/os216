;  Copyright (c) 2017-2018 Martin McDonough.  All rights reserved.
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

section .text
align 4

global OS216_Setup8259Pic
OS216_Setup8259Pic:
    
    ; Send init sequence to the PICs
    mov al, 0x11
    out 0x20, al
    out 0xA0, al
    
    times 8 nop
    
    ; Set the interrupt vector offsets
    mov al, 0x20
    out 0x21, al
    mov al, 0x28
    out 0xA1, al
    
    times 8 nop
    
    ; Set the identity of PIC2 on PIC1
    mov al, 4
    out 0x21, al
    mov al, 2
    out 0xA1, al
    
    times 8 nop
    
    ; Set the mode (8086)
    mov al, 1
    out 0x21, al
    out 0xA1, al
    
    times 8 nop
    
    ; Unmask all interrupts
    mov al, 0
    out 0x21, al
    out 0xA1, al
    
    times 8 nop
    
    ret

global OS216_Disable8259Pic
OS216_Disable8259Pic:
    ; "Disable" by masking all interrupts.
    mov al, 0xFF
    out 0x21, al
    out 0xA1, al
    
    times 8 nop
    
    ret
