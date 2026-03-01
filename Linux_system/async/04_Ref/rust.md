# Rust 异步 扩展阅读 — 总结

本文件汇总了多篇 Rust 异步（Future、Pin/Unpin、运行时设计、async fn in traits、Tokio）相关文章的核心内容，作为本仓库第二、三章 Rust 示例的补充阅读。  
**推荐学习顺序见下方「学习顺序」表及「为何这样排」说明**；部分链接需在浏览器或微信内打开。

---

## 学习顺序（推荐按此顺序阅读）

| 顺序 | 主题 | 链接 | 说明 |
|------|------|------|------|
| **①** | **运行时与 Future 模型**：epoll/io-uring、Reactor/Executor、Monoio 设计 | https://mp.weixin.qq.com/s/Vu9kfes7whMEjuFFk9I3qQ | 微信，已总结 |
| **②** | **Pin 与 Unpin**：自引用、`poll(Pin<&mut Self>)`、pin-project | https://blog.adamchalmers.com/pin-unpin/ | 已总结 |
| **③** | **深入浅出 Rust 异步编程之 Tokio**（微信） | https://mp.weixin.qq.com/s/FzJAV8Ah8DqDeNSee9WnPA | 入门向；需浏览器打开全文 |
| **④** | **Tokio 源码与设计**：9 篇解析（tony612） | https://mp.weixin.qq.com/s/qj6-KiqOMaJtrQw8bz68lA；[book](https://tony612.github.io/tokio-internals/) | 源码向，已总结 |
| **⑤** | **async fn in traits**：AFIT nightly、GAT、dyn 与引用译文 | [rustcc 索引](https://rustcc.cn/article?id=b00ce60a-f922-4403-9734-0d0354cc1bef)、[AFIT nightly 译文](https://zjp-cn.github.io/translation/rust-lang-blog/async-fn-in-trait-nightly.html) | 进阶/库作者向，已总结 |

**为何这样排**  
- **① → ②**：先建立「Future、Reactor、Executor、Waker」的整体图景（①），再搞清为什么 `poll` 是 `Pin<&mut Self>`、何时需要 pin-project（②），否则看 ① 里的签名会一头雾水。  
- **② → ③**：Pin 之后先读「深入浅出 Tokio」做**使用向**入门（③），再啃 Tokio 源码（④），由用到实现更顺。  
- **④ → ⑤**：Tokio 源码看完再读 AFIT（⑤），适合「写库、抽象 async trait、关心 dyn/GAT」的进阶；若只写业务 async 可把 ⑤ 放最后或选读。

在整体学习计划中的位置见顶层 **README.md** → **第四章：扩展阅读与参考**。

---

## ① 运行时与 Future 模型：Rust 异步运行时的设计与实现

> 建议最先读。建立 epoll/io-uring、Reactor/Executor/Waker、Future 与 poll 的模型，再对照本仓库 `03_internals/rust` 的迷你 executor 与 Pin 讲解。

**参考来源：** 微信公众号「Rust 语言中文社区」— 茌海/徐帅，原文 [RustMagazine 2021 第 12 章 Monoio](https://rustmagazine.github.io/rust_magazine_2021/chapter_12/monoio.html)  
**原文链接：** 见上方学习顺序表 ①

### 要点总结（摘自原文）

- **epoll 与 io-uring**：epoll 是事件通知机制（`epoll_create`/`epoll_ctl`/`epoll_wait`），fd 需设非阻塞，read 返回 `WOULD_BLOCK` 时注册到 epoll，在 `epoll_wait` 返回后再操作 fd。io-uring 是真正的异步 syscall：SQ 提交任务、CQ 接收完成；submit 后内核消费 SQE 并注册 callback，数据就绪时完成 Op；相比 epoll 减少用户态/内核态切换，但需保证 buffer 在 Op 完成前有效。
- **异步任务执行流**：面向 callback（如 libevent）易写成状态分散；有栈协程（如 goroutine）由 runtime 调度、栈在堆上；Rust 采用**无栈协程**，async/await 展开为状态机，实现 `Future`，通过 `poll` 与 runtime 交互，零成本抽象。
- **Future 与 Reactor/Executor**：`Future::poll(self: Pin<&mut Self>, cx: &mut Context) -> Poll<Output>`；返回 `Pending` 时需在依赖的 IO 就绪后通过 `Context` 里的 **Waker** 唤醒。**Reactor** 负责存 Waker 并在事件就绪时 wake；**Executor** 负责调度并调用 `poll`；IO 库负责在 WouldBlock 时把 fd 注册到 Reactor。Reactor 与 Executor 通过 Waker 解耦。
- **极简 Runtime 实现**（epoll）：Reactor = Poller + `HashMap<Token, Waker>`，`modify_readable`/`modify_writable` 存 Waker，`wait()` 里 `epoll_wait` 后按 token 取出并 `waker.wake()`。Task = `Rc<RefCell<LocalBoxFuture<'static, ()>>>`；Waker 的 vtable 在 wake 时把 Task 推回 Executor 队列。Executor 的 `block_on` 循环：poll 主 future → 消费队列里所有 task 的 poll → 再 poll 主 future → 若仍 Pending 则 `reactor.wait()`。IO 组件（如 TcpStream）实现 `AsyncRead`，read 返回 `WouldBlock` 时调用 `reactor.modify_readable(fd, cx)` 并返回 `Poll::Pending`。
- **Monoio**：基于 io-uring 的 thread-per-core Runtime（字节开源）。动机：减少 syscall、用 Rust 泛型消除动态分发开销。与 Tokio 公平调度对比：thread-per-core 无跨线程调度、Task 不必 `Send+Sync`、可用 thread local，但负载不均时核心利用率可能不均衡。io-uring 的 **buffer 生命周期**：Op 提交后 buffer 不能移动直至完成或 Cancel，故 Monoio 采用**所有权 IO**（AsyncReadRent/AsyncWriteRent）：read/write 拿走 buffer 所有权，Future 完成时归还；trait 用 **GAT** 定义带生命周期的关联 Future 类型。

### 与本仓库的对应

- 与 `03_internals/rust` 的「手写 Future 状态机」「Pin/Unpin」「迷你 executor」一致；与 `02_language_examples/rust` 的 async/await、Future 组合对应。

---

## ② Pin 与 Unpin

> 在理解 Future 与 poll 之后读。弄清为何 `poll` 接收 `Pin<&mut Self>`、何时需要 `Unpin`/`!Unpin` 以及如何安全地写嵌套 Future。

**参考来源：** [Pin, Unpin, and why Rust needs them](https://blog.adamchalmers.com/pin-unpin/)（Adam Chalmers）  
**原文链接：** 见上方学习顺序表 ②

### 要点总结（摘自原文）

- **Future 的 poll 签名**：`fn poll(self: Pin<&mut Self>, cx: &mut Context) -> Poll<Self::Output>`。若要在外层 Future 里调用内层 `future.poll(cx)`，必须拿到 `Pin<&mut Fut>`，不能是裸 `&mut Fut`。
- **自引用类型不安全**：若结构体内部有指针指向自身（如 `pointer: *const i32` 指向同结构体的 `val`），移动该结构体会导致指针仍指向旧地址，产生悬垂指针。Rust 通过 **Pin** 与 **Unpin** 区分「可安全移动」与「不可移动」的类型。
- **Unpin 与 !Unpin**：绝大多数类型默认 **Unpin**（可安全移动）。自引用类型、以及「实现 Future 且借用了数据」的 async 块生成的类型多为 **!Unpin**。`Pin<P>` 包装指针，保证其指向的值在 `Unpin` 时仍可移动，在 `!Unpin` 时不可被移动，从而安全地 poll 嵌套 Future。
- **Projection**：从 `Pin<&mut Struct>` 拿到字段的引用时，若字段需要被 poll（如内层 Future），需得到 `Pin<&mut Field>`，通常需手写 `unsafe` 或使用 **[pin-project](https://docs.rs/pin-project)**。`#[pin_project]` 与 `#[pin]` 标记字段后，`self.project()` 会生成正确的 pinned 字段引用，从而无需手写 unsafe 即可调用 `inner_future.poll(cx)`。
- **小结**：自引用/借用的 Future 不能安全移动；Rust 用 Unpin（可移动）与 Pin（禁止移动的包装）区分；poll 必须用 `Pin<&mut Self>`；写嵌套 Future 时用 pin-project 生成正确的字段投影。

### 与本仓库的对应

- 与 `03_internals/rust/pin_unpin.rs` 及 README 中的 Pin/Unpin 讲解一致；与 `02_language_examples/rust` 中手写 Future 的 poll 签名对应。

---

## ③ 深入浅出 Rust 异步编程之 Tokio

> 建议在 ①② 之后读，作为 Tokio **使用向**入门；再读 ④ 啃源码。正文需在浏览器中打开链接阅读。

**参考来源：** 微信公众号  
**原文链接：** [深入浅出Rust异步编程之Tokio](https://mp.weixin.qq.com/s/FzJAV8Ah8DqDeNSee9WnPA)（见上方学习顺序表 ③）

### 说明

- 该文标题为「**深入浅出Rust异步编程之Tokio**」，从入门到深入介绍 Rust 异步编程与 Tokio 的使用与原理。因微信环境限制，正文未做自动抓取，请**在浏览器中打开链接**阅读全文；读完后可与 ① 运行时模型、④ Tokio 源码解析 对照。

### 与本仓库的对应

- 与 `02_language_examples/rust` 的 Tokio 示例、`03_internals/rust` 的 executor/Reactor 设计可对照。

---

## ④ Tokio 源码与设计

> 在掌握 Reactor/Executor 与 Pin、并读过 ③ 入门后读。作为主流 Runtime 的源码解析与设计分析。

**参考来源：** 微信公众号「Rust 语言中文社区」— tony612；[Tokio Internals](https://tony612.github.io/tokio-internals/)（共 9 篇）  
**原文链接：** 见上方学习顺序表 ④

### 要点总结（摘自原文）

- 作者在阅读 Tokio 源码后写了 9 篇解析与设计分析，涵盖 Tokio 内部机制与实现细节。  
- **Book 地址**：https://tony612.github.io/tokio-internals/  
- 适合与「① 运行时与 Future 模型」对照：Tokio 为公平调度、多线程 work-stealing，与 Monoio 的 thread-per-core 形成对比；结合本仓库 `02_language_examples/rust` 使用 Tokio 的示例与 `03_internals/rust` 的迷你 executor 可加深理解。

### 与本仓库的对应

- 与 `02_language_examples/rust` 中使用 Tokio 的 async 示例、以及 `03_internals/rust` 的 executor/Reactor 设计可对照阅读。

---

## ⑤ async fn in traits（AFIT）与引用链接

> 在掌握标准 async/await、Future 与 Tokio 使用后读；偏**进阶/库作者**。了解为何 trait 里写 async fn 困难、nightly 的 AFIT 支持与限制、以及 dyn 与 GAT 的关系。

**参考来源：** [async fn in traits 系列文章翻译](https://rustcc.cn/article?id=b00ce60a-f922-4403-9734-0d0354cc1bef)（rustcc，苦瓜小仔）、[async fn in trait 在 nightly 已可用](https://zjp-cn.github.io/translation/rust-lang-blog/async-fn-in-trait-nightly.html)（zjp-cn 译）  
**原文链接：** 见上方学习顺序表 ⑤；**引用链接**（rustcc 表中）如下一并总结。

### 要点总结（摘自原文与译文）

- **为何 trait 里 async fn 难**：`async fn` 返回匿名 Future 类型，无法在 trait 里写死返回类型；若用关联类型表示返回的 Future，需要**泛型关联类型（GAT）** 才能带生命周期（捕获 `&self`）。stable 上常用方案：① **async-trait** 宏：脱糖为 `Pin<Box<dyn Future + Send + '_>>`，有分配与动态分发开销，且不适合 no_std；② 手写 **poll** 形式接口（如 `AsyncIterator::poll_next`），难写易错。
- **Nightly AFIT（async fn in trait）**：`#![feature(async_fn_in_trait)]` 后可在 trait 中直接写 `async fn`，编译器为每个 impl 生成对应 Future 类型。限制 1：**从泛型 spawn 时**，若 executor 要求 `Send`，需要「async fn 返回的 Future 是 Send」的约束，目前可用 `return_position_impl_trait_in_trait` 在签名里加 `+ Send`。限制 2：**dyn Trait** 上还不能直接调用 async fn，需继续用 async-trait 或等待 dyn* 等方案。
- **引用链接（rustcc 表中）**  
  - [Async fn in trait MVP comes to nightly](https://blog.rust-lang.org/inside-rust/2022/11/17/async-fn-in-trait-nightly.html) → [译文](https://zjp-cn.github.io/translation/rust-lang-blog/async-fn-in-trait-nightly.html)（上文已概括）。  
  - [How Async Functions in Traits could Work in Rustc](https://blog.theincredibleholk.org/blog/2022/04/18/how-async-functions-in-traits-could-work-in-rustc/) → [AFIT 如何在 rustc 中工作](https://zjp-cn.github.io/translation/async/async-fn-in-trait/how-async-functions-in-traits-could-work-in-rustc.html)。  
  - [dyn* Code Generation](https://blog.theincredibleholk.org/blog/2022/12/12/dyn-star-codegen/) → [dyn* 如何生成代码](https://zjp-cn.github.io/translation/async/async-fn-in-trait/dyn-star-codegen.html)。  
  - [Async Functions in Trait Objects Update](https://blog.theincredibleholk.org/blog/2022/12/19/async-fn-in-trait-object-update/) → [trait object 中的异步函数](https://zjp-cn.github.io/translation/async/async-fn-in-trait/async-fn-in-trait-object-update.html)。  
  后三篇为 Eric Holk（Rust 异步工作组）所作，从实现与 dyn/trait object 角度串联 AFIT 与 Niko 的 dyn async traits 系列。

### 与本仓库的对应

- 与 `02_language_examples/rust` 中 async/await、手写 Future 的用法互补；与 `03_internals` 中「Future 状态机」理解一致。

---

## 原文链接（与上方学习顺序一致，便于复制）

| 顺序 | 主题 | 链接 |
|------|------|------|
| ① | Rust 异步运行时的设计与实现（Monoio，微信） | https://mp.weixin.qq.com/s/Vu9kfes7whMEjuFFk9I3qQ |
| ① | 原文 RustMagazine 2021 第 12 章 | https://rustmagazine.github.io/rust_magazine_2021/chapter_12/monoio.html |
| ② | Pin, Unpin, and why Rust needs them | https://blog.adamchalmers.com/pin-unpin/ |
| ③ | 深入浅出 Rust 异步编程之 Tokio（微信） | https://mp.weixin.qq.com/s/FzJAV8Ah8DqDeNSee9WnPA |
| ④ | Tokio Internals 推荐（微信） | https://mp.weixin.qq.com/s/qj6-KiqOMaJtrQw8bz68lA |
| ④ | Tokio Internals book（tony612） | https://tony612.github.io/tokio-internals/ |
| ⑤ | async fn in traits 系列翻译索引（rustcc） | https://rustcc.cn/article?id=b00ce60a-f922-4403-9734-0d0354cc1bef |
| ⑤ | AFIT nightly 译文（zjp-cn） | https://zjp-cn.github.io/translation/rust-lang-blog/async-fn-in-trait-nightly.html |

在整体学习计划中的位置见顶层 **README.md** → **第四章：扩展阅读与参考**。
