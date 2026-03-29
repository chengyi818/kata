---
name: elite-longterm-memory
type: dev-memory
tier: 5 - 低优先级
purpose: "长期记忆系统(WAL + vector search)"
---
# Elite Long-Term Memory

## 问题与背景

AI 没有长期记忆能力，重要的上下文信息一旦丢失就需要用户重复输入。Elite Long-Term Memory 基于 WAL（Write-Ahead Log）协议、向量检索和 git-notes 同步机制，为 AI 提供持久化、可检索的长期记忆能力。

## 安装

```bash
git clone --depth 1 https://github.com/NextFrontierBuilds/elite-longterm-memory.git ~/.config/opencode/skills/elite-longterm-memory
```

## 命令说明

### WAL 协议写入记忆

通过 Write-Ahead Log 协议确保记忆写入的原子性和一致性。即使进程意外中断，已提交的记忆也不会丢失。

### Vector Search 检索相关记忆

基于向量相似度搜索，从海量记忆中快速定位与当前上下文最相关的信息。支持语义级别的模糊匹配。

### Git-Notes 同步

利用 git-notes 机制将记忆与代码仓库关联。在不同设备和团队成员之间同步记忆数据，保持上下文一致性。

### 云端备份

将本地记忆数据加密备份至云端，防止数据丢失。支持增量备份和按需恢复。

## 使用示例

```bash
# 存储一条记忆
elite-memory remember "项目使用 PostgreSQL 作为主数据库"

# 检索相关记忆
elite-memory recall "数据库选型"

# 同步记忆到 git-notes
elite-memory sync

# 备份到云端
elite-memory backup
```
