//! 手动实现 Future 状态机
//!
//! 展示编译器如何将 async fn 转换为状态机枚举。
//!
//! 本文件包含：
//!   1. 一个 async fn 和它的手动等价状态机
//!   2. 详细的状态转移分析
//!   3. 内存布局对比
//!
//! 运行方式：cargo run --bin state_machine
//!
//! 生成汇编：
//!   cargo rustc --bin state_machine -- --emit asm -C opt-level=0
//!   # 输出在 target/debug/deps/state_machine-*.s

use std::future::Future;
use std::pin::Pin;
use std::task::{Context, Poll, RawWaker, RawWakerVTable, Waker};

// ============================================================
// 1. 一个简单的 async fn（编译器会将其变换为状态机）
// ============================================================

/// 这个 async fn 包含两个 await 点
///
/// 编译器会将其变换为一个枚举状态机：
///   enum AsyncTwoSteps {
///       State0 { x: i32 },                              // 初始状态
///       State1 { x: i32, a: i32, fut: SleepFuture },    // 等待第一个 sleep
///       State2 { x: i32, a: i32, b: i32, fut: SleepFuture }, // 等待第二个 sleep
///       Done,                                             // 完成
///   }
async fn two_steps(x: i32) -> i32 {
    let a = x + 1;
    // --- await 点 1: 这里是状态 0 → 状态 1 的边界 ---
    // 跨越 await 点存活的变量 (x, a) 被保存到状态机中
    yield_now().await;
    let b = a * 2;
    // --- await 点 2: 这里是状态 1 → 状态 2 的边界 ---
    yield_now().await;
    a + b
}


// ============================================================
// 2. 手动实现的等价状态机
// ============================================================

/// 模拟一个立即就绪的 Future（简化 sleep）
struct YieldOnce {
    yielded: bool,
}

impl Future for YieldOnce {
    type Output = ();

    fn poll(mut self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<()> {
        if self.yielded {
            Poll::Ready(())
        } else {
            self.yielded = true;
            cx.waker().wake_by_ref(); // 立即通知再次 poll
            Poll::Pending
        }
    }
}

fn yield_now() -> YieldOnce {
    YieldOnce { yielded: false }
}


/// 手动实现的状态机 —— 等价于编译器对 two_steps() 的变换
///
/// 关键观察：
///   - 每个 await 点是一个状态边界
///   - 跨越 await 点的变量被保存在对应状态中
///   - 不跨越 await 点的变量可以是临时的，不占用状态空间
enum TwoStepsStateMachine {
    /// 初始状态：准备开始执行
    State0 { x: i32 },

    /// 等待第一个 yield_now()
    /// 跨越此 await 点的变量：x, a
    /// (x 保留在此状态中用于演示，实际编译器可能优化掉)
    #[allow(dead_code)]
    State1 { x: i32, a: i32, fut: YieldOnce },

    /// 等待第二个 yield_now()
    /// 跨越此 await 点的变量：a, b
    /// x 不再需要，所以不保存
    State2 { a: i32, b: i32, fut: YieldOnce },

    /// 完成状态（不应再被 poll）
    Done,
}

impl TwoStepsStateMachine {
    fn new(x: i32) -> Self {
        TwoStepsStateMachine::State0 { x }
    }
}

impl Future for TwoStepsStateMachine {
    type Output = i32;

    fn poll(mut self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<i32> {
        // 使用 loop 来在状态转移后立即重新匹配
        loop {
            // 安全：我们从不移动内部的数据
            let this = unsafe { self.as_mut().get_unchecked_mut() };

            match this {
                TwoStepsStateMachine::State0 { x } => {
                    println!("    [状态机] State0: x={}", x);
                    let x = *x;
                    let a = x + 1;
                    println!("    [状态机] 计算 a = x + 1 = {}", a);

                    // 创建第一个子 Future 并转移到 State1
                    *this = TwoStepsStateMachine::State1 {
                        x,
                        a,
                        fut: yield_now(),
                    };
                    println!("    [状态机] → 转移到 State1");
                    // 继续 loop，立即 poll State1
                }

                TwoStepsStateMachine::State1 { x: _, a, fut } => {
                    println!("    [状态机] State1: polling 子 Future...");
                    // Poll 子 Future
                    let pinned_fut = unsafe { Pin::new_unchecked(fut) };
                    match pinned_fut.poll(cx) {
                        Poll::Pending => {
                            println!("    [状态机] State1: 子 Future 返回 Pending");
                            return Poll::Pending;
                        }
                        Poll::Ready(()) => {
                            println!("    [状态机] State1: 子 Future 完成");
                            let a = *a;
                            let b = a * 2;
                            println!("    [状态机] 计算 b = a * 2 = {}", b);

                            *this = TwoStepsStateMachine::State2 {
                                a,
                                b,
                                fut: yield_now(),
                            };
                            println!("    [状态机] → 转移到 State2");
                            // 继续 loop
                        }
                    }
                }

                TwoStepsStateMachine::State2 { a, b, fut } => {
                    println!("    [状态机] State2: polling 子 Future...");
                    let pinned_fut = unsafe { Pin::new_unchecked(fut) };
                    match pinned_fut.poll(cx) {
                        Poll::Pending => {
                            println!("    [状态机] State2: 子 Future 返回 Pending");
                            return Poll::Pending;
                        }
                        Poll::Ready(()) => {
                            println!("    [状态机] State2: 子 Future 完成");
                            let result = *a + *b;
                            println!("    [状态机] 计算 result = a + b = {}", result);
                            *this = TwoStepsStateMachine::Done;
                            return Poll::Ready(result);
                        }
                    }
                }

                TwoStepsStateMachine::Done => {
                    panic!("poll after completion!");
                }
            }
        }
    }
}


// ============================================================
// 3. 简单的 poll 驱动器（用于测试）
// ============================================================

fn block_on<F: Future>(mut future: F) -> F::Output {
    // 创建一个空的 waker（最简实现）
    fn dummy_raw_waker() -> RawWaker {
        fn no_op(_: *const ()) {}
        fn clone(data: *const ()) -> RawWaker {
            RawWaker::new(data, &VTABLE)
        }
        const VTABLE: RawWakerVTable =
            RawWakerVTable::new(clone, no_op, no_op, no_op);
        RawWaker::new(std::ptr::null(), &VTABLE)
    }

    let waker = unsafe { Waker::from_raw(dummy_raw_waker()) };
    let mut cx = Context::from_waker(&waker);

    // 安全：future 在栈上且不会被移动
    let mut future = unsafe { Pin::new_unchecked(&mut future) };

    let mut poll_count = 0;
    loop {
        poll_count += 1;
        println!("  --- poll #{} ---", poll_count);
        match future.as_mut().poll(&mut cx) {
            Poll::Ready(val) => {
                println!("  --- 完成! (共 {} 次 poll) ---\n", poll_count);
                return val;
            }
            Poll::Pending => {
                println!("  --- Pending, 将再次 poll ---\n");
            }
        }
    }
}


// ============================================================
// 4. 主函数
// ============================================================

fn main() {
    println!("=== Rust 协程状态机分析 ===\n");

    // --- 使用编译器生成的 async fn ---
    println!("1. 编译器生成的 async fn:");
    let result = block_on(two_steps(10));
    println!("  结果: {}\n", result);

    // --- 使用手动实现的状态机 ---
    println!("2. 手动实现的等价状态机:");
    let result = block_on(TwoStepsStateMachine::new(10));
    println!("  结果: {}\n", result);

    // --- 内存大小对比 ---
    println!("3. 内存布局分析:");
    println!("  编译器 async fn 大小: {} bytes", std::mem::size_of_val(&two_steps(10)));
    println!("  手动状态机大小:       {} bytes", std::mem::size_of::<TwoStepsStateMachine>());
    println!("  YieldOnce 大小:       {} bytes", std::mem::size_of::<YieldOnce>());
    println!();

    println!("  状态机枚举的大小 = max(各变体大小) + 判别标签");
    println!("  编译器可能进行更好的布局优化（如 niche 优化）");
    println!();

    println!("=== 编译器变换规则总结 ===\n");
    println!("  1. 每个 .await 点是一个状态边界");
    println!("  2. 跨越 await 点的变量保存在状态枚举中");
    println!("  3. 不跨越 await 点的变量是临时的（在栈上）");
    println!("  4. 状态机大小 = max(各状态) + 判别标签");
    println!("  5. poll() 使用 match 进行状态分发");
    println!("  6. 状态转移 = 修改枚举变体 + 继续 poll");
    println!();

    println!("=== 生成汇编的方法 ===\n");
    println!("  # 未优化（保留完整状态机结构）");
    println!("  cargo rustc --bin state_machine -- --emit asm -C opt-level=0");
    println!();
    println!("  # 优化后（观察编译器优化效果）");
    println!("  cargo rustc --bin state_machine -- --emit asm -C opt-level=2");
    println!();
    println!("  汇编输出在 target/{{debug|release}}/deps/state_machine-*.s");
}
