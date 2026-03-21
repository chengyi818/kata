# Summarize

## 解决的问题

长文、论文、视频信息量大，手动阅读耗时。需要快速提炼核心内容，跳过冗余信息直达要点。

## 安装

```bash
git clone --depth 1 https://github.com/steipete/summarize.git ~/.config/opencode/skills/summarize
npm i -g @steipete/summarize
```

## 命令

### summarize "URL"

摘要网页内容，输入任意网页链接即可获取结构化摘要。
```bash
summarize "https://example.com/article"
```

### summarize file.pdf

摘要本地 PDF 文件，自动提取文本并生成摘要。
```bash
summarize paper.pdf
```

### summarize "YouTube 链接"

提取视频字幕/转录内容，生成视频摘要。
```bash
summarize "https://youtube.com/watch?v=xxxxx"
```

### --length short/long/xl

控制摘要长度。`short` 极简要点，`long` 详细概括，`xl` 完整分析。
```bash
summarize "https://example.com" --length long
```

### --json

JSON 格式输出，方便程序化处理和管道调用。
```bash
summarize report.pdf --json
```

### --extract-only

仅提取原文，不做摘要处理。适合需要纯净文本的场景。
```bash
summarize article.pdf --extract-only
```
