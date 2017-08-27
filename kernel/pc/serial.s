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

section .text
align 4

global OS216_Serial_Init
OS216_Serial_Init:
    xor edx, edx
    xor eax, eax
    mov [os216_serial_lock], DWORD 0
    
    ; Disable serial interrupts
    mov dx, 0x03F8
    out dx, al
    
    
    ; Set the baud rate:
    
    ; Set divisor latch
    mov dx, 0x03F8 + 3
    in al, dx
    ; Store the original value of the control register in cx
    mov cx, ax
    or al, 0x80
    out dx, al
    
    ; Set the divisor value.
    mov al, 2
    mov dx, 0x03F8
    out dx, al

    inc dx
    mov al, 0
    out dx, al
    
    ; Clear the divisor latch by restoring the original value.
    mov ax, cx
    mov dx, 0x03F8 + 3
    ; While we are modifying the control register, set the data bits,
    ; stop bits, and parity. We use 8 data bits, 1 stop bits, and even parity.
    
    ; The two least significan bits set the length (0=5, 1=6, 2=7, 3=8)
    ; The third least significant bit is the stop enable bit
    ; The 4-6 bits are the parity setting. 3 (0b011) is even parity.
    or al, 0x1F
    out dx, al
    ret

global OS216_Serial_PutString
OS216_Serial_PutString:
    ; Lock the serial lock
    push edi
    push esi
;    mov edi, os216_serial_lock 
;    mov ecx, 1
;serial_write_lock_try:
;    xor eax, eax
;    cmpxchg [edi], ecx
;    jnz serial_write_lock_try
    
    ; Wait until the transfer buffer is empty
    mov dx, 0x03F8 + 5
serial_wait_for_transfer:
    in al, dx
    test al, 0x20
    jz serial_wait_for_transfer
    
    ; Write the string out.
    mov esi, [esp+16]
    mov ecx, [esp+12]
    
    mov dx, 0x03F8
    
    rep outsb
    
serial_write_end:
;    ; Release the serial lock
;    mov [edi], DWORD 0
    pop esi
    pop edi
    ret

section .bss
align 4
    
    os216_serial_lock: resd 1
