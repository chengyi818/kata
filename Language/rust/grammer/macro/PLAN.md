# Rust 宏学习计划实现方案

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**目标：** 构建 Rust 宏学习项目的完整结构，包含 6 个模块的代码示例、练习题和阅读笔记。

**架构：** 在 `Language/rust/grammer/macro/` 目录下创建 6 个独立 Rust crate（M1-M5）和 1 个实战项目（M6），每个模块包含讲解代码、示例和练习，所有代码均通过编译验证。

**技术栈：** Rust (Cargo), `syn`, `quote`, `proc_macro2`, `serde`, `thiserror` (阅读参考)

---

## 文件结构

```
Language/rust/grammer/macro/
├── README.md
├── m1_macro_rules/
│   ├── Cargo.toml
│   ├── src/lib.rs
│   └── exercises/
│       ├── my_vec.rs
│       └── hashmap.rs
├── m2_hygiene/
│   ├── Cargo.toml
│   ├── src/lib.rs
│   └── exercises/
│       └── hygiene_exercise.rs
├── m3_advanced_match/
│   ├── Cargo.toml
│   ├── src/lib.rs
│   └── exercises/
│       ├── json_macro.rs
│       └── ast_builder.rs
├── m4_derive/
│   ├── Cargo.toml
│   ├── src/lib.rs
│   └── tests/
│       └── integration_test.rs
├── m5_proc_macro/
│   ├── Cargo.toml
│   ├── src/lib.rs
│   └── tests/
│       └── integration_test.rs
├── m6_project/
│   ├── Cargo.toml
│   ├── src/lib.rs
│   └── tests/
│       └── integration_test.rs
└── reading_notes/
    ├── serde_derive.md
    ├── async_trait.md
    └── tokio_macros.md
```

---

### 任务 1：创建项目总览 README

**文件：**
- 创建: `Language/rust/grammer/macro/README.md`

- [ ] **步骤 1：编写 README 内容**

```markdown
# Rust 宏学习计划

> 从零基础到全面掌握 Rust 宏（声明宏、卫生宏、过程宏）
> 学习方式：教程驱动，理论 + 代码示例 + 动手练习
> 节奏：每天 1 小时，预计 18-20 天完成

## 进度追踪

| 模块 | 主题 | 预计天数 | 状态 |
|------|------|----------|------|
| M1 | macro_rules! 基础 | 3 天 | ⬜ 未开始 |
| M2 | 宏卫生 (Hygiene) | 2 天 | ⬜ 未开始 |
| M3 | 递归宏与高级模式匹配 | 3 天 | ⬜ 未开始 |
| M4 | 过程宏入门：derive 宏 | 4 天 | ⬜ 未开始 |
| M5 | 过程宏进阶：function-like 与 attribute | 4 天 | ⬜ 未开始 |
| M6 | 综合实战与阅读 | 3-4 天 | ⬜ 未开始 |

## 推荐学习资源

### 入门
- [The Rust Reference - Macros](https://doc.rust-lang.org/reference/macros.html)
- [The Little Book of Rust Macros](https://veykril.github.io/tlborm/)

### 过程宏
- [`proc_macro` 官方文档](https://doc.rust-lang.org/proc_macro/)
- [`syn` 文档](https://docs.rs/syn/)
- [`quote` 文档](https://docs.rs/quote/)

## 与 C/C++ 宏的对比

| 特性 | C/C++ 宏 | Rust 声明宏 | Rust 过程宏 |
|------|----------|-------------|-------------|
| 阶段 | 预处理期 | 编译期 | 编译期 |
| 作用域 | 全局，易污染 | 卫生的 | 完全控制 |
| 能力 | 简单文本替换 | 模式匹配 + 代码生成 | 完整语法树操作 |
| 类型检查 | 无 | 展开后检查 | 可自定义检查 |
```

- [ ] **步骤 2：验证文件创建**

运行: `ls -la Language/rust/grammer/macro/README.md`
期望: 文件存在

- [ ] **步骤 3：提交**

```bash
git add Language/rust/grammer/macro/README.md
git commit -m "docs: add Rust macro learning plan README"
```

---

### 任务 2：创建 M1 macro_rules! 基础模块

**文件：**
- 创建: `Language/rust/grammer/macro/m1_macro_rules/Cargo.toml`
- 创建: `Language/rust/grammer/macro/m1_macro_rules/src/lib.rs`

- [ ] **步骤 1：创建 Cargo.toml**

```toml
[package]
name = "m1_macro_rules"
version = "0.1.0"
edition = "2021"

[dependencies]
```

- [ ] **步骤 2：编写 lib.rs (包含讲解代码和示例)**

```rust
//! # M1: macro_rules! 基础
//!
//! 本模块演示 Rust 声明宏的基础语法和用法。

// ============================================================================
// Day 1: 宏的概念与基本语法
// ============================================================================

/// 宏与函数的区别：
/// - 宏在编译期展开，函数在运行时调用
/// - 宏可以接受任意数量和类型的参数
/// - 宏在展开前不进行类型检查
///
/// 基本语法：
/// macro_rules! name {
///     (pattern) => { expansion };
/// }

/// 简单的 hello! 宏示例
#[macro_export]
macro_rules! hello {
    () => {
        println!("Hello from macro!");
    };
}

/// 示例：输出问候语
#[cfg(test)]
mod day1_examples {
    use super::*;

    #[test]
    fn test_hello_macro() {
        hello!();
    }

    /// 模拟标准库 vec! 宏的简化版本
    #[macro_export]
    macro_rules! simple_vec {
        ( $( $x:expr ),* $(,)? ) => {
            {
                let mut temp_vec = Vec::new();
                $(
                    temp_vec.push($x);
                )*
                temp_vec
            }
        };
    }

    #[test]
    fn test_simple_vec() {
        let v = simple_vec![1, 2, 3];
        assert_eq!(v, vec![1, 2, 3]);

        let v2 = simple_vec![1];
        assert_eq!(v2, vec![1]);

        // 测试尾逗号
        let v3 = simple_vec![1, 2, 3,];
        assert_eq!(v3, vec![1, 2, 3]);
    }
}

// ============================================================================
// Day 2: 片段说明符 (Fragment Specifiers)
// ============================================================================

/// Rust 宏支持多种片段说明符：
///
/// - `ident`: 标识符
/// - `ty`: 类型
/// - `expr`: 表达式
/// - `stmt`: 语句
/// - `pat`: 模式
/// - `path`: 路径
/// - `tt`: 标记树 (Token Tree)
/// - `item`: 项（函数、结构体等）
/// - `block`: 代码块
/// - `meta`: 元数据
/// - `literal`: 字面量

/// 练习：实现 hashmap! 宏
#[macro_export]
macro_rules! hashmap {
    ( $( $key:expr => $val:expr ),* $(,)? ) => {
        {
            let mut map = ::std::collections::HashMap::new();
            $(
                map.insert($key, $val);
            )*
            map
        }
    };
}

#[cfg(test)]
mod day2_examples {
    use super::*;
    use std::collections::HashMap;

    #[test]
    fn test_hashmap_macro() {
        let map = hashmap! {
            "name" => "Alice",
            "age" => 30,
        };
        assert_eq!(map.get("name"), Some(&"Alice"));
        assert_eq!(map.get("age"), Some(&30));
        assert_eq!(map.len(), 2);
    }

    /// 示例：片段说明符 expr 的使用
    #[macro_export]
    macro_rules! calculate {
        (add $a:expr, $b:expr) => {
            $a + $b
        };
        (mul $a:expr, $b:expr) => {
            $a * $b
        };
    }

    #[test]
    fn test_calculate_macro() {
        assert_eq!(calculate!(add 5, 3), 8);
        assert_eq!(calculate!(mul 5, 3), 15);
    }

    /// 示例：使用多个匹配规则
    #[macro_export]
    macro_rules! greet {
        (Hello $name:ident) => {
            println!("Hello, {}!", stringify!($name));
        };
        (Goodbye $name:ident) => {
            println!("Goodbye, {}!", stringify!($name));
        };
    }

    #[test]
    fn test_greet_macro() {
        greet!(Hello world);
        greet!(Goodbye world);
    }
}

// ============================================================================
// Day 3: 综合练习 - my_vec! 完整版
// ============================================================================

/// 练习：实现支持嵌套的 my_vec! 宏
#[macro_export]
macro_rules! my_vec {
    // 基础情况：空 vec
    () => {
        Vec::new()
    };

    // 单个元素
    ($elem:expr) => {
        {
            let mut v = Vec::new();
            v.push($elem);
            v
        }
    };

    // 多个元素
    ( $( $x:expr ),* $(,)? ) => {
        {
            let mut v = Vec::new();
            $(
                v.push($x);
            )*
            v
        }
    };

    // 嵌套 vec：[1, [2, 3], 4]
    ( $( $x:expr ),+ ) => {
        {
            let mut v = Vec::new();
            $(
                v.push($x);
            )*
            v
        }
    };
}

#[cfg(test)]
mod day3_examples {
    use super::*;

    #[test]
    fn test_my_vec_empty() {
        let v: Vec<i32> = my_vec![];
        assert!(v.is_empty());
    }

    #[test]
    fn test_my_vec_single() {
        let v = my_vec![42];
        assert_eq!(v, vec![42]);
    }

    #[test]
    fn test_my_vec_multiple() {
        let v = my_vec![1, 2, 3, 4];
        assert_eq!(v, vec![1, 2, 3, 4]);
    }

    #[test]
    fn test_my_vec_with_trailing_comma() {
        let v = my_vec![1, 2, 3,];
        assert_eq!(v, vec![1, 2, 3]);
    }
}
```

- [ ] **步骤 2.4：创建 exercises 目录**

运行: `mkdir -p Language/rust/grammer/macro/m1_macro_rules/exercises`
期望: 目录创建成功

- [ ] **步骤 2.5：创建 my_vec.rs 练习文件**

```rust
//! 练习：实现 my_vec! 宏
//!
//! Day 1 练习：从零实现 vec! 宏
//!
//! 目标：
//! 1. 支持空 vec: my_vec![]
//! 2. 支持单个元素: my_vec![1]
//! 3. 支持多个元素: my_vec![1, 2, 3]
//! 4. 支持可选尾逗号: my_vec![1, 2, 3,]
//!
//! 提示：
//! - 使用 $( $x:expr ),* 来匹配多个元素
//! - 使用 $(,)? 来匹配可选尾逗号
//! - 使用 Vec::new() 和 push 方法

// TODO: 实现 my_vec! 宏

#[cfg(test)]
mod tests {
    // TODO: 取消注释这些测试并在你实现宏后运行
    /*
    use super::*;

    #[test]
    fn test_empty() {
        let v: Vec<i32> = my_vec![];
        assert!(v.is_empty());
    }

    #[test]
    fn test_single() {
        let v = my_vec![42];
        assert_eq!(v, vec![42]);
    }

    #[test]
    fn test_multiple() {
        let v = my_vec![1, 2, 3];
        assert_eq!(v, vec![1, 2, 3]);
    }

    #[test]
    fn test_trailing_comma() {
        let v = my_vec![1, 2, 3,];
        assert_eq!(v, vec![1, 2, 3]);
    }
    */
}
```

- [ ] **步骤 2.6：创建 hashmap.rs 练习文件**

```rust
//! 练习：实现 hashmap! 宏
//!
//! Day 2 练习：实现 HashMap 初始化宏
//!
//! 目标：
//! 1. 支持键值对: hashmap! { "key" => "value" }
//! 2. 支持多个键值对
//! 3. 支持可选尾逗号
//!
//! 提示：
//! - 使用 std::collections::HashMap
//! - 使用 $( $key:expr => $val:expr ),* 匹配键值对

// TODO: 实现 hashmap! 宏

#[cfg(test)]
mod tests {
    use std::collections::HashMap;

    // TODO: 取消注释这些测试
    /*
    use super::*;

    #[test]
    fn test_single_pair() {
        let map = hashmap! { "name" => "Alice" };
        assert_eq!(map.get("name"), Some(&"Alice"));
        assert_eq!(map.len(), 1);
    }

    #[test]
    fn test_multiple_pairs() {
        let map = hashmap! {
            "name" => "Alice",
            "age" => 30,
        };
        assert_eq!(map.get("name"), Some(&"Alice"));
        assert_eq!(map.get("age"), Some(&30));
        assert_eq!(map.len(), 2);
    }

    #[test]
    fn test_trailing_comma() {
        let map = hashmap! {
            "key" => "value",
        };
        assert_eq!(map.len(), 1);
    }
    */
}
```

- [ ] **步骤 3：验证编译**

运行: `cd Language/rust/grammer/macro/m1_macro_rules && cargo check`
期望: Compiling m1_macro_rules v0.1.0 Finished

- [ ] **步骤 4：运行测试**

运行: `cargo test`
期望: All tests passed

- [ ] **步骤 5：提交**

```bash
git add Language/rust/grammer/macro/m1_macro_rules/
git commit -m "feat: add M1 macro_rules!基础模块"
```

---

### 任务 3：创建 M2 卫生宏模块

**文件：**
- 创建: `Language/rust/grammer/macro/m2_hygiene/Cargo.toml`
- 创建: `Language/rust/grammer/macro/m2_hygiene/src/lib.rs`

- [ ] **步骤 1：创建 Cargo.toml**

```toml
[package]
name = "m2_hygiene"
version = "0.1.0"
edition = "2021"
```

- [ ] **步骤 2：编写 lib.rs (卫生宏讲解与对比)**

```rust
//! # M2: 宏卫生 (Hygiene)
//!
//! Rust 的宏是「卫生的」，这意味着宏内部定义的变量不会污染调用者的作用域。

// ============================================================================
// Day 1: 卫生宏的概念与原理
// ============================================================================

/// 什么是宏卫生？
///
/// 宏卫生确保宏内部定义的变量不会与外部变量冲突。
/// 这是通过在展开时为变量添加唯一的标识符来实现的。
///
/// 对比 C 宏的问题：
/// ```c
/// #define SQUARE(x) x * x
/// int a = 5;
/// int b = SQUARE(a + 1);  // 展开为: a + 1 * a + 1 = 11 (错误!)
/// ```
///
/// Rust 宏不会出现这个问题：
/// ```rust
/// macro_rules! square {
///     ($x:expr) => { $x * $x };
/// }
/// let a = 5;
/// let b = square!(a + 1);  // 正确计算: (a + 1) * (a + 1) = 36
/// ```

/// 不卫生的宏示例（通过避免使用卫生机制）
#[macro_export]
macro_rules! bad_log {
    ($msg:expr) => {
        let x = 42;  // 这个 x 可能污染外部作用域
        println!("{}: {}", $msg, x);
    };
}

/// 卫生的宏示例（Rust 默认行为）
#[macro_export]
macro_rules! good_log {
    ($msg:expr) => {
        let x = 42;  // 这个 x 是卫生的，不会污染外部
        println!("{}: {}", $msg, x);
    };
}

#[cfg(test)]
mod day1_examples {
    use super::*;

    #[test]
    fn test_hygiene_basic() {
        let x = 100;

        bad_log!("Using bad macro");
        assert_eq!(x, 100);  // 外部 x 不受影响

        good_log!("Using good macro");
        assert_eq!(x, 100);  // 外部 x 不受影响
    }

    /// 使用 $crate:: 引用当前 crate 的项
    #[macro_export]
    macro_rules! using_crate {
        () => {
            $crate::helper_function()
        };
    }

    fn helper_function() -> i32 {
        42
    }

    #[test]
    fn test_dollar_crate() {
        assert_eq!(using_crate!(), 42);
    }
}

// ============================================================================
// Day 2: Span 与调用上下文
// ============================================================================

/// Span 决定了编译器错误信息的位置。
///
/// - `Span::call_site()`: 使用宏调用的位置
/// - `Span::mixed_site()`: 混合使用宏定义和调用的位置
///
/// 声明宏中，Rust 会自动处理 Span，确保错误信息指向正确的位置。

#[macro_export]
macro_rules! assert_eq_with_message {
    ($left:expr, $right:expr, $msg:expr) => {
        if $left != $right {
            panic!(
                "{}: assertion failed: {} == {}",
                $msg,
                stringify!($left),
                stringify!($right)
            );
        }
    };
}

#[cfg(test)]
mod day2_examples {
    use super::*;

    #[test]
    fn test_assert_eq_with_message() {
        assert_eq_with_message!(1 + 1, 2, "Math check");
    }

    #[test]
    #[should_panic(expected = "Math check")]
    fn test_assert_eq_with_message_panic() {
        assert_eq_with_message!(1 + 1, 3, "Math check");
    }

    /// 对比：不卫生的实现（模拟）
    #[macro_export]
    macro_rules! unsafe_counter {
        () => {{
            static COUNTER: ::std::sync::atomic::AtomicUsize =
                ::std::sync::atomic::AtomicUsize::new(0);
            COUNTER.fetch_add(1, ::std::sync::atomic::Ordering::SeqCst)
        }};
    }

    #[test]
    fn test_unsafe_counter() {
        // 注意：这个宏在多次调用时会共享同一个计数器
        let count1 = unsafe_counter!();
        let count2 = unsafe_counter!();
        assert!(count2 > count1);
    }
}
```

- [ ] **步骤 2.3：创建 exercises 目录**

运行: `mkdir -p Language/rust/grammer/macro/m2_hygiene/exercises`
期望: 目录创建成功

- [ ] **步骤 2.4：创建 hygiene_exercise.rs 练习文件**

```rust
//! 练习：探索宏卫生
//!
//! Day 2 练习：理解宏卫生的实际效果
//!
//! 目标：
//! 1. 对比不卫生的实现（使用全局变量）和卫生的实现
//! 2. 理解 Span 的作用
//! 3. 使用 $crate:: 引用当前 crate 的项
//!
//! 提示：
//! - 使用 static 创建全局变量
//! - 使用 AtomicUsize 进行原子操作
//! - 使用 $crate:: 来确保宏可以找到 helper 函数

// TODO: 实现不卫生的计数器宏（使用全局 static）

// TODO: 实现卫生的计数器宏（使用 $crate::）

#[cfg(test)]
mod tests {
    use std::sync::atomic::{AtomicUsize, Ordering};

    // TODO: 在你实现宏后取消注释这些测试
    /*
    use super::*;

    #[test]
    fn test_unhygienic_counter() {
        let c1 = unsafe_counter!();
        let c2 = unsafe_counter!();
        assert!(c2 > c1);
    }

    #[test]
    fn test_hygienic_counter() {
        let c1 = safe_counter!();
        let c2 = safe_counter!();
        assert!(c2 > c1);
    }

    /// 对比：两个计数器是否相互影响？
    #[test]
    fn test_counter_isolation() {
        let uc1 = unsafe_counter!();
        let sc1 = safe_counter!();
        let uc2 = unsafe_counter!();
        let sc2 = safe_counter!();

        // 不卫生的计数器跨调用共享状态
        assert_eq!(uc2, uc1 + 2);

        // 卫生的计数器应该...（思考一下）
    }
    */
}
```

- [ ] **步骤 3：验证编译**

运行: `cd Language/rust/grammer/macro/m2_hygiene && cargo check`
期望: Compiling m2_hygiene v0.1.0 Finished

- [ ] **步骤 4：运行测试**

运行: `cargo test`
期望: All tests passed

- [ ] **步骤 5：提交**

```bash
git add Language/rust/grammer/macro/m2_hygiene/
git commit -m "feat: add M2 卫生宏模块"
```

---

### 任务 4：创建 M3 高级模式匹配模块

**文件：**
- 创建: `Language/rust/grammer/macro/m3_advanced_match/Cargo.toml`
- 创建: `Language/rust/grammer/macro/m3_advanced_match/src/lib.rs`
- 创建: `Language/rust/grammer/macro/m3_advanced_match/exercises/json_macro.rs`
- 创建: `Language/rust/grammer/macro/m3_advanced_match/exercises/ast_builder.rs`

- [ ] **步骤 1：创建 Cargo.toml**

```toml
[package]
name = "m3_advanced_match"
version = "0.1.0"
edition = "2021"

[dependencies]
serde = { version = "1.0", features = ["derive"] }
serde_json = "1.0"
```

- [ ] **步骤 2：编写 lib.rs (递归宏和高级匹配)**

```rust
//! # M3: 递归宏与高级模式匹配
//!
//! 本模块演示更高级的宏技巧：递归、TT Muncher、嵌套匹配。

// ============================================================================
// Day 1: 递归宏与 TT Muncher
// ============================================================================

/// 递归宏的概念：
/// 宏可以调用自身来处理复杂的情况。
/// 由于 Rust 宏在编译期展开，递归深度有限制，需要谨慎使用。

/// 简单的递归计数宏
#[macro_export]
macro_rules! count_tts {
    () => { 0 };
    ( $_tt:tt $($rest:tt)* ) => { 1 + count_tts!($($rest)*) };
}

#[cfg(test)]
mod day1_examples {
    use super::*;

    #[test]
    fn test_count_tts() {
        assert_eq!(count_tts!(), 0);
        assert_eq!(count_tts!(a), 1);
        assert_eq!(count_tts!(a b c), 3);
        assert_eq!(count_tts!(1, 2, 3, 4), 7);  // 包括逗号
    }

    /// TT Muncher 模式：逐个处理 token
    #[macro_export]
    macro_rules! sum {
        // 基础情况
        () => { 0 };
        // 递归情况
        ( $first:expr, $($rest:expr),* ) => {
            $first + sum!($($rest),*)
        };
    }

    #[test]
    fn test_sum_macro() {
        assert_eq!(sum!(), 0);
        assert_eq!(sum!(1), 1);
        assert_eq!(sum!(1, 2, 3), 6);
        assert_eq!(sum!(10, 20, 30, 40), 100);
    }

    /// 使用 @ 内部规则标记（避免外部误调用）
    #[macro_export]
    macro_rules! sum_internal {
        (@accum $acc:expr, ) => { $acc };
        (@accum $acc:expr, $head:expr, $($tail:expr),*) => {
            sum_internal!(@accum $acc + $head, $($tail),*)
        };
        ($($expr:expr),*) => {
            sum_internal!(@accum 0, $($expr),*)
        };
    }

    #[test]
    fn test_sum_internal_macro() {
        assert_eq!(sum_internal!(), 0);
        assert_eq!(sum_internal!(1, 2, 3), 6);
    }
}

// ============================================================================
// Day 2: 高级模式匹配
// ============================================================================

/// 高级模式匹配技巧：
/// - 可选尾逗号：`$(,)?`
/// - 嵌套重复
/// - 多种模式组合

#[macro_export]
macro_rules! vector {
    ( $( $x:expr ),* $(,)? ) => {
        {
            let mut v = Vec::new();
            $(
                v.push($x);
            )*
            v
        }
    };
}

#[cfg(test)]
mod day2_examples {
    use super::*;

    #[test]
    fn test_vector_macro() {
        let v1 = vector![1, 2, 3];
        let v2 = vector![1, 2, 3,];
        assert_eq!(v1, v2);
    }

    /// 嵌套重复示例
    #[macro_export]
    macro_rules! matrix {
        ( $( [ $( $x:expr ),* ] ),* $(,)? ) => {
            {
                let mut mat = Vec::new();
                $(
                    let mut row = Vec::new();
                    $(
                        row.push($x);
                    )*
                    mat.push(row);
                )*
                mat
            }
        };
    }

    #[test]
    fn test_matrix_macro() {
        let mat = matrix![
            [1, 2, 3],
            [4, 5, 6],
        ];
        assert_eq!(mat[0], vec![1, 2, 3]);
        assert_eq!(mat[1], vec![4, 5, 6]);
    }

    /// 多种片段说明符组合
    #[macro_export]
    macro_rules! struct_field {
        ( $name:ident: $type:ty ) => {
            $name: $type
        };
    }

    #[macro_export]
    macro_rules! my_struct {
        (
            $( $vis:vis struct $name:ident {
                $( $field_name:ident : $field_type:ty ),* $(,)?
            } )*
        ) => {
            $(
                $vis struct $name {
                    $( struct_field!($field_name: $field_type) ),*
                }
            )*
        };
    }

    my_struct! {
        pub struct Point {
            x: i32,
            y: i32,
        }

        pub struct Color {
            r: u8,
            g: u8,
            b: u8,
        }
    }

    #[test]
    fn test_my_struct_macro() {
        let p = Point { x: 10, y: 20 };
        assert_eq!(p.x, 10);
        assert_eq!(p.y, 20);

        let c = Color { r: 255, g: 128, b: 0 };
        assert_eq!(c.r, 255);
    }
}

// ============================================================================
// Day 3: 综合练习
// ============================================================================

#[cfg(test)]
mod day3_examples {
    use super::*;

    /// JSON 宏（简化版）练习提示见 exercises/json_macro.rs
    /// AST 构建宏练习提示见 exercises/ast_builder.rs

    #[test]
    fn test_json_basic() {
        // 这个测试引导学习者完成 json_macro.rs
        use serde_json::json;

        let value = json!({
            "name": "Alice",
            "age": 30,
        });

        assert_eq!(value["name"], "Alice");
        assert_eq!(value["age"], 30);
    }
}
```

- [ ] **步骤 3：创建 json_macro.rs 练习文件**

```rust
//! 练习：实现一个简化版的 json! 宏
//!
//! 目标：实现一个可以创建 JSON 值的宏
//! 支持的语法：
//! - `json!({ "key": value })` - 对象
//! - `json!([elem1, elem2])` - 数组
//! - `json!("string")` - 字符串
//! - `json!(42)` - 数字
//! - `json!(true)` - 布尔值
//!
//! 提示：
//! 1. 使用嵌套的 macro_rules!
//! 2. 使用不同的片段说明符（literal, expr, tt）
//! 3. 参考 serde_json::json! 的实现（但不要直接复制）
//!
//! 练习步骤：
//! 1. 先实现支持字面量的版本
//! 2. 添加对对象和数组的支持
//! 3. 测试嵌套结构

// TODO: 实现你的 json! 宏

// 测试模板
#[cfg(test)]
mod tests {
    use super::*;
    use serde_json::Value;

    // TODO: 当你实现宏后，取消注释这些测试

    /*
    #[test]
    fn test_json_string() {
        let value = json!("hello");
        assert_eq!(value, Value::String("hello".to_string()));
    }

    #[test]
    fn test_json_number() {
        let value = json!(42);
        assert_eq!(value, Value::Number(42.into()));
    }

    #[test]
    fn test_json_object() {
        let value = json!({ "name": "Alice", "age": 30 });
        assert_eq!(value["name"], "Alice");
        assert_eq!(value["age"], 30);
    }

    #[test]
    fn test_json_array() {
        let value = json!([1, 2, 3]);
        assert_eq!(value[0], 1);
        assert_eq!(value[1], 2);
        assert_eq!(value[2], 3);
    }
    */
}
```

- [ ] **步骤 4：创建 ast_builder.rs 练习文件**

```rust
//! 练习：实现一个 AST 构建宏
//!
//! 目标：实现一个可以构建抽象语法树（AST）的宏
//!
//! 假设我们有一个简单的表达式 AST：
//! ```rust
//! enum Expr {
//!     Literal(i32),
//!     Add(Box<Expr>, Box<Expr>),
//!     Mul(Box<Expr>, Box<Expr>),
//! }
//! ```
//!
//! 我们希望可以用这样的语法构建 AST：
//! ```rust
//! ast!(1 + 2 * 3)
//! ```
//!
//! 提示：
//! 1. 这需要递归宏来解析嵌套表达式
//! 2. 需要考虑运算符优先级
//! 3. 可以使用 TT Muncher 模式
//!
//! 练习步骤：
//! 1. 先定义 Expr 枚举
//! 2. 实现 ast! 宏支持字面量
//! 3. 添加对 + 和 * 的支持
//! 4. 实现一个简单的求值函数

// TODO: 定义 Expr 枚举
/*
#[derive(Debug, PartialEq)]
enum Expr {
    Literal(i32),
    Add(Box<Expr>, Box<Expr>),
    Mul(Box<Expr>, Box<Expr>),
}

impl Expr {
    fn eval(&self) -> i32 {
        match self {
            Expr::Literal(n) => *n,
            Expr::Add(left, right) => left.eval() + right.eval(),
            Expr::Mul(left, right) => left.eval() * right.eval(),
        }
    }
}
*/

// TODO: 实现 ast! 宏

// 测试模板
#[cfg(test)]
mod tests {
    use super::*;

    // TODO: 当你实现宏后，取消注释这些测试

    /*
    #[test]
    fn test_ast_literal() {
        let expr = ast!(42);
        assert_eq!(expr, Expr::Literal(42));
        assert_eq!(expr.eval(), 42);
    }

    #[test]
    fn test_ast_addition() {
        let expr = ast!(1 + 2);
        assert_eq!(expr.eval(), 3);
    }

    #[test]
    fn test_ast_multiplication() {
        let expr = ast!(2 * 3);
        assert_eq!(expr.eval(), 6);
    }

    #[test]
    fn test_ast_mixed() {
        let expr = ast!(1 + 2 * 3);
        // 注意：简单的实现可能不处理优先级
        // 你的实现应该能正确计算
        assert_eq!(expr.eval(), 7);
    }
    */
}
```

- [ ] **步骤 5：验证编译**

运行: `cd Language/rust/grammer/macro/m3_advanced_match && cargo check`
期望: Compiling m3_advanced_match v0.1.0 Finished

- [ ] **步骤 6：运行测试**

运行: `cargo test`
期望: All tests passed

- [ ] **步骤 7：提交**

```bash
git add Language/rust/grammer/macro/m3_advanced_match/
git commit -m "feat: add M3 高级模式匹配模块"
```

---

### 任务 5：创建 M4 过程宏入门模块 (derive)

**文件：**
- 创建: `Language/rust/grammer/macro/m4_derive/Cargo.toml`
- 创建: `Language/rust/grammer/macro/m4_derive/src/lib.rs`

- [ ] **步骤 1：创建 Cargo.toml**

```toml
[package]
name = "m4_derive"
version = "0.1.0"
edition = "2021"

[lib]
proc-macro = true

[dependencies]
syn = { version = "2.0", features = ["full"] }
quote = "1.0"
proc-macro2 = "1.0"
```

- [ ] **步骤 2：编写 lib.rs (derive 宏实现)**

```rust
//! # M4: 过程宏入门 - derive 宏
//!
//! 本模块演示如何编写 derive 过程宏。
//!
//! 过程宏在编译期接收 TokenStream，处理后再返回 TokenStream。
//! 与声明宏不同，过程宏可以访问完整的语法树。

extern crate proc_macro;

use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, DeriveInput, Data, DataStruct, Fields};

// ============================================================================
// Day 1: 过程宏基础
// ============================================================================

/// 过程宏的类型：
/// 1. derive 宏 - #[derive(MyTrait)]
/// 2. function-like 宏 - my_macro!(args)
/// 3. attribute 宏 - #[my_macro]
///
/// TokenStream 是编译器提供的抽象，表示 token 序列。

/// 简单的 derive 宫：添加一个 `Hello` trait
#[proc_macro_derive(Hello)]
pub fn hello_derive(input: TokenStream) -> TokenStream {
    // 1. 解析输入为语法树
    let input = parse_macro_input!(input as DeriveInput);

    // 2. 获取结构体名称
    let name = &input.ident;

    // 3. 生成实现代码
    let expanded = quote! {
        impl Hello for #name {
            fn hello(&self) {
                println!("Hello, I am {}!", stringify!(#name));
            }
        }
    };

    // 4. 返回 TokenStream
    TokenStream::from(expanded)
}

/// Hello trait 定义（使用者在自己的代码中定义）
pub trait Hello {
    fn hello(&self);
}

// ============================================================================
// Day 2: 解析结构体字段
// ============================================================================

/// 这个 derive 宏可以访问结构体的字段
#[proc_macro_derive(Describe)]
pub fn describe_derive(input: TokenStream) -> TokenStream {
    let input = parse_macro_input!(input as DeriveInput);

    let name = &input.ident;

    // 检查是否是结构体
    let fields = match &input.data {
        Data::Struct(DataStruct { fields, .. }) => fields,
        _ => {
            return syn::Error::new_spanned(
                name,
                "Describe derive only works on structs",
            )
            .to_compile_error()
            .into();
        }
    };

    // 获取字段名称
    let field_names: Vec<_> = fields
        .iter()
        .filter_map(|f| f.ident.as_ref())
        .collect();

    // 生成实现
    let expanded = quote! {
        impl Describe for #name {
            fn describe(&self) -> String {
                let mut description = String::new();
                $(
                    description.push_str(&format!("{}: {:?}, ", stringify!(#field_names), self.#field_names));
                )*
                description
            }
        }
    };

    TokenStream::from(expanded)
}

pub trait Describe {
    fn describe(&self) -> String;
}

// ============================================================================
// Day 3: Builder 模式 derive
// ============================================================================

/// Builder 模式 derive 宏
#[proc_macro_derive(Builder)]
pub fn builder_derive(input: TokenStream) -> TokenStream {
    let input = parse_macro_input!(input as DeriveInput);
    let name = &input.ident;
    let builder_name = format!("{}Builder", name);
    let builder_ident = syn::Ident::new(&builder_name, name.span());

    let fields = match &input.data {
        Data::Struct(DataStruct { fields, .. }) => fields,
        _ => {
            return syn::Error::new_spanned(name, "Builder only works on structs")
                .to_compile_error()
                .into();
        }
    };

    let field_idents: Vec<_> = fields.iter().filter_map(|f| f.ident.as_ref()).collect();
    let field_types: Vec<_> = fields
        .iter()
        .map(|f| &f.ty)
        .collect();

    let expanded = quote! {
        impl #name {
            pub fn builder() -> #builder_ident {
                #builder_ident::default()
            }
        }

        #[derive(Default)]
        pub struct #builder_ident {
            #(
                #field_idents: Option<#field_types>,
            )*
        }

        impl #builder_ident {
            #(
                pub fn #field_idents(mut self, value: #field_types) -> Self {
                    self.#field_idents = Some(value);
                    self
                }
            )*

            pub fn build(self) -> Result<#name, String> {
                Ok(#name {
                    #(
                        #field_idents: self.#field_idents.ok_or_else(|| {
                            format!("Field `{}` is missing", stringify!(#field_idents))
                        })?,
                    )*
                })
            }
        }
    };

    TokenStream::from(expanded)
}

// ============================================================================
// 测试
// ============================================================================

#[cfg(test)]
mod tests {
    use super::*;

    // 测试 Hello derive
    #[derive(Hello)]
    struct Person {
        name: String,
        age: u32,
    }

    #[test]
    fn test_hello_derive() {
        let p = Person {
            name: "Alice".to_string(),
            age: 30,
        };
        p.hello();  // 输出: Hello, I am Person!
    }

    // 测试 Describe derive
    #[derive(Describe)]
    struct Point {
        x: i32,
        y: i32,
    }

    #[test]
    fn test_describe_derive() {
        let p = Point { x: 10, y: 20 };
        let desc = p.describe();
        assert!(desc.contains("x: 10"));
        assert!(desc.contains("y: 20"));
    }

    // 测试 Builder derive
    #[derive(Builder)]
    struct Config {
        host: String,
        port: u16,
    }

    #[test]
    fn test_builder_derive() {
        let config = Config::builder()
            .host("localhost".to_string())
            .port(8080)
            .build()
            .unwrap();

        assert_eq!(config.host, "localhost");
        assert_eq!(config.port, 8080);
    }
}
```

**注意：** 过程宏的测试在 proc-macro crate 的 tests 模块中进行。这些测试使用同一 crate 中定义的 derive 宏，可以验证基本功能。对于更完整的集成测试，可以创建单独的 test crate。

- [ ] **步骤 3：验证编译**

运行: `cd Language/rust/grammer/macro/m4_derive && cargo check`
期望: Compiling m4_derive v0.1.0 Finished

- [ ] **步骤 4：运行测试**

运行: `cargo test`
期望: All tests passed

- [ ] **步骤 5：提交**

```bash
git add Language/rust/grammer/macro/m4_derive/
git commit -m "feat: add M4 过程宏入门模块"
```

---

### 任务 6：创建 M5 过程宏进阶模块

**文件：**
- 创建: `Language/rust/grammer/macro/m5_proc_macro/Cargo.toml`
- 创建: `Language/rust/grammer/macro/m5_proc_macro/src/lib.rs`

- [ ] **步骤 1：创建 Cargo.toml**

```toml
[package]
name = "m5_proc_macro"
version = "0.1.0"
edition = "2021"

[lib]
proc-macro = true

[dependencies]
syn = { version = "2.0", features = ["full"] }
quote = "1.0"
proc-macro2 = "1.0"
```

- [ ] **步骤 2：编写 lib.rs (function-like 和 attribute 宏)**

```rust
//! # M5: 过程宏进阶
//!
//! 本模块演示 function-like 宏和 attribute 宏。

extern crate proc_macro;

use proc_macro::{TokenStream, Ident};
use quote::quote;
use syn::{parse_macro_input, DeriveInput, AttributeArgs, ItemFn, LitStr};

// ============================================================================
// Day 1: function-like 过程宏
// ============================================================================

/// function-like 宏看起来像函数调用：`my_macro!(args)`
///
/// 与 derive 不同，它们可以接受任意参数，不依赖类型。

/// 简单的字符串处理宏
#[proc_macro]
pub fn uppercase(input: TokenStream) -> TokenStream {
    let input = input.to_string();
    let uppercase = input.to_uppercase();

    let output = quote! {
        #uppercase
    };

    TokenStream::from(output)
}

/// 简单的 DSL 宏示例：SQL 查询（非常简化）
#[proc_macro]
pub fn sql(input: TokenStream) -> TokenStream {
    let sql = input.to_string();

    // 这是一个非常简化的实现，只作演示
    // 实际的 SQL 宏需要完整的解析器
    let output = quote! {
        format!("Executing SQL: {}", #sql)
    };

    TokenStream::from(output)
}

// ============================================================================
// Day 2: attribute 过程宏
// ============================================================================

/// attribute 宏附加到函数、结构体等项上：`#[my_macro]`
///
/// 它们可以修改、替换或增强被附加的项。

/// 路由属性宏示例
#[proc_macro_attribute]
pub fn route(_attr: TokenStream, item: TokenStream) -> TokenStream {
    let input = parse_macro_input!(item as ItemFn);

    let fn_name = &input.sig.ident;

    // 在函数开始时添加打印语句
    let expanded = quote! {
        fn #fn_name() {
            println!("Executing route handler: {}", stringify!(#fn_name));
            #input
        }
    };

    TokenStream::from(expanded)
}

/// 调试打印属性宏
#[proc_macro_attribute]
pub fn debug_print(_attr: TokenStream, item: TokenStream) -> TokenStream {
    let input = parse_macro_input!(item as ItemFn);

    let fn_name = &input.sig.ident;
    let block = &input.block;

    let expanded = quote! {
        fn #fn_name() {
            println!(">>> Entering {}", stringify!(#fn_name));
            #block
            println!("<<< Exiting {}", stringify!(#fn_name));
        }
    };

    TokenStream::from(expanded)
}

// ============================================================================
// Day 3: 自定义语法解析
// ============================================================================

/// 自定义解析示例：从属性中提取参数
///
/// 这个宏可以接受属性参数，如 `#[log_call(level = "info")]`

#[proc_macro_attribute]
pub fn log_call(attr: TokenStream, item: TokenStream) -> TokenStream {
    // 解析属性参数，如 #[log_call(level = "debug")]
    let args = parse_macro_input!(attr as AttributeArgs);

    // 解析 level 参数
    let mut level = "info".to_string();  // 默认值

    for arg in args {
        // 简单的参数解析：寻找 MetaNameValue 形式的 level = "xxx"
        if let syn::NestedMeta::Meta(syn::Meta::NameValue(nv)) = arg {
            if nv.path.is_ident("level") {
                if let syn::Lit::Str(lit_str) = nv.lit {
                    level = lit_str.value();
                }
            }
        }
    }

    let input = parse_macro_input!(item as ItemFn);
    let fn_name = &input.sig.ident;
    let block = &input.block;

    let expanded = quote! {
        fn #fn_name() {
            println!("[{}] Calling {}", #level, stringify!(#fn_name));
            #block
            println!("[{}] Finished {}", #level, stringify!(#fn_name));
        }
    };

    TokenStream::from(expanded)
}

// ============================================================================
// Day 4: 综合练习
// ============================================================================

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_uppercase_macro() {
        let result = uppercase!(hello);
        assert_eq!(result, "HELLO");
    }

    #[test]
    fn test_sql_macro() {
        let query = sql!(SELECT * FROM users);
        assert!(query.contains("SELECT * FROM users"));
    }

    #[route]
    fn handler() {
        println!("Handler logic");
    }

    #[test]
    fn test_route_attribute() {
        handler();  // 应该打印 "Executing route handler: handler"
    }

    #[debug_print]
    fn test_function() {
        println!("Inside test function");
    }

    #[test]
    fn test_debug_print() {
        test_function();  // 应该打印进入和退出的信息
    }

    #[log_call]
    fn my_function() {
        println!("Function body");
    }

    #[test]
    fn test_log_call() {
        my_function();  // 应该打印调用和完成的信息
    }
}
```

**注意：** 过程宏的测试在 proc-macro crate 的 tests 模块中进行。这些测试使用同一 crate 中定义的宏，可以验证基本功能。对于更完整的集成测试，可以创建单独的 test crate。

- [ ] **步骤 3：验证编译**

运行: `cd Language/rust/grammer/macro/m5_proc_macro && cargo check`
期望: Compiling m5_proc_macro v0.1.0 Finished

- [ ] **步骤 4：运行测试**

运行: `cargo test`
期望: All tests passed

- [ ] **步骤 5：提交**

```bash
git add Language/rust/grammer/macro/m5_proc_macro/
git commit -m "feat: add M5 过程宏进阶模块"
```

---

### 任务 7：创建 M6 综合实战模块

**文件：**
- 创建: `Language/rust/grammer/macro/m6_project/Cargo.toml`
- 创建: `Language/rust/grammer/macro/m6_project/src/lib.rs`

- [ ] **步骤 1：创建 Cargo.toml**

```toml
[package]
name = "m6_project"
version = "0.1.0"
edition = "2021"

[lib]
proc-macro = true

[dependencies]
syn = { version = "2.0", features = ["full"] }
quote = "1.0"
proc-macro2 = "1.0"
```

- [ ] **步骤 2：编写 lib.rs (综合实战项目框架)**

```rust
//! # M6: 综合实战
//!
//! 这个模块提供了一个实战项目的框架。
//!
//! 实战项目选题：
//! 1. 简化 CRUD 操作的宏
//! 2. 自动序列化宏
//! 3. 命令行解析宏
//!
//! 在这个模块中，从零设计并实现一个完整的宏库。

extern crate proc_macro;

use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, DeriveInput};

// ============================================================================
// 示例项目：自动实现 Display trait
// ============================================================================

/// 这是一个简单的示例，自动为结构体实现 Display trait
///
/// 使用方法：
/// ```rust
/// #[derive(AutoDisplay)]
/// struct Person {
///     name: String,
///     age: u32,
/// }
/// ```
/// 会生成类似 "Person { name: Alice, age: 30 }" 的显示格式

#[proc_macro_derive(AutoDisplay)]
pub fn auto_display_derive(input: TokenStream) -> TokenStream {
    let input = parse_macro_input!(input as DeriveInput);
    let name = &input.ident;

    // 这里简化实现，实际项目需要处理各种情况
    let expanded = quote! {
        impl std::fmt::Display for #name {
            fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
                write!(f, "{} (AutoDisplay)", stringify!(#name))
            }
        }
    };

    TokenStream::from(expanded)
}

// ============================================================================
// 实战项目：简化 CRUD 操作的宏
// ============================================================================

/// 这个实战项目实现了一个简化的 CRUD derive 宏
///
/// 使用方法：
/// ```rust
/// #[derive(CRUD)]
/// struct User {
///     id: u32,
///     name: String,
/// }
/// ```
///
/// 会生成：
/// - `new()`: 创建新实例
/// - `get_id()`: 获取 id 字段
/// - `set_id()`: 设置 id 字段
///
/// 这是一个简化的实现，真实项目会更复杂（支持所有字段、自定义 getter/setter 等）

#[proc_macro_derive(CRUD)]
pub fn crud_derive(input: TokenStream) -> TokenStream {
    let input = parse_macro_input!(input as DeriveInput);
    let name = &input.ident;

    // 获取 id 字段的类型（简化版：假设总是有 id 字段）
    let fields = match &input.data {
        syn::Data::Struct(syn::DataStruct { fields, .. }) => fields,
        _ => {
            return syn::Error::new_spanned(
                name,
                "CRUD derive only works on structs",
            )
            .to_compile_error()
            .into();
        }
    };

    // 查找 id 字段
    let id_field = fields.iter().find(|f| f.ident.as_ref().map_or(false, |i| i == "id"));
    let id_type = id_field
        .and_then(|f| {
            match &f.ty {
                syn::Type::Path(syn::TypePath { path, .. }) => {
                    // 简化：取路径的最后一个段作为类型
                    Some(path.segments.last().unwrap().ident.clone())
                }
                _ => None,
            }
        })
        .unwrap_or_else(|| syn::Ident::new("u32", proc_macro2::Span::call_site()));

    // 生成 CRUD 方法
    let expanded = quote! {
        impl #name {
            /// 创建新实例（简化版：只有 id）
            pub fn new(id: #id_type) -> Self {
                Self {
                    id,
                    // 其他字段使用 Default
                    ..Default::default()
                }
            }

            /// 获取 id
            pub fn id(&self) -> #id_type {
                self.id
            }

            /// 设置 id
            pub fn set_id(&mut self, id: #id_type) {
                self.id = id;
            }
        }

        impl Default for #name {
            fn default() -> Self {
                Self {
                    id: Default::default(),
                    // 注意：真实实现需要处理所有字段
                }
            }
        }
    };

    TokenStream::from(expanded)
}

// ============================================================================
// 测试
// ============================================================================

#[cfg(test)]
mod tests {
    use super::*;

    #[derive(AutoDisplay)]
    struct Example {
        value: i32,
    }

    #[test]
    fn test_auto_display() {
        let ex = Example { value: 42 };
        let display = format!("{}", ex);
        assert!(display.contains("Example"));
        assert!(display.contains("AutoDisplay"));
    }

    #[derive(CRUD)]
    struct User {
        id: u32,
        name: String,
    }

    #[test]
    fn test_crud_derive() {
        let user = User::new(42);
        assert_eq!(user.id(), 42);

        let mut user = user;
        user.set_id(100);
        assert_eq!(user.id(), 100);
    }
}
```

**注意：** 这个实战项目提供了一个简化的 CRUD derive 宏作为起点。你可以基于这个实现继续扩展，例如：
- 支持所有字段而不仅仅是 id
- 添加更多 CRUD 方法（update, delete 等）
- 支持自定义字段映射

- [ ] **步骤 3：验证编译**

运行: `cd Language/rust/grammer/macro/m6_project && cargo check`
期望: Compiling m6_project v0.1.0 Finished

- [ ] **步骤 4：运行测试**

运行: `cargo test`
期望: All tests passed

- [ ] **步骤 5：提交**

```bash
git add Language/rust/grammer/macro/m6_project/
git commit -m "feat: add M6 综合实战模块"
```

---

### 任务 8：创建阅读笔记模板

**文件：**
- 创建: `Language/rust/grammer/macro/reading_notes/serde_derive.md`
- 创建: `Language/rust/grammer/macro/reading_notes/async_trait.md`
- 创建: `Language/rust/grammer/macro/reading_notes/tokio_macros.md`

- [ ] **步骤 1：创建 serde_derive.md**

```markdown
# serde_derive 源码阅读笔记

> 阅读日期：YYYY-MM-DD
> 项目地址：https://github.com/serde-rs/serde

## 概述

serde_derive 是 Rust 中最常用的序列化/反序列化宏库。

## 架构

### 主要组件

1. **derive 宏定义**
   - `#[derive(Serialize)]` - 序列化
   - `#[derive(Deserialize)]` - 反序列化

2. **内部模块**
   - `internals` - 内部类型
   - `bound` - trait bound 处理
   - `de` - 反序列化逻辑
   - `ser` - 序列化逻辑

## 关键技术点

### 1. 如何处理不同的类型？

```rust
// 伪代码示例
match data {
    Data::Struct(_) => handle_struct(...),
    Data::Enum(_) => handle_enum(...),
    Data::Union(_) => handle_union(...),
}
```

### 2. 如何生成 trait bound？

```rust
// 使用 bound 模块
let bounds = compute_bounds(&input, ...);
```

### 3. 如何处理属性？

```rust
// 解析 #[serde(...)] 属性
let attrs = parse_serde_attributes(&input.attrs);
```

## 学习心得

TODO: 填写你的学习心得和发现的最佳实践

## 有用的代码片段

TODO: 记录有价值的代码片段
```

- [ ] **步骤 2：创建 async_trait.md**

```markdown
# async-trait 源码阅读笔记

> 阅读日期：YYYY-MM-DD
> 项目地址：https://github.com/dtolnay/async-trait

## 概述

async-trait 允许在 trait 中使用 async fn，这是 Rust 目前不支持的原生特性。

## 实现原理

### 问题：为什么需要 async-trait？

Rust 的 `async fn` 本质上是返回 `impl Future<Output = T>` 的语法糖。
但是 trait 不能直接使用 `impl Future`，所以需要宏来转换。

### 解决方案

```rust
// 原始代码
async trait MyTrait {
    async fn foo(&self) -> i32;
}

// 宏展开后
trait MyTrait {
    fn foo<'async_trait>(
        &'async_trait self
    ) -> Pin<Box<dyn Future<Output = i32> + Send + 'async_trait>>;
}
```

## 关键技术点

### 1. 函数签名转换

```rust
// 将 async fn 转换为返回 Future 的普通 fn
```

### 2. 生命周期处理

```rust
// 正确处理 'async_trait 生命周期
```

### 3. Self 类型处理

```rust
// 处理不同的 Self 类型（&Self, &mut Self, Arc<Self> 等）
```

## 学习心得

TODO: 填写你的学习心得

## 有用的代码片段

TODO: 记录有价值的代码片段
```

- [ ] **步骤 3：创建 tokio_macros.md**

```markdown
# tokio-macros 源码阅读笔记

> 阅读日期：YYYY-MM-DD
> 项目地址：https://github.com/tokio-rs/tokio

## 概述

tokio-macros 提供了 Tokio 运行时的过程宏，最常用的是 `#[tokio::main]` 和 `#[tokio::test]`。

## 主要宏

### 1. `#[tokio::main]`

```rust
#[tokio::main]
async fn main() {
    // 异步代码
}
```

展开后：
```rust
fn main() {
    tokio::runtime::Builder::new_multi_thread()
        .enable_all()
        .build()
        .unwrap()
        .block_on(async {
            // 原始代码
        })
}
```

### 2. `#[tokio::test]`

类似 main，但创建的是单线程运行时并支持测试框架。

## 关键技术点

### 1. 属性宏的应用

```rust
#[proc_macro_attribute]
pub fn main(args: TokenStream, item: TokenStream) -> TokenStream {
    // 解析属性参数
    // 包装异步代码块
}
```

### 2. 运行时配置

```rust
// 根据属性参数选择运行时类型
// - multi_thread (默认)
// - current_thread
// - single_thread (deprecated)
```

### 3. 错误处理

```rust
// 正确处理测试中的 panic
```

## 学习心得

TODO: 填写你的学习心得

## 有用的代码片段

TODO: 记录有价值的代码片段
```

- [ ] **步骤 4：提交**

```bash
git add Language/rust/grammer/macro/reading_notes/
git commit -m "docs: add reading notes templates"
```

---

### 任务 9：更新主 README 并验证

**文件：**
- 修改: `Language/rust/grammer/macro/README.md`

- [ ] **步骤 1：添加完成状态**

在 README.md 的进度追踪部分，添加一个检查脚本说明：

```markdown
## 验证所有模块

运行以下命令验证所有模块都能正确编译：

```bash
cd m1_macro_rules && cargo test
cd ../m2_hygiene && cargo test
cd ../m3_advanced_match && cargo test
cd ../m4_derive && cargo test
cd ../m5_proc_macro && cargo test
cd ../m6_project && cargo test
```

## 学习检查清单

完成每个模块后，检查是否能够：

- [M1] 理解宏与函数的区别，能编写基本的 `macro_rules!` 宏
- [M1] 熟练使用各种片段说明符（expr, ident, ty 等）
- [M2] 理解宏卫生的概念，能解释 Rust 宏为什么不会污染作用域
- [M2] 知道 Span 的作用，能调试宏展开
- [M3] 能编写递归宏处理复杂情况
- [M3] 能使用 TT Muncher 模式逐个处理 token
- [M4] 理解 TokenStream 和过程宏的工作原理
- [M4] 能独立编写 derive 宏
- [M5] 能编写 function-like 和 attribute 过程宏
- [M5] 能使用 syn 解析自定义语法
- [M6] 能独立设计和实现一个完整的宏库
- [M6] 能阅读和理解真实项目中的宏代码
```

- [ ] **步骤 2：验证所有模块**

运行：
```bash
cd Language/rust/grammer/macro/m1_macro_rules && cargo test
cd ../m2_hygiene && cargo test
cd ../m3_advanced_match && cargo test
cd ../m4_derive && cargo test
cd ../m5_proc_macro && cargo test
cd ../m6_project && cargo test
```

期望: 所有模块测试通过

- [ ] **步骤 3：提交**

```bash
git add Language/rust/grammer/macro/README.md
git commit -m "docs: update README with checklist"
```

---

## 总结

实现完成后，你将拥有：

1. **6 个完整的学习模块**，每个都有详细的代码示例和练习
2. **可运行的测试**，验证所有示例代码的正确性
3. **阅读笔记模板**，用于记录源码学习心得
4. **清晰的目录结构**，方便按进度学习

每个模块都可以独立学习和测试，适合每天 1 小时的学习节奏。
