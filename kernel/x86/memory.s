
TSS_LEN equ 4096
PAGE_SIZE equ 4096

section .text
align 4

extern OS216_LockRegionAllocator
extern OS216_UnlockRegionAllocator
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

global OS216_VM_Enable
OS216_VM_Enable:
    mov eax, cr0
    or eax, 0x80000001
    mov cr0, eax
    ret

global OS216_VM_GetPageSize
OS216_VM_GetPageSize:
    mov eax, PAGE_SIZE
    ret

global OS216_VM_CreateNewVMDirectory
OS216_VM_CreateNewVMDirectory:
    ; Get a physical page to put the directory into.
    push edi
    push DWORD 0
    push PAGE_SIZE
    
    call OS216_LockRegionAllocator
    
    cmp DWORD [os216_identity_memory_map], 0
    jne os216_identity_memory_map_ready
    
    call OS216_AllocateRegion
    mov eax, [eax]
    mov [os216_identity_memory_map], eax
    
    mov ecx, 3
    xor edi, edi
os216_fill_table_iter:
    mov DWORD [eax+(edi*4)], ecx
    add ecx, 1<<12
    inc edi
    cmp edi, 1024
    jl os216_fill_table_iter

os216_identity_memory_map_ready:
    call OS216_AllocateRegion
    
    ; [eax] is the address, [eax+4] is the size (unneeded)
    ; Set up the directory to be empty except for the last table (which points
    ; to the directory again).
    ;                              GSADWURP
    ; 0b00000000,00000000,00000000,00000000
    mov eax, [eax]
    push eax
    
    call OS216_UnlockRegionAllocator
    
    ; If paging is set up, we need to map the page directory into the current address space. The
    ; second to last table in the directory is reserved for this.
    mov edi, eax
    mov eax, cr0
    mov ecx, eax
    or ecx, 0x80000001
    cmp ecx, eax
    jne os216_paging_is_not_setup
    ; Map the new page directory into the 1022nd page table in the current directory, and then put
    ; that address into edi.
    or edi, 3
    mov [0xFFFFFFF7], edi
    
    mov edi, 0xFFFFE000
    
os216_paging_is_not_setup:
    mov ecx, 1024
    
    mov eax, 0
    rep stosd
    
    pop eax
    ; Set up identity mapping for the kernel and the lower memory map.
    mov ecx, [os216_identity_memory_map]
    mov DWORD [eax], ecx
    or  DWORD [eax], 3
    ; Set the last entry to be the table itself.
    mov DWORD [eax+PAGE_SIZE-4], eax
    or  DWORD [eax+PAGE_SIZE-4], 3
    
    add esp, 8
    pop edi
    ret

global OS216_VM_DestroyVMDirectory
OS216_VM_DestroyVMDirectory:
    call OS216_LockRegionAllocator
    call OS216_FreeRegion
    jmp OS216_UnlockRegionAllocator

; void OS216_SetVMDirectory(struct OS216_VMDirectory *);
global OS216_VM_SetVMDirectory
OS216_VM_SetVMDirectory:
    mov eax, [esp+4]
    mov cr3, eax
    ret

global OS216_VM_GetMappableStart
OS216_VM_GetMappableStart:
    mov eax, 4190208
    ret

global OS216_VM_Initialize
OS216_VM_Initialize:
    call OS216_VM_CreateNewVMDirectory
    push eax
    call OS216_VM_SetVMDirectory
    call OS216_VM_Enable
    add esp, 4
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

global os216_identity_memory_map
os216_identity_memory_map: dw 0
