# Skill Creator

## 问题与背景

重复性的工作流无法复用，每次都需要重新向 AI 说明步骤和规则。Skill Creator 提供标准化的 Skill 创建流程，帮助用户将常用工作流封装为可复用的 Skill，实现一次定义、永久使用。

## 安装

```bash
git clone --depth 1 --filter=blob:none --sparse https://github.com/openclaw/skills.git /tmp/openclaw-skills
cd /tmp/openclaw-skills
git sparse-checkout set skills/chindden/skill-creator
cp -r skills/chindden/skill-creator ~/.config/opencode/skills/skill-creator
rm -rf /tmp/openclaw-skills
```

## 命令说明

### 引导创建 SKILL.md

交互式引导用户创建规范的 SKILL.md 文件，自动填充必要的元数据字段。确保生成的 Skill 符合平台标准格式。

### 定义触发条件

帮助用户定义 Skill 的触发场景和匹配规则。支持关键词匹配、文件类型过滤和上下文条件组合。

### 编写工作流内容

提供结构化的工作流编辑界面，支持分步骤定义、条件分支和工具调用配置。可预览工作流执行效果。

### 验证 Skill 格式

自动检查 Skill 文件的格式完整性、触发条件有效性和工作流逻辑正确性。输出详细的验证报告和修复建议。

## 使用示例

```bash
# 启动 Skill 创建向导
skill-creator new

# 验证现有 Skill 文件
skill-creator validate ./skills/my-skill/SKILL.md

# 从模板创建 Skill
skill-creator from-template --name "代码审查" --category review
```
