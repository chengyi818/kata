//! Rust 异步编程基础：async/await + tokio
//!
//! Rust 的异步模型核心特点：
//!   1. async fn 返回一个实现了 Future trait 的匿名类型
//!   2. Future 是惰性的 (lazy)——创建后不会执行，必须被 .await 或提交给 executor
//!   3. 编译器将 async fn 转换为状态机（零开销抽象）
//!   4. 标准库只提供 Future trait，运行时需要第三方库（tokio, async-std 等）
//!
//! 运行方式：cargo run --bin basic_async

use std::time::{Duration, Instant};
use tokio::time::sleep;

// ============================================================
// 1. 基本的 async fn
// ============================================================

/// 模拟异步网络请求
///
/// 这个函数的实际类型签名等价于：
///   fn fetch_data(url: &str, delay_ms: u64) -> impl Future<Output = String>
///
/// 编译器会将函数体转换为一个状态机结构体
async fn fetch_data(url: &str, delay_ms: u64) -> String {
    println!("  [fetch] 开始请求 {}...", url);
    sleep(Duration::from_millis(delay_ms)).await; // 挂起点：让出控制权
    println!("  [fetch] {} 响应完成!", url);
    format!("来自 {} 的数据", url)
}

/// 演示：async fn 是惰性的
async fn demo_lazy_future() {
    println!("=== 1. Future 是惰性的 ===\n");

    // 调用 async fn 不会执行函数体，只是创建一个 Future
    let future = fetch_data("https://example.com", 100);
    println!("  Future 已创建，但函数体还没有执行!");
    println!("  现在 .await 它...");

    // .await 才会真正驱动 Future 执行
    let result = future.await;
    println!("  结果: {}\n", result);
}

// ============================================================
// 2. 串行 vs 并发
// ============================================================

async fn demo_sequential_vs_concurrent() {
    println!("=== 2. 串行 vs 并发 ===\n");

    // --- 串行 ---
    println!("--- 串行 .await ---");
    let start = Instant::now();

    let r1 = fetch_data("site-A", 500).await;
    let r2 = fetch_data("site-B", 500).await;

    println!("  串行结果: [{}, {}]", r1, r2);
    println!("  串行耗时: {:?}\n", start.elapsed());

    // --- 并发 (tokio::join!) ---
    println!("--- tokio::join! (并发) ---");
    let start = Instant::now();

    // join! 宏将多个 Future 同时提交给 executor
    let (r1, r2) = tokio::join!(
        fetch_data("site-A", 500),
        fetch_data("site-B", 500),
    );

    println!("  并发结果: [{}, {}]", r1, r2);
    println!("  并发耗时: {:?}\n", start.elapsed());
}

// ============================================================
// 3. tokio::spawn —— 创建异步任务
// ============================================================

async fn demo_spawn() {
    println!("=== 3. tokio::spawn 异步任务 ===\n");

    // spawn 将 Future 提交到 tokio 运行时的任务队列
    // 返回 JoinHandle（类似于线程的 JoinHandle）
    let handle1 = tokio::spawn(async {
        println!("  [任务1] 开始");
        sleep(Duration::from_millis(300)).await;
        println!("  [任务1] 完成");
        42
    });

    let handle2 = tokio::spawn(async {
        println!("  [任务2] 开始");
        sleep(Duration::from_millis(200)).await;
        println!("  [任务2] 完成");
        "hello"
    });

    // .await JoinHandle 获取任务结果
    // 注意：spawn 的任务可能在不同的线程上执行（多线程运行时）
    let result1 = handle1.await.unwrap();
    let result2 = handle2.await.unwrap();

    println!("  任务1 结果: {}", result1);
    println!("  任务2 结果: {}\n", result2);

    // spawn vs join! 的区别：
    println!("  spawn vs join! 的区别:");
    println!("    join!:  在当前任务中并发轮询多个 Future");
    println!("    spawn: 创建独立的任务，可能在不同线程执行");
    println!("           任务有自己的生命周期，可以 detach");
    println!();
}

// ============================================================
// 4. 异步闭包与 async 块
// ============================================================

async fn demo_async_blocks() {
    println!("=== 4. async 块 ===\n");

    // async 块创建匿名 Future
    let future = async {
        println!("  [async 块] 执行中...");
        sleep(Duration::from_millis(100)).await;
        "async 块的结果"
    };

    println!("  async 块已创建，还未执行");
    let result = future.await;
    println!("  结果: {}\n", result);

    // 在循环中使用 async
    println!("  批量异步任务:");
    let start = Instant::now();
    let mut handles = vec![];
    for i in 0..5 {
        handles.push(tokio::spawn(async move {
            sleep(Duration::from_millis(200)).await;
            i * i
        }));
    }

    let mut results = vec![];
    for h in handles {
        results.push(h.await.unwrap());
    }
    println!("  结果: {:?}", results);
    println!("  耗时: {:?} (5 个 200ms 任务并发)\n", start.elapsed());
}

// ============================================================
// 5. 错误处理
// ============================================================

async fn may_fail(id: u32) -> Result<String, String> {
    sleep(Duration::from_millis(100)).await;
    if id == 2 {
        Err(format!("任务 {} 失败!", id))
    } else {
        Ok(format!("任务 {} 成功", id))
    }
}

async fn demo_error_handling() {
    println!("=== 5. 异步错误处理 ===\n");

    // ? 运算符在 async fn 中正常工作
    async fn process() -> Result<(), String> {
        let r1 = may_fail(1).await?;
        println!("  {}", r1);
        let r2 = may_fail(2).await?; // 这里会失败
        println!("  {}", r2); // 不会执行到这里
        Ok(())
    }

    match process().await {
        Ok(()) => println!("  全部成功"),
        Err(e) => println!("  捕获错误: {}", e),
    }

    // 并发任务中的错误处理
    println!("\n  并发任务错误处理 (try_join!):");
    let result = tokio::try_join!(may_fail(1), may_fail(2), may_fail(3));
    match result {
        Ok((r1, r2, r3)) => println!("  全部成功: {}, {}, {}", r1, r2, r3),
        Err(e) => println!("  某个任务失败: {}", e),
    }
    println!();
}

// ============================================================
// 主函数
// ============================================================

#[tokio::main]
async fn main() {
    println!("=== Rust 异步编程基础 ===\n");

    demo_lazy_future().await;
    demo_sequential_vs_concurrent().await;
    demo_spawn().await;
    demo_async_blocks().await;
    demo_error_handling().await;

    println!("=== 总结 ===");
    println!("  1. async fn 返回 impl Future<Output=T>，是惰性的");
    println!("  2. .await 驱动 Future 执行（挂起点）");
    println!("  3. tokio::join! 在同一任务中并发轮询多个 Future");
    println!("  4. tokio::spawn 创建独立的异步任务");
    println!("  5. ? 运算符在 async fn 中正常工作");
    println!("  6. Rust 的 async 是零开销抽象——编译为状态机，无 GC");
}
