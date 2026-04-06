---
name: tmux
description: Remote-control tmux sessions for interactive CLIs - OpenCode 多会话编排、长时任务监控、远程研发持久化
tier: 第一梯队
source: ClawHub + OpenCode 实践
---

# tmux Skill - OpenCode 研发效率提升指南

> **编号**: 04
> **梯队**: 第一梯队
> **来源**: ClawHub + OpenCode 实践总结

## 核心关联：为什么需要 tmux skill

OpenCode 本身是**会话式 AI 编程助手**，但有些场景下你需要 tmux 来扩展能力边界。

---

## 使用场景

### 🎯 场景 1：多会话并行研发

你作为主 orchestrator，需要同时管理多个并行的研发任务：

```
tmux 会话布局：
├── shared (主会话 - 你在这里与 OpenCode 交互)
├── worker-2 (并行任务：前端开发)
├── worker-3 (并行任务：后端 API)
├── worker-4 (并行任务：测试编写)
└── worker-5 (并行任务：文档更新)
```

**tmux skill 的价值**：
- 让 OpenCode **自动检查** `worker-3` 会话的后端任务进展
- 发现某个会话卡在"等待确认"时，**自动发送确认**
- **批量查询所有会话状态**，而不需要你手动切换

---

### 🎯 场景 2：长时任务监控

```bash
# 场景：你在 worker-2 启动了全量测试套件
# tmux skill 可以：
tmux capture-pane -t worker-2 -p -S - | grep -E "PASS|FAIL|Error"
```

**价值**：
- 在主会话继续工作
- 定期**自动抓取**测试会话的输出
- 测试完成后**自动通知**你

---

### 🎯 场景 3：交互式 TUI 自动化

```bash
# 场景：另一个 OpenCode 会话在 worker-3 等待你的确认
tmux capture-pane -t worker-3 -p | tail -10
# 输出："❯ Do you want to proceed? Yes/No"

# 用 tmux skill 自动确认
tmux send-keys -t worker-3 'y' Enter
```

**价值**：
- 无需手动切换会话
- 可以编写脚本**批量处理**多个会话的确认请求

---

### 🎯 场景 4：跨会话任务分发

```bash
# 你作为 orchestrator，可以用 tmux skill 分发任务：
tmux send-keys -t worker-2 "Implement the login component" Enter
tmux send-keys -t worker-3 "Add auth middleware to Express" Enter
tmux send-keys -t worker-4 "Write tests for auth flow" Enter
```

**价值**：
- 一个会话作为**指挥中心**
- 同时驱动多个并行研发会话
- 每个会话可以是不同的 AI 实例或人类协作者

---

### 🎯 场景 5：SSH/远程研发场景

```bash
# 场景：你在本地，研发环境在远程服务器
# tmux 会话在服务器上持续运行
# tmux skill 可以：
tmux capture-pane -t remote-dev:0 -p | tail -50  # 查看远程进展
tmux send-keys -t remote-dev "npm run build" Enter  # 远程执行
```

**价值**：
- 会话**持久化**（SSH 断开也不中断）
- 可以**异步检查**远程研发进展
- 无需保持终端连接

---

## 实际工作流示例

```bash
# 1. 早上开工：检查昨晚的长时任务
tmux capture-pane -t nightly-build -p -S - | grep -E "completed|failed"

# 2. 并行开发：启动多个 worker 会话
tmux new-session -d -s frontend-dev
tmux new-session -d -s backend-dev
tmux send-keys -t frontend-dev "npm run dev" Enter
tmux send-keys -t backend-dev "cargo watch" Enter

# 3. 中途检查：看看哪个会话需要关注
for s in frontend-dev backend-dev; do
  echo "=== $s ==="
  tmux capture-pane -t $s -p | tail -3
done

# 4. 自动确认：处理卡住的会话
tmux capture-pane -t frontend-dev -p | grep "proceed?" && \
  tmux send-keys -t frontend-dev 'y' Enter
```

---

## 什么时候**不需要** tmux skill

| 场景 | 应该用 |
|------|--------|
| 运行一次性命令 | `Bash` 工具直接执行 |
| 后台进程 | `Bash` + `&` 或 `task(run_in_background=true)` |
| 非交互式脚本 | `Bash` 工具 |
| 没有 tmux 会话 | 直接用 `Bash` |

---

## 安装方法

```bash
# 确保 tmux 已安装
brew install tmux  # macOS
apt install tmux   # Ubuntu/Debian

# 安装 skill
npx skills add steipete/clawhub@tmux -g -y
```

---

## 常用命令速查

### 会话管理
```bash
tmux list-sessions              # 列出所有会话
tmux new-session -d -s name     # 创建后台会话
tmux kill-session -t name       # 删除会话
tmux rename-session -t old new  # 重命名会话
```

### 捕获输出
```bash
tmux capture-pane -t shared -p | tail -20    # 最后 20 行
tmux capture-pane -t shared -p -S -          # 完整历史
tmux capture-pane -t shared:0.0 -p           # 指定窗口/面板
```

### 发送按键
```bash
tmux send-keys -t shared "hello"             # 发送文本
tmux send-keys -t shared "y" Enter           # 发送 + 回车
tmux send-keys -t shared C-c                 # Ctrl+C
tmux send-keys -t shared C-d                 # Ctrl+D
```

### 批量检查所有会话
```bash
for s in shared worker-2 worker-3 worker-4; do
  echo "=== $s ==="
  tmux capture-pane -t $s -p 2>/dev/null | tail -5
done
```

---

## 总结

**tmux skill 的核心价值**：

| 价值 | 说明 |
|------|------|
| 多会话编排 | 作为 orchestrator 管理多个并行研发流 |
| 异步监控 | 长时任务无需占用注意力 |
| 交互式自动化 | 自动处理 TUI 确认、选择等操作 |
| 远程持久化 | SSH 断开不影响研发会话 |

**适用人群**：
- ✅ 需要同时推进多个任务的开发者
- ✅ 需要运行长时构建/测试的开发者
- ✅ 远程研发场景
- ✅ 需要自动化会话管理的 orchestrator

**可能不需要**：
- ❌ 单人单会话开发
- ❌ 仅需运行简单命令

---

## 相关 Skill

参考 [opencode-skill-list.md](../opencode-skill-list.md) 获取完整清单和学习路径。
