# Humanizer

## 解决的问题

AI 生成的文本有明显的套路痕迹——"值得注意的是""综上所述"、过度使用 em dash、三段式结构等。读起来像机器写的，缺乏人味。Humanizer 帮你把这些痕迹扫出来并改写为自然表达。

## 安装

```bash
git clone --depth 1 --filter=blob:none --sparse https://github.com/openclaw/skills.git /tmp/openclaw-skills
cd /tmp/openclaw-skills
git sparse-checkout set skills/biostartechnology/humanizer
cp -r skills/biostartechnology/humanizer ~/.config/opencode/skills/humanizer
rm -rf /tmp/openclaw-skills
```

## 命令

### 扫描 AI 写作痕迹

分析文本中常见的 AI 写作模式，标记问题所在。
```bash
humanizer scan article.txt
```

扫描覆盖以下类别：

- **夸大象征**：过度使用绝对化表述和宏大叙事
- **促销语言**：堆砌形容词和号召性用语
- **em dash 滥用**：不必要的破折号插入
- **三段式套路**：开头-展开-总结的机械结构

### 自动改写

检测到问题后，自动将文本改写为更自然的表达。
```bash
humanizer rewrite article.txt -o revised.txt
```

### 边扫描边改写

一步完成扫描和改写，输出修改前后的对比。
```bash
humanizer fix draft.md --diff
```

### 指定风格

可指定目标风格，如 `casual`（口语化）、`professional`（专业但不僵硬）。
```bash
humanizer rewrite essay.txt --style casual
```
