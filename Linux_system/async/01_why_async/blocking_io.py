"""
同步阻塞 I/O 示例

演示：串行执行多个模拟 I/O 操作时，总耗时 = 单次耗时 × 任务数。
每个任务使用 time.sleep() 模拟网络请求的阻塞等待。
"""

import time


def simulate_io_task(task_id: int, duration: float = 1.0) -> str:
    """模拟一个阻塞的 I/O 操作（如 HTTP 请求）"""
    print(f"  [任务 {task_id}] 开始请求... (模拟 {duration}s 网络延迟)")
    time.sleep(duration)  # 线程在此完全阻塞，CPU 空转
    print(f"  [任务 {task_id}] 请求完成!")
    return f"任务{task_id}的结果"


def main():
    num_tasks = 5
    duration_per_task = 1.0  # 每个任务模拟 1 秒的 I/O 延迟

    print(f"=== 同步阻塞模式 ===")
    print(f"任务数: {num_tasks}, 每个任务 I/O 耗时: {duration_per_task}s")
    print(f"预期总耗时: {num_tasks * duration_per_task}s (串行执行)\n")

    start = time.perf_counter()

    results = []
    for i in range(num_tasks):
        result = simulate_io_task(i, duration_per_task)
        results.append(result)

    elapsed = time.perf_counter() - start

    print(f"\n结果: {results}")
    print(f"实际总耗时: {elapsed:.2f}s")
    print(f"结论: 同步阻塞模式下，5 个各需 1s 的 I/O 操作总共花了 ~5s")
    print(f"      线程在等待 I/O 时完全空转，CPU 利用率极低")


if __name__ == "__main__":
    main()
