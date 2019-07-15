obj:
	gcc -c -m32 a.c b.c

ab: obj
	gcc a.o b.o -m32 -o ab

clean:
	rm -f a.o b.o ab
