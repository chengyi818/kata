# Everything Claude Code - Rules & Hooks

> **Rules**: 必须遵守的规范文件
> 
> **Hooks**: 基于触发器的自动化逻辑

---

## Rules 结构

ECC 的 Rules 分为 `common/`（通用）+ 语言特定目录，需手动安装到 `~/.claude/rules/` 或 `.claude/rules/`。

### 通用规范（必装）

| 文件 | 用途 | 嵌入式场景 |
|------|------|------------|
| `coding-style.md` | 不可变性、文件组织规范 | 代码风格统一 |
| `git-workflow.md` | 提交格式、PR 流程 | Git 提交规范 |
| `testing.md` | TDD、80% 覆盖率要求 | 测试规范 |
| `performance.md` | 模型选型、上下文管理 | Token 优化 |
| `patterns.md` | 设计模式、项目骨架 | 架构模式 |
| `hooks.md` | 钩子架构、TodoWrite | 自动化规范 |
| `agents.md` | 子智能体委派时机 | 任务委派 |
| `security.md` | 强制安全检查 | 安全编码 |

### 语言专属规范（按需）

| 目录 | 适用技术栈 | 嵌入式场景 |
|------|-----------|------------|
| `typescript/` | TypeScript/JavaScript | Node.js 工具/前端 |
| `python/` | Python | Python 脚本/工具 |
| `golang/` | Go | Go 微服务/工具 |
| `swift/` | Swift | iOS/macOS 开发 |
| `php/` | PHP | PHP 后端（较少用） |
| `perl/` | Perl | 内核脚本/构建脚本 |
| `rust/` | Rust | Rust 嵌入式/内核 |
| `cpp/` | C++ | C++ 内核模块 |

---

## Hooks 核心配置

ECC 提供基于触发器的自动化钩子，配置在 `hooks/hooks.json` 中。

### 核心钩子

| 钩子类型 | 触发时机 | 用途 |
|---------|---------|------|
| `memory-persistence` | 会话启动/结束 | 自动加载/保存上下文 |
| `strategic-compact` | 上下文精简前 | 状态保存与建议 |
| `pre-compact` | 上下文精简前 | 精简前状态保存 |
| `suggest-compact` | 上下文精简建议 | 策略性精简 |
| `evaluate-session` | 会话结束 | 从会话中提取模式 |

### 钩子示例

```json
{
  "matcher": "tool == \"Edit\" && tool_input.file_path matches \"\\\\.(ts|tsx|js|jsx)$\"",
  "hooks": [{
    "type": "command",
    "command": "#!/bin/bash\ngrep -n 'console\\.log' \"$file_path\" && echo '[Hook] 移除 console.log' >&2"
  }]
}
```

---

## 安装 Rules

### 用户级规则（对所有项目生效）

```bash
mkdir -p ~/.claude/rules
cp -r everything-claude-code/rules/common ~/.claude/rules/
cp -r everything-claude-code/rules/golang ~/.claude/rules/   # 选择技术栈
```

### 项目级规则（仅对当前项目生效）

```bash
mkdir -p .claude/rules
cp -r everything-claude-code/rules/common .claude/rules/
cp -r everything-claude-code/rules/golang .claude/rules/
```

---

## 钩子自动加载机制

> ⚠️ **重要**: Claude Code v2.1+ 会**按照约定自动加载**已安装插件中的 `hooks/hooks.json`。
> 
> 请勿在 `.claude-plugin/plugin.json` 中添加 `"hooks"` 字段，会触发重复检测错误：
> ```
> 检测到重复的钩子文件：./hooks/hooks.json 指向已加载的文件
> ```

---

## 自定义钩子

可以基于项目需求自定义钩子，添加到 `hooks/hooks.json`：

```json
{
  "hooks": [
    {
      "matcher": "tool == \"Bash\" && tool_input.command matches \"rm.*-rf.*\"",
      "hooks": [{
        "type": "command",
        "command": "echo '[Hook] 警告：危险操作！' >&2"
      }]
    },
    {
      "matcher": "tool == \"Edit\" && tool_input.file_path matches \"Makefile$\"",
      "hooks": [{
        "type": "command",
        "command": "echo '[Hook] Makefile 变更，建议运行 make test' >&2"
      }]
    }
  ]
}
```

---

**最后更新**: 2026-04
