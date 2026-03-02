/**
 * C++20 co_yield 生成器 (Generator)
 *
 * 生成器是协程最直观的应用场景之一：
 * 函数可以产出 (yield) 一系列值，每次产出后挂起，
 * 调用者消费一个值后再恢复生成器产出下一个。
 *
 * 这与 Python 的 yield 语义完全一致。
 *
 * co_yield expr 等价于 co_await promise.yield_value(expr)
 */

#include <coroutine>
#include <iostream>
#include <optional>
#include <cstdint>

// ============================================================
// 1. Generator<T> 类型定义
// ============================================================

template <typename T>
class Generator {
public:
    struct promise_type {
        T current_value;

        Generator get_return_object() {
            return Generator{handle_type::from_promise(*this)};
        }

        // 创建后挂起，等待调用者调用 next()
        std::suspend_always initial_suspend() noexcept { return {}; }

        // 结束后挂起，让调用者知道生成器已耗尽
        std::suspend_always final_suspend() noexcept { return {}; }

        // co_yield value 的处理：
        // 保存值并挂起协程，控制权返回给调用者
        std::suspend_always yield_value(T value) {
            current_value = std::move(value);
            return {};
        }

        // 生成器不需要 co_return 值（只 co_yield）
        void return_void() {}

        void unhandled_exception() {
            std::terminate();
        }
    };

    using handle_type = std::coroutine_handle<promise_type>;

    explicit Generator(handle_type h) : coro_handle(h) {}

    Generator(Generator&& other) noexcept : coro_handle(other.coro_handle) {
        other.coro_handle = nullptr;
    }

    ~Generator() {
        if (coro_handle) coro_handle.destroy();
    }

    // 获取下一个值
    std::optional<T> next() {
        if (!coro_handle || coro_handle.done()) {
            return std::nullopt;
        }
        coro_handle.resume();  // 恢复协程执行到下一个 co_yield
        if (coro_handle.done()) {
            return std::nullopt;  // 协程已结束
        }
        return coro_handle.promise().current_value;
    }

    // 支持 range-based for loop 的迭代器
    struct iterator {
        handle_type handle;
        bool at_end;

        iterator& operator++() {
            handle.resume();
            at_end = handle.done();
            return *this;
        }

        T operator*() const {
            return handle.promise().current_value;
        }

        bool operator!=(const iterator& other) const {
            return at_end != other.at_end;
        }
    };

    iterator begin() {
        if (coro_handle) {
            coro_handle.resume();  // 执行到第一个 co_yield
            if (coro_handle.done()) return end();
        }
        return iterator{coro_handle, false};
    }

    iterator end() {
        return iterator{coro_handle, true};
    }

private:
    handle_type coro_handle;
};


// ============================================================
// 2. 使用生成器
// ============================================================

// 简单的范围生成器
Generator<int> range(int start, int end) {
    for (int i = start; i < end; ++i) {
        co_yield i;
        // 执行到这里后协程挂起
        // 调用者获取 i 的值
        // 调用者下次调用 next() / ++iterator 时从这里恢复
    }
    // 函数结束 → 生成器耗尽
}

// 斐波那契数列生成器（无限序列）
Generator<uint64_t> fibonacci() {
    uint64_t a = 0, b = 1;
    while (true) {
        co_yield a;
        auto next = a + b;
        a = b;
        b = next;
    }
}

// 过滤生成器：只产出满足条件的值
Generator<int> filter_even(int start, int end) {
    for (int i = start; i < end; ++i) {
        if (i % 2 == 0) {
            co_yield i;
        }
    }
}


// ============================================================
// 3. 主函数
// ============================================================

int main() {
    std::cout << "=== C++20 co_yield Generator ===\n\n";

    // --- range 生成器 ---
    std::cout << "1. range(0, 5) generator:\n   ";
    auto gen = range(0, 5);
    while (auto val = gen.next()) {
        std::cout << *val << " ";
    }
    std::cout << "\n\n";

    // --- 使用 range-based for ---
    std::cout << "2. range-based for loop:\n   ";
    for (int val : range(10, 15)) {
        std::cout << val << " ";
    }
    std::cout << "\n\n";

    // --- 斐波那契 ---
    std::cout << "3. Fibonacci sequence (first 15):\n   ";
    auto fib = fibonacci();
    for (int i = 0; i < 15; ++i) {
        auto val = fib.next();
        if (val) std::cout << *val << " ";
    }
    std::cout << "\n\n";

    // --- 过滤生成器 ---
    std::cout << "4. Even filter filter_even(0, 10):\n   ";
    for (int val : filter_even(0, 10)) {
        std::cout << val << " ";
    }
    std::cout << "\n\n";

    std::cout << "=== Execution Flow (range(0, 3) as example) ===\n";
    std::cout << "  Call range(0,3):\n";
    std::cout << "    -> allocate coroutine frame\n";
    std::cout << "    -> initial_suspend: suspend (lazy)\n";
    std::cout << "  Call next():\n";
    std::cout << "    -> resume() resumes coroutine\n";
    std::cout << "    -> execute co_yield 0\n";
    std::cout << "    -> yield_value(0): store value, suspend coroutine\n";
    std::cout << "    -> return optional(0)\n";
    std::cout << "  Call next():\n";
    std::cout << "    -> resume() resumes coroutine\n";
    std::cout << "    -> i++, co_yield 1\n";
    std::cout << "    -> return optional(1)\n";
    std::cout << "  ... until loop ends, coroutine returns -> done()=true\n";

    return 0;
}
