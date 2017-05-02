# Makefile for XinOS

CFLAGS=-Wall -std=c11 -O2 -m32
HEADER=-Iinclude
OBJECT=object/boot.o object/kernel.o object/string.o object/terminal.o

xinos.iso: root/boot/xinkernel root/boot/grub/grub.cfg
	@echo building $@
	@grub-mkrescue root/ -o $@

root/boot/xinkernel: $(OBJECT)
	@echo building $@
	@ld -m elf_i386 -T source/link.ld $(OBJECT) -o $@

object/boot.o: source/boot.asm
	@echo building $@
	@nasm -f elf32 $< -o $@

object/%.o: source/%.c
	@echo building $@
	@gcc $(CFLAGS) $(HEADER) -c $< -o $@

.PHONY : run clean

run: xinos.iso
	@qemu-system-i386 -cdrom xinos.iso -boot d

runkernel: root/kernel
	@qemu-system-i386 -kernel root/kernel

clean:
	@rm -vf object/*.o root/boot/xinkernel xinos.iso