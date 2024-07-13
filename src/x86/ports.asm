
section .text
bits 64
    
global outb
outb:
mov dx, di
mov ax, si
out dx, al
ret


global inb
inb:
mov dx, di
in al, dx
movzx rax, al
ret
    
