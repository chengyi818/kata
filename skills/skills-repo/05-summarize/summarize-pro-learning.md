---
name: summarize-pro
description: 20 功能 AI 摘要引擎 - 支持文档/会议/邮件/视频转录摘要，多语言/多格式/本地处理，数据不出设备
tier: 第一梯队
source: ClawHub (3.7★ 高评分)
---

# summarize-pro - OpenCode 研发摘要技能

> **编号**: 05
> **梯队**: 第一梯队
> **来源**: ClawHub (Manish Pareek)
> **评分**: 3.7/5.0
> **安装**: `npx clawhub install summarize-pro`

---

## 解决的问题

研发场景中大量信息需要快速消化：
- 📄 技术文档、RFC、Patch 描述动辄数十页
- 🤝 会议记录、讨论线程需要提取决策和待办
- 📧 邮件往来需要快速理解意图和行动项
- 📚 芯片 datasheet、驱动手册信息密度低
- 🌐 外文资料需要翻译 + 摘要双重处理

**summarize-pro** 提供 20 种摘要模式，所有处理在本地完成，数据不出设备。

---

## 核心特性

| 特性 | 说明 |
|------|------|
| 🔒 隐私安全 | 所有数据存储在 `~/.openclaw/summarize-pro/`，无网络请求 |
| 🌍 多语言 | 支持中文、英文、日文、德文等任意语言摘要 |
| 📊 20 种格式 | TL;DR、要点、行动项、会议纪要、邮件摘要等 |
| 📈 进度追踪 | 自动记录摘要历史、统计字数、成就系统 |
| 📝 自定义模板 | 可创建团队专用的摘要格式 |
| 🤖 智能检测 | 自动识别内容类型选择最佳摘要格式 |

---

## 使用场景

### 🎯 场景 1：技术文档快速消化

```
User: summarize this: [粘贴 RFC 文档]

📝 SUMMARY
━━━━━━━━━━━━━━━━━━
• [核心协议变更]
• [向后兼容性影响]
• [实现时间线]
• [参考实现链接]

📊 Stats: 3500 words → 120 words (97% reduction)
```

**价值**：30 分钟阅读 → 30 秒理解核心变更

---

### 🎯 场景 2：会议纪要提取行动项

```
User: action items from this meeting: [粘贴会议记录]

✅ ACTION ITEMS
━━━━━━━━━━━━━━━━━━
□ [修复认证模块 bug] — [张三] — [2026-04-10]
□ [更新 API 文档] — [李四] — [2026-04-12]
□ [性能测试报告] — [王五] — [2026-04-15]

⏰ Deadlines found: 2026-04-10, 2026-04-12, 2026-04-15
👤 People mentioned: 张三，李四，王五
```

**价值**：手动提取 15 分钟 → 自动提取 3 秒

---

### 🎯 场景 3：邮件快速理解

```
User: email summary: [粘贴邮件内容]

📧 EMAIL SUMMARY
━━━━━━━━━━━━━━━━━━
**From:** [sender]
**Subject:** [推断主题]
**Purpose:** [发送目的 - 1 句话]

**Key Points:**
• [要点 1]
• [要点 2]

**Action Required:** [需要做什么]
**Urgency:** 🟡 Medium
```

**价值**：长邮件 3 分钟阅读 → 30 秒判断优先级

---

### 🎯 场景 4：多语言技术文档

```
User: summarize in Chinese: [粘贴英文 datasheet]

📝 SUMMARY (中文)
━━━━━━━━━━━━━━━━━━
• [芯片核心参数]
• [接口协议说明]
• [典型应用场景]
• [注意事项]

📊 2800 words → 150 words
```

**价值**：翻译 + 阅读 20 分钟 → 一步到位 1 分钟

---

### 🎯 场景 5：对比两个技术方案

```
User: compare [方案 A 文档] vs [方案 B 文档]

⚖️ COMPARISON SUMMARY
━━━━━━━━━━━━━━━━━━
| Aspect    | 方案 A          | 方案 B          |
|-----------|----------------|----------------|
| Main Idea | [核心思路]      | [核心思路]      |
| Strength  | [优势]          | [优势]          |
| Weakness  | [劣势]          | [劣势]          |

**Agreement:** [共识点]
**Disagreement:** [分歧点]
**Verdict:** [推荐方案及原因]
```

**价值**：人工对比 1 小时 → 自动对比 1 分钟

---

### 🎯 场景 6：ELI5 理解复杂概念

```
User: eli5: quantum entanglement

🧒 ELI5
━━━━━━━━━━━━━━━━━━
想象你有两个魔法骰子，无论它们相隔多远，
当一个显示 6 时，另一个立刻也显示 6。
它们之间有某种"心灵感应"连接。

量子纠缠就像这样——两个粒子无论距离多远，
改变一个的状态会瞬间影响另一个。

💡 In one sentence: 两个粒子像有心灵感应，
改变一个会瞬间影响另一个。
```

**价值**：复杂概念通俗化，降低学习门槛

---

## 20 种摘要模式速查

| 模式 | 触发词 | 输出 |
|------|--------|------|
| 快速摘要 | `summarize this` | 3-5 要点 |
| TL;DR | `tldr` | 1-2 句话，≤50 词 |
| 要点列表 | `bullet points` | 3-7 条要点 |
| 通俗解释 | `eli5` | 儿童能懂的解释 |
| 核心收获 | `key takeaways` | 按重要性排序的洞察 |
| 行动项 | `action items` | 任务 + 负责人 + 截止日期 |
| 高管摘要 | `executive summary` | 正式商业报告格式 |
| 自定义长度 | `summarize in 50 words` | 精确字数控制 |
| 会议纪要 | `meeting summary` | 讨论/决策/行动项 |
| 邮件摘要 | `email summary` | 发件人/目的/行动/紧急度 |
| 方案对比 | `compare A vs B` | 对比表格 + 推荐 |
| 多语言 | `summarize in Chinese` | 指定语言输出 |
| 对话摘要 | `thread summary` | 话题/共识/待决问题 |
| 章节摘要 | `chapter summary` | 书籍/文档章节概要 |
| 渐进摘要 | `progressive summary` | 一句话→要点→段落 |
| 保存摘要 | `save summary` | 收藏摘要 |
| 查看收藏 | `show saved summaries` | 浏览已保存 |
| 历史记录 | `summary history` | 过往摘要列表 |
| 使用统计 | `summary stats` | 字数/成就/ streak |
| 自定义模板 | `create template [name]` | 团队专用格式 |

---

## 安装与配置

### 安装
```bash
npx clawhub install summarize-pro
```

### 数据存储位置
```
~/.openclaw/summarize-pro/
├── settings.json    # 用户偏好和统计
├── history.json     # 摘要历史记录
├── saved.json       # 收藏的摘要
└── templates.json   # 自定义模板
```

### 首次运行
技能会自动创建配置目录和初始化文件，无需手动配置。

---

## 典型工作流

### 工作流 1：每日技术资讯消化
```
1. 收集：复制 5-10 篇技术文章链接/内容
2. 批量摘要：对每篇说 "tldr: [内容]"
3. 筛选：标记值得深入阅读的
4. 深入：对标记的文章说 "key takeaways: [内容]"
5. 保存：对重要摘要说 "save summary"
```

### 工作流 2：会议后快速分发
```
1. 粘贴会议记录：`meeting summary: [记录]`
2. 提取行动项：`action items: [记录]`
3. 保存摘要：`save summary`
4. 分享给参会者
```

### 工作流 3：外文文档学习
```
1. 复制英文文档
2. `summarize in Chinese: [内容]`
3. 对关键概念 `eli5: [概念]`
4. 保存重要摘要供复习
```

---

## 隐私与安全

**所有数据本地处理**：
- ✅ 无网络请求
- ✅ 无 API 调用
- ✅ 数据不出设备
- ✅ 仅读写 `~/.openclaw/summarize-pro/` 目录

**权限说明**：
- `read`：读取本地配置和历史记录
- `write`：保存摘要和更新统计

---

## 适用人群

| 人群 | 价值 |
|------|------|
| 嵌入式开发 | 快速消化 datasheet、驱动文档、内核 RFC |
| 全栈开发 | 处理技术文档、会议记录、邮件往来 |
| 技术管理 | 快速理解团队报告、提取决策要点 |
| 学习者 | ELI5 模式降低复杂概念理解门槛 |
| 多语言环境 | 翻译 + 摘要一步完成 |

---

## 限制与注意

| 限制 | 说明 |
|------|------|
| 输入长度 | 受 AI 模型上下文窗口限制，超长文档需分段 |
| 准确性 | 摘要不会添加原文没有的信息，但可能遗漏细节 |
| 格式识别 | 自动检测可能误判，可手动指定格式 |
| 语言支持 | 小语种可能效果不佳 |

---

## 相关 Skill

参考 [opencode-skill-list.md](../opencode-skill-list.md) 获取完整清单和学习路径。

---

## 作者信息

**Built by**: Manish Pareek ([@Mkpareek19_](https://x.com/Mkpareek19_))

**License**: MIT-0 (免费使用、修改、分发，无需署名)

**版本**: 1.0.0
