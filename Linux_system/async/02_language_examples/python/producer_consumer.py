"""
Python 异步编程实战：生产者-消费者模式

使用 asyncio.Queue 实现经典的生产者-消费者模式，
展示异步编程在实际场景中的应用。

场景模拟：
  - 多个生产者异步爬取网页，将结果放入队列
  - 多个消费者从队列取出数据并处理（如解析、存储）
  - 生产者和消费者之间通过 asyncio.Queue 解耦
"""

import asyncio
import random
import time


async def producer(name: str, queue: asyncio.Queue, num_items: int):
    """生产者：模拟异步爬取网页，将数据放入队列"""
    for i in range(num_items):
        # 模拟网络请求的随机延迟
        delay = random.uniform(0.1, 0.5)
        await asyncio.sleep(delay)

        item = f"{name}-数据{i}"
        await queue.put(item)
        print(f"  [生产者 {name}] 生产: {item} (队列大小: {queue.qsize()})")

    print(f"  [生产者 {name}] 已完成所有生产")


async def consumer(name: str, queue: asyncio.Queue):
    """消费者：从队列获取数据并处理

    注意这是一个无限循环，依赖外部取消机制来停止。
    """
    processed = 0
    while True:
        try:
            # 从队列获取数据，如果队列为空则挂起等待
            item = await asyncio.wait_for(queue.get(), timeout=2.0)
        except asyncio.TimeoutError:
            # 超时说明可能没有更多数据了
            print(f"  [消费者 {name}] 超时退出，共处理 {processed} 项")
            return

        # 模拟数据处理
        process_time = random.uniform(0.05, 0.2)
        await asyncio.sleep(process_time)

        queue.task_done()
        processed += 1
        print(f"  [消费者 {name}] 处理: {item} (耗时 {process_time:.2f}s)")


async def demo_basic_producer_consumer():
    """基本的生产者-消费者模式"""
    print("=== 1. 基本生产者-消费者模式 ===\n")

    # 创建有界队列（maxsize 限制队列大小，满时 put 会阻塞）
    queue: asyncio.Queue[str] = asyncio.Queue(maxsize=5)

    start = time.perf_counter()

    # 启动 2 个生产者和 3 个消费者
    producers = [
        asyncio.create_task(producer(f"P{i}", queue, 5))
        for i in range(2)
    ]
    consumers = [
        asyncio.create_task(consumer(f"C{i}", queue))
        for i in range(3)
    ]

    # 等待所有生产者完成
    await asyncio.gather(*producers)
    print(f"\n  所有生产者已完成，等待队列清空...")

    # 等待队列中所有项被处理
    await queue.join()
    print(f"  队列已清空!")

    # 取消消费者（它们是无限循环，需要显式取消）
    for c in consumers:
        c.cancel()

    # 等待消费者优雅退出
    await asyncio.gather(*consumers, return_exceptions=True)

    elapsed = time.perf_counter() - start
    print(f"\n  总耗时: {elapsed:.2f}s")
    print()


# ============================================================
# 进阶：带优先级的任务队列
# ============================================================

async def priority_producer(queue: asyncio.PriorityQueue, num_items: int):
    """生产带优先级的任务"""
    for i in range(num_items):
        priority = random.randint(1, 5)  # 1 = 最高优先级
        item = (priority, f"任务{i}(优先级{priority})")
        await queue.put(item)
        await asyncio.sleep(0.05)
    print(f"  [优先级生产者] 已生产 {num_items} 个任务")


async def priority_consumer(name: str, queue: asyncio.PriorityQueue):
    """按优先级消费任务"""
    while not queue.empty():
        priority, item = await queue.get()
        print(f"  [消费者 {name}] 处理 {item}")
        await asyncio.sleep(0.1)
        queue.task_done()


async def demo_priority_queue():
    """优先级队列示例"""
    print("=== 2. 优先级任务队列 ===\n")

    queue: asyncio.PriorityQueue = asyncio.PriorityQueue()

    # 先生产所有任务
    await priority_producer(queue, 10)
    print()

    # 再启动消费者（会按优先级顺序消费）
    consumers = [
        asyncio.create_task(priority_consumer(f"C{i}", queue))
        for i in range(2)
    ]
    await asyncio.gather(*consumers)
    print()
    print("  注意：低优先级数字的任务先被处理（PriorityQueue 是最小堆）")
    print()


# ============================================================
# 进阶：限流（Semaphore）
# ============================================================

async def rate_limited_fetch(sem: asyncio.Semaphore, url: str) -> str:
    """使用信号量限制并发数"""
    async with sem:
        # 同一时刻最多只有 sem 个协程在此区域内
        print(f"  开始请求 {url}")
        await asyncio.sleep(random.uniform(0.3, 0.8))
        print(f"  完成请求 {url}")
        return f"{url}的结果"


async def demo_semaphore():
    """信号量限流示例"""
    print("=== 3. Semaphore 限流 ===\n")

    # 限制最大并发数为 3
    semaphore = asyncio.Semaphore(3)
    urls = [f"https://api.example.com/page/{i}" for i in range(8)]

    print(f"  总请求数: {len(urls)}, 最大并发: 3")
    print(f"  观察输出：同时最多只有 3 个请求在执行\n")

    start = time.perf_counter()
    results = await asyncio.gather(
        *[rate_limited_fetch(semaphore, url) for url in urls]
    )
    elapsed = time.perf_counter() - start

    print(f"\n  所有请求完成，结果数: {len(results)}")
    print(f"  总耗时: {elapsed:.2f}s")
    print(f"  如果无限流（8 个并发）: ~0.8s")
    print(f"  限流到 3 个并发后: ~{0.55 * 3:.1f}s (三批)")
    print()


# ============================================================
# 主函数
# ============================================================

async def main():
    await demo_basic_producer_consumer()
    await demo_priority_queue()
    await demo_semaphore()

    print("=== 总结 ===")
    print("  asyncio.Queue:         FIFO 异步队列，生产者-消费者解耦")
    print("  asyncio.PriorityQueue: 优先级队列，按优先级处理任务")
    print("  asyncio.Semaphore:     信号量限流，控制最大并发数")
    print("  queue.join():          等待队列中所有项被处理完")
    print("  queue.task_done():     消费者处理完一项后通知队列")


if __name__ == "__main__":
    asyncio.run(main())
