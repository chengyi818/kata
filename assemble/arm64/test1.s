	.arch armv8-a
	.file	"test1.c"
	.section	.rodata
	.align	3
.LC0:
	.string	"hello"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
#APP
// 5 "test1.c" 1
	nop
// 0 "" 2
#NO_APP
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	puts
#APP
// 7 "test1.c" 1
	nop
	nop
	
// 0 "" 2
#NO_APP
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
