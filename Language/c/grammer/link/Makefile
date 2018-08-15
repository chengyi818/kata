STATIC_FILE := static.c
STATIC_UNLESS_FILE := static_unless.c
DYNAMIC_FILE := dynamic.c

all: dynamic

dynamic: static
	gcc -o libdynamic.so dynamic.o -shared -fPIC -L. -lstatic

static: object
	ar -r libstatic.a static.o static_unless.o

object:
	gcc -shared -fPIC -c $(STATIC_FILE)
	gcc -shared -fPIC -c $(STATIC_UNLESS_FILE)
	gcc -shared -fPIC -c $(DYNAMIC_FILE)

clean:
	rm *.o *.so *.a

dump:
	objdump -tT libdynamic.so
