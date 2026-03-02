"""
Python 异步编程基础：async/await 与协程

本文件逐步演示 Python 协程的核心概念：
1. 什么是协程函数和协程对象
2. await 的语义
3. 协程的执行流程
"""

import asyncio


# ============================================================
# 1. 协程函数 vs 普通函数
# ============================================================

def regular_function():
    """普通函数：调用时立即执行，返回结果"""
    return "hello"


async def coroutine_function():
    """协程函数：用 async def 定义。
    调用时不会执行函数体，而是返回一个协程对象（coroutine object）。
    协程对象需要被 await 或交给 event loop 才会真正执行。
    """
    return "hello from coroutine"


def demo_coroutine_object():
    """演示协程函数返回的是协程对象，而非直接的返回值"""
    print("=== 1. Coroutine Function vs Regular Function ===\n")

    result = regular_function()
    print(f"regular_function() returns: {result!r}  (type: {type(result).__name__})")

    coro = coroutine_function()
    print(f"coroutine_function() returns: {coro!r}  (type: {type(coro).__name__})")
    print("  Note: the function body has NOT executed! Only a coroutine object was created.")
    print("  The coroutine must be awaited or submitted to the event loop to run.")

    coro.close()
    print()


# ============================================================
# 2. await 的语义：挂起当前协程，等待另一个可等待对象完成
# ============================================================

async def fetch_data(url: str, delay: float) -> str:
    """模拟一个异步网络请求"""
    print(f"  Start fetching {url}...")
    await asyncio.sleep(delay)
    print(f"  {url} response complete!")
    return f"data from {url}"


async def demo_await():
    """演示 await 的执行流程"""
    print("=== 2. Semantics of await ===\n")

    print("Step 1: Call fetch_data() to create a coroutine")
    print("Step 2: await the coroutine -- suspend current coroutine, start executing fetch_data")
    print("Step 3: Inside fetch_data, await asyncio.sleep() -- suspend again")
    print("Step 4: After sleep finishes, fetch_data resumes and returns")
    print("Step 5: demo_await receives the return value and continues\n")

    result = await fetch_data("https://api.example.com", 0.5)
    print(f"  Got result: {result}")
    print()


# ============================================================
# 3. 协程并发执行：await 的串行 vs gather 的并发
# ============================================================

async def demo_sequential_vs_concurrent():
    """对比串行 await 和并发 gather"""
    print("=== 3. Sequential vs Concurrent ===\n")

    import time

    # --- 串行 await ---
    print("--- Sequential await (next one starts only after previous completes) ---")
    start = time.perf_counter()

    r1 = await fetch_data("site-A", 1.0)
    r2 = await fetch_data("site-B", 1.0)

    elapsed = time.perf_counter() - start
    print(f"  Sequential results: [{r1}, {r2}]")
    print(f"  Sequential elapsed: {elapsed:.2f}s (1s + 1s = 2s)\n")

    # --- 并发 gather ---
    print("--- asyncio.gather (all coroutines run concurrently) ---")
    start = time.perf_counter()

    r1, r2 = await asyncio.gather(
        fetch_data("site-A", 1.0),
        fetch_data("site-B", 1.0),
    )

    elapsed = time.perf_counter() - start
    print(f"  Concurrent results: [{r1}, {r2}]")
    print(f"  Concurrent elapsed: {elapsed:.2f}s (two 1s requests concurrently, total ~1s)\n")

    print("Key takeaways:")
    print("  - Sequential await: each await waits for the coroutine to finish before continuing")
    print("  - gather: all coroutines start simultaneously, event loop switches between them")
    print("  - For I/O-bound tasks, gather can dramatically reduce total elapsed time")
    print()


# ============================================================
# 4. 协程的异常处理
# ============================================================

async def may_fail(task_id: int):
    """一个可能失败的协程"""
    await asyncio.sleep(0.1)
    if task_id == 2:
        raise ValueError(f"Task {task_id} failed!")
    return f"Task {task_id} succeeded"


async def demo_exception_handling():
    """演示协程中的异常处理"""
    print("=== 4. Exception Handling in Coroutines ===\n")

    # 方式 1: try/except 捕获单个协程异常
    print("--- Method 1: try/except ---")
    try:
        result = await may_fail(2)
    except ValueError as e:
        print(f"  Caught exception: {e}")

    # 方式 2: gather 中使用 return_exceptions=True
    print("\n--- Method 2: gather + return_exceptions=True ---")
    results = await asyncio.gather(
        may_fail(1),
        may_fail(2),  # this one will fail
        may_fail(3),
        return_exceptions=True,
    )
    for i, r in enumerate(results):
        if isinstance(r, Exception):
            print(f"  result[{i}]: exception - {r}")
        else:
            print(f"  result[{i}]: {r}")
    print()


# ============================================================
# 主函数：运行所有演示
# ============================================================

async def main():
    demo_coroutine_object()

    await demo_await()
    await demo_sequential_vs_concurrent()
    await demo_exception_handling()

    print("=== Summary ===")
    print("1. async def defines a coroutine function; calling it returns a coroutine object (body not executed)")
    print("2. await suspends the current coroutine, waiting for the target awaitable to complete")
    print("3. asyncio.gather() concurrently starts multiple coroutines and waits for all to finish")
    print("4. Exception handling in coroutines is the same as synchronous code: use try/except")


if __name__ == "__main__":
    asyncio.run(main())
