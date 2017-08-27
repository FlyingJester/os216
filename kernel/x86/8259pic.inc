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

; PIC1 is 0x20, PIC2 is 0xA0.
; This makes 1 = 0x20 and 2 = 0xA0
%define pic_cmd(N) (0x20 + ((0xA0 - 0x20)*( N - 1 )))
%define pic_data(N) (pic_cmd(N)+1)

%macro pic_cmd_out 2
    mov al, BYTE %2
    out pic_cmd( %1 ), al
    call nop_call
%endmacro

%macro pic_data_out 2
    mov al, BYTE %2
    out pic_data( %1 )+1, al
    call nop_call
%endmacro

%macro pic_set_mask_irq 1
%if %1 < 8
    in al, pic_data(1)
    or al, 1 << %1
    out pic_data(1), al
%else
    in al, pic_data(2)
    or al, 1 << ( %1 - 8 )
    out pic_data(2), al
%endif
%endmacro

%macro pic_clear_mask_irq 1
%if %1 < 8
    in al, pic_data(1)
    or al, ~(1 << %1)
    out pic_data(1), al
%else
    in al, pic_data(2)
    or al, ~(1 << ( %1 - 8 ))
    out pic_data(2), al
%endif
%endmacro
