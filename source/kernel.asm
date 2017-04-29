; kernel.asm for XinOS
bits 32			; 32位模式
section .text	; 代码段
	align 	4                     ; 多重引导规范
	dd 		0x1BADB002 	          ; 魔数
	dd 		0x00000000 	          ; 标志
	dd 		- (0x1BADB002 + 0x00) ; 校验和==-(魔数+标志)

global start
extern main

start:
	cli
	call main  ; 调用C代码main函数
end:
	hlt
    jmp end
