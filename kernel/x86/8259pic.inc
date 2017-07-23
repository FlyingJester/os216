
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
