---
name: requesting-code-review
type: process
tier: 内置
purpose: "请求代码审查 - 完成任务后自动触发代码审查发现问题"
---

# Requesting Code Review

## 作用

在关键节点自动分发代码审查 agent，用独立视角检查代码问题。审查者获得精确的上下文，而非整个会话历史。

## 触发时机

- ✅ 每个 subagent 任务完成后（在 subagent-driven-development 中）
- ✅ 重大功能实现完成后
- ✅ 合并到主分支前
- ✅ 修复复杂 bug 后
- 卡住时 / 重构前

## 流程

1. **准备审查上下文** — 精确描述要审查什么，不含会话历史
2. **分发审查 agent** — 独立视角审查
3. **审查 agent 检查**:
   - 是否符合 spec？
   - 代码质量是否达标？
   - 是否有安全隐患？
   - 是否有遗漏的边界情况？
4. **处理审查结果** — 修复问题或合理反驳

## 与 receiving-code-review 的关系

- 本 skill: 主动发起审查
- receiving-code-review: 处理收到的审查反馈
