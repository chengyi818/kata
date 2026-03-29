---
name: self-improving-agent
type: dev-memory
tier: 1 - 必须掌握
purpose: "跨会话记住经验，调试过的错误不再犯"
---
# Self-Improving Agent

## 问题与背景

AI 每次对话都从零开始，之前犯过的错误会重复犯，用户的偏好每次都要重新说明。这导致交互效率低下，用户体验差。Self-Improving Agent 通过自动捕获错误和修正、记录用户偏好、跨会话持久化学习成果，让 AI 真正具备"成长"能力。

## 安装

```bash
git clone --depth 1 --filter=blob:none --sparse https://github.com/openclaw/skills.git /tmp/openclaw-skills
cd /tmp/openclaw-skills
git sparse-checkout set skills/991200448/self-improving-agent-3-0-0
cp -r skills/991200448/self-improving-agent-3-0-0 ~/.config/opencode/skills/self-improving-agent
rm -rf /tmp/openclaw-skills
```

## 命令说明

### 自动捕获错误与修正

在对话过程中自动检测 AI 回答中的错误，记录修正方案。下次遇到类似问题时，Agent 会主动参考历史修正结果，避免重复犯错。

### 记录用户偏好

自动学习并持久化用户的编码风格、命名习惯、工具偏好等设置。跨会话保持一致的个性化体验，无需用户反复说明。

### 跨会话持久化学习成果

将学习到的知识和偏好存储在本地知识库中，支持跨项目复用。每次新会话启动时自动加载历史学习成果，实现持续改进。

## 使用示例

```bash
# 启用自动学习
self-improving-agent enable

# 查看已记录的偏好
self-improving-agent show-preferences

# 清除学习记录
self-improving-agent reset
```
