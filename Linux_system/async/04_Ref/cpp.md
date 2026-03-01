# C++ 异步/并发 扩展阅读 — 总结

本文件汇总了多篇 C++ future/promise、async、packaged_task 及进阶（folly）相关文章的核心内容，作为本仓库第二、三章 C++ 示例的补充阅读。  
**建议按下方「学习顺序」表中的顺序阅读**：先总览关系，再学 promise/future 基础与同步，接着学 async/packaged_task 与生产-消费对比，最后学 folly 链式与实现原理。各节要点总结见下表之后。

---

## 学习顺序（建议按此顺序阅读）

| 顺序 | 主题 | 链接 | 说明 |
|------|------|------|------|
| **①** | **总览**：thread / future / promise / packaged_task / async 关系 | https://mp.weixin.qq.com/s/fUD4HxtUNhnpVlqGNAbc6Q | 程序喵大人，已总结 |
| **②** | **第 1 步**：promise 与 future 基础（API + 同步与 wait_for 超时） | [haippy](https://www.cnblogs.com/haippy/p/3239248.html)、[guotianqing](https://blog.csdn.net/guotianqing/article/details/103770992) | 已总结 |
| **③** | **第 2 步**：async 与 packaged_task（生产-消费对比 + 示例） | [AC_hell](https://blog.csdn.net/AC_hell/article/details/72718363)、[guxuanqing](https://www.cnblogs.com/guxuanqing/p/11360572.html) | 已总结 |
| **④** | **第 3 步**：folly future/promise（then 链式） | https://www.cnblogs.com/chenyangyao/p/folly-future.html | 已总结 |
| **⑤** | **进阶**：实现原理、when_all、EnableSharedFromThis | https://blog.csdn.net/jiange_zh/article/details/52542084 | jiange_zh，已总结 |

在整体学习计划中的位置见顶层 **README.md** → **第四章：扩展阅读与参考**。部分链接需在浏览器中打开（微信/知乎/CSDN 可能加载较慢或需登录）。

---

## 概念总览：thread、future、promise、packaged_task、async 的关系

> 建议最先读，建立整体图景后再按下面第一步、第二步深入。

**参考来源：** 微信公众号「CPP开发前沿」— 程序喵大人（2022-07-12）  
**原文链接：** [thread、future、promise、packaged_task、async之间有什么关系？](https://mp.weixin.qq.com/s/fUD4HxtUNhnpVlqGNAbc6Q)（见上方学习顺序表 ①；若在浏览器中打开，带 `poc_token` 的同一链接也可用。）

### 要点总结（摘自原文）

- **背景**：并发编程一般指多线程编程；C++11 之后相关高级 API 包括：`std::thread`、`std::future`、`std::shared_future`、`std::promise`、`std::packaged_task`、`std::async`。
- **关系（原文图示结论）**：
  - **packaged_task ≈ promise + function**（可调用对象 + 结果通道）。
  - **async = thread + packaged_task**（在新线程中执行任务并返回 future）。
  - 通过 **promise 的 `get_future()`** 得到 **future**；通过 **future 的 `share()`** 得到 **shared_future**。
- **图示结构**：`function` 与 `promise` 包在 `packaged_task` 内；`get_future()` 指向 `future`，`future` 经 `share()` 指向 `shared_future`；`thread` 与 `packaged_task` 并列，`async` 在概念上统合「线程 + 任务」。
- **延伸阅读**：若对上述 API 还不熟悉，可先看 [这篇入门](https://mp.weixin.qq.com/s/rPjRTOTYK2SGr6WxgWI_Vg)（原文内链）。

---

## 第一步：std::promise 与 std::future 基础

> 建议最先读。理解「线程间传值的占位符」模型，以及 promise（写入端）与 future（读取端）的配对关系，再对照本仓库 `02_language_examples/cpp/future_promise.cpp`。

**参考来源：** 博客园（C++11 并发指南 / C++之 future 和 promise）、CSDN guotianqing  
**原文链接：** 见上方学习顺序表 ②（两篇：haippy、guotianqing）

### 要点总结

- **作用**：在不同线程之间传递数据；比裸指针安全（不暴露共享内存），且支持泛型，接口统一。
- **关系**：`std::promise<T>` 与 `std::future<T>` 通过**共享状态（shared state）**关联；promise 是「写入端」，future 是「读取端」。一个 promise 只能 `get_future()` 一次。
- **基本用法**：线程 A 创建 `promise` 和 `future`，把 promise 传给线程 B；线程 B 在合适时机 `promise.set_value(value)`（或 `set_exception`）；线程 A 在需要结果时 `future.get()`，若尚未就绪则阻塞直到 B 设置完毕。
- **线程间同步与超时**（参见 [CSDN guotianqing](https://blog.csdn.net/guotianqing/article/details/103770992)）：用 `future.wait_for(std::chrono::seconds(0)) == std::future_status::ready` 可判断结果是否已就绪；`wait_for(timeout)` 在超时或状态变为 ready 时返回，返回值可为 `future_status::deferred` / `ready` / `timeout`。典型场景：等待「异步登录」等结果时，主线程 `wait_for(10s)`，若 ready 则 `get()` 取结果，否则按超时处理（注意实际阻塞时间可能略长于指定 timeout）。
- **API 要点**：
  - `promise::get_future()`：返回关联的 future，只能调用一次。
  - `promise::set_value(val)` / `promise::set_exception(ex)`：设置结果或异常，使共享状态变为 ready；**只能设置一次**。
  - `promise::set_value_at_thread_exit(val)`：在**当前线程退出时**才将共享状态置为 ready，便于在线程结束前做清理。
  - `future::get()`：阻塞直到 ready，然后取走值（或抛出 set 进去的异常）；**只能调用一次**（移动语义）。
  - `future::wait_for(timeout)`：在超时时间内等待，返回 `future_status::ready` / `timeout` / `deferred`。
- **与 mutex 的区别**：promise/future 用于**一次性**结果传递；不能重复 get，不能替代条件变量做多轮通信。
- **使用注意**（同上 CSDN 文）：只能从一个 promise 获取一个 future；若 promise 析构前未 set_value/set_exception，会自动设置 `future_error(broken_promise)`；`set_value` 只能调用一次；future 必须通过 `promise::get_future()` 获得，不能默认构造后使用。

### 与本仓库的对应

- 与 `02_language_examples/cpp/future_promise.cpp` 中的「基本 promise/future」「异常传递」示例一致。
- 标准库的 future 是**线程级**的（阻塞的是线程），与本仓库 03 的 **C++20 协程**（挂起协程、不阻塞线程）是不同层次。

---

## 第二步：std::async 与 std::packaged_task

> 建议在第一步之后读。掌握基于 future 的两种高层用法：async 直接返回 future，packaged_task 把可调用对象包装成「可在线程中执行并得到 future」的任务。

**参考来源：** 博客园（C++之 future 和 promise）、[C++11之 future,promise,packaged_task,async 详解](https://blog.csdn.net/AC_hell/article/details/72718363)（CSDN AC_hell）  
**原文链接：** 见上方学习顺序表 ③（两篇：AC_hell、guxuanqing）

### 要点总结

- **生产-消费对比**（参见 [CSDN AC_hell](https://blog.csdn.net/AC_hell/article/details/72718363)）：同一「生产-消费」场景可用多种方式实现——**mutex + condition_variable**（全局数据 + 锁 + `wait`/`notify_one`）→ **promise + future**（生产线程 `set_value`，消费线程 `get()`，无需显式共享变量与条件变量）→ **packaged_task**（把生产逻辑封装成可调用对象，投递到线程执行，`get_future()` 取结果）→ **async**（直接 `std::async(launch::async, func)` 返回 future，无需手写 thread）。后三者逐步简化代码并降低出错可能；但 **future 非线程安全**，`get()` 只能调用一次，多线程多次获取需用 **shared_future**。
- **std::async**
  - 高级封装：相当于「创建线程执行某函数 + 用 promise/future 传回结果」。  
  - `std::future<R> fut = std::async(std::launch::async, func, args...)`：在新线程中执行 `func(args...)`，`fut.get()` 取得返回值（或异常）。  
  - `std::launch::deferred`：延迟执行，在第一次 `fut.get()` 或 `fut.wait()` 时**在当前线程**执行。  
  - 不指定策略时，实现可自由选择 async 或 deferred；若需明确异步，应传 `std::launch::async`。  
  - **与生产-消费示例**（同上 AC_hell 文）：`std::async(std::launch::async, [](){ ... return result; })` 返回 `future<R>`，主线程可在任意时刻 `get()` 获取结果；使用 `launch::async` 时任务在另一线程执行（与主线程并发）；使用 `launch::deferred` 时仅在第一次 `get()`/`wait()` 时在当前线程执行，可用于对比耗时（async 约 2s+，deferred 约 3s+）。
- **std::packaged_task**
  - 把「可调用对象」包装成「可移动、可在其他线程执行、且结果通过 future 获取」的任务。  
  - 用法：`std::packaged_task<R(Args...)> task(callable)`，`auto fut = task.get_future()`，在另一线程中 `task(args...)` 执行；`fut.get()` 得到返回值。  
  - 适合「任务队列」场景：主线程把 packaged_task 投递到队列，工作线程取出并执行，主线程通过 future 等待结果。
- **三者的关系**：`future` 是结果的消费者；`promise` 是生产者；`async` = thread + promise/future 的封装；`packaged_task` = 可调用对象 + promise/future 的封装。**packaged_task** 的模板参数为**函数签名**（如 `_data()`），返回值类型决定关联的 future 类型。

### 与本仓库的对应

- 与 `02_language_examples/cpp/future_promise.cpp` 中的「std::async」「std::packaged_task」示例一致。

---

## 第三步：folly Future/Promise（进阶）

> 建议在掌握标准库之后读。了解「带 then 链式回调」的 Future 模型，便于理解其他语言中的 Promise 链与组合方式。

**参考来源：** 博客园（folly 教程系列之 future/promise）  
**原文链接：** 见上方学习顺序表 ④

### 要点总结

- **为何 folly 再实现一套**：标准库 `std::future` 只能阻塞地 `get()`，不能方便地挂回调；folly 的 Future 支持 **then**，可链式编排异步步骤，避免回调地狱。
- **基本用法**：  
  - `Promise<T> p; Future<T> f = p.getFuture();`  
  - `f.then(callback)`：当 promise 被 setValue/setException 时，执行 callback；**then 返回新的 Future**，可继续链式 then。  
  - `p.setValue(val)` / `p.setException(ex)`：填充结果，触发已注册的 then 回调。
- **链式与类型变化**：`f.then([](int i){ return string(...); })` 得到 `Future<string>`，可继续 `.then(...)`；回调也可返回 `Future<U>`，实现「异步接异步」。
- **setWith**：`p.setWith([] { ... return value; })`，在 lambda 内执行可能抛异常的逻辑，folly 自动将异常传给 promise，无需手写 setException。
- **Try**：回调参数可用 `Try<T>` 同时表示成功值或异常，便于统一处理；但更推荐用 then 的异常传播机制，在链末统一处理。
- **注意**：folly 是 Facebook 的 C++ 库，需单独集成；本仓库的 C++ 示例仅使用标准库，此处仅作概念扩展。

### 与本仓库的对应

- 概念上对应「Promise 链」与「async 编排」，可与 Python 的 Future 回调、Rust 的 Future 组合对比（见 `02_language_examples/README.md`）。

---

## 实现原理与 then / when_all（进阶阅读）

> 适合在掌握标准库与 folly 用法后，从「依赖组件 + 共享状态」角度理解 future/promise 的实现思路。以 boost/类 boost 实现为背景。

**参考来源：** [C++异步调用利器 future/promise 实现原理](https://blog.csdn.net/jiange_zh/article/details/52542084)（CSDN jiange_zh）  
**原文链接：** 见上方学习顺序表 ⑤

### 要点总结（摘自原文）

- **动机**：异步编程中回调多、代码分散难维护；future/promise 使异步逻辑更清晰、易维护。原文从**源码**入手，针对借鉴 boost 的实现进行分析。
- **依赖组件**：实现 future/promise 及 then 链通常依赖：**bind/callback**（类似 boost::bind、boost::function）；**shared_ptr / scoped_ptr / tuple / exception**；**Future 与 Promise** 共享同一**共享状态（shared state）**；**when_all** 在多个 Future 上做「全部完成」的同步（异步并行同步化）。
- **共享状态**：Promise 在构造时与一个共享状态关联，该状态可存类型 T 的值或 `std::exception` 派生对象；通过 `get_future()` 得到的 Future 与 Promise **共享同一 shared state**，从而在不同线程间安全读写。
- **then 的用法与实现**：文中讨论了 then 的返回值类型、回调函数体与链式组合，与 folly 的 then 思路一致（回调在结果就绪时执行，返回新 Future）。
- **EnableSharedFromThis**：当类被 `shared_ptr` 管理，且成员函数中需要把「当前对象」作为参数传给其他函数（如异步回调）时，应继承 `enable_shared_from_this<T>`，在成员函数内通过 `shared_from_this()` 传递指向自身的 `shared_ptr`，避免传裸指针（调用者可能误 delete）或 `shared_ptr<this>`（会产生另一组引用计数导致二次析构）。典型场景：Boost.Asio 的 `tcp_connection` 在 `async_write` 回调中传递 `shared_from_this()`。
- **延伸**：原文还链接了作者同系列的 [future/promise 简介](http://blog.csdn.net/jiange_zh/article/details/51602938)、[Function 与 Bind 用法](http://blog.csdn.net/jiange_zh/article/details/51598580)，可作补充。

### 与本仓库的对应

- 共享状态、get_future 一次性与标准库一致；then / when_all 与第三步 folly 的链式、组合用法对应；EnableSharedFromThis 在异步回调中传递 `shared_ptr` 的用法，可与本仓库中涉及异步回调的示例对照。

---

## 原文链接（与上方学习顺序一致，便于复制）

| 顺序 | 主题 | 链接 |
|------|------|------|
| ① | 总览：五者关系（程序喵大人） | https://mp.weixin.qq.com/s/fUD4HxtUNhnpVlqGNAbc6Q |
| ② | 第 1 步：promise 详解（haippy） | https://www.cnblogs.com/haippy/p/3239248.html |
| ② | 第 1 步：同步与 wait_for 超时（guotianqing） | https://blog.csdn.net/guotianqing/article/details/103770992 |
| ③ | 第 2 步：生产-消费对比（AC_hell） | https://blog.csdn.net/AC_hell/article/details/72718363 |
| ③ | 第 2 步：async/packaged_task 示例（guxuanqing） | https://www.cnblogs.com/guxuanqing/p/11360572.html |
| ④ | 第 3 步：folly then 链式（chenyangyao） | https://www.cnblogs.com/chenyangyao/p/folly-future.html |
| ⑤ | 进阶：实现原理（jiange_zh） | https://blog.csdn.net/jiange_zh/article/details/52542084 |

在整体学习计划中的位置见顶层 **README.md** → **第四章：扩展阅读与参考**。
