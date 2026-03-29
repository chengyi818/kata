# obsidian

## 问题背景

Obsidian 知识库管理依赖图形界面，无法批量操作或自动化，效率受限。该技能通过命令行操作 Vault，实现笔记的快速创建、搜索和管理。

## 安装

```bash
git clone --depth 1 --filter=blob:none --sparse https://github.com/openclaw/skills.git /tmp/openclaw-skills
cd /tmp/openclaw-skills
git sparse-checkout set skills/0x-cryptopriest/obsidian-cli-skills
cp -r skills/0x-cryptopriest/obsidian-cli-skills ~/.config/opencode/skills/obsidian
rm -rf /tmp/openclaw-skills
```

需要预先安装 obsidian-cli 或配置 Vault 路径。

## 命令说明

### 创建笔记

指定标题、内容和目标文件夹，自动创建 Markdown 笔记并添加 frontmatter 元数据。

### 读取笔记

按路径或笔记标题读取内容，支持返回全文或仅返回 frontmatter 信息。

### 搜索笔记

按关键词、标签或正则表达式搜索 Vault 中的笔记，返回匹配结果和上下文片段。

### 管理标签和链接

批量添加、删除或重命名标签，管理笔记间的双向链接，维护知识图谱完整性。

### 批量操作

对 Vault 中的笔记执行批量重命名、移动、导出或格式转换，支持条件过滤。
