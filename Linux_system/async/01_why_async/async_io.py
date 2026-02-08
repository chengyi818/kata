"""
异步 I/O 示例

演示：使用 asyncio 协程并发执行多个模拟 I/O 操作。
总耗时 ≈ 单次最长耗时，且所有协程运行在单个线程中，开销极小。
"""

import asyncio
import time


async def simulate_io_task(task_id: int, duration: float = 1.0) -> str:
    """模拟一个异步 I/O 操作

    关键区别：这里使用 asyncio.sleep() 而非 time.sleep()。
    - time.sleep() 会阻塞整个线程
    - asyncio.sleep() 会挂起当前协程，让出控制权给 event loop
      event loop 可以趁机去运行其他就绪的协程
    """
    print(f"  [协程][任务 {task_id}] 开始请求...")
    await asyncio.sleep(duration)  # 协程在此挂起，event loop 去执行其他协程
    print(f"  [协程][任务 {task_id}] 请求完成!")
    return f"任务{task_id}的结果"


async def main():
    num_tasks = 5
    duration_per_task = 1.0

    print(f"=== 异步协程模式 ===")
    print(f"任务数: {num_tasks}, 每个任务 I/O 耗时: {duration_per_task}s")
    print(f"预期总耗时: ~{duration_per_task}s (协程并发等待，单线程)\n")

    start = time.perf_counter()

    # asyncio.gather() 并发启动所有协程
    # 内部原理：
    #   1. 每个协程被包装成一个 Task（Future 的子类）
    #   2. 所有 Task 注册到 event loop
    #   3. event loop 循环检查哪些 Task 可以推进（对应的 I/O 就绪）
    #   4. 就绪的 Task 被恢复执行，执行到下一个 await 点再挂起
    tasks = [simulate_io_task(i, duration_per_task) for i in range(num_tasks)]
    results = await asyncio.gather(*tasks)

    elapsed = time.perf_counter() - start

    print(f"\n结果: {list(results)}")
    print(f"实际总耗时: {elapsed:.2f}s")
    print(f"线程数: 1 (所有协程在同一个线程的 event loop 中调度)")
    print()
    print(f"结论: 异步模式下，5 个 I/O 操作在单线程中并发等待，总耗时 ~1s")
    print(f"      与多线程方案相比：")
    print(f"        - 无额外线程创建开销（协程仅需 KB 级内存）")
    print(f"        - 无内核态上下文切换（协程切换在用户态完成）")
    print(f"        - 无锁/同步问题（单线程天然无数据竞争）")
    print(f"        - 可轻松支持数十万并发连接")
    print()
    print(f"=== 执行流程图 ===")
    print(f"  Event Loop:  ──┬── 启动任务0 ── await sleep ──┐")
    print(f"                 ├── 启动任务1 ── await sleep ──┤")
    print(f"                 ├── 启动任务2 ── await sleep ──┤ 所有协程同时")
    print(f"                 ├── 启动任务3 ── await sleep ──┤ 等待 1 秒")
    print(f"                 ├── 启动任务4 ── await sleep ──┤")
    print(f"                 │         (event loop 空闲等待) │")
    print(f"                 │       1 秒后所有 sleep 到期   │")
    print(f"                 ├── 恢复任务0 ── 完成 ─────────┤")
    print(f"                 ├── 恢复任务1 ── 完成 ─────────┤")
    print(f"                 ├── 恢复任务2 ── 完成 ─────────┤")
    print(f"                 ├── 恢复任务3 ── 完成 ─────────┤")
    print(f"                 └── 恢复任务4 ── 完成 ─────────┘")


if __name__ == "__main__":
    asyncio.run(main())
