---
name: code-review
description: Use when 补丁审查、内核补丁检查 - 内核补丁提交前审查、驱动代码质量检查。
tier: 第二梯队
source: Anthropic 官方
---

# code-review

> **编号**: 08
> **梯队**: 第二梯队
> **来源**: Anthropic 官方

## 解决的问题

内核补丁审查严格，格式/风格/逻辑错误会被 reject。code-review 在提交前自查，提高 patch 接受率。

## 适用场景

补丁审查、内核补丁检查

**嵌入式场景**: 内核补丁提交前审查、驱动代码质量检查。

## 安装方法

Anthropic 官方: npx skills add anthropics/skills@code-review -g -y

## 使用方法

提交代码前自动审查：检查编码规范、潜在 bug、安全漏洞、性能问题。生成结构化 review 报告。

## 嵌入式开发场景

内核补丁提交前审查、驱动代码质量检查。

## 相关 Skill

参考 [opencode-skill-list.md](../opencode-skill-list.md) 获取完整清单和学习路径。
