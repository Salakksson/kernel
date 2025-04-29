global start
extern long_mode_start
extern get_memmap

section .text
bits 32

start:
	mov esp, stack_top
    
    mov [multiboot_info], ebx   ; Keep multiboot struct

	call check_multiboot
	call check_cpuid
	call check_long_mode
    
	call setup_page_tables
	call enable_paging
    
    push dword 0
    push dword [multiboot_info] ; Will be passed to kernel_main()
    
	lgdt [gdt64.descriptor]
	jmp gdt64.code_segment:long_mode_start

.halt:
    hlt
	jmp .halt

setup_page_tables:
	mov eax, page_table_l3
	or eax, 0b11; present, writable
	mov [page_table_l4], eax

	mov eax, page_table_l2
	or eax, 0b11; present, writable
	mov [page_table_l3], eax

	mov ecx, 0

.loop:
	mov eax, 0x200000
	mul ecx
	or eax, 0b10000011
	mov [page_table_l2 + ecx * 8], eax

	inc ecx
	cmp ecx, 512
	jne .loop
	
	ret

enable_paging:
	mov eax, page_table_l4
	mov cr3, eax

	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax
	
	mov ecx, 0xc0000080
	rdmsr
	or eax, 1 << 8
	wrmsr
	
	mov eax, cr0
	or eax, 1 << 31
	mov cr0, eax
	ret

check_multiboot:
	cmp eax, 0x36d76289
	jne .fail
	ret
.fail:
	mov al, 'M'
	jmp error

check_cpuid:
	pushfd
	pop eax
	mov ecx, eax
	xor eax, 1 << 21 ; CPUID bit
	push eax
	popfd
	pushfd
	pop eax
	push ecx
	popfd
	cmp eax, ecx
je .fail
	ret
.fail:
	mov al, 'C'
	jmp error

check_long_mode:
	mov eax, 0x80000000
	cpuid ; If this returns a larger number then we procede
	cmp eax, 0x80000001
	jb .fail
	
	mov eax, 0x80000001
	cpuid
	test edx, 1 << 29
	jz .fail
	ret
.fail:
	mov al, 'L'
	jmp error

error:
	mov dword [0xb8000], 0x4f524f45
	mov dword [0xb8004], 0x4f3a4f52
	mov dword [0xb8008], 0x4f204f20
	mov byte  [0xb800a], al
	hlt

section .bss
align 0x1000
    

page_table_l4:
	resb 0x1000
page_table_l3:
	resb 0x1000
page_table_l2:
	resb 0x1000

stack_bottom:
	resb 0x4000
stack_top:

multiboot_info:
    resb 8

section .rodata

gdt64:
	dq 0
.code_segment: equ $ - gdt64
	dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53) 
.descriptor:
	dw $ - gdt64 - 1
	dq gdt64

