---
name: mcp-builder
description: Use when 自定义 MCP Server（如连接开发板） - 连接开发板调试接口、硬件测试工具、串口控制台。
tier: 第三梯队
source: Anthropic 官方 (29.3K 下载)
---

# mcp-builder

> **编号**: 15
> **梯队**: 第三梯队
> **来源**: Anthropic 官方 (29.3K 下载)

## 解决的问题

开发板调试工具、硬件测试设备没有标准 API。MCP Server 桥接这些工具与 Agent。29.3K 下载量。

## 适用场景

自定义 MCP Server（如连接开发板）

**嵌入式场景**: 连接开发板调试接口、硬件测试工具、串口控制台。

## 安装方法

Anthropic 官方: npx skills add anthropics/skills@mcp-builder -g -y

## 使用方法

创建自定义 MCP Server，将外部工具/服务（如开发板调试接口、示波器控制、JTAG 调试器）暴露给 Agent 调用。

## 嵌入式开发场景

连接开发板调试接口、硬件测试工具、串口控制台。

## 相关 Skill

参考 [opencode-skill-list.md](../opencode-skill-list.md) 获取完整清单和学习路径。
