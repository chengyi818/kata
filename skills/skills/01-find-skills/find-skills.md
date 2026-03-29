---
name: find-skills
type: search
tier: 1 - 必须掌握
purpose: "发现并安装需要的skill"
---
# find-skills

## 问题背景

不知道有哪些 Skill 可用，手动在 ClawHub 上翻找效率低，尤其当仓库规模不断增长时，难以快速定位所需功能。

## 安装

```bash
mkdir -p ~/.config/opencode/skills/find-skills
# 需手动创建 SKILL.md 文件，内容参考下方"使用方式"章节
```

## 使用方法

直接用自然语言描述你的需求，例如：

- "找个能抓网页的 skill"
- "有没有文件管理相关的 skill"
- "搜索 PDF 处理工具"

Skill 会自动搜索 ClawHub 仓库，返回匹配结果及对应的安装命令，省去手动查找的时间。

## 返回内容

- 匹配的 Skill 名称及简介
- 相关标签与分类
- 一键安装命令（可直接复制执行）

## 适用场景

- 初次接触 ClawHub，不了解生态
- 已有明确需求，想快速找到对应工具
- 定期探索新增 Skill，保持工具链更新
