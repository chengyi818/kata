//! 手写最小 Executor
//!
//! 从零实现一个 ~80 行的 Future executor，揭示 tokio 的核心机制。
//!
//! 包含：
//!   1. Waker 机制：通知 executor 重新 poll
//!   2. Executor: 管理和调度 Task
//!   3. Spawner: 提交新任务
//!   4. 简单的 Timer Future
//!
//! 运行方式：cargo run --bin mini_executor

use std::collections::VecDeque;
use std::future::Future;
use std::pin::Pin;
use std::sync::{Arc, Mutex};
use std::task::{Context, Poll, RawWaker, RawWakerVTable, Waker};
use std::thread;
use std::time::{Duration, Instant};

// ============================================================
// 1. Task: 封装 Future 的执行单元
// ============================================================

/// Task 包装了一个 boxed Future 和它的 Waker
///
/// 当 Future 返回 Pending 时，Waker 会在适当时机
/// 将 Task 重新放入就绪队列。
struct Task {
    /// 被 box + pin 的 Future
    future: Mutex<Pin<Box<dyn Future<Output = ()> + Send>>>,
    /// 就绪队列的引用——Waker 通过它重新入队
    ready_queue: Arc<Mutex<VecDeque<Arc<Task>>>>,
}

impl Task {
    /// 创建一个 Waker，当调用 wake() 时将 Task 放回就绪队列
    fn waker(self: &Arc<Self>) -> Waker {
        let task = Arc::clone(self);
        // 将 Arc<Task> 转为原始指针，放入 RawWaker
        let raw = Arc::into_raw(task) as *const ();
        let raw_waker = RawWaker::new(raw, &VTABLE);
        unsafe { Waker::from_raw(raw_waker) }
    }
}

/// Waker 的虚表 —— 定义 clone/wake/drop 行为
///
/// 这就是 Waker 机制的核心：
///   wake() → 将 Task 放回就绪队列 → Executor 下一轮会 poll 它
const VTABLE: RawWakerVTable = RawWakerVTable::new(
    // clone: 增加引用计数
    |data| {
        let arc = unsafe { Arc::from_raw(data as *const Task) };
        let cloned = Arc::clone(&arc);
        std::mem::forget(arc); // 不减少原始的引用计数
        RawWaker::new(Arc::into_raw(cloned) as *const (), &VTABLE)
    },
    // wake: 将 Task 放入就绪队列（消耗所有权）
    |data| {
        let task = unsafe { Arc::from_raw(data as *const Task) };
        let queue = task.ready_queue.clone();
        queue.lock().unwrap().push_back(task);
    },
    // wake_by_ref: 将 Task 放入就绪队列（不消耗所有权）
    |data| {
        let task = unsafe { Arc::from_raw(data as *const Task) };
        let queue = task.ready_queue.clone();
        let task_clone = Arc::clone(&task);
        std::mem::forget(task); // 不减少引用计数
        queue.lock().unwrap().push_back(task_clone);
    },
    // drop: 减少引用计数
    |data| {
        unsafe { Arc::from_raw(data as *const Task) };
    },
);

// ============================================================
// 2. Executor 和 Spawner
// ============================================================

/// 最小化的 Executor
struct MiniExecutor {
    ready_queue: Arc<Mutex<VecDeque<Arc<Task>>>>,
    _stopping: bool,
}

/// Spawner 用于提交新任务
struct Spawner {
    ready_queue: Arc<Mutex<VecDeque<Arc<Task>>>>,
}

impl MiniExecutor {
    fn new() -> (MiniExecutor, Spawner) {
        let queue = Arc::new(Mutex::new(VecDeque::new()));
        (
            MiniExecutor {
                ready_queue: queue.clone(),
                _stopping: false,
            },
            Spawner {
                ready_queue: queue,
            },
        )
    }

    /// 运行 executor：不断从就绪队列取出 Task 并 poll
    fn run(&mut self) {
        loop {
            // 从就绪队列取出一个 Task
            let task = {
                let mut queue = self.ready_queue.lock().unwrap();
                queue.pop_front()
            };

            match task {
                Some(task) => {
                    // 创建 Waker
                    let waker = task.waker();
                    let mut cx = Context::from_waker(&waker);

                    // Poll Future
                    let mut future = task.future.lock().unwrap();
                    match future.as_mut().poll(&mut cx) {
                        Poll::Ready(()) => {
                            // Task 完成，不再入队
                            println!("    [executor] 一个 Task 完成");
                        }
                        Poll::Pending => {
                            // Task 未完成
                            // Waker 会在适当时机将 Task 重新入队
                            println!("    [executor] 一个 Task 返回 Pending");
                        }
                    }
                }
                None => {
                    // 队列为空，等待后台线程 wake() 将 Task 入队
                    // 重复检查，短暂 sleep 避免忙等
                    let mut empty_rounds = 0;
                    loop {
                        thread::sleep(Duration::from_millis(10));
                        let queue = self.ready_queue.lock().unwrap();
                        if !queue.is_empty() {
                            break; // 有新 Task 入队，继续主循环
                        }
                        empty_rounds += 1;
                        if empty_rounds >= 200 {
                            // 2 秒内无新 Task，认为全部完成
                            println!("    [executor] 所有任务已完成，退出");
                            self._stopping = true;
                            break;
                        }
                    }
                    if self._stopping {
                        break;
                    }
                }
            }
        }
    }
}

impl Spawner {
    /// 提交一个新的 Future 到 executor
    fn spawn<F>(&self, future: F)
    where
        F: Future<Output = ()> + Send + 'static,
    {
        let task = Arc::new(Task {
            future: Mutex::new(Box::pin(future)),
            ready_queue: self.ready_queue.clone(),
        });
        self.ready_queue.lock().unwrap().push_back(task);
    }
}

// ============================================================
// 3. Timer Future —— 基于线程的简单定时器
// ============================================================

struct TimerFuture {
    /// 目标完成时间
    when: Instant,
    /// 是否已启动后台线程
    started: bool,
    /// 是否已完成
    done: Arc<Mutex<bool>>,
}

impl TimerFuture {
    fn new(duration: Duration) -> Self {
        TimerFuture {
            when: Instant::now() + duration,
            started: false,
            done: Arc::new(Mutex::new(false)),
        }
    }
}

impl Future for TimerFuture {
    type Output = ();

    fn poll(mut self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<()> {
        // 检查是否已完成
        if *self.done.lock().unwrap() {
            return Poll::Ready(());
        }

        // 首次 poll 时启动后台定时线程
        if !self.started {
            self.started = true;
            let when = self.when;
            let done = self.done.clone();
            let waker = cx.waker().clone();

            thread::spawn(move || {
                let now = Instant::now();
                if now < when {
                    thread::sleep(when - now);
                }
                *done.lock().unwrap() = true;
                // 关键：通知 executor 重新 poll 这个 Future
                waker.wake();
            });
        }

        Poll::Pending
    }
}

/// 辅助函数：sleep
async fn sleep(duration: Duration) {
    TimerFuture::new(duration).await;
}

// ============================================================
// 4. 测试
// ============================================================

fn main() {
    println!("=== 手写最小 Executor ===\n");

    let (mut executor, spawner) = MiniExecutor::new();

    // 提交任务 1
    spawner.spawn(async {
        println!("  [任务1] 开始");
        sleep(Duration::from_millis(300)).await;
        println!("  [任务1] 第一次 sleep 完成");
        sleep(Duration::from_millis(200)).await;
        println!("  [任务1] 完成!");
    });

    // 提交任务 2
    spawner.spawn(async {
        println!("  [任务2] 开始");
        sleep(Duration::from_millis(200)).await;
        println!("  [任务2] 完成!");
    });

    // 提交任务 3（立即完成）
    spawner.spawn(async {
        println!("  [任务3] 立即完成!");
    });

    // drop spawner 以避免额外的 Arc 引用
    drop(spawner);

    println!("  [main] 开始运行 executor...\n");
    let start = Instant::now();
    executor.run();
    println!("\n  [main] Executor 退出, 总耗时: {:?}", start.elapsed());

    println!("\n=== Executor 工作原理总结 ===\n");
    println!(r#"  核心循环：
    loop {{
        task = ready_queue.pop();
        result = task.future.poll(waker);
        if result == Pending {{
            // waker 会在适当时机 wake() → 重新入队
        }}
    }}

  Waker 机制：
    1. Executor 为每个 Task 创建 Waker
    2. Waker 内部持有 Task 的引用和就绪队列的引用
    3. Future 返回 Pending 时保存 Waker
    4. I/O 就绪 / 定时器到期时调用 waker.wake()
    5. wake() 将 Task 放回就绪队列
    6. Executor 下一轮 poll 该 Task

  这就是 tokio 的核心骨架！
  tokio 在此基础上增加了：
    - 多线程工作窃取调度器
    - 基于 epoll/kqueue/IOCP 的 I/O 驱动
    - 高效的定时器轮 (timer wheel)
    - 任务优先级和公平调度
    - channel、mutex 等异步同步原语
"#);
}
