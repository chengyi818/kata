# tokio-macros 源码阅读笔记

> 阅读日期：YYYY-MM-DD
> 项目地址：https://github.com/tokio-rs/tokio

## 概述

tokio-macros 提供了 Tokio 运行时的过程宏，最常用的是 `#[tokio::main]` 和 `#[tokio::test]`。

## 主要宏

### 1. `#[tokio::main]`

```rust
#[tokio::main]
async fn main() {
    // 异步代码
}
```

展开后：
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

```rust
#[proc_macro_attribute]
pub fn main(args: TokenStream, item: TokenStream) -> TokenStream {
    // 解析属性参数
    // 包装异步代码块
}
```

### 2. 运行时配置

```rust
// 根据属性参数选择运行时类型
// - multi_thread (默认)
// - current_thread
// - single_thread (deprecated)
```

### 3. 错误处理

```rust
// 正确处理测试中的 panic
```

## 学习心得

TODO: 填写你的学习心得

## 有用的代码片段

TODO: 记录有价值的代码片段
