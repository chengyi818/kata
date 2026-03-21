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
