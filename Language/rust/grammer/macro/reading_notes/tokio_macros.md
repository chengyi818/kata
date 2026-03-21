# tokio-macros 源码阅读笔记

> 阅读日期：YYYY-MM-DD
> 项目地址：https://github.com/tokio-rs/tokio

## 概述

tokio-macros 提供了 Tokio 运行时的过程宏，最常用的是 `#[tokio::main]` 和 `#[tokio::test]`。
这些宏展示了 attribute 宏如何简化异步代码的编写。

## 主要宏

### 1. `#[tokio::main]`

```rust
#[tokio::main]
async fn main() {
    // 异步代码
}
```

展开后（简化版）：

```rust
fn main() {
    tokio::runtime::Builder::new_multi_thread()
        .enable_all()
        .build()
        .unwrap()
        .block_on(async {
            // 原始代码
        })
}
```

### 2. `#[tokio::test]`

类似 main，但创建的是单线程运行时并支持测试框架。

## 关键技术点

### 1. 属性宏的应用

解析属性参数，选择运行时类型：

```rust
#[tokio::main]                    // 默认多线程
#[tokio::main(flavor = "current_thread")]  // 单线程
#[tokio::main(worker_threads = 4)]       // 指定线程数
```

### 2. 运行时配置

根据属性参数选择运行时类型：
- `multi_thread` (默认)
- `current_thread`

### 3. 错误处理

正确处理测试中的 panic 和错误传播。

## 宏 2.0 工程实践

tokio-macros 展示了宏 2.0 的工程化最佳实践：

1. **模块化组织**：宏代码与其他代码分离
2. **文档示例**：提供丰富的文档测试
3. **配置灵活性**：支持多种运行时配置
4. **IDE 兼容**：展开后的代码可被正确分析

## 调试技巧

### 使用 cargo-expand

```bash
cargo install cargo-expand
cargo expand --test my_test
```

查看 `#[tokio::test]` 展开后的代码。

### 使用 rust-analyzer

VS Code 中可以使用 "Inline Macro" 功能查看展开。

## 学习心得

TODO: 填写你的学习心得

### 关键发现

1. ___________
2. ___________
3. ___________

## 有用的代码片段

TODO: 记录有价值的代码片段

```rust
// 示例：如何创建运行时并 block_on
```

## 参考资源

- [Tokio 官方文档](https://tokio.rs/)
- [Tokio 源码](https://github.com/tokio-rs/tokio/tree/master/tokio-macros)
- [宏小书](https://veykril.github.io/tlborm/)

## 延伸阅读

- `#[tokio::main]` vs 手动创建运行时
- 测试中的异步运行时选择
- 性能考量
