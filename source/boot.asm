; kernel.asm for XinOS

[bits 32]

%define multiboot_magic 0x1BADB002
%define multiboot_flags 0x00000000
%define multiboot_checksum -(multiboot_magic + multiboot_flags)

; Declare a multiboot header that marks the program as a kernel. These are magic
; values that are documented in the multiboot standard. The bootloader will
; search for this signature in the first 8 KiB of the kernel file, aligned at a
; 32-bit boundary. The signature is in its own section so the header can be
; forced to be within the first 8 KiB of the kernel file.
[section .multiboot_header]
align 4
	dd multiboot_magic
	dd multiboot_flags
	dd multiboot_checksum

; The linker script specifies start as the entry point to the kernel and the
; bootloader will jump to this position once the kernel has been loaded. It
; doesn't make sense to return from this function as the bootloader is gone.
; Declare start as a function symbol with the given symbol size.
[section .text]
global start:function (end - start)
start:
	extern kmain
	call kmain  ; call c kmain function

	; If the system has nothing more to do, put the computer into an
	; infinite loop. To do that:
	; 1) Disable interrupts with cli (clear interrupt enable in eflags).
	;    They are already disabled by the bootloader, so this is not needed.
	;    Mind that you might later enable interrupts and return from
	;    kernel_main (which is sort of nonsensical to do).
	; 2) Wait for the next interrupt to arrive with hlt (halt instruction).
	;    Since they are disabled, this will lock up the computer.
	; 3) Jump to the hlt instruction if it ever wakes up due to a
	;    non-maskable interrupt occurring or due to system management mode.
	cli 		; clear interrupts
halt:
	hlt 		; halt the CPU
	jmp halt
end: