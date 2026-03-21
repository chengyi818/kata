//! # cli-parser - 命令行解析宏库
//!
//! 这是 M6 综合实战项目的主库，综合运用 M1-M5 所学知识。
//!
//! ## 功能特性
//!
//! - `#[derive(Parser)]` - 自动为结构体实现命令行解析 (M4)
//! - `#[arg(short = "x", long = "name")]` - 自定义参数属性 (M5)
//! - `#[command(name = "myapp")]` - 自定义命令属性 (M5)
//! - `declare_args!` - 声明宏简化参数创建 (M1)
//!
//! ## 使用示例
//!
//! ```rust
//! use cli_parser::{Parser, declare_args};
//!
//! #[derive(Parser)]
//! #[command(name = "myapp")]
//! struct Args {
//!     #[arg(short = "n", long = "name")]
//!     name: String,
//!
//!     #[arg(short = "c", long = "count", default_value = "1")]
//!     count: u32,
//! }
//!
//! // 使用声明宏创建参数
//! let args = declare_args! {
//!     "--name" => "Alice",
//!     "--count" => 5,
//! };
//!
//! let parsed = Args::parse_from(&args.iter().map(|s| s.as_str()).collect::<Vec<_>>());
//! ```

// 重新导出 derive 宏
pub use cli_derive::Parser;

// ============================================================================
// 声明宏：declare_args! (M1 知识)
// ============================================================================

/// 声明宏：简化参数列表创建
///
/// 示例：
/// ```rust
/// # use cli_parser::declare_args;
/// let args = declare_args! {
///     "--name" => "Alice",
///     "--count" => 5,
/// };
/// ```
#[macro_export]
macro_rules! declare_args {
    // 基础情况：空参数
    () => {
        Vec::<String>::new()
    };

    // 单个键值对
    ($key:expr => $value:expr) => {
        {
            let mut args = Vec::new();
            args.push($key.to_string());
            args.push($value.to_string());
            args
        }
    };

    // 多个键值对（支持尾逗号）
    (
        $(
            $key:expr => $value:expr
        ),*
        $(,)?
    ) => {
        {
            let mut args = Vec::new();
            $(
                args.push($key.to_string());
                args.push($value.to_string());
            )*
            args
        }
    };
}

// ============================================================================
// Trait 定义
// ============================================================================

/// 可解析 trait（由 derive(Parser) 自动实现）
pub trait Parsable {
    fn parse() -> Self;
    fn parse_from(args: &[&str]) -> Self;
    fn command_name() -> &'static str;
}

/// 参数 trait（用于字段类型约束）
pub trait Arg: Sized {
    fn parse_arg(value: &str) -> Result<Self, String>;
}

// 为常用类型实现 Arg trait
impl Arg for String {
    fn parse_arg(value: &str) -> Result<Self, String> {
        Ok(value.to_string())
    }
}

impl Arg for u32 {
    fn parse_arg(value: &str) -> Result<Self, String> {
        value.parse().map_err(|e| format!("Parse error: {:?}", e))
    }
}

impl Arg for i32 {
    fn parse_arg(value: &str) -> Result<Self, String> {
        value.parse().map_err(|e| format!("Parse error: {:?}", e))
    }
}

impl Arg for bool {
    fn parse_arg(value: &str) -> Result<Self, String> {
        match value.to_lowercase().as_str() {
            "true" | "yes" | "1" => Ok(true),
            "false" | "no" | "0" => Ok(false),
            _ => Err(format!("Invalid boolean value: {}", value)),
        }
    }
}

// ============================================================================
// 辅助函数
// ============================================================================

/// 解析命令行参数（简单版本，不使用宏）
///
/// 这是 M6 项目的底层实现，展示了不使用宏的情况下
/// 如何手动解析命令行参数。
pub fn parse_simple_args(args: &[&str]) -> Vec<(String, String)> {
    let mut result = Vec::new();
    let mut i = 0;

    while i < args.len() {
        let arg = args[i];
        if arg.starts_with("--") || arg.starts_with("-") {
            let key = arg.to_string();
            let value = if i + 1 < args.len() && !args[i + 1].starts_with("-") {
                i += 1;
                args[i].to_string()
            } else {
                "true".to_string() // 对于标志型参数，默认值为 true
            };
            result.push((key, value));
        }
        i += 1;
    }

    result
}

// ============================================================================
// 单元测试
// ============================================================================

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_declare_args_empty() {
        let args: Vec<String> = declare_args!();
        assert!(args.is_empty());
    }

    #[test]
    fn test_declare_args_single() {
        let args = declare_args!["--name" => "Alice"];
        assert_eq!(args, vec!["--name", "Alice"]);
    }

    #[test]
    fn test_declare_args_multiple() {
        let args = declare_args! {
            "--name" => "Alice",
            "--count" => 5,
        };
        assert_eq!(args, vec!["--name", "Alice", "--count", "5"]);
    }

    #[test]
    fn test_declare_args_trailing_comma() {
        let args = declare_args! {
            "--a" => 1,
            "--b" => 2,
        };
        assert_eq!(args, vec!["--a", "1", "--b", "2"]);
    }

    #[test]
    fn test_arg_parsing() {
        assert_eq!(String::parse_arg("test").unwrap(), "test");
        assert_eq!(u32::parse_arg("42").unwrap(), 42);
        assert_eq!(i32::parse_arg("-10").unwrap(), -10);
        assert_eq!(bool::parse_arg("true").unwrap(), true);
        assert_eq!(bool::parse_arg("false").unwrap(), false);
    }

    #[test]
    fn test_parse_simple_args() {
        let args = &["--name", "Alice", "--count", "5"];
        let parsed = parse_simple_args(args);
        assert_eq!(parsed, vec![
            ("--name".to_string(), "Alice".to_string()),
            ("--count".to_string(), "5".to_string()),
        ]);
    }

    #[test]
    fn test_parse_simple_args_flags() {
        let args = &["--verbose", "--name", "test"];
        let parsed = parse_simple_args(args);
        assert_eq!(parsed, vec![
            ("--verbose".to_string(), "true".to_string()),
            ("--name".to_string(), "test".to_string()),
        ]);
    }
}
