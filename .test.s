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
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, a(%rip)
	movl	a(%rip), %eax
	cmpl	-4(%rbp), %eax
	jle	.L2
	movl	$0, %eax
	jmp	.L3
.L2:
	movl	a(%rip), %eax
	cltq
	movl	c(,%rax,4), %eax
	movl	%eax, b(%rip)
	movl	c+4(%rip), %eax
	movl	%eax, d(%rip)
	movl	b(%rip), %eax
	cltq
	movl	$10, c(,%rax,4)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
.L3:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	add, .-add
	.section	.rodata
.LC0:
	.string	"asdasd"
.LC1:
	.string	"%d"
	.text
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
	movl	b(%rip), %eax
	cmpl	$9, %eax
	jg	.L5
	movl	a(%rip), %eax
	addl	$1, %eax
	movl	%eax, a(%rip)
.L5:
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	b(%rip), %eax
	movl	d(%rip), %ecx
	cltd
	idivl	%ecx
	movl	%eax, a(%rip)
	movl	$0, %r8d
	movl	$0, %ecx
	movl	$3, %edx
	movl	$2, %esi
	movl	$1, %edi
	call	add
	movl	%eax, d(%rip)
	movl	$d, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	$115, %edi
	call	putchar
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.9.2-10ubuntu13) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
