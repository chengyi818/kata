"""
CPython 字节码层面分析协程

使用 dis 模块反汇编协程函数，观察 CPython 虚拟机如何处理 async/await。

关键字节码指令：
  - GET_AWAITABLE:   将对象转换为可等待的迭代器
  - SEND:            向协程/生成器发送值并获取下一个产出值 (Python 3.12+)
  - YIELD_VALUE:     挂起协程/生成器，向调用者返回值
  - RETURN_VALUE:    协程完成，返回最终结果
  - RESUME:          协程/生成器被恢复时的入口点 (Python 3.11+)

注意：字节码指令在不同 Python 版本间可能有差异，本文件基于 Python 3.11+ 分析。
"""

import dis
import sys
import types

print(f"Python 版本: {sys.version}\n")


# ============================================================
# 1. 对比普通函数、生成器、协程的字节码
# ============================================================

def regular_function():
    x = 1
    y = 2
    return x + y


def generator_function():
    x = 1
    yield x
    y = 2
    yield y


async def coroutine_function():
    x = 1
    y = 2
    return x + y


print("=" * 60)
print("1. 普通函数的字节码")
print("=" * 60)
dis.dis(regular_function)

print("\n" + "=" * 60)
print("2. 生成器函数的字节码")
print("=" * 60)
dis.dis(generator_function)
print(f"\n  注意：yield 被编译为 YIELD_VALUE 指令")
print(f"  生成器的 code flags: {generator_function.__code__.co_flags:#x}")
print(f"    CO_GENERATOR (0x20) = {bool(generator_function.__code__.co_flags & 0x20)}")

print("\n" + "=" * 60)
print("3. 协程函数的字节码")
print("=" * 60)
dis.dis(coroutine_function)
print(f"\n  注意：没有 await 的协程函数与普通函数字节码几乎相同")
print(f"  但 code flags 不同: {coroutine_function.__code__.co_flags:#x}")
print(f"    CO_COROUTINE (0x100) = {bool(coroutine_function.__code__.co_flags & 0x100)}")


# ============================================================
# 2. 含有 await 的协程字节码
# ============================================================

async def fetch_data():
    """模拟异步操作"""
    return "data"


async def process():
    """含 await 的协程"""
    result = await fetch_data()
    return result


print("\n" + "=" * 60)
print("4. 含 await 的协程字节码")
print("=" * 60)
dis.dis(process)
print("""
关键指令分析：
  1. LOAD_GLOBAL fetch_data    → 加载协程函数
  2. CALL                       → 调用协程函数，创建协程对象
  3. GET_AWAITABLE              → 将协程对象转换为迭代器协议
                                  (调用 __await__() 方法)
  4. SEND / YIELD_VALUE         → 执行协程：
     - SEND None 启动协程
     - 如果协程产出 (yield) 了值 → 当前协程也 YIELD_VALUE 挂起
     - 如果协程返回了 → 获取返回值，继续执行
""")


# ============================================================
# 3. 多层 await 的字节码传播
# ============================================================

async def inner():
    return 42

async def middle():
    val = await inner()
    return val + 1

async def outer():
    val = await middle()
    return val + 1

print("=" * 60)
print("5. 多层 await 的字节码")
print("=" * 60)
print("\n--- inner() ---")
dis.dis(inner)
print("\n--- middle() ---")
dis.dis(middle)
print("\n--- outer() ---")
dis.dis(outer)
print("""
多层 await 的执行链：
  outer() await → middle() await → inner()

  在 CPython 中，这形成了一个协程链：
  1. outer 调用 middle()，获得协程对象
  2. GET_AWAITABLE 将其转换为迭代器
  3. SEND None 启动 middle 协程
  4. middle 内部同样对 inner 做 GET_AWAITABLE + SEND
  5. inner 返回 42 (StopIteration(42))
  6. middle 收到 42，计算 43，返回 (StopIteration(43))
  7. outer 收到 43，计算 44，返回

  挂起时的传播：
  如果 inner 中 yield 了（如 await asyncio.sleep()），
  yield 的值会沿着链向上传播：
    inner YIELD_VALUE → middle YIELD_VALUE → outer YIELD_VALUE → event loop
  恢复时则反向传播：
    event loop SEND → outer → middle → inner
""")


# ============================================================
# 4. async for 和 async with 的字节码
# ============================================================

async def demo_async_for():
    """async for 的字节码"""
    class AsyncRange:
        def __init__(self, n):
            self.n = n
            self.i = 0
        def __aiter__(self):
            return self
        async def __anext__(self):
            if self.i >= self.n:
                raise StopAsyncIteration
            val = self.i
            self.i += 1
            return val

    async for i in AsyncRange(3):
        pass

async def demo_async_with():
    """async with 的字节码"""
    class AsyncCtx:
        async def __aenter__(self):
            return self
        async def __aexit__(self, *args):
            pass

    async with AsyncCtx() as ctx:
        pass

print("=" * 60)
print("6. async for 的字节码")
print("=" * 60)
dis.dis(demo_async_for)
print("""
  GET_AITER:  调用 __aiter__()，获取异步迭代器
  GET_ANEXT:  调用 __anext__()，获取下一个值的协程
  GET_AWAITABLE + SEND: 等待 __anext__() 协程完成
""")

print("\n" + "=" * 60)
print("7. async with 的字节码")
print("=" * 60)
dis.dis(demo_async_with)
print("""
  BEFORE_ASYNC_WITH: 调用 __aenter__()，获取协程
  GET_AWAITABLE + SEND: 等待 __aenter__() 完成
  ...执行 with 体...
  调用 __aexit__()
  GET_AWAITABLE + SEND: 等待 __aexit__() 完成
""")


# ============================================================
# 5. 查看协程对象的内部结构
# ============================================================

print("=" * 60)
print("8. 协程对象的内部结构")
print("=" * 60)

async def sample_coro(x):
    y = x + 1
    return y

coro = sample_coro(10)
print(f"""
  协程对象: {coro}
  类型: {type(coro)}

  关键属性:
    cr_code:      {coro.cr_code}          (字节码对象)
    cr_frame:     {coro.cr_frame}         (当前栈帧)
    cr_running:   {coro.cr_running}       (是否正在执行)
    cr_await:     {coro.cr_await}         (当前 await 的对象)
    cr_origin:    {getattr(coro, 'cr_origin', 'N/A')}  (创建追踪)

  这些属性与生成器的 gi_code, gi_frame 等是对应的。
  这证实了协程在 CPython 内部本质上就是生成器的变体。
""")
coro.close()


# ============================================================
# 6. 底层协议：__await__ 方法
# ============================================================

print("=" * 60)
print("9. __await__ 协议")
print("=" * 60)

print("""
  当 CPython 执行 GET_AWAITABLE 指令时，它会：
  1. 检查对象是否是协程对象 → 直接使用
  2. 否则，调用对象的 __await__() 方法
  3. __await__() 必须返回一个迭代器

  这就是为什么你可以自定义可等待对象：
""")

class CustomAwaitable:
    """自定义可等待对象"""
    def __await__(self):
        print("    __await__ 被调用!")
        # 产出控制权给 event loop
        yield "我正在等待..."
        # 恢复后继续
        return "自定义结果"

async def use_custom_awaitable():
    result = await CustomAwaitable()
    return result

# 手动驱动协程来观察协议
print("  手动驱动协程:")
coro = use_custom_awaitable()
try:
    # send(None) 启动协程
    yielded = coro.send(None)
    print(f"    协程产出: {yielded}")
    # send(None) 恢复协程
    coro.send(None)
except StopIteration as e:
    print(f"    协程返回: {e.value}")

print("""
  总结：
    await 的本质 = 迭代器协议
    协程挂起 = yield (YIELD_VALUE)
    协程恢复 = send() (SEND)
    协程完成 = raise StopIteration(返回值) (RETURN_VALUE)
""")
