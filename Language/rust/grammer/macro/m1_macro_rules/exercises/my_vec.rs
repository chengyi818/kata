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
//!
//! 宏 2.0 风格提示：
//! 完成实现后，可以在 lib.rs 中添加：
//! ```rust
//! pub(crate) use my_vec;
//! ```
//! 这样其他模块可以通过 `use crate::my_vec;` 导入，符合模块化最佳实践。

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
