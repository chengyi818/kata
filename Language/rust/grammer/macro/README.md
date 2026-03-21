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
