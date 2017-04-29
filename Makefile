# Makefile for XinOS

CFLAGS=-Wall -m32
HEADER=-Iinclude

xinos.iso: root/boot/kernel
	grub-mkrescue root/ -o $@

root/boot/kernel: obj/kernel.elf obj/main.o obj/screen.o
	ld -m elf_i386 -T source/link.ld $? -o $@

obj/kernel.elf: source/kernel.asm
	nasm -f elf32 $< -o $@

obj/%.o: source/%.c
	gcc $(CFLAGS) -c $< -o $@ $(HEADER)

.PHONY : run clean

run: xinos.iso
	@qemu-system-i386 -cdrom xinos.iso -boot d

clean:
	@rm -vf obj/* root/boot/kernel xinos.iso