/* crt0.S -- This file is part of PML.
   Copyright (C) 2021 XNSC

   PML is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   PML is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with PML. If not, see <https://www.gnu.org/licenses/>. */

#include <pml/asm.h>

	.section .text
	.global _start
ASM_FUNC_BEGIN (_start):
	xor	%edi, %edi
	test	%rsi, %rsi
	jz	.no_argv

.argc_loop:
	mov	(%rsi,%rdi,8), %rax
	test	%rax, %rax
	jz	.argc_done
	inc	%edi
	jmp	.argc_loop

.argc_done:
	mov	(%rsi), %rax
	mov	%rax, __progname(%rip)

.no_argv:
	call	main
	mov	%eax, %edi
	call	exit
ASM_FUNC_END (_start)
