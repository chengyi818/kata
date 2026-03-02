/**
 * C++20 协程基础：co_await 与 co_return
 *
 * C++20 的协程与 Python/Rust 有一个本质区别：
 * C++ 标准只定义了协程的底层机制（编译器变换规则），
 * 而不提供高层运行时（如 Python 的 asyncio 或 Rust 的 tokio）。
 *
 * 你需要自己定义：
 *   1. Promise Type —— 控制协程的行为（创建、挂起、恢复、返回值）
 *   2. Awaitable/Awaiter —— 控制 co_await 表达式的行为
 *   3. 协程返回类型 —— 包装 promise，提供对外接口
 *
 * 本文件从零构建一个最简单的协程框架来演示这些概念。
 */

#include <coroutine>
#include <iostream>
#include <string>

// ============================================================
// 1. 定义协程返回类型和 Promise Type
// ============================================================

/**
 * Task<T> —— 最简单的协程返回类型
 *
 * 当你写 `Task<int> my_coroutine() { co_return 42; }` 时，
 * 编译器会：
 *   1. 在堆上分配一个协程帧 (coroutine frame)
 *   2. 在帧中构造 promise_type 对象
 *   3. 调用 promise.get_return_object() 创建 Task 对象
 *   4. 调用 promise.initial_suspend() 决定是否立即挂起
 *   5. 执行函数体
 *   6. 遇到 co_return 时调用 promise.return_value()
 *   7. 调用 promise.final_suspend() 决定最终行为
 */
template <typename T>
struct Task {
    // --- Promise Type ---
    struct promise_type {
        T result;
        std::exception_ptr exception;

        // 1. 创建返回给调用者的 Task 对象
        Task get_return_object() {
            return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        // 2. 协程开始时是否挂起
        //    suspend_never: 立即开始执行（eager）
        //    suspend_always: 创建后挂起，需要手动 resume（lazy）
        std::suspend_never initial_suspend() noexcept {
            std::cout << "    [promise] initial_suspend: coroutine starts executing\n";
            return {};
        }

        // 3. 协程结束时是否挂起
        //    suspend_always: 挂起，让调用者可以读取结果后再销毁
        std::suspend_always final_suspend() noexcept {
            std::cout << "    [promise] final_suspend: coroutine finished\n";
            return {};
        }

        // 4. co_return value; 调用此函数
        void return_value(T value) {
            std::cout << "    [promise] return_value: storing return value\n";
            result = std::move(value);
        }

        // 5. 未捕获异常时调用
        void unhandled_exception() {
            exception = std::current_exception();
        }
    };

    // --- Task 本身 ---
    using handle_type = std::coroutine_handle<promise_type>;
    handle_type coro_handle;

    explicit Task(handle_type h) : coro_handle(h) {}

    // 移动语义（协程句柄不可复制）
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

    // 获取协程的返回值
    T result() const {
        if (coro_handle.promise().exception)
            std::rethrow_exception(coro_handle.promise().exception);
        return coro_handle.promise().result;
    }

    // 检查协程是否完成
    bool done() const { return coro_handle.done(); }
};


// ============================================================
// 2. 定义自定义 Awaiter
// ============================================================

/**
 * 一个简单的 Awaiter，演示 co_await 的三个步骤：
 *
 * co_await expr 的执行流程：
 *   1. 调用 awaiter.await_ready()
 *      - 返回 true:  不挂起，直接获取结果
 *      - 返回 false: 需要挂起
 *   2. 如果需要挂起，调用 awaiter.await_suspend(handle)
 *      - handle 是当前协程的句柄
 *      - 可以在此将 handle 保存起来，之后调用 handle.resume() 恢复
 *   3. 恢复后，调用 awaiter.await_resume() 获取 co_await 的结果值
 */
struct PrintAwaiter {
    std::string message;

    // 是否可以不挂起？（false = 必须挂起）
    bool await_ready() const noexcept {
        std::cout << "    [awaiter] await_ready: returns false, must suspend\n";
        return false;
    }

    // 挂起时的处理
    void await_suspend(std::coroutine_handle<> handle) const noexcept {
        std::cout << "    [awaiter] await_suspend: coroutine suspended, running custom logic\n";
        std::cout << "    [awaiter] message: " << message << "\n";
        // 在实际应用中，你可能会在这里注册 I/O 回调
        // 回调触发时调用 handle.resume() 恢复协程
        // 这里为了简单，立即恢复
        handle.resume();
    }

    // 恢复后获取结果
    std::string await_resume() const noexcept {
        std::cout << "    [awaiter] await_resume: coroutine resumed, returning result\n";
        return "awaiter result: " + message;
    }
};


// ============================================================
// 3. 使用协程
// ============================================================

Task<std::string> simple_coroutine() {
    std::cout << "\n  --- coroutine started ---\n";

    // co_await 一个自定义 awaiter
    std::cout << "  about to co_await PrintAwaiter...\n";
    std::string result = co_await PrintAwaiter{"Hello, Coroutine!"};
    std::cout << "  co_await returned: " << result << "\n";

    std::cout << "  --- coroutine about to return ---\n";
    co_return result;
}


// ============================================================
// 4. 主函数
// ============================================================

int main() {
    std::cout << "=== C++20 Coroutine Basics ===\n\n";

    std::cout << "1. Creating coroutine...\n";
    auto task = simple_coroutine();
    // 由于 initial_suspend 返回 suspend_never，协程会立即开始执行

    std::cout << "\n2. Check coroutine state: done=" << std::boolalpha << task.done() << "\n";

    std::cout << "3. Get result: " << task.result() << "\n";

    std::cout << "\n=== Execution Flow Summary ===\n";
    std::cout << "  1. Call simple_coroutine() -> compiler allocates coroutine frame\n";
    std::cout << "  2. Construct promise_type -> call get_return_object() to return Task\n";
    std::cout << "  3. initial_suspend() -> suspend_never -> start executing body immediately\n";
    std::cout << "  4. co_await PrintAwaiter:\n";
    std::cout << "     a. await_ready() -> false -> must suspend\n";
    std::cout << "     b. await_suspend(handle) -> run custom logic, then resume\n";
    std::cout << "     c. await_resume() -> return result to co_await expression\n";
    std::cout << "  5. co_return -> return_value() -> store result in promise\n";
    std::cout << "  6. final_suspend() -> suspend_always -> coroutine suspended awaiting destruction\n";

    return 0;
}
