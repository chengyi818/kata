---
name: byterover
type: dev-memory
tier: 5 - 低优先级
purpose: "Agent知识管理，项目模式存储检索"
---
# Byterover

## 问题与背景

项目中的设计决策、代码模式、踩坑经验散落各处，新成员或 AI 无法快速获取这些隐性知识。Byterover 提供结构化的项目知识库管理，让团队和 AI 能够高效存储与检索项目级别的模式和经验。

## 安装

```bash
git clone --depth 1 --filter=blob:none --sparse https://github.com/openclaw/skills.git /tmp/openclaw-skills
cd /tmp/openclaw-skills
git sparse-checkout set skills/byteroverinc/byterover
cp -r skills/byteroverinc/byterover ~/.config/opencode/skills/byterover
rm -rf /tmp/openclaw-skills
```

## 命令说明

### brv store（存储项目模式）

将设计决策、代码模式、最佳实践和踩坑经验以结构化方式存储到项目知识库中。支持标签分类和上下文关联。

### brv retrieve（检索相关模式）

根据当前开发上下文，从知识库中检索最相关的模式和经验。支持关键词搜索和语义匹配。

### 项目知识库管理

提供知识库的初始化、导入导出、清理和统计功能。支持团队共享和个人知识库分离。

## 使用示例

```bash
# 初始化项目知识库
brv init

# 存储一个模式
brv store --title "API 错误处理" --tags "backend,error-handling"

# 检索相关模式
brv retrieve "如何处理 API 超时"

# 导出知识库
brv export --format markdown
```
