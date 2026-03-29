---
name: writing-skills
type: meta
tier: 内置
purpose: "创建自定义Skill - 用TDD方法论编写、测试、部署新skill"
---

# Writing Skills

## 作用

用 TDD 方法论创建和测试 skill。核心思想：先让 agent 在没有 skill 的情况下失败（记录它的理性化借口），再写 skill 去堵住这些漏洞。

## 前置条件

**必须理解 test-driven-development**。本 skill 是 TDD 在文档领域的应用。

## TDD 映射

| TDD 概念 | Skill 创建 |
|----------|-----------|
| 测试用例 | 压力场景（subagent） |
| 生产代码 | SKILL.md 文档 |
| RED | agent 没有 skill 时违规 |
| GREEN | agent 有 skill 后合规 |
| REFACTOR | 堵住新发现的漏洞 |

## 铁律

**没有失败测试就没有 skill。** 先跑基线场景看 agent 失败，再写 skill。

## 流程

1. **RED** — 用 subagent 跑压力场景（无 skill），记录失败行为
2. **GREEN** — 写最小的 skill 堵住这些漏洞
3. **REFACTOR** — 再跑测试，发现新漏洞继续堵
4. **部署** — 提交到 git

## SKILL.md 结构

```yaml
---
name: skill-name
description: Use when [触发条件] - 不要总结流程
---

# Skill 标题

## Overview
核心原则 1-2 句话

## Checklist
必须完成的步骤清单
```

## 适用场景

- 沉淀内核调试工作流
- 团队可复用的开发模式
- 跨项目通用的最佳实践
