---
name: skill-vetter
description: Use when 装其他 skill 前的安全审计，防止恶意代码 - 嵌入式开发常需安装交叉编译、开发板调试等第三方 skill，安全审计尤为重要。
tier: 第一梯队
source: ClawHub
---

# skill-vetter

> **编号**: 01
> **梯队**: 第一梯队
> **来源**: ClawHub

## 解决的问题

ClawHub 上存在 820+ 恶意 skill（约 20%），可能窃取数据、提权、注入 prompt。skill-vetter 是安装其他 skill 的前置安全屏障。

## 适用场景

装其他 skill 前的安全审计，防止恶意代码

**嵌入式场景**: 嵌入式开发常需安装交叉编译、开发板调试等第三方 skill，安全审计尤为重要。

## 安装方法

ClawHub 安装: npx skills add <author>/skill-vetter -g -y

## 使用方法

在安装任何第三方 skill 之前，运行 skill-vetter 扫描其 SKILL.md 和相关脚本，检查是否存在恶意代码、未声明的环境变量访问、隐藏网络调用等。

## 嵌入式开发场景

嵌入式开发常需安装交叉编译、开发板调试等第三方 skill，安全审计尤为重要。

## 相关 Skill

参考 [opencode-skill-list.md](../opencode-skill-list.md) 获取完整清单和学习路径。
