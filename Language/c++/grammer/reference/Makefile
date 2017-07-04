dump: dlopen
	objdump -d a.out > dump_a.txt
	objdump -d libpoint.so > dump_so.txt

dlopen: dynamic
	g++ dlopen.cpp -L. -lpoint -ldl

dynamic: object
	g++ -shared -fPIC -o libpoint.so point.o

object:
	g++ -fPIC -shared -c point.cpp


clean:
	rm *.out *.so *.o *.txt
