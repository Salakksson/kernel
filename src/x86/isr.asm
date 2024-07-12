bits 64

section .text

%macro ISR_NOERROR 1 
global isr%1:
isr%1:
    push 0
    push %1
    jmp _isr_main

%endmacro

%macro ISR_ERROR 1 
global isr%1:
isr%1:
    push %1
    jmp _isr_main

%endmacro

%include "src/x86/isr.inc"

%macro pushall 0
    push rax  
    push rbx  
    push rcx  
    push rdx  
    push rsi  
    push rdi  
    push rbp  
    push r8   
    push r9   
    push r10  
    push r11  
    push r12  
    push r13  
    push r14  
    push r15  
%endmacro

%macro popall 0 
    pop r15  
    pop r14  
    pop r13  
    pop r12  
    pop r11  
    pop r10  
    pop r9   
    pop r8   
    pop rbp  
    pop rdi  
    pop rsi  
    pop rdx  
    pop rcx  
    pop rbx  
    pop rax  
%endmacro

extern global_isr_handler

_isr_main:
    
    ; Macro to push all the general purpose registers
    pushall
    
    xor rax, rax
    mov ax, ds
    push rax
    
    ; Set segments to 1 (kernel)
    mov ax, 1
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov rdi, rsp
    call global_isr_handler
    
    pop rax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popall
    add rsp, 16 ; Remove error code and interrupt number from stack
    iretq



