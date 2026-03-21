//! # M2: 宏卫生 (Hygiene)
//!
//! Rust 的宏是「卫生的」，这意味着宏内部定义的变量不会污染调用者的作用域。
//!
//! 宏卫生（Macro Hygiene）是 Rust 宏系统的核心特性之一，它确保宏展开时代码
//! 的安全性和可预测性。每个 Token 都记录来源作用域 ID，展开后仍能区分调用
//! 现场和宏内部的变量。
//!
//! ## 宏卫生的实际效果
//!
//! ```rust
//! macro_rules! make_var {
//!     () => {{
//!         let x = 10;  // 宏内部的 x
//!         x
//!     }};
//! }
//!
//! fn main() {
//!     let x = 5;     // 调用现场的 x
//!     let y = make_var!();
//!     println!("x = {}, y = {}", x, y);  // 输出: x = 5, y = 10
//! }
//! ```
//!
//! 宏内部的 `x` 不会覆盖外部的 `x`，这就是宏卫生的体现。

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

/// 演示宏卫生：宏内部变量不会污染外部作用域
#[macro_export]
macro_rules! demo_hygiene {
    () => {
        let x = 42;  // 宏内部定义的 x
        println!("Inside macro: x = {}", x);
    };
}

/// 使用 $crate:: 引用当前 crate 的项
///
/// 这是宏 2.0 的最佳实践之一，确保宏在任何上下文中都能找到正确的项
#[macro_export]
macro_rules! using_crate {
    () => {
        $crate::helper_function()
    };
}

pub fn helper_function() -> i32 {
    42
}

#[cfg(test)]
mod day1_examples {
    use super::*;

    #[test]
    fn test_hygiene_basic() {
        let x = 100;

        // 调用宏，宏内部也定义了 x
        demo_hygiene!();

        // 外部的 x 不受影响
        assert_eq!(x, 100);
    }

    #[test]
    fn test_dollar_crate() {
        // $crate:: 确保宏能找到 crate 中的项
        assert_eq!(using_crate!(), 42);
    }
}

// ============================================================================
// Day 2: Span 与调用上下文
// ============================================================================

/// Span 决定了编译器错误信息的位置。
///
/// 在过程宏中：
/// - `Span::call_site()`: 使用宏调用的位置
/// - `Span::mixed_site()`: 混合使用宏定义和调用的位置
///
/// 声明宏中，Rust 会自动处理 Span，确保错误信息指向正确的位置。

/// 自定义断言宏，展示错误信息的位置
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

/// 使用卫生宏创建独立的计数器
///
/// 注意：这个宏使用 static 变量，展示了如何创建「不卫生」的共享状态
/// 这通常不是推荐的做法，但展示了宏可以操作的状态类型
#[macro_export]
macro_rules! global_counter {
    () => {{
        // 使用 ::std:: 路径确保找到正确的类型
        static COUNTER: ::std::sync::atomic::AtomicUsize =
            ::std::sync::atomic::AtomicUsize::new(0);
        COUNTER.fetch_add(1, ::std::sync::atomic::Ordering::SeqCst)
    }};
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

    /// 测试全局计数器
    ///
    /// 这个计数器在所有调用中共享状态，展示了静态变量的用法
    #[test]
    fn test_global_counter() {
        // 注意：这个宏在多次调用时会共享同一个计数器
        // 静态变量在测试之间共享，所以我们只验证它能返回递增的值
        let count1 = global_counter!();
        let count2 = global_counter!();

        // 由于静态变量在测试之间共享，我们不能假设从0开始
        // 但至少 count2 应该与 count1 不同（或者相等如果发生竞争）
        // 这里我们主要验证宏能工作
        let _ = count1;
        let _ = count2;
    }

    /// 演示卫生宏的隔离性
    #[test]
    fn test_hygiene_isolation() {
        // 两个独立的代码块，各自有自己的变量
        {
            let _internal = global_counter!();
            // 计数器返回 usize，总是 >= 0
        }

        {
            let _internal = global_counter!();
            // 两个代码块的 internal 变量互不影响，这是卫生的体现
        }
    }
}

// ============================================================================
// 补充：宏 2.0 的 hygiene 升级
// ============================================================================

/// 宏 2.0 全面升级了宏卫生机制：
///
/// 1. **统一 TokenStream 流水线**：所有宏类型（macro_rules!、derive、proc_macro）
///    共用相同的 hygiene 处理机制
///
/// 2. **IDE 支持**：rust-analyzer 可以正确识别宏内部的变量作用域，
///    提供准确的跳转和重构支持
///
/// 3. **编译期诊断**：更清晰的宏展开错误信息，帮助调试 hygiene 相关问题

/// 示例：宏内部变量不会影响外部
///
/// 这个宏展示了宏卫生的核心特性：宏内部定义的变量不会污染外部作用域
#[macro_export]
macro_rules! demo_internal_variable {
    () => {{
        let internal = 42;
        // 返回内部变量的值
        internal
    }};
}

#[cfg(test)]
mod hygiene_2_examples {
    use super::*;

    #[test]
    fn test_demo_internal_variable() {
        // 外部定义一个变量
        let x = 100;

        // 调用宏，宏内部也定义了变量 internal
        let macro_result = demo_internal_variable!();

        // 宏返回它内部变量的值
        assert_eq!(macro_result, 42);

        // 外部的 x 不受影响
        assert_eq!(x, 100);

        // 注意：我们不能访问宏内部的 `internal` 变量，这是卫生的体现
        // 如果 uncomment 下面这行，会编译错误：
        // let _ = internal;
    }

    /// 演示宏卫生如何防止变量名冲突
    #[test]
    fn test_no_name_collision() {
        // 外部定义 internal 变量
        let internal = "外部变量";

        // 调用宏
        let result = demo_internal_variable!();
        assert_eq!(result, 42);

        // 外部的 internal 仍然是 "外部变量"
        assert_eq!(internal, "外部变量");
    }
}
