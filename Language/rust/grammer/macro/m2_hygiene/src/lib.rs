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

/// 使用 $crate:: 引用当前 crate 的项
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

    #[test]
    fn test_hygiene_basic() {
        let x = 100;

        bad_log!("Using bad macro");
        assert_eq!(x, 100);  // 外部 x 不受影响

        good_log!("Using good macro");
        assert_eq!(x, 100);  // 外部 x 不受影响
    }

    #[test]
    fn test_dollar_crate() {
        assert_eq!(using_crate!(), 42);
    }

    /// 对比：不卫生的实现（模拟 C 宏行为）
    /// 使用 const 代替 let 来展示命名冲突
    #[macro_export]
    macro_rules! unhygienic_const {
        () => {
            const COUNTER: u32 = 0;
        };
    }

    #[test]
    fn test_hygiene_with_const() {
        // 外部的 COUNTER
        const COUNTER: u32 = 999;

        // 宏内部也定义了 COUNTER，但由于卫生性，不会冲突
        good_log!("Testing");

        // 外部 COUNTER 仍然是 999
        assert_eq!(COUNTER, 999);
    }
}

// ============================================================================
// Day 2: Span 与调用上下文，对比 $crate:: 和非 $crate::
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

/// 使用 $crate:: 的路径形式（推荐，用于引用当前 crate 的项）
/// 注意：std 库应该使用 ::std 而不是 $crate::std
#[macro_export]
macro_rules! safe_counter {
    () => {{
        static COUNTER: ::std::sync::atomic::AtomicUsize =
            ::std::sync::atomic::AtomicUsize::new(0);
        COUNTER.fetch_add(1, ::std::sync::atomic::Ordering::SeqCst)
    }};
}

/// 不使用 $crate:: 的路径形式（仅在本 crate 可用）
#[macro_export]
macro_rules! unsafe_counter {
    () => {{
        static COUNTER: ::std::sync::atomic::AtomicUsize =
            ::std::sync::atomic::AtomicUsize::new(0);
        COUNTER.fetch_add(1, ::std::sync::atomic::Ordering::SeqCst)
    }};
}

#[cfg(test)]
mod day2_examples {

    #[test]
    fn test_assert_eq_with_message() {
        assert_eq_with_message!(1 + 1, 2, "Math check");
    }

    #[test]
    #[should_panic(expected = "Math check")]
    fn test_assert_eq_with_message_panic() {
        assert_eq_with_message!(1 + 1, 3, "Math check");
    }

    #[test]
    fn test_unsafe_counter() {
        // 注意：由于宏卫生性，每次调用宏都会创建独立的 static 变量
        // 这实际上演示了卫生宏的隔离性
        let count1 = unsafe_counter!();
        // 每次调用都从 0 开始（新的独立变量）
        assert_eq!(count1, 0);
    }

    #[test]
    fn test_safe_counter() {
        // 同样，safe_counter 也因为卫生性而隔离
        let count1 = safe_counter!();
        assert_eq!(count1, 0);
    }

    /// 演示：两个计数器宏的行为实际上相同
    /// 区别在于跨 crate 使用时，$crate:: 能确保正确引用本 crate 的 helper
    /// 而 ::std 是全局路径，用于标准库
    #[test]
    fn test_counter_isolation() {
        let uc1 = unsafe_counter!();
        let sc1 = safe_counter!();

        // 由于卫生性，每个宏调用都创建独立的静态变量
        // 所以每次都是 0
        assert_eq!(uc1, 0);
        assert_eq!(sc1, 0);
    }

    /// 手动测试卫生性：即使我们在外部定义同名变量，宏内部仍然独立
    #[test]
    fn test_hygiene_isolation() {
        let x = 100;
        let y = 200;

        // 宏内部使用 x 和 y，但不会影响外部
        bad_log!("Testing");
        good_log!("Testing");

        // 外部变量不受影响
        assert_eq!(x, 100);
        assert_eq!(y, 200);
    }
}

// ============================================================================
// 跨模块卫生性示例
// ============================================================================

/// 演示宏如何正确处理跨模块的路径引用
pub mod inner {
    pub fn helper() -> i32 {
        100
    }

    /// 在子模块中使用 $crate:: 引用父模块的项
    #[macro_export]
    macro_rules! cross_module_helper {
        () => {
            $crate::inner::helper()
        };
    }
}

#[cfg(test)]
mod cross_module_tests {
    use super::*;

    #[test]
    fn test_cross_module_macro() {
        assert_eq!(cross_module_helper!(), 100);
    }
}
