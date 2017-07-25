	.data
	.globl	a
	.align	4
	.type	a, @object
	.size	a, 4
a:
	.long	0
	.globl	i
	.align	4
	.type	i, @object
	.size	i, 4
i:
	.long	0
	.globl	v
	.align	4
	.type	v, @object
	.size	v, 40
v:
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.comm	mat,40,4
	.globl	f
	.align	4
	.type	f, @object
	.size	f, 4
f:
	.long	10
	.globl	c
	.align	4
	.type	c, @object
	.size	c, 4
c:
	.long	120
	.globl	d
	.align	4
	.type	d, @object
	.size	d, 4
d:
	.long	65
.str1:
	.string	" "
.str2:
	.string	"\n"
.str3:
	.string	"*****\n"
.str4:
	.string	" Digite um numero: \n"
.str5:
	.string	"Incrementado algumas vezes fica "
.str6:
	.string	"Parou no meio\n"
.str7:
	.string	"É 11\n"
.str8:
	.string	"Não 11\n"
	.comm	n,4,4
	.comm	x,4,4
	.comm	.temp8,4,4
.str0:
	.string	"%d"
	.text
	.globl	main
	.type	main, @function
main:
.label15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$5, a(%rip)
	movl	$1, i(%rip)
.label13:
	movl	i(%rip), %eax
	cmpl	$9, %eax
	jge	.label14
	subl	$1, %eax
	cltq
	movl	v(,%rax,4), %eax
	movl	i(%rip), %ebx
	imull	%eax, %ebx
	movl	i(%rip), %eax
	cltq
	movl	%ebx, v(,%rax,4)
	movl	i(%rip), %eax
	movl	%eax, %esi
	movl	$.str0, %edi
	movl	$0, %eax
	call	printf
	movl	$.str1, %edi
	movl	$0, %eax
	call	printf
	movl	i(%rip), %eax
	cltq
	movl	v(,%rax,4), %eax
	movl	%eax, %esi
	movl	$.str0, %edi
	movl	$0, %eax
	call	printf
	movl	$.str2, %edi
	movl	$0, %eax
	call	printf
	movl	i(%rip), %eax
	addl	$1, %eax
	movl	%eax, i(%rip)
	jmp	.label13
.label14:
	movl	$.str3, %edi
	movl	$0, %eax
	call	printf
	movl	$1, i(%rip)
.label11:
	movl	i(%rip), %eax
	cmpl	$9, %eax
	jge	.label12
	cltq
	movl	v(,%rax,4), %eax
	movl	i(%rip), %esi
	cltd
	idivl	%esi
	movl	%eax, %ebx
	movl	i(%rip), %eax
	cltq
	movl	%ebx, v(,%rax,4)
	movl	i(%rip), %eax
	movl	%eax, %esi
	movl	$.str0, %edi
	movl	$0, %eax
	call	printf
	movl	$.str1, %edi
	movl	$0, %eax
	call	printf
	movl	i(%rip), %eax
	cltq
	movl	v(,%rax,4), %eax
	movl	%eax, %esi
	movl	$.str0, %edi
	movl	$0, %eax
	call	printf
	movl	$.str2, %edi
	movl	$0, %eax
	call	printf
	movl	i(%rip), %eax
	addl	$1, %eax
	movl	%eax, i(%rip)
	jmp	.label11
.label12:
	movl	$6, i(%rip)
	movl	i(%rip), %eax
	movl	%eax, %esi
	movl	$.str0, %edi
	movl	$0, %eax
	call	printf
	movl	$.str2, %edi
	movl	$0, %eax
	call	printf
	movl	$.str4, %edi
	movl	$0, %eax
	call	printf
	movl	$i, %esi
	movl	$.str0, %edi
	movl	$0, %eax
	call	__isoc99_scanf
.label5:
	movl	i(%rip), %eax
	cmpl	$10, %eax
	jg	.label6
	movl	a(%rip), %ebx
	movl	%ebx, x(%rip)
	movl	$1, n(%rip)
	call	incn
	movl	%eax, a(%rip)
	movl	i(%rip), %ebx
	addl	$1, %ebx
	movl	%ebx, i(%rip)
	movl	%ebx, %esi
	movl	$.str0, %edi
	movl	$0, %eax
	call	printf
	movl	$.str1, %edi
	movl	$0, %eax
	call	printf
	movl	a(%rip), %eax
	movl	%eax, %esi
	movl	$.str0, %edi
	movl	$0, %eax
	call	printf
	movl	$.str2, %edi
	movl	$0, %eax
	call	printf
	jmp	.label5
.label6:
	movl	$.str5, %edi
	movl	$0, %eax
	call	printf
	movl	a(%rip), %eax
	movl	%eax, %esi
	movl	$.str0, %edi
	movl	$0, %eax
	call	printf
	movl	$.str2, %edi
	movl	$0, %eax
	call	printf
	movl	$5, %eax
	movl	a(%rip), %ebx
	cmpl	%ebx, %eax
	jne	.label4
	movl	$.str6, %edi
	movl	$0, %eax
	call	printf
.label4:
	movl	$11, %eax
	movl	a(%rip), %ebx
	cmpl	%ebx, %eax
	je	.label2
	jmp	.label3
.label2:
	movl	$.str7, %edi
	movl	$0, %eax
	call	printf
.label3:
	movl	$11, %eax
	movl	a(%rip), %ebx
	cmpl	%ebx, %eax
	je	.label0
	movl	$.str8, %edi
	movl	$0, %eax
	call	printf
.label0:
.label1:
.label16:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.label17:
.size	main, .-main
	.text
	.globl	incn
	.type	incn, @function
incn:
.label18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	n(%rip), %eax
	movl	%eax,-8(%rbp)
	movl	x(%rip), %eax
	movl	%eax,-4(%rbp)
	movl	-4(%rbp), %eax
	movl	-8(%rbp), %ebx
	addl	%eax, %ebx
	movl	%ebx, %eax
.label19:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.label20:
.size	incn, .-incn
	.text
	.globl	voidfunc
	.type	voidfunc, @function
voidfunc:
.label21:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
.label22:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.label23:
.size	voidfunc, .-voidfunc
