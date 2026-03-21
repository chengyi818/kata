# M6 综合实战 - 命令行解析宏库

这是 Rust 宏学习计划的第 6 个模块，综合运用 M1-M5 的知识创建一个完整的命令行解析宏库。

## 项目结构

```
m6_project/
├── Cargo.toml          # Workspace 定义
├── README.md           # 本文件
├── cli-derive/         # 过程宏 crate
│   ├── Cargo.toml
│   └── src/lib.rs      # #[derive(Parser)] 实现
└── cli-parser/         # 主库 crate
    ├── Cargo.toml
    ├── src/lib.rs      # 声明宏、trait 和辅助函数
    └── tests/
        └── integration_test.rs  # 集成测试
```

## 功能特性

### 1. derive(Parser) 宏 (M4 + M5)

为结构体自动生成命令行解析功能：

```rust
use cli_parser::Parser;

#[derive(Parser)]
#[command(name = "myapp")]
struct Args {
    #[arg(short = "n", long = "name")]
    name: String,

    #[arg(short = "c", long = "count", default_value = "1")]
    count: u32,
}
```

支持的属性：
- `#[command(name = "...")]` - 自定义命令名称
- `#[arg(short = "x", long = "name")]` - 短/长选项名
- `#[arg(default_value = "...")]` - 默认值

### 2. declare_args! 声明宏 (M1)

简化测试时的参数创建：

```rust
use cli_parser::declare_args;

let args = declare_args! {
    "--name" => "Alice",
    "--count" => 5,
};
```

特性：
- 支持空参数列表
- 支持单个/多个键值对
- 支持可选尾逗号 (M3)

### 3. 宏卫生实践 (M2)

- 使用 `__cli_args` 等带双下划线前缀的变量名
- 避免变量名与调用者代码冲突

## 知识综合运用

### M1: macro_rules! 基础
- `declare_args!` 宏实现
- 重复模式 `$(...),*` 和可选尾逗号 `$(,)?`

### M2: 宏卫生
- 过程宏内部使用 `__` 前缀变量
- 防止变量名污染调用者作用域

### M3: 高级模式匹配
- 复杂的属性解析逻辑
- 条件代码生成（根据 short/long/default 是否存在）

### M4: 过程宏入门
- `#[proc_macro_derive(Parser)]`
- 使用 `syn` 解析输入
- 使用 `quote` 生成代码

### M5: 过程宏进阶
- 属性解析（`#[arg(...)]`, `#[command(...)]`）
- 嵌套元数据处理
- 错误处理和 span 定位

## 测试覆盖

运行测试：

```bash
cargo test
```

测试类别：
- **单元测试**: 声明宏、trait、辅助函数
- **集成测试**: 完整 CLI 解析场景
- **文档测试**: 示例代码验证

## 使用示例

```rust
use cli_parser::{Parser, declare_args};

#[derive(Parser, Debug)]
#[command(name = "http-cli")]
struct HttpCli {
    #[arg(short = "u", long = "url")]
    url: String,

    #[arg(short = "m", long = "method", default_value = "GET")]
    method: String,
}

fn main() {
    // 方式 1: 从环境变量解析
    // let args = HttpCli::parse();

    // 方式 2: 从字符串切片解析（测试用）
    let args = declare_args! {
        "--url" => "https://example.com",
        "--method" => "POST",
    };
    let cli = HttpCli::parse_from(&args.iter().map(|s| s.as_str()).collect::<Vec<_>>());

    println!("URL: {}", cli.url);
    println!("Method: {}", cli.method);
}
```

## 扩展方向

这个实战项目可以进一步扩展：

1. **子命令支持**: `#[derive(Subcommand)]`
2. **位置参数**: 非选项参数解析
3. **验证器**: 自定义参数验证逻辑
4. **文档生成**: 自动生成 --help 内容
5. **配置文件**: 支持从文件读取配置
