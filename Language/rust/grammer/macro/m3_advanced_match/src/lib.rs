//! # M3: 递归宏与高级模式匹配
//!
//! 本模块演示更高级的宏技巧：递归、TT Muncher、嵌套匹配。
//!
//! 宏 2.0 的模块化特性让这些高级模式更易于组织和维护。
//! 通过 `pub(crate) use macro_name;` 可以精确控制宏的可见性。

use serde_json::Value;

// ============================================================================
// Day 1: 递归宏与 TT Muncher
// ============================================================================

/// 递归宏的概念：
/// 宏可以调用自身来处理复杂的情况。
/// 由于 Rust 宏在编译期展开，递归深度有限制，需要谨慎使用。

/// 简单的递归计数宏
///
/// 这个宏递归地统计 token 数量
#[macro_export]
macro_rules! count_tts {
    () => { 0 };
    ( $_tt:tt $($rest:tt)* ) => { 1 + count_tts!($($rest)*) };
}

/// 递归求和宏
///
/// 使用递归逐个处理参数
#[macro_export]
macro_rules! sum {
    // 基础情况：空参数返回 0
    () => { 0 };
    // 递归情况：第一个参数 + 剩余参数的和
    ( $first:expr, $($rest:expr),* ) => {
        $first + sum!($($rest),*)
    };
    // 单个参数
    ( $single:expr ) => { $single };
}

/// TT Muncher 模式：使用 @ 内部规则标记
///
/// @ 开头的规则约定为内部规则，不应该被外部直接调用
/// 这是宏 2.0 最佳实践之一
#[macro_export]
macro_rules! sum_internal {
    // 内部规则：累积计算（基础情况：没有更多参数）
    (@accum $acc:expr) => { $acc };
    // 内部规则：累积计算（递归情况）
    (@accum $acc:expr, $head:expr $(, $tail:expr)*) => {
        sum_internal!(@accum $acc + $head $(, $tail)*)
    };
    // 公共接口
    () => { 0 };
    ($($expr:expr),+ $(,)?) => {
        sum_internal!(@accum 0, $($expr),+)
    };
}

#[cfg(test)]
mod day1_examples {
    use super::*;

    #[test]
    fn test_count_tts() {
        assert_eq!(count_tts!(), 0);
        assert_eq!(count_tts!(a), 1);
        assert_eq!(count_tts!(a b c), 3);
    }

    #[test]
    fn test_sum_macro() {
        assert_eq!(sum!(), 0);
        assert_eq!(sum!(1), 1);
        assert_eq!(sum!(1, 2, 3), 6);
        assert_eq!(sum!(10, 20, 30, 40), 100);
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

/// vector! 宏 - 支持可选尾逗号
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

/// 矩阵宏 - 嵌套重复示例
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

/// 使用 vis 片段说明符匹配可见性修饰符
#[macro_export]
macro_rules! my_struct {
    (
        $( $vis:vis struct $name:ident {
            $( $field_name:ident : $field_type:ty ),* $(,)?
        } )*
    ) => {
        $(
            $vis struct $name {
                $( $field_name: $field_type ),*
            }
        )*
    };
}

// 使用宏生成结构体
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

#[cfg(test)]
mod day2_examples {
    use super::*;

    #[test]
    fn test_vector_macro() {
        let v1 = vector![1, 2, 3];
        let v2 = vector![1, 2, 3,];
        assert_eq!(v1, v2);
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
// Day 3: JSON 宏（简化版演示）
// ============================================================================

/// 简化版 JSON 值构造器
///
/// 这个模块演示了如何为特定类型创建构造宏
/// 完整的 JSON 宏（如 serde_json::json!）需要更复杂的实现
///
/// 练习：尝试实现支持嵌套的完整 json! 宏
pub mod json_demo {
    use serde_json::Value;

    /// 创建 JSON null
    pub fn null() -> Value {
        Value::Null
    }

    /// 创建 JSON 布尔值
    pub fn bool_(v: bool) -> Value {
        Value::Bool(v)
    }

    /// 创建 JSON 字符串
    pub fn string(s: &str) -> Value {
        Value::String(s.to_string())
    }

    /// 创建 JSON 数字
    pub fn number(n: i64) -> Value {
        Value::Number(n.into())
    }
}

#[cfg(test)]
mod day3_examples {
    use super::json_demo::*;

    #[test]
    fn test_json_null() {
        let v = null();
        assert!(v.is_null());
    }

    #[test]
    fn test_json_bool() {
        let v = bool_(true);
        assert_eq!(v, serde_json::Value::Bool(true));

        let v = bool_(false);
        assert_eq!(v, serde_json::Value::Bool(false));
    }

    #[test]
    fn test_json_string() {
        let v = string("hello");
        assert_eq!(v, serde_json::Value::String("hello".to_string()));
    }

    #[test]
    fn test_json_number() {
        let v = number(42);
        assert_eq!(v, serde_json::Value::Number(42.into()));
    }
}
