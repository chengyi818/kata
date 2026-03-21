# OpenCode Skill 清单

> 适用人群: Linux 嵌入式底层程序员 (C/Rust/Python, 内核/效率工具/防护网)
>
> 更新时间: 2026-03-21
>
> 数据来源: [ClawHub](https://clawhub.ai/skills?sort=downloads) TOP 50 下载排名
>
> **本清单覆盖 80+ Skills，按 6 大维度分类，含 4 级安装优先级**

---

## 什么是 Skill？

> 🎬 视频入门：[什么是大模型Skill 10分钟弄懂](https://www.bilibili.com/video/BV1dz6oBWEWx/) (隔壁的程序员老王)

### 一句话理解

**Skill = 高级提示词 + 模块化能力 + 可复用 + 可控**

### 普通 Prompt vs Skill

| 维度 | 普通 Prompt | Skill |
|------|-------------|-------|
| 颗粒度 | 粗糙，一句话指令 | 精细，数千字步骤拆解 |
| 稳定性 | 碰运气，容易"幻觉" | 像工厂流水线稳定输出 |
| 复用性 | 复制粘贴，很麻烦 | 一键调用，无缝衔接 |
| 形象类比 | 临时抓壮丁 | 请了一位带手册的专家 |

### Skill 本质：岗位 SOP

如果大模型是一个高智商的"通用人才"，Skill 就是为它配备的**"岗位 SOP（标准作业程序）"**。

- 传统方式：把所有规则塞进 System Prompt → token 浪费、容易混淆
- Skill 方式：模型按需动态加载对应的 Skill → 只加载当前需要的规则

### 文件结构

每个 Skill 就是一个包含 `SKILL.md` 的目录：

```yaml
---
name: skill-name
description: Use when [触发条件] - [功能描述]
---

# Skill 标题

[数千字的步骤拆解、规则定义、工具调用说明]
```

### 渐进式披露架构 (Progressive Disclosure)

| 层级 | 组件 | 加载策略 | 作用 |
|------|------|----------|------|
| L0 | 目录 | Always-On (始终加载) | 告诉模型有哪些 Skill 可用 |
| L1 | 元数据 | On-Demand | 判断是否需要调用此 Skill |
| L2 | 指令 | On-Demand (命中后加载) | 定义具体业务处理逻辑与 SOP |
| L3 | 引用 | On-Demand | 外部知识库、参考资料 |
| L4 | 脚本 | Execution (执行时) | 实际的自动化脚本和工具调用 |

### Skill 生态层级

```
大模型 (嘴) ──→ 我问你答
    ↓
智能体 Agent (模板) ──→ 套模板复用
    ↓
工作流 Workflow (生产线) ──→ 串联多步
    ↓
Skill (经验) ──→ 用我的方法做，带知识库
    ↓
龙虾助理 Lobster (手) ──→ 帮你动手干，跨软件操作
```

### 类比理解

| 角色 | 类比 | 能力 |
|------|------|------|
| 大模型 | 万事通 | 随叫随到回答问题 |
| 智能体 | 熟练工 | 专干某一类活 |
| 工作流 | 生产线 | 串联多步智能体 |
| **Skill** | **带手册的专家** | **封装经验和知识，可复用** |
| 龙虾助理 | 私人秘书 | 操作设备，跨软件执行 |

---

## 一、ClawHub TOP 50 Skills (按用途分类)

### 🔧 1. 开发工具 (Development)

| # | Skill | 下载量 | ⭐ | 说明 |
|---|-------|--------|-----|------|
| 1 | [self-improving-agent](https://clawhub.ai/skills/self-improving-agent) | 87.6K | 1061 | Agent 自学习记忆系统，跨会话持续改进 |
| 2 | [github](https://clawhub.ai/skills/github) | 61.6K | 208 | GitHub CLI 集成 (issue/pr/run/api) |
| 3 | [skill-creator](https://clawhub.ai/skills/skill-creator) | 21.9K | 84 | 自定义 Skill 创建指南 |
| 4 | [byterover](https://clawhub.ai/skills/byterover) | 23.4K | 71 | Agent 知识管理，项目模式存储检索 |
| 5 | [elite-longterm-memory](https://clawhub.ai/skills/elite-longterm-memory) | 19.3K | 89 | 长期记忆系统 (WAL + vector search + git-notes) |
| 6 | [proactive-agent](https://clawhub.ai/skills/proactive-agent) | 49.2K | 327 | 主动式 Agent，预测需求自主执行 |
| 7 | [mcporter](https://clawhub.ai/skills/mcporter) | 26.4K | 78 | MCP 服务器工具调用管理 |
| 8 | [frontend-design](https://clawhub.ai/skills/frontend-design) | 20.2K | 160 | 高质量前端界面生成，告别 AI 模板感 |
| 9 | [clawddocs](https://clawhub.ai/skills/clawddocs) | 21.5K | 211 | Clawdbot 文档专家，配置代码速查 |
| 10 | [auto-updater](https://clawhub.ai/skills/auto-updater) | 24.0K | 178 | 自动更新 Agent 和已装 Skills |
| 11 | [model-usage](https://clawhub.ai/skills/model-usage) | 18.9K | 63 | 模型用量/成本统计 |
| 12 | [skill-vetter](https://clawhub.ai/skills/skill-vetter) | 12.3K | — | 安全审计 Skill (安装前检查 20+ 危险信号) |

---

### 🔍 2. 搜索与信息获取 (Search & Research)

| # | Skill | 下载量 | ⭐ | 说明 |
|---|-------|--------|-----|------|
| 1 | [tavily-search](https://clawhub.ai/skills/tavily-search) | 76.3K | 345 | AI 优化的网页搜索 API |
| 2 | [find-skills](https://clawhub.ai/skills/find-skills) | 72.3K | 320 | 智能发现并安装可用 Skills |
| 3 | [agent-browser](https://clawhub.ai/skills/agent-browser) | 61.1K | 321 | Rust 无头浏览器自动化 (点击/输入/截图) |
| 4 | [brave-search](https://clawhub.ai/skills/brave-search) | 25.1K | 111 | Brave Search API 文档/事实搜索 |
| 5 | [baidu-search](https://clawhub.ai/skills/baidu-search) | 19.8K | 39 | 百度 AI 搜索引擎集成 |
| 6 | [browser-use](https://clawhub.ai/skills/browser-use) | 17.2K | 44 | 浏览器交互自动化 (测试/表单/数据提取) |
| 7 | [youtube-watcher](https://clawhub.ai/skills/youtube-watcher) | 21.3K | 163 | YouTube 视频转录获取与摘要 |
| 8 | [playwright-mcp](https://clawhub.ai/skills/playwright-mcp) | 12.7K | — | Playwright MCP 浏览器自动化 (导航/交互/截图) |
| 9 | [playwright-scraper-skill](https://clawhub.ai/skills/playwright-scraper-skill) | 15.2K | 30 | Playwright 反爬虫抓取 (支持 Cloudflare 绕过) |

---

### 📄 3. 文档与内容处理 (Document & Content)

| # | Skill | 下载量 | ⭐ | 说明 |
|---|-------|--------|-----|------|
| 1 | [summarize](https://clawhub.ai/skills/summarize) | 66.4K | 309 | 智能摘要 (网页/PDF/图片/音频/YouTube) |
| 2 | [humanizer](https://clawhub.ai/skills/humanizer) | 28.6K | 261 | 去 AI 痕迹写作，让文字更自然 |
| 3 | [nano-pdf](https://clawhub.ai/skills/nano-pdf) | 32.9K | 78 | 自然语言编辑 PDF |
| 4 | [nano-banana-pro](https://clawhub.ai/skills/nano-banana-pro) | 31.6K | 144 | AI 图片生成/编辑 (Gemini 3 Pro) |
| 5 | [humanize-ai-text](https://clawhub.ai/skills/humanize-ai-text) | 24.5K | 102 | AI 文本人性化改写，绕过检测器 |
| 6 | [obsidian](https://clawhub.ai/skills/obsidian) | 30.9K | 129 | Obsidian 知识库管理 (Markdown 笔记) |
| 7 | [openai-whisper](https://clawhub.ai/skills/openai-whisper) | 28.4K | 149 | 本地语音转文字 (无需 API Key) |
| 8 | [video-frames](https://clawhub.ai/skills/video-frames) | 18.3K | 51 | ffmpeg 视频帧/片段提取 |

---

### 📧 4. 通讯与社交 (Communication)

| # | Skill | 下载量 | ⭐ | 说明 |
|---|-------|--------|-----|------|
| 1 | [himalaya](https://clawhub.ai/skills/himalaya) | 21.3K | 41 | CLI 邮件管理 (IMAP/SMTP，多账户) |
| 2 | [slack](https://clawhub.ai/skills/slack) | 20.2K | 79 | Slack 消息/频道/置顶管理 |
| 3 | [gmail](https://clawhub.ai/skills/gmail) | 19.4K | 50 | Gmail API (OAuth) 邮件/标签/草稿 |
| 4 | [imap-smtp-email](https://clawhub.ai/skills/imap-smtp-email) | 16.9K | 37 | IMAP/SMTP 邮件收发 (含附件) |
| 5 | [outlook-api](https://clawhub.ai/skills/outlook-api) | 17.7K | 28 | Microsoft Outlook (Graph API) 集成 |
| 6 | [whatsapp-business](https://clawhub.ai/skills/whatsapp-business) | 17.0K | 38 | WhatsApp Business API 消息管理 |
| 7 | [youtube-api-skill](https://clawhub.ai/skills/youtube-api-skill) | 20.5K | 103 | YouTube Data API (视频/播放列表/评论) |

---

### ☁️ 5. 云服务与平台集成 (Cloud & Integration)

| # | Skill | 下载量 | ⭐ | 说明 |
|---|-------|--------|-----|------|
| 1 | [gog](https://clawhub.ai/skills/gog) | 77.7K | 607 | Google Workspace 全家桶 (Gmail/Calendar/Drive/Docs/Sheets/Contacts) |
| 2 | [notion](https://clawhub.ai/skills/notion) | 35.9K | 131 | Notion API 页面/数据库/块管理 |
| 3 | [api-gateway](https://clawhub.ai/skills/api-gateway) | 31.2K | 149 | 100+ API 统一网关 (OAuth 管理) |
| 4 | [trello](https://clawhub.ai/skills/trello) | 18.0K | 86 | Trello 看板/列表/卡片管理 |
| 5 | [stripe-api](https://clawhub.ai/skills/stripe-api) | 17.5K | 22 | Stripe 支付/订阅/发票管理 |
| 6 | [shopify](https://clawhub.ai/skills/shopify) | 16.5K | 2 | Shopify 电商集成 (维护中) |
| 7 | [xero](https://clawhub.ai/skills/xero) | 16.4K | 8 | Xero 财务 API (联系人/发票/报表) |

---

### 🤖 6. Agent 能力增强 (Agent Enhancement)

| # | Skill | 下载量 | ⭐ | 说明 |
|---|-------|--------|-----|------|
| 1 | [free-ride](https://clawhub.ai/skills/free-ride) | 26.1K | 190 | OpenRouter 免费模型管理，自动排名/降级 |
| 2 | [gemini](https://clawhub.ai/skills/gemini) | 17.0K | 35 | Gemini CLI 问答/摘要/生成 |
| 3 | [desktop-control](https://clawhub.ai/skills/desktop-control) | 16.3K | 125 | 桌面自动化 (鼠标/键盘/屏幕控制) |

---

### 🌤️ 7. 生活与工具 (Lifestyle & Utility)

| # | Skill | 下载量 | ⭐ | 说明 |
|---|-------|--------|-----|------|
| 1 | [weather](https://clawhub.ai/skills/weather) | 52.2K | 185 | 天气查询与预报 (无需 API Key) |
| 2 | [polymarketodds](https://clawhub.ai/skills/polymarketodds) | 50.7K | 128 | Polymarket 预测市场查询 (赔率/趋势/告警) |
| 3 | [sonoscli](https://clawhub.ai/skills/sonoscli) | 44.6K | 30 | Sonos 音箱控制 (发现/播放/音量/分组) |
| 4 | [stock-analysis](https://clawhub.ai/skills/stock-analysis) | 20.8K | 111 | 股票/加密货币分析 (Yahoo Finance) |
| 5 | [blogwatcher](https://clawhub.ai/skills/blogwatcher) | 18.8K | 25 | RSS/Atom 博客监控更新 |
| 6 | [lnbits-with-qrcode](https://clawhub.ai/skills/lnbits-with-qrcode) | 19.2K | 4 | LNbits 闪电网络钱包管理 |
| 7 | [automation-workflows](https://clawhub.ai/skills/automation-workflows) | 19.4K | 82 | 自动化工作流设计 (Zapier/Make/n8n) |

---

## 二、重点推荐 (近期上手清单)

以下 10 个 Skill 经过筛选，覆盖开发全链路：

| Skill | 类别 | 下载量 | 安装命令 | 一句话 |
|-------|------|--------|----------|--------|
| [Self-Improving Agent](https://clawhub.ai/skills/self-improving-agent) | 记忆 | 87.6K | [安装文档](skills/03-dev-memory/self-improving-agent.md) | Agent 自学习，跨会话记住错误和修正 |
| [Find Skills](https://clawhub.ai/skills/find-skills) | 搜索 | 72.3K | [安装文档](skills/02-search/find-skills.md) | 你说需求，它帮你找并装好 Skill |
| [Skill Vetter](https://clawhub.ai/skills/skill-vetter) | 安全 | 12.3K | [安装文档](skills/01-security/skill-vetter.md) | 安装前审计 Skill，检测 20+ 危险信号 |
| [Focus Mode](https://clawhub.ai/skills/focus-mode) | 效率 | 新兴 | 见 [docs/skills/](skills/) | 专注模式，屏蔽干扰，深度工作 |
| [Agent Browser](https://clawhub.ai/skills/agent-browser) | 浏览器 | 61.1K | [安装文档](skills/02-search/agent-browser.md) | Rust 无头浏览器自动化 (点击/输入/截图) |
| [AI Daily Briefing](https://clawhub.ai/skills/ai-daily-briefing) | 效率 | 新兴 | [安装文档](skills/07-productivity/ai-daily-briefing.md) | 每日晨报：任务/日历/优先级一览 |
| [Multi Search Engine](https://clawhub.ai/skills/multi-search-engine) | 搜索 | 13.7K | [安装文档](skills/02-search/multi-search-engine.md) | 17 搜索引擎集成 (8 国内 + 9 国际) |
| [YouTube Ultimate](https://clawhub.ai/skills/youtube-ultimate) | 内容 | 新兴 | ❌ 不适合国内 | YouTube 被墙，不建议安装 |
| [OpenClaw Feeds](https://clawhub.ai/skills/openclaw-feeds) | 信息 | 新兴 | 见 [docs/skills/](skills/) | RSS/Twitter/HN/Reddit 信息流聚合 |
| [Reddit Search](https://clawhub.ai/skills/reddit-search) | 搜索 | 新兴 | ❌ 不适合国内 | Reddit 被墙，不建议安装 |

> 💡 **建议安装顺序**: Skill Vetter → Find Skills → Self-Improving Agent → Agent Browser → Multi Search Engine → AI Daily Briefing → Focus Mode → OpenClaw Feeds → YouTube Ultimate → Reddit Search
>
> 先装 `skill-vetter` 做安全审计，再装其他 Skill 时用它检查一遍。

---

## 二B. 生产力必备 TOP 10 (用户精选)

| # | Skill | ClawHub 名 | 下载量 | 安装方式 | 一句话 |
|---|-------|------------|--------|----------|--------|
| 1 | 🥇 Skill Vet | `skill-vetter` | 12.3K | [安装文档](skills/01-security/skill-vetter.md) | 安全守门员，安装前自动扫描恶意行为 |
| 2 | 🔍 Find Skills | `find-skills` | 72.3K | [安装文档](skills/02-search/find-skills.md) | 打字描述需求，自动搜索并安装 Skill |
| 3 | 🧠 Memory Setup | `elite-longterm-memory` | 19.3K | [安装文档](skills/03-dev-memory/elite-longterm-memory.md) | 解决 AI 鱼的记忆，记住使用习惯 |
| 4 | 📝 Self-Improving | `self-improving-agent` | 87.6K | [安装文档](skills/03-dev-memory/self-improving-agent.md) | 纠错后自动记录，下次不再犯 |
| 5 | 📄 Summarize | `summarize` | 66.4K | [安装文档](skills/04-document/summarize.md) | 链接/PDF/视频几秒提炼核心摘要 |
| 6 | 🌐 Web Content | `agent-browser` | 61.1K | [安装文档](skills/02-search/agent-browser.md) | 绕过限制抓取网页，输出干净 Markdown |
| 7 | ✏️ NanoPDF | `nano-pdf` | 32.9K | [安装文档](skills/04-document/nano-pdf.md) | 自然语言编辑 PDF，告别 Adobe |
| 8 | 🗣️ Humanizer | `humanizer` | 28.6K | [安装文档](skills/04-document/humanizer.md) | 去 AI 味，让文字更像真人说话 |
| 9 | 🎨 Nano Banana Pro | `nano-banana-pro` | 31.6K | 见 [docs/skills/](skills/) | 对话框直接生图/改图，支持 4K |
| 10 | ⏰ Proactive Agent | `proactive-agent` | 49.2K | 见 [docs/skills/](skills/) | AI 从被动应答变为主动服务 |

> 💡 以上 10 个 Skill 与本清单其他章节有重叠，此处按 **日常使用场景** 重新排列。

---

## 二C. 补充推荐 (按需安装)

| # | Skill | ClawHub/来源 | 类别 | 安装方式 | 说明 |
|---|-------|-------------|------|----------|------|
| 1 | [Anthropic Docs Suite](https://clawhub.ai/skills/anthropic-docs-skill) | Anthropic 官方 | 文档 | [安装文档](skills/04-document/anthropic-docs-skill.md) | AI 读写 Word/PPT/Excel/PDF，论文速读 + PPT 生成 |
| 2 | [UI/UX Pro Max](https://clawhub.ai/skills/ui-ux-pro-max-skill) | ClawHub | 设计 | [安装文档](skills/06-design/ui-ux-pro-max-skill.md) | UI 设计智库，配色/字体/组件/交互规范，输出高质感设计 |
| 3 | [Humanizer ZH](https://clawhub.ai/skills/humanizer-zh) | ClawHub | 写作 | [安装文档](skills/04-document/humanizer-zh.md) | 中文去 AI 痕迹写作，4 类 24 项扫描优化，更像真人表达 |
| 4 | [Remotion Dev](https://clawhub.ai/skills/remotion-dev) | ClawHub | 视频 | [安装文档](skills/06-design/remotion-dev.md) | 代码生成产品发布动画视频，文字排版/转场/自定义渲染 |
| 5 | [Research Skills](https://clawhub.ai/skills/research-skills) | ClawHub | 搜索 | [安装文档](skills/08-research/research-skills.md) | 多源研究工作流 (论文/文档/网页) |
| 6 | [NotebookLM Skill](https://clawhub.ai/skills/notebooklm-skill) | ClawHub | 知识 | ❌ 不适合国内 | Google NotebookLM 被墙 |
| 7 | [CSV Data Summarizer](https://clawhub.ai/skills/csv-data-summarizer) | ClawHub | 数据 | [安装文档](skills/09-tools/csv-data-summarizer.md) | CSV 文件智能分析与摘要 |
| 8 | [File Organizer](https://clawhub.ai/skills/file-organizer) | ClawHub | 工具 | [安装文档](skills/09-tools/file-organizer.md) | 文件自动分类整理 |
| 9 | [Video Downloader](https://clawhub.ai/skills/video-downloader) | ClawHub | 媒体 | [安装文档](skills/05-media/video-downloader.md) | 视频下载 (YouTube/B站/抖音等) |
| 10 | [AI Content Operator](https://clawhub.ai/skills/ai-content-operator) | ClawHub | 内容 | 见 [docs/skills/](skills/) | AI 内容生产运营助手 |
| 11 | [Awesome Claude Skills](https://clawhub.ai/skills/awesome-claude-skill) | ClawHub | 工具 | 见 [docs/skills/](skills/) | Claude 精选 Skill 合集导航 |
| 12 | [Docx Skill](https://clawhub.ai/skills/docx-skill) | ClawHub | 文档 | 见 [docs/skills/](skills/) | Word 文档读写/生成/编辑 |

> ⚠️ **已去重**：Skill Creator / Agent Browser / Find Skills / Superpowers / Humanizer (英文版) 已在其他章节，此处不重复。

---

## 二D. 不适合中国大陆使用 (需梯子或服务不可达)

以下 Skill 依赖被墙或国内无法访问的服务，**不建议安装**：

| Skill | 原因 | 替代方案 |
|-------|------|----------|
| `tavily-search` | 需海外 API Key，国内延迟高 | `baidu-search` / `multi-search-engine` |
| `brave-search` | 需海外 API Key | `baidu-search` / `multi-search-engine` |
| `gog` (Google Workspace) | Google 服务被墙 | 无直接替代，可用 `notion` |
| `gmail` | Gmail 被墙 | `himalaya` / `imap-smtp-email` (配国内邮箱) |
| `gemini` | Google API 被墙 | 直接用 OpenCode 内置模型 |
| `youtube-watcher` | YouTube 被墙 | `video-downloader` (B站/抖音) |
| `youtube-api-skill` | YouTube API 被墙 | 同上 |
| `youtube-ultimate` | YouTube 被墙 | 同上 |
| `reddit-search` | Reddit 被墙 | `blogwatcher` (RSS 订阅替代) |
| `whatsapp-business` | WhatsApp 被墙 | 无直接替代 |
| `polymarketodds` | Polymarket 被墙 | 无直接替代 |
| `sonoscli` | 依赖 Sonos 硬件 (国内少见) | 无 |
| `notebooklm-skill` | Google NotebookLM 被墙 | `obsidian` + `research-skills` |
| `slack` | 国内团队不用 Slack | 无 |
| `free-ride` | OpenRouter 国内不稳定 | 直接用 OpenCode 内置模型 |
| `lnbits-with-qrcode` | 闪电网络，国内无场景 | 无 |

> 💡 **替代原则**：搜索用 `baidu-search`，邮箱用 `imap-smtp-email`，知识库用 `obsidian`，文档用 `anthropic-docs-skill`。

---

## 三、Super Powers 已安装 (内置 15 Skill)

| Skill | 用途 |
|-------|------|
| brainstorming | 需求澄清、方案设计 |
| writing-plans | 生成实施计划 |
| executing-plans | 按计划执行开发 |
| test-driven-development | 红绿 TDD 开发 |
| systematic-debugging | 系统性调试定位 |
| dispatching-parallel-agents | 多 Agent 并行任务 |
| subagent-driven-development | 子 Agent 驱动开发 |
| requesting-code-review | 请求代码审查 |
| receiving-code-review | 接收代码审查反馈 |
| verification-before-completion | 完成前验证 |
| finishing-a-development-branch | 分支合并/清理 |
| using-git-worktrees | Git worktree 隔离开发 |
| writing-skills | 自定义 Skill 打包 |
| using-superpowers | 技能使用指南 |

---

## 四、推荐自定义开发 (Embedded/Linux 专用)

针对你的技术栈 (Linux 内核/效率工具/防护网)，建议创建以下 Skill：

| Skill 名称 | 用途 | 优先级 |
|------------|------|--------|
| kernel-module-debugging | 内核模块调试、dmesg 分析、Oops/panic 处理 | ⭐⭐⭐ |
| cross-compilation | 交叉编译环境管理、Yocto/Buildroot 集成 | ⭐⭐⭐ |
| device-driver-development | 驱动开发模板、设备树分析 | ⭐⭐ |
| performance-profiling | perf/ftrace 使用、内存泄漏检测、实时性分析 | ⭐⭐⭐ |
| security-hardening | 内核安全加固、漏洞扫描、权限最小化 | ⭐⭐ |
| rust-embedded | Rust 嵌入式开发工作流 (no_std/async HAL) | ⭐⭐ |
| bpf-development | eBPF 程序开发、libbpf/bcc 工作流 | ⭐⭐⭐ |

---

## 五、安装优先级建议 (含重点推荐)

| 阶段 | Skill | 来源 | 说明 |
|------|-------|------|------|
| P0 已装 | Superpowers (15个) | git plugin | 核心开发工作流 |
| P1 必装 | skill-vetter | ClawHub | 安装其他 Skill 前先审计 |
| P1 必装 | find-skills | ClawHub | 智能发现可用 Skills |
| P1 必装 | self-improving-agent | ClawHub | Agent 自学习记忆 |
| P1 推荐 | summarize | ClawHub | 文档/网页/视频摘要 |
| P1 推荐 | agent-browser | ClawHub | 浏览器自动化 |
| P1 推荐 | playwright-mcp | ClawHub | 浏览器自动化 (备选) |
| P1 推荐 | skill-creator | ClawHub | 自定义 Skill 打包 |
| P1 推荐 | humanizer | ClawHub | 去 AI 痕迹写作 (英文版) |
| P1 推荐 | humanizer-zh | ClawHub | 去 AI 痕迹写作 (中文版) |
| P1 推荐 | anthropic-docs-skill | Anthropic 官方 | Word/PPT/Excel/PDF 四件套 |
| P2 推荐 | nano-pdf | ClawHub | PDF 编辑 |
| P2 推荐 | nano-banana-pro | ClawHub | AI 生图/改图 |
| P2 推荐 | proactive-agent | ClawHub | 主动式 Agent |
| P2 推荐 | tavily-search | ClawHub | AI 搜索 |
| P2 推荐 | github | ClawHub | GitHub 工作流 |
| P2 推荐 | multi-search-engine | ClawHub | 多引擎搜索 |
| P2 推荐 | ai-daily-briefing | ClawHub | 每日晨报 |
| P2 推荐 | elite-longterm-memory | ClawHub | 长期记忆 |
| P3 可选 | notebooklm-skill | ClawHub | NotebookLM 知识库 |
| P3 可选 | remotion-dev | ClawHub | 代码生成动画视频 |
| P3 可选 | ui-ux-pro-max-skill | ClawHub | UI 设计 |
| P3 可选 | csv-data-summarizer | ClawHub | CSV 数据分析 |
| P3 可选 | video-downloader | ClawHub | 视频下载 |
| P3 可选 | ai-content-operator | ClawHub | AI 内容运营 |
| P3 可选 | docx-skill | ClawHub | Word 文档处理 |
| P3 可选 | research-skills | ClawHub | 研究工作流 |
| P3 可选 | file-organizer | ClawHub | 文件整理 |
| P3 可选 | gog | ClawHub | Google Workspace |
| P3 可选 | notion | ClawHub | 笔记管理 |
| P3 可选 | api-gateway | ClawHub | 多 API 统一入口 |
| P4 创建 | kernel-module-debugging | 自定义 | 内核调试 |
| P4 创建 | bpf-development | 自定义 | eBPF 开发 |
| P4 创建 | performance-profiling | 自定义 | 性能分析 |
| P4 创建 | kernel-module-debugging | 自定义 | 内核调试 |
| P4 创建 | bpf-development | 自定义 | eBPF 开发 |
| P4 创建 | performance-profiling | 自定义 | 性能分析 |

---

## 六、自定义 Skill 快速参考

```
~/.config/opencode/skills/
├── brainstorming/          (Superpowers)
├── systematic-debugging/   (Superpowers)
├── writing-plans/          (Superpowers)
└── kernel-debug/           (自定义)
    └── SKILL.md
```

**SKILL.md 模板：**
```markdown
---
name: skill-name
description: Use when [触发条件] - [功能描述]
---

# Skill Title

[工作流内容]
```

---

## 参考 (References)

| 来源 | 链接 | 说明 |
|------|------|------|
| 🎬 什么是大模型 Skill | https://www.bilibili.com/video/BV1dz6oBWEWx/ | 10 分钟入门，什么是 Skill、怎么用、底层原理 (隔壁的程序员老王) |
| ClawHub Skills 排行 | https://clawhub.ai/skills?sort=downloads | TOP 50 数据来源 |
| Top ClawHub Skills API | https://topclawhubskills.com/api/top-downloads?limit=50 | 实时下载量 API |
| Superpowers (GitHub) | https://github.com/obra/superpowers | 已安装，15 个内置 Skill |
| oh-my-opencode | https://www.npmjs.com/package/oh-my-opencode | Oracle + Librarian Agent |
| ClawHub 安全审计 | https://clawhub.ai/skills/skill-vetter | Skill 安装前审计 |
| OpenClaw Skills 推荐 | https://help.apiyi.com/en/openclaw-skill-recommendations-2026-en.html | 社区推荐 TOP 10 |
| Firecrawl 最佳 Skills | https://www.firecrawl.dev/blog/openclaw-skills | 16 个最佳 Skills 评测 |
| ClawHub Skills Lib | https://www.clawhub-skills.com/blog | Skill 使用教程 |
| LobeHub Skills | https://lobehub.com/skills | 100K+ Skills 市场 |
| **本地 Skill 文档** | [docs/skills/](./skills/) | 30 个可用 Skill 详细使用指南 |
