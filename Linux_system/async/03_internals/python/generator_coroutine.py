"""
从 Generator 到 Coroutine 的演进历史

Python 的协程不是凭空出现的，而是从生成器逐步演化而来：

  Python 2.2  → yield 语句（PEP 255）：基本的生成器
  Python 2.5  → send()/throw()/close()（PEP 342）：协程的雏形
  Python 3.3  → yield from（PEP 380）：委托生成器，简化协程链
  Python 3.4  → @asyncio.coroutine + yield from（PEP 3156）：异步框架
  Python 3.5  → async/await 语法（PEP 492）：原生协程
  Python 3.10 → aiter()/anext() 内置函数
  Python 3.11 → TaskGroup，异常组

本文件沿着这条演进路线，展示每个阶段的实现方式。
"""

import asyncio
import sys

print(f"Python {sys.version}\n")

# ============================================================
# 阶段 1：基本生成器 (Python 2.2+)
# ============================================================

print("=" * 60)
print("阶段 1: 基本生成器 yield (PEP 255)")
print("=" * 60)

def simple_generator():
    """最基本的生成器：yield 产出值，函数在 yield 处挂起"""
    print("    生成器开始")
    yield 1
    print("    第一次恢复")
    yield 2
    print("    第二次恢复")
    yield 3
    print("    生成器结束")

print("\n  生成器的本质是一个可以暂停和恢复的函数：")
gen = simple_generator()
print(f"  类型: {type(gen)}")
for val in gen:
    print(f"  获取值: {val}")

print("""
  关键理解：
    - yield 使函数变成生成器函数
    - 调用生成器函数返回生成器对象（不执行函数体）
    - next() 执行到下一个 yield，返回 yield 后的值
    - 函数状态（局部变量、执行位置）保存在生成器对象中
""")


# ============================================================
# 阶段 2：send() 双向通信 (Python 2.5+)
# ============================================================

print("=" * 60)
print("阶段 2: send() 双向通信 (PEP 342)")
print("=" * 60)

def coroutine_v1():
    """使用 send() 实现双向通信的'协程'

    yield 不仅可以产出值，还可以接收值：
      received = yield produced
    """
    print("    协程启动")
    received = yield "我准备好了"  # 产出 "我准备好了"，等待接收
    print(f"    收到: {received}")
    received = yield f"处理了 {received}"  # 产出处理结果，等待下一个输入
    print(f"    收到: {received}")
    yield f"最终处理了 {received}"

print("\n  send() 让生成器变成了双向通信的协程：")
coro = coroutine_v1()

# 第一次必须 send(None) 或 next() 来启动
msg = next(coro)            # 等价于 coro.send(None)
print(f"  协程产出: {msg}")

msg = coro.send("任务A")    # 发送值给协程，获取下一个产出
print(f"  协程产出: {msg}")

msg = coro.send("任务B")
print(f"  协程产出: {msg}")

print("""
  关键理解：
    - send(value) 恢复生成器，并将 value 作为 yield 表达式的值
    - 这使得生成器可以作为"协程"使用：接收输入，产出输出
    - 这就是 Python 协程的雏形！
    - 同时还有 throw() 注入异常和 close() 关闭协程
""")


# ============================================================
# 阶段 3：yield from 委托 (Python 3.3+)
# ============================================================

print("=" * 60)
print("阶段 3: yield from 委托 (PEP 380)")
print("=" * 60)

def sub_generator():
    """子生成器"""
    yield "sub-1"
    yield "sub-2"
    return "sub 的返回值"  # 生成器的 return 值通过 StopIteration 传递

def delegating_generator():
    """委托生成器：yield from 自动处理子生成器的所有交互"""
    print("    委托开始")
    # yield from 会：
    # 1. 自动迭代 sub_generator
    # 2. 将每个 yield 值传递给外部调用者
    # 3. 将外部 send() 的值传递给子生成器
    # 4. 处理子生成器的 return 值（StopIteration.value）
    result = yield from sub_generator()
    print(f"    子生成器返回: {result}")
    yield "delegate-done"

print("\n  yield from 自动代理整个子生成器的交互：")
gen = delegating_generator()
for val in gen:
    print(f"  获取: {val}")

print()

# --- yield from 对比手动委托 ---
print("  没有 yield from 时，手动委托非常繁琐：")

def manual_delegation():
    """手动实现 yield from 的等价逻辑（简化版）"""
    sub = sub_generator()
    try:
        value = next(sub)
        while True:
            received = yield value  # 转发产出值，接收外部 send 的值
            value = sub.send(received)  # 转发给子生成器
    except StopIteration as e:
        result = e.value  # 子生成器的 return 值
        print(f"    手动委托：子生成器返回 {result}")

gen = manual_delegation()
for val in gen:
    print(f"  手动获取: {val}")

print("""
  关键理解：
    - yield from 是协程组合的关键——让你可以像调用函数一样调用子协程
    - 它自动处理 send/throw/close 的传播
    - 子生成器的 return 值成为 yield from 表达式的值
    - 这为 async/await 奠定了基础
""")


# ============================================================
# 阶段 4：asyncio + yield from (Python 3.4)
# ============================================================

print("=" * 60)
print("阶段 4: @asyncio.coroutine + yield from (Python 3.4)")
print("=" * 60)

print("""
  Python 3.4 引入了 asyncio 模块，使用装饰器标记协程：

  @asyncio.coroutine
  def old_style_coro():
      yield from asyncio.sleep(1)
      return "完成"

  这种风格现在已被 async/await 取代，但原理完全相同：
    yield from asyncio.sleep(1)  ≡  await asyncio.sleep(1)

  asyncio.sleep() 返回一个 Future 对象，
  Future 的 __iter__ 方法（即 __await__ 在旧式协程中的等价物）
  会 yield 自己给 event loop，然后等待被 set_result() 唤醒。
""")


# ============================================================
# 阶段 5：async/await 原生协程 (Python 3.5+)
# ============================================================

print("=" * 60)
print("阶段 5: async/await 原生协程 (PEP 492)")
print("=" * 60)

async def modern_coroutine():
    """现代异步协程"""
    await asyncio.sleep(0.1)
    return "现代协程完成"

_coro = modern_coroutine()
_coro_type_name = type(_coro).__name__
_coro.close()

print(f"""
  async def 创建的协程类型: {_coro_type_name}

  async/await 相比 yield from 的改进：
    1. 语义清晰：async 明确标记异步函数，await 明确标记挂起点
    2. 类型区分：原生协程 (coroutine) ≠ 生成器 (generator)
       - 不能对协程使用 next()
       - 不能在非 async 函数中使用 await
    3. 新增 async for 和 async with 语法
    4. 编译器可以检查误用（如忘记 await）
""")


# ============================================================
# 阶段 6：演示协程与生成器的内在联系
# ============================================================

print("=" * 60)
print("阶段 6: 协程与生成器的内在联系")
print("=" * 60)

# 用生成器模拟 async/await
def fake_sleep(seconds):
    """用生成器模拟 asyncio.sleep"""
    yield ("sleep", seconds)

def fake_async_task():
    """用 yield from 模拟 await"""
    print("    [fake] 开始任务")
    yield from fake_sleep(1.0)
    print("    [fake] sleep 完成")
    yield from fake_sleep(0.5)
    print("    [fake] 任务完成")
    return "fake 结果"

print("\n  手动驱动'协程'（模拟 event loop）：")
coro = fake_async_task()
try:
    while True:
        command = next(coro)
        print(f"    Event Loop 收到命令: {command}")
        # 在真正的 event loop 中，这里会注册定时器
        # 定时器到期后调用 coro.send(None) 恢复协程
except StopIteration as e:
    print(f"    协程返回: {e.value}")

print("""
  这个例子揭示了异步编程的本质：
    1. 协程 yield 命令给 event loop（如 "sleep 1秒"）
    2. Event loop 注册对应的 I/O 操作或定时器
    3. 操作完成后，event loop 调用 send() 恢复协程
    4. 协程继续执行到下一个 yield 或 return

  async/await 只是让这个过程的语法更优雅，
  底层机制完全基于生成器的 yield/send 协议！
""")


# ============================================================
# 总结时间线
# ============================================================

print("=" * 60)
print("总结：Python 异步编程的演进时间线")
print("=" * 60)
print("""
  2001  Python 2.2   yield 语句               → 基本生成器
  2005  Python 2.5   send()/throw()/close()   → 协程雏形
  2009  Python 3.0   (生成器语法改进)
  2012  Python 3.3   yield from               → 协程组合
  2014  Python 3.4   asyncio + @coroutine     → 异步框架
  2015  Python 3.5   async/await              → 原生协程语法
  2016  Python 3.6   async generators         → async def + yield
  2020  Python 3.10  aiter()/anext() 内置函数
  2022  Python 3.11  TaskGroup, ExceptionGroup → 结构化并发

  核心洞察：
    yield → yield from → await
    是同一个机制的三个语法层次，
    本质都是"挂起函数执行，保存状态，稍后恢复"。
""")
