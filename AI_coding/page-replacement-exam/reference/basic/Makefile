# basic/Makefile — 基础版本构建
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -g -O2
TARGET  = page_sim_basic

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean run

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
