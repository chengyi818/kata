"""
手写迷你 Event Loop

从零实现一个约 100 行的 event loop，揭示 asyncio 的核心调度逻辑。

这个迷你实现包含：
  1. Task: 封装协程的执行
  2. Future: 异步结果占位符
  3. EventLoop: 调度器——运行就绪任务，管理定时器和 I/O
  4. sleep(): 基于定时器的挂起
  5. gather(): 并发等待多个协程

这就是 asyncio 的核心骨架——去掉了错误处理和边界条件后的本质。
"""

import time
import heapq
from collections import deque


# ============================================================
# 1. Future: 异步结果的占位符
# ============================================================

class Future:
    """最小化的 Future 实现

    Future 代表一个尚未完成的异步操作的结果。
    它实现 __await__ 协议，使其可以被 await。
    """

    def __init__(self):
        self._result = None
        self._done = False
        self._callbacks = []  # 完成时要调用的回调列表

    def set_result(self, result):
        """设置结果，标记完成，触发回调"""
        self._result = result
        self._done = True
        for callback in self._callbacks:
            callback(self)

    def result(self):
        if not self._done:
            raise RuntimeError("Future 尚未完成")
        return self._result

    def done(self):
        return self._done

    def add_done_callback(self, callback):
        if self._done:
            callback(self)
        else:
            self._callbacks.append(callback)

    def __await__(self):
        """实现 await 协议

        关键！这就是连接协程和 event loop 的桥梁：
        1. yield self —— 将 Future 本身产出给 event loop
        2. event loop 记录"这个 Task 在等待这个 Future"
        3. Future 完成时，event loop 恢复对应的 Task
        4. Task 恢复后，协程从 await 处继续，获取 self._result
        """
        if not self._done:
            yield self  # 挂起点！控制权返回 event loop
        return self._result


# ============================================================
# 2. Task: 封装协程的执行
# ============================================================

class Task(Future):
    """Task 是 Future 的子类，封装一个协程的执行

    Task 负责驱动协程：调用 send() 推进协程执行，
    处理 yield 出的 Future（注册回调），
    处理协程完成（设置 Task 自己的结果）。
    """

    def __init__(self, coro, loop):
        super().__init__()
        self._coro = coro
        self._loop = loop
        # 立即开始调度
        self._loop.call_soon(self._step)

    def _step(self, future_result=None):
        """推进协程执行一步

        这个方法是 Task 的核心：
        1. 调用 coro.send(value) 恢复协程
        2. 如果协程 yield 了一个 Future → 注册回调，等 Future 完成后再 _step
        3. 如果协程返回 (StopIteration) → 设置 Task 自己的结果
        """
        try:
            # 恢复协程执行
            result = self._coro.send(future_result)

            if isinstance(result, Future):
                # 协程 await 了一个 Future，注册回调
                # 当 Future 完成时，会再次调用 _step
                result.add_done_callback(
                    lambda fut: self._loop.call_soon(self._step, fut.result())
                )
            else:
                # 协程 yield 了非 Future 的值（不应该发生）
                self._loop.call_soon(self._step)

        except StopIteration as e:
            # 协程执行完毕，设置 Task 的结果
            self.set_result(e.value)


# ============================================================
# 3. EventLoop: 核心调度器
# ============================================================

class EventLoop:
    """最小化的 Event Loop

    核心数据结构：
      _ready: 就绪队列——可以立即执行的回调
      _scheduled: 定时器堆——按到期时间排序的回调

    调度循环：
      while 有任务:
        1. 检查定时器，将到期的移到就绪队列
        2. 执行就绪队列中的所有回调
        3. 如果没有就绪任务，sleep 到最近的定时器到期
    """

    def __init__(self):
        self._ready = deque()       # 就绪队列：[(callback, args), ...]
        self._scheduled = []        # 定时器堆：[(when, callback, args), ...]
        self._stopping = False

    def call_soon(self, callback, *args):
        """将回调添加到就绪队列"""
        self._ready.append((callback, args))

    def call_later(self, delay, callback, *args):
        """注册定时器：delay 秒后执行 callback"""
        when = time.monotonic() + delay
        heapq.heappush(self._scheduled, (when, callback, args))

    def create_task(self, coro):
        """创建 Task 并调度"""
        return Task(coro, self)

    def run_until_complete(self, coro):
        """运行直到指定协程完成"""
        task = self.create_task(coro)
        task.add_done_callback(lambda _: self._stop())
        self._run()
        return task.result()

    def _stop(self):
        self._stopping = True

    def _run(self):
        """核心事件循环"""
        while not self._stopping:
            # 1. 检查定时器，将到期的移到就绪队列
            now = time.monotonic()
            while self._scheduled and self._scheduled[0][0] <= now:
                _, callback, args = heapq.heappop(self._scheduled)
                self._ready.append((callback, args))

            # 2. 执行就绪队列中的所有回调
            while self._ready:
                callback, args = self._ready.popleft()
                callback(*args)

            # 3. 如果没有就绪任务，sleep 到最近的定时器到期
            if not self._ready and self._scheduled and not self._stopping:
                next_time = self._scheduled[0][0]
                sleep_time = max(0, next_time - time.monotonic())
                if sleep_time > 0:
                    time.sleep(sleep_time)

            # 4. 如果什么都没有了，退出
            if not self._ready and not self._scheduled:
                break

        self._stopping = False


# ============================================================
# 4. sleep(): 基于定时器的挂起
# ============================================================

async def sleep(seconds):
    """等价于 asyncio.sleep()

    原理：
    1. 创建一个 Future
    2. 注册定时器：seconds 秒后调用 future.set_result()
    3. await future —— 协程挂起
    4. 定时器到期 → set_result() → Task._step() 恢复协程
    """
    future = Future()
    _current_loop.call_later(seconds, future.set_result, None)
    await future


# ============================================================
# 5. gather(): 并发等待多个协程
# ============================================================

async def gather(*coros):
    """等价于 asyncio.gather()

    原理：
    1. 为每个协程创建 Task
    2. 创建一个 Future 代表"全部完成"
    3. 每个 Task 完成时检查是否全部完成
    4. 全部完成后设置 gather Future 的结果
    """
    tasks = [_current_loop.create_task(c) for c in coros]

    if not tasks:
        return []

    gather_future = Future()
    results = [None] * len(tasks)
    done_count = 0

    def on_task_done(idx, task):
        nonlocal done_count
        results[idx] = task.result()
        done_count += 1
        if done_count == len(tasks):
            gather_future.set_result(results)

    for i, task in enumerate(tasks):
        task.add_done_callback(lambda t, idx=i: on_task_done(idx, t))

    return await gather_future


# ============================================================
# 6. 测试：使用我们的迷你 event loop
# ============================================================

# 全局变量保存当前 loop（简化实现，实际 asyncio 用 contextvars）
_current_loop = None


async def fetch_data(name, delay):
    """模拟异步请求"""
    print(f"  [{name}] 开始请求...")
    await sleep(delay)
    print(f"  [{name}] 完成!")
    return f"{name}的数据"


async def demo_sequential():
    """串行 await"""
    print("=== 串行 await ===")
    start = time.perf_counter()

    r1 = await fetch_data("A", 0.5)
    r2 = await fetch_data("B", 0.3)

    elapsed = time.perf_counter() - start
    print(f"  结果: [{r1}, {r2}]")
    print(f"  耗时: {elapsed:.2f}s (串行: 0.5+0.3=0.8s)\n")


async def demo_concurrent():
    """并发 gather"""
    print("=== 并发 gather ===")
    start = time.perf_counter()

    results = await gather(
        fetch_data("A", 0.5),
        fetch_data("B", 0.3),
        fetch_data("C", 0.4),
    )

    elapsed = time.perf_counter() - start
    print(f"  结果: {results}")
    print(f"  耗时: {elapsed:.2f}s (并发: max(0.5,0.3,0.4)=0.5s)\n")


async def main():
    print("=" * 60)
    print("手写迷你 Event Loop 演示")
    print("=" * 60)
    print()

    await demo_sequential()
    await demo_concurrent()

    print("=" * 60)
    print("Event Loop 核心原理总结")
    print("=" * 60)
    print("""
  我们刚刚用 ~100 行代码实现了 asyncio 的核心：

  1. Future.__await__():
     yield self → 将 Future 交给 event loop → 协程挂起

  2. Task._step():
     coro.send(value) → 推进协程 → 收到 yield 的 Future → 注册回调

  3. EventLoop._run():
     循环: 检查定时器 → 执行就绪回调 → sleep 等待

  4. sleep():
     创建 Future + 注册定时器 → 定时器到期 → set_result → Task 恢复

  5. gather():
     创建多个 Task + 计数器 → 全部完成 → set_result

  这就是 asyncio 的骨架！
  真正的 asyncio 在此基础上增加了：
    - I/O 多路复用 (epoll/kqueue) 而非 time.sleep
    - 错误处理和取消机制
    - DNS 解析、SSL/TLS、子进程等
    - 线程安全、调试工具、性能优化
""")


if __name__ == "__main__":
    _current_loop = EventLoop()
    _current_loop.run_until_complete(main())
