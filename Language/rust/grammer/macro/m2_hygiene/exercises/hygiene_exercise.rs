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
// 目标：创建一个宏，每次调用返回递增的计数值
// 使用 ::std::sync::atomic::AtomicUsize

// TODO: 实现卫生的计数器宏（使用 $crate::）
// 目标：使用 $crate::std::sync::atomic::AtomicUsize

// TODO: 实现一个使用 $crate:: 引用 helper 函数的宏
// 先定义一个 pub fn exercise_helper() -> i32 函数，返回 42
// 然后实现宏调用这个函数

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
        assert_eq!(uc2, uc1 + 1);

        // 卫生的计数器同样跨调用共享状态
        // （在这个例子中，$crate:: 和 ::std 的静态变量行为相同）
        assert_eq!(sc2, sc1 + 1);
    }

    /// 测试 $crate:: 引用的 helper 函数
    #[test]
    fn test_crate_helper() {
        assert_eq!(exercise_helper!(), 42);
    }

    /// 测试卫生性：宏内部变量不影响外部
    #[test]
    fn test_variable_isolation() {
        let temp = "external";

        // 假设你的宏内部也使用了 temp 变量
        my_macro!("test");

        // 外部 temp 应该保持不变
        assert_eq!(temp, "external");
    }
    */
}

// 参考：Rust 宏卫生的实际机制
//
// Rust 的宏卫生性是通过 "hygienic identifiers" 实现的：
// 1. 每个标识符都有一个隐式的 "syntax context"
// 2. 宏展开时，宏内部定义的变量会被赋予独特的上下文
// 3. 这确保宏变量不会与外部变量冲突
//
// 对比 C/C++ 宏：
// - C 宏是简单的文本替换，没有上下文概念
// - Rust 宏在编译期展开，但保留了标识符的上下文信息
//
// $crate:: 的作用：
// - 确保宏可以正确引用定义它的 crate 中的项
// - 即使在其他 crate 中使用这个宏，路径也能正确解析
// - 推荐在所有宏中使用 $crate:: 而不是直接使用 ::
