# Skill 初学者学习指南

> 为 Linux 嵌入式开发定制的 Skill 学习路径

---

## 一、Skill 是什么？

### 一句话理解

**Skill = 给 AI 的岗位 SOP（标准作业程序）**

就像你进入新公司需要学习工作流程一样，Skill 就是教 AI 如何完成特定任务的"工作手册"。

### 为什么需要 Skill？

| 方式 | 做法 | 问题 |
|------|------|------|
| ❌ 不用 Skill | 每次手动告诉 AI 怎么做 | 重复、容易遗漏、结果不稳定 |
| ✅ 使用 Skill | 按需加载对应的 Skill | 标准化、可复用、结果可控 |

### 文件结构

每个 Skill 都是一个文件夹，核心是 `SKILL.md`：

```
skills/01-skill-vetter/
└── SKILL.md    # 核心：包含所有规则和步骤
```

---

## 二、本仓库目录结构

```
skills/
├── opencode-skill-list.md     # 📋 完整清单（90 个 Skill）
│
├── 00-BEGINNER-GUIDE.md       # 📘 本文件：初学者指南
│
├── 01-skill-vetter/           # 🔒 安全审计（第 1 个必学）
├── 02-find-skills/            # 🔍 发现 Skill（第 2 个必学）
├── 03-oh-my-opencode/         # 🤖 多 Agent 编排（第 3 个必学）
├── 04-tmux/                   # 💻 终端复用
├── 05-summarize/              # 📄 文档摘要
├── ...
└── 89-awesome-claude-skill/   # 共 89 个 Skill
```

### 编号规则

- `01-xx` 到 `07-xx`：第一梯队（必学）
- `08-xx` 到 `14-xx`：第二梯队（代码质量）
- `15-xx` 到 `20-xx`：第三梯队（效率增强）
- `21-xx` 到 `26-xx`：第四梯队（按需）
- `27-xx` 到 `89-xx`：Superpowers 内置 + 补充

---

## 三、学习路径（4 周计划）

### 📍 Week 1：工具准备（第一梯队前 3 个）

| 顺序 | Skill | 学习内容 | 时间 | 状态 |
|:----:|-------|----------|:----:|:----:|
| 1 | [skill-vetter](01-skill-vetter/SKILL.md) | 安全审计，防止恶意代码 | 5min | ⬜ |
| 2 | [find-skills](02-find-skills/SKILL.md) | 搜索和安装 Skill | 10min | ⬜ |
| 3 | [oh-my-opencode](03-oh-my-opencode/SKILL-oh-my-opencode.md) | 多 Agent 编排 | 15min | ⬜ |

**学习目标**：
- ✅ 理解如何安全地安装 Skill
- ✅ 学会搜索需要的 Skill
- ✅ 了解多 Agent 协作的基本概念

---

### 📍 Week 2：核心能力（第一梯队剩余 4 个）

| 顺序 | Skill | 学习内容 | 时间 | 状态 |
|:----:|-------|----------|:----:|:----:|
| 4 | [tmux](04-tmux/SKILL.md) | 终端复用，远程开发 | 15min | ⬜ |
| 5 | [summarize](05-summarize/SKILL.md) | 文档摘要，读内核文档 | 10min | ⬜ |
| 6 | [planning-with-files](06-planning-with-files/SKILL.md) | 长任务规划 | 10min | ⬜ |
| 7 | [self-improving-agent](07-self-improving-agent/SKILL.md) | 跨会话记忆 | 15min | ⬜ |

**学习目标**：
- ✅ 能用 tmux 跑长任务（编译、调试）
- ✅ 能快速理解内核文档/patch
- ✅ 长任务不会"做到一半忘了在干嘛"
- ✅ 调试过的错误不再犯

---

### 📍 Week 3：代码质量（第二梯队）

| 顺序 | Skill | 学习内容 | 时间 | 状态 |
|:----:|-------|----------|:----:|:----:|
| 8 | [systematic-debugging](08-systematic-debugging/SKILL.md) | 内核 Oops/panic 分析 | 20min | ⬜ |
| 9 | [openspec](09-openspec/SKILL.md) | 规范驱动开发流程 | 20min | ⬜ |
| 10 | [code-review](10-code-review/SKILL.md) | 补丁审查 | 20min | ⬜ |
| 11 | [code-simplifier](11-code-simplifier/SKILL.md) | 代码简化 | 15min | ⬜ |
| 12 | [code-refactoring](12-code-refactoring/SKILL.md) | 代码重构 | 20min | ⬜ |
| 13 | [changelog-maintenance](13-changelog-maintenance/SKILL.md) | commit 规范 | 10min | ⬜ |
| 14 | [trailofbits-security](14-trailofbits-security/SKILL.md) | 安全静态分析 | 30min | ⬜ |

**学习目标**：
- ✅ 能系统性调试内核崩溃
- ✅ 补丁提交前自查
- ✅ 代码更简洁、更安全

---

### 📍 Week 4：按需扩展

根据实际需求选择学习：

| 场景 | 推荐 Skill |
|------|-----------|
| 需要访问网页/下载驱动 | [agent-browser](23-agent-browser/SKILL.md) |
| 需要记笔记 | [obsidian](24-obsidian/SKILL.md) |
| 需要沉淀工作流 | [skill-creator](21-skill-creator/SKILL.md) |
| 复杂多步骤任务 | [deer-flow](26-deer-flow/SKILL.md) |

---

## 四、Superpowers 内置 Skill（15 个，无需安装）

这些 Skill 已经内置在 opencode 中，直接使用即可：

| Skill | 用途 | 嵌入式场景 |
|-------|------|------------|
| `brainstorming` | 需求澄清、方案设计 | 驱动架构设计 |
| `writing-plans` | 生成实施计划 | 开发任务分解 |
| `executing-plans` | 按计划执行 | 自动执行计划 |
| `test-driven-development` | TDD 开发 | 驱动单元测试 |
| `systematic-debugging` | 系统性调试 | 内核 Oops 分析 ⭐ |
| `dispatching-parallel-agents` | 多 Agent 并行 | 多模块并行开发 |
| `subagent-driven-development` | 子 Agent 驱动 | 复杂任务分解 |
| `requesting-code-review` | 请求代码审查 | 补丁提交前自查 |
| `receiving-code-review` | 接收审查反馈 | 处理 review 意见 |
| `verification-before-completion` | 完成前验证 | 确保任务完成 |
| `finishing-a-development-branch` | 分支合并/清理 | 补丁合并流程 |
| `using-git-worktrees` | Git worktree 隔离 | 多版本并行开发 |
| `writing-skills` | 自定义 Skill 打包 | 沉淀工作流 |
| `using-superpowers` | Superpowers 使用指南 | 确保纪律性 |

---

## 五、如何学习一个 Skill？

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

### 示例：学习 skill-vetter

```bash
# 1. 阅读 SKILL.md
cat skills/01-skill-vetter/SKILL.md

# 2. 理解核心：安装任何 skill 前先审计
# 3. 实际使用：
npx skills add some-author/some-skill -g -y
# skill-vetter 会自动运行审计

# 4. 记录：这个 skill 帮我避免了恶意代码
```

---

## 六、常见问题

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
- ✅ 先学第一梯队（7 个）
- ✅ 其他按需安装
- ❌ 不要一次性全装

### Q4: 如何避免恶意 Skill？

**安装前必做**：
1. 用 `skill-vetter` 审计
2. 查看下载量/安装量（高 = 更多人验证过）
3. 查看更新时间（新 = 有人维护）
4. 查看作者/仓库信誉

---

## 七、下一步

1. **今天**：阅读 [skill-vetter](01-skill-vetter/SKILL.md)（5 分钟）
2. **明天**：阅读 [find-skills](02-find-skills/SKILL.md)（10 分钟）
3. **本周**：完成 Week 1 的 3 个 Skill

---

## 附录：Skill 清单速查表

| 梯队 | 数量 | 学习优先级 | 核心 Skill |
|------|------|-----------|-----------|
| 第一梯队 | 7 个 | ⭐⭐⭐ 必学 | vetter, find-skills, oh-my-opencode, tmux |
| 第二梯队 | 7 个 | ⭐⭐ 重要 | debugging, code-review, security |
| 第三梯队 | 6 个 | ⭐ 有用 | github, mcp-builder |
| 第四梯队 | 6 个 | 按需 | skill-creator, agent-browser |
| Superpowers | 15 个 | 内置 | 直接使用 |

---

**记住**：Skill 是工具，不是负担。用得好能提升效率，但不要为了学而学。

**核心原则**：先解决实际问题，再考虑扩展能力。
