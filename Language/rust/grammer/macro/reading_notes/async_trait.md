# async-trait 源码阅读笔记

> 阅读日期：YYYY-MM-DD
> 项目地址：https://github.com/dtolnay/async-trait

## 概述

async-trait 允许在 trait 中使用 async fn，这是 Rust 目前不支持的原生特性。
它是学习 attribute 宏和复杂代码生成的绝佳案例。

## 实现原理

### 问题：为什么需要 async-trait？

Rust 的 `async fn` 本质上是返回 `impl Future<Output = T>` 的语法糖。
但是 trait 不能直接使用 `impl Future`，所以需要宏来转换。

### 解决方案

```rust
// 原始代码（用户写的）
#[async_trait]
trait MyTrait {
    async fn foo(&self) -> i32;
}

// 宏展开后（编译器看到的）
trait MyTrait {
    fn foo<'async_trait>(
        &'async_trait self
    ) -> ::std::pin::Pin<Box<dyn ::std::future::Future<Output = i32> + Send + 'async_trait>>;
}
```

## 关键技术点

### 1. 函数签名转换

将 `async fn` 转换为返回 Future 的普通 fn：

```rust
// 原始签名
async fn foo(&self) -> i32

// 转换后
fn foo<'life0>(&'life0 self) -> Pin<Box<dyn Future<Output = i32> + Send + 'life0>>
```

### 2. 生命周期处理

正确处理 `'async_trait` 生命周期，确保 self 引用在 Future 执行期间有效。

### 3. Self 类型处理

处理不同的 Self 类型：
- `&Self` -> 正常处理
- `&mut Self` -> 需要特殊处理
- `Arc<Self>` -> 需要特殊处理

### 4. Send bound

默认添加 `+ Send` bound，确保 Future 可以跨线程发送：

```rust
#[async_trait]  // 默认 Send

#[async_trait(?Send)]  // 不需要 Send
```

## 宏 2.0 视角

async-trait 展示了宏 2.0 统一命名空间的优势：

1. **模块化导入**：作为普通 crate 导入，不需要 `#[macro_use]`
2. **IDE 支持**：rust-analyzer 可以理解展开后的 trait 定义
3. **TokenStream 流水线**：生成的代码可以被其他工具正确处理

## 学习心得

TODO: 填写你的学习心得

### 关键点理解

1. ___________
2. ___________
3. ___________

## 有用的代码片段

TODO: 记录有价值的代码片段

```rust
// 示例：如何转换 async fn 签名
```

## 参考资源

- [async-trait 文档](https://docs.rs/async-trait/)
- [Rust Async 书籍](https://rust-lang.github.io/async-book/)
- [dtolnay 的其他宏项目](https://github.com/dtolnay)
