# OpenCode Skill 清单

> **适用人群**: Linux 嵌入式底层程序员 (C/Rust/Python, 内核/效率工具/防护网)
>
> **更新时间**: 2026-06-14 (ClawHub TOP200 已同步)

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
├── opencode-skill-list.md     # 📋 完整清单（TOP 200 Skill 分析）
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

| 顺序 | Skill | 安装量 | 适用场景 | 学习时间 | 安装命令 |
|:----:|-------|------:|----------|:--------:|----------|
| 1 | **find-skills** | 2.0M | 发现并安装需要的 skill，解决"不知道有什么" | 10min | `npx skills add vercel-labs/skills@find-skills -g -y` |
| 2 | **oh-my-opencode** | 内置 | OpenCode 多 agent 编排、ultrawork 模式、后台任务 | 15min | 内置插件 |
| 3 | **tmux** | — | 远程开发板调试、交叉编译长任务、内核日志观察 | 15min | `npx skills add steipete/clawdis@tmux -g -y` |
| 4 | **caveman** | 244.3K | 代码极简主义，精简驱动代码/内核模块（生态系统 611.8K） | 15min | `npx skills add juliusbrussee/caveman@caveman -g -y` |
| 5 | **grill-me** | 311.5K | 追问式审查，深挖设计缺陷和安全隐患 | 15min | `npx skills add mattpocock/skills@grill-me -g -y` |

**为什么这 5 个必学？**
- `find-skills`：发现 skill 的入口，装其他 skill 的前置。**2.0M 安装量**，整个生态的入口
- `oh-my-opencode`：OpenCode 核心编排能力，多 agent 协作/ultrawork/后台任务管理
- `tmux`：嵌入式/远程开发的核心能力，没有它无法跑长任务
- `caveman`：代码极简主义（主模块 244.3K，全家桶 611.8K），commit/review/compress/help/stats/cavecrew 全覆盖
- `grill-me`：**3 个月从 34K 涨到 311.5K（+816%）**，社区验证的顶级审查 skill

**较上一版（2026-04）主要变化：**
- ⬆ `caveman` 从第二梯队升至第一梯队（安装量从 80.5K → 244.3K，+203%）
- ⬆ `grill-me` 从第二梯队升至第一梯队（安装量从 34K → 311.5K，+816%）
- ➡ `summarize` 从第一梯队移至第三梯队（社区安装量不在 TOP200，但功能仍重要）
- ~~`summarize`~~ 移至第三梯队，核心原因：功能分散到多个 skill（summarize-pro、caveman-help 等），社区不再集中安装单一 summarize

---

### 第二梯队：开发核心（显著提升代码质量）

| 顺序 | Skill | 安装量 | 适用场景 | 学习时间 | 来源 |
|:----:|-------|------:|----------|:--------:|------|
| 6 | **diagnose** | 212.8K | 系统性 bug 诊断方法论，内核 Oops/panic 分析 | 15min | `npx skills add mattpocock/skills@diagnose -g -y` |
| 7 | **systematic-debugging** | 142.3K | 内置调试框架，与 diagnose 互补 | 内置 | Superpowers |
| 8 | **simple** | 185.0K | 代码简化强制执行，复杂度控制 | 10min | `npx skills add roin-orca/skills@simple -g -y` |
| 9 | **openspec** | — | 规范驱动开发：proposal → specs → design → tasks | 20min | 内置插件 |
| 10 | **caveman-commit** | 156.0K | commit 规范与极简化 | 10min | `npx skills add juliusbrussee/caveman@caveman-commit -g -y` |
| 11 | **caveman-review** | 107K+ | 极简代码审查，补丁检查 | 10min | `npx skills add juliusbrussee/caveman@caveman-review -g -y` |
| 12 | **caveman-compress** | 107K+ | 代码压缩精简，合并重复逻辑 | 10min | `npx skills add juliusbrussee/caveman@caveman-compress -g -y` |
| 13 | **grill-with-docs** | 248.6K | 基于文档的代码审查，对照 datasheet/spec 检查 | 15min | `npx skills add mattpocock/skills@grill-with-docs -g -y` |
| 14 | **improve-codebase-architecture** | 254.6K | 大型代码库架构改进，嵌入式平台代码重构 | 20min | `npx skills add mattpocock/skills@improve-codebase-architecture -g -y` |

**适用场景**：
- 内核补丁提交前审查（caveman-review + grill-me + grill-with-docs）
- 驱动代码精简重构（caveman-compress + simple）
- commit 规范化（caveman-commit）
- 规范驱动开发流程（openspec）
- Bug 根因分析（diagnose + systematic-debugging 互补）
- 大型嵌入式代码库重构（improve-codebase-architecture）
- 基于 datasheet/spec 的代码正确性检查（grill-with-docs）

**较上一版主要变化：**
- 🆕 **diagnose**（212.8K）：系统性诊断方法论新增，替代 manual 调试流程
- 🆕 **simple**（185.0K）：极简主义强制执行，与 caveman 互补
- 🆕 **grill-with-docs**（248.6K）：文档驱动审查，嵌入式开发中对照 datasheet 的利器
- 🆕 **improve-codebase-architecture**（254.6K）：架构级改进，替代手动重构流程
- ⬇ **trailofbits-security** 从第二梯队移除：安装量较低，安全需求由 skill-vetter + grill-me 覆盖

---

### 第三梯队：效率增强（中频使用）

| 顺序 | Skill | 安装量 | 适用场景 | 学习时间 | 来源 |
|:----:|-------|------:|----------|:--------:|------|
| 15 | **summarize** | — | 读内核文档、驱动文档、RFC、patch 描述 | 10min | ClawHub |
| 16 | **triage** | 191.0K | Bug 优先级分类，大规模缺陷管理 | 10min | `npx skills add mattpocock/skills@triage -g -y` |
| 17 | **mcp-builder** | — | 自定义 MCP Server（如连接开发板） | 30min | `npx skills add anthropics/skills@mcp-builder -g -y` |
| 18 | **firecrawl** | — | 网页抓取/搜索，返回干净 Markdown | 10min | `npx skills add firecrawl/cli@firecrawl -g -y` |
| 19 | **github-actions-docs** | 216.5K | CI/CD workflow 模板速查 | 10min | `npx skills add xixu-me/skills@github-actions-docs -g -y` |
| 20 | **paper-context-resolver** | 140.1K | 论文/技术文档复现与理解 | 15min | `npx skills add llllllllama/ai-paper-reproduction-skill@paper-context-resolver -g -y` |

**较上一版主要变化：**
- 🆕 **triage**（191.0K）：大规模缺陷分类管理，对维护多平台嵌入式 BSP 很有价值
- 🗑 ~~markitdown~~ 移除：firecrawl 已覆盖文档转换需求，维护成本 > 收益
- 🗑 ~~better-auth-best-practices~~ 移除：嵌入式场景低频，从第三梯队移至第四梯队
- ⬇ **summarize**：虽然仍重要，但社区安装量低，功能可被 summarize-pro 等替代

---

### 第四梯队：按需安装

| 顺序 | Skill | 适用场景 | 建议时机 |
|:----:|-------|----------|----------|
| 21 | skill-creator | 沉淀内核调试工作流 | 学完核心 skill 后再学 |
| 22 | agent-browser | 访问厂商文档、下载驱动 | 偶尔需要时再装 |
| 23 | caveman-help | 代码解释/帮助 | 需要理解陌生代码时 |
| 24 | cavecrew | 多 agent 协作 dev team 模式 | 大型跨模块任务时 |
| 25 | caveman-stats | Agent 使用统计/效率分析 | 想量化 AI 辅助效果时 |
| 26 | impeccable | 代码质量检查，适合安全关键系统 | 交付前审查时 |
| 27 | supabase-postgres-best-practices | DB 最佳实践、嵌入式数据层 | 涉及数据库时 |
| 28 | better-auth-best-practices | 认证安全最佳实践 | 涉及认证系统时 |
| 29 | obsidian-markdown | Obsidian 笔记知识库管理 | 有笔记习惯再考虑 |
| 30 | lark-doc + lark-approval | 飞书文档/审批自动化 | 团队用飞书时 |

**较上一版主要变化：**
- 🆕 **caveman-help**、**cavecrew**（106.2K）、**caveman-stats**（106.2K）：caveman 生态系统新成员
- 🆕 **impeccable**（158.8K）：pbakaus 出品，代码质量工具，适合 safety-critical 场景
- 🔄 **skill-creator** 从第三梯队移至第四梯队（学习门槛较高，先掌握使用再学创建）

---

## 二、Superpowers 已安装（内置 15 Skill）

> 这些 skill 已内置，无需安装，直接可用。

| 顺序 | Skill | 安装量 | 用途 | 嵌入式场景 |
|:----:|-------|------:|------|------------|
| 31 | brainstorming | 220.2K | 需求澄清、方案设计 | 驱动架构设计 |
| 32 | writing-plans | 141.5K | 生成实施计划 | 开发任务分解 |
| 33 | executing-plans | 116.1K | 按计划执行开发 | 自动执行计划 |
| 34 | test-driven-development | 125.7K | 红绿 TDD 开发 | 驱动单元测试 |
| 7 | **systematic-debugging** | **142.3K** | **系统性调试定位** | **内核 Oops 分析** ⭐ |
| 35 | dispatching-parallel-agents | — | 多 Agent 并行任务 | 多模块并行开发 |
| 36 | subagent-driven-development | 109.1K | 子 Agent 驱动开发 | 复杂任务分解 |
| 37 | requesting-code-review | 127.2K | 请求代码审查 | 补丁提交前自查 |
| 38 | receiving-code-review | 103.0K | 接收代码审查反馈 | 处理 review 意见 |
| 39 | verification-before-completion | 107.6K | 完成前验证 | 确保任务完成 |
| 40 | finishing-a-development-branch | — | 分支合并/清理 | 补丁合并流程 |
| 41 | using-git-worktrees | — | Git worktree 隔离开发 | 多版本并行开发 |
| 42 | writing-skills | 102.1K | 自定义 Skill 打包 | 沉淀工作流 |
| 43 | using-superpowers | 142.0K | Superpowers 使用指南 | 确保纪律性 |

---

## 三、暂时不需要浪费精力的 Skills

### ❌ 前端/设计类（完全不适用）

| Skill | 安装量 | 原因 |
|-------|------:|------|
| frontend-design | 541.5K | React/Tailwind 前端设计 |
| vercel-react-best-practices | 474.4K | React 最佳实践 |
| web-design-guidelines | 388.8K | Web 设计规范 |
| ui-ux-pro-max | 215.1K | UI/UX 设计，67种风格161套配色 |
| shadcn | 189.0K | React 组件库 |
| design-taste-frontend | 144.8K | 前端设计品味 |
| webapp-testing | — | Playwright 前端测试 |
| web-artifacts-builder | — | HTML artifacts 构建 |
| canvas-design | — | 视觉艺术设计 |
| high-end-visual-design | 118.9K | 高端视觉设计 |
| minimalist-ui | 108.9K | 极简 UI |
| industrial-brutalist-ui | 101.3K | 工业粗野风 UI |

### ❌ 媒体/内容类（低频）

| Skill | 安装量 | 原因 |
|-------|------:|------|
| remotion-best-practices | 369.0K | 代码生成动画视频 |
| video-edit | 234.0K | 视频编辑（runcomfy 生态） |
| nano-banana-2 | 133.3K | AI 生图 |
| ai-video-generation | 133.4K | AI 视频生成 |
| flux-kontext | 133.4K | AI 图像编辑 |
| seedance-v2 | 134.2K | AI 视频 |
| ai-music | 164.6K | AI 音乐生成 |
| lipsync | 133.6K | AI 唇形同步 |
| face-swap | 133.6K | AI 换脸 |

### ❌ 云平台锁定类

| Skill | 安装量 | 原因 |
|-------|------:|------|
| microsoft/azure-skills 全家桶 | 5.8M | Azure 云服务，与嵌入式开发无关 |
| vercel composition patterns | 210.5K | Vercel 部署模式 |
| convex | 520 | Convex 后端平台 |
| supabase | 120.6K | Supabase 平台（非 postgres 最佳实践版本） |
| firebase | 5.1K | Firebase 后端 |

### ❌ 通讯/社交类（低频）

| Skill | 安装量 | 原因 |
|-------|------:|------|
| larksuite 全家桶 | 2.5M+ | 飞书生态（doc/base/im/drive/approval/slides/attendance/okr...），除非团队用飞书 |

### ❌ 营销/电商类

| Skill | 安装量 | 原因 |
|-------|------:|------|
| copywriting | 125.8K | 营销文案 |
| seo-audit | 136.1K | SEO 审计 |
| content-strategy | 506 | 内容策略 |

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
Week 1: 第一梯队（基础能力 + 核心 Skill）
├── Day 1-2: find-skills（发现 Skill 的入口，2.0M 安装量）
├── Day 3-4: oh-my-opencode（多 agent 编排核心）
├── Day 5-6: tmux（远程开发必备）
└── Day 7: caveman（代码极简主义，244.3K）+ grill-me（追问式审查，311.5K）

Week 2: 第二梯队（代码质量 + 诊断能力）
├── diagnose（212.8K）+ systematic-debugging（142.3K）→ 双调试组合
├── openspec（规范驱动开发流程）
├── simple（185.0K）+ caveman-compress → 极简双保险
├── caveman-review + caveman-commit → 审查+提交规范
├── grill-with-docs（248.6K）→ 文档驱动审查
└── improve-codebase-architecture（254.6K）→ 架构重构

Week 3: 第三梯队（效率增强）
├── summarize → 文档/补丁信息压缩
├── triage（191.0K）→ 缺陷管理分类
├── mcp-builder（如需自定义 MCP）
├── firecrawl（网页抓取 + 文档转换二合一）
└── github-actions-docs（216.5K）+ paper-context-resolver（140.1K）

Week 4+: 按需补充
├── skill-creator（开始沉淀自己的工作流）
├── caveman 全家桶补充（help/stats/cavecrew）
├── impeccable（158.8K）→ 交付审查
└── 创建嵌入式专用 skill
```

---

## 六、Skill 目录结构

```
~/.config/opencode/skills/
├── brainstorming/          (Superpowers)
├── systematic-debugging/   (Superpowers)
├── writing-plans/          (Superpowers)
├── caveman/                (已安装)
├── grill-me/               (已安装)
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

### Q5: Matt Pocock 系列 skill 和 Superpowers 是否重复？

**互补关系，不是替代**：

| 领域 | Superpowers 内置 | Matt Pocock | 如何选？ |
|------|-----------------|-------------|----------|
| TDD | test-driven-development | tdd (240.6K) | Superpowers 已够用 |
| 调试 | systematic-debugging | diagnose (212.8K) | **两个都用**：diagnose 方法论 + sys-debug 工具链 |
| 审查 | requesting-code-review | grill-me (311.5K) | **两个都用**：request-review 流程 + grill-me 深度 |
| 计划 | writing/executing-plans | to-prd / to-issues | Superpowers 已覆盖 |
| 手递 | finishing-dev-branch | handoff (162.8K) | Superpowers 已覆盖 |

**核心原则**：Superpowers 覆盖流程，Matt Pocock 覆盖思考方法论，两者互补不冲突。

---

## 九、Skills.sh TOP200 核心 Skill（2026-06-14 更新）

> 按 skills.sh 全时间安装量排名，已排除前端/设计/媒体/社交/营销/Azure/GitHub 被墙/飞书生态类 skill。
> 标注 🆕 为本次新增；⬆ 为排名上升；⬇ 为排名下降。
> 数据来源：[skills.sh](https://skills.sh/) All Time 总排行（总计 701,684 安装，含所有 agent 平台）。

### 🏆 核心 Skill（嵌入式开发强相关）

| 排名 | Skill | 安装量 | 来源 | vs 上期 | 嵌入式场景 |
|:----:|-------|------:|------|:------:|------------|
| 1 | **find-skills** | 2.0M | vercel-labs/skills | ⬆ +67% | 发现并安装需要的 skill |
| 4 | **agent-browser** | 447.2K | vercel-labs/agent-browser | ⬆ +111% | 访问厂商文档、下载驱动 |
| 26 | **grill-me** | 311.5K | mattpocock/skills | ⬆ +816% | 追问式审查，深挖设计缺陷 |
| 27 | **skill-creator** | 267.8K | anthropics/skills | ⬆ +60% | 沉淀内核调试工作流 |
| 29 | **improve-codebase-architecture** | 254.6K | mattpocock/skills | 🆕 | 大型代码库架构改进 |
| 31 | **grill-with-docs** | 248.6K | mattpocock/skills | 🆕 | 基于文档的代码审查 |
| 32 | **caveman** | 244.3K | juliusbrussee/caveman | ⬆ +203% | 代码极简主义 |
| 33 | **tdd** | 240.6K | mattpocock/skills | 🆕 | TDD（补充 Superpowers 版本） |
| 48 | **supabase-postgres-best-practices** | 229.5K | supabase/agent-skills | ⬆ +89% | DB 最佳实践 |
| 67 | **to-prd** | 222.1K | mattpocock/skills | 🆕 | 需求转 PRD |
| 90 | **brainstorming** | 220.2K | obra/superpowers | ⬆ +81% | 需求澄清、方案设计 |
| 91 | **github-actions-docs** | 216.5K | xixu-me/skills | ⬆ +202% | CI/CD workflow 模板 |
| 100 | **diagnose** | 212.8K | mattpocock/skills | 🆕 | 系统性 bug 诊断 |
| 101 | **openclaw-secure-linux-cloud** | 212.8K | xixu-me/skills | ⬆ +199% | Linux 安全加固 |
| 103 | **to-issues** | 212.5K | mattpocock/skills | 🆕 | 需求转 Issues |
| 104 | **skills-cli** | 212.4K | xixu-me/skills | ⬆ +200% | Skill CLI 管理 |
| 111 | **xget** | 209.3K | xixu-me/skills | ⬆ +208% | 增强下载，断点续传/多线程 |
| 112 | **tzst** | 209.2K | xixu-me/skills | ⬆ +208% | Zstd 压缩/解压 |
| 113 | **xdrop** | 209.0K | xixu-me/skills | ⬆ +208% | 文件传输 |
| 115 | **write-a-skill** | 205.8K | mattpocock/skills | 🆕 | Skill 创建指南 |
| 116 | **zoom-out** | 205.1K | mattpocock/skills | 🆕 | 全局视角审视 |
| 120 | **caveman** (mattpocock fork) | 200.6K | mattpocock/skills | 🆕 | 极简主义（Matt 版） |
| 123 | **triage** | 191.0K | mattpocock/skills | 🆕 | Bug 优先级分类 |
| 126 | **simple** | 185.0K | roin-orca/skills | 🆕 | 代码简化强制执行 |
| 149 | **prototype** | 164.4K | mattpocock/skills | 🆕 | 快速原型 |
| 150 | **handoff** | 162.8K | mattpocock/skills | 🆕 | 会话 handoff |
| 151 | **impeccable** | 158.8K | pbakaus/impeccable | 🆕 | 代码质量检查 |
| 152 | **caveman-commit** | 156.0K | juliusbrussee/caveman | ⬆ +296% | commit 规范 |
| 159 | **systematic-debugging** | 142.3K | obra/superpowers | ⬆ +100% | 系统性调试定位 |
| 160 | **using-superpowers** | 142.0K | obra/superpowers | ⬆ +96% | Superpowers 使用指南 |
| 162 | **writing-plans** | 141.5K | obra/superpowers | ⬆ +101% | 长任务规划持久化 |
| 163 | **paper-context-resolver** | 140.1K | llllllllama/ai-paper-reproduction-skill | ⬆ +225% | 论文/文档复现 |
| 183 | **pdf** | 133.7K | anthropics/skills | ⬆ +59% | PDF 工具包 |
| 230 | **requesting-code-review** | 127.2K | obra/superpowers | ⬆ +110% | 补丁提交前自查 |
| 232 | **test-driven-development** | 125.7K | obra/superpowers | ⬆ +106% | 驱动单元测试 |
| 233 | **docx** | 124.0K | anthropics/skills | ⬆ +81% | Word 文档 |
| 239 | **executing-plans** | 116.1K | obra/superpowers | ⬆ +104% | 按计划执行开发 |
| 243 | **subagent-driven-development** | 109.1K | obra/superpowers | ⬆ +111% | 子 Agent 驱动开发 |
| 245 | **verification-before-completion** | 107.6K | obra/superpowers | ⬆ +116% | 完成前验证 |
| 246 | **cavecrew** | 106.2K | juliusbrussee/caveman | 🆕 | 多 Agent 协作团队 |
| 247 | **caveman-stats** | 106.2K | juliusbrussee/caveman | 🆕 | Agent 效率统计 |
| 250 | **receiving-code-review** | 103.0K | obra/superpowers | ⬆ +113% | 接收 review 意见 |
| 251 | **writing-skills** | 102.1K | obra/superpowers | ⬆ +112% | 自定义 Skill 打包 |
| 254 | **firecrawl** | — | firecrawl/cli | — | 网页抓取/搜索 |
| 265 | **mcp-builder** | — | anthropics/skills | — | 自定义 MCP Server |

### 📊 社区趋势观察（2026-04 → 2026-06）

| 趋势 | 具体数据 |
|------|----------|
| 🔥 **Matt Pocock 生态爆发** | grill-me +816%, 多个新 skill 空降 TOP150（diagnose, triage, zoom-out 等） |
| 🔥 **Caveman 生态扩张** | 主模块 +203%，全家桶从 260K → 611.8K |
| 🔥 **xixu-me 工具集高速增长** | github-actions-docs +202%, openclaw-secure-linux-cloud +199% |
| 📈 **Superpowers 全线翻倍** | 全部 15 个 skill 安装量平均翻倍，最高 +116% |
| 📉 **Anthropic 官方 skill 增速放缓** | pdf +59%, docx +81%, pptx +83% — 被社区 skill 分流 |
| 💤 **runcomfy/doany-ai 媒体类** | 130-140K 大量 AI 视频/图像 skill，对嵌入式开发无价值 |

---

## 十、双平台对比与安装策略

### 📊 ClawHub vs skills.sh 安装命令对比

| 平台 | 搜索命令 | 安装命令 | 适用场景 |
|------|---------|---------|---------|
| **ClawHub** | `npx clawhub search "query"` | `npx clawhub install <slug>` | 需要版本控制/回滚，Clawdbot 用户 |
| **skills.sh** | `npx skills find "query"` | `npx skills add <owner/repo@skill>` | 主流选择，18+ agent 支持 |
| **双源搜索** | `npx skills add vercel-labs/skills@find-skills` | 自动选择最优源 | 日常使用（推荐） |

### 🎯 嵌入式开发推荐安装策略

```bash
# 1. 先装 find-skills（双源搜索入口）
npx skills add vercel-labs/skills@find-skills -g -y

# 2. 用 find-skills 搜索并比较两个平台的 skill
# 在对话中： "用 find-skills 搜索 caveman 并比较 ClawHub 和 skills.sh 的结果"

# 3. 优先选择 skills.sh（安装量高 = 更多人验证）
npx skills add juliusbrussee/caveman@caveman -g -y

# 4. 需要版本控制/回滚时用 ClawHub
npx clawhub install self-improving-agent

# 5. 国内搜索需求（ClawHub 独有）
npx clawhub install multi-search-engine
npx clawhub install baidu-search
```

### ⚠️ 安全警告（Trail of Bits 2026-06）

根据 Trail of Bits 研究：
- ClawHub、skills.sh、Cisco skill-scanner 均被发现存在绕过漏洞
- **建议**：
  1. 始终使用 `skill-vetter` 审计后再安装
  2. 生产环境 curated 已审计的 skill 集合
  3. 优先选择高安装量 + 高 stars 的 skill
  4. 避免安装来源不明/下载量异常的 skill

---

## 十一、ClawHub 独有 Skill（嵌入式开发强相关）

> 数据来源：https://clawhub.ai/api/v1/skills?sort=downloads&limit=200
> 最后同步时间：2026-06-14
> **筛选标准**：仅展示 ClawHub 独有或排名显著高于 skills.sh 的 skill，已排除 skills.sh 已覆盖的内容

### 🎯 强烈推荐（ClawHub 独有）

| 排名 | Skill | 下载量 | 安装量 | 嵌入式价值 | 安装命令 |
|:----:|-------|------:|-------:|-----------|----------|
| #1 | **self-improving-agent** | 461K | 6,871 | ⭐⭐⭐ 跨会话自我改进，错误学习永久化 | `npx clawhub install self-improving-agent` |
| #2 | **skill-vetter** | 258K | 4,630 | ⭐⭐⭐ 安全审计必装（安装前必用） | `npx clawhub install skill-vetter` |
| #10 | **multi-search-engine** | 153K | 2,148 | ⭐⭐⭐ 17 搜索引擎（8 个国内：百度/搜狗/必应中国） | `npx clawhub install multi-search-engine` |
| #22 | **baidu-search** | 90K | 968 | ⭐⭐ 百度搜索专用（国内开发环境必备） | `npx clawhub install baidu-search` |
| #35 | **elite-longterm-memory** | 62K | 622 | ⭐⭐ 长期记忆系统（WAL + vector search + git-notes） | `npx clawhub install elite-longterm-memory` |

### 💡 按需安装（特定场景有用）

| 排名 | Skill | 下载量 | 嵌入式价值 | 适用场景 |
|:----:|-------|------:|-----------|----------|
| #4 | **github** | 190K | ⭐⭐ | GitHub CLI 增强，PR/Issue/CI 操作 |
| #16 | **obsidian** | 103K | ⭐⭐ | Obsidian 笔记知识库管理 |
| #21 | **skill-creator** | 92K | ⭐⭐ | 自定义 Skill 创建（沉淀内核调试工作流） |
| #32 | **mcporter** | 67K | ⭐⭐ | MCP 服务器工具调用管理 |
| #48 | **himalaya** | 46K | ⭐ | CLI 邮件管理（IMAP/SMTP，多账户） |
| #63 | **byterover** | 39K | ⭐ | Agent 知识管理（项目模式存储检索） |
| #60 | **clawddocs** | 41K | ⭐ | Clawdbot 文档专家，配置代码速查 |

### 📊 双平台对比

| 维度 | ClawHub | skills.sh |
|------|---------|-----------|
| 定位 | 精选 registry（198 在榜） | 开放市场（701K+ 安装） |
| 独有优势 | 自我改进 agent、国内搜索、长期记忆 | caveman、grill-me、Matt Pocock 生态 |
| 统计口径 | 下载量 + 安装量双指标 | 安装量单一指标 |
| 推荐策略 | 互补安装，不冲突 | 优先主战场 |

---

## 附录：Skill 清单速查表

| 梯队 | 数量 | 学习优先级 | 核心 Skill |
|------|------|-----------|-----------|
| 第一梯队 | 5 个 | ⭐⭐⭐ 必学 | find-skills, oh-my-opencode, tmux, caveman, grill-me |
| 第二梯队 | 9 个 | ⭐⭐ 重要 | diagnose, systematic-debugging, simple, openspec, caveman 三件套, grill-with-docs, improve-architecture |
| 第三梯队 | 6 个 | ⭐ 有用 | summarize, triage, mcp-builder, firecrawl, github-actions-docs, paper-context-resolver |
| 第四梯队 | 10 个 | 按需 | skill-creator, agent-browser, caveman-help, cavecrew, caveman-stats, impeccable, supabase-pg, better-auth, obsidian-markdown, lark |
| Superpowers | 15 个 | 内置 | 直接使用 |

---

## 更新日志

### 2026-06-14 v2.0（本次更新）
- 📊 **数据刷新**：skills.sh 排行从 2026-04 更新至 2026-06，总量从 90,987 → 701,684
- 🔥 **Matt Pocock 生态**：grill-me 从 #45(34K) 升至 #26(311.5K)，新增 diagnose(212.8K)、triage(191.0K)、grill-with-docs(248.6K) 等 10+ 个 skill
- 🔥 **Caveman 生态**：主模块 80.5K→244.3K，全家桶从 260K→611.8K，新增 cavecrew、caveman-stats
- 🆕 **第一梯队调整**：caveman 和 grill-me 升至第一梯队，summarize 移至第三梯队
- 🆕 **第二梯队扩展**：新增 diagnose、simple、grill-with-docs、improve-codebase-architecture
- 🆕 **第三梯队新增**：triage（大规模缺陷管理）
- 🗑 **移除过时 skill**：trailofbits-security、markitdown、better-auth-best-practices 从主要梯队移除
- 📝 **新增 Q5**：Matt Pocock 与 Superpowers 的对比与互补说明
- 📝 **新增趋势章节**：社区生态变化趋势分析
- 🆕 **ClawHub 独有 Skill**：实时 API 爬取 198 个 skill，仅保留与嵌入式开发强相关且 skills.sh 未覆盖的内容（5 个强推荐 + 7 个按需）
- 🆕 **双平台安装策略**：skills.sh 主战场 + ClawHub 互补（国内搜索/自我改进/长期记忆）
- 🆕 **其他平台发现**：SkillsMP (351K), SkillzWave (44K), theskills.directory (91K) 等 10+ 平台汇总

### 2026-04-25 v1.0（初始版本）
- 初始版本，基于 skills.sh TOP 50 排名整理

---

**核心原则**：先装能帮你**干活**的（tmux、caveman、grill-me），再装帮你**提质**的（diagnose、simple、grill-with-docs），最后装帮你**扩展**的（mcp-builder、skill-creator）。

**避坑原则**：前端/设计/媒体/社交/云平台锁定类 skill 对嵌入式开发几乎没有价值，不要被"看起来很酷"和高安装量（很多来自前端开发者）诱惑。

**数据来源**：
- [skills.sh](https://skills.sh/) — 主战场，701,684 总安装，18+ agent 支持
- [ClawHub](https://clawhub.ai/skills?sort=downloads) — 互补，198 skill 在榜，独有：self-improving-agent、multi-search-engine、baidu-search
- [SkillsMP](https://skillsmp.com) — 最大目录，351,349 skill（无质量门槛）
- [SkillzWave](https://skillzwave.ai) — 商业平台，44,000+ skill
- [theskills.directory](https://theskills.directory) — 场景 bundling，91,000 skill
- [officialskills.sh](https://officialskills.sh) — 官方 skill，577（Microsoft、Trail of Bits 等）
- 其他：killer-skills.com (3.4K)、Agent Skill Source (787+)、AgenticSkills (181+)

**最后同步时间**：2026-06-14
