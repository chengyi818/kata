# ============================================================
# 异步编程学习 —— 顶层 Makefile
# ============================================================
#
# 本地（x86_64 host）：
#   make help           查看所有可用目标
#   make run-all        运行全部示例
#   make ch1            运行第一章 Python 对比示例
#   make ch2            编译并运行第二章所有语言示例
#   make ch3            编译并运行第三章所有底层分析
#   make clean          清理所有编译产物
#
# 树莓派（ARM64）：
#   make pi-deploy      将代码同步到树莓派
#   make pi-build       在树莓派上编译 C++ 和 Rust
#   make pi-run         在树莓派上运行所有示例
#   make pi-asm         在树莓派上生成 ARM64 汇编
#   make pi-clean       清理树莓派上的编译产物
#
# 变量可覆盖：
#   PI_HOST=pi@192.168.3.15  树莓派 SSH 地址
#   PI_DIR=/tmp/async_kata    树莓派上的工作目录
#   PI_CXX=clang++-13        树莓派上的 C++ 编译器
#   PYTHON=python3            Python 解释器
# ============================================================

PYTHON   ?= python3
PI_HOST  ?= pi@192.168.3.15
PI_DIR   ?= /tmp/async_kata
PI_CXX   ?= clang++-13
PI_CXXFLAGS ?= -std=c++20 -stdlib=libc++

.PHONY: help run-all clean
.PHONY: ch1 ch2 ch2-python ch2-cpp ch2-rust ch3 ch3-python ch3-cpp ch3-rust
.PHONY: pi-deploy pi-build pi-run pi-asm pi-clean

# ============================================================
# 帮助
# ============================================================

help:
	@echo "============================================"
	@echo " 异步编程学习 Makefile"
	@echo "============================================"
	@echo ""
	@echo " 本地运行（x86_64）："
	@echo "   make ch1            第一章：同步/多线程/异步对比"
	@echo "   make ch2            第二章：所有语言示例"
	@echo "   make ch2-python       Python 示例"
	@echo "   make ch2-cpp          C++ 示例"
	@echo "   make ch2-rust         Rust 示例"
	@echo "   make ch3            第三章：所有底层分析"
	@echo "   make ch3-python       Python 字节码分析"
	@echo "   make ch3-cpp          C++ 协程变换"
	@echo "   make ch3-rust         Rust 状态机/Pin/executor"
	@echo "   make run-all        运行全部"
	@echo "   make clean          清理所有编译产物"
	@echo ""
	@echo " 树莓派（ARM64, $(PI_HOST)）："
	@echo "   make pi-deploy      同步代码到树莓派"
	@echo "   make pi-build       编译 C++ 和 Rust"
	@echo "   make pi-run         运行所有示例"
	@echo "   make pi-asm         生成 ARM64 汇编"
	@echo "   make pi-clean       清理树莓派编译产物"
	@echo ""
	@echo " 变量: PI_HOST=$(PI_HOST) PI_DIR=$(PI_DIR)"

# ============================================================
# 第一章：为什么需要异步
# ============================================================

ch1:
	@echo ""; echo "##############################"
	@echo "# 第一章：为什么需要异步"
	@echo "##############################"
	@echo ""; echo "--- 1/3 同步阻塞 ---"
	$(PYTHON) 01_why_async/blocking_io.py
	@echo ""; echo "--- 2/3 多线程 ---"
	$(PYTHON) 01_why_async/multithread_io.py
	@echo ""; echo "--- 3/3 异步协程 ---"
	$(PYTHON) 01_why_async/async_io.py

# ============================================================
# 第二章：各语言异步示例
# ============================================================

ch2: ch2-python ch2-cpp ch2-rust

ch2-python:
	@echo ""; echo "##############################"
	@echo "# 第二章 Python"
	@echo "##############################"
	@echo ""; echo "--- basic_coroutine ---"
	$(PYTHON) 02_language_examples/python/basic_coroutine.py
	@echo ""; echo "--- future_and_task ---"
	$(PYTHON) 02_language_examples/python/future_and_task.py
	@echo ""; echo "--- producer_consumer ---"
	$(PYTHON) 02_language_examples/python/producer_consumer.py

ch2-cpp:
	@echo ""; echo "##############################"
	@echo "# 第二章 C++"
	@echo "##############################"
	$(MAKE) -C 02_language_examples/cpp run

ch2-rust:
	@echo ""; echo "##############################"
	@echo "# 第二章 Rust"
	@echo "##############################"
	$(MAKE) -C 02_language_examples/rust run

# ============================================================
# 第三章：底层实现细节
# ============================================================

ch3: ch3-python ch3-cpp ch3-rust

ch3-python:
	@echo ""; echo "##############################"
	@echo "# 第三章 Python 字节码分析"
	@echo "##############################"
	@echo ""; echo "--- generator → coroutine 演进 ---"
	$(PYTHON) 03_internals/python/generator_coroutine.py
	@echo ""; echo "--- 协程字节码反汇编 ---"
	$(PYTHON) 03_internals/python/bytecode_inspect.py
	@echo ""; echo "--- 手写迷你 event loop ---"
	$(PYTHON) 03_internals/python/event_loop_mini.py

ch3-cpp:
	@echo ""; echo "##############################"
	@echo "# 第三章 C++ 协程变换"
	@echo "##############################"
	$(MAKE) -C 03_internals/cpp run

ch3-rust:
	@echo ""; echo "##############################"
	@echo "# 第三章 Rust 状态机/Pin/executor"
	@echo "##############################"
	$(MAKE) -C 03_internals/rust run

# ============================================================
# 全部运行
# ============================================================

run-all: ch1 ch2 ch3

# ============================================================
# 清理
# ============================================================

clean:
	$(MAKE) -C 02_language_examples/cpp clean
	$(MAKE) -C 02_language_examples/rust clean
	$(MAKE) -C 03_internals/cpp clean
	$(MAKE) -C 03_internals/rust clean

# ============================================================
# 树莓派（ARM64）
# ============================================================

# --- 同步代码到树莓派 ---
pi-deploy:
	@echo "=== 同步代码到 $(PI_HOST):$(PI_DIR) ==="
	ssh $(PI_HOST) "mkdir -p $(PI_DIR)"
	rsync -av --delete \
		--exclude 'target/' \
		--exclude '*.o' --exclude '*.s' --exclude '*.dis' \
		--exclude 'basic_coroutine' --exclude 'future_promise' \
		--exclude 'generator' --exclude 'coroutine_transform' \
		--exclude 'Cargo.lock' \
		02_language_examples/cpp/ $(PI_HOST):$(PI_DIR)/ch2_cpp/
	rsync -av --delete \
		--exclude 'target/' --exclude 'Cargo.lock' \
		02_language_examples/rust/ $(PI_HOST):$(PI_DIR)/ch2_rust/
	rsync -av --delete \
		--exclude 'target/' \
		--exclude '*.o' --exclude '*.s' --exclude '*.dis' \
		--exclude 'coroutine_transform' \
		--exclude 'Cargo.lock' \
		03_internals/cpp/ $(PI_HOST):$(PI_DIR)/ch3_cpp/
	rsync -av --delete \
		--exclude 'target/' --exclude 'Cargo.lock' \
		03_internals/rust/ $(PI_HOST):$(PI_DIR)/ch3_rust/
	@echo ""
	@echo "=== 同步 coro_compat.h 并替换 include ==="
	scp coro_compat.h $(PI_HOST):$(PI_DIR)/ch2_cpp/
	scp coro_compat.h $(PI_HOST):$(PI_DIR)/ch3_cpp/
	ssh $(PI_HOST) 'cd $(PI_DIR) && \
		sed -i '\''s|#include <coroutine>|#include "coro_compat.h"|'\'' \
		ch2_cpp/*.cpp ch3_cpp/*.cpp 2>/dev/null; true'
	@echo "同步完成: $(PI_HOST):$(PI_DIR)/"

# --- 在树莓派上编译 ---
pi-build: pi-deploy
	@echo ""
	@echo "=== 编译 C++ ($(PI_CXX)) ==="
	ssh $(PI_HOST) 'cd $(PI_DIR)/ch2_cpp && \
		$(PI_CXX) $(PI_CXXFLAGS) -O0 -o basic_coroutine basic_coroutine.cpp && \
		$(PI_CXX) $(PI_CXXFLAGS) -O0 -pthread -o future_promise future_promise.cpp && \
		$(PI_CXX) $(PI_CXXFLAGS) -O0 -o generator generator.cpp && \
		echo "ch2_cpp: OK"'
	ssh $(PI_HOST) 'cd $(PI_DIR)/ch3_cpp && \
		$(PI_CXX) $(PI_CXXFLAGS) -O0 -o coroutine_transform coroutine_transform.cpp && \
		echo "ch3_cpp: OK"'
	@echo ""
	@echo "=== 编译 Rust ==="
	ssh $(PI_HOST) 'source $$HOME/.cargo/env && \
		cd $(PI_DIR)/ch2_rust && cargo build 2>&1 | tail -3'
	ssh $(PI_HOST) 'source $$HOME/.cargo/env && \
		cd $(PI_DIR)/ch3_rust && cargo build 2>&1 | tail -3'
	@echo ""
	@echo "=== 编译完成 ==="

# --- 在树莓派上运行所有示例 ---
pi-run: pi-build
	@echo ""
	@echo "=== 运行 C++ 第二章示例 ==="
	ssh $(PI_HOST) 'cd $(PI_DIR)/ch2_cpp && \
		echo "--- basic_coroutine ---" && ./basic_coroutine && \
		echo "" && echo "--- future_promise ---" && ./future_promise && \
		echo "" && echo "--- generator ---" && ./generator'
	@echo ""
	@echo "=== 运行 C++ 第三章示例 ==="
	ssh $(PI_HOST) 'cd $(PI_DIR)/ch3_cpp && \
		echo "--- coroutine_transform ---" && ./coroutine_transform'
	@echo ""
	@echo "=== 运行 Rust 第二章示例 ==="
	ssh $(PI_HOST) 'source $$HOME/.cargo/env && cd $(PI_DIR)/ch2_rust && \
		echo "--- basic_async ---" && cargo run --bin basic_async 2>&1 && \
		echo "" && echo "--- future_impl ---" && cargo run --bin future_impl 2>&1 && \
		echo "" && echo "--- select_join ---" && cargo run --bin select_join 2>&1'
	@echo ""
	@echo "=== 运行 Rust 第三章示例 ==="
	ssh $(PI_HOST) 'source $$HOME/.cargo/env && cd $(PI_DIR)/ch3_rust && \
		echo "--- state_machine ---" && cargo run --bin state_machine 2>&1 && \
		echo "" && echo "--- pin_unpin ---" && cargo run --bin pin_unpin 2>&1 && \
		echo "" && echo "--- mini_executor ---" && cargo run --bin mini_executor 2>&1'

# --- 在树莓派上生成 ARM64 汇编 ---
pi-asm: pi-build
	@echo ""
	@echo "=== 生成 C++ ARM64 汇编 ==="
	ssh $(PI_HOST) 'cd $(PI_DIR)/ch3_cpp && \
		$(PI_CXX) $(PI_CXXFLAGS) -O0 -S -o coroutine_transform_O0.s coroutine_transform.cpp && \
		$(PI_CXX) $(PI_CXXFLAGS) -O2 -S -o coroutine_transform_O2.s coroutine_transform.cpp && \
		echo "C++ O0: $$(wc -l < coroutine_transform_O0.s) 行" && \
		echo "C++ O2: $$(wc -l < coroutine_transform_O2.s) 行"'
	@echo ""
	@echo "=== 生成 Rust ARM64 汇编 ==="
	ssh $(PI_HOST) 'source $$HOME/.cargo/env && cd $(PI_DIR)/ch3_rust && \
		cargo rustc --bin state_machine -- --emit asm -C opt-level=0 2>&1 | tail -1 && \
		ASM=$$(find target/debug/deps -name "state_machine-*.s" | head -1) && \
		echo "Rust O0: $$(wc -l < $$ASM) 行 ($$ASM)"'
	@echo ""
	@echo "=== ARM64 汇编生成完成 ==="
	@echo "查看: ssh $(PI_HOST) 'ls -la $(PI_DIR)/ch3_cpp/*.s $(PI_DIR)/ch3_rust/target/debug/deps/state_machine-*.s'"

# --- 清理树莓派上的编译产物 ---
pi-clean:
	ssh $(PI_HOST) "rm -rf $(PI_DIR)"
	@echo "已清理: $(PI_HOST):$(PI_DIR)/"
