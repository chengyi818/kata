# 第二章 C++ 异步示例 Makefile
#
# 用法：
#   make          编译所有示例
#   make run      编译并运行所有示例
#   make clean    清理

CXX ?= g++
CXXFLAGS_BASE = -std=c++20 -O0 -g

# GCC 需要 -fcoroutines 标志
ifeq ($(findstring g++,$(CXX)),g++)
  CXXFLAGS_CORO = $(CXXFLAGS_BASE) -fcoroutines
else ifeq ($(findstring clang,$(CXX)),clang)
  CXXFLAGS_CORO = $(CXXFLAGS_BASE)
else
  CXXFLAGS_CORO = $(CXXFLAGS_BASE) -fcoroutines
endif

CXXFLAGS_THREAD = -pthread

TARGETS = basic_coroutine future_promise generator

.PHONY: all run run-basic run-future run-generator clean

all: $(TARGETS)

basic_coroutine: basic_coroutine.cpp
	$(CXX) $(CXXFLAGS_CORO) -o $@ $<

future_promise: future_promise.cpp
	$(CXX) $(CXXFLAGS_BASE) $(CXXFLAGS_THREAD) -o $@ $<

generator: generator.cpp
	$(CXX) $(CXXFLAGS_CORO) -o $@ $<

run: all run-basic run-future run-generator

run-basic: basic_coroutine
	@echo ""; echo "=== basic_coroutine ==="; echo ""
	./basic_coroutine

run-future: future_promise
	@echo ""; echo "=== future_promise ==="; echo ""
	./future_promise

run-generator: generator
	@echo ""; echo "=== generator ==="; echo ""
	./generator

clean:
	rm -f $(TARGETS)
