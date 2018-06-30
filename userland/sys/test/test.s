; Any copyright of this file is dedicated to the Public Domain.
; http://creativecommons.org/publicdomain/zero/1.0/

section .text
align 4

; Call the NOP syscall over and over again.
global start
start:
    mov eax, 0
    ;ud2
    jmp start
