# serde_derive 源码阅读笔记

> 阅读日期：YYYY-MM-DD
> 项目地址：https://github.com/serde-rs/serde

## 概述

serde_derive 是 Rust 中最常用的序列化/反序列化宏库。
它展示了如何编写生产级别的 derive 宏。

## 架构

### 主要组件

1. **derive 宏定义**
   - `#[derive(Serialize)]` - 序列化
   - `#[derive(Deserialize)]` - 反序列化

2. **内部模块**
   - `internals` - 内部类型和工具
   - `bound` - trait bound 处理
   - `de` - 反序列化逻辑
   - `ser` - 序列化逻辑

## 关键技术点

### 1. 如何处理不同的类型？

```rust
// 伪代码示例
match data {
    Data::Struct(_) => handle_struct(...),
    Data::Enum(_) => handle_enum(...),
    Data::Union(_) => handle_union(...),
}
```

### 2. 如何生成 trait bound？

serde_derive 使用 bound 模块智能计算需要的 trait bound：

```rust
// 例如：对于泛型结构体
struct Wrapper<T> {
    value: T,
}

// 生成的 Serialize 实现需要：
// impl<T: Serialize> Serialize for Wrapper<T>
```

### 3. 如何处理属性？

解析 `#[serde(...)]` 属性：

```rust
#[derive(Serialize)]
struct User {
    #[serde(rename = "user_name")]
    name: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    email: Option<String>,
}
```

## 宏 2.0 兼容性

serde_derive 利用了宏 2.0 的统一 TokenStream 流水线：

1. **IDE 支持**：rust-analyzer 可以展开 serde 宏，提供正确的类型推断
2. **Clippy 集成**：可以对展开后的代码进行 lint
3. **错误定位**：编译错误指向正确的代码位置

## 学习心得

TODO: 填写你的学习心得和发现的最佳实践

### 最佳实践笔记

1. ___________
2. ___________
3. ___________

## 有用的代码片段

TODO: 记录有价值的代码片段

```rust
// 示例：如何处理字段属性
```

## 参考资源

- [Serde 官方文档](https://serde.rs/)
- [宏小书 - 过程宏](https://veykril.github.io/tlborm/proc-macros.html)
