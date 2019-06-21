	.file	"v1.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	call	create_chain_node
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -24(%rbp)
	movl	$0, -28(%rbp)
	movl	$0, -28(%rbp)
	jmp	.L2
.L3:
	call	create_chain_node
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
	addl	$1, -28(%rbp)
.L2:
	cmpl	$999, -28(%rbp)
	jle	.L3
	movq	-24(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-16(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, (%rax)
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.globl	create_point
	.type	create_point, @function
create_point:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movsd	%xmm0, -24(%rbp)
	movsd	%xmm1, -32(%rbp)
	movl	$16, %edi
	call	malloc
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movsd	-32(%rbp), %xmm0
	movsd	%xmm0, 8(%rax)
	movq	-8(%rbp), %rax
	movsd	-24(%rbp), %xmm0
	movsd	%xmm0, (%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	create_point, .-create_point
	.globl	create_circle
	.type	create_circle, @function
create_circle:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movsd	%xmm0, -32(%rbp)
	movl	$16, %edi
	call	malloc
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movsd	-32(%rbp), %xmm0
	movsd	%xmm0, 8(%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	create_circle, .-create_circle
	.globl	create_rectangle
	.type	create_rectangle, @function
create_rectangle:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movsd	%xmm0, -24(%rbp)
	movsd	%xmm1, -32(%rbp)
	movl	$16, %edi
	call	malloc
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movsd	-32(%rbp), %xmm0
	movsd	%xmm0, 8(%rax)
	movq	-8(%rbp), %rax
	movsd	-24(%rbp), %xmm0
	movsd	%xmm0, (%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	create_rectangle, .-create_rectangle
	.globl	create_chain_node_shape
	.type	create_chain_node_shape, @function
create_chain_node_shape:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movl	$24, %edi
	call	malloc
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	create_chain_node_shape, .-create_chain_node_shape
	.globl	create_chain_node
	.type	create_chain_node, @function
create_chain_node:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movsd	.LC0(%rip), %xmm0
	movsd	%xmm0, -88(%rbp)
	movsd	.LC1(%rip), %xmm0
	movsd	%xmm0, -80(%rbp)
	movsd	.LC1(%rip), %xmm0
	movsd	%xmm0, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movq	-80(%rbp), %rax
	movapd	%xmm0, %xmm1
	movq	%rax, -104(%rbp)
	movsd	-104(%rbp), %xmm0
	call	create_point
	movq	%rax, -64(%rbp)
	movq	-88(%rbp), %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, -104(%rbp)
	movsd	-104(%rbp), %xmm0
	movq	%rax, %rdi
	call	create_circle
	movq	%rax, -56(%rbp)
	movsd	.LC2(%rip), %xmm0
	movsd	%xmm0, -48(%rbp)
	movsd	.LC1(%rip), %xmm0
	movsd	%xmm0, -40(%rbp)
	movsd	-40(%rbp), %xmm0
	movq	-48(%rbp), %rax
	movapd	%xmm0, %xmm1
	movq	%rax, -104(%rbp)
	movsd	-104(%rbp), %xmm0
	call	create_point
	movq	%rax, -32(%rbp)
	movq	-88(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, -104(%rbp)
	movsd	-104(%rbp), %xmm0
	movq	%rax, %rdi
	call	create_circle
	movq	%rax, -24(%rbp)
	movsd	.LC3(%rip), %xmm0
	movabsq	$4621819117588971520, %rax
	movapd	%xmm0, %xmm1
	movq	%rax, -104(%rbp)
	movsd	-104(%rbp), %xmm0
	call	create_rectangle
	movq	%rax, -16(%rbp)
	movl	$24, %edi
	call	malloc
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$0, (%rax)
	movq	-8(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movq	-56(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	create_chain_node_shape
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 16(%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	create_chain_node, .-create_chain_node
	.section	.rodata
	.align 8
.LC0:
	.long	0
	.long	1071644672
	.align 8
.LC1:
	.long	0
	.long	1072693248
	.align 8
.LC2:
	.long	0
	.long	1075970048
	.align 8
.LC3:
	.long	0
	.long	1073741824
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
