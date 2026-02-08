/**
 * C++20 协程的编译器变换过程
 *
 * 本文件展示编译器如何将协程函数变换为状态机。
 * 包含两部分：
 *   1. 一个简单的协程函数
 *   2. 等价的手动变换结果（编译器内部做的事）
 *
 * 编译命令（生成汇编）：
 *   g++ -std=c++20 -fcoroutines -O0 -S -o coroutine_transform.s coroutine_transform.cpp
 *   g++ -std=c++20 -fcoroutines -O2 -S -o coroutine_transform_opt.s coroutine_transform.cpp
 *
 * 对比 -O0 和 -O2 的汇编输出，观察 HALO (Heap Allocation eLision Optimization) 优化。
 */

#include <coroutine>
#include <iostream>
#include <cstdlib>
#include <cstring>

// ============================================================
// 基础设施：最简化的协程类型
// ============================================================

struct SimpleTask {
    struct promise_type {
        int result = 0;

        SimpleTask get_return_object() {
            return SimpleTask{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_value(int v) { result = v; }
        void unhandled_exception() { std::terminate(); }
    };

    std::coroutine_handle<promise_type> handle;

    int get_result() {
        handle.resume();  // 执行到完成
        return handle.promise().result;
    }

    ~SimpleTask() { if (handle) handle.destroy(); }
};

// 一个总是挂起并返回指定值的 awaiter
struct SuspendAndReturn {
    int value;
    bool await_ready() noexcept { return false; }
    void await_suspend(std::coroutine_handle<>) noexcept {}
    int await_resume() noexcept { return value; }
};


// ============================================================
// 1. 原始协程函数
// ============================================================

/**
 * 这个简单的协程函数会被编译器变换。
 * 我们来分析编译器做了什么。
 */
SimpleTask original_coroutine(int x) {
    int a = x + 1;
    int b = co_await SuspendAndReturn{a * 2};
    co_return a + b;
}


// ============================================================
// 2. 编译器变换的等价代码（伪代码形式）
// ============================================================

/**
 * 编译器将上面的 original_coroutine 大致变换为如下形式。
 *
 * 注意：这是概念性的等价代码，不是精确的编译器输出，
 * 但展示了编译器做的核心变换。
 */

// 协程帧 —— 在堆上分配，保存协程的所有状态
struct CoroutineFrame {
    // --- 编译器生成的管理字段 ---
    void (*resume_fn)(CoroutineFrame*);   // 恢复函数指针
    void (*destroy_fn)(CoroutineFrame*);  // 销毁函数指针
    int suspend_point;                      // 当前挂起点索引

    // --- promise 对象 ---
    SimpleTask::promise_type promise;

    // --- 函数参数 ---
    int x;

    // --- 局部变量 ---
    int a;
    int b;

    // --- 临时 awaiter 对象 ---
    SuspendAndReturn awaiter;
};

/**
 * 变换后的恢复函数 —— 这是编译器生成的核心代码
 *
 * 原始协程体被拆分为多个 case，每个挂起点一个。
 * resume() 根据 suspend_point 跳转到正确的位置继续执行。
 */
void transformed_resume(CoroutineFrame* frame) {
    switch (frame->suspend_point) {
    case 0:
        // === initial_suspend 后的恢复点 ===
        // 执行 int a = x + 1;
        frame->a = frame->x + 1;

        // 执行 co_await SuspendAndReturn{a * 2}:
        // 1. 创建 awaiter
        frame->awaiter = SuspendAndReturn{frame->a * 2};

        // 2. 调用 await_ready()
        if (!frame->awaiter.await_ready()) {
            // 3. 需要挂起
            frame->suspend_point = 1;  // 记录恢复点
            frame->awaiter.await_suspend(
                std::coroutine_handle<SimpleTask::promise_type>::from_promise(frame->promise)
            );
            return;  // 挂起：返回给调用者
        }
        [[fallthrough]];
        // 如果 await_ready() 返回 true，直接进入 case 1

    case 1:
        // === co_await 后的恢复点 ===
        // 4. 调用 await_resume() 获取结果
        frame->b = frame->awaiter.await_resume();

        // 执行 co_return a + b;
        frame->promise.return_value(frame->a + frame->b);

        // 执行 final_suspend
        frame->suspend_point = 2;
        // final_suspend 返回 suspend_always → 挂起
        return;

    case 2:
        // === final_suspend 后的恢复点 ===
        // 通常不会执行到这里，因为 final_suspend 后协程应该被销毁
        break;
    }
}

/**
 * 变换后的入口函数 —— 替代原始的 original_coroutine()
 */
SimpleTask transformed_coroutine_entry(int x) {
    // 1. 在堆上分配协程帧
    auto* frame = new CoroutineFrame{};
    frame->resume_fn = transformed_resume;
    frame->suspend_point = 0;

    // 2. 保存参数
    frame->x = x;

    // 3. 构造 promise
    // （promise 已在 new 时默认构造）

    // 4. 调用 get_return_object()
    auto task = frame->promise.get_return_object();

    // 5. initial_suspend
    // suspend_always → 立即挂起，不执行函数体
    // 控制权返回给调用者

    return task;
}


// ============================================================
// 3. 主函数 —— 对比运行
// ============================================================

int main() {
    std::cout << "=== C++20 协程编译器变换分析 ===\n\n";

    // 使用原始协程
    std::cout << "1. 原始协程:\n";
    auto task = original_coroutine(10);
    // initial_suspend 后协程挂起
    // resume 开始执行：a=11, await SuspendAndReturn{22}
    // 挂起（await_ready=false）
    task.handle.resume();   // 第一次 resume: 执行到 co_await 挂起
    task.handle.resume();   // 第二次 resume: 从 co_await 恢复，执行 co_return
    std::cout << "   结果: " << task.handle.promise().result << "\n\n";

    std::cout << "2. 编译器变换等价代码:\n";
    std::cout << "   (见源代码注释中的详细分析)\n\n";

    std::cout << "=== 编译器变换总结 ===\n\n";

    std::cout << "协程帧 (Coroutine Frame) 内存布局:\n";
    std::cout << "  +---------------------------+\n";
    std::cout << "  | resume 函数指针           | → 恢复执行的入口\n";
    std::cout << "  | destroy 函数指针          | → 销毁帧的入口\n";
    std::cout << "  | suspend_point (int)       | → 当前挂起点索引\n";
    std::cout << "  +---------------------------+\n";
    std::cout << "  | promise_type 对象         | → 协程的返回值/异常\n";
    std::cout << "  +---------------------------+\n";
    std::cout << "  | 函数参数 (x)              | → 跨挂起点存活的参数\n";
    std::cout << "  | 局部变量 (a, b)           | → 跨挂起点存活的局部变量\n";
    std::cout << "  | awaiter 对象              | → 当前 co_await 的 awaiter\n";
    std::cout << "  +---------------------------+\n\n";

    std::cout << "关键变换步骤:\n";
    std::cout << "  1. 分配协程帧 (operator new) → 所有状态上堆\n";
    std::cout << "  2. 函数体变为 switch-case 状态机\n";
    std::cout << "  3. 每个 co_await 是一个挂起点 (suspend point)\n";
    std::cout << "  4. resume() 通过 suspend_point 索引跳转到正确位置\n";
    std::cout << "  5. 编译器可能通过 HALO 优化消除堆分配\n\n";

    std::cout << "GCC 内部使用的 intrinsics:\n";
    std::cout << "  __builtin_coro_id()      → 获取协程 ID\n";
    std::cout << "  __builtin_coro_alloc()   → 是否需要分配帧\n";
    std::cout << "  __builtin_coro_noop()    → 空操作协程句柄\n";
    std::cout << "  __builtin_coro_free()    → 获取帧指针以释放\n";
    std::cout << "  __builtin_coro_size()    → 协程帧大小\n";
    std::cout << "  __builtin_coro_begin()   → 帧分配后的入口\n";
    std::cout << "  __builtin_coro_end()     → 协程结束标记\n";
    std::cout << "  __builtin_coro_suspend() → 挂起点\n";
    std::cout << "  __builtin_coro_resume()  → 恢复协程\n";
    std::cout << "  __builtin_coro_destroy() → 销毁协程帧\n";
    std::cout << "  __builtin_coro_done()    → 检查协程是否完成\n";
    std::cout << "  __builtin_coro_promise() → 获取 promise 对象指针\n";

    return 0;
}
