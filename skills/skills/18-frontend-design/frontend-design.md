---
name: frontend-design
type: design
tier: 5 - 低优先级
purpose: "React/Tailwind前端设计"
---
# frontend-design

## 问题背景

AI 生成的前端代码千篇一律，缺少设计感——布局单调、缺乏层次、配色模板化。本 skill 注入专业设计原则，让输出接近成熟产品的视觉品质。

## 安装

```bash
mkdir -p ~/.config/opencode/skills/frontend-design
# 需手动创建 SKILL.md 文件，内容参考下方"使用方式"章节
```

## 命令

### 创建界面

```
design <页面描述>
```

根据自然语言描述生成高质量前端界面代码，自动应用排版、间距、配色最佳实践。

### 指定技术栈

```
design <描述> --stack react
```

支持 `react`、`vue`、`html`、`svelte`，按项目技术栈输出对应代码。

### 避免 AI 模板感

```
design <描述> --premium
```

启用高级模式：更精细的渐变、微交互、层次阴影、动态布局。

### 响应式布局

```
design <描述> --responsive
```

输出包含移动端适配的响应式断点代码。

### 组件复用

```
design <描述> --components
```

将界面拆分为可复用组件，输出独立组件文件而非单文件。
