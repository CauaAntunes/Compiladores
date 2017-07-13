	.file	".test.c"
	.comm	a,4,4
	.globl	b
	.data
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.long	5
	.comm	d,4,4
	.globl	e
	.align 8
	.type	e, @object
	.size	e, 8
e:
	.long	2576980378
	.long	1070176665
	.globl	f
	.align 4
	.type	f, @object
	.size	f, 4
f:
	.long	1045220557
	.comm	c,12,4
	.globl	cococococ
	.align 4
	.type	cococococ, @object
	.size	cococococ, 12
cococococ:
	.long	1
	.long	2
	.long	3
	.text
	.globl	add
	.type	add, @function
add:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, a(%rip)
	movl	a(%rip), %eax
	movl	%eax, b(%rip)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	add, .-add
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	a(%rip), %edx
	movl	b(%rip), %eax
	cmpl	%eax, %edx
	jge	.L4
	movl	a(%rip), %eax
	addl	$1, %eax
	movl	%eax, a(%rip)
.L4:
	movl	$1, d(%rip)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.9.2-10ubuntu13) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
