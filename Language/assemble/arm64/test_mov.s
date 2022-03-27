	.arch armv8-a
	.file	"test_mov.c"
	.global	a
	.data
	.align	2
	.type	a, %object
	.size	a, 4
a:
	.word	1
	.global	b
	.align	2
	.type	b, %object
	.size	b, 4
b:
	.word	2
	.comm	c,4,4
	.section	.rodata
	.align	3
.LC0:
	.string	"c = %d\n"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
#APP
// 9 "test_mov.c" 1
	mov x0, 0xffff0000ffff
	
// 0 "" 2
#NO_APP
	adrp	x0, c
	add	x0, x0, :lo12:c
	ldr	w1, [x0]
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
