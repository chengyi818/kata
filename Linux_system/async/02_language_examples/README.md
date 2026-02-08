# 第二章：各语言异步编程示例

## 核心概念三语言对照表

| 概念 | Python | C++ | Rust |
|------|--------|-----|------|
| **协程定义** | `async def fn()` | `Task<T> fn() { co_return; }` | `async fn foo() -> T` |
| **挂起/等待** | `await expr` | `co_await expr` | `expr.await` |
| **产出值** | `yield value` | `co_yield value` | 无直接等价（用 Stream） |
| **Future/Promise** | `asyncio.Future` | `std::future` / `std::promise` | `Future` trait |
| **任务** | `asyncio.Task` | 无标准实现 | `tokio::task::JoinHandle` |
| **运行时** | `asyncio` event loop | 无标准运行时 | `tokio` / `async-std` |
| **并发等待全部** | `asyncio.gather()` | 无标准实现 | `tokio::join!` |
| **竞争/首个完成** | `asyncio.wait(FIRST_COMPLETED)` | 无标准实现 | `tokio::select!` |
| **生成器** | `def gen(): yield` | `Generator<T> gen() { co_yield; }` | `Stream` trait |
| **底层实现** | CPython 字节码 + event loop | 编译器协程帧变换 | 编译器状态机变换 |

## 关键区别

### 1. 协程的本质

```
Python:  协程 = 生成器的扩展（基于字节码 YIELD_VALUE/SEND）
         运行在 CPython 虚拟机中，有 GIL 限制
         async/await 是 yield from 的语法糖

C++:     协程 = 编译器变换（分配协程帧，在堆上保存状态）
         标准只定义机制，不提供运行时
         需要手写 promise_type + awaiter 或使用第三方库

Rust:    协程 = 编译器生成的状态机枚举（栈上分配，零堆开销）
         标准只提供 Future trait，运行时由 tokio 等提供
         Pin 机制解决自引用问题
```

### 2. 惰性 (Lazy) vs 立即 (Eager)

```
Python:  调用 async def 返回协程对象（惰性），
         但 create_task() 后立即在 event loop 中调度

C++:     取决于 initial_suspend() 的返回值：
         suspend_always → 惰性（需要手动 resume）
         suspend_never  → 立即开始执行

Rust:    严格惰性——调用 async fn 只创建 Future，不执行任何代码
         必须 .await 或 tokio::spawn() 才会开始执行
         这是与 Python/JS 最大的区别之一
```

### 3. 运行时

```
Python:  asyncio 是标准库的一部分
         event loop 基于 I/O 多路复用 (selectors / epoll)
         单线程执行所有协程

C++:     标准库不提供异步运行时
         std::future/promise 是线程级的，不是协程级的
         协程运行时需要自建或使用 boost::asio, cppcoro 等

Rust:    标准库只提供 Future trait 和 async/await 语法
         tokio 是事实上的标准运行时：
           - 多线程工作窃取调度器
           - 基于 epoll/kqueue/IOCP 的 I/O 驱动
           - 定时器、channel、同步原语等
```

### 4. 内存模型

```
Python:  协程状态保存在 CPython 的栈帧对象中
         栈帧在堆上分配，由 GC 管理
         内存开销：数百字节到 KB 级

C++:     协程帧 (coroutine frame) 在堆上分配
         包含：promise 对象、函数参数、局部变量、挂起点索引
         编译器可能优化掉堆分配（HALO 优化）

Rust:    Future 状态机在栈上分配（默认）
         tokio::spawn 时移到堆上
         大小 = max(各状态分支的大小) + 状态判别标签
         无 GC，由所有权系统管理生命周期
```

## 运行示例

### Python
```bash
cd python/
python basic_coroutine.py
python future_and_task.py
python producer_consumer.py
```

### C++
```bash
cd cpp/
mkdir -p build && cd build
cmake .. && make
./basic_coroutine
./future_promise
./generator
```

### Rust
```bash
cd rust/
cargo run --bin basic_async
cargo run --bin future_impl
cargo run --bin select_join
```

## 学习路径建议

1. **先学 Python**：语法最简洁，概念最直观，快速建立异步编程的心智模型
2. **再学 Rust**：理解 Future trait 和状态机变换，体会零开销抽象
3. **最后学 C++**：需要理解 promise_type 和 awaiter 的底层机制，最复杂但也最透明
