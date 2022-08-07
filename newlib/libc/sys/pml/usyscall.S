/* usyscall.S -- This file is part of PML.
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
	.global do_syscall
ASM_FUNC_BEGIN (do_syscall):
	push	%rbp
	mov	%rsp, %rbp

	mov	%rdi, %rax
	mov	%rsi, %rdi
	mov	%rdx, %rsi
	mov	%rcx, %rdx
	mov	%r8, %r10
	mov	%r9, %r8
	mov	8(%rbp), %r9
	clc
	syscall
	jnc	.end

	mov	%eax, %edi
	call	__set_errno
	mov	$-1, %rax

.end:
	pop	%rbp
	ret
ASM_FUNC_END (do_syscall)
