---
name: using-superpowers
type: meta
tier: 内置
purpose: "元技能 - 管理所有skill的发现与调用，会话开始时自动加载"
---

# Using Superpowers

## 作用

Superpowers 的入口技能，会话启动时自动加载。定义了所有 skill 的发现、调用规则和优先级。

## 核心规则

**调用铁律**: 任何任务开始前，必须先检查是否有适用的 skill。即使只有 1% 可能性，也要调用 skill 检查。

## 优先级

```
1. 用户指令 (CLAUDE.md / AGENTS.md)  — 最高
2. Superpowers skills                — 覆盖默认行为
3. 默认系统提示                       — 最低
```

## 常见误区

| 想法 | 真相 |
|------|------|
| "这个太简单不需要skill" | 简单任务也需要检查 |
| "我先看看代码再说" | skill 会告诉你怎么看 |
| "我记得这个skill" | skill 会更新，每次都要重新读 |

## 使用方式

无需手动调用，每次会话自动加载。遇到任何任务时：
1. 先想"有没有 skill 适用？"
2. 有 → 调用 skill
3. 没有 → 正常处理
