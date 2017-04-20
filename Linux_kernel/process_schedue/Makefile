.PHONY: clean

CC = gcc -g
RM = rm
EXE = a.out
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

$(EXE): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $^

clean:
	$(RM) $(EXE) $(OBJS)
