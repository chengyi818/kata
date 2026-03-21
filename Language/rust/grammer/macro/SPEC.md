# Rust 宏学习计划设计

> 目标：从零基础到全面掌握 Rust 宏（声明宏、卫生宏、过程宏），覆盖阅读理解、实际开发、深入原理。
> 学习方式：教程驱动，理论 + 代码示例 + 动手练习。
> 节奏：每天 1 小时，预计 18-20 天完成。

---

## 1. 背景

用户有 Rust、C、Python 语言基础，但不熟悉 Rust 的宏机制（包括声明宏 `macro_rules!`、卫生宏 Hygiene、过程宏 proc_macro 等）。希望制定一套从零开始、全面系统的学习计划。

## 2. 学习路径：线性递进式

采用方案 A（线性递进），从 `macro_rules!` 基础逐步深入到过程宏。

### 2.1 模块总览

| 模块 | 主题 | 预计天数 | 阶段目标 |
|------|------|----------|----------|
| M1 | macro_rules! 基础 | 3 天 | 能写基本的声明宏 |
| M2 | 宏卫生 (Hygiene) | 2 天 | 理解卫生宏原理 |
| M3 | 递归宏与高级模式匹配 | 3 天 | 掌握复杂声明宏 |
| M4 | 过程宏入门：derive 宏 | 4 天 | 能写 derive 过程宏 |
| M5 | 过程宏进阶：function-like 与 attribute | 4 天 | 掌握三种过程宏 |
| M6 | 综合实战与阅读 | 3-4 天 | 独立设计宏库 + 阅读源码 |

---

## 3. 模块详细内容

### M1：macro_rules! 基础（3 天）

**目标**：理解宏与函数的区别，掌握 `macro_rules!` 基本语法。

- **Day 1**：宏的概念（宏 vs 函数，编译期 vs 运行时）、基本语法 `macro_rules! name { ... }`、单个模式匹配、片段说明符 `expr`。练习：从零实现 `vec!` 宏。
- **Day 2**：多种匹配规则、重复模式 `$x:expr, *`、所有片段说明符（`ident`, `ty`, `stmt`, `pat`, `path`, `meta`, `tt`, `item`, `block`）、优先级与规则顺序。练习：实现 `hashmap!` 宏。
- **Day 3**：综合练习日。实现 `my_vec!` 宏（完整版，支持嵌套），回顾并整理笔记。

### M2：宏卫生 (Hygiene)（2 天）

**目标**：理解 Rust 卫生宏机制，对比 C 宏的问题。

- **Day 1**：什么是宏卫生、为什么需要（C `#define` 宏的问题对比）、Rust 卫生宏机制原理：`$crate`、变量作用域隔离、Span 与调用上下文。
- **Day 2**：练习：写一个「不卫生」的宏（用 `$crate::` 和非 `$crate::` 对比）、理解 `Span::call_site()` vs `Span::mixed_site()` 的区别。

### M3：递归宏与高级模式匹配（3 天）

**目标**：掌握复杂声明宏的编写技巧。

- **Day 1**：递归宏展开、`@` 内部规则约定（避免外部误调用）、TT Muncher 模式（逐个处理 token）。
- **Day 2**：高级模式匹配：`$($x:expr),* $(,)?`（可选尾逗号）、嵌套匹配、`@__` 内部标记。
- **Day 3**：练习：实现简化版 `json!` 宏、实现一个 AST 构建宏。

### M4：过程宏入门：derive 宏（4 天）

**目标**：理解过程宏体系，能编写 derive 宏。

- **Day 1**：过程宏 vs 声明宏、三种过程宏类型概述（derive / function-like / attribute）、`proc_macro` crate 基础、`TokenStream` 概念。
- **Day 2**：derive 宏结构：`#[proc_macro_derive(MyTrait)]`、`syn` crate 入门（解析 Rust 语法树）、`quote` crate 入门（生成 Rust 代码）。
- **Day 3**：动手写：实现 `#[derive(Hello)]`（输出结构体名）、实现 `#[derive(Builder)]`（生成 builder 模式代码）。
- **Day 4**：阅读任务：阅读 `serde` 的 derive 实现、`thiserror` 的 derive 实现，写阅读笔记。

### M5：过程宏进阶（4 天）

**目标**：掌握 function-like 过程宏和 attribute 过程宏。

- **Day 1**：function-like 过程宏 `#[proc_macro]`，用法场景。练习：实现一个简单的 DSL 宏（如 `sql!(SELECT * FROM users)`）。
- **Day 2**：attribute 过程宏 `#[proc_macro_attribute]`，用法场景。练习：实现 `#[route(GET, "/")]` 或 `#[debug_print]` 宏。
- **Day 3**：`syn` 深入：自定义语法解析、`Parse` trait、`Token!` 宏、`punctuated` 模块。
- **Day 4**：练习：实现 `#[log_call]` 属性宏（自动在函数调用前后打印日志）。

### M6：综合实战与阅读（3-4 天）

**目标**：独立完成一个完整宏库，阅读真实项目源码。

- **Day 1-2**：综合项目。选一个真实场景，从设计到实现一个完整宏库（如简化 CRUD 操作、自动序列化、命令行解析宏等）。
- **Day 3-4**：源码阅读。阅读 2-3 个知名宏库：`serde_derive`、`async-trait`、`tokio-macros`，写阅读笔记，总结最佳实践。

---

## 4. 目录结构

```
Language/rust/grammer/macro/
├── README.md                  # 学习计划总览与进度追踪
├── m1_macro_rules/
│   ├── Cargo.toml
│   ├── src/lib.rs             # 讲解代码 + 示例
│   └── exercises/             # 练习题
│       ├── my_vec.rs
│       └── hashmap.rs
├── m2_hygiene/
│   ├── Cargo.toml
│   └── src/lib.rs
├── m3_advanced_match/
│   ├── Cargo.toml
│   ├── src/lib.rs
│   └── exercises/
│       ├── json_macro.rs
│       └── ast_builder.rs
├── m4_derive/
│   ├── Cargo.toml
│   └── src/lib.rs
├── m5_proc_macro/
│   ├── Cargo.toml
│   └── src/lib.rs
├── m6_project/
│   ├── Cargo.toml
│   └── src/lib.rs
└── reading_notes/
    ├── serde_derive.md
    └── async_trait.md
```

每个模块目录包含：
- `Cargo.toml` — 依赖配置（过程宏模块需 workspace + proc-macro crate）
- `src/lib.rs` — 讲解代码、示例、练习
- 部分模块有 `exercises/` 子目录

---

## 5. 推荐学习资源

### 入门
- [The Rust Reference - Macros](https://doc.rust-lang.org/reference/macros.html)
- [The Little Book of Rust Macros](https://veykril.github.io/tlborm/) — 声明宏最好的教程

### 过程宏
- [`proc_macro` 官方文档](https://doc.rust-lang.org/proc_macro/)
- [`syn` 文档](https://docs.rs/syn/) — Rust 语法解析
- [`quote` 文档](https://docs.rs/quote/) — 代码生成

### 参考项目（源码阅读）
- `serde_derive` — 最经典的 derive 宏
- `thiserror` — 简洁的 derive 宏示例
- `tokio-macros` — attribute 宏实战
- `async-trait` — function-like 过程宏

---

## 6. 与 C/C++ 宏的对比参照

考虑到用户有 C 语言基础，在学习过程中可参照对比：

| 特性 | C/C++ 宏 | Rust 声明宏 | Rust 过程宏 |
|------|----------|-------------|-------------|
| 阶段 | 预处理期 | 编译期 | 编译期 |
| 作用域 | 全局，易污染 | 卫生的 | 完全控制 |
| 能力 | 简单文本替换 | 模式匹配 + 代码生成 | 完整语法树操作 |
| 类型检查 | 无 | 展开后检查 | 可自定义检查 |

---

## 7. 成功标准

学完后应能做到：
1. **读懂**：能读懂标准库和第三方库中的宏定义
2. **编写**：能独立编写声明宏和三种过程宏
3. **调试**：能使用 `cargo expand` 等工具调试宏展开
4. **原理**：理解卫生宏机制、TokenStream、Span 的工作原理
