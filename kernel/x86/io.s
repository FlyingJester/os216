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

global OS216_IOOut
OS216_IOOut:
    cmp [esp+12], DWORD 2
    jl OS216_IOOut8
    jg OS216_IOOut32
    ; fallthrough

global OS216_IOOut16
OS216_IOOut16:
    mov eax, [esp+4]
    mov edx, [esp+8]
    out dx, ax
    ret

global OS216_IOOut8
OS216_IOOut8:
    mov eax, [esp+4]
    mov edx, [esp+8]
    out dx, al
    ret

global OS216_IOOut32
OS216_IOOut32:
    mov eax, [esp+4]
    mov edx, [esp+8]
os216_io_out_32:
    out dx, eax
    ret

global OS216_IOIn
OS216_IOIn:
    cmp [esp+8], DWORD 2
    jl OS216_IOIn8
    jg OS216_IOIn32
    ; fallthrough

global OS216_IOIn16
OS216_IOIn16:
    mov edx, [esp+4]
    xor eax, eax
    in ax, dx
    ret

global OS216_IOIn8
OS216_IOIn8:
    mov edx, [esp+4]
    xor eax, eax
    in al, dx
    ret

global OS216_IOIn32
OS216_IOIn32:
    mov edx, [esp+4]
    in eax, dx
    ret
