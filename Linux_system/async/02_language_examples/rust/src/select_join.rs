//! tokio::select! 和 tokio::join! 的高级用法
//!
//! - join!:   并发等待多个 Future，全部完成后返回
//! - select!: 并发等待多个 Future，第一个完成时返回（竞争模式）
//!
//! 运行方式：cargo run --bin select_join

use std::time::Duration;
use tokio::sync::mpsc;
use tokio::time::{sleep, timeout, Instant};

// ============================================================
// 1. tokio::join! —— 并发等待所有完成
// ============================================================

async fn fetch_user() -> String {
    sleep(Duration::from_millis(300)).await;
    "用户数据".to_string()
}

async fn fetch_orders() -> Vec<String> {
    sleep(Duration::from_millis(500)).await;
    vec!["订单1".into(), "订单2".into()]
}

async fn fetch_settings() -> String {
    sleep(Duration::from_millis(200)).await;
    "设置数据".to_string()
}

async fn demo_join() {
    println!("=== 1. tokio::join! ===\n");

    let start = Instant::now();

    // join! 并发执行所有 Future，等待全部完成
    let (user, orders, settings) = tokio::join!(
        fetch_user(),
        fetch_orders(),
        fetch_settings(),
    );

    println!("  用户: {}", user);
    println!("  订单: {:?}", orders);
    println!("  设置: {}", settings);
    println!("  总耗时: {:?} (取最慢的 500ms，而非 300+500+200=1000ms)\n", start.elapsed());
}

// ============================================================
// 2. tokio::select! —— 竞争模式，第一个完成者获胜
// ============================================================

async fn demo_select_basic() {
    println!("=== 2. tokio::select! 基本用法 ===\n");

    let start = Instant::now();

    // select! 等待第一个完成的 Future
    tokio::select! {
        val = async {
            sleep(Duration::from_millis(500)).await;
            "慢速操作"
        } => {
            println!("  慢速操作先完成: {}", val);
        }
        val = async {
            sleep(Duration::from_millis(200)).await;
            "快速操作"
        } => {
            println!("  快速操作先完成: {}", val);
        }
    }

    println!("  耗时: {:?}", start.elapsed());
    println!("  注意：未完成的分支被自动取消 (drop)\n");
}

// ============================================================
// 3. select! 实现超时
// ============================================================

async fn slow_operation() -> String {
    sleep(Duration::from_millis(2000)).await;
    "慢操作完成".to_string()
}

async fn demo_timeout_with_select() {
    println!("=== 3. select! 实现超时 ===\n");

    // 方法 1：使用 select! 手动实现超时
    println!("--- 方法 1: select! ---");
    let start = Instant::now();
    tokio::select! {
        result = slow_operation() => {
            println!("  操作完成: {}", result);
        }
        _ = sleep(Duration::from_millis(500)) => {
            println!("  操作超时! (500ms)");
        }
    }
    println!("  耗时: {:?}\n", start.elapsed());

    // 方法 2：使用 tokio::time::timeout（更简洁）
    println!("--- 方法 2: tokio::time::timeout ---");
    let start = Instant::now();
    match timeout(Duration::from_millis(500), slow_operation()).await {
        Ok(result) => println!("  操作完成: {}", result),
        Err(_) => println!("  操作超时!"),
    }
    println!("  耗时: {:?}\n", start.elapsed());
}

// ============================================================
// 4. select! 在循环中使用（事件处理模式）
// ============================================================

async fn demo_select_loop() {
    println!("=== 4. select! 事件循环 ===\n");

    let (tx, mut rx) = mpsc::channel::<String>(10);

    // 模拟生产者
    tokio::spawn(async move {
        for i in 0..3 {
            sleep(Duration::from_millis(200)).await;
            tx.send(format!("消息{}", i)).await.unwrap();
        }
        // tx 被 drop，channel 关闭
    });

    // 事件循环：同时处理消息和定时器
    let mut tick_count = 0;
    let mut msg_count = 0;

    loop {
        tokio::select! {
            // 分支 1：接收消息
            msg = rx.recv() => {
                match msg {
                    Some(m) => {
                        msg_count += 1;
                        println!("  收到消息: {}", m);
                    }
                    None => {
                        println!("  Channel 关闭，退出循环");
                        break;
                    }
                }
            }
            // 分支 2：定时 tick
            _ = sleep(Duration::from_millis(150)) => {
                tick_count += 1;
                println!("  Tick #{}", tick_count);
                if tick_count >= 6 {
                    println!("  Tick 达到上限，退出循环");
                    break;
                }
            }
        }
    }

    println!("  总消息数: {}, 总 tick 数: {}\n", msg_count, tick_count);
}

// ============================================================
// 5. select! 与 biased 模式
// ============================================================

async fn demo_biased_select() {
    println!("=== 5. select! biased 模式 ===\n");

    let (tx, mut rx) = mpsc::channel::<i32>(100);

    // 快速生产大量数据
    for i in 0..5 {
        tx.send(i).await.unwrap();
    }
    drop(tx);

    // 默认 select! 会随机选择就绪的分支（公平调度）
    // biased 模式下按代码顺序优先选择（有确定性，但可能饿死后面的分支）
    println!("  biased 模式：按代码顺序优先匹配");
    loop {
        tokio::select! {
            biased;  // 按顺序优先级

            msg = rx.recv() => {
                match msg {
                    Some(m) => println!("    优先处理消息: {}", m),
                    None => {
                        println!("    Channel 关闭");
                        break;
                    }
                }
            }
            _ = sleep(Duration::from_millis(10)) => {
                println!("    Tick (只在没有消息时才执行)");
            }
        }
    }
    println!();
}

// ============================================================
// 6. 并发批量任务 + JoinSet
// ============================================================

async fn demo_join_set() {
    println!("=== 6. tokio::task::JoinSet ===\n");

    let mut set = tokio::task::JoinSet::new();

    // 添加多个异步任务到 JoinSet
    for i in 0..5 {
        set.spawn(async move {
            let delay = (5 - i) * 100; // 任务 0 最慢，任务 4 最快
            sleep(Duration::from_millis(delay as u64)).await;
            format!("任务{} ({}ms)", i, delay)
        });
    }

    // 按完成顺序获取结果（类似 Python 的 as_completed）
    println!("  按完成顺序获取结果:");
    let start = Instant::now();
    while let Some(result) = set.join_next().await {
        let elapsed = start.elapsed();
        match result {
            Ok(msg) => println!("    {:?} - {}", elapsed, msg),
            Err(e) => println!("    {:?} - 错误: {}", elapsed, e),
        }
    }
    println!();
}

// ============================================================
// 主函数
// ============================================================

#[tokio::main]
async fn main() {
    println!("=== tokio::select! 和 tokio::join! ===\n");

    demo_join().await;
    demo_select_basic().await;
    demo_timeout_with_select().await;
    demo_select_loop().await;
    demo_biased_select().await;
    demo_join_set().await;

    println!("=== 总结 ===");
    println!("  join!:      并发等待所有 Future 完成");
    println!("  try_join!:  并发等待所有 Result Future，任一失败则返回");
    println!("  select!:    等待第一个完成的 Future（竞争模式）");
    println!("  select! biased: 按代码顺序优先匹配");
    println!("  JoinSet:    动态管理一组异步任务，按完成顺序获取结果");
    println!("  timeout():  为 Future 添加超时限制");
}
