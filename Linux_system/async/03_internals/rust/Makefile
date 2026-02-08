# 第三章 Rust 异步底层分析 Makefile
#
# 用法：
#   make          编译所有示例
#   make run      编译并运行所有示例
#   make asm      生成未优化 ARM64/x86_64 汇编
#   make asm-opt  生成优化后汇编
#   make clean    清理

BINS = state_machine pin_unpin mini_executor

.PHONY: all run $(addprefix run-,$(BINS)) asm asm-opt clean

all:
	cargo build

run: $(addprefix run-,$(BINS))

run-state_machine:
	@echo ""; echo "=== state_machine ==="; echo ""
	cargo run --bin state_machine

run-pin_unpin:
	@echo ""; echo "=== pin_unpin ==="; echo ""
	cargo run --bin pin_unpin

run-mini_executor:
	@echo ""; echo "=== mini_executor ==="; echo ""
	cargo run --bin mini_executor

asm:
	@echo "=== 生成未优化汇编 ==="
	cargo rustc --bin state_machine -- --emit asm -C opt-level=0
	@ASM=$$(find target/debug/deps -name 'state_machine-*.s' | head -1); \
	 echo "已生成: $$ASM  ($$(wc -l < $$ASM) 行)"

asm-opt:
	@echo "=== 生成优化汇编 ==="
	cargo rustc --release --bin state_machine -- --emit asm -C opt-level=2
	@ASM=$$(find target/release/deps -name 'state_machine-*.s' | head -1); \
	 echo "已生成: $$ASM  ($$(wc -l < $$ASM) 行)"

clean:
	cargo clean
