//! 练习：探索宏卫生
//!
//! Day 2 练习：理解宏卫生的实际效果
//!
//! 目标：
//! 1. 对比不同实现方式的效果
//! 2. 理解 Span 的作用
//! 3. 使用 $crate:: 引用当前 crate 的项
//!
//! 提示：
//! - 使用 static 创建全局变量（谨慎使用）
//! - 使用 AtomicUsize 进行原子操作
//! - 使用 $crate:: 来确保宏可以找到 helper 函数
//!
//! 宏 2.0 风格提示：
//! 使用 `::std::` 开头的绝对路径（如 `::std::sync::atomic::AtomicUsize`）
//! 确保宏在任何 crate 中都能正确工作，这是宏 2.0 的最佳实践。

use std::sync::atomic::{AtomicUsize, Ordering};

// TODO: 实现一个使用全局 static 计数器的宏
// 提示：使用 ::std::sync::atomic::AtomicUsize

// TODO: 实现一个使用 $crate:: 调用 helper 函数的宏
// 提示：先在 lib.rs 中定义 helper 函数，然后用 $crate:: 引用

// TODO: 实现一个展示卫生性的宏
// 宏内部定义变量，外部同名变量不受影响

#[cfg(test)]
mod tests {
    use std::sync::atomic::{AtomicUsize, Ordering};

    // TODO: 在你实现宏后，取消注释这些测试

    /*
    use super::*;

    #[test]
    fn test_global_counter() {
        let c1 = my_counter!();
        let c2 = my_counter!();
        assert!(c2 > c1);
    }

    #[test]
    fn test_hygiene_demo() {
        let x = "original";
        hygiene_demo!();  // 宏内部定义了 x = 42
        // 这里的 x 仍然是 "original"，不受宏内部影响
        assert_eq!(x, "original");
    }

    #[test]
    fn test_dollar_crate_helper() {
        // 假设你在 lib.rs 中定义了 helper_fn() -> i32
        let result = call_helper!();
        assert_eq!(result, 100);  // 假设 helper_fn 返回 100
    }
    */
}
