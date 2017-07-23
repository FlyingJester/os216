
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
