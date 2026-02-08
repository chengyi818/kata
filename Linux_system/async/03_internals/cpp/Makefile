# 第三章 C++ 协程底层分析 Makefile
#
# 用法：
#   make          编译程序
#   make run      编译并运行
#   make asm      生成 -O0 汇编（完整协程变换细节）
#   make asm-opt  生成 -O2 汇编（观察 HALO 优化）
#   make disasm   生成反汇编
#   make clean    清理

CXX ?= g++
CXXFLAGS_BASE = -std=c++20

# GCC 需要 -fcoroutines 标志
ifeq ($(findstring g++,$(CXX)),g++)
  CXXFLAGS_CORO = $(CXXFLAGS_BASE) -fcoroutines
else ifeq ($(findstring clang,$(CXX)),clang)
  CXXFLAGS_CORO = $(CXXFLAGS_BASE)
else
  CXXFLAGS_CORO = $(CXXFLAGS_BASE) -fcoroutines
endif

CXXFLAGS_DEBUG = $(CXXFLAGS_CORO) -O0 -g
CXXFLAGS_OPT   = $(CXXFLAGS_CORO) -O2

TARGET = coroutine_transform

.PHONY: all run asm asm-opt disasm clean

all: $(TARGET)

$(TARGET): coroutine_transform.cpp
	$(CXX) $(CXXFLAGS_DEBUG) -o $@ $<

run: $(TARGET)
	@echo ""; echo "=== coroutine_transform ==="; echo ""
	./$(TARGET)

asm: coroutine_transform.cpp
	@echo "=== 生成未优化汇编 (-O0) ==="
	$(CXX) $(CXXFLAGS_DEBUG) -S -fverbose-asm -o $(TARGET)_O0.s $<
	@echo "已生成: $(TARGET)_O0.s  ($$(wc -l < $(TARGET)_O0.s) 行)"
	@echo "推荐: grep -n 'coro\|resume\|suspend' $(TARGET)_O0.s"

asm-opt: coroutine_transform.cpp
	@echo "=== 生成优化汇编 (-O2) ==="
	$(CXX) $(CXXFLAGS_OPT) -S -fverbose-asm -o $(TARGET)_O2.s $<
	@echo "已生成: $(TARGET)_O2.s  ($$(wc -l < $(TARGET)_O2.s) 行)"

disasm: $(TARGET)
	objdump -d -C --no-show-raw-insn $< > $(TARGET).dis
	@echo "已生成: $(TARGET).dis"

clean:
	rm -f $(TARGET) $(TARGET)_O0.s $(TARGET)_O2.s $(TARGET).dis
