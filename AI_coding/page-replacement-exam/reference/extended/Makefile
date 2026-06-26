# extended/Makefile — 扩展版本构建
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -g -O2
TARGET  = page_sim

OBJS = main.o page_repl.o fifo.o lru.o clock.o optimal.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c page_repl.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean run test

clean:
	rm -f $(TARGET) *.o

run: $(TARGET)
	./$(TARGET) 3 FIFO
	./$(TARGET) 3 LRU
	./$(TARGET) 3 Clock
	./$(TARGET) 3 Optimal
