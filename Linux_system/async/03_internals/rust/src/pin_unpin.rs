//! Pin 与 Unpin 机制详解
//!
//! Pin 是 Rust 异步编程中最令人困惑的概念之一。
//! 本文件从"为什么需要 Pin"出发，逐步解释：
//!
//!   1. 自引用结构体问题
//!   2. 为什么 async fn 产生自引用
//!   3. Pin<&mut T> 的语义
//!   4. Unpin trait 的作用
//!
//! 运行方式：cargo run --bin pin_unpin

use std::marker::PhantomPinned;
use std::pin::Pin;

fn main() {
    demo_self_referential_problem();
    demo_why_async_creates_self_ref();
    demo_pin_semantics();
    demo_unpin_trait();
    print_summary();
}

// ============================================================
// 1. 自引用结构体问题
// ============================================================

fn demo_self_referential_problem() {
    println!("=== 1. 自引用结构体问题 ===\n");

    // 考虑这个结构体：
    struct SelfRef {
        value: String,
        // ptr 指向自身的 value 字段
        ptr: *const String,
    }

    let mut s = SelfRef {
        value: "hello".to_string(),
        ptr: std::ptr::null(),
    };
    // 设置自引用
    s.ptr = &s.value as *const String;

    println!("  初始状态:");
    println!("    value 地址: {:p}", &s.value);
    println!("    ptr 指向:   {:p}", s.ptr);
    println!("    ptr 解引用: {}", unsafe { &*s.ptr });

    // 问题：如果 move 了 s，ptr 就变成了悬垂指针！
    let s2 = s; // move!
    println!("\n  move 之后:");
    println!("    新 value 地址: {:p}", &s2.value);
    println!("    ptr 仍指向:    {:p}", s2.ptr);
    println!("    ptr 现在是悬垂指针! (指向旧地址)");
    // unsafe { &*s2.ptr } // 这会是未定义行为！

    println!(r#"
  问题本质：
    Rust 的 move 是 memcpy —— 按字节复制整个结构体。
    但自引用指针不会随 move 更新！
    move 后指针仍指向旧地址 → 悬垂指针 → UB

  这就是为什么 Rust 不允许安全地创建自引用结构体。
"#);
}

// ============================================================
// 2. 为什么 async fn 产生自引用
// ============================================================

fn demo_why_async_creates_self_ref() {
    println!("=== 2. async fn 为什么产生自引用 ===\n");

    println!(r#"  考虑这个 async fn:

    async fn example() {{
        let data = vec![1, 2, 3];
        let reference = &data;        // reference 借用 data
        some_async_op().await;         // <-- 挂起点
        println!("{{:?}}", reference);  // 恢复后仍需要 reference
    }}

  编译器将其变换为状态机：

    enum ExampleStateMachine {{
        State0 {{ }},
        State1 {{
            data: Vec<i32>,           // 跨 await 存活
            reference: &Vec<i32>,     // 跨 await 存活，指向 data!
            fut: SomeAsyncOpFuture,
        }},
        Done,
    }}

  State1 中 reference 指向同一结构体中的 data 字段！
  这就是一个自引用结构体！

  如果这个状态机被 move（如传给另一个函数），
  reference 会变成悬垂指针。

  Pin 就是为了防止这种 move 而设计的。
"#);
}

// ============================================================
// 3. Pin<&mut T> 的语义
// ============================================================

fn demo_pin_semantics() {
    println!("=== 3. Pin<&mut T> 的语义 ===\n");

    println!(r#"  Pin<P> 是一个智能指针包装器，其核心保证是：

    "被 Pin 的值不会被移动（move）"

  具体来说：
    Pin<&mut T> 保证：
      - 你无法获取 &mut T（因为 &mut T 允许 std::mem::swap/replace）
      - 因此无法 move T
      - T 的内存地址在 Pin 存在期间保持不变

  这确保了自引用结构体的安全：
    - Future 被 Pin 后不会被移动
    - 自引用指针始终有效
"#);

    // 演示 Pin 阻止 move
    struct Pinnable {
        data: String,
        _pin: PhantomPinned, // 标记为 !Unpin
    }

    let mut val = Pinnable {
        data: "pinned data".to_string(),
        _pin: PhantomPinned,
    };

    println!("  演示 Pin 的效果：");
    println!("    原始地址: {:p}", &val);

    // 将值 pin 住
    // 安全：我们保证不会再移动 val
    let pinned = unsafe { Pin::new_unchecked(&mut val) };
    println!("    Pin 后地址: {:p}", &*pinned);

    // 以下操作会被编译器拒绝（如果取消注释）：
    // let moved = *pinned;              // 错误：不能移出 Pin
    // std::mem::swap(&mut *pinned, ...) // 错误：不能获取 &mut T

    println!("    Pin 成功阻止了 move!\n");

    // 但可以通过 Pin 安全地访问数据
    // （通过 Pin::as_ref / Pin::as_mut 或投影）
    println!("    通过 Pin 访问数据: {}\n", pinned.data);
}

// ============================================================
// 4. Unpin trait
// ============================================================

fn demo_unpin_trait() {
    println!("=== 4. Unpin trait ===\n");

    println!(r#"  Unpin 是一个 auto trait（编译器自动实现）：

    pub auto trait Unpin {{}}

  含义：
    - T: Unpin  → T 在 Pin 中仍然可以安全移动
                   Pin<&mut T> 等价于 &mut T
    - T: !Unpin → T 在 Pin 中不能移动（Pin 的保证生效）

  大多数类型都是 Unpin 的：
    - i32, String, Vec<T>, ... 都是 Unpin
    - 它们没有自引用，移动不会造成问题

  !Unpin 的类型：
    - 编译器生成的 Future 状态机（可能自引用）
    - 包含 PhantomPinned 的类型
    - 手动 impl !Unpin 的类型
"#);

    // 演示 Unpin 类型可以自由 move
    let mut x = 42i32; // i32: Unpin
    let pinned = Pin::new(&mut x); // Pin::new 只接受 Unpin 类型
    println!("  i32 是 Unpin 的，Pin::new(&mut i32) 编译通过");
    println!("  值: {}\n", *pinned);

    // 编译器生成的 Future 是 !Unpin
    let future = async {
        let data = vec![1, 2, 3];
        let _ref = &data;
        yield_point().await;
        println!("{:?}", _ref);
    };

    println!("  async 块的类型信息:");
    println!("    大小: {} bytes", std::mem::size_of_val(&future));
    // async block 是 !Unpin 的，无法传给 impls_unpin（编译错误就是证明）
    println!("    是否 Unpin: false (async 块实现 !Unpin)");
    drop(future);
    println!();

    println!(r#"  Future trait 的 poll 方法签名：
    fn poll(self: Pin<&mut Self>, cx: &mut Context) -> Poll<Output>
                  ^^^^^^^^^^^^^^^^
                  要求 Self 被 Pin 住!

  这就是为什么 executor 必须 Pin Future 才能 poll：
    - Future 可能包含自引用
    - Pin 保证 Future 在被 poll 期间不会被移动
    - 从而保证自引用指针始终有效
"#);
}

// 辅助函数
async fn yield_point() {}

// ============================================================
// 5. 总结
// ============================================================

fn print_summary() {
    println!("=== Pin/Unpin 总结 ===\n");
    println!(r#"  问题链：
    async fn 包含跨 await 的借用
    → 编译器生成自引用状态机
    → move 会导致悬垂指针
    → 需要防止 move
    → Pin<&mut Self> 保证不会 move
    → Future::poll 要求 Pin<&mut Self>

  Pin 规则：
    1. Pin<&mut T> where T: Unpin
       → Pin 无效果，可以自由 get_mut
    2. Pin<&mut T> where T: !Unpin
       → 不能获取 &mut T
       → 不能 move T
       → 自引用安全

  实际使用：
    - Box::pin(future) → Pin<Box<dyn Future>>  (堆上 pin)
    - tokio::pin!(future) → Pin<&mut Future>   (栈上 pin)
    - std::pin::pin!(future) → Pin<&mut Future> (标准库，1.68+)

  常见陷阱：
    - 直接 &mut future 然后 poll → 编译错误（需要 Pin）
    - 在 Pin 后移动值 → 编译错误
    - 忘记 #[pin] 或 PhantomPinned → 类型意外变成 Unpin
"#);
}
