test1:
	aarch64-linux-gnu-gcc -static -g test1.c
	aarch64-linux-gnu-gcc -S test1.c

test2:
	aarch64-linux-gnu-gcc -static -g test2.c
	aarch64-linux-gnu-gcc -S test2.c

test_sbc:
	aarch64-linux-gnu-gcc -static -g test_sbc.c
	aarch64-linux-gnu-gcc -S test_sbc.c

run:
	qemu-aarch64 -L /usr/aarch64-linux-gnu  ./a.out

gdb:
	qemu-aarch64 -L /usr/aarch64-linux-gnu  -g 1234 ./a.out
