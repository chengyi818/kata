all:
	gcc -fpic -c -I/usr/include/python2.7 example.c wrapper.c
	gcc -shared -o example.so example.o wrapper.o
