# Makefile for XinOS

CFLAGS=-Wall -std=c11 -O2 -m32
HEADER=-Iinclude

xinos.iso: root/kernel root/boot/grub/grub.cfg
	grub-mkrescue root/ -o $@

root/kernel: obj/boot.o obj/kernel.o obj/string.o obj/screen.o
	ld -m elf_i386 -T source/link.ld obj/boot.o obj/kernel.o obj/string.o obj/screen.o -o $@

obj/boot.o: source/boot.asm
	nasm -f elf32 $< -o $@

obj/%.o: source/%.c
	gcc $(CFLAGS) $(HEADER) -c $< -o $@

.PHONY : run clean

run: xinos.iso
	@qemu-system-i386 -cdrom xinos.iso -boot d

clean:
	@rm -vf obj/*.o root/kernel xinos.iso