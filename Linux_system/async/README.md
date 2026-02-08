# 异步编程系统学习

## 前言

我希望系统地学习和总结异步编程知识，至少包括如下方面：
1. 为什么需要引入 async 异步编程，其用于解决什么问题
2. 常见语言如 C++、Python、Rust 的异步编程示例及运行逻辑
3. 对应示例在系统运行层面的细节运行实现，如果是 C++ 和 Rust，我希望可以深入到汇编层面；如果是 Python，则需要深入到 CPython 虚拟机字节码层面

## 编译环境

- **Host 环境**：Linux x86_64
- **Python**：解释型语言，直接在 host 运行
- **C++ / Rust**：深入汇编层面时使用 ARM64
- **ARM64 环境**：局域网 `192.168.3.15`（树莓派），可登录编译执行

---

## 目录结构

```
async/
├── README.md                          ← 本文件（总纲 + 学习计划）
│
├── 01_why_async/                      第一章：为什么需要异步
│   ├── README.md                      概念讲解
│   ├── blocking_io.py                 同步阻塞示例
│   ├── multithread_io.py              多线程方案
│   └── async_io.py                    异步方案（对比效果）
│
├── 02_language_examples/              第二章：各语言异步示例
│   ├── README.md                      核心概念三语言对照表
│   ├── python/
│   │   ├── basic_coroutine.py         async/await 基础
│   │   ├── future_and_task.py         Future, Task, gather
│   │   └── producer_consumer.py       asyncio.Queue 实战
│   ├── cpp/
│   │   ├── CMakeLists.txt
│   │   ├── basic_coroutine.cpp        C++20 co_await / co_return
│   │   ├── future_promise.cpp         std::future / std::promise
│   │   └── generator.cpp             co_yield 生成器
│   └── rust/
│       ├── Cargo.toml
│       └── src/
│           ├── basic_async.rs         async/await + tokio
│           ├── future_impl.rs         手写 Future trait
│           └── select_join.rs         tokio::select! / join!
│
└── 03_internals/                      第三章：底层实现细节
    ├── README.md                      总览：各语言异步的本质
    ├── python/
    │   ├── bytecode_inspect.py        dis 模块查看协程字节码
    │   ├── generator_coroutine.py     从 generator 到 coroutine 的演进
    │   └── event_loop_mini.py         手写迷你 event loop (~100行)
    ├── cpp/
    │   ├── CMakeLists.txt
    │   ├── coroutine_transform.cpp    编译器协程变换分析
    │   ├── Makefile                   生成汇编输出
    │   └── README.md                  汇编层面详细讲解
    └── rust/
        ├── Cargo.toml
        ├── src/
        │   ├── state_machine.rs       手动实现 Future 状态机
        │   ├── pin_unpin.rs           Pin/Unpin 机制详解
        │   └── mini_executor.rs       手写最小 executor (~80行)
        └── README.md                  汇编分析 + 状态机讲解
```

---

## 学习计划

### 第一章：为什么需要异步编程

> 核心问题：I/O 等待中的 CPU 浪费

**知识要点：**

| 主题 | 内容 |
|------|------|
| 问题根源 | 同步阻塞模型中，线程等待 I/O 时 CPU 完全空转 |
| 延迟鸿沟 | CPU 1ns vs 网络 50ms（差 5000 万倍） |
| 方案演进 | 多进程 → 多线程 → I/O 多路复用 → 协程 |
| 核心概念 | 并发 vs 并行、阻塞 vs 非阻塞、协程 vs 线程 |

**解决方案演进路线：**

```
单线程同步阻塞
     │  并发需求增长
     ▼
多进程 (fork)
     │  进程开销太大（~MB 级内存），IPC 复杂
     ▼
多线程 (pthread)
     │  线程栈 ~8MB，上下文切换需内核介入，同步原语复杂
     ▼
I/O 多路复用 (select → poll → epoll/kqueue)
     │  事件驱动但回调地狱，代码逻辑碎片化
     ▼
协程 + async/await
     用同步的写法实现异步的性能
```

**实践：** 运行三个 Python 脚本，定量对比同步/多线程/异步的性能差异。

---

### 第二章：各语言异步编程示例

> 核心目标：掌握 Python / C++ / Rust 三种语言的异步编程模型

**核心概念对照：**

| 概念 | Python | C++ | Rust |
|------|--------|-----|------|
| 协程定义 | `async def fn()` | `Task<T> fn() { co_return; }` | `async fn foo() -> T` |
| 挂起/等待 | `await expr` | `co_await expr` | `expr.await` |
| 产出值 | `yield value` | `co_yield value` | 无直接等价（用 Stream） |
| Future/Promise | `asyncio.Future` | `std::future / std::promise` | `Future` trait |
| 运行时 | `asyncio` event loop | 无标准运行时 | `tokio` / `async-std` |
| 并发等待 | `asyncio.gather()` | 无标准实现 | `tokio::join!` |
| 竞争模式 | `asyncio.wait(FIRST_COMPLETED)` | 无标准实现 | `tokio::select!` |

**关键区别：**

- **惰性 vs 立即**：Rust 严格惰性（调用 async fn 不执行任何代码）；Python 创建协程对象后可通过 create_task 调度；C++ 取决于 initial_suspend
- **运行时**：Python/Rust 有标准或事实标准运行时；C++ 需自建或用第三方库
- **内存模型**：Python 靠 GC；C++ 协程帧在堆上（RAII）；Rust 状态机在栈上（所有权系统）

**实践：** 每种语言 3 个由浅入深的示例，附详细注释说明执行流程。

---

### 第三章：底层实现细节

> 核心目标：理解 async/await 在各语言底层的真实实现机制

**三种语言的变换方式：**

```
              Python              C++                Rust
              ──────              ───                ────
语法层面      async/await         co_await           async/.await

编译层面      CPython 字节码       编译器变换为        编译器变换为
              GET_AWAITABLE       协程帧+恢复函数      状态机枚举
              YIELD_VALUE/SEND

运行时层面    asyncio event loop  无标准运行时         tokio executor
              (基于 epoll)        (需自建)            (基于 epoll)

内存分配      栈帧对象(堆上,GC)   协程帧(堆上,RAII)   状态机(栈上,所有权)

系统调用      selectors→epoll     自行集成 epoll      tokio→epoll
```

#### Python 深入路线

| 步骤 | 文件 | 学习内容 |
|------|------|----------|
| 1 | `generator_coroutine.py` | 从 yield → yield from → async/await 的演进历史 |
| 2 | `bytecode_inspect.py` | 用 dis 模块反汇编，观察 GET_AWAITABLE / YIELD_VALUE / SEND 等字节码 |
| 3 | `event_loop_mini.py` | 手写 ~100 行迷你 event loop，揭示 asyncio 核心调度逻辑 |

核心洞察：**await 的本质 = 迭代器协议**（协程挂起=yield，恢复=send，完成=StopIteration）

#### C++ 深入路线

| 步骤 | 文件 | 学习内容 |
|------|------|----------|
| 1 | `coroutine_transform.cpp` | 编译器协程变换过程：协程帧分配、promise_type 生命周期 |
| 2 | `Makefile` (make asm) | 生成 `-O0` 和 `-O2` 汇编，对比观察 |
| 3 | `README.md` | 汇编层面分析：`__builtin_coro_*` intrinsics、HALO 优化 |

核心洞察：**编译器将协程体变换为 switch-case 状态机 + 堆上协程帧**

```
协程帧内存布局：
  +---------------------------+
  | resume 函数指针           |
  | destroy 函数指针          |
  | suspend_point 索引        |
  +---------------------------+
  | promise_type 对象         |
  +---------------------------+
  | 函数参数副本              |
  | 跨挂起点存活的局部变量     |
  | 当前 awaiter 对象         |
  +---------------------------+
```

#### Rust 深入路线

| 步骤 | 文件 | 学习内容 |
|------|------|----------|
| 1 | `state_machine.rs` | 手动实现等价状态机枚举，理解编译器变换 |
| 2 | `pin_unpin.rs` | 自引用结构体问题 → 为什么需要 Pin → Unpin trait |
| 3 | `mini_executor.rs` | 手写 ~80 行 executor，理解 Waker 机制 |
| 4 | `README.md` | 生成汇编并分析状态机判别标签、poll 跳转表 |

核心洞察：**async fn → 状态机枚举（零开销抽象），Pin 保证自引用安全**

```rust
// 编译器将 async fn 变换为：
enum FutureSM {
    State0 { x: i32 },                     // 初始
    State1 { a: i32, fut: SubFuture },      // 等待子 Future
    Done,
}
// 大小 = max(各状态) + 判别标签，完全在栈上
```

---

## 建议学习顺序

```
第一章                    第二章                         第三章
───────                  ───────                        ───────
                    ┌─→ Python 示例 ──────────────→ Python 字节码分析
why_async ─────────┤                                    ↓
(概念 + 对比)       ├─→ Rust 示例 ───────────────→ Rust 状态机 + Pin
                    │                                    ↓
                    └─→ C++ 示例 ────────────────→ C++ 汇编分析
```

**推荐语言顺序：Python（最直观）→ Rust（零开销抽象）→ C++（最底层最透明）**

---

## 快速运行指南

```bash
# === 第一章 ===
python3 01_why_async/blocking_io.py
python3 01_why_async/multithread_io.py
python3 01_why_async/async_io.py

# === 第二章 Python ===
python3 02_language_examples/python/basic_coroutine.py
python3 02_language_examples/python/future_and_task.py
python3 02_language_examples/python/producer_consumer.py

# === 第二章 C++ (需要 GCC 11+ 或 Clang 14+) ===
cd 02_language_examples/cpp && mkdir -p build && cd build
cmake .. && make
./basic_coroutine && ./future_promise && ./generator

# === 第二章 Rust ===
cd 02_language_examples/rust
cargo run --bin basic_async
cargo run --bin future_impl
cargo run --bin select_join

# === 第三章 Python ===
python3 03_internals/python/generator_coroutine.py
python3 03_internals/python/bytecode_inspect.py
python3 03_internals/python/event_loop_mini.py

# === 第三章 C++ (汇编分析) ===
cd 03_internals/cpp
make run       # 运行程序
make asm       # 生成 -O0 汇编
make asm-opt   # 生成 -O2 汇编

# === 第三章 Rust ===
cd 03_internals/rust
cargo run --bin state_machine
cargo run --bin pin_unpin
cargo run --bin mini_executor
```