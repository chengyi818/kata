//! 手动实现 Future trait
//!
//! 本文件展示 async/await 的底层机制：
//! 当你写 `async fn foo() { ... }` 时，编译器将其转换为一个
//! 实现了 `Future` trait 的状态机结构体。
//!
//! 这里我们手动实现同样的过程，以理解：
//!   1. Future trait 的 poll 方法
//!   2. Context 和 Waker 的作用
//!   3. Pin 的必要性
//!
//! 运行方式：cargo run --bin future_impl

use std::future::Future;
use std::pin::Pin;
use std::task::{Context, Poll};
use std::time::{Duration, Instant};
use tokio::time::sleep;

// ============================================================
// 1. Future trait 详解
// ============================================================

/// Future trait 的定义（标准库中）：
///
/// ```
/// pub trait Future {
///     type Output;
///
///     fn poll(self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<Self::Output>;
/// }
/// ```
///
/// - poll() 被 executor 调用来推进 Future 的执行
/// - 返回 Poll::Ready(value) 表示完成
/// - 返回 Poll::Pending 表示未完成，需要在适当时机再次 poll
/// - cx.waker() 提供了通知 executor "我准备好了，请再 poll 我" 的机制


// ============================================================
// 2. 手动实现一个简单的 Delay Future
// ============================================================

/// 一个简单的延迟 Future：等待指定时间后完成
struct Delay {
    when: Instant,
    // 标记是否已注册 waker（简化实现）
    registered: bool,
}

impl Delay {
    fn new(duration: Duration) -> Self {
        Delay {
            when: Instant::now() + duration,
            registered: false,
        }
    }
}

impl Future for Delay {
    type Output = String;

    fn poll(mut self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<Self::Output> {
        println!("    [Delay::poll] 被调用");

        if Instant::now() >= self.when {
            println!("    [Delay::poll] 时间到了! 返回 Ready");
            Poll::Ready("延迟完成".to_string())
        } else {
            println!("    [Delay::poll] 时间未到, 返回 Pending");

            if !self.registered {
                // 在实际实现中，你需要安排在适当时机调用 waker.wake()
                // 这里用一个线程模拟定时唤醒
                let waker = cx.waker().clone();
                let when = self.when;
                self.registered = true;

                std::thread::spawn(move || {
                    let now = Instant::now();
                    if now < when {
                        std::thread::sleep(when - now);
                    }
                    // 通知 executor 重新 poll 这个 Future
                    waker.wake();
                    println!("    [Delay::waker] wake() 已调用，通知 executor 重新 poll");
                });
            }

            Poll::Pending
        }
    }
}


// ============================================================
// 3. 手动实现一个组合 Future（模拟 async fn 的编译器变换）
// ============================================================

/// 这个结构体模拟了编译器对以下 async fn 的变换：
///
/// ```
/// async fn two_step() -> String {
///     let msg1 = delay(500ms).await;    // 第一步
///     println!("第一步完成: {msg1}");
///     let msg2 = delay(300ms).await;    // 第二步
///     println!("第二步完成: {msg2}");
///     format!("{msg1} + {msg2}")
/// }
/// ```
///
/// 编译器将其转换为一个状态机枚举：
enum TwoStepState {
    /// 初始状态：还没开始
    Start,
    /// 等待第一个 delay
    WaitingFirst { delay: Delay },
    /// 第一步完成，等待第二个 delay
    WaitingSecond { first_result: String, delay: Delay },
    /// 已完成（临时状态）
    Done,
}

struct TwoStepFuture {
    state: TwoStepState,
}

impl TwoStepFuture {
    fn new() -> Self {
        TwoStepFuture {
            state: TwoStepState::Start,
        }
    }
}

impl Future for TwoStepFuture {
    type Output = String;

    fn poll(mut self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<Self::Output> {
        loop {
            match &mut self.state {
                TwoStepState::Start => {
                    println!("  [TwoStep] 状态: Start → 创建第一个 Delay");
                    self.state = TwoStepState::WaitingFirst {
                        delay: Delay::new(Duration::from_millis(500)),
                    };
                    // 不返回，继续 loop 立即 poll 新状态
                }

                TwoStepState::WaitingFirst { delay } => {
                    // 安全：我们不移动 delay，只是 pin 它来 poll
                    let delay_pin = unsafe { Pin::new_unchecked(delay) };
                    match delay_pin.poll(cx) {
                        Poll::Ready(msg) => {
                            println!("  [TwoStep] 第一步完成: {}", msg);
                            self.state = TwoStepState::WaitingSecond {
                                first_result: msg,
                                delay: Delay::new(Duration::from_millis(300)),
                            };
                            // 继续 loop
                        }
                        Poll::Pending => return Poll::Pending,
                    }
                }

                TwoStepState::WaitingSecond { first_result, delay } => {
                    let delay_pin = unsafe { Pin::new_unchecked(delay) };
                    match delay_pin.poll(cx) {
                        Poll::Ready(msg) => {
                            println!("  [TwoStep] 第二步完成: {}", msg);
                            let result = format!("{} + {}", first_result, msg);
                            self.state = TwoStepState::Done;
                            return Poll::Ready(result);
                        }
                        Poll::Pending => return Poll::Pending,
                    }
                }

                TwoStepState::Done => {
                    panic!("poll after completion");
                }
            }
        }
    }
}


// ============================================================
// 4. 演示
// ============================================================

async fn demo_manual_delay() {
    println!("=== 1. 手动实现的 Delay Future ===\n");

    let start = Instant::now();
    let result = Delay::new(Duration::from_millis(500)).await;
    println!("  结果: {}", result);
    println!("  耗时: {:?}\n", start.elapsed());
}

async fn demo_state_machine() {
    println!("=== 2. 手动实现的状态机 Future ===\n");
    println!("  模拟 async fn 被编译器转换为状态机的过程:\n");

    let start = Instant::now();
    let result = TwoStepFuture::new().await;
    println!("\n  最终结果: {}", result);
    println!("  总耗时: {:?}\n", start.elapsed());
}

async fn demo_comparison() {
    println!("=== 3. 对比：手写 vs async/await ===\n");

    // 等价的 async fn 版本
    async fn two_step_async() -> String {
        let msg1 = sleep(Duration::from_millis(500)).await;
        let _ = msg1;
        let msg1 = "延迟完成".to_string();
        println!("  [async fn] 第一步完成");

        sleep(Duration::from_millis(300)).await;
        let msg2 = "延迟完成".to_string();
        println!("  [async fn] 第二步完成");

        format!("{} + {}", msg1, msg2)
    }

    let start = Instant::now();
    let result = two_step_async().await;
    println!("  结果: {}", result);
    println!("  耗时: {:?}", start.elapsed());
    println!();
    println!("  关键理解：");
    println!("    手写的 TwoStepFuture 状态机 ≡ 编译器对 async fn 的变换结果");
    println!("    async/await 只是语法糖，编译后没有运行时开销（零开销抽象）");
    println!();
}


// ============================================================
// 主函数
// ============================================================

#[tokio::main]
async fn main() {
    println!("=== Rust Future trait 手动实现 ===\n");

    demo_manual_delay().await;
    demo_state_machine().await;
    demo_comparison().await;

    println!("=== 总结 ===");
    println!("  Future::poll() 是异步执行的核心驱动方法");
    println!("  返回 Poll::Pending 时必须安排 Waker 在适当时机调用 wake()");
    println!("  async fn 被编译器转换为状态机，每个 .await 是一个状态转移点");
    println!("  手动实现 Future 有助于理解编译器的零开销抽象");
}
