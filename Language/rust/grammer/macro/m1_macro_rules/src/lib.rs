//! # M1: macro_rules! 基础
//!
//! 本模块演示 Rust 声明宏的基础语法和用法。

// ============================================================================
// Day 1: 宏的概念与基本语法
// ============================================================================

/// 宏与函数的区别：
/// - 宏在编译期展开，函数在运行时调用
/// - 宏可以接受任意数量和类型的参数
/// - 宏在展开前不进行类型检查
///
/// 基本语法：
/// macro_rules! name {
///     (pattern) => { expansion };
/// }

/// 简单的 hello! 宏示例
#[macro_export]
macro_rules! hello {
    () => {
        println!("Hello from macro!");
    };
}

/// 示例：输出问候语
#[cfg(test)]
mod day1_examples {

    #[test]
    fn test_hello_macro() {
        hello!();
    }

    /// 模拟标准库 vec! 宏的简化版本
    #[macro_export]
    macro_rules! simple_vec {
        ( $( $x:expr ),* $(,)? ) => {
            {
                let mut temp_vec = Vec::new();
                $(
                    temp_vec.push($x);
                )*
                temp_vec
            }
        };
    }

    #[test]
    fn test_simple_vec() {
        let v = simple_vec![1, 2, 3];
        assert_eq!(v, vec![1, 2, 3]);

        let v2 = simple_vec![1];
        assert_eq!(v2, vec![1]);

        // 测试尾逗号
        let v3 = simple_vec![1, 2, 3,];
        assert_eq!(v3, vec![1, 2, 3]);
    }
}

// ============================================================================
// Day 2: 片段说明符 (Fragment Specifiers)
// ============================================================================

/// Rust 宏支持多种片段说明符：
///
/// - `ident`: 标识符
/// - `ty`: 类型
/// - `expr`: 表达式
/// - `stmt`: 语句
/// - `pat`: 模式
/// - `path`: 路径
/// - `tt`: 标记树 (Token Tree)
/// - `item`: 项（函数、结构体等）
/// - `block`: 代码块
/// - `meta`: 元数据
/// - `literal`: 字面量

/// 练习：实现 hashmap! 宏
#[macro_export]
macro_rules! hashmap {
    ( $( $key:expr => $val:expr ),* $(,)? ) => {
        {
            let mut map = ::std::collections::HashMap::new();
            $(
                map.insert($key, $val);
            )*
            map
        }
    };
}

#[cfg(test)]
mod day2_examples {

    #[test]
    fn test_hashmap_macro() {
        let map = hashmap! {
            "name" => "Alice",
            "role" => "Developer",
        };
        assert_eq!(map.get("name"), Some(&"Alice"));
        assert_eq!(map.get("role"), Some(&"Developer"));
        assert_eq!(map.len(), 2);
    }

    /// 示例：片段说明符 expr 的使用
    #[macro_export]
    macro_rules! calculate {
        (add $a:expr, $b:expr) => {
            $a + $b
        };
        (mul $a:expr, $b:expr) => {
            $a * $b
        };
    }

    #[test]
    fn test_calculate_macro() {
        assert_eq!(calculate!(add 5, 3), 8);
        assert_eq!(calculate!(mul 5, 3), 15);
    }

    /// 示例：使用多个匹配规则
    #[macro_export]
    macro_rules! greet {
        (Hello $name:ident) => {
            println!("Hello, {}!", stringify!($name));
        };
        (Goodbye $name:ident) => {
            println!("Goodbye, {}!", stringify!($name));
        };
    }

    #[test]
    fn test_greet_macro() {
        greet!(Hello world);
        greet!(Goodbye world);
    }
}

// ============================================================================
// Day 3: 综合练习 - my_vec! 完整版
// ============================================================================

/// 练习：实现支持嵌套的 my_vec! 宏
#[macro_export]
macro_rules! my_vec {
    // 空 vec
    () => {
        Vec::new()
    };

    // 多个元素（包括单个元素情况）
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
mod day3_examples {

    #[test]
    fn test_my_vec_empty() {
        let v: Vec<i32> = my_vec![];
        assert!(v.is_empty());
    }

    #[test]
    fn test_my_vec_single() {
        let v = my_vec![42];
        assert_eq!(v, vec![42]);
    }

    #[test]
    fn test_my_vec_multiple() {
        let v = my_vec![1, 2, 3, 4];
        assert_eq!(v, vec![1, 2, 3, 4]);
    }

    #[test]
    fn test_my_vec_with_trailing_comma() {
        let v = my_vec![1, 2, 3,];
        assert_eq!(v, vec![1, 2, 3]);
    }
}
