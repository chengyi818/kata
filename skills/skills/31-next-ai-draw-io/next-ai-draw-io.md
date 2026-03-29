---
name: next-ai-draw-io
type: mcp-server
tier: 3 - 效率增强
purpose: "AI 驱动的架构图/流程图生成（基于 draw.io）"
---

# next-ai-draw-io

## 解决的问题

手动绘制架构图/流程图耗时且难以维护。需要通过自然语言描述快速生成专业图表。

## 功能

- 自然语言生成 AWS/GCP/Azure 架构图
- 图片/截图转可编辑图表（OCR + 重建）
- PDF/文档自动提取生成图表
- 交互式对话迭代优化图表
- 支持多模型：Claude、GPT-4、DeepSeek 等

## 安装（MCP Server 方式）

```bash
# 方式1：OpenCode MCP 添加
opencode mcp add
# 配置：npx @next-ai-drawio/mcp-server@latest

# 方式2：直接 npx
npx @next-ai-drawio/mcp-server@latest
```

## 在线体验

https://next-ai-drawio.jiang.jp/

## 来源

https://github.com/DayuanJiang/next-ai-draw-io (23.7k ⭐)

## 适用场景

- 嵌入式系统架构设计
- 内核模块依赖关系图
- 驱动流程图/状态机图
- 云原生部署架构
