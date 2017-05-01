# Makefile for XinOS

CFLAGS=-Wall -std=c11 -O2 -m32
HEADER=-Iinclude

xinos.iso: root/kernel root/boot/grub/grub.cfg
	@echo building $@
	@grub-mkrescue root/ -o $@

root/kernel: object/boot.o object/kernel.o object/string.o object/screen.o
	@echo building $@
	@ld -m elf_i386 -T source/link.ld object/boot.o object/kernel.o object/string.o object/screen.o -o $@

object/boot.o: source/boot.asm
	@echo building $@
	@nasm -f elf32 $< -o $@

object/%.o: source/%.c
	@echo building $@
	@gcc $(CFLAGS) $(HEADER) -c $< -o $@

.PHONY : run clean

run: xinos.iso
	@qemu-system-i386 -cdrom xinos.iso -boot d

clean:
	@rm -vf object/*.o root/kernel xinos.iso