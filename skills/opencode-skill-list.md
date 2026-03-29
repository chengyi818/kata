# OpenCode Skill 清单

> **适用人群**: Linux 嵌入式底层程序员 (C/Rust/Python, 内核/效率工具/防护网)
>
> **更新时间**: 2026-03-29

---

## 筛选标准

1. ✅ 是不是真的能装进 opencode
2. ✅ 会不会高频用到
3. ✅ 能不能明显提升结果，而不只是看起来很酷

---

## 什么是 Skill？

> 🎬 视频入门：[什么是大模型Skill 10分钟弄懂](https://www.bilibili.com/video/BV1dz6oBWEWx/) (隔壁的程序员老王)

### 一句话理解

**Skill = 高级提示词 + 模块化能力 + 可复用 + 可控**

### Skill 本质

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

---

## 一、学习路径（按优先级）

### 第一梯队：必须掌握（高频 + 明显提升效率）

| 顺序 | Skill | 适用场景 | 学习时间 | 安装命令 |
|:----:|-------|----------|:--------:|----------|
| 1 | **skill-vetter** | 装其他 skill 前的安全审计，防止恶意代码 | 5min | ClawHub |
| 2 | **find-skills** | 发现并安装需要的 skill，解决"不知道有什么" | 10min | ClawHub |
| 3 | **tmux** | 远程开发板调试、交叉编译长任务、内核日志观察 | 15min | `npx skills add steipete/clawdis@tmux -g -y` |
| 4 | **summarize** | 读内核文档、驱动文档、RFC、patch 描述 | 10min | ClawHub |
| 5 | **planning-with-files** | 长任务规划持久化，上下文压缩不丢失 | 10min | GitHub |
| 6 | **self-improving-agent** | 跨会话记住调试经验、编译错误修正 | 15min | ClawHub |

**为什么这 6 个必学？**
- `skill-vetter` + `find-skills`：工具准备，装其他 skill 的前置条件
- `tmux`：嵌入式/远程开发的核心能力，没有它无法跑长任务
- `summarize`：信息压缩能力，读文档/补丁的核心
- `planning-with-files`：长任务不丢失状态，避免"做到一半忘了在干嘛"
- `self-improving-agent`：跨会话记忆，调试过的错误不再犯

---

### 第二梯队：开发核心（显著提升代码质量）

| 顺序 | Skill | 适用场景 | 学习时间 | 来源 |
|:----:|-------|----------|:--------:|------|
| 7 | **systematic-debugging** | 内核 Oops/panic 分析、驱动调试 | 内置 | Superpowers |
| 8 | **code-review** | 补丁审查、内核补丁检查 | 20min | Anthropic 官方 |
| 9 | **code-simplifier** | 驱动代码简化、合并重复逻辑 | 15min | Anthropic 官方 |
| 10 | **code-refactoring** | 驱动重构、代码结构调整 | 20min | `npx skills add supercent-io/skills-template --skill code-refactoring -g -y` |
| 11 | **changelog-maintenance** | commit 规范、changelog 生成 | 10min | `npx skills add supercent-io/skills-template@changelog-maintenance -g -y` |
| 12 | **trailofbits-security** | CodeQL/Semgrep 静态分析，漏洞检测 | 30min | GitHub |

**适用场景**：
- 内核补丁提交前审查
- 驱动代码重构简化
- 安全漏洞静态分析
- commit message 规范化

---

### 第三梯队：效率增强（中频使用）

| 顺序 | Skill | 适用场景 | 学习时间 | 来源 |
|:----:|-------|----------|:--------:|------|
| 13 | **github** | PR/issue 管理、内核补丁提交 | 15min | ClawHub |
| 14 | **ralph-loop** | 强制完成复杂任务，避免半途而废 | 10min | 社区 |
| 15 | **mcp-builder** | 自定义 MCP Server（如连接开发板） | 30min | Anthropic 官方 |
| 16 | **markitdown** | PDF/PPT/Word/Excel/HTML → Markdown 转换 | 5min | `pip install markitdown[all]` |
| 17 | **dev-agent-skills** | Git/GitHub 工作流完整支持 | 15min | GitHub |
| 18 | **next-ai-draw-io** | AI 驱动架构图/流程图生成 | 10min | MCP Server |

> 详细信息见 [skills/31-next-ai-draw-io/](skills/31-next-ai-draw-io/)

---

### 第四梯队：按需安装

| Skill | 适用场景 | 建议时机 |
|-------|----------|----------|
| skill-creator | 沉淀内核调试工作流 | 学完核心 skill 后再学 |
| ontology | 结构化记忆知识图谱 | 长期使用后再考虑 |
| agent-browser | 访问厂商文档、下载驱动 | 偶尔需要时再装 |
| obsidian | 知识库管理笔记 | 有笔记习惯再考虑 |
| proactive-agent | 主动预测需求执行 | 有需求再装 |
| deer-flow | ByteDance 长时程 SuperAgent 框架（独立运行，MCP 集成） | 复杂多步骤任务时再考虑 |

> 详细信息见 [skills/32-deer-flow/](skills/32-deer-flow/)

---

## 二、Superpowers 已安装（内置 15 Skill）

> 这些 skill 已内置，无需安装，直接可用。

| Skill | 用途 | 嵌入式场景 |
|-------|------|------------|
| brainstorming | 需求澄清、方案设计 | 驱动架构设计 |
| writing-plans | 生成实施计划 | 开发任务分解 |
| executing-plans | 按计划执行开发 | 自动执行计划 |
| test-driven-development | 红绿 TDD 开发 | 驱动单元测试 |
| **systematic-debugging** | **系统性调试定位** | **内核 Oops 分析** ⭐ |
| dispatching-parallel-agents | 多 Agent 并行任务 | 多模块并行开发 |
| subagent-driven-development | 子 Agent 驱动开发 | 复杂任务分解 |
| requesting-code-review | 请求代码审查 | 补丁提交前自查 |
| receiving-code-review | 接收代码审查反馈 | 处理 review 意见 |
| verification-before-completion | 完成前验证 | 确保任务完成 |
| finishing-a-development-branch | 分支合并/清理 | 补丁合并流程 |
| using-git-worktrees | Git worktree 隔离开发 | 多版本并行开发 |
| writing-skills | 自定义 Skill 打包 | 沉淀工作流 |

---

## 三、暂时不需要浪费精力的 Skills

### ❌ 前端/设计类（完全不适用）

| Skill | 原因 |
|-------|------|
| frontend-design | React/Tailwind 前端设计 |
| ui-ux-pro-max-skill | UI/UX 设计，67种风格161套配色 |
| webapp-testing | Playwright 前端测试 |
| web-artifacts-builder | HTML artifacts 构建 |
| canvas-design | 视觉艺术设计 |
| algorithmic-art | p5.js 生成艺术 |
| frontend-slides | HTML 演示文稿 |
| shadcn/ui skills | React 组件 |

### ❌ 媒体/内容类（低频）

| Skill | 原因 |
|-------|------|
| remotion-dev | 代码生成动画视频 |
| video-downloader | 视频下载 |
| video-frames | 视频帧提取 |
| ai-content-operator | AI 内容运营 |
| nano-banana-pro | AI 生图/改图 |

### ❌ 通讯/社交类（低频）

| Skill | 原因 |
|-------|------|
| slack | 团队不用 Slack |
| gmail / outlook-api | 邮件 API |
| whatsapp-business | WhatsApp |
| youtube-* | YouTube 被墙 |

### ❌ 生活/娱乐类

| Skill | 原因 |
|-------|------|
| weather | 偶尔用，不是核心 |
| stock-analysis | 股票分析 |
| polymarketodds | 预测市场 |
| sonoscli | Sonos 音箱 |

### ❌ 国内受限服务

| Skill | 原因 | 替代方案 |
|-------|------|----------|
| tavily-search | 海外 API 延迟高 | baidu-search |
| brave-search | 海外 API | baidu-search |
| gog (Google Workspace) | Google 被墙 | notion |
| gemini | Google API 被墙 | 内置模型 |
| notebooklm-skill | NotebookLM 被墙 | obsidian |
| free-ride | OpenRouter 国内不稳定 | 内置模型 |

---

## 四、推荐自定义开发（Embedded/Linux 专用）

针对你的技术栈，建议创建以下 Skill：

| Skill 名称 | 用途 | 优先级 | 场景 |
|------------|------|:------:|------|
| kernel-module-debugging | 内核模块调试、dmesg 分析、Oops/panic 处理 | ⭐⭐⭐ | 驱动开发调试 |
| cross-compilation | 交叉编译环境管理、Yocto/Buildroot 集成 | ⭐⭐⭐ | 嵌入式编译 |
| performance-profiling | perf/ftrace 使用、内存泄漏检测、实时性分析 | ⭐⭐⭐ | 性能优化 |
| bpf-development | eBPF 程序开发、libbpf/bcc 工作流 | ⭐⭐⭐ | 内核观测 |
| device-driver-development | 驱动开发模板、设备树分析 | ⭐⭐ | 驱动开发 |
| security-hardening | 内核安全加固、漏洞扫描、权限最小化 | ⭐⭐ | 安全加固 |
| rust-embedded | Rust 嵌入式开发工作流 (no_std/async HAL) | ⭐⭐ | Rust 嵌入式 |

**创建方法**：使用 `skill-creator` 或手动创建 `~/.config/opencode/skills/<skill-name>/SKILL.md`

---

## 五、学习计划

```
Week 1: 第一梯队（安全 + 基础能力）
├── Day 1-2: skill-vetter + find-skills（工具准备）
├── Day 3-4: tmux（远程开发必备）
└── Day 5-6: summarize + planning-with-files（信息处理）

Week 2: 第二梯队（代码质量）
├── systematic-debugging（Superpowers 已内置）
├── code-review + code-simplifier + code-refactoring
├── changelog-maintenance
└── trailofbits-security（安全分析）

Week 3: 第三梯队（效率增强）
├── github + ralph-loop
└── mcp-builder（如需自定义 MCP）

Week 4+: 按需补充
├── skill-creator（开始沉淀自己的工作流）
└── 创建嵌入式专用 skill
```

---

## 六、Skill 目录结构

```
~/.config/opencode/skills/
├── brainstorming/          (Superpowers)
├── systematic-debugging/   (Superpowers)
├── writing-plans/          (Superpowers)
├── code-refactoring/       (已安装)
└── kernel-debug/           (自定义)
    └── SKILL.md
```

---

## 数据源与参考

### 数据来源

| 来源 | 链接 | 说明 |
|------|------|------|
| ClawHub | https://clawhub.ai/skills?sort=downloads | TOP 50 下载排名 |
| skills.sh | https://skills.sh/ | Skill 安装工具 (`npx skills add`) |
| Awesome Claude Skills | https://github.com/travisvn/awesome-claude-skills | 社区精选清单 |
| Anthropic 官方 | https://github.com/anthropics/skills | 官方 Skills 仓库 |
| Superpowers | https://github.com/obra/superpowers | 已安装，15 个内置 Skill |
| Trail of Bits | https://github.com/trailofbits/skills | 安全研究 Skills |

### 学习资源

| 资源 | 链接 | 说明 |
|------|------|------|
| 🎬 视频入门 | https://www.bilibili.com/video/BV1dz6oBWEWx/ | 10分钟弄懂 Skill |
| 🎬 封装教程 | https://www.bilibili.com/video/BV1i2wbzhEL9/ | 保姆级 Agent Skill 封装教程（PM刘搞定） |
| OpenClaw 推荐 | https://help.apiyi.com/en/openclaw-skill-recommendations-2026-en.html | 社区推荐 TOP 10 |
| Firecrawl 评测 | https://www.firecrawl.dev/blog/openclaw-skills | 16 个最佳 Skills 评测 |

---

## 一句话总结

**核心原则**：先装能帮你**干活**的（tmux、summarize、code-review），再装帮你**提质**的（code-simplifier、trailofbits-security），最后装帮你**扩展**的（mcp-builder、skill-creator）。

**避坑原则**：前端/设计/媒体/社交类 skill 对嵌入式开发几乎没有价值，不要被"看起来很酷"诱惑。

---

## 七、低优先级 Skills 完整列表（按需查阅）

> 以下 Skills 对嵌入式开发优先级较低，但保留完整列表供查阅。

### 开发工具类

| Skill | 说明 | 来源 |
|-------|------|------|
| byterover | Agent 知识管理，项目模式存储检索 | ClawHub |
| elite-longterm-memory | 长期记忆系统 (WAL + vector search + git-notes) | ClawHub |
| mcporter | MCP 服务器工具调用管理 | ClawHub |
| clawddocs | Clawdbot 文档专家，配置代码速查 | ClawHub |
| auto-updater | 自动更新 Agent 和已装 Skills | ClawHub |
| model-usage | 模型用量/成本统计 | ClawHub |
| ffuf-web-fuzzing | Web 模糊测试渗透测试 | GitHub |
| claude-scientific-skills | 科学计算库与数据库操作技能 | GitHub |

### 搜索与信息获取类

| Skill | 说明 | 来源 |
|-------|------|------|
| agent-browser | Rust 无头浏览器自动化 (点击/输入/截图) | ClawHub |
| browser-use | 浏览器交互自动化 (测试/表单/数据提取) | ClawHub |
| playwright-mcp | Playwright MCP 浏览器自动化 | ClawHub |
| playwright-scraper-skill | Playwright 反爬虫抓取 | ClawHub |
| multi-search-engine | 17 搜索引擎集成 (8 国内 + 9 国际) | ClawHub |
| baidu-search | 百度 AI 搜索引擎集成 | ClawHub |

### 文档与内容处理类

| Skill | 说明 | 来源 |
|-------|------|------|
| humanizer | 去 AI 痕迹写作，让文字更自然 | ClawHub |
| humanizer-zh | 中文去 AI 痕迹写作 | ClawHub |
| humanize-ai-text | AI 文本人性化改写，绕过检测器 | ClawHub |
| nano-pdf | 自然语言编辑 PDF | ClawHub |
| openai-whisper | 本地语音转文字 (无需 API Key) | ClawHub |
| anthropic-docs-skill | AI 读写 Word/PPT/Excel/PDF | ClawHub |
| docx-skill | Word 文档读写/生成/编辑 | ClawHub |

### Anthropic 官方文档 Skills

| Skill | 说明 | 安装 |
|-------|------|------|
| docx | Word 文档，支持修订/批注/格式保留 | `/plugin install docx` |
| pdf | PDF 工具包，提取/创建/合并/拆分/表单 | `/plugin install pdf` |
| pptx | PPT 生成/编辑，支持母版/模板/图表 | `/plugin install pptx` |
| xlsx | Excel 表格，公式/格式/数据分析/可视化 | `/plugin install xlsx` |

### 通讯与社交类

| Skill | 说明 | 来源 |
|-------|------|------|
| himalaya | CLI 邮件管理 (IMAP/SMTP，多账户) | ClawHub |
| imap-smtp-email | IMAP/SMTP 邮件收发 (含附件) | ClawHub |

### 云服务与平台集成类

| Skill | 说明 | 来源 |
|-------|------|------|
| notion | Notion API 页面/数据库/块管理 | ClawHub |
| api-gateway | 100+ API 统一网关 (OAuth 管理) | ClawHub |
| trello | Trello 看板/列表/卡片管理 | ClawHub |
| stripe-api | Stripe 支付/订阅/发票管理 | ClawHub |
| shopify | Shopify 电商集成 | ClawHub |
| xero | Xero 财务 API | ClawHub |

### Agent 能力增强类

| Skill | 说明 | 来源 |
|-------|------|------|
| desktop-control | 桌面自动化 (鼠标/键盘/屏幕控制) | ClawHub |

### 生活与工具类

| Skill | 说明 | 来源 |
|-------|------|------|
| blogwatcher | RSS/Atom 博客监控更新 | ClawHub |
| automation-workflows | 自动化工作流设计 (Zapier/Make/n8n) | ClawHub |
| csv-data-summarizer | CSV 文件智能分析与摘要 | ClawHub |
| file-organizer | 文件自动分类整理 | ClawHub |
| research-skills | 多源研究工作流 (论文/文档/网页) | ClawHub |

### 更多社区 Skills

| Skill | 说明 | 来源 |
|-------|------|------|
| ios-simulator-skill | iOS app building, navigation, and testing | GitHub |
| claude-d3js-skill | Visualizations in d3.js | GitHub |
| web-asset-generator | Generates web assets like favicons, app icons | GitHub |
| loki-mode | Multi-agent autonomous startup system (37 agents) | GitHub |
| awesome-claude-skill | Claude 精选 Skill 合集导航 | ClawHub |