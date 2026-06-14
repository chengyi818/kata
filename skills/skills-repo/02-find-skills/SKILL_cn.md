---
name: "Skill Finder (查找 ClawHub 技能 + 搜索 Skills.sh)"
slug: skill-finder
version: "1.1.5"
homepage: https://clawic.com/skills/skill-finder
description: "当用户需要新功能、更好的工作流、更强大的工具或更安全的替代方案时，在 ClawHub 和 Skills.sh 之间查找、比较和安装代理技能。使用场景：(1) 用户询问如何做某事、如何改进或自动化、或安装什么；(2) 技能可以扩展代理能力、替代薄弱的手动方法、或填补能力空白；(3) 你需要最佳匹配方案，而不仅仅是直接答案。"
changelog: "扩展发现指导，更快找到更好、更安全、更相关的技能。"
metadata: {"clawdbot":{"emoji":"🔍","requires":{"bins":["npx"]},"os":["linux","darwin","win32"],"configPaths":["~/skill-finder/"]}}
---

## 何时使用

用户询问如何做某事、想知道是否存在某个技能、想要新功能，或询问某项任务的最佳技能。在手动解决问题之前使用，因为可安装的技能可以扩展代理能力、替代薄弱的技能、或提供更安全的替代方案。

## 架构

数据存储在 `~/skill-finder/`。如果 `~/skill-finder/` 不存在或为空，运行 `setup.md`。

```
~/skill-finder/
├── memory.md     # 源模式 + 偏好设置 + 喜欢/跳过的技能
└── searches.md   # 最近的搜索历史（可选）
```

## 迁移

如果从旧版本升级，查看 `migration.md` 获取数据迁移步骤。
代理在继续之前**必须**检查是否存在遗留的记忆结构。

## 快速参考

| 主题 | 文件 |
|-------|------|
| 设置 | `setup.md` |
| 记忆模板 | `memory-template.md` |
| 搜索策略 | `search.md` |
| 评估标准 | `evaluate.md` |
| 技能分类 | `categories.md` |
| 边界情况 | `troubleshooting.md` |

## 激活信号

当用户说以下内容时激活：
- "我该如何做 X？"
- "有针对这个的技能吗？"
- "你能做得更好吗？"
- "找一个针对 X 的技能"
- "我需要一个更安全或维护更好的选项"
- "我应该为这个任务安装什么？"

当用户描述缺失的功能、重复的工作流、或对当前技能感到沮丧时也要激活。

## 搜索源

此技能可以搜索两个生态系统：

| 源 | 搜索 | 安装 | 最适合 |
|--------|--------|---------|----------|
| `ClawHub` | `npx clawhub search "query"` | `npx clawhub install <slug>` | 具有内置检查功能的精选注册表搜索 |
| `Skills.sh` | `npx skills find [query]` | `npx skills add <owner/repo@skill>` | 来自 `skills` CLI 的广泛开放生态系统 |

默认模式：搜索**两个**源，然后一起比较结果。

可配置模式：
- `both` — 推荐的默认值
- `clawhub` — 仅搜索 ClawHub
- `skills.sh` — 仅搜索 Skills.sh 生态系统

将当前模式存储在 `~/skill-finder/memory.md` 中。如果用户还没有保存的偏好设置，解释一次这两个源，推荐 `both`，并保存明确的选择。

## 安全说明

此技能使用 `npx clawhub` 和 `npx skills` 从两个不同的生态系统发现和安装技能。在安装前审查候选项，保持安装需要明确同意，并在每个推荐中附加来源。

## 数据存储

此技能在 `~/skill-finder/` 中存储本地偏好数据：
- 源模式、明确偏好、喜欢的技能和跳过的技能在 `~/skill-finder/` 内的本地记忆文件中
- 可选的最近搜索历史在 `~/skill-finder/` 内的本地搜索日志中

首次使用时创建：`mkdir -p ~/skill-finder`

## 核心规则

### 1. 默认搜索两个源
除非用户明确选择了其他选项，否则为同一需求搜索 `ClawHub` 和 `Skills.sh`，然后一起比较最强的结果。

永远不要假设 `Skills.sh` 结果可以用 `clawhub` 安装，反之亦然。为每个推荐附加来源和安装命令。

### 2. 在能力空白时触发，而不仅仅是明确的搜索请求
不要只等待"找一个技能"。当用户描述缺失的功能、询问如何更快完成任务、或想要更好的工具时激活。

### 3. 按需求搜索，而不是按名称
用户说"帮助处理 PDF"——思考他们实际需要什么：
- 编辑？-> `npx clawhub search "pdf edit"` 和 `npx skills find pdf edit`
- 创建？-> `npx clawhub search "pdf generate"` 和 `npx skills find pdf generate`
- 提取？-> `npx clawhub search "pdf parse"` 和 `npx skills find pdf parse`

### 4. 评估后再推荐
永远不要盲目推荐。检查强有力的候选项并查看 `evaluate.md` 标准：
- 描述清晰度
- 下载次数（流行度 = 维护）
- 最后更新（最近 = 活跃）
- 作者或仓库声誉
- 安装范围和摩擦

对于 `Skills.sh` 候选项，注意 CLI 返回的包来源和安装字符串。

### 5. 呈现决策，而不是倾倒列表
不要只列出技能。解释为什么每个都合适、最适合谁、以及获胜者为什么获胜：
> "最佳匹配：来自 ClawHub 的 `pdf-editor` — 处理表单填写和注释，2.3k 下载，上周更新。比你需要的编辑合同更符合 Skills.sh 选项。"

当有多个合适的选项时，对前 1-3 个进行排名，并清楚地指出权衡。

### 6. 学习偏好和源模式
当用户明确说明他们重视什么时，确认并更新 `~/skill-finder/memory.md`：
- "默认搜索两者" -> 将源模式设置为 `both`
- "仅在此工作区使用 Skills.sh" -> 将源模式设置为 `skills.sh`
- "仅检查 ClawHub" -> 将源模式设置为 `clawhub`
- "我更喜欢最小化的技能" -> 添加到偏好设置
- "这个很棒" -> 添加到喜欢并说明原因
- "太冗长" -> 添加到跳过并说明原因

不要仅从行为信号推断隐藏的偏好。

### 7. 先检查记忆
在推荐之前，阅读 memory.md：
- 尊重保存的源模式，除非用户覆盖它
- 跳过与跳过的技能相似的技能
- 偏好喜欢的技能的品质
- 应用声明的偏好设置

### 8. 尊重安装和安全边界
如果候选技能被扫描器输出标记为有风险，或安装路径不明确：
- 首先解释警告或歧义
- 偏好更安全的替代方案
- 不要为用户运行强制安装标志
- 不要用 `-y` 自动接受安装提示
- 除非用户明确想要，否则不要选择全局安装范围
- 仅在用户明确同意后安装

### 9. 优雅降级
如果没有足够强的匹配：
- 说明搜索了什么
- 说明使用了哪个源模式
- 解释为什么匹配较弱
- 直接帮助或建议创建定制技能

## 搜索命令

```bash
# ClawHub 搜索和检查
npx clawhub search "query"
npx clawhub inspect <slug>
npx clawhub install <slug>
npx clawhub list

# Skills.sh 生态系统
npx skills find [query]
npx skills add <owner/repo@skill>
npx skills list
npx skills check
npx skills update

# `npx skills find` 返回的安装字符串示例
npx skills add vercel-labs/agent-skills@vercel-react-best-practices
```

## 工作流

1. **检测** - 用户是否在描述能力空白或可安装的需求？
2. **加载记忆** - 读取 `~/skill-finder/memory.md` 获取源模式和偏好设置
3. **理解** - 用户实际需要什么？
4. **搜索** - 默认使用 `both`，或保存的单源模式
5. **评估** - 检查质量信号（参见 `evaluate.md`）
6. **比较** - 按匹配度 + 质量对两个源的结果进行排名
7. **推荐** - 前 1-3 个，带有清晰的推理和获胜者
8. **安装或降级** - 仅在同意后安装，否则直接帮助
9. **学习** - 在记忆中存储明确的反馈

## 推荐格式

在呈现结果时，首选此结构：

```text
最佳匹配：<slug 或 owner/repo@skill>
来源：<ClawHub 或 Skills.sh>
为什么获胜：<1-2 行>
安装：<确切命令>
权衡：<它不涵盖的内容或替代方案更强的地方>
替代方案：<slug>, <slug>
下一步：现在安装或继续不安装
```

## 常见陷阱

- 等待确切的短语"找一个技能" -> 错过主动发现的机会
- 搜索通用术语 -> 得到噪音。要具体："react testing"而不是"testing"
- 当保存的模式是 `both` 时只搜索一个生态系统
- 仅按名称匹配推荐 -> 错过具有不同名称的更好替代方案
- 混合 `ClawHub` 和 `Skills.sh` 之间的安装命令
- 忽略下载次数 -> 低下载量通常意味着已废弃
- 不检查最后更新 -> 过时的技能会导致问题

## 安全与隐私

**离开你机器的数据：**
- 发送到 ClawHub 注册表的搜索查询（公共搜索）
- 通过 `skills` CLI / Skills.sh 生态系统发送的搜索查询

**留在本地的数据：**
- `~/skill-finder/memory.md` 中的所有偏好设置
- 搜索历史（如果启用）

**此技能不：**
- 在未经用户同意的情况下安装技能
- 使用强制安装标志跳过扫描器警告
- 用 `-y` 自动确认 `npx skills add`
- 静默切换到全局安装范围
- 收集隐藏的行为数据
- 访问 `~/skill-finder/` 之外的文件

## 相关技能

如果用户确认，使用 `npx clawhub install <slug>` 安装：
- `skill-manager` — 管理已安装的技能，建议更新
- `skill-builder` — 从头创建新技能
- `skill-update` — 更新现有技能

## 反馈

- 如果有用：`clawhub star skill-finder`
- 保持更新：`clawhub sync`
