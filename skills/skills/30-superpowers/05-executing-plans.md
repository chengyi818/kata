---
name: executing-plans
type: process
tier: 内置
purpose: "按计划执行 - 加载实施计划并逐步完成所有任务"
---

# Executing Plans

## 作用

加载实施计划，逐个任务执行。每完成一个任务就标记为完成，遇到验证步骤就运行验证命令。

## 适用场景

**不支持 subagent 的平台**用此 skill。如果支持 subagent，优先使用 subagent-driven-development。

## 流程

1. **加载计划** — 读取实施计划文档
2. **审查计划** — 批判性评估可行性
3. **逐任务执行**:
   - 标记为 `in_progress`
   - 按计划的步骤精确执行
   - 运行验证命令
   - 标记为 `completed`
4. **最终验证** — 确认所有任务完成

## 关键原则

- 严格按照计划执行，不偏离
- 每步都有验证
- 计划有问题时暂停，向用户确认

## 与其他 skill 的关系

```
brainstorming → writing-plans → executing-plans
                                  或
brainstorming → writing-plans → subagent-driven-development
```
