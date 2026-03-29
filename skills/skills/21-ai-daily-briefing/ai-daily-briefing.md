---
name: ai-daily-briefing
type: productivity
tier: 5 - 低优先级
purpose: "AI每日简报"
---
# ai-daily-briefing

## 问题背景

每天需要查看日历、待办任务、邮件和新闻，信息分散在多个平台，汇总耗时。本 skill 聚合多源信息，一键生成结构化每日晨报。

## 安装

```bash
mkdir -p ~/.config/opencode/skills/ai-daily-briefing
# 需手动创建 SKILL.md 文件，内容参考下方"使用方式"章节
```

## 命令

### 每日晨报

```
briefing
```

一键生成今日晨报，包含：

- **逾期任务**：来自任务管理工具的超期事项
- **今日日历**：当日所有会议和日程
- **优先事项**：按紧急程度排序的待办
- **天气**：当前位置今日天气概况

### 周预览

```
weekly preview
```

生成本周概览：重要截止日期、会议分布、未完成任务趋势、本周优先级建议。

### 指定信息源

```
briefing --sources calendar,tasks
```

仅从指定来源拉取数据，可选 `calendar`、`tasks`、`email`、`news`。

### 静默模式

```
briefing --quiet
```

生成精简版晨报，仅显示高优先级事项，适合快速扫读。
