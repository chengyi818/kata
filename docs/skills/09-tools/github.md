# github

## 问题背景

GitHub 操作（查看 Issue、创建 PR、检查 CI 状态）需要离开终端打开浏览器，打断开发工作流。该技能基于 gh CLI，将常用 GitHub 操作留在终端内完成。

## 安装

```bash
brew install gh
# 或
apt install gh

git clone --depth 1 --filter=blob:none --sparse https://github.com/openclaw/skills.git /tmp/openclaw-skills
cd /tmp/openclaw-skills
git sparse-checkout set skills/164149043/github-tools
cp -r skills/164149043/github-tools ~/.config/opencode/skills/github
rm -rf /tmp/openclaw-skills
```

安装后需要运行 `gh auth login` 完成认证。

## 命令说明

### gh issue

创建、查看和管理 Issue。支持添加标签、指派负责人、关闭和评论操作。

### gh pr

创建 Pull Request、查看 PR 详情、执行 Code Review、合并 PR。支持指定分支和审查人。

### gh run

查看 GitHub Actions 工作流运行状态，获取构建日志和失败原因，便于快速定位 CI 问题。

### gh api

调用 GitHub REST API，执行高级查询操作，适用于批量处理和自定义工作流。
