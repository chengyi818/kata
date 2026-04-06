---
name: oh-my-opencode
description: Use when 安装、配置或操作 oh-my-opencode - 多 agent 编排、ultrawork 模式、后台任务管理
tier: 第一梯队
source: OpenCode 内置插件
---

# oh-my-opencode

> **编号**: 03
> **梯队**: 第一梯队
> **来源**: OpenCode 内置插件

## 解决的问题

OpenCode 默认是单 agent 交互模式。oh-my-opencode 提供多 agent 编排能力，支持 ultrawork 模式、后台任务、Prometheus 规划、分类路由等高级功能。

## 适用场景

多 agent 协作、ultrawork 模式、后台任务管理、Prometheus 规划、分类路由、tmux 集成。

**嵌入式场景**: 复杂驱动开发任务分解为多个子 agent 并行执行；后台运行交叉编译长任务；自动规划内核移植步骤。

## 安装方法

OpenCode 内置插件，无需额外安装。配置 `~/.config/opencode/oh-my-opencode.json` 即可使用。

## 使用方法

- **Agent 委派**: 将独立任务分派给不同 agent（Sisyphus、Oracle、Librarian、Explore、Atlas、Prometheus、Metis、Momus）
- **Ultrawork 模式**: 高强度连续工作模式，适合复杂开发任务
- **Prometheus 规划**: 自动生成实施计划，分解复杂任务
- **后台任务**: 将长任务放到后台运行，不阻塞主会话
- **分类路由**: 根据任务类型自动路由到最合适的 agent
- **tmux 集成**: 结合 tmux 实现远程开发板调试

## 嵌入式开发场景

复杂驱动开发任务分解为多个子 agent 并行执行；后台运行交叉编译长任务；自动规划内核移植步骤；结合 tmux 实现远程开发板调试。

## 相关 Skill

参考 [opencode-skill-list.md](../opencode-skill-list.md) 获取完整清单和学习路径。
