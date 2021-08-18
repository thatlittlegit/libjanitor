/*
 * Copyright 2021 thatlittlegit <personal@thatlittlegit.tk>
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */
	.section .text
	.global janitor_clean
	.func janitor_clean
janitor_clean:
	/* (struct janitor_context *) */
	endbr32

	/* allocate a holding cell */
	mov %rdi, %rdx
	mov 8(%rbp), %rsi
	mov %rbp, %rdi
	add $0x10, %rdi /* why? */
	call janitor_cell_new

	/* replace the old return address */
	lea janitor_clean_post(%rip), %rax
	mov %rax, 8(%rbp)

	/* return */
	ret
	.endfunc

	.func janitor_clean_post
janitor_clean_post:
	/* save the stack pointer */
	mov %rsp, %rdi

	/* save the return value */
	push %rax

	/* jump to the C code, will return correct return address */
	call janitor_clean_post_c
	mov %rax, %rdi

	/* jump there */
	pop %rax
	jmp *%rdi
