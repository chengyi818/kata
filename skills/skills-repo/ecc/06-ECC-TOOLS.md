# Everything Claude Code - 生态系统工具

> ECC 提供的增强工具和第三方集成

---

## AgentShield — 安全审计工具

> 于 Claude Code 黑客松（Cerebral Valley x Anthropic，2026 年 2 月）开发完成
> 
> **指标**: 1282 项测试、98% 覆盖率、102 条静态分析规则

### 快速使用

```bash
# 快速扫描（无需安装）
npx ecc-agentshield scan

# 自动修复安全问题
npx ecc-agentshield scan --fix

# 3 个 Opus 4.6 智能体深度分析
npx ecc-agentshield scan --opus --stream

# 从零生成安全配置
npx ecc-agentshield init
```

### 扫描范围

| 类别 | 检测内容 |
|------|----------|
| 密钥检测 | 14 种模式（API Key、Token、密码） |
| 权限审计 | 文件权限、命令注入风险 |
| 钩子注入 | 钩子脚本安全分析 |
| MCP 评估 | MCP 服务配置风险 |
| Agent 审查 | 智能体定义与工具权限 |

### 输出格式

- **终端**: 彩色等级 A-F
- **JSON**: CI 流水线集成
- **Markdown**: 报告导出
- **HTML**: 可视化报告

### 在 Claude Code 中使用

```bash
/security-scan              # 快速扫描
/security-scan --fix        # 自动修复
/security-scan --opus       # 深度分析
```

### GitHub Action 集成

```yaml
- name: AgentShield Security Scan
  uses: affaan-m/agentshield@main
  with:
    args: --opus --stream
```

**相关链接**: [GitHub](https://github.com/affaan-m/agentshield) | [npm](https://www.npmjs.com/package/ecc-agentshield)

---

## 技能创建器

两种从仓库生成 Claude Code Skills 的方法。

### 选项 A：本地分析（内置）

```bash
/skill-create                    # 分析当前仓库
/skill-create --instincts        # 还为 continuous-learning 生成直觉
```

**输出**:
- `SKILL.md` 文件 - 可直接用于 Claude Code
- 直觉集合 - 用于 continuous-learning-v2
- 模式提取 - 从提交历史中学习

### 选项 B：GitHub 应用（高级）

适用于 10k+ 提交、自动 PR、团队共享场景。

[安装 GitHub 应用](https://github.com/apps/skill-creator) | [ecc.tools](https://ecc.tools)

```bash
# 在任何问题上评论：
/skill-creator analyze

# 或推送到默认分支时自动触发
```

---

## 持续学习 v2

基于直觉的学习系统，自动学习你的模式。

### 核心命令

```bash
# 查看已学习的本能（带置信度评分）
/instinct-status

# 从他人导入本能
/instinct-import <file>

# 导出你的本能供分享
/instinct-export

# 将相关本能聚类为技能
/evolve

# 将项目级直觉提升为全局直觉
/promote

# 查看已识别项目与直觉统计
/projects
```

### 工作流程

1. **学习**: 会话结束时自动提取模式
2. **评估**: 带置信度评分的质量评估
3. **聚类**: 相关本能自动分组
4. **进化**: 高频模式升级为 Skills

完整文档见 `skills/continuous-learning-v2/`。

---

## 上下文注入

ECC 提供动态注入的系统提示上下文。

### 模式上下文

| 上下文 | 用途 |
|--------|------|
| `dev.md` | 开发模式上下文 |
| `review.md` | 代码审查模式上下文 |
| `research.md` | 研究/探索模式上下文 |

### 使用方式

在会话开始时指定模式：

```bash
/context dev      # 开发模式
/context review   # 审查模式
/context research # 研究模式
```

---

## 示例配置

### 项目级 CLAUDE.md

```markdown
# 项目配置

**技术栈**: Go + PostgreSQL + gRPC

**启用 Rules**:
- common/*
- golang/*

**禁用 MCPs**:
- github
- playwright

**自定义命令**:
- /api-review: 审查 API 变更
- /db-migrate: 运行数据库迁移
```

### SaaS 项目示例

参考 `examples/saas-nextjs-CLAUDE.md`：
- Next.js + Supabase + Stripe
- 完整配置示例
- 可直接复用

### Go 微服务示例

参考 `examples/go-microservice-CLAUDE.md`：
- gRPC + PostgreSQL
- 微服务架构配置
- 测试覆盖率要求

---

## 第三方集成

### MCP 服务配置

ECC 预配置了以下 MCP 服务：

| 服务 | 用途 |
|------|------|
| GitHub | PR/Issue 管理 |
| Supabase | 数据库操作 |
| Vercel | 部署管理 |
| Railway | 云服务管理 |
| Context7 | 文档查询 |
| Exa | 网络搜索 |
| Playwright | 浏览器自动化 |
| Sequential Thinking | 多步推理 |
| Memory | 长期记忆 |

配置见 `mcp-configs/mcp-servers.json`。

---

## 性能优化

### 上下文窗口管理

**关键**: 不要一次启用所有 MCP。

经验法则：
- 配置 20-30 个 MCP
- 每个项目保持启用少于 10 个
- 活动工具少于 80 个

在项目配置中使用 `disabledMcpServers`：

```json
{
  "disabledMcpServers": ["github", "playwright"]
}
```

### Token 优化

- 使用后台进程运行长任务
- 精简系统提示
- 选择合适的模型（Opus/Sonnet/Haiku）

---

**最后更新**: 2026-04
