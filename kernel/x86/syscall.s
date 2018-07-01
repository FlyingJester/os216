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

NUM_SYSCALLS equ 4

extern OS216_Fatal
extern OS216_SysCall
;6949647
ud2_test:
    ud2

global OS216_Int_Syscall
OS216_Int_Syscall:
    push edx
    push ecx
    mov edx, [esp+8]; EAX has the old EIP
    mov cx, [ud2_test]
    cmp WORD [edx], cx ; Check if it's UD2
    jne not_ud2
    
    ; Push ebx and eax as well
    push ebx
    push eax
    call OS216_SysCall
    
    add esp, 16
    iret

OS216_Int_SyscallX:
    push eax
    push ebx
    mov eax, [esp+8]; EAX has the old EIP
    mov bx, [ud2_test]
    cmp WORD [eax], bx ; Check if it's UD2
    jne not_ud2
    cld
    ; EAX was already pushed.
    mov eax, [esp]
    cmp eax, NUM_SYSCALLS
    jle syscall_0_args
    
    movzx eax, BYTE [num_syscall_args+eax]
    cmp eax, 1
    jl syscall_0_args
    je syscall_1_args
    
    cmp eax, 3
    jl syscall_2_args
    je syscall_3_args

not_ud2:
    pushad
    push invalid_opcode_string
    push syscall_name
    push DWORD [eax]
    push file_name
    call OS216_Fatal
    add esp, 16
    popad
    pop eax
    pop ebx
    iret

syscall_0_args:
    pushad
    push eax
    call OS216_SysCall
    add esp, 4
    popad
    pop eax
    pop ebx
    iret
    
syscall_1_args:
    pushad
    push ebx
    push eax
    call OS216_SysCall
    add esp, 8
    popad
    pop eax
    pop ebx
    iret

syscall_2_args:
    pushad
    push ecx
    push ebx
    push eax
    call OS216_SysCall
    add esp, 12
    popad
    pop eax
    pop ebx
    iret
    
syscall_3_args:
    pushad
    push edx
    push ecx
    push ebx
    push eax
    call OS216_SysCall
    add esp, 16
    popad
    pop eax
    pop ebx
    iret

section .data
align 4

num_syscall_args:
    db 0,1,3,0

invalid_opcode_string:
    db 'Invalid Opcode', 0
file_name:
    db 'syscall.s',0
syscall_name:
    db  'OS216_Int_Syscall',0