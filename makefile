c-src := $(shell find src/kernel -name *.c)
c-obj := $(patsubst src/kernel/%.c, bin/kernel/%.c.o, $(c-src))

x86-32-c-src := $(shell find src/x86 -name *.c)
x86-32-c-obj := $(patsubst src/x86/%.c, bin/x86/%.c.o, $(x86-32-c-src))

x86-asm-src := $(shell find src/x86 -name *.asm)
x86-asm-obj := $(patsubst src/x86/%.asm, bin/x86/%.asm.o, $(x86-asm-src))

cflags = -mno-sse -mno-sse2 -mno-mmx -mno-80387 -mno-red-zone -m64 -mabi=sysv -ffreestanding -fno-stack-protector
cflags += -Wall -O3
ldflags = -n -T dist/linker.ld

src/kernel/incl/pch.h.gch: src/kernel/incl/pch.h
	gcc -xc-header -ffreestanding $< -o $@

$(x86-asm-obj): bin/x86/%.asm.o: src/x86/%.asm
	@mkdir -p $(dir $@)
	nasm -f elf64 $< -o $@

$(x86-32-c-obj): bin/x86/%.c.o: src/x86/%.c
	@mkdir -p $(dir $@)
	gcc -c -m32 -ffreestanding $< -o $@

$(c-obj): bin/kernel/%.c.o: src/kernel/%.c src/kernel/incl/pch.h.gch
	@mkdir -p $(dir $@)
	gcc -c $(cflags) $< -o $@

.PHONY: build clean
build: $(x86-asm-obj) $(c-obj)
    # echo $(c-src) ::: $(c-obj)
	ld $(ldflags) -o dist/iso/boot/kernel.bin $(x86-asm-obj) $(c-obj)
	@rm -f dist/kernel.iso
	@grub-mkrescue /usr/lib/grub/i386-pc -o dist/kernel.iso dist/iso > /dev/null 2>&1


clean:
	rm -r ./bin/*

