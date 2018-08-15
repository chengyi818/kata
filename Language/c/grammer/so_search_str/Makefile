compile:
	gcc -fPIC -c func.c
	gcc -shared -fPIC -o libfunc.so func.o
	g++ main.cpp -L. -lfunc

clean:
	- rm func.o
	- rm libfunc.so
