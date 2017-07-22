section .text
align 4

NUM_SYSCALLS equ 3

extern OS216_Fatal
extern OS216_SysCall
;6949647
ud2_test:
    ud2

global OS216_Int_Syscall
OS216_Int_Syscall:
    push eax
    push ebx
    mov eax, [esp+8]; EAX has the old EIP
    mov bx, [ud2_test]
    cmp WORD [eax], bx ; Check if it's UD2
    jne not_ud2
    cld
    ; EAX was already pushed.
    mov eax, [esp]
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
    db 0,1,3

invalid_opcode_string:
    db 'Invalid Opcode', 0
file_name:
    db 'syscall.s',0
syscall_name:
    db  'OS216_Int_Syscall',0