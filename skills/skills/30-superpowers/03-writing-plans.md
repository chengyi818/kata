---
name: writing-plans
type: process
tier: 内置
purpose: "生成实施计划 - 把设计文档拆解成可执行的步骤清单"
---

# Writing Plans

## 作用

将设计文档（spec）转写为详细的实施计划。假设执行者对代码库零上下文，所以需要记录一切：要改哪些文件、写什么代码、怎么测试。

## 流程

1. **读取设计文档** — 理解要实现什么
2. **探索代码库** — 找到相关文件和现有模式
3. **生成任务清单** — 每个任务原子化、可独立完成
4. **记录验证方式** — 每个任务如何确认完成
5. **保存计划** — `docs/superpowers/plans/YYYY-MM-DD-<feature-name>.md`

## 计划要求

- 每步足够小，执行者能无上下文完成
- 遵循 DRY、YAGNI 原则
- 指定测试方法（推荐 TDD）
- 包含频繁提交的建议

## 适用场景

- Brainstorming 完成后生成实施计划
- 多步骤开发任务拆解
- 团队协作的任务分配

## 前置条件

- 需要已确认的设计文档（来自 brainstorming）
- 建议在 git worktree 中执行（来自 using-git-worktrees）
