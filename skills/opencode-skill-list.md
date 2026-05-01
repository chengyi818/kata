# OpenCode Skill 清单

> **适用人群**: Linux 嵌入式底层程序员 (C/Rust/Python, 内核/效率工具/防护网)
>
> **更新时间**: 2026-04-25

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

### 为什么需要 Skill？

| 方式 | 做法 | 问题 |
|------|------|------|
| ❌ 不用 Skill | 每次手动告诉 AI 怎么做 | 重复、容易遗漏、结果不稳定 |
| ✅ 使用 Skill | 按需加载对应的 Skill | 标准化、可复用、结果可控 |

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

## 本仓库目录结构

```
skills/
├── opencode-skill-list.md     # 📋 完整清单（TOP 50 Skill）
│
├── 01-skill-vetter/           # 🔒 安全审计（第 1 个必学）
├── 02-find-skills/            # 🔍 发现 Skill（第 2 个必学）
├── 03-oh-my-opencode/         # 🤖 多 Agent 编排（第 3 个必学）
├── 04-tmux/                   # 💻 终端复用
├── 05-summarize/              # 📄 文档摘要
├── 06-caveman/                # ✂️ 代码极简主义
├── ...
└── skills-repo/               # 第三方 Skill 仓库
```

### 编号规则

- `01-xx` 到 `07-xx`：第一梯队（必学）
- `08-xx` 到 `14-xx`：第二梯队（代码质量）
- `15-xx` 到 `20-xx`：第三梯队（效率增强）
- `21-xx` 到 `26-xx`：第四梯队（按需）
- `27-xx` 起：Superpowers 内置 + 补充

---

## 一、学习路径（按优先级）

### 第一梯队：必须掌握（高频 + 明显提升效率）

> ⚠️ **前置条件**：`skill-vetter` 已作为项目级 skill 预装，安装任何新 skill 前务必先用它审计。无需单独学习，自动生效。

| 顺序 | Skill | 适用场景 | 学习时间 | 安装命令 |
|:----:|-------|----------|:--------:|----------|
| 1 | **find-skills** | 发现并安装需要的 skill，解决"不知道有什么" | 10min | `npx skills add vercel-labs/skills@find-skills -g -y` |
| 2 | **oh-my-opencode** | OpenCode 多 agent 编排、ultrawork 模式、后台任务 | 15min | 内置插件 |
| 3 | **tmux** | 远程开发板调试、交叉编译长任务、内核日志观察 | 15min | `npx skills add steipete/clawdis@tmux -g -y` |
| 4 | **summarize** | 读内核文档、驱动文档、RFC、patch 描述 | 10min | ClawHub |
| 5 | **caveman** | 代码极简主义，精简驱动代码/内核模块 | 15min | `npx skills add juliusbrussee/caveman@caveman -g -y` |

**为什么这 5 个必学？**
- `find-skills`：发现 skill 的入口，装其他 skill 的前置
- `oh-my-opencode`：OpenCode 核心编排能力，多 agent 协作/ultrawork/后台任务管理
- `tmux`：嵌入式/远程开发的核心能力，没有它无法跑长任务
- `summarize`：信息压缩能力，读文档/补丁的核心
- `caveman`：代码极简主义，commit/review/compress/help 全家桶，80.5K 安装量

**已移除及原因：**
- ~~`skill-vetter`~~：不在 skills.sh TOP 排行中，但已作为项目级 skill 预装，无需学习，安装新 skill 前自动审计即可
- ~~`self-improving-agent`~~：排名跌至 48（25.8K），跨会话记忆需求已被 oh-my-opencode 的 session 持久化 + Superpowers 的 writing-plans 组合替代
- ~~`planning-with-files`~~：不在 TOP50，功能已被 Superpowers 内置的 writing-plans + executing-plans 组合完整替代
- ~~`openclaw-secure-linux-cloud`~~：与嵌入式底层开发场景不匹配

---

### 第二梯队：开发核心（显著提升代码质量）

| 顺序 | Skill | 适用场景 | 学习时间 | 来源 |
|:----:|-------|----------|:--------:|------|
| 8 | **systematic-debugging** | 内核 Oops/panic 分析、驱动调试 | 内置 | Superpowers |
| 9 | **openspec** | 规范驱动开发：proposal → specs → design → tasks | 20min | 内置插件 |
| 10 | **caveman-review** | 极简代码审查，补丁检查 | 10min | `npx skills add juliusbrussee/caveman@caveman-review -g -y` |
| 11 | **caveman-compress** | 代码压缩精简，合并重复逻辑 | 10min | `npx skills add juliusbrussee/caveman@caveman-compress -g -y` |
| 12 | **caveman-commit** | commit 规范与极简化 | 10min | `npx skills add juliusbrussee/caveman@caveman-commit -g -y` |
| 13 | **grill-me** | 追问式审查，深挖设计缺陷 | 15min | `npx skills add mattpocock/skills@grill-me -g -y` |
| 14 | **trailofbits-security** | CodeQL/Semgrep 静态分析，漏洞检测 | 30min | GitHub |

**适用场景**：
- 内核补丁提交前审查（caveman-review + grill-me）
- 驱动代码精简重构（caveman-compress）
- 安全漏洞静态分析（trailofbits-security）
- commit 规范化（caveman-commit）
- 规范驱动开发流程（openspec）

**已移除及原因：**
- ~~`code-review`~~：caveman-review（38.9K 安装量）功能等价且更极简
- ~~`code-simplifier`~~：caveman-compress（36.9K 安装量）功能等价且更极简
- ~~`code-refactoring`~~：不在 TOP50，caveman 系列已覆盖代码简化需求
- ~~`changelog-maintenance`~~：不在 TOP50，caveman-commit 已覆盖 commit 规范需求

---

### 第三梯队：效率增强（中频使用）

| 顺序 | Skill | 适用场景 | 学习时间 | 来源 |
|:----:|-------|----------|:--------:|------|
| 15 | **mcp-builder** | 自定义 MCP Server（如连接开发板） | 30min | `npx skills add anthropics/skills@mcp-builder -g -y` |
| 16 | **markitdown** | PDF/PPT/Word/Excel/HTML → Markdown 转换 | 5min | `pip install markitdown[all]` |
| 17 | **firecrawl** | 网页抓取/搜索，返回干净 Markdown | 10min | `npx skills add firecrawl/cli@firecrawl -g -y` |
| 18 | **github-actions-docs** | CI/CD workflow 模板速查 | 10min | `npx skills add xixu-me/skills@github-actions-docs -g -y` |
| 19 | **paper-context-resolver** | 论文/技术文档复现与理解 | 15min | `npx skills add llllllllama/ai-paper-reproduction-skill@paper-context-resolver -g -y` |
| 20 | **better-auth-best-practices** | 认证安全最佳实践 | 10min | `npx skills add better-auth/skills@better-auth-best-practices -g -y` |

**已移除及原因：**
- ~~`ralph-loop`~~：不在 TOP50，oh-my-opencode 已内置 ultrawork 模式，功能完全覆盖
- ~~`dev-agent-skills`~~：不在 TOP50，功能被 oh-my-opencode + Superpowers 内置 skill 完整覆盖
- ~~`next-ai-draw-io`~~：不在 TOP50，低频使用
- ~~`github`~~：排名靠后，github-actions-docs（71.7K）已覆盖 CI/CD 需求

---

### 第四梯队：按需安装

| 顺序 | Skill | 适用场景 | 建议时机 |
|:----:|-------|----------|----------|
| 21 | skill-creator | 沉淀内核调试工作流 | 学完核心 skill 后再学 |
| 22 | agent-browser | 访问厂商文档、下载驱动 | 偶尔需要时再装 |
| 23 | obsidian-markdown | Obsidian 笔记知识库管理 | 有笔记习惯再考虑 |
| 24 | supabase-postgres-best-practices | DB 最佳实践、嵌入式数据层 | 涉及数据库时再考虑 |
| 25 | audit-website | 网站/服务安全审计 | 有 Web 服务安全需求时再装 |
| 26 | lark-doc + lark-approval | 飞书文档/审批自动化 | 团队用飞书时再装 |

**已移除及原因：**
- ~~`ontology`~~：不在 TOP50，已过时
- ~~`proactive-agent`~~：不在 TOP50，功能不成熟
- ~~`deer-flow`~~：不在 TOP50，独立框架太重

---

## 二、Superpowers 已安装（内置 15 Skill）

> 这些 skill 已内置，无需安装，直接可用。

| 顺序 | Skill | 用途 | 嵌入式场景 |
|:----:|-------|------|------------|
| 27 | brainstorming | 需求澄清、方案设计 | 驱动架构设计 |
| 28 | writing-plans | 生成实施计划 | 开发任务分解 |
| 29 | executing-plans | 按计划执行开发 | 自动执行计划 |
| 30 | test-driven-development | 红绿 TDD 开发 | 驱动单元测试 |
| 8 | **systematic-debugging** | **系统性调试定位** | **内核 Oops 分析** ⭐ |
| 31 | dispatching-parallel-agents | 多 Agent 并行任务 | 多模块并行开发 |
| 32 | subagent-driven-development | 子 Agent 驱动开发 | 复杂任务分解 |
| 33 | requesting-code-review | 请求代码审查 | 补丁提交前自查 |
| 34 | receiving-code-review | 接收代码审查反馈 | 处理 review 意见 |
| 35 | verification-before-completion | 完成前验证 | 确保任务完成 |
| 36 | finishing-a-development-branch | 分支合并/清理 | 补丁合并流程 |
| 37 | using-git-worktrees | Git worktree 隔离开发 | 多版本并行开发 |
| 38 | writing-skills | 自定义 Skill 打包 | 沉淀工作流 |
| 39 | using-superpowers | Superpowers 使用指南 | 确保纪律性 |

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
├── Day 1-2: find-skills（发现 Skill 的入口）
├── Day 3-4: oh-my-opencode（多 agent 编排核心）
├── Day 5-6: tmux（远程开发必备）
└── Day 7: summarize + caveman（信息处理 + 代码极简）

Week 2: 第二梯队（代码质量）
├── systematic-debugging（Superpowers 已内置）
├── openspec（规范驱动开发流程）
├── caveman-review + caveman-compress + caveman-commit（极简代码审查/精简/提交）
├── grill-me（追问式审查，深挖设计缺陷）
└── trailofbits-security（安全分析）

Week 3: 第三梯队（效率增强）
├── mcp-builder（如需自定义 MCP）
├── markitdown + firecrawl（文档转换 + 网页抓取）
└── github-actions-docs + paper-context-resolver（CI/CD + 论文复现）

Week 4+: 按需补充
├── skill-creator（开始沉淀自己的工作流）
├── 创建嵌入式专用 skill
└── 第四梯队按需安装
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

## 七、如何学习一个 Skill？

### 5 步学习法

```
1️⃣ 读 SKILL.md 的 "When to Use" / "适用场景"
   └─→ 了解什么时候用

2️⃣ 读 "Quick Reference" / "快速参考"
   └─→ 了解基本用法

3️⃣ 读 "Usage" / "使用方法"
   └─→ 了解具体步骤

4️⃣ 实际使用一次
   └─→ 动手实践

5️⃣ 记录心得到笔记
   └─→ 巩固记忆
```

---

## 八、常见问题

### Q1: Skill 装在哪里？

```
~/.config/opencode/skills/     # opencode 的 Skill 目录
~/skill-finder/                # find-skills 的数据目录
```

### Q2: 怎么知道装了什么 Skill？

```bash
# 查看已安装的 Skill
ls ~/.config/opencode/skills/

# 查看本仓库的 Skill 清单
cat opencode-skill-list.md
```

### Q3: 会不会装太多用不过来？

**不会！** 遵循原则：
- ✅ 先学第一梯队（5 个）
- ✅ 其他按需安装
- ❌ 不要一次性全装

### Q4: 如何避免恶意 Skill？

**安装前必做**：
1. 用 `skill-vetter` 审计
2. 查看下载量/安装量（高 = 更多人验证过）
3. 查看更新时间（新 = 有人维护）
4. 查看作者/仓库信誉

---

## 数据源与参考

### 数据来源

| 来源 | 链接 | 说明 |
|------|------|------|
| ClawHub | https://clawhub.ai/skills?sort=downloads | TOP 50 下载排名 |
| skills.sh | https://skills.sh/ | Skill 安装排行榜 (`npx skills add`) |
| Awesome Claude Skills | https://github.com/travisvn/awesome-claude-skills | 社区精选清单 |
| Anthropic 官方 | https://github.com/anthropics/skills | 官方 Skills 仓库 |
| Superpowers | https://github.com/obra/superpowers | 已安装，15 个内置 Skill |
| Trail of Bits | https://github.com/trailofbits/skills | 安全研究 Skills |
| VoltAgent Awesome List | https://github.com/VoltAgent/awesome-openclaw-skills | 5,494 已审核 Skills |
| Firecrawl 评测 | https://www.firecrawl.dev/blog/openclaw-skills | 16 个最佳 Skills 评测 |

### 学习资源

| 资源 | 链接 | 说明 |
|------|------|------|
| 🎬 视频入门 | https://www.bilibili.com/video/BV1dz6oBWEWx/ | 10分钟弄懂 Skill |
| 🎬 封装教程 | https://www.bilibili.com/video/BV1i2wbzhEL9/ | 保姆级 Agent Skill 封装教程（PM刘搞定） |
| OpenClaw 推荐 | https://help.apiyi.com/en/openclaw-skill-recommendations-2026-en.html | 社区推荐 TOP 10 |
| Firecrawl 评测 | https://www.firecrawl.dev/blog/openclaw-skills | 16 个最佳 Skills 评测 |

---

## 九、skills.sh TOP 50 汇总（2026-04-25 更新）

> 按 skills.sh 全时间安装量排名，已排除前端/设计/媒体/社交/营销/Azure/GitHub 被墙/纯前端框架类 skill。
> 标注 ⭐ 为本次新增；数据来源：[skills.sh](https://skills.sh/) All Time 排行（总计 90,987 个 skill）。

| 排名 | Skill | 安装量 | 来源 | 嵌入式场景 | 已在文档 |
|:----:|-------|------:|------|------------|:--------:|
| 1 | **find-skills** | 1.2M | vercel-labs/skills | 发现并安装需要的 skill | ✅ 第一梯队 |
| 2 | **agent-browser** | 212.3K | vercel-labs/agent-browser | 访问厂商文档、下载驱动 | ✅ 第四梯队 |
| 3 | **skill-creator** | 167.7K | anthropics/skills | 沉淀内核调试工作流 | ✅ 第四梯队 |
| 4 | **brainstorming** | 121.9K | obra/superpowers | 需求澄清、方案设计 | ✅ Superpowers |
| 5 | ⭐ **supabase-postgres-best-practices** | 121.1K | supabase/agent-skills | DB 最佳实践、嵌入式数据层 | — |
| 6 | **pdf** | 84.2K | anthropics/skills | PDF 提取/生成（内核文档） | ✅ 第十节 |
| 7 | ⭐ **caveman** | 80.5K | juliusbrussee/caveman | 代码极简主义、精简驱动代码 | — |
| 8 | **pptx** | 78.9K | anthropics/skills | PPT 生成（技术汇报） | ✅ 第十节 |
| 9 | ⭐ **lark-doc** | 75.7K | larksuite/cli | 飞书文档自动化 | — |
| 10 | **using-superpowers** | 72.6K | obra/superpowers | Superpowers 使用指南 | ✅ Superpowers |
| 11 | ⭐ **github-actions-docs** | 71.7K | xixu-me/skills | CI/CD workflow 模板 | ✅ 第十节 |
| 12 | ⭐ **openclaw-secure-linux-cloud** | 71.1K | xixu-me/skills | Linux 安全加固、云安全 | — |
| 13 | **systematic-debugging** | 71.0K | obra/superpowers | 内核 Oops/panic 分析 | ✅ Superpowers |
| 14 | ⭐ **skills-cli** | 70.9K | xixu-me/skills | Skill CLI 管理 | — |
| 15 | **writing-plans** | 70.4K | obra/superpowers | 长任务规划持久化 | ✅ Superpowers |
| 16 | ⭐ **readme-i18n** | 70.3K | xixu-me/skills | README 多语言国际化 | — |
| 17 | ⭐ **browser-use** | 69.5K | browser-use/browser-use | 浏览器交互自动化 | — |
| 18 | ⭐ **use-my-browser** | 68.5K | xixu-me/skills | 浏览器页面操作自动化 | — |
| 19 | **docx** | 68.4K | anthropics/skills | Word 文档读写 | ✅ 第十节 |
| 20 | ⭐ **xget** | 68.0K | xixu-me/skills | 增强下载，断点续传/多线程 | ✅ 第十节 |
| 21 | ⭐ **tzst** | 68.0K | xixu-me/skills | Zstd 压缩/解压，内核镜像/固件包 | ✅ 第十节 |
| 22 | ⭐ **xdrop** | 67.8K | xixu-me/skills | 文件传输工具 | — |
| 23 | **test-driven-development** | 61.1K | obra/superpowers | 驱动单元测试 | ✅ Superpowers |
| 24 | **xlsx** | 61.1K | anthropics/skills | Excel 数据分析 | ✅ 第十节 |
| 25 | **requesting-code-review** | 60.6K | obra/superpowers | 补丁提交前自查 | ✅ Superpowers |
| 26 | **executing-plans** | 57.0K | obra/superpowers | 按计划执行开发 | ✅ Superpowers |
| 27 | **subagent-driven-development** | 51.8K | obra/superpowers | 子 Agent 驱动开发 | ✅ Superpowers |
| 28 | **verification-before-completion** | 49.9K | obra/superpowers | 完成前验证 | ✅ Superpowers |
| 29 | ⭐ **lark-approval** | 48.6K | larksuite/cli | 飞书审批流程 | — |
| 30 | **receiving-code-review** | 48.4K | obra/superpowers | 接收 review 意见 | ✅ Superpowers |
| 31 | **writing-skills** | 48.2K | obra/superpowers | 自定义 Skill 打包 | ✅ Superpowers |
| 32 | ⭐ **audit-website** | 46.5K | squirrelscan/skills | 网站/服务安全审计 | — |
| 33 | **dispatching-parallel-agents** | 46.4K | obra/superpowers | 多 Agent 并行任务 | ✅ Superpowers |
| 34 | **using-git-worktrees** | 46.2K | obra/superpowers | Git worktree 隔离开发 | ✅ Superpowers |
| 35 | **finishing-a-development-branch** | 44.2K | obra/superpowers | 分支合并/清理 | ✅ Superpowers |
| 36 | **mcp-builder** | 43.7K | anthropics/skills | 自定义 MCP Server | ✅ 第三梯队 |
| 37 | ⭐ **paper-context-resolver** | 43.1K | llllllllama/ai-paper-reproduction-skill | 论文/技术文档复现 | — |
| 38 | ⭐ **better-auth-best-practices** | 41.7K | better-auth/skills | 认证安全最佳实践 | — |
| 39 | ⭐ **firecrawl** | 40.4K | firecrawl/cli | 网页抓取/搜索，返回干净 Markdown | — |
| 40 | ⭐ **caveman-commit** | 39.4K | juliusbrussee/caveman | commit 规范与极简 | — |
| 41 | ⭐ **caveman-review** | 38.9K | juliusbrussee/caveman | 极简代码审查 | — |
| 42 | ⭐ **caveman-compress** | 36.9K | juliusbrussee/caveman | 代码压缩精简 | — |
| 43 | ⭐ **typescript-advanced-types** | 36.5K | wshobson/agents | TS 高级类型（工具链开发） | — |
| 44 | ⭐ **value** | 35.4K | hugmouse/skills | 价值分析 | — |
| 45 | ⭐ **grill-me** | 34.0K | mattpocock/skills | 追问式审查，深挖设计缺陷 | — |
| 46 | ⭐ **caveman-help** | 33.5K | juliusbrussee/caveman | 代码帮助/解释 | — |
| 47 | ⭐ **doc-coauthoring** | 33.0K | anthropics/skills | 文档协作编辑 | — |
| 48 | ⭐ **self-improving-agent** | 25.8K | charon-fan/agent-playbook | 跨会话记住调试经验 | ✅ 第一梯队 |
| 49 | ⭐ **obsidian-markdown** | 22.9K | kepano/obsidian-skills | Obsidian 笔记知识库 | — |
| 50 | ⭐ **git-commit** | 26.6K | github/awesome-copilot | Git commit 规范与自动化 | ✅ 第十节 |

---

## 十、低优先级 Skills 完整列表（按需查阅）

> 以下 Skills 对嵌入式开发优先级较低，但保留完整列表供查阅。

### 开发工具类

| 顺序 | Skill | 说明 | 来源 |
|:----:|-------|------|------|
| 40 | byterover | Agent 知识管理，项目模式存储检索 | ClawHub |
| 41 | elite-longterm-memory | 长期记忆系统 (WAL + vector search + git-notes) | ClawHub |
| 42 | mcporter | MCP 服务器工具调用管理 | ClawHub |
| 43 | clawddocs | Clawdbot 文档专家，配置代码速查 | ClawHub |
| 44 | auto-updater | 自动更新 Agent 和已装 Skills | ClawHub |
| 45 | model-usage | 模型用量/成本统计 | ClawHub |
| 46 | ffuf-web-fuzzing | Web 模糊测试渗透测试 | GitHub |
| 47 | claude-scientific-skills | 科学计算库与数据库操作技能 | GitHub |
| 48 | git-commit | Git commit 规范与自动化消息生成 (26.6K 安装) | skills.sh |
| 49 | gh-cli | GitHub CLI 增强，PR/Issue/CI 操作 | skills.sh |
| 50 | security-best-practices | 安全编码最佳实践，CodeQL/Semgrep 集成 | skills.sh |
| 51 | python-performance-optimization | Python 性能分析与优化技巧 | skills.sh |
| 52 | github-actions-docs | GitHub Actions 文档速查与 workflow 模板 (71.7K 安装) | skills.sh |
| 53 | xget | 增强型文件下载工具，支持断点续传/多线程 (68.0K 安装) | skills.sh |
| 54 | tzst | Zstandard 压缩/解压工具，适合内核镜像/固件包 (68.0K 安装) | skills.sh |

### 搜索与信息获取类

| 顺序 | Skill | 说明 | 来源 |
|:----:|-------|------|------|
| 55 | agent-browser | Rust 无头浏览器自动化，点击/输入/截图 (212.3K 安装) | skills.sh |
| 56 | browser-use | 浏览器交互自动化，测试/表单/数据提取 (69.5K 安装) | skills.sh |
| 57 | playwright-mcp | Playwright MCP 浏览器自动化 | ClawHub |
| 58 | playwright-scraper-skill | Playwright 反爬虫抓取 | ClawHub |
| 59 | multi-search-engine | 17 搜索引擎集成 (8 国内 + 9 国际) | ClawHub |
| 60 | baidu-search | 百度 AI 搜索引擎集成 | ClawHub |
| 61 | firecrawl-cli | JS 重网页抓取/爬取/搜索，返回干净 Markdown | ClawHub/Firecrawl |
| 62 | use-my-browser | 浏览器交互与页面操作自动化 (68.5K 安装) | skills.sh |

### 文档与内容处理类

| 顺序 | Skill | 说明 | 来源 |
|:----:|-------|------|------|
| 63 | humanizer | 去 AI 痕迹写作，让文字更自然 | ClawHub |
| 64 | humanizer-zh | 中文去 AI 痕迹写作 | ClawHub |
| 65 | humanize-ai-text | AI 文本人性化改写，绕过检测器 | ClawHub |
| 66 | nano-pdf | 自然语言编辑 PDF | ClawHub |
| 67 | openai-whisper | 本地语音转文字 (无需 API Key) | ClawHub |
| 68 | anthropic-docs-skill | AI 读写 Word/PPT/Excel/PDF | ClawHub |
| 69 | docx-skill | Word 文档读写/生成/编辑 | ClawHub |
| 70 | readme-i18n | README 多语言国际化生成 (70.3K 安装) | skills.sh |

### Anthropic 官方文档 Skills

| Skill | 说明 | 安装 |
|-------|------|------|
| docx | Word 文档，支持修订/批注/格式保留 | `/plugin install docx` |
| pdf | PDF 工具包，提取/创建/合并/拆分/表单 | `/plugin install pdf` |
| pptx | PPT 生成/编辑，支持母版/模板/图表 | `/plugin install pptx` |
| xlsx | Excel 表格，公式/格式/数据分析/可视化 | `/plugin install xlsx` |

### 通讯与社交类

| 顺序 | Skill | 说明 | 来源 |
|:----:|-------|------|------|
| 71 | himalaya | CLI 邮件管理 (IMAP/SMTP，多账户) | ClawHub |
| 72 | imap-smtp-email | IMAP/SMTP 邮件收发 (含附件) | ClawHub |

### 云服务与平台集成类

| 顺序 | Skill | 说明 | 来源 |
|:----:|-------|------|------|
| 73 | notion | Notion API 页面/数据库/块管理 | ClawHub |
| 74 | api-gateway | 100+ API 统一网关 (OAuth 管理) | ClawHub |
| 75 | trello | Trello 看板/列表/卡片管理 | ClawHub |
| 76 | stripe-api | Stripe 支付/订阅/发票管理 | ClawHub |
| 77 | shopify | Shopify 电商集成 | ClawHub |
| 78 | xero | Xero 财务 API | ClawHub |
| 79 | supabase-postgres-best-practices | Supabase/PostgreSQL 最佳实践 (121.1K 安装) | skills.sh |

### Agent 能力增强类

| 顺序 | Skill | 说明 | 来源 |
|:----:|-------|------|------|
| 80 | desktop-control | 桌面自动化 (鼠标/键盘/屏幕控制) | ClawHub |

### 生活与工具类

| 顺序 | Skill | 说明 | 来源 |
|:----:|-------|------|------|
| 81 | blogwatcher | RSS/Atom 博客监控更新 | ClawHub |
| 82 | automation-workflows | 自动化工作流设计 (Zapier/Make/n8n) | ClawHub |
| 83 | csv-data-summarizer | CSV 文件智能分析与摘要 | ClawHub |
| 84 | file-organizer | 文件自动分类整理 | ClawHub |
| 85 | research-skills | 多源研究工作流 (论文/文档/网页) | ClawHub |

### 更多社区 Skills

| 顺序 | Skill | 说明 | 来源 |
|:----:|-------|------|------|
| 86 | ios-simulator-skill | iOS app building, navigation, and testing | GitHub |
| 87 | claude-d3js-skill | Visualizations in d3.js | GitHub |
| 88 | web-asset-generator | Generates web assets like favicons, app icons | GitHub |
| 89 | loki-mode | Multi-agent autonomous startup system (37 agents) | GitHub |
| 90 | awesome-claude-skill | Claude 精选 Skill 合集导航 | ClawHub |

---

## 十一、Everything Claude Code (ECC)

> [affaan-m/everything-claude-code](https://github.com/affaan-m/everything-claude-code) | 140K+ stars | Anthropic 黑客松获胜作品

**核心组件**: 181+ Skills, 36 个 Agents, 47 个 Commands, Rules, Hooks

**嵌入式推荐**:
| Skill | 用途 |
|-------|------|
| cpp-coding-standards | C++ 内核模块规范 |
| rust-reviewer | Rust 代码审查 |
| perl-patterns | 内核脚本模式 |
| security-scan | AgentShield 安全审计 |
| search-first | 先调研再编码 |

**安装**:
```bash
/plugin marketplace add affaan-m/everything-claude-code
/plugin install ecc@ecc
```

**详细文档**: 见 [`skills-repo/ecc/`](skills-repo/ecc/README.md)

---

## 附录：Skill 清单速查表

| 梯队 | 数量 | 学习优先级 | 核心 Skill |
|------|------|-----------|-----------|
| 第一梯队 | 5 个 | ⭐⭐⭐ 必学 | find-skills, oh-my-opencode, tmux, summarize, caveman |
| 第二梯队 | 7 个 | ⭐⭐ 重要 | debugging, caveman 系列, grill-me, security |
| 第三梯队 | 6 个 | ⭐ 有用 | mcp-builder, firecrawl, paper-context-resolver |
| 第四梯队 | 6 个 | 按需 | skill-creator, agent-browser, obsidian-markdown |
| Superpowers | 15 个 | 内置 | 直接使用 |

---

**核心原则**：先装能帮你**干活**的（tmux、summarize、caveman），再装帮你**提质**的（caveman-review、trailofbits-security），最后装帮你**扩展**的（mcp-builder、skill-creator）。

**避坑原则**：前端/设计/媒体/社交类 skill 对嵌入式开发几乎没有价值，不要被"看起来很酷"诱惑。

**最后更新**: 2026-04-25
