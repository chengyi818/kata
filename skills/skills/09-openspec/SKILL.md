---
name: openspec
description: Use when 构建功能、迁移、重构或任何结构化开发工作 - 规范驱动开发流程
tier: 第二梯队
source: OpenCode 内置插件
---

# openspec

> **编号**: 09
> **梯队**: 第二梯队
> **来源**: OpenCode 内置插件

## 解决的问题

开发任务缺乏结构化规划，直接编码容易导致需求理解偏差、架构设计不合理、实现遗漏。openspec 提供 proposal → specs → design → tasks 的完整流程。

## 适用场景

规范驱动开发：proposal → specs → design → tasks → implementation。支持自定义 schema（TDD、rapid 等）。

**嵌入式场景**: 驱动开发前先写规范文档；内核迁移任务分解；重构任务的结构化规划。

## 安装方法

OpenCode 内置插件，无需额外安装。使用 `/opsx` 命令触发 openspec 工作流。

## 使用方法

- **Proposal**: 提出功能/重构/迁移的初步方案
- **Specs**: 定义详细的技术规范和需求
- **Design**: 设计实现方案，包括架构、接口、数据流
- **Tasks**: 分解为可执行的具体任务列表
- **Implementation**: 按任务列表逐步实现
- **自定义 Schema**: 支持 TDD、rapid 等不同开发模式

## 嵌入式开发场景

驱动开发前先写规范文档（设备接口、数据结构、错误处理）；内核迁移任务分解（API 变更、配置调整、测试验证）；重构任务的结构化规划。

## 相关 Skill

参考 [opencode-skill-list.md](../opencode-skill-list.md) 获取完整清单和学习路径。
