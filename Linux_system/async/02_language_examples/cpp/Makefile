# Chapter 2: C++ async examples Makefile
#
# Usage:
#   make          compile all examples
#   make run      compile and run all examples
#   make clean    clean build artifacts

CXX ?= g++
CXXFLAGS_BASE = -std=c++20 -O0 -g

# GCC >= 14: coroutines enabled by default with -std=c++20
# GCC < 14:  needs -fcoroutines flag
GCC_VER_MAJOR := $(shell $(CXX) -dumpversion 2>/dev/null | cut -d. -f1)
GCC_NEEDS_CORO := $(shell [ "$(GCC_VER_MAJOR)" -lt 14 ] 2>/dev/null && echo yes || echo no)

ifeq ($(findstring clang,$(CXX)),clang)
  CXXFLAGS_CORO = $(CXXFLAGS_BASE)
else ifeq ($(GCC_NEEDS_CORO),yes)
  CXXFLAGS_CORO = $(CXXFLAGS_BASE) -fcoroutines
else
  CXXFLAGS_CORO = $(CXXFLAGS_BASE)
endif

# Windows vs Linux (.exe suffix)
ifeq ($(OS),Windows_NT)
  EXE = .exe
else
  EXE =
endif

CXXFLAGS_THREAD = -pthread

NAMES   = basic_coroutine future_promise generator
TARGETS = $(addsuffix $(EXE),$(NAMES))

.PHONY: all run run-basic run-future run-generator clean

all: $(TARGETS)

basic_coroutine$(EXE): basic_coroutine.cpp
	$(CXX) $(CXXFLAGS_CORO) -o $@ $<

future_promise$(EXE): future_promise.cpp
	$(CXX) $(CXXFLAGS_BASE) $(CXXFLAGS_THREAD) -o $@ $<

generator$(EXE): generator.cpp
	$(CXX) $(CXXFLAGS_CORO) -o $@ $<

run: all run-basic run-future run-generator

run-basic: basic_coroutine$(EXE)
	@echo ""
	@echo "=== basic_coroutine ==="
	@echo ""
	./basic_coroutine$(EXE)

run-future: future_promise$(EXE)
	@echo ""
	@echo "=== future_promise ==="
	@echo ""
	./future_promise$(EXE)

run-generator: generator$(EXE)
	@echo ""
	@echo "=== generator ==="
	@echo ""
	./generator$(EXE)

clean:
	rm -f $(TARGETS)
