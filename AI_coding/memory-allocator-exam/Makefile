CC       = gcc
CFLAGS   = -Wall -Wextra -g -O0 -std=c11
BASIC    = reference/basic
EXTENDED = reference/extended
TEST     = reference/tests

.PHONY: all basic extended test test_basic test_extended clean

all: basic extended test

# ---- Basic ----
basic: $(BASIC)/main
	@echo "Running basic test..."
	@$(BASIC)/main

$(BASIC)/main: $(BASIC)/main.c $(BASIC)/allocator.c $(BASIC)/allocator.h
	$(CC) $(CFLAGS) -o $@ $(BASIC)/main.c $(BASIC)/allocator.c

# ---- Extended ----
EXT_SRCS = $(EXTENDED)/allocator.c \
           $(EXTENDED)/strategy_factory.c \
           $(EXTENDED)/strategy_first_fit.c \
           $(EXTENDED)/strategy_best_fit.c \
           $(EXTENDED)/strategy_worst_fit.c \
           $(EXTENDED)/strategy_buddy.c

extended: $(EXTENDED)/main
	@echo "Running extended test..."
	@$(EXTENDED)/main

$(EXTENDED)/main: $(EXTENDED)/main.c $(EXT_SRCS) $(EXTENDED)/allocator.h $(EXTENDED)/strategy_factory.h
	$(CC) $(CFLAGS) -o $@ $(EXTENDED)/main.c $(EXT_SRCS)

# ---- Tests ----
test: test_basic test_extended

test_basic: $(TEST)/test_basic
	@echo "=== Running basic unit tests ==="
	@$(TEST)/test_basic

$(TEST)/test_basic: $(TEST)/test_basic.c $(BASIC)/allocator.c $(BASIC)/allocator.h
	$(CC) $(CFLAGS) -o $@ $(TEST)/test_basic.c $(BASIC)/allocator.c

test_extended: $(TEST)/test_extended
	@echo "=== Running extended unit tests ==="
	@$(TEST)/test_extended

$(TEST)/test_extended: $(TEST)/test_extended.c $(EXT_SRCS) $(EXTENDED)/allocator.h $(EXTENDED)/strategy_factory.h
	$(CC) $(CFLAGS) -o $@ $(TEST)/test_extended.c $(EXT_SRCS)

clean:
	rm -f $(BASIC)/main $(EXTENDED)/main $(TEST)/test_basic $(TEST)/test_extended
