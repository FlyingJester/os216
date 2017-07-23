
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

section .text
align 4

nop_call:
    times 64 nop
    ret

global OS216_Setup8259Pic
OS216_Setup8259Pic:
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
    
    ; Restore saved masks
    mov ax, cx
    out 0xA1, al
    shr al, 8
    out 0x21, al
    
    ; Delay...
    call nop_call
    pop ecx
    ret

global OS216_Disable8259Pic
OS216_Disable8259Pic:
    mov al,0xFF
    out pic_data(1)+1, al
    out pic_data(2)+1, al
    call nop_call
    ret
