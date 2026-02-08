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
    print("=== 1. asyncio.Future 基本概念 ===\n")

    loop = asyncio.get_running_loop()

    # 手动创建一个 Future
    future = loop.create_future()
    print(f"  Future 创建后状态: done={future.done()}, cancelled={future.cancelled()}")

    # 在后台任务中设置 Future 的结果
    async def set_result_later():
        await asyncio.sleep(0.5)
        future.set_result("Future 的结果值")
        print("  [后台] 已设置 Future 的结果")

    # 启动后台任务
    asyncio.create_task(set_result_later())

    # 等待 Future 完成
    print("  等待 Future 完成...")
    result = await future
    print(f"  Future 完成! 结果: {result}")
    print(f"  Future 状态: done={future.done()}")
    print()

    print("  核心理解:")
    print("    - Future 是一个容器，最初为空（pending 状态）")
    print("    - 某人在某处调用 set_result() 后，Future 变为完成状态")
    print("    - await future 会挂起当前协程，直到 Future 完成")
    print("    - 这就是 Promise/Future 模式的核心思想")
    print()


# ============================================================
# 2. Task：封装协程执行的 Future
# ============================================================

async def slow_operation(name: str, duration: float) -> str:
    """模拟耗时操作"""
    print(f"    [{name}] 开始 (预计 {duration}s)")
    await asyncio.sleep(duration)
    print(f"    [{name}] 完成")
    return f"{name}的结果"


async def demo_task():
    """演示 Task 的创建与管理

    Task 是 Future 的子类。当你用 asyncio.create_task() 包装一个协程时：
    1. 协程被调度到 event loop 中
    2. 返回一个 Task 对象（可以 await、取消、检查状态）
    3. Task 内部驱动协程的执行：每次协程 yield（遇到 await）时，
       Task 负责在适当时机恢复协程
    """
    print("=== 2. asyncio.Task 与调度 ===\n")

    print("--- 创建 Task 后立即开始调度 ---")
    task1 = asyncio.create_task(slow_operation("任务A", 1.0))
    task2 = asyncio.create_task(slow_operation("任务B", 0.5))

    print(f"  task1 类型: {type(task1).__name__}, 状态: done={task1.done()}")
    print(f"  task2 类型: {type(task2).__name__}, 状态: done={task2.done()}")
    print()

    # 注意：create_task 之后，协程已经开始在 event loop 中调度了
    # 但还没有执行（因为当前协程还没有让出控制权）
    # 直到我们 await 某个东西，event loop 才有机会执行 task1 和 task2

    print("--- await task 获取结果 ---")
    result1 = await task1
    result2 = await task2
    print(f"  task1 结果: {result1}")
    print(f"  task2 结果: {result2}")
    print()


# ============================================================
# 3. Task 的取消机制
# ============================================================

async def long_running_task(name: str):
    """一个长时间运行的任务"""
    try:
        print(f"    [{name}] 开始执行...")
        await asyncio.sleep(10.0)  # 模拟长时间操作
        print(f"    [{name}] 正常完成")  # 如果被取消，不会执行到这里
        return f"{name}完成"
    except asyncio.CancelledError:
        print(f"    [{name}] 被取消了! 执行清理工作...")
        # 在此处可以做资源清理
        raise  # 必须重新抛出 CancelledError


async def demo_cancellation():
    """演示 Task 的取消"""
    print("=== 3. Task 取消机制 ===\n")

    task = asyncio.create_task(long_running_task("长任务"))

    # 等一小会后取消任务
    await asyncio.sleep(0.5)
    print(f"  取消前: done={task.done()}, cancelled={task.cancelled()}")

    task.cancel()
    print("  已请求取消...")

    # await 已取消的 task 会抛出 CancelledError
    try:
        await task
    except asyncio.CancelledError:
        print(f"  取消后: done={task.done()}, cancelled={task.cancelled()}")

    print()
    print("  核心理解:")
    print("    - cancel() 不会立即终止协程，而是在下一个 await 点注入 CancelledError")
    print("    - 协程可以 try/except CancelledError 来做清理工作")
    print("    - 捕获后应该重新 raise，否则取消会被吞掉")
    print()


# ============================================================
# 4. asyncio.wait() —— 更灵活的等待策略
# ============================================================

async def demo_wait():
    """演示 asyncio.wait 的不同策略"""
    print("=== 4. asyncio.wait() 高级用法 ===\n")

    tasks = [
        asyncio.create_task(slow_operation(f"任务{i}", duration))
        for i, duration in enumerate([2.0, 0.5, 1.0, 0.3, 1.5])
    ]

    # --- FIRST_COMPLETED: 只要有一个完成就返回 ---
    print("--- wait(FIRST_COMPLETED): 第一个完成时返回 ---")
    done, pending = await asyncio.wait(tasks, return_when=asyncio.FIRST_COMPLETED)
    print(f"  完成数: {len(done)}, 未完成数: {len(pending)}")
    for t in done:
        print(f"  已完成: {t.result()}")

    # --- 等待剩余全部完成 ---
    print("\n--- wait(ALL_COMPLETED): 等待剩余全部完成 ---")
    done, pending = await asyncio.wait(pending, return_when=asyncio.ALL_COMPLETED)
    print(f"  完成数: {len(done)}, 未完成数: {len(pending)}")
    for t in done:
        print(f"  已完成: {t.result()}")
    print()

    print("  核心理解:")
    print("    - gather(): 简单并发，等待全部完成，返回有序结果列表")
    print("    - wait():   灵活控制，支持 FIRST_COMPLETED / FIRST_EXCEPTION / ALL_COMPLETED")
    print("    - as_completed(): 返回迭代器，按完成顺序产出 Task")
    print()


# ============================================================
# 5. asyncio.as_completed() —— 按完成顺序处理
# ============================================================

async def demo_as_completed():
    """演示 asyncio.as_completed"""
    print("=== 5. asyncio.as_completed() ===\n")

    durations = {"快速任务": 0.3, "中速任务": 0.7, "慢速任务": 1.2}
    coros = [slow_operation(name, dur) for name, dur in durations.items()]

    start = time.perf_counter()
    print("  按完成顺序获取结果:")
    for coro in asyncio.as_completed(coros):
        result = await coro
        elapsed = time.perf_counter() - start
        print(f"    {elapsed:.2f}s - 获得: {result}")
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

    print("=== 总结 ===")
    print("  Future: 异步结果的占位符，最底层的可等待对象")
    print("  Task:   Future 的子类，封装协程并驱动其执行")
    print("  create_task(): 将协程调度到 event loop，返回 Task")
    print("  gather(): 并发等待多个协程，返回结果列表")
    print("  wait():   灵活控制等待策略（首个完成/全部完成）")
    print("  as_completed(): 按完成顺序迭代处理结果")


if __name__ == "__main__":
    asyncio.run(main())
