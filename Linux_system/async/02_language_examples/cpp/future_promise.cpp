/**
 * C++ std::future 与 std::promise
 *
 * 这是 C++11 引入的线程间通信机制，与 C++20 协程是不同的概念。
 *
 * 核心思想：
 *   - std::promise: 结果的"写入端"，生产者在另一个线程设置值
 *   - std::future:  结果的"读取端"，消费者等待值就绪
 *   - 两者通过共享状态 (shared state) 连接
 *
 * 类比：
 *   promise 像一个信封的"写入口"，future 像"读取口"
 *   生产者往信封里塞结果，消费者从信封里取结果
 */

#include <future>
#include <thread>
#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>
#include <stdexcept>

using namespace std::chrono_literals;


// ============================================================
// 1. 基本的 promise/future 用法
// ============================================================

void demo_basic_promise_future() {
    std::cout << "=== 1. Basic promise/future ===\n\n";

    // 创建 promise 并获取关联的 future
    std::promise<std::string> promise;
    std::future<std::string> future = promise.get_future();

    // 在另一个线程中设置结果
    std::thread producer([&promise]() {
        std::cout << "  [producer thread] working...\n";
        std::this_thread::sleep_for(500ms);  // 模拟耗时操作
        promise.set_value("result from producer");
        std::cout << "  [producer thread] result set\n";
    });

    // 在主线程中等待结果
    std::cout << "  [main thread] waiting for result...\n";
    std::string result = future.get();  // 阻塞直到结果就绪
    std::cout << "  [main thread] got result: " << result << "\n\n";

    producer.join();
}


// ============================================================
// 2. std::async —— 简化版的 future
// ============================================================

int compute_sum(int from, int to) {
    std::cout << "  [compute thread] computing sum from " << from << " to " << to << "...\n";
    int sum = 0;
    for (int i = from; i <= to; ++i) sum += i;
    std::this_thread::sleep_for(300ms);  // 模拟耗时
    return sum;
}

void demo_std_async() {
    std::cout << "=== 2. std::async ===\n\n";

    // std::async 自动创建线程并返回 future
    // 启动策略：
    //   std::launch::async    —— 强制在新线程中执行
    //   std::launch::deferred —— 延迟到 future.get() 时在当前线程执行

    auto future1 = std::async(std::launch::async, compute_sum, 1, 50000);
    auto future2 = std::async(std::launch::async, compute_sum, 50001, 100000);

    std::cout << "  [main thread] two compute tasks launched, waiting...\n";

    int result1 = future1.get();
    int result2 = future2.get();

    std::cout << "  [main thread] result1: " << result1 << "\n";
    std::cout << "  [main thread] result2: " << result2 << "\n";
    std::cout << "  [main thread] total: " << result1 + result2 << "\n\n";

    // 对比 deferred
    std::cout << "--- launch::deferred mode ---\n";
    auto lazy_future = std::async(std::launch::deferred, []() {
        std::cout << "  [deferred] this runs only when get() is called\n";
        return 42;
    });
    std::cout << "  [main thread] future created, function not yet executed\n";
    std::cout << "  [main thread] calling get()...\n";
    std::cout << "  [main thread] result: " << lazy_future.get() << "\n\n";
}


// ============================================================
// 3. promise 传递异常
// ============================================================

void demo_exception_propagation() {
    std::cout << "=== 3. Exception Propagation ===\n\n";

    std::promise<int> promise;
    std::future<int> future = promise.get_future();

    std::thread worker([&promise]() {
        try {
            // 模拟一个失败的操作
            throw std::runtime_error("operation failed: connection timeout");
        } catch (...) {
            // 将异常传递给 future
            promise.set_exception(std::current_exception());
        }
    });

    try {
        int result = future.get();  // 这会重新抛出异常
        std::cout << "  result: " << result << "\n";
    } catch (const std::exception& e) {
        std::cout << "  [main thread] caught exception: " << e.what() << "\n";
        std::cout << "  exception propagated from worker thread to main thread!\n\n";
    }

    worker.join();
}


// ============================================================
// 4. shared_future —— 多个消费者
// ============================================================

void demo_shared_future() {
    std::cout << "=== 4. shared_future (multiple consumers) ===\n\n";

    std::promise<int> promise;
    // shared_future 允许多个线程同时等待同一个结果
    std::shared_future<int> shared = promise.get_future().share();

    std::vector<std::thread> consumers;
    for (int i = 0; i < 3; ++i) {
        consumers.emplace_back([shared, i]() {
            std::cout << "  [consumer " << i << "] waiting for result...\n";
            int result = shared.get();  // 所有消费者都能 get()
            std::cout << "  [consumer " << i << "] got result: " << result << "\n";
        });
    }

    std::this_thread::sleep_for(300ms);
    promise.set_value(42);
    std::cout << "  [producer] result set\n";

    for (auto& t : consumers) t.join();
    std::cout << "\n";
}


// ============================================================
// 5. std::packaged_task —— 将函数包装为异步任务
// ============================================================

void demo_packaged_task() {
    std::cout << "=== 5. std::packaged_task ===\n\n";

    // packaged_task 将一个可调用对象与 promise 绑定
    // 调用 packaged_task 时自动 set_value/set_exception
    std::packaged_task<int(int, int)> task([](int a, int b) {
        std::this_thread::sleep_for(200ms);
        return a + b;
    });

    std::future<int> future = task.get_future();

    // 可以把 task 移动到另一个线程执行
    std::thread worker(std::move(task), 10, 20);

    std::cout << "  [main thread] waiting for packaged_task result...\n";
    std::cout << "  [main thread] result: " << future.get() << "\n\n";

    worker.join();
}


// ============================================================
// 主函数
// ============================================================

int main() {
    std::cout << "=== C++ std::future / std::promise ===\n\n";

    demo_basic_promise_future();
    demo_std_async();
    demo_exception_propagation();
    demo_shared_future();
    demo_packaged_task();

    std::cout << "=== Summary ===\n";
    std::cout << "  promise/future: one-shot result passing between threads\n";
    std::cout << "  std::async:     simplified -- auto-manages thread and future\n";
    std::cout << "  shared_future:  multiple consumers can wait for the same result\n";
    std::cout << "  packaged_task:  wraps a callable as an async task\n";
    std::cout << "\n";
    std::cout << "  Note: these are C++11 thread-level concurrency primitives,\n";
    std::cout << "  a different abstraction layer from C++20 coroutines (co_await).\n";
    std::cout << "  future.get() blocks the thread, while co_await only suspends the coroutine.\n";

    return 0;
}
