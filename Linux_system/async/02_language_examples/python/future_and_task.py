"""
Python 异步编程进阶：Future, Task 与 asyncio 调度

本文件深入讲解：
1. asyncio.Future —— 异步结果的占位符
2. asyncio.Task —— Future 的子类，封装协程的执行
3. Task 的生命周期与取消机制
4. asyncio.wait() 的高级用法
"""

import asyncio
import time


# ============================================================
# 1. Future：异步结果的占位符
# ============================================================

async def demo_future():
    """演示 Future 的基本用法

    Future 是一个低层级的可等待对象，代表一个异步操作的最终结果。
    通常你不需要直接创建 Future，但理解它有助于理解 Task 和 await 的本质。
    """
    print("=== 1. asyncio.Future Basics ===\n")

    loop = asyncio.get_running_loop()

    future = loop.create_future()
    print(f"  Future after creation: done={future.done()}, cancelled={future.cancelled()}")

    async def set_result_later():
        await asyncio.sleep(0.5)
        future.set_result("result value of the Future")
        print("  [background] Future result has been set")

    asyncio.create_task(set_result_later())

    print("  Waiting for Future to complete...")
    result = await future
    print(f"  Future completed! Result: {result}")
    print(f"  Future state: done={future.done()}")
    print()

    print("  Key insights:")
    print("    - A Future is a container, initially empty (pending state)")
    print("    - Once someone calls set_result(), the Future transitions to done state")
    print("    - await future suspends the current coroutine until the Future completes")
    print("    - This is the core idea of the Promise/Future pattern")
    print()


# ============================================================
# 2. Task：封装协程执行的 Future
# ============================================================

async def slow_operation(name: str, duration: float) -> str:
    """模拟耗时操作"""
    print(f"    [{name}] started (expected {duration}s)")
    await asyncio.sleep(duration)
    print(f"    [{name}] completed")
    return f"result of {name}"


async def demo_task():
    """演示 Task 的创建与管理

    Task 是 Future 的子类。当你用 asyncio.create_task() 包装一个协程时：
    1. 协程被调度到 event loop 中
    2. 返回一个 Task 对象（可以 await、取消、检查状态）
    3. Task 内部驱动协程的执行：每次协程 yield（遇到 await）时，
       Task 负责在适当时机恢复协程
    """
    print("=== 2. asyncio.Task and Scheduling ===\n")

    print("--- Tasks are scheduled immediately after creation ---")
    task1 = asyncio.create_task(slow_operation("TaskA", 1.0))
    task2 = asyncio.create_task(slow_operation("TaskB", 0.5))

    print(f"  task1 type: {type(task1).__name__}, state: done={task1.done()}")
    print(f"  task2 type: {type(task2).__name__}, state: done={task2.done()}")
    print()

    print("--- await task to get results ---")
    result1 = await task1
    result2 = await task2
    print(f"  task1 result: {result1}")
    print(f"  task2 result: {result2}")
    print()


# ============================================================
# 3. Task 的取消机制
# ============================================================

async def long_running_task(name: str):
    """一个长时间运行的任务"""
    try:
        print(f"    [{name}] started running...")
        await asyncio.sleep(10.0)
        print(f"    [{name}] completed normally")
        return f"{name} done"
    except asyncio.CancelledError:
        print(f"    [{name}] was cancelled! Performing cleanup...")
        raise


async def demo_cancellation():
    """演示 Task 的取消"""
    print("=== 3. Task Cancellation ===\n")

    task = asyncio.create_task(long_running_task("LongTask"))

    await asyncio.sleep(0.5)
    print(f"  Before cancel: done={task.done()}, cancelled={task.cancelled()}")

    task.cancel()
    print("  Cancel requested...")

    try:
        await task
    except asyncio.CancelledError:
        print(f"  After cancel: done={task.done()}, cancelled={task.cancelled()}")

    print()
    print("  Key insights:")
    print("    - cancel() does not immediately stop the coroutine; it injects CancelledError at the next await point")
    print("    - The coroutine can try/except CancelledError to do cleanup")
    print("    - After catching, you should re-raise; otherwise the cancellation is swallowed")
    print()


# ============================================================
# 4. asyncio.wait() —— 更灵活的等待策略
# ============================================================

async def demo_wait():
    """演示 asyncio.wait 的不同策略"""
    print("=== 4. asyncio.wait() Advanced Usage ===\n")

    tasks = [
        asyncio.create_task(slow_operation(f"Task{i}", duration))
        for i, duration in enumerate([2.0, 0.5, 1.0, 0.3, 1.5])
    ]

    print("--- wait(FIRST_COMPLETED): return when the first one completes ---")
    done, pending = await asyncio.wait(tasks, return_when=asyncio.FIRST_COMPLETED)
    print(f"  Done: {len(done)}, Pending: {len(pending)}")
    for t in done:
        print(f"  Completed: {t.result()}")

    print("\n--- wait(ALL_COMPLETED): wait for all remaining ---")
    done, pending = await asyncio.wait(pending, return_when=asyncio.ALL_COMPLETED)
    print(f"  Done: {len(done)}, Pending: {len(pending)}")
    for t in done:
        print(f"  Completed: {t.result()}")
    print()

    print("  Key insights:")
    print("    - gather(): simple concurrency, wait for all, return ordered result list")
    print("    - wait():   flexible control, supports FIRST_COMPLETED / FIRST_EXCEPTION / ALL_COMPLETED")
    print("    - as_completed(): returns iterator, yields Tasks in completion order")
    print()


# ============================================================
# 5. asyncio.as_completed() —— 按完成顺序处理
# ============================================================

async def demo_as_completed():
    """演示 asyncio.as_completed"""
    print("=== 5. asyncio.as_completed() ===\n")

    durations = {"FastTask": 0.3, "MediumTask": 0.7, "SlowTask": 1.2}
    coros = [slow_operation(name, dur) for name, dur in durations.items()]

    start = time.perf_counter()
    print("  Getting results in completion order:")
    for coro in asyncio.as_completed(coros):
        result = await coro
        elapsed = time.perf_counter() - start
        print(f"    {elapsed:.2f}s - got: {result}")
    print()


# ============================================================
# 主函数
# ============================================================

async def main():
    await demo_future()
    await demo_task()
    await demo_cancellation()
    await demo_wait()
    await demo_as_completed()

    print("=== Summary ===")
    print("  Future: placeholder for async result, the lowest-level awaitable")
    print("  Task:   subclass of Future, wraps and drives coroutine execution")
    print("  create_task(): schedules coroutine on the event loop, returns Task")
    print("  gather(): concurrently await multiple coroutines, return result list")
    print("  wait():   flexible wait strategy (first completed / all completed)")
    print("  as_completed(): iterate results in completion order")


if __name__ == "__main__":
    asyncio.run(main())
