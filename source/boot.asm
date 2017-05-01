; kernel.asm for XinOS

%define multiboot_magic 0x1badb002
%define multiboot_flags 0x00000000

[bits 32]
global start
extern main
align  4

[section .text]
multiboot_header:
	dd multiboot_magic
	dd multiboot_flags
	dd - (multiboot_magic + multiboot_flags) ; multiboot magic checksum

start:
	cli 		; block interrupts
	call main	; call c main function
end:
	hlt 		; halt the CPU
	jmp end
