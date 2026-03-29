# Nano PDF

## 解决的问题

修改 PDF 通常需要 Adobe Acrobat 等重型软件，即使只是简单编辑也得打开图形界面。nano-pdf 让你用自然语言指令直接操作 PDF。

## 安装

```bash
mkdir -p ~/.config/opencode/skills/nano-pdf
# 需手动创建 SKILL.md 文件，内容参考下方"命令"章节
```

安装依赖 CLI 工具：

```bash
npm i -g @steipete/nano-pdf
```

Skill 目录创建后，OpenCode 会自动识别 `~/.config/opencode/skills/` 下的 SKILL.md。

## 命令

### 自然语言编辑

用自然语言描述你想要的修改，nano-pdf 会解析指令并执行。
```bash
nano-pdf edit report.pdf "修改第二段中的错别字，把'的得'改成'得到'"
```

### 文本修改

指定页码和修改内容，直接编辑 PDF 中的文本。
```bash
nano-pdf edit contract.pdf "将第1页标题改为 2026年度报告"
```

### 页面提取

从 PDF 中提取指定页面，生成新的 PDF 文件。
```bash
nano-pdf extract report.pdf --pages 3-5 -o excerpt.pdf
```

### PDF 合并

将多个 PDF 文件合并为一个。
```bash
nano-pdf merge part1.pdf part2.pdf part3.pdf -o combined.pdf
```

### 其他操作

支持删除页面、重排页面顺序、添加水印等操作，均可通过自然语言指令完成。
```bash
nano-pdf edit doc.pdf "删除第2页"
nano-pdf edit doc.pdf "把第4页移到第1页前面"
```
