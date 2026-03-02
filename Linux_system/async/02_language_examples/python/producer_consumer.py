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
        delay = random.uniform(0.1, 0.5)
        await asyncio.sleep(delay)

        item = f"{name}-item{i}"
        await queue.put(item)
        print(f"  [Producer {name}] produced: {item} (queue size: {queue.qsize()})")

    print(f"  [Producer {name}] finished all production")


async def consumer(name: str, queue: asyncio.Queue):
    """消费者：从队列获取数据并处理

    注意这是一个无限循环，依赖外部取消机制来停止。
    """
    processed = 0
    while True:
        try:
            item = await asyncio.wait_for(queue.get(), timeout=2.0)
        except asyncio.TimeoutError:
            print(f"  [Consumer {name}] timed out, processed {processed} items total")
            return

        process_time = random.uniform(0.05, 0.2)
        await asyncio.sleep(process_time)

        queue.task_done()
        processed += 1
        print(f"  [Consumer {name}] processed: {item} (took {process_time:.2f}s)")


async def demo_basic_producer_consumer():
    """基本的生产者-消费者模式"""
    print("=== 1. Basic Producer-Consumer Pattern ===\n")

    queue: asyncio.Queue[str] = asyncio.Queue(maxsize=5)

    start = time.perf_counter()

    producers = [
        asyncio.create_task(producer(f"P{i}", queue, 5))
        for i in range(2)
    ]
    consumers = [
        asyncio.create_task(consumer(f"C{i}", queue))
        for i in range(3)
    ]

    await asyncio.gather(*producers)
    print(f"\n  All producers finished, waiting for queue to drain...")

    await queue.join()
    print(f"  Queue drained!")

    for c in consumers:
        c.cancel()

    await asyncio.gather(*consumers, return_exceptions=True)

    elapsed = time.perf_counter() - start
    print(f"\n  Total elapsed: {elapsed:.2f}s")
    print()


# ============================================================
# 进阶：带优先级的任务队列
# ============================================================

async def priority_producer(queue: asyncio.PriorityQueue, num_items: int):
    """生产带优先级的任务"""
    for i in range(num_items):
        priority = random.randint(1, 5)  # 1 = highest priority
        item = (priority, f"Task{i}(priority={priority})")
        await queue.put(item)
        await asyncio.sleep(0.05)
    print(f"  [PriorityProducer] produced {num_items} tasks")


async def priority_consumer(name: str, queue: asyncio.PriorityQueue):
    """按优先级消费任务"""
    while not queue.empty():
        priority, item = await queue.get()
        print(f"  [Consumer {name}] processing {item}")
        await asyncio.sleep(0.1)
        queue.task_done()


async def demo_priority_queue():
    """优先级队列示例"""
    print("=== 2. Priority Task Queue ===\n")

    queue: asyncio.PriorityQueue = asyncio.PriorityQueue()

    await priority_producer(queue, 10)
    print()

    consumers = [
        asyncio.create_task(priority_consumer(f"C{i}", queue))
        for i in range(2)
    ]
    await asyncio.gather(*consumers)
    print()
    print("  Note: tasks with lower priority numbers are processed first (PriorityQueue is a min-heap)")
    print()


# ============================================================
# 进阶：限流（Semaphore）
# ============================================================

async def rate_limited_fetch(sem: asyncio.Semaphore, url: str) -> str:
    """使用信号量限制并发数"""
    async with sem:
        print(f"  Start fetching {url}")
        await asyncio.sleep(random.uniform(0.3, 0.8))
        print(f"  Done fetching {url}")
        return f"result of {url}"


async def demo_semaphore():
    """信号量限流示例"""
    print("=== 3. Semaphore Rate Limiting ===\n")

    semaphore = asyncio.Semaphore(3)
    urls = [f"https://api.example.com/page/{i}" for i in range(8)]

    print(f"  Total requests: {len(urls)}, max concurrency: 3")
    print(f"  Observe: at most 3 requests are running at the same time\n")

    start = time.perf_counter()
    results = await asyncio.gather(
        *[rate_limited_fetch(semaphore, url) for url in urls]
    )
    elapsed = time.perf_counter() - start

    print(f"\n  All requests done, result count: {len(results)}")
    print(f"  Total elapsed: {elapsed:.2f}s")
    print(f"  Without rate limit (8 concurrent): ~0.8s")
    print(f"  With rate limit (3 concurrent): ~{0.55 * 3:.1f}s (three batches)")
    print()


# ============================================================
# 主函数
# ============================================================

async def main():
    await demo_basic_producer_consumer()
    await demo_priority_queue()
    await demo_semaphore()

    print("=== Summary ===")
    print("  asyncio.Queue:         FIFO async queue, decouples producers and consumers")
    print("  asyncio.PriorityQueue: priority queue, processes tasks by priority")
    print("  asyncio.Semaphore:     semaphore rate limiter, controls max concurrency")
    print("  queue.join():          wait until all items in the queue have been processed")
    print("  queue.task_done():     notify the queue that a consumed item has been processed")


if __name__ == "__main__":
    asyncio.run(main())
