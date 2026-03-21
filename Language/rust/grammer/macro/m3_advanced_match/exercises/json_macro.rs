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
//! 宏 2.0 风格提示：
//! 使用 `::serde_json::` 开头的绝对路径，确保宏在任何上下文中都能找到正确的类型。
//! 这是宏 2.0 统一命名空间的重要特性。
//!
//! 练习步骤：
//! 1. 先实现支持字面量的版本
//! 2. 添加对对象和数组的支持
//! 3. 测试嵌套结构

use serde_json::Value;

// TODO: 实现你的 json! 宏

// 测试模板
#[cfg(test)]
mod tests {
    use super::*;
    use serde_json::Value;

    // TODO: 当你实现宏后，取消注释这些测试

    /*
    #[test]
    fn test_json_null() {
        let value = json!(null);
        assert!(value.is_null());
    }

    #[test]
    fn test_json_bool() {
        let value = json!(true);
        assert_eq!(value, Value::Bool(true));
    }

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
    fn test_json_array() {
        let value = json!([1, 2, 3]);
        assert!(value.is_array());
        assert_eq!(value[0], 1);
    }

    #[test]
    fn test_json_object() {
        let value = json!({ "name": "Alice", "age": 30 });
        assert!(value.is_object());
        assert_eq!(value["name"], "Alice");
    }

    #[test]
    fn test_json_nested() {
        let value = json!({
            "user": {
                "name": "Alice",
                "tags": ["rust", "macro"]
            }
        });
        assert!(value["user"].is_object());
        assert!(value["user"]["tags"].is_array());
    }
    */
}
