# C++20 协程汇编层面分析

## 编译器变换概述

当你写一个 C++20 协程函数时，编译器执行以下变换：

### 1. 协程帧分配

```cpp
// 你写的代码
SimpleTask my_coro(int x) {
    int a = x + 1;
    int b = co_await some_awaiter;
    co_return a + b;
}

// 编译器生成的伪代码
SimpleTask my_coro(int x) {
    // 1. 分配协程帧
    void* frame_mem = operator new(sizeof(coroutine_frame));
    auto* frame = new (frame_mem) coroutine_frame{};

    // 2. 保存参数到帧中
    frame->x = x;

    // 3. 构造 promise
    auto& promise = frame->promise;

    // 4. 获取返回对象
    auto return_obj = promise.get_return_object();

    // 5. initial_suspend
    co_await promise.initial_suspend();

    // 6. 执行函数体（变换为状态机）
    try {
        // ... 状态机代码 ...
    } catch (...) {
        promise.unhandled_exception();
    }

    // 7. final_suspend
    co_await promise.final_suspend();
}
```

### 2. 状态机变换

每个 `co_await` 表达式创建一个挂起点 (suspend point)。
编译器将函数体拆分为状态机：

```
suspend_point = 0 (initial)
    │
    ▼
执行代码直到第一个 co_await
    │
    ├─ await_ready() == true ──→ 直接获取结果
    │
    └─ await_ready() == false
        │
        ▼
    suspend_point = 1
    await_suspend(handle)
    return (挂起)
        │
        ▼  (被 resume 调用)
    suspend_point == 1:
    result = await_resume()
    继续执行...
```

## 生成和分析汇编

### 使用 Makefile

```bash
# 生成未优化汇编（保留完整的变换细节）
make asm

# 生成优化后汇编（观察 HALO 优化）
make asm-opt

# 生成反汇编
make all && make disasm
```

### 手动编译

```bash
# 未优化（看清楚每一步变换）
g++ -std=c++20 -fcoroutines -O0 -S -fverbose-asm -o output_O0.s coroutine_transform.cpp

# 优化后（看编译器怎么优化协程）
g++ -std=c++20 -fcoroutines -O2 -S -fverbose-asm -o output_O2.s coroutine_transform.cpp
```

### 在汇编中寻找什么

#### a) 协程帧分配

在 `-O0` 汇编中查找：
```asm
call    operator new(unsigned long)    # 协程帧堆分配
```

在 `-O2` 汇编中，如果编译器能证明协程的生命周期不超过调用者，
HALO (Heap Allocation eLision Optimization) 可能消除这个分配。

#### b) 恢复函数

查找协程的 resume 函数（通常包含 `.resume` 或 `actor` 后缀）：
```asm
original_coroutine(int)::_Z19original_coroutinei.resume:
    # 这是编译器生成的恢复函数
    # 包含 switch-case 状态机
```

#### c) 挂起点

查找 `__builtin_coro_suspend` 相关的代码：
```asm
    # suspend_point 保存/加载
    mov     DWORD PTR [rbp-XX], 1    # 设置 suspend_point = 1
    ret                               # 返回（挂起）
```

#### d) 协程 intrinsics

GCC 使用以下 intrinsics 实现协程：

| Intrinsic | 作用 | 对应汇编 |
|-----------|------|----------|
| `__builtin_coro_id` | 获取协程 ID | 通常内联 |
| `__builtin_coro_alloc` | 检查是否需要分配 | 条件跳转 |
| `__builtin_coro_size` | 获取帧大小 | 立即数 |
| `__builtin_coro_begin` | 帧分配后入口 | 标签 |
| `__builtin_coro_suspend` | 挂起点 | 保存状态 + ret |
| `__builtin_coro_resume` | 恢复协程 | 间接调用 resume_fn |
| `__builtin_coro_done` | 检查是否完成 | 检查 suspend_point |
| `__builtin_coro_free` | 获取帧指针 | 加载指针 |
| `__builtin_coro_destroy` | 销毁帧 | 间接调用 destroy_fn |

## 协程帧内存布局

```
偏移量   字段
──────   ──────────────────
+0x00    resume 函数指针 (void (*)(frame*))
+0x08    destroy 函数指针 (void (*)(frame*))
+0x10    suspend_point 索引 (int / index)
+0x14    padding
+0x18    promise_type 对象
+0x??    函数参数副本
+0x??    跨挂起点存活的局部变量
+0x??    当前 awaiter 对象
```

协程句柄 (`coroutine_handle<>`) 本质上就是一个指向协程帧的指针。

`handle.resume()` 等价于 `frame->resume_fn(frame)`。

## HALO 优化 (Heap Allocation eLision Optimization)

当编译器能证明以下条件时，可以将协程帧从堆移到栈上：

1. 协程的生命周期不超过其调用者
2. 协程帧大小在编译期已知
3. 协程不被移动到其他作用域

这是 C++ 协程"零开销"的关键优化之一。

对比 `-O0` 和 `-O2` 的汇编：
- `-O0`: 总是看到 `operator new` 调用
- `-O2`: 在满足条件时，帧直接在栈上分配（`sub rsp, XX`）

## Godbolt 在线实验

推荐在 [Compiler Explorer (Godbolt)](https://godbolt.org/) 上实验：
1. 选择 GCC 或 Clang
2. 添加 `-std=c++20 -fcoroutines`
3. 粘贴协程代码
4. 观察生成的汇编

在线环境可以方便地切换编译器版本和优化级别。
