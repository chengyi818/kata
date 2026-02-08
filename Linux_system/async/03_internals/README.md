# 第三章：底层实现细节

## 总览：各语言异步的本质

三种语言的 async/await 在语法层面相似，但底层实现机制截然不同：

```
                    Python              C++                 Rust
                    ──────              ───                 ────
语言层面            async/await         co_await/co_return  async/.await

编译/解释层面       CPython 字节码      编译器变换为         编译器变换为
                    GET_AWAITABLE       协程帧 + 恢复函数    状态机枚举
                    YIELD_VALUE
                    SEND

运行时层面          asyncio event loop  无标准运行时         tokio executor
                    (基于 epoll)        (需自建/第三方)      (基于 epoll)

内存模型            栈帧对象(堆上)      协程帧(堆上)         状态机(栈上)
                    GC 管理             手动/RAII            所有权系统

挂起机制            yield 传播          suspend 点返回       Poll::Pending
                    到 event loop       给调用者             返回给 executor

恢复机制            send() 沿协程链     resume() 调用        executor poll()
                    传播                恢复函数             再次调用

系统调用层面        selectors 模块      自行集成             tokio I/O driver
                    → epoll_wait        epoll/io_uring      → epoll_wait
```

## 三种变换方式的本质

### Python：字节码级别的生成器协议

```
async def foo():           CPython 字节码            执行模型
    result = await bar()   ──────────────            ────────
                           LOAD_GLOBAL bar           |
                           CALL                      | 创建协程对象
                           GET_AWAITABLE             | 获取迭代器
                           SEND None                 | 启动/恢复子协程
                           YIELD_VALUE               | 挂起，值传给 event loop
                           ...                       |
                           RETURN_VALUE              | 完成
```

### C++：编译器框架变换

```
Task<int> foo() {          编译器变换                 内存布局
    int a = 1;             ──────────                 ────────
    co_await bar();        1. 分配协程帧(堆)          +------------------+
    co_return a;           2. 保存参数+局部变量到帧    | resume_fn ptr    |
}                          3. 函数体→switch/case      | destroy_fn ptr   |
                           4. 每个 co_await 一个 case  | suspend_point    |
                                                      | promise          |
                                                      | a (局部变量)     |
                                                      | awaiter          |
                                                      +------------------+
```

### Rust：状态机枚举变换

```
async fn foo() -> i32 {    编译器变换                 内存布局
    let a = 1;             ──────────                 ────────
    bar().await;           1. 生成状态机枚举           enum FooFuture {
    a + 1                  2. 每个 await 一个状态         State0 { },
}                          3. impl Future for 枚举       State1 { a: i32,
                           4. poll() 中 match 状态                 fut: BarFuture },
                                                         Done,
                                                      }
                                                      大小 = max(各状态) + tag
```

## 学习路径

### Python 路径（最直观）
```
python/bytecode_inspect.py     → 用 dis 模块查看协程字节码
python/generator_coroutine.py  → 从 yield 到 async/await 的演进
python/event_loop_mini.py      → 手写 ~100 行 event loop
```

### C++ 路径（最底层）
```
cpp/coroutine_transform.cpp    → 编译器协程变换分析
cpp/Makefile                   → 生成汇编并分析
cpp/README.md                  → 汇编层面详细讲解
```

### Rust 路径（最完整）
```
rust/src/state_machine.rs      → 手动实现等价状态机
rust/src/pin_unpin.rs          → Pin 机制详解
rust/src/mini_executor.rs      → 手写最小 executor
rust/README.md                 → 汇编分析指南
```

## 建议学习顺序

1. 先运行 Python 的 `generator_coroutine.py` —— 理解"协程就是高级生成器"
2. 运行 `bytecode_inspect.py` —— 看到 await 在字节码层面就是 yield
3. 运行 `event_loop_mini.py` —— 理解 event loop 的调度逻辑
4. 运行 Rust 的 `state_machine.rs` —— 理解状态机变换
5. 运行 `pin_unpin.rs` —— 理解为什么需要 Pin
6. 运行 `mini_executor.rs` —— 理解 Waker 和 executor
7. 编译 C++ 的 `coroutine_transform.cpp` 并分析汇编 —— 看到最底层的实现
