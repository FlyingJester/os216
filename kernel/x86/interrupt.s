;  Copyright (c) 2017-2018 Martin McDonough.  All rights reserved.
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

%include "interrupt.inc"

section .text
align 4

extern OS216_Fatal
extern OS216_SysCall
extern OS216_Int_Syscall
extern OS216_Setup8259Pic
extern OS216_Disable8259Pic
extern OS216_CallDriverAtInterrupt
extern OS216_TimerInterruptCallback

OS216_Int_Timer:
    cli
    pushf
    push eax
    mov eax, [OS216_TimerInterruptCallback]
    cmp eax, 0
    jz no_callback
    
    pushad
    push esp
    call eax
    pop esp
    popad
    
no_callback:
    pop eax
    popf
    
    ; Send the End Of Interrupt command to the PIC
    mov al, 0x20
    out 0x20, al
    sti
    iret

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
    add esp, 4
    pop eax
    push null_term
    push seg_fault_name
    push DWORD [eax]
    push file_name
    call OS216_Fatal

OS216_Int_PageFault:
    dummy_int page_fault_name

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
    
    push ebx
    ; We always need to set up the IRQ vectors, even with an APIC
    call OS216_Setup8259Pic
    
    ; Begin setting up the divide by zero interrupt
    mov eax, OS216_IDT
    ; Setup the offset.
    
    os216_setup_interrupt OS216_Int_DivideByZero, 0x8E, 0
    ; Reserved
    os216_setup_interrupt OS216_Int_NMI, 0x8E, 2
    os216_setup_interrupt OS216_Int_Break, 0x8E, 3
    os216_setup_interrupt OS216_Int_Overflow, 0x8E, 4
    os216_setup_interrupt OS216_Int_Bounds, 0x8E, 5
    os216_setup_interrupt OS216_Int_Syscall, 0x8E, 6
    os216_setup_interrupt OS216_Int_DevNotReady, 0x8E, 7
    os216_setup_interrupt OS216_Int_DoubleFault, 0x8E, 8
    os216_setup_interrupt OS216_Int_Coprocessor, 0x8E, 9
    os216_setup_interrupt OS216_Int_BadTSS, 0x8E, 10
    os216_setup_interrupt OS216_Int_BadSegment, 0x8E, 11
    os216_setup_interrupt OS216_Int_StackFault, 0x8E, 12
    os216_setup_interrupt OS216_Int_GPFault, 0x8E, 13
    os216_setup_interrupt OS216_Int_PageFault, 0x8E, 14
    ; Reserved
    os216_setup_interrupt OS216_Int_FPU, 0x8E, 16
    os216_setup_interrupt OS216_Int_Alignment, 0x8E, 17
    os216_setup_interrupt OS216_Int_MachineCheck, 0x8E, 18
    os216_setup_interrupt OS216_Int_SSE, 0x8E, 19
    os216_setup_interrupt OS216_Int_Virtualization, 0x8E, 20
    
    ; IRQs
    os216_setup_interrupt OS216_Int_Timer, 0x8F, 0x20
    
NUM_SET_INTERRUPTS equ 0x30

    mov ax, OS216_IDTEntry_size * NUM_SET_INTERRUPTS
    
    mov WORD [OS216_IDTInfo], ax
    mov DWORD [OS216_IDTInfo+2], OS216_IDT
    lidt [OS216_IDTInfo]
    
    pop ebx
    
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

driver_interrupt_vector_drivers:
    resd 16

null_term:
    resb 0

OS216_IDTInfo:
    resb 6

OS216_IDT:
    times 256 resb OS216_IDTEntry_size
