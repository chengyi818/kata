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
    use crate::count_tts;

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
        // 单个元素情况
        ( $first:expr ) => { $first };
        // 递归情况
        ( $first:expr, $($rest:expr),+ ) => {
            $first + sum!($($rest),+)
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
        (@accum $acc:expr ) => { $acc };
        (@accum $acc:expr, $head:expr $(, $tail:expr)*) => {
            sum_internal!(@accum $acc + $head $(, $tail)*)
        };
        ($($expr:expr),*) => {
            sum_internal!(@accum 0 $(, $expr)*)
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
    use crate::vector;

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
                    $( $field_name : $field_type ),*
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
