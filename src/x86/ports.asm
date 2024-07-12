
section .text
bits 64
    
global port_outb
port_outb:
mov dx, di
mov ax, si
out dx, al
ret


global port_inb
port_inb:
mov dx, di
in al, dx
movzx rax, al
ret
    
