---
name: tmux
description: Use when 远程开发板调试、交叉编译长任务、内核日志观察 - 嵌入式开发核心能力：远程调试开发板、交叉编译长任务、串口日志监控。
tier: 第一梯队
source: ClawHub
---

# tmux

> **编号**: 03
> **梯队**: 第一梯队
> **来源**: ClawHub

## 解决的问题

远程开发板调试时 SSH 断开会中断任务；交叉编译内核耗时长需后台运行；dmesg 日志需持续观察。tmux 解决会话持久化问题。

## 适用场景

远程开发板调试、交叉编译长任务、内核日志观察

**嵌入式场景**: 嵌入式开发核心能力：远程调试开发板、交叉编译长任务、串口日志监控。

## 安装方法

npx skills add steipete/clawdis@tmux -g -y

## 使用方法

通过 Agent 控制 tmux session，创建/管理/监控远程终端会话。适合 SSH 到开发板后保持长连接运行编译、烧录、日志监控等任务。

## 嵌入式开发场景

嵌入式开发核心能力：远程调试开发板、交叉编译长任务、串口日志监控。

## 相关 Skill

参考 [opencode-skill-list.md](../opencode-skill-list.md) 获取完整清单和学习路径。
