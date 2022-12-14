.PHONY: clean

CC = gcc
RM = rm
EXE = simple.exe
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

$(EXE): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $^

clean:
	$(RM) $(EXE) $(OBJS)
