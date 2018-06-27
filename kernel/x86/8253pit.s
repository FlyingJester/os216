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

global OS216_SetTimerSpeed
OS216_SetTimerSpeed:
    
    ; Writing 52 port 0x43 sets channel 0 to mode 2 (frequency generator) and
    ; sets up port 0x40 to accept two consecutive bytes (via two consecutive
    ; writes, low then high).
    mov al, 52
    out 0x43, al
    
    ; Frequency = (1193182 / register) Hertz
    ; For instance to get a frequency of 0xFF Hertz, we must write 0x123A
    ; To determine the value to write, we must divide 1193182 by eax, and then
    ; write this value out to port 0x40 bytewise.
    
    push ecx
    push edx
    
    mov ecx, [esp + 12]
    
    mov dx, WORD (1193182 >> 16)
    mov ax, WORD (1193182 & 0xFFFF)
    div cx
    
    pop edx
    pop ecx
    
    ; Using just the floor of the division is fine, since the frequency is
    ; rounded up as 1193182 anyway.
    out 0x40, al
    
    shr ax, 8
    out 0x40, al
    
    ret

global OS216_SetTimerInterrupt
OS216_SetTimerInterrupt:
    mov eax, [esp + 4]
    mov [OS216_TimerInterruptCallback], eax
    ret

section .data
align 4
    global OS216_TimerInterruptCallback
    OS216_TimerInterruptCallback: resb 4
