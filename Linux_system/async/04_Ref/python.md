# Python 异步/协程 扩展阅读 — 总结

本文件汇总了三篇微信公众号文章的核心内容，作为本仓库第二、三章 Python 学习后的补充阅读。  
**下文已按建议学习顺序排布**：先打牢模型（async/await 与事件循环），再吃透 Future/Task，最后掌握多任务控制。原文链接见文末，需在浏览器或微信内打开。

---

## 第一步：用 Python 3 的 async/await 做异步编程

> 建议最先读。建立「生成器 → yield from → async/await」和「事件循环用 send 驱动协程」的模型，再学本仓库 03 的字节码与迷你 event loop。

**来源：** keakon，Python开发者 转载  
**原文链接：** 见文末「按学习顺序」第 1 条

### 要点总结

- **PEP 脉络**：PEP 255（生成器）→ PEP 342（send，协程雏形）→ PEP 380（yield from）→ PEP 492（async/await）→ PEP 525（异步生成器）。
- **生成器即协程基础**：`yield` 挂起并返回值，`send(value)` 恢复并传入值；用 `select` + 生成器即可手写事件循环。
- **yield from**：简化「委托子生成器」，一行代替手写迭代与异常传播；协程调用协程也用 `yield from`。
- **原生协程 vs 基于生成器的协程**：`async def` 为原生协程（`CO_COROUTINE`），不能含 `yield`；`@types.coroutine` 为基于生成器的协程。原生协程不能「真正暂停并强制返回事件循环」（不能 yield），所以**最底层**需要基于生成器的协程 yield 回事件循环。
- **await**：只能接 awaitable（有 `__await__` 且返回迭代器）；协程、Future 都是 awaitable。
- **async with / async for**：对应 `__aenter__`/`__aexit__` 和 `__aiter__`/`__anext__`；异步生成器（async def + yield）实现后者，但不可 await。
- **实战**：用 `DefaultSelector` + 协程 `send(None)` 驱动多个 `fetch_url`，在 IO 就绪时再 `send` 恢复；业务层用 `await` 即可。

### 与本仓库的对应

- 与 `03_internals/python/generator_coroutine.py` 的演进历史一致。
- 与 `03_internals/python/event_loop_mini.py` 的「Future + Task + 事件循环」模型一致；该文用 `selector` + `send` 驱动协程。

---

## 第二步：解密 asyncio 的 Future 和 Task

> 建议在第一步之后读。吃透 Future/Task 的语义与陷阱（并发须 create_task、阻塞 IO 不能用），对应本仓库 02 的 Future/Task 示例。

**作者：** 古明地觉，Python开发者  
**原文链接：** 见文末「按学习顺序」第 2 条

### 要点总结

- **Future**
  - 表示「未来才会有的值」；状态：PENDING → FINISHED（或 CANCELLED）。
  - `set_result()` / `set_exception()` 只能调用一次，使 future 变为 FINISHED；`result()` 取结果（有异常则抛出），`exception()` 取异常（无则 None）。
  - 可 `add_done_callback()`；可 `await future`，等价于「阻塞直到有结果再 `result()`」。
  - 源码层面：`_state`、`_result`、`_exception`；C 实现与 Python 实现语义一致。
- **Task**
  - Task 是 Future 的子类 = Future + 协程；`create_task(coro)` 即创建「空 Future + 开始跑协程」，协程结束自动 `set_result`/`set_exception`。
  - `await task` = 等协程结束 + 取内部 future 的 result；协程异常会在 await 时抛出。
  - **并发**：必须先 `create_task` 再 `await`，否则是串行；直接 `await coro()` 不会并发。
- **取消**：`task.cancel()`；`CancelledError` 只会在**下一次 await 该 task** 时抛出，不会在「正在执行普通代码」时立刻抛。
- **超时**：`await asyncio.wait_for(task, timeout)` 超时抛 `TimeoutError` 并取消任务；`asyncio.shield(task)` 可防止 wait_for 的取消传到被保护任务。
- **awaitable**：实现 `__await__` 的对象都可被 await；协程、Future、Task 都实现了。
- **陷阱**：CPU 密集或同步阻塞 IO（如 `requests`、`time.sleep`）会阻塞事件循环，无法并发；应用 aiohttp/httpx 或配合线程池/进程池。

### 与本仓库的对应

- 与 `02_language_examples/python/future_and_task.py` 的 Future/Task/取消/回调 完全对应。
- 与 `01_why_async/` 的「同步阻塞 vs 异步」一致；陷阱部分呼应「为什么要异步」。

---

## 第三步：如何精确控制 asyncio 中并发运行的多个任务

> 建议在前两步之后读。掌握 gather / as_completed / wait 的差异和 return_when、timeout、取消策略，对应本仓库 02 的 wait/as_completed 部分。

**作者：** 古明地觉，Python开发者  
**原文链接：** 见文末「按学习顺序」第 3 条

### 要点总结

- **asyncio.gather**
  - 一次等待多个 awaitable；若传入协程会自动包装成任务；返回**列表**，顺序与传入顺序一致。
  - 某任务异常时默认会向上抛出；`return_exceptions=True` 时异常作为列表元素返回，不抛。
  - 局限：不能「一个失败就取消其余」；必须等全部完成才返回，无法「完成一个处理一个」。
- **asyncio.as_completed**
  - 传入可等待对象列表，返回生成器；**谁先完成谁先被迭代**，适合「完成即处理」。
  - 可设 `timeout`，超时抛 `TimeoutError`，但**未完成任务不会被取消**，仍在后台跑。
- **asyncio.wait**
  - 返回 `(done_set, pending_set)`；可配合 `return_when`：
    - `ALL_COMPLETED`（默认）：等全部完成。
    - `FIRST_COMPLETED`：有一个完成就返回。
    - `FIRST_EXCEPTION`：有一个异常就返回，便于「一个失败就取消其余」（手动 cancel pending）。
  - 可设 `timeout`；超时后**不抛异常**，只返回当前 done/pending；pending 需手动 `task.cancel()`。
  - 任务异常不会自动向上抛，需遍历 `done` 用 `task.exception()` 检查，否则会看到 “Task exception was never retrieved”。
- **最佳实践**：先 `create_task` 得到任务列表，再传给 gather/wait/as_completed，便于对 pending 做精确取消或比对。

### 与本仓库的对应

- 与 `02_language_examples/python/future_and_task.py` 中的 `gather`、`wait`、`as_completed` 用法一致。
- 与 Rust 的 `tokio::join!` / `tokio::select!` 对比可参考 `02_language_examples/README.md`。

---

## 原文链接（按建议学习顺序）

| 学习顺序 | 主题 | 链接 |
|----------|------|------|
| 第 1 步 | 用 Python 3 的 async/await 做异步编程（PEP、事件循环） | https://mp.weixin.qq.com/s?__biz=MzA4MjEyNTA5Mw==&mid=2652566258&idx=1&sn=b690ea944521d9c68f962244246473e0&chksm=8464dab8b31353aec2c12465157f2a15fd5c0acce0c347fa57c273765a5acaeee7a0f15d705c&mpshare=1&scene=1&srcid=0917dnveKMKeIEfLW7JJkv1s#rd |
| 第 2 步 | 解密 asyncio 的 Future 和 Task | https://mp.weixin.qq.com/s/pOk7s_GkTns-sAtVHkBrGw |
| 第 3 步 | 如何精确控制 asyncio 中并发运行的多个任务 | https://mp.weixin.qq.com/s/9Z3xyyOC1Ls62KuVwJoArA |

在整体学习计划中的位置见顶层 **README.md** → **第四章：扩展阅读与参考**。
