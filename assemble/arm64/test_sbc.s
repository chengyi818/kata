	.arch armv8-a
	.file	"test_sbc.c"
	.section	.rodata
	.align	3
.LC0:
	.string	"mask: %lu\n"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	mov	x0, 1
	str	x0, [x29, 24]
	mov	x0, 1
	str	x0, [x29, 32]
	mov	x0, 1
	str	x0, [x29, 40]
	ldr	x0, [x29, 24]
	ldr	x1, [x29, 32]
#APP
// 8 "test_sbc.c" 1
	cmp x0, x1
sbc x0, xzr, xzr

// 0 "" 2
#NO_APP
	str	x0, [x29, 40]
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	ldr	x1, [x29, 40]
	bl	printf
	mov	w0, 0
	ldp	x29, x30, [sp], 48
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
