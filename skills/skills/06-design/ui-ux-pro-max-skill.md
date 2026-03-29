# ui-ux-pro-max-skill

## 问题背景

AI 生成的界面设计通常缺乏专业水准——配色不协调、字体搭配随意、组件规格不统一。本 skill 提供系统化的设计规范，让 AI 输出达到专业设计师水准。

## 安装

```bash
mkdir -p ~/.config/opencode/skills/ui-ux-pro-max-skill
# 需手动创建 SKILL.md 文件，内容参考下方"使用方式"章节
```

## 命令

### 生成配色方案

```
generate-palette --style modern
```

根据风格关键词生成主色、辅助色、中性色及语义色板，附带 WCAG 对比度标注。

### 字体搭配建议

```
font-pairing --scenario landing
```

按使用场景（落地页、仪表盘、博客等）推荐标题+正文字体组合及字号阶梯。

### 组件规范

```
component-spec --type button
```

输出指定组件的设计规范：尺寸、间距、圆角、状态变体、暗色模式适配。

### 交互设计指南

```
interaction-guide --pattern modal
```

提供交互模式（模态框、表单验证、导航、动效）的 UX 最佳实践。

### 完整设计系统

```
design-system --theme <关键词>
```

一站式输出配色、字体、组件库、间距系统的完整设计系统文档。
