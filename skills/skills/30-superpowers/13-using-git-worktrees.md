---
name: using-git-worktrees
type: process
tier: 内置
purpose: "Git Worktree隔离开发 - 同一仓库多分支并行工作，互不干扰"
---

# Using Git Worktrees

## 作用

用 git worktree 在同一仓库中创建隔离的工作目录，每个 worktree 对应一个分支，共享 git 历史。适合同时处理多个功能或在不同版本间切换。

## 使用场景

- 开始新功能但当前工作区有未完成的修改
- 需要在多个版本间并行调试
- 执行实施计划前创建隔离环境

## 流程

1. **选择目录** — 按优先级查找：
   - `.worktrees/` (推荐)
   - `worktrees/`
   - CLAUDE.md 中指定的位置
2. **安全验证** — 确认目录干净、无冲突
3. **创建 worktree** — `git worktree add <path> <branch>`
4. **在 worktree 中工作** — 完全隔离的文件系统
5. **完成后清理** — `git worktree remove <path>`

## 命令速查

```bash
# 列出所有 worktrees
git worktree list

# 创建新 worktree（新分支）
git worktree add ../feature-x -b feature/x

# 创建已有分支的 worktree
git worktree add ../hotfix ../hotfix-branch

# 删除 worktree
git worktree remove ../feature-x
```

## 优势

- 共享同一 git 仓库，不占用额外空间
- 各 worktree 的修改完全隔离
- 编译缓存独立，不互相污染
