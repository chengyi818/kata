# async-trait 源码阅读笔记

> 阅读日期：YYYY-MM-DD
> 项目地址：https://github.com/dtolnay/async-trait

## 概述

async-trait 允许在 trait 中使用 async fn，这是 Rust 目前不支持的原生特性。

## 实现原理

### 问题：为什么需要 async-trait？

Rust 的 `async fn` 本质上是返回 `impl Future<Output = T>` 的语法糖。
但是 trait 不能直接使用 `impl Future`，所以需要宏来转换。

### 解决方案

```rust
// 原始代码
async trait MyTrait {
    async fn foo(&self) -> i32;
}

// 宏展开后
trait MyTrait {
    fn foo<'async_trait>(
        &'async_trait self
    ) -> Pin<Box<dyn Future<Output = i32> + Send + 'async_trait>>;
}
```

## 关键技术点

### 1. 函数签名转换

```rust
// 将 async fn 转换为返回 Future 的普通 fn
```

### 2. 生命周期处理

```rust
// 正确处理 'async_trait 生命周期
```

### 3. Self 类型处理

```rust
// 处理不同的 Self 类型（&Self, &mut Self, Arc<Self> 等）
```

## 学习心得

TODO: 填写你的学习心得

## 有用的代码片段

TODO: 记录有价值的代码片段
