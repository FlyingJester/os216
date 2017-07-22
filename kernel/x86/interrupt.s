
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

section .text
align 4

extern OS216_Fatal
extern OS216_SysCall
extern OS216_Int_Syscall
extern OS216_Setup8259Pic
extern OS216_Disable8259Pic

; There are 32 exceptions. Each one has its own function here.
OS216_Int_DivideByZero:
    dummy_int div_by_zero_name

OS216_Int_NMI:
    dummy_int nmi_name

OS216_Int_Break:
    dummy_int break_name

OS216_Int_Overflow:
    dummy_int into_name

OS216_Int_Bounds:
    dummy_int bounds_name

OS216_Int_DevNotReady:
    dummy_int dev_not_ready_name

OS216_Int_DoubleFault:
    dummy_int double_fault_name

OS216_Int_Coprocessor:
    dummy_int coprocessor_name

OS216_Int_BadTSS:
    dummy_int bad_tss_name
    
OS216_Int_BadSegment:
    dummy_int bad_segment_name

OS216_Int_StackFault:
    dummy_int stack_fault_name

OS216_Int_GPFault:
    pop eax
    pop eax
    push null_term
    push seg_fault_name
    push DWORD [eax]
    push file_name
    call OS216_Fatal

OS216_Int_PageFault:
    

OS216_Int_FPU:
    dummy_int fpu_name

OS216_Int_Alignment:
    dummy_int align_name

OS216_Int_MachineCheck:
    dummy_int machine_check_name

OS216_Int_SSE:
    dummy_int sse_name
    
OS216_Int_Virtualization:
    dummy_int virtualization_name

global OS216_InitInterrupts
OS216_InitInterrupts:
    ; Begin setting up the divide by zero interrupt
    mov eax, OS216_IDT
    ; Setup the offset.
    
    os216_setup_interrupt OS216_Int_DivideByZero, 0x8F, 0
    ; Reserved
    os216_setup_interrupt OS216_Int_NMI, 0x8F, 2
    os216_setup_interrupt OS216_Int_Break, 0x8F, 3
    os216_setup_interrupt OS216_Int_Overflow, 0x8F, 4
    os216_setup_interrupt OS216_Int_Bounds, 0x8F, 5
    os216_setup_interrupt OS216_Int_Syscall, 0x8F, 6
    os216_setup_interrupt OS216_Int_DevNotReady, 0x8F, 7
    os216_setup_interrupt OS216_Int_DoubleFault, 0x8F, 8
    os216_setup_interrupt OS216_Int_Coprocessor, 0x8F, 9
    os216_setup_interrupt OS216_Int_BadTSS, 0x8F, 10
    os216_setup_interrupt OS216_Int_BadSegment, 0x8F, 11
    os216_setup_interrupt OS216_Int_StackFault, 0x8F, 12
    os216_setup_interrupt OS216_Int_GPFault, 0x8F, 13
    os216_setup_interrupt OS216_Int_PageFault, 0x8F, 14
    ; Reserved
    os216_setup_interrupt OS216_Int_FPU, 0x8F, 16
    os216_setup_interrupt OS216_Int_Alignment, 0x8F, 17
    os216_setup_interrupt OS216_Int_MachineCheck, 0x8F, 18
    os216_setup_interrupt OS216_Int_SSE, 0x8F, 19
    os216_setup_interrupt OS216_Int_Virtualization, 0x8F, 20
    
NUM_SET_INTERRUPTS equ 21

    add eax, OS216_IDTEntry_size * NUM_SET_INTERRUPTS
    
;%rep 256-NUM_SET_INTERRUPTS
;    mov WORD [eax+idt_selector], 0x10 ; Put the code segment into the selector for the ISR
;    add eax, OS216_IDTEntry_size
;%endrep
    
    mov WORD [OS216_IDTInfo], OS216_IDTEntry_size*NUM_SET_INTERRUPTS
    mov DWORD [OS216_IDTInfo+2], OS216_IDT
    lidt [OS216_IDTInfo]
    
    ; We always need to set up the IRQ vectors, even with an APIC
    call OS216_Setup8259Pic
    
    ; Check for an APIC
    mov eax, 1
    push ebx
    cpuid
    pop ebx
    bt edx, 9
    jc has_apic
    
    ; Now that the interrupt controller is properly configured, we can enable interrupts.
    sti
    ret
    
has_apic:
    ; Not supported yet....
    ; call OS216_Disable8259Pic
    ; call OS216_EnableApic
    ; Now that the interrupt controller is properly configured, we can enable interrupts.
    sti
    ret

section .data
align 1
file_name:
    db 'interrupt.s',0
div_by_zero_name:
    db 'OS216_Int_DivideByZero', 0
nmi_name:
    db 'OS216_Int_NMI', 0
break_name:
    db 'OS216_Int_Break', 0
into_name:
    db 'OS216_Int_Overflow', 0
bounds_name:
    db 'OS216_Int_Bounds', 0
dev_not_ready_name:
    db 'OS216_Int_DevNotReady', 0
double_fault_name:
    db 'OS216_Int_DoubleFault', 0
coprocessor_name:
    db 'OS216_Int_Coprocessor', 0
bad_tss_name:
    db 'OS216_Int_BadTSS', 0
bad_segment_name:
    db 'OS216_Int_BadSegment', 0
stack_fault_name:
    db 'OS216_Int_StackFault', 0
seg_fault_name:
    db 'OS216_Int_GPFault', 0
page_fault_name:
    db 'OS216_Int_PageFault', 0
fpu_name:
    db 'OS216_Int_FPU', 0
align_name:
    db 'OS216_Int_Alignment', 0
machine_check_name:
    db 'OS216_Int_MachineCheck', 0
sse_name:
    db 'OS216_Int_SSE', 0
virtualization_name:
    db 'OS216_Int_Virtualization', 0

section .bss
align 4

null_term:
    resb 0

OS216_IDTInfo:
    resb 6

OS216_IDT:
    times 256 resb OS216_IDTEntry_size
