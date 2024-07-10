section .multiboot_header
header_start:
    
magic_num:      dd 0xe85250d6; multiboot2
arch:           dd 0
header_length:  dd header_end - header_start

checksum:       dd -(0xe85250d6 + 0 + (header_end - header_start))

end_tag:    dw 0
            dw 0
            dd 8
header_end:
