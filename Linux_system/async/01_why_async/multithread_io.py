"""
多线程并发 I/O 示例

演示：使用多线程并行执行多个模拟 I/O 操作。
总耗时 ≈ 单次最长耗时（因为线程并行等待），但每个线程都有内存和切换开销。
"""

import time
import threading


def simulate_io_task(task_id: int, duration: float, results: dict):
    """模拟一个阻塞的 I/O 操作（在独立线程中运行）"""
    print(f"  [线程 {threading.current_thread().name}][任务 {task_id}] 开始请求...")
    time.sleep(duration)  # 这个线程阻塞，但其他线程可以继续运行
    results[task_id] = f"任务{task_id}的结果"
    print(f"  [线程 {threading.current_thread().name}][任务 {task_id}] 请求完成!")


def main():
    num_tasks = 5
    duration_per_task = 1.0

    print(f"=== 多线程并发模式 ===")
    print(f"任务数: {num_tasks}, 每个任务 I/O 耗时: {duration_per_task}s")
    print(f"预期总耗时: ~{duration_per_task}s (线程并行等待)\n")

    start = time.perf_counter()

    results = {}
    threads = []

    for i in range(num_tasks):
        t = threading.Thread(
            target=simulate_io_task,
            args=(i, duration_per_task, results),
            name=f"Worker-{i}",
        )
        threads.append(t)
        t.start()

    # 等待所有线程完成
    for t in threads:
        t.join()

    elapsed = time.perf_counter() - start

    print(f"\n结果: {dict(sorted(results.items()))}")
    print(f"实际总耗时: {elapsed:.2f}s")
    print(f"线程数: {num_tasks}")
    print()
    print(f"结论: 多线程模式下，5 个 I/O 操作并行等待，总耗时 ~1s")
    print(f"      但每个线程有 ~8MB 默认栈空间开销，且线程切换需要内核介入")
    print(f"      当并发数达到数千时，线程开销会成为瓶颈：")
    print(f"        - 内存: 1000 线程 × 8MB = ~8GB")
    print(f"        - 上下文切换: 内核态/用户态切换、寄存器保存/恢复、TLB 刷新")


if __name__ == "__main__":
    main()
