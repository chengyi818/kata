# 异步编程系统学习

## 前言

我希望系统地学习和总结异步编程知识，至少包括如下方面：
1. 为什么需要引入 async 异步编程，其用于解决什么问题
2. 常见语言如 C++、Python、Rust 的异步编程示例及运行逻辑
3. 对应示例在系统运行层面的细节运行实现，如果是 C++ 和 Rust，我希望可以深入到汇编层面；如果是 Python，则需要深入到 CPython 虚拟机字节码层面

## 学习者背景

**假设学习者熟悉：**
- Linux 进程/线程管理（fork/pthread等）
- 内核机制（调度器、内存管理等）
- 设备驱动开发

**核心学习策略：** 通过Linux内核概念类比来理解async编程

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
└── 04_Ref/                            第四章：扩展阅读与参考
    ├── python.md                      Python async/await、Future/Task、多任务控制推荐阅读
    ├── cpp.md                         C++11/20 future/promise、async/packaged_task、folly Future 扩展阅读
    └── rust.md                        Rust Runtime/Pin、Tokio、async fn in traits 扩展阅读
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

### 基于Linux系统编程背景的学习路径

**核心类比表（建议先理解）：**

| async编程概念 | Linux内核类比 | 关键区别 |
|---------------|---------------|----------|
| **Event Loop** | 进程调度器 | 用户态vs内核态 |
| **协程** | 轻量级进程 | KB级vsMB级内存 |
| **await** | `schedule()`让出CPU | 主动让出vs抢占 |
| **Future** | 等待队列(wait_queue) | 用户态vs内核态 |
| **epoll** | Event Loop的I/O驱动 | 系统调用vs用户态调度 |

**详细类比对照：**

```
Linux内核                          async编程
────────                          ────────
进程调度器                        Event Loop
进程描述符(task_struct)           Task
等待队列(wait_queue)              Future
epoll_wait()                      Event Loop等待事件
时钟中断                          await让出CPU
fork()创建进程                    创建协程
wait()等待子进程                  await gather()
```

### 第一阶段：建立直观感受（1-2天）

**目标：** 理解"为什么需要异步"，建立性能对比的直观感受

```bash
# 运行这三个脚本，观察耗时差异
python3 01_why_async/blocking_io.py        # 串行执行，5s
python3 01_why_async/multithread_io.py     # 多线程并行，1s，但有5个线程
python3 01_why_async/async_io.py           # 单线程异步，1s，只有1个线程
```

**思考题（用Linux知识回答）：**
1. 多线程方案中，5个线程各自需要多少栈空间？总内存开销是多少？
2. 线程切换需要内核介入吗？协程切换呢？
3. 为什么异步方案只用1个线程就能达到多线程的效果？

### 第二阶段：理解核心概念（2-3天）

**目标：** 理解协程、Future、Event Loop的本质

```bash
# 运行基础示例
python3 02_language_examples/python/basic_coroutine.py
python3 02_language_examples/python/future_and_task.py
```

**关键类比理解：**

1. **协程函数 ≈ fork()**
   - `async def fn()` 调用时返回协程对象，但不执行（类似fork创建子进程但不立即运行）
   - 必须await或交给Event Loop才会执行

2. **await ≈ schedule()**
   - `await future` 主动让出CPU，让其他协程运行
   - 类似进程调用schedule()让出CPU

3. **Future ≈ 等待队列**
   - `await future` 挂起协程，直到set_result被调用
   - 类似wait_event()挂起进程，直到wake_up()

### 第三阶段：深入底层实现（3-5天）

**目标：** 理解Event Loop如何工作，对比内核调度器

```bash
# 运行迷你Event Loop实现
python3 03_internals/python/event_loop_mini.py
```

**核心洞察（用Linux知识理解）：**

1. **Event Loop ≈ 调度器**
   ```python
   # Event Loop核心循环（类似内核调度器）
   while not self._stopping:
       # 1. 检查定时器（类似检查时间片）
       # 2. 执行就绪队列（类似运行就绪进程）
       # 3. sleep等待（类似schedule()）
   ```

2. **协程切换 ≈ 用户态上下文切换**
   - 协程切换在用户态完成，只需保存少量状态
   - 线程切换需要内核态，保存/恢复寄存器、TLB刷新

3. **epoll是底层实现**
   - asyncio的Event Loop底层使用epoll（Linux）
   - 类似你熟悉的网络编程中的epoll_wait

### 第四阶段：实战应用（2-3天）

**目标：** 使用asyncio解决实际问题

```bash
# 运行生产者-消费者示例
python3 02_language_examples/python/producer_consumer.py
```

**思考题：**
1. asyncio.Queue如何实现线程安全？
2. Semaphore如何限制并发数？
3. 如何优雅地取消协程？

### 第五阶段：跨语言对比（可选，5-7天）

**目标：** 理解不同语言的异步实现差异

```bash
# Rust示例
cd 02_language_examples/rust
cargo run --bin basic_async

# C++示例
cd 02_language_examples/cpp && mkdir -p build && cd build
cmake .. && make && ./basic_coroutine
```

**关键区别：**
- Python：协程基于生成器协议（yield/send）
- Rust：协程是状态机枚举（零开销抽象）
- C++：协程是编译器变换（协程帧+恢复函数）

---

### 传统学习顺序

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

## 第四章：扩展阅读与参考（04_Ref）

> 在完成前三章代码与讲解后，推荐按「语言 → 深度」查阅 `04_Ref/` 下的扩展阅读，巩固并拓展视野。

**整体定位：** 04_Ref 不是必读源码，而是「**精选高质量文章 + 本仓库示例对应关系 + 建议阅读顺序**」：

- `04_Ref/python.md`：\n  - 汇总多篇关于 Python async/await、事件循环、Task/Future、多任务控制（gather、wait）的文章。  \n  - 已按「第一步：async/await 基本模型 → 第二步：Future/Task → 第三步：并发模式与实践」排序，可在跑完 `02_language_examples/python` 和 `03_internals/python` 后阅读。
- `04_Ref/cpp.md`：\n  - 围绕 `std::promise/future`、`std::async`、`std::packaged_task` 以及 folly Future/Promise，整理了多篇博文（含 CSDN/博客园/folly 教程），并给出**建议学习顺序**。  \n  - 补充了 C++11 多线程同步（`wait_for` 超时）、实现原理、then/when_all 等内容，可在看完 `02_language_examples/cpp` 与 `03_internals/cpp` 后作为纵深阅读。
- `04_Ref/rust.md`：\n  - 围绕 Rust 异步 Runtime 设计（Monoio、epoll/io-uring、Reactor/Executor/Waker）、Pin/Unpin、Tokio 使用与源码、async fn in traits（AFIT）等内容整理了推荐阅读清单。  \n  - 文内已给出推荐顺序：**运行时与 Future 模型 → Pin/Unpin → 深入浅出 Tokio → Tokio Internals 源码解析 → AFIT/GAT/dyn**，与 `02_language_examples/rust` 与 `03_internals/rust` 精读路线强关联。

**使用建议：**

- 若你刚完成某语言的第二、三章，可以直接跳到对应的 `04_Ref/*.md`，按其中的**「学习顺序表」**先挑 1–2 篇读，重点看「要点总结」部分，再决定是否精读原文。
- 若你在实际工程中需要更深入的理解（例如自实现 Runtime、自定义 async trait 接口、调试 Tokio 行为），优先阅读 Rust/C++ 对应的 `04_Ref` 文档。

---

## 快速运行指南

```bash
# === 第一阶段：建立直观感受 ===
python3 01_why_async/blocking_io.py        # 同步阻塞：5s
python3 01_why_async/multithread_io.py     # 多线程：1s（5个线程）
python3 01_why_async/async_io.py           # 异步：1s（1个线程）

# === 第二阶段：理解核心概念 ===
python3 02_language_examples/python/basic_coroutine.py
python3 02_language_examples/python/future_and_task.py

# === 第三阶段：深入底层实现 ===
python3 03_internals/python/event_loop_mini.py  # 手写Event Loop

# === 第四阶段：实战应用 ===
python3 02_language_examples/python/producer_consumer.py

# === 第五阶段：跨语言对比（可选） ===
# Python深入
python3 03_internals/python/generator_coroutine.py
python3 03_internals/python/bytecode_inspect.py

# Rust
cd 02_language_examples/rust
cargo run --bin basic_async
cargo run --bin future_impl
cargo run --bin select_join

# C++ (需要 GCC 11+ 或 Clang 14+)
cd 02_language_examples/cpp && mkdir -p build && cd build
cmake .. && make
./basic_coroutine && ./future_promise && ./generator
```

### 给Linux系统编程背景学习者的建议

1. **先运行示例，建立直观感受**
   - 不要急于理解原理，先观察现象
   - 对比同步/多线程/异步的性能差异

2. **用Linux内核概念类比**
   - Event Loop ≈ 调度器
   - 协程 ≈ 用户态线程
   - await ≈ 让出CPU
   - Future ≈ 等待队列

3. **重点关注用户态vs内核态的区别**
   - 协程切换在用户态，轻量级
   - 线程切换在内核态，重量级

4. **理解epoll是底层实现**
   - asyncio底层使用epoll
   - 类似你熟悉的网络编程

5. **实践是最好的学习方式**
   - 修改示例代码，观察行为变化
   - 尝试实现自己的迷你Event Loop