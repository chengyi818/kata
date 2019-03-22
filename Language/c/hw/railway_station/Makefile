# Author: ChengYi
# created time: Fri 22 Mar 2019 02:15:49 PM CST

vpath %.h include
vpath %.c src
vpath %.c tests

objects := railway.o check_railway.o

test: $(objects)
	gcc -I include $^ -o test -lcheck

$(objects): %.o: %.c
	gcc -c -I include $< -o $@

.PHONY: clean
clean:
	rm *.o test
