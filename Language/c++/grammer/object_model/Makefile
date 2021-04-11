CC := g++
CFLAGS := -std=c++11 -g
LDFLAGS :=

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %cpp, %out, $(SRCS))

all: clean $(OBJS)

%.out:%.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@


clean:
	rm -rf *.out
