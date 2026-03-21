#include <coroutine>
#include <iostream>
#include <string>

template <typename T>
struct Task {
    struct promise_type {
        T result;
        std::exception_ptr exception;

        Task get_return_object() {
            return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_never initial_suspend() noexcept {
            std::cout << "  [promise] initial_suspend\n";
            return {};
        }

        std::suspend_always final_suspend() noexcept {
            std::cout << "  [promise] final_suspend\n";
            return {};
        }

        void return_value(T value) {
            std::cout << "  [promise] return_value\n";
            result = std::move(value);
        }

        void unhandled_exception() {
            exception = std::current_exception();
        }
    };

    using handle_type = std::coroutine_handle<promise_type>;
    handle_type coro_handle;

    explicit Task(handle_type h) : coro_handle(h) {}
    
    Task(Task&& other) noexcept : coro_handle(other.coro_handle) {
        other.coro_handle = nullptr;
    }
    
    Task& operator=(Task&& other) noexcept {
        if (this != &other) {
            if (coro_handle) coro_handle.destroy();
            coro_handle = other.coro_handle;
            other.coro_handle = nullptr;
        }
        return *this;
    }

    ~Task() {
        if (coro_handle) coro_handle.destroy();
    }

    T result() const {
        if (coro_handle.promise().exception)
            std::rethrow_exception(coro_handle.promise().exception);
        return coro_handle.promise().result;
    }

    bool done() const { return coro_handle.done(); }
};

struct SimpleAwaiter {
    bool await_ready() const noexcept {
        std::cout << "  [awaiter] await_ready\n";
        return false;
    }
    
    bool await_suspend(std::coroutine_handle<> handle) const noexcept {
        std::cout << "  [awaiter] await_suspend\n";
        return false;  // 立即恢复
    }
    
    std::string await_resume() const noexcept {
        std::cout << "  [awaiter] await_resume\n";
        return "hello";
    }
};

Task<std::string> simple_coroutine() {
    std::cout << "coroutine start\n";
    auto result = co_await SimpleAwaiter{};
    std::cout << "coroutine got: " << result << "\n";
    co_return result;
}

int main() {
    std::cout << "main start\n";
    auto task = simple_coroutine();
    std::cout << "main after coroutine, done=" << task.done() << "\n";
    std::cout << "result: " << task.result() << "\n";
    return 0;
}
