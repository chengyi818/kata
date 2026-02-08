# 第二章 Rust 异步示例 Makefile
#
# 用法：
#   make          编译所有示例
#   make run      编译并运行所有示例
#   make clean    清理

BINS = basic_async future_impl select_join

.PHONY: all run $(addprefix run-,$(BINS)) clean

all:
	cargo build

run: $(addprefix run-,$(BINS))

run-basic_async:
	@echo ""; echo "=== basic_async ==="; echo ""
	cargo run --bin basic_async

run-future_impl:
	@echo ""; echo "=== future_impl ==="; echo ""
	cargo run --bin future_impl

run-select_join:
	@echo ""; echo "=== select_join ==="; echo ""
	cargo run --bin select_join

clean:
	cargo clean
