# Rust 宏学习计划

> 从零基础到全面掌握 Rust 宏（声明宏、卫生宏、过程宏）
> 学习方式：教程驱动，理论 + 代码示例 + 动手练习
> 节奏：每天 1 小时，预计 18-20 天完成

## 进度追踪

| 模块 | 主题 | 预计天数 | 状态 |
|------|------|----------|------|
| M1 | macro_rules! 基础 | 3 天 | ⬜ 未开始 |
| M2 | 宏卫生 (Hygiene) | 2 天 | ⬜ 未开始 |
| M3 | 递归宏与高级模式匹配 | 3 天 | ⬜ 未开始 |
| M4 | 过程宏入门：derive 宏 | 4 天 | ⬜ 未开始 |
| M5 | 过程宏进阶：function-like 与 attribute | 4 天 | ⬜ 未开始 |
| M6 | 综合实战与阅读 | 3-4 天 | ⬜ 未开始 |

## 推荐学习资源

### 入门
- [The Rust Reference - Macros](https://doc.rust-lang.org/reference/macros.html)
- [The Little Book of Rust Macros](https://veykril.github.io/tlborm/)

### 过程宏
- [`proc_macro` 官方文档](https://doc.rust-lang.org/proc_macro/)
- [`syn` 文档](https://docs.rs/syn/)
- [`quote` 文档](https://docs.rs/quote/)

## 与 C/C++ 宏的对比

| 特性 | C/C++ 宏 | Rust 声明宏 | Rust 过程宏 |
|------|----------|-------------|-------------|
| 阶段 | 预处理期 | 编译期 | 编译期 |
| 作用域 | 全局，易污染 | 卫生的 | 完全控制 |
| 能力 | 简单文本替换 | 模式匹配 + 代码生成 | 完整语法树操作 |
| 类型检查 | 无 | 展开后检查 | 可自定义检查 |

## 宏 1.0 vs 宏 2.0

Rust 宏系统正在向「宏 2.0」演进，主要改进包括：

| 对比项 | 宏 1.0 (`macro_rules!`) | 宏 2.0（模块化声明宏） |
|--------|------------------------|----------------------|
| 导入方式 | 依赖 `#[macro_use]` 或 `use crate::macros::*` | 使用常规路径 `crate::macros::macro_name!`，无需特殊导出 |
| 作用域控制 | 宏默认全局，命名冲突较多 | 遵循模块可见性，可通过 `pub` 精准控制 |
| IDE 支持 | 匹配分支提示有限 | `rust-analyzer` 等工具提供补全、跳转、文档提示 |
| 组合维护 | 大型宏库需要手动拆分文件 | 支持模块化组织与按需导入，更易维护 |

### 宏 2.0 模块化导出示例（Stable Rust）

```rust
// src/macros.rs
macro_rules! add_two {
    ($a:expr, $b:expr) => { $a + $b };
}
pub(crate) use add_two; // 宏 2.0：通过 use 暴露宏

// src/main.rs
use crate::macros::add_two; // 和函数一样通过 use 引入
fn main() {
    println!("9 + 23 = {}", add_two!(9, 23));
}
```

## 验证所有模块

运行以下命令验证所有模块都能正确编译：

```bash
cd m1_macro_rules && cargo test
cd ../m2_hygiene && cargo test
cd ../m3_advanced_match && cargo test
cd ../m4_derive && cargo test
cd ../m5_proc_macro && cargo test
cd ../m6_project && cargo test
```

## 学习检查清单

完成每个模块后，检查是否能够：

- [M1] 理解宏与函数的区别，能编写基本的 `macro_rules!` 宏
- [M1] 熟练使用各种片段说明符（expr, ident, ty 等）
- [M2] 理解宏卫生的概念，能解释 Rust 宏为什么不会污染作用域
- [M2] 知道 Span 的作用，能调试宏展开
- [M3] 能编写递归宏处理复杂情况
- [M3] 能使用 TT Muncher 模式逐个处理 token
- [M4] 理解 TokenStream 和过程宏的工作原理
- [M4] 能独立编写 derive 宏
- [M5] 能编写 function-like 和 attribute 过程宏
- [M5] 能使用 syn 解析自定义语法
- [M6] 能独立设计和实现一个完整的宏库
- [M6] 能阅读和理解真实项目中的宏代码

## 调试技巧

### 使用 cargo-expand 查看宏展开

```bash
cargo install cargo-expand
cargo expand  # 查看当前 crate 的宏展开
cargo expand module_name  # 查看特定模块的宏展开
```

### 使用 rust-analyzer

现代 IDE（如 VS Code + rust-analyzer）支持：
- 宏展开的预览（Inline Macro）
- 跳转到宏定义
- 宏参数补全和文档提示

## 目录结构

```
Language/rust/grammer/macro/
├── README.md                  # 本文件
├── m1_macro_rules/            # M1: macro_rules! 基础
├── m2_hygiene/                # M2: 宏卫生
├── m3_advanced_match/         # M3: 递归宏与高级模式匹配
├── m4_derive/                 # M4: 过程宏入门
├── m5_proc_macro/             # M5: 过程宏进阶
├── m6_project/                # M6: 综合实战
└── reading_notes/             # 源码阅读笔记
    ├── serde_derive.md
    ├── async_trait.md
    └── tokio_macros.md
```

## 关于宏卫生（Macro Hygiene）

Rust 的宏是「卫生的」，这意味着宏内部定义的变量不会污染调用者的作用域。这是通过在展开时为变量添加唯一的标识符来实现的。

### 宏卫生的实际效果

```rust
macro_rules! make_var {
    () => {{
        let x = 10;  // 宏内部的 x
        x
    }};
}

fn main() {
    let x = 5;     // 调用现场的 x
    let y = make_var!();
    println!("x = {}, y = {}", x, y);  // 输出: x = 5, y = 10
}
```

宏内部的 `x` 不会覆盖外部的 `x`，这就是宏卫生的体现。

---

> **注意：** 本学习计划参考了《Rust宏2.0入门：像搭乐高一样写代码》（微信公众号文章）中的现代宏系统概念和最佳实践。
