CC := g++
OBJDUMP := objdump

dump: dlopen
	$(OBJDUMP) -d a.out > dump_a.txt
	$(OBJDUMP) -d libpoint.so > dump_so.txt

dlopen: dynamic
	$(CC) dlopen.cpp -L. -lpoint -ldl

dynamic: object
	$(CC) -shared -fPIC -o libpoint.so point.o

object:
	$(CC) -fPIC -shared -c point.cpp

clean:
	rm *.out *.so *.o *.txt
