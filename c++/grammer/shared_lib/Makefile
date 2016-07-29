all: a.so
	g++ link.cpp -L. -la -o link
	g++ dl.cpp -ldl -o dl

a.so:
	g++ -fPIC -c a.cpp -o a.o
	g++ -fPIC -shared a.o -o liba.so

clean:
	rm a.o liba.so link dl
