
TSS_LEN equ 4096
PAGE_SIZE equ 4096

section .text
align 4

extern OS216_AllocateRegion
extern OS216_FreeRegion

struc OS216_GDTEntry
    gdt_entry_limit resb 2
    gdt_entry_base  resb 3
    gdt_entry_access resb 1
    gdt_entry_limit_flags resb 1
    gdt_entry_base_end resb 1
endstruc

%macro os216_gdt_large_entry 3 ; base, limit, type
    istruc OS216_GDTEntry
        at gdt_entry_limit, db ( (%2>>12) & 0xFF), (( (%2>>12) >> 8 ) & 0xFF)
        at gdt_entry_base, db ( %1 & 0xFF), (( %1 >> 8 ) & 0xFF), (( %1 >> 16 ) & 0xFF)
        at gdt_entry_access, db %3
        at gdt_entry_limit_flags, db 0xC0 | (( (%2>>12) >> 16) & 0x0F) ; 0xC0 is for large segments
        at gdt_entry_base_end, db (( %1 >> 24) & 0xFF)
    iend
%endmacro

global OS216_InitSegmentation
OS216_InitSegmentation:
    pushf
    cli
    ; Setup the TSS entry of the GDT
    mov eax, os216_start_tss
    mov word [os216_tss_descriptor+gdt_entry_base], ax
    shr eax, 16
    mov byte [os216_tss_descriptor+gdt_entry_base+2], al
    shr eax, 24
    mov byte [os216_tss_descriptor+gdt_entry_base_end], al
    
    ; Set the GDT
    mov eax, os216_gdt_table
    mov [os216_gdt+2], eax
    mov word [os216_gdt], OS216_GDTEntry_size * 4
    
    ; Load the new GDT
    lgdt [os216_gdt]
    
    mov eax, cr0
    or eax, DWORD 0x01
    mov cr0, eax
    
    ; Force all segments to be reloaded immediately.
    xor eax, eax
    jmp 0x10:reload_code_segment
    reload_code_segment:
    mov ax, 0x08
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    
    mov ax, 0x18
    ltr ax
    popf
    ret

global OS216_GetPageSize
OS216_GetPageSize:
    mov eax, PAGE_SIZE
    ret

; struct OS216_VMDirectory *OS216_CreateNewVMDirectory(void);
global OS216_CreateNewVMDirectory
OS216_CreateNewVMDirectory:
    ; Get a physical page to put the directory into.
    push edi
    push DWORD 0
    push PAGE_SIZE
    call OS216_AllocateRegion
    
    ; [eax] is the address, [eax+4] is the size (unneeded)
    ; Set up the directory to be empty except for the last table (which points
    ; to the directory again).
    ;                              GSADWURP
    ; 0b00000000,00000000,00000000,00000000
    push eax
    mov edi, eax
    mov ecx, 1023
    
    mov eax, 0
    rep stosd
    
    ; Set the last entry to be the table itself.
    pop eax
    mov [eax+PAGE_SIZE-4], eax
    
    add esp, 8
    pop edi
    ret

global OS216_DestroyVMDirectory
OS216_DestroyVMDirectory:
    jmp OS216_FreeRegion

; void OS216_SetVMDirectory(struct OS216_VMDirectory *);
global OS216_SetVMDirectory
OS216_SetVMDirectory:

global OS216_GetMappableStart
OS216_GetMappableStart:
    mov eax, os216_memory_end
    ret

section .data
align 4

; The GDT will contain four entries. The first is unusable and must be zeroed.
; The second and third will be our data and code, the fourth is the TLR.
; Data and code are base 0, limit 0xFFFFFFFF
; TSS is type 0x89, and uses the TSS memory arena
os216_gdt_table:
    times OS216_GDTEntry_size db 0 ; Zeroed out first entry
    os216_gdt_large_entry 0, 0xFFFFFFFF, 0x92
    os216_gdt_large_entry 0, 0xFFFFFFFF, 0x9A
os216_tss_descriptor:
    ; TSS, will be fully filled out later
    istruc OS216_GDTEntry
        at gdt_entry_limit, dw TSS_LEN
        at gdt_entry_base, db 0, 0, 0
        at gdt_entry_access, db 0x89
        at gdt_entry_limit_flags, db 0x40 ; 0x40 is for small segments
        at gdt_entry_base_end, db 0
    iend
db 0

section .bss
align 4

os216_gdt:
    dw 0
    dd 0

; TSS area
os216_start_tss:
times TSS_LEN db 0

section .ending
    os216_memory_end: dd 1
