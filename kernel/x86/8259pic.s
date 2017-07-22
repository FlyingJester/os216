
; PIC1 is 0x20, PIC2 is 0xA0.
; This makes 1 = 0x20 and 2 = 0xA0
%define pic_base(N) (0x20 + ((0xA0 - 0x20)*( N - 1 )))

%macro pic_cmd_out 2
    mov al, BYTE %2
    out pic_base( %1 ), al
    call nop_call
%endmacro

%macro pic_data_out 2
    mov al, BYTE %2
    out pic_base( %1 )+1, al
    call nop_call
%endmacro

section .text
align 4

nop_call:
    times 64 nop
    ret

global OS216_Enable8259Pic
OS216_Enable8259Pic:
    push ecx
    
    ; Save the PIC masks
    in al, 0x21
    shl ax, 8
    in al, 0xA1
    mov cx, ax
    
    ; Delay...
    call nop_call
    
    ; Send init sequence to the PICs
    pic_cmd_out 1, 0x11
    pic_cmd_out 2, 0x11
    ; Set the interrupt vector offsets.
    pic_data_out 1, 32
    pic_data_out 2, 40
    ; Set the identity of PIC2 on PIC1
    pic_data_out 1, 4
    ; Set PIC2's identity
    pic_data_out 2, 2
    
    ; Set the mode (8086)
    pic_data_out 1, 0x01
    pic_data_out 2, 0x01
    ; Resture saved masks
    mov ax, cx
    out 0xA1, al
    shr al, 8
    out 0x21, al
    
    ; Delay...
    call nop_call
    pop ecx
    ret
