# serde_derive 源码阅读笔记

> 阅读日期：YYYY-MM-DD
> 项目地址：https://github.com/serde-rs/serde

## 概述

serde_derive 是 Rust 中最常用的序列化/反序列化宏库。

## 架构

### 主要组件

1. **derive 宏定义**
   - `#[derive(Serialize)]` - 序列化
   - `#[derive(Deserialize)]` - 反序列化

2. **内部模块**
   - `internals` - 内部类型
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

```rust
// 使用 bound 模块
let bounds = compute_bounds(&input, ...);
```

### 3. 如何处理属性？

```rust
// 解析 #[serde(...)] 属性
let attrs = parse_serde_attributes(&input.attrs);
```

## 学习心得

TODO: 填写你的学习心得和发现的最佳实践

## 有用的代码片段

TODO: 记录有价值的代码片段
