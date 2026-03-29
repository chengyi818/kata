---
name: deer-flow
type: agent-framework
tier: 4 - 按需安装
purpose: "ByteDance 开源长时程超级 Agent 协调框架"
---

# deer-flow

## 解决的问题

复杂多步骤任务（内核模块开发、安全审计、驱动移植）需要长时间自主执行，OpenCode 等对话式助手不适合小时级任务。

## 注意

⚠️ **非传统 Skill** - DeerFlow 是独立 Agent 框架，不是 OpenCode/Claude 的 Skill。可通过 **MCP 协议** 与 OpenCode/Cursor/Claude 集成。

## 功能

- **子 Agent 协调** - LangGraph 驱动，动态工具加载，任务委派
- **沙盒执行** - Docker 隔离容器，完整文件系统 + bash 命令执行
- **长期记忆** - 持久化记忆 + 事实提取 + 上下文摘要
- **渐进式技能** - 按需加载自定义能力，保持上下文精简
- **MCP 集成** - 通过 Model Context Protocol 连接外部工具（支持 OAuth）
- **多模型支持** - 兼容任何 OpenAI 兼容 LLM（支持视觉和推理）

## 安装（Docker 方式，推荐）

```bash
# 1. 克隆仓库
git clone https://github.com/bytedance/deer-flow.git
cd deer-flow

# 2. 配置模型
make config
# 编辑 config.yaml 添加 API key

# 3. 启动服务
make docker-init      # 首次拉取沙盒镜像
make docker-start     # 启动所有服务
# 访问 http://localhost:2026
```

## 本地开发安装

```bash
make dev
```

## 配置示例（config.yaml）

```yaml
models:
  - name: gpt-4
    display_name: GPT-4
    use: langchain_openai:ChatOpenAI
    model: gpt-4
    api_key: $OPENAI_API_KEY
    max_tokens: 4096
```

## 来源

- GitHub: https://github.com/bytedance/deer-flow (51.5k ⭐)
- 文档: https://bytedance-deer-flow.mintlify.app/
- 趋势: GitHub Trending #1 (2026.02 发布后)

## 适用场景

- 复杂内核模块开发（多文件协调、长时编译）
- 自动化安全审计（代码扫描 + 漏洞验证）
- 多步骤设备驱动移植（分析→修改→测试→验证）
- 长时程性能优化（perf 分析 + 多轮调优）

## 与 OpenCode 关系

DeerFlow 是 **独立运行** 的 SuperAgent 平台，与 OpenCode 是互补关系：
- OpenCode: 即时对话式编程助手
- DeerFlow: 长时程自主任务执行（小时级）

可通过 MCP Server 让 OpenCode 调用 DeerFlow 能力。

## 环境要求

- 需要 Docker 环境（沙盒执行依赖）
- 支持多语言界面：中/英/日/法/俄
