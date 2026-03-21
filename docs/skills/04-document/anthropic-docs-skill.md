# Anthropic Docs Skill

## 解决的问题

处理 Word、PPT、Excel、PDF 等办公文件需要多个工具，格式转换麻烦。这个技能统一了文档操作入口，一个工具搞定常见办公文件处理。

## 安装

```bash
mkdir -p ~/.config/opencode/skills/anthropic-docs-skill
# 需手动创建 SKILL.md 文件，内容参考下方"使用方式"章节
```

## 命令

### 读取 / 写入 Word 文档

读取 `.docx` 内容，或创建 / 修改 Word 文档。
```bash
docs read report.docx
docs write report.docx "第一章 审计报告"
```

### 生成 PPT

根据大纲或 Markdown 内容自动生成演示文稿。
```bash
docs ppt slides.pptx --from outline.md
```

### 操作 Excel 表格

读取、写入、筛选 Excel 数据，支持公式和格式设置。
```bash
docs excel data.xlsx --read
docs excel data.xlsx --write "A1=名称,B1=金额"
```

### PDF 速读

快速提取 PDF 核心内容，生成精简摘要。
```bash
docs pdf summarize paper.pdf
```

### PDF 翻译

将 PDF 内容翻译为指定语言，保留原始排版结构。
```bash
docs pdf translate paper.pdf --to zh
```

### PDF 提取

从 PDF 中提取文本、图片或表格数据。
```bash
docs pdf extract report.pdf --text
docs pdf extract report.pdf --tables -o data.csv
```
