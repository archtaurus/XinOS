; kernel.asm for XinOS

%define multiboot_magic 0x1badb002
%define multiboot_flags 0x00000000

[bits 32]
[section .text]
global start
extern kmain
align  4

multiboot_header:
	dd multiboot_magic
	dd multiboot_flags
	dd - (multiboot_magic + multiboot_flags) ; multiboot magic checksum
start:
	cli 		; clear interrupts
	call kmain	; call c kmain function
end:
	hlt 		; halt the CPU
	jmp end
