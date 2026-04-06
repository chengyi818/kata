---
name: code-simplifier
description: Use when 驱动代码简化、合并重复逻辑 - 简化驱动中的重复初始化逻辑、错误处理代码。
tier: 第二梯队
source: Anthropic 官方
---

# code-simplifier

> **编号**: 09
> **梯队**: 第二梯队
> **来源**: Anthropic 官方

## 解决的问题

驱动代码常因历史原因积累大量重复逻辑；简化后更易维护、减少 bug。

## 适用场景

驱动代码简化、合并重复逻辑

**嵌入式场景**: 简化驱动中的重复初始化逻辑、错误处理代码。

## 安装方法

Anthropic 官方: npx skills add anthropics/skills@code-simplifier -g -y

## 使用方法

分析代码复杂度，识别重复逻辑、过度设计、冗余代码，提供简化建议并自动重构。

## 嵌入式开发场景

简化驱动中的重复初始化逻辑、错误处理代码。

## 相关 Skill

参考 [opencode-skill-list.md](../opencode-skill-list.md) 获取完整清单和学习路径。
