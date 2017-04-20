.PHONY: clean

CC = gcc
RM = rm
EXE = simple.exe
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
COMMON_CPPFLAGS = -Wextra -Wall -pedantic -D_FORTIFY_SOURCE=2 -fwrapv --param ssp-buffer-size=4 -O2 -Werror -std=gnu99
COMMON_LDFLAGS =  -Wl,-z,relro,-z,now

$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(COMMON_CPPFLAGS) $(COMMON_LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $^ $(COMMON_CPPFLAGS) $(COMMON_LDFLAGS)

clean:
	$(RM) $(EXE) $(OBJS)
