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
