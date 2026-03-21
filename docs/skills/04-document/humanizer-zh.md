# Humanizer-ZH

## 解决的问题

英文 Humanizer 不懂中文语境。中文 AI 文本有独特的套路感——"在当今社会""随着科技的发展""总而言之"等。Humanizer-ZH 针对中文特有模式进行检测和优化。

## 安装

```bash
mkdir -p ~/.config/opencode/skills/humanizer-zh
# 需手动创建 SKILL.md 文件，内容参考下方"使用方式"章节
```

## 命令

### 扫描中文 AI 痕迹

从 4 大类、24 个维度分析中文文本的 AI 特征。
```bash
humanizer-zh scan article.txt
```

四大检测类别：

- **内容层面**：空洞论述、过度概括、虚假权威引用
- **语言层面**：书面语堆砌、四字成语滥用、句式单一
- **风格层面**：情感不自然、语气前后不一致、过度谦虚或自信
- **对话习惯**：自问自答、过度列举、机械总结

### 自动优化

将检测到的问题自动改写为更自然的中文表达。
```bash
humanizer-zh optimize draft.txt -o revised.txt
```

### 对比输出

显示原文和优化后的差异，方便逐条审核修改。
```bash
humanizer-zh optimize draft.txt --diff
```

### 指定语境

可指定文本类型，如 `blog`（博客）、`formal`（正式公文）、`social`（社媒文案）。
```bash
humanizer-zh optimize post.txt --context blog
```
