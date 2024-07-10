c-src := $(shell find src/kernel -name *.c)
c-obj := $(patsubst src/kernel/%.c, bin/kernel/%.c.o, $(c-src))

x86-asm-src := $(shell find src/x86 -name *.asm)
x86-asm-obj := $(patsubst src/x86/%.asm, bin/x86/%.asm.o, $(x86-asm-src))

$(x86-asm-obj): bin/x86/%.asm.o: src/x86/%.asm
	@mkdir -p $(dir $@)
	nasm -f elf64 $< -o $@

$(c-obj): bin/kernel/%.c.o: src/kernel/%.c
	@mkdir -p $(dir $@)
	gcc -c -ffreestanding $< -o $@

.PHONY: build-x86
build-x86: $(x86-asm-obj) $(c-obj)
	ld -n -o dist/iso/boot/kernel.bin -T dist/linker.ld $(x86-asm-obj) $(c-obj)
	@rm -f dist/kernel.iso
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/kernel.iso dist/iso
