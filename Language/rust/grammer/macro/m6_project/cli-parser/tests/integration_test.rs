//! M6 综合实战 - 集成测试
//!
//! 这个测试文件演示了如何测试一个完整的宏库项目。
//! 综合运用 M1-M5 的知识：
//! - M4: derive 宏测试
//! - M5: 复杂属性解析
//! - M3: 嵌套结构处理
//! - M2: 卫生宏实践
//! - M1: 声明宏使用

use cli_parser::{Parser, declare_args};

// ============================================================================
// 基础 Parser 测试
// ============================================================================

/// 最简单的命令行参数结构体
#[derive(Parser, Debug, PartialEq)]
struct SimpleArgs {
    #[arg(short = "n", long = "name")]
    name: String,
}

#[test]
fn test_simple_parser() {
    let args = SimpleArgs::parse_from(&["--name", "Alice"]);
    assert_eq!(args.name, "Alice");
}

#[test]
fn test_simple_parser_with_short() {
    let args = SimpleArgs::parse_from(&["-n", "Bob"]);
    assert_eq!(args.name, "Bob");
}

// ============================================================================
// 多字段测试
// ============================================================================

/// 多字段命令行参数结构体
#[derive(Parser, Debug, PartialEq)]
struct MultiArgs {
    #[arg(short = "n", long = "name")]
    name: String,

    #[arg(short = "c", long = "count", default_value = "1")]
    count: u32,

    #[arg(short = "v", long = "verbose", default_value = "false")]
    verbose: bool,
}

#[test]
fn test_multi_fields() {
    let args = MultiArgs::parse_from(&[
        "--name", "Test",
        "--count", "42",
        "--verbose", "true",
    ]);
    assert_eq!(args.name, "Test");
    assert_eq!(args.count, 42);
    assert!(args.verbose);
}

#[test]
fn test_default_values() {
    let args = MultiArgs::parse_from(&["--name", "DefaultTest"]);
    assert_eq!(args.name, "DefaultTest");
    assert_eq!(args.count, 1);
    assert!(!args.verbose);
}

#[test]
fn test_partial_override_defaults() {
    let args = MultiArgs::parse_from(&["--name", "Partial", "--count", "10"]);
    assert_eq!(args.name, "Partial");
    assert_eq!(args.count, 10);
    assert!(!args.verbose);
}

// ============================================================================
// 声明宏 integration
// ============================================================================

/// 使用 declare_args! 宏构建参数
#[derive(Parser, Debug, PartialEq)]
struct AppConfig {
    #[arg(short = "h", long = "host")]
    host: String,

    #[arg(short = "p", long = "port", default_value = "8080")]
    port: u32,

    #[arg(short = "d", long = "debug", default_value = "false")]
    debug: bool,
}

#[test]
fn test_declare_args_integration() {
    let args_vec = declare_args! {
        "--host" => "localhost",
        "--port" => 3000,
        "--debug" => true,
    };

    let args_slice: Vec<&str> = args_vec.iter().map(|s| s.as_str()).collect();
    let config = AppConfig::parse_from(&args_slice);

    assert_eq!(config.host, "localhost");
    assert_eq!(config.port, 3000);
    assert!(config.debug);
}

// ============================================================================
// 复杂类型测试
// ============================================================================

/// 混合不同类型的参数
#[derive(Parser, Debug, PartialEq)]
struct MixedTypes {
    #[arg(short = "s", long = "string")]
    string_val: String,

    #[arg(short = "u", long = "unsigned", default_value = "0")]
    unsigned_val: u32,

    #[arg(short = "i", long = "signed", default_value = "-1")]
    signed_val: i32,
}

#[test]
fn test_mixed_types() {
    let args = MixedTypes::parse_from(&[
        "--string", "hello",
        "--unsigned", "100",
        "--signed", "-50",
    ]);

    assert_eq!(args.string_val, "hello");
    assert_eq!(args.unsigned_val, 100);
    assert_eq!(args.signed_val, -50);
}

// ============================================================================
// 命令名称测试
// ============================================================================

/// 测试 command_name 方法
#[derive(Parser, Debug)]
#[command(name = "my-awesome-cli")]
struct CustomNameArgs {
    #[arg(short = "v", long = "value")]
    value: String,
}

#[test]
fn test_custom_command_name() {
    assert_eq!(CustomNameArgs::command_name(), "my-awesome-cli");
}

/// 默认命令名称（结构体名小写）
#[derive(Parser, Debug)]
struct DefaultNameArgs {
    #[arg(short = "v", long = "value")]
    value: String,
}

#[test]
fn test_default_command_name() {
    assert_eq!(DefaultNameArgs::command_name(), "defaultnameargs");
}

// ============================================================================
// 单元结构体测试（简化版）
// ============================================================================

/// 没有字段的单元结构体
#[derive(Parser, Debug, PartialEq)]
struct UnitArgs;

#[test]
fn test_unit_struct() {
    let args = UnitArgs::parse_from(&[]);
    assert_eq!(args, UnitArgs);
    assert_eq!(UnitArgs::command_name(), "unitargs");
}

// ============================================================================
// 错误处理测试
// ============================================================================

/// 测试缺少必需参数的情况（应该 panic）
#[derive(Parser, Debug)]
struct RequiredOnly {
    #[arg(short = "r", long = "required")]
    required: String,
}

#[test]
#[should_panic(expected = "Missing required argument")]
fn test_missing_required_arg() {
    let _args = RequiredOnly::parse_from(&[]);
}

// ============================================================================
// 命名风格测试
// ============================================================================

/// 测试不同的字段命名风格
#[derive(Parser, Debug, PartialEq)]
struct NamingStyles {
    #[arg(short = "s", long = "snake_case")]
    snake_case: String,

    #[arg(short = "c", long = "camelCase")]
    camel_case: String,

    #[arg(short = "u", long = "UPPER_CASE")]
    upper_case: String,
}

#[test]
fn test_naming_styles() {
    let args = NamingStyles::parse_from(&[
        "--snake_case", "snake",
        "--camelCase", "camel",
        "--UPPER_CASE", "upper",
    ]);

    assert_eq!(args.snake_case, "snake");
    assert_eq!(args.camel_case, "camel");
    assert_eq!(args.upper_case, "upper");
}

// ============================================================================
// 综合实战测试
// ============================================================================

/// 模拟真实 CLI 应用的完整测试
#[derive(Parser, Debug, PartialEq)]
#[command(name = "http-cli", version = "1.0.0")]
struct HttpCli {
    #[arg(short = "m", long = "method", default_value = "GET")]
    method: String,

    #[arg(short = "u", long = "url")]
    url: String,

    #[arg(short = "t", long = "timeout", default_value = "30")]
    timeout: u32,

    #[arg(short = "r", long = "retry", default_value = "3")]
    retry: u32,

    #[arg(short = "v", long = "verbose", default_value = "false")]
    verbose: bool,
}

#[test]
fn test_http_cli_full() {
    let cli = HttpCli::parse_from(&[
        "--url", "https://api.example.com/users",
        "--method", "POST",
        "--timeout", "60",
        "--retry", "5",
        "--verbose", "true",
    ]);

    assert_eq!(cli.method, "POST");
    assert_eq!(cli.url, "https://api.example.com/users");
    assert_eq!(cli.timeout, 60);
    assert_eq!(cli.retry, 5);
    assert!(cli.verbose);
}

#[test]
fn test_http_cli_minimal() {
    let cli = HttpCli::parse_from(&["--url", "https://example.com"]);

    assert_eq!(cli.method, "GET");
    assert_eq!(cli.url, "https://example.com");
    assert_eq!(cli.timeout, 30);
    assert_eq!(cli.retry, 3);
    assert!(!cli.verbose);
}

// ============================================================================
// 声明宏组合测试
// ============================================================================

/// 测试 declare_args! 宏的各种用法
#[test]
fn test_declare_args_combinations() {
    // 空参数
    let empty: Vec<String> = declare_args!();
    assert!(empty.is_empty());

    // 单个键值对
    let single = declare_args!("--key" => "value");
    assert_eq!(single, vec!["--key", "value"]);

    // 多个键值对（无尾逗号）
    let multi_no_trailing = declare_args!(
        "--a" => 1,
        "--b" => 2,
        "--c" => 3
    );
    assert_eq!(multi_no_trailing, vec!["--a", "1", "--b", "2", "--c", "3"]);

    // 多个键值对（有尾逗号）
    let multi_trailing = declare_args!(
        "--x" => "hello",
        "--y" => "world",
    );
    assert_eq!(multi_trailing, vec!["--x", "hello", "--y", "world"]);
}

// ============================================================================
// M1-M5 知识回顾测试
// ============================================================================

/// 这个测试展示了如何综合运用 M1-M5 的知识
/// - M1: 使用 declare_args! 声明宏
/// - M2: 宏卫生 - 宏内部变量不会污染测试作用域
/// - M3: 复杂模式匹配支持
/// - M4: derive 宏实现
/// - M5: 属性解析
#[test]
fn test_m1_through_m5_integration() {
    // 使用声明宏创建参数（M1）
    let args = declare_args! {
        "--input" => "data.json",
        "--output" => "result.txt",
        "--threads" => 4,
        "--verbose" => true,
    };

    // 宏卫生验证（M2）：宏内部使用的变量名不会与外部冲突
    let input = "this is a test variable";

    // 使用 derive 宏（M4）解析复杂参数
    #[derive(Parser, Debug, PartialEq)]
    struct ProcessingArgs {
        #[arg(short = "i", long = "input")]
        input: String,

        #[arg(short = "o", long = "output")]
        output: String,

        #[arg(short = "t", long = "threads", default_value = "1")]
        threads: u32,

        #[arg(short = "v", long = "verbose", default_value = "false")]
        verbose: bool,
    }

    let parsed = ProcessingArgs::parse_from(
        &args.iter().map(|s| s.as_str()).collect::<Vec<_>>()
    );

    // 验证外部变量未被宏内部变量覆盖（卫生宏 M2）
    assert_eq!(input, "this is a test variable");

    // 验证解析结果
    assert_eq!(parsed.input, "data.json");
    assert_eq!(parsed.output, "result.txt");
    assert_eq!(parsed.threads, 4);
    assert!(parsed.verbose);
}
