# Auto Updater

## 背景

Agent 和已安装的 Skill 会持续发布新版本，手动检查并逐一更新既繁琐又容易遗漏。版本落后意味着错过安全补丁、性能优化和新功能，长期积累后还可能因跨度太大导致升级兼容性问题。

Auto Updater 自动完成检查和更新流程，确保环境始终保持最新。

## 安装

```bash
git clone --depth 1 --filter=blob:none --sparse https://github.com/openclaw/skills.git /tmp/openclaw-skills
cd /tmp/openclaw-skills
git sparse-checkout set skills/aahuaxu/auto-updater-skill
cp -r skills/aahuaxu/auto-updater-skill ~/.config/opencode/skills/auto-updater
rm -rf /tmp/openclaw-skills
```

Skill 复制到 `~/.config/opencode/skills/` 后，OpenCode 会自动识别，无需额外配置。

## 命令说明

### `auto-updater start`

启动后台定时任务，默认每日一次自动执行完整更新流程：

1. 检查 Agent 及所有已安装 Skill 的最新版本
2. 对比当前版本，识别可用更新
3. 按依赖顺序逐个应用更新
4. 发送变更摘要通知，包含本次更新的组件和版本号

### `auto-updater check`

立即执行一次更新检查，列出所有可更新的组件及版本变化，但不自动应用。适合在手动控制更新节奏时使用。

### `auto-updater apply`

将 `check` 命令检测到的待更新项全部应用。可配合 `--skill <name>` 参数仅更新指定 Skill。

### `auto-updater schedule`

配置自动更新的执行频率和时间窗口。支持参数：

- `--interval <daily|weekly>`：设置检查频率
- `--time <HH:MM>`：设置每日执行时间
- `--notify <true|false>`：开启或关闭更新通知

### `auto-updater history`

查看更新历史记录，包括每次更新的时间、涉及的组件和版本变化，便于回溯和排查问题。
