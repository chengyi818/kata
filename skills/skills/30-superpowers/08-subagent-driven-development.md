---
name: subagent-driven-development
type: process
tier: 内置
purpose: "子Agent驱动开发 - 每个任务用独立Agent执行并自动审查"
---

# Subagent-Driven Development

## 作用

执行实施计划时，每个任务分派给独立的 subagent。每个任务完成后自动进行两阶段审查：规格合规审查 + 代码质量审查。

## 与 executing-plans 的区别

| | executing-plans | subagent-driven-development |
|--|----------------|---------------------------|
| 平台 | 不支持 subagent | 支持 subagent |
| 执行 | 串行逐步骤 | 每任务独立 agent |
| 审查 | 手动 | 自动两阶段审查 |
| 上下文 | 共享 | 每个 agent 隔离 |

## 流程

1. **加载实施计划**
2. **逐任务分派**:
   - 为每个任务创建独立 subagent
   - 提供精确的上下文（不含会话历史）
3. **两阶段审查**:
   - **Spec 合规审查** — 是否按计划实现？
   - **代码质量审查** — 代码质量是否达标？
4. **通过 → 继续下一任务** / **不通过 → 修复后重审**

## 适用场景

- 计划中的大部分任务相互独立
- 当前会话中执行（非分 session）
- 需要自动质量保证
