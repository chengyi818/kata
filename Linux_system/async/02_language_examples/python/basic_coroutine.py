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
    print("=== 1. 协程函数 vs 普通函数 ===\n")

    # 普通函数：直接返回结果
    result = regular_function()
    print(f"regular_function() 返回: {result!r}  (类型: {type(result).__name__})")

    # 协程函数：返回协程对象
    coro = coroutine_function()
    print(f"coroutine_function() 返回: {coro!r}  (类型: {type(coro).__name__})")
    print("  注意：函数体还没有执行！只是创建了协程对象。")
    print("  协程对象必须被 await 或提交给 event loop 才会执行。")

    # 关闭未使用的协程，避免 RuntimeWarning
    coro.close()
    print()


# ============================================================
# 2. await 的语义：挂起当前协程，等待另一个可等待对象完成
# ============================================================

async def fetch_data(url: str, delay: float) -> str:
    """模拟一个异步网络请求"""
    print(f"  开始请求 {url}...")
    await asyncio.sleep(delay)  # 挂起当前协程，让出 CPU
    print(f"  {url} 响应完成!")
    return f"来自 {url} 的数据"


async def demo_await():
    """演示 await 的执行流程"""
    print("=== 2. await 的语义 ===\n")

    print("步骤 1: 调用 fetch_data() 创建协程")
    print("步骤 2: await 协程 —— 挂起当前协程，开始执行 fetch_data")
    print("步骤 3: fetch_data 内部 await asyncio.sleep() —— 再次挂起")
    print("步骤 4: sleep 结束后，fetch_data 恢复执行并返回")
    print("步骤 5: demo_await 收到返回值，继续执行\n")

    result = await fetch_data("https://api.example.com", 0.5)
    print(f"  收到结果: {result}")
    print()


# ============================================================
# 3. 协程并发执行：await 的串行 vs gather 的并发
# ============================================================

async def demo_sequential_vs_concurrent():
    """对比串行 await 和并发 gather"""
    print("=== 3. 串行 vs 并发 ===\n")

    import time

    # --- 串行 await ---
    print("--- 串行 await (一个完成后才开始下一个) ---")
    start = time.perf_counter()

    r1 = await fetch_data("site-A", 1.0)
    r2 = await fetch_data("site-B", 1.0)

    elapsed = time.perf_counter() - start
    print(f"  串行结果: [{r1}, {r2}]")
    print(f"  串行耗时: {elapsed:.2f}s (1s + 1s = 2s)\n")

    # --- 并发 gather ---
    print("--- asyncio.gather (所有协程并发执行) ---")
    start = time.perf_counter()

    r1, r2 = await asyncio.gather(
        fetch_data("site-A", 1.0),
        fetch_data("site-B", 1.0),
    )

    elapsed = time.perf_counter() - start
    print(f"  并发结果: [{r1}, {r2}]")
    print(f"  并发耗时: {elapsed:.2f}s (两个 1s 的请求并发，总计 ~1s)\n")

    print("关键理解：")
    print("  - 串行 await: 每个 await 都会等待协程完成后才继续")
    print("  - gather:    所有协程同时启动，event loop 在它们之间切换")
    print("  - 对于 I/O 密集型任务，gather 可以大幅减少总耗时")
    print()


# ============================================================
# 4. 协程的异常处理
# ============================================================

async def may_fail(task_id: int):
    """一个可能失败的协程"""
    await asyncio.sleep(0.1)
    if task_id == 2:
        raise ValueError(f"任务 {task_id} 失败了!")
    return f"任务{task_id}成功"


async def demo_exception_handling():
    """演示协程中的异常处理"""
    print("=== 4. 协程的异常处理 ===\n")

    # 方式 1: try/except 捕获单个协程异常
    print("--- 方式 1: try/except ---")
    try:
        result = await may_fail(2)
    except ValueError as e:
        print(f"  捕获异常: {e}")

    # 方式 2: gather 中使用 return_exceptions=True
    print("\n--- 方式 2: gather + return_exceptions=True ---")
    results = await asyncio.gather(
        may_fail(1),
        may_fail(2),  # 这个会失败
        may_fail(3),
        return_exceptions=True,  # 异常作为返回值而非抛出
    )
    for i, r in enumerate(results):
        if isinstance(r, Exception):
            print(f"  结果[{i}]: 异常 - {r}")
        else:
            print(f"  结果[{i}]: {r}")
    print()


# ============================================================
# 主函数：运行所有演示
# ============================================================

async def main():
    demo_coroutine_object()

    await demo_await()
    await demo_sequential_vs_concurrent()
    await demo_exception_handling()

    print("=== 总结 ===")
    print("1. async def 定义协程函数，调用它返回协程对象（不执行函数体）")
    print("2. await 挂起当前协程，等待目标可等待对象（awaitable）完成")
    print("3. asyncio.gather() 并发启动多个协程，等待全部完成")
    print("4. 协程中的异常处理与同步代码一致，使用 try/except")


if __name__ == "__main__":
    asyncio.run(main())
