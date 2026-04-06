---
name: planning-with-files
description: Use when 长任务规划持久化，上下文压缩不丢失 - 驱动开发、内核移植等长周期任务的进度管理。
tier: 第一梯队
source: GitHub
---

# planning-with-files

> **编号**: 05
> **梯队**: 第一梯队
> **来源**: GitHub

## 解决的问题

长任务做到一半容易忘记进度；上下文窗口有限导致信息丢失。planning-with-files 将计划外置到文件，跨会话不丢失。

## 适用场景

长任务规划持久化，上下文压缩不丢失

**嵌入式场景**: 驱动开发、内核移植等长周期任务的进度管理。

## 安装方法

GitHub 安装

## 使用方法

将复杂开发任务分解为可追踪的步骤，写入文件持久化。Agent 跨会话读取计划文件，保持上下文连续性。

## 嵌入式开发场景

驱动开发、内核移植等长周期任务的进度管理。

## 相关 Skill

参考 [opencode-skill-list.md](../opencode-skill-list.md) 获取完整清单和学习路径。
