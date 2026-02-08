# Rust 异步底层实现：状态机 + Pin + Executor

## 概述

Rust 的 async/await 是真正的零开销抽象 —— 编译器在编译期将协程转换为状态机，
没有运行时反射、没有 GC、没有隐藏的堆分配。

本章包含三个深入分析：

| 文件 | 内容 | 核心概念 |
|------|------|----------|
| `state_machine.rs` | 手动实现等价状态机 | 编译器变换过程 |
| `pin_unpin.rs` | Pin 机制详解 | 自引用问题与解决方案 |
| `mini_executor.rs` | 手写最小 executor | Waker 机制与任务调度 |

## 编译器变换：async fn → 状态机

### 变换规则

```rust
// 你写的代码
async fn example(x: i32) -> i32 {
    let a = x + 1;
    some_future.await;    // ← await 点 1
    let b = a * 2;
    another_future.await; // ← await 点 2
    a + b
}

// 编译器生成的等价代码（概念性）
enum ExampleStateMachine {
    State0 { x: i32 },
    State1 { a: i32, fut: SomeFuture },
    State2 { a: i32, b: i32, fut: AnotherFuture },
    Done,
}

impl Future for ExampleStateMachine {
    type Output = i32;

    fn poll(self: Pin<&mut Self>, cx: &mut Context) -> Poll<i32> {
        loop {
            match self.state {
                State0 { x } => {
                    let a = x + 1;
                    self.state = State1 { a, fut: some_future };
                }
                State1 { a, ref mut fut } => {
                    match Pin::new(fut).poll(cx) {
                        Pending => return Pending,
                        Ready(()) => {
                            let b = a * 2;
                            self.state = State2 { a, b, fut: another_future };
                        }
                    }
                }
                State2 { a, b, ref mut fut } => {
                    match Pin::new(fut).poll(cx) {
                        Pending => return Pending,
                        Ready(()) => {
                            self.state = Done;
                            return Ready(a + b);
                        }
                    }
                }
                Done => panic!("polled after completion"),
            }
        }
    }
}
```

### 关键观察

1. **每个 `.await` 是一个状态边界**
2. **只有跨 await 存活的变量被保存** —— 编译器做"活跃性分析"
3. **状态机大小 = max(各状态) + 判别标签** —— 类似 enum 的内存布局
4. **完全在编译期完成** —— 运行时没有额外开销

## Pin 机制

### 为什么需要 Pin

```
async fn problem() {
    let data = vec![1, 2, 3];
    let reference = &data;     // ← 借用 data
    yield_point().await;        // ← 挂起点
    use(reference);             // ← 恢复后使用 reference
}
```

编译器生成的状态机：
```
State1 {
    data: Vec<i32>,
    reference: &Vec<i32>,  // ← 指向同一结构体中的 data!
    fut: YieldPointFuture,
}
```

这是一个自引用结构体！如果被 move，reference 会变成悬垂指针。

### Pin 的保证

```
Pin<&mut T> where T: !Unpin
```

保证 T 不会被移动，从而：
- 自引用指针始终有效
- Future::poll(self: Pin<&mut Self>) 可以安全地访问自引用字段

## Waker 机制

```
Executor                          Future (Task)
   │                                  │
   │── poll(waker) ──────────────────►│
   │                                  │
   │◄── Pending ──────────────────────│ (保存 waker)
   │                                  │
   │    ... 等待 I/O ...              │
   │                                  │
   │◄── waker.wake() ────────────────│ (I/O 就绪，后台线程调用)
   │                                  │
   │── poll(waker) ──────────────────►│
   │                                  │
   │◄── Ready(value) ────────────────│
```

Waker 的本质是一个包含回调函数的胖指针：
- `wake()` 将对应的 Task 放回 executor 的就绪队列
- 通过 `RawWakerVTable` 实现多态

## 生成和分析汇编

```bash
# 未优化汇编（保留完整状态机结构）
cargo rustc --bin state_machine -- --emit asm -C opt-level=0

# 优化汇编
cargo rustc --bin state_machine -- --emit asm -C opt-level=2

# 查看 LLVM IR（更容易读懂）
cargo rustc --bin state_machine -- --emit llvm-ir -C opt-level=0
```

### 在汇编中寻找什么

1. **状态机枚举的判别标签**：
   ```asm
   cmp     byte ptr [rdi], 0    ; 检查 discriminant
   je      .LBB_state0
   cmp     byte ptr [rdi], 1
   je      .LBB_state1
   ```

2. **poll 函数的跳转表**：
   ```asm
   ; 每个状态对应一个分支
   .LBB_state0:
       ; State0 的处理代码
   .LBB_state1:
       ; State1 的处理代码
   ```

3. **Waker 的虚表调用**：
   ```asm
   ; waker.wake() → 间接调用虚表中的 wake 函数
   call    qword ptr [rax + 8]  ; vtable->wake
   ```

## 运行示例

```bash
# 状态机演示
cargo run --bin state_machine

# Pin/Unpin 演示
cargo run --bin pin_unpin

# 迷你 executor 演示
cargo run --bin mini_executor
```

## 与 C++ 协程的对比

| 特性 | Rust | C++ |
|------|------|-----|
| 变换方式 | 状态机枚举 | 协程帧 + switch-case |
| 内存分配 | 栈上（默认） | 堆上（默认） |
| 自引用处理 | Pin<&mut Self> | 编译器自动处理（帧不移动） |
| 大小 | max(各状态) + tag | 所有状态之和 |
| 优化 | LLVM 内联 + niche opt | HALO 消除堆分配 |
| 运行时 | 需要第三方 (tokio) | 需要第三方或自建 |
