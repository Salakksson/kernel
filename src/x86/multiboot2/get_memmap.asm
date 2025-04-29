; bits 32
; section .text
;
; global get_memmap
; get_memmap:
;     cli
;     
;     sgdt [old_gdt]
;
;     mov eax, cr0
;     and eax, 0x7fffffff
;     mov cr0, eax
;     
;     lgdt [gdt_real]
;
;     mov eax, 0x10
;     mov ds, ax
;     mov es, ax
;     mov fs, ax
;     mov gs, ax
;     mov ss, ax
;
;     jmp 0x08:call_bios
;
; .return:
;     lgdt [old_gdt]
;
; bits 16
; section .text
;
; call_bios:
;     mov ax, 0
;     mov ds, ax
;     mov es, ax
;     mov fs, ax
;     mov gs, ax
;     mov ss, ax
;     mov sp, 0x7c00
;
;     
;
;     mov eax, cr0
;     or eax, 0x1
;     mov cr0, eax
;     jmp 0x08:get_memmap.return
;
; section .data
; align 8
;
; old_gdt: dd 0; allocate 32bits for the old gdt pointer
;
; gdt_real:
;     dw 0xFFFF               ; Limit
;     dw 0x0000               ; Base Low
;     db 0x00                 ; Base Middle
;     db 0x9A                 ; Access
;     db 0xCF                 ; Granularity
;     db 0x00                 ; Base High
;
;     dw 0xFFFF               ; Limit
;     dw 0x0000               ; Base Low
;     db 0x00                 ; Base Middle
;     db 0x92                 ; Access
;     db 0xCF                 ; Granularity
;     db 0x00                 ; Base High
;
; section .bss
; global memmap_ptr:
; memmap_ptr:
;     resb 8
