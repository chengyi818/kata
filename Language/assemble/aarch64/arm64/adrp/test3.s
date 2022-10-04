	.arch armv8-a
	.file	"test3.c"
	.global	g
	.data
	.align	2
	.type	g, %object
	.size	g, 4
g:
	.word	1
	.global	g2
	.align	2
	.type	g2, %object
	.size	g2, 4
g2:
	.word	4
	.global	g3
	.align	2
	.type	g3, %object
	.size	g3, 4
g3:
	.word	7
	.global	g4
	.align	2
	.type	g4, %object
	.size	g4, 4
g4:
	.word	8
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	adrp	x0, g
	add	x0, x0, :lo12:g
	mov	w1, 2
	str	w1, [x0]
	adrp	x0, g2
	add	x0, x0, :lo12:g2
	mov	w1, 5
	str	w1, [x0]
	adrp	x0, g3
	add	x0, x0, :lo12:g3
	mov	w1, 6
	str	w1, [x0]
	adrp	x0, g4
	add	x0, x0, :lo12:g4
	mov	w1, 9
	str	w1, [x0]
	nop
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
