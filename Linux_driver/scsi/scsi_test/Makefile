CC = gcc
RM = rm
EXE = scsi_test
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

$(EXE): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $^

clean:
	$(RM) $(EXE) $(OBJS)

.PHONY: clean
