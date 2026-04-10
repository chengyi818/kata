# Everything Claude Code (ECC) 资料库

> **来源**: [affaan-m/everything-claude-code](https://github.com/affaan-m/everything-claude-code)
> 
> **状态**: 140K+ stars, 21K+ forks, Anthropic 黑客松获胜作品
> 
> **更新**: 2026-04

---

## 文档导航

| 编号 | 文档 | 内容 |
|:----:|------|------|
| 01 | [ECC-SKILLS.md](01-ECC-SKILLS.md) | 34 个精选 Skills 清单 |
| 02 | [ECC-AGENTS.md](02-ECC-AGENTS.md) | 36 个专用 Agents 详解 |
| 03 | [ECC-COMMANDS.md](03-ECC-COMMANDS.md) | 47 个 Commands 详解 |
| 04 | [ECC-RULES.md](04-ECC-RULES.md) | Rules 规范与 Hooks |
| 05 | [ECC-INSTALL.md](05-ECC-INSTALL.md) | 完整安装指南 |
| 06 | [ECC-TOOLS.md](06-ECC-TOOLS.md) | 生态系统工具 |

---

## 快速开始

### 1. 安装插件

```bash
/plugin marketplace add affaan-m/everything-claude-code
/plugin install ecc@ecc
```

### 2. 安装 Rules（必需）

```bash
git clone https://github.com/affaan-m/everything-claude-code.git
cd everything-claude-code
./install.sh --profile full
```

### 3. 开始使用

```bash
/ecc:plan "添加用户认证"
/security-scan
```

---

## 核心组件

### Skills (181+)

工作流定义与领域知识库，按任务类型委派。

**嵌入式相关精选**:
- 语言专属：C++/Rust/Perl/Python 编码标准
- 安全质量：AgentShield 安全扫描
- 工作流：search-first、autonomous-loops
- 持续学习：continuous-learning-v2

### Agents (36 个)

专用子智能体，专业化处理委托任务。

**通用 Agents**: planner, architect, code-reviewer, build-error-resolver

**语言 Reviewers**: cpp, go, rust, java, python, typescript

### Commands (47 个)

传统斜杠命令，快速操作。

**核心**: `/tdd`, `/plan`, `/code-review`, `/build-fix`

**持续学习**: `/learn`, `/instinct-status`, `/evolve`

**多智能体**: `/multi-plan`, `/multi-execute` (需 ccg-workflow)

### Rules & Hooks

- **Rules**: 必须遵守的规范（common + 语言专属）
- **Hooks**: 自动化触发器（会话管理、上下文精简）

---

## 生态系统工具

### AgentShield

安全审计工具，1282 项测试，98% 覆盖率。

```bash
npx ecc-agentshield scan
npx ecc-agentshield scan --fix
npx ecc-agentshield scan --opus  # 深度分析
```

### 技能创建器

从 Git 历史生成 Skills。

```bash
/skill-create
/skill-create --instincts
```

### 持续学习 v2

基于本能的学习系统。

```bash
/instinct-status
/instinct-import <file>
/evolve
```

---

## 嵌入式开发推荐配置

### 必装 Skills

| Skill | 用途 |
|-------|------|
| cpp-coding-standards | C++ 内核模块规范 |
| rust-reviewer | Rust 代码审查 |
| perl-patterns | 内核脚本模式 |
| security-scan | 安全审计 |
| search-first | 先调研再编码 |

### 必装 Rules

```bash
cp -r rules/common ~/.claude/rules/
cp -r rules/golang ~/.claude/rules/   # 或 rust/cpp/perl
```

### 推荐 Agents

- `code-reviewer` - 补丁审查
- `build-error-resolver` - 编译错误修复
- `security-reviewer` - 安全分析

---

## 与其他 Skill 集合对比

| 特性 | ECC | Superpowers | 原生 |
|------|-----|-------------|------|
| Skills | 181+ | 15 | 10+ |
| Agents | 36+ | 15 | 5-8 |
| Commands | 47+ | 0 | 10+ |
| Hooks | ✅ | ❌ | ⚠️ |
| 持续学习 | ✅ | ❌ | ❌ |
| 安全扫描 | ✅ | ❌ | ❌ |

**推荐组合**: Superpowers（核心工作流）+ ECC（语言规范/Agents/安全）

---

## 注意事项

### 上下文窗口

- 配置 20-30 个 MCP
- 每项目启用 <10 个
- 活动工具 <80 个

### multi-* 命令

需要额外安装：`npx ccg-workflow`

### 钩子自动加载

Claude Code v2.1+ 自动加载 `hooks/hooks.json`，勿在 `plugin.json` 重复声明。

---

## 相关链接

| 资源 | 链接 |
|------|------|
| GitHub 仓库 | https://github.com/affaan-m/everything-claude-code |
| ECC 简明指南 | https://x.com/affaanmustafa/status/2012378465664745795 |
| ECC 详细指南 | https://x.com/affaanmustafa/status/2014040193557471352 |
| AgentShield 指南 | https://x.com/affaanmustafa/status/2033263813387223421 |
| AgentShield GitHub | https://github.com/affaan-m/agentshield |

---

**最后更新**: 2026-04
