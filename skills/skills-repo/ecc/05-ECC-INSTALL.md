# Everything Claude Code - 安装指南

> 完整安装 ECC 插件、Rules、Hooks 和生态系统工具

---

## 方式 1：插件安装（推荐）

最简便的安装方式，自动配置 Commands 和 Agents。

```bash
# 添加市场
/plugin marketplace add affaan-m/everything-claude-code

# 安装插件
/plugin install ecc@ecc
```

### 验证安装

```bash
# 查看可用命令
/plugin list ecc@ecc

# 尝试一个命令
/ecc:plan "添加用户认证"
```

---

## 方式 2：手动安装脚本

适合需要完全控制安装内容的场景。

```bash
# 克隆仓库
git clone https://github.com/affaan-m/everything-claude-code.git
cd everything-claude-code

# 安装依赖
npm install        # 或：pnpm install | yarn install | bun install

# macOS/Linux 完整安装
./install.sh --profile full

# 仅安装特定语言
./install.sh typescript    # python/golang/swift/php/perl/rust/cpp

# Windows PowerShell
.\install.ps1 --profile full
```

---

## 方式 3：npx 快捷安装

全平台兼容入口。

```bash
npx ecc-install typescript
```

---

## 手动安装 Rules（必需）

> ⚠️ **重要**: Claude Code 插件系统不支持通过插件分发 `rules`，需要手动安装。

### 用户级规则（对所有项目生效）

```bash
mkdir -p ~/.claude/rules
cp -r everything-claude-code/rules/common ~/.claude/rules/
cp -r everything-claude-code/rules/golang ~/.claude/rules/
```

### 项目级规则（仅对当前项目生效）

```bash
mkdir -p .claude/rules
cp -r everything-claude-code/rules/common .claude/rules/
cp -r everything-claude-code/rules/golang .claude/rules/
```

---

## 配置 MCP 服务

从 `mcp-configs/mcp-servers.json` 复制需要的 MCP 服务定义到：

- 全局配置：`~/.claude/settings.json`
- 项目配置：`.mcp.json`

```json
{
  "mcpServers": {
    "github": {
      "command": "npx",
      "args": ["-y", "@modelcontextprotocol/server-github"]
    }
  }
}
```

---

## 可选：ccg-workflow 运行时

> ⚠️ **注意**: 基础安装**不包含** `multi-*` 命令所需的运行时。

如需使用 `/multi-plan`、`/multi-execute` 等多智能体编排命令：

```bash
npx ccg-workflow
```

这会提供：
- `~/.claude/bin/codeagent-wrapper`
- `~/.claude/.ccg/prompts/*`

---

## 环境变量配置

### 包管理器选择

```bash
# 通过环境变量
export CLAUDE_PACKAGE_MANAGER=pnpm

# 通过全局配置
node scripts/setup-package-manager.js --global pnpm

# 通过项目配置
node scripts/setup-package-manager.js --project bun
```

### 钩子运行时控制

```bash
# 钩子严格度配置（默认：standard）
export ECC_HOOK_PROFILE=standard

# 禁用指定钩子
export ECC_DISABLED_HOOKS="pre:bash:tmux-reminder,post:edit:typecheck"
```

### 禁用重复 MCP

如果已自行运行 ECC 捆绑的 MCP 服务：

```bash
export ECC_DISABLED_MCPS="github,context7,exa,playwright,sequential-thinking,memory"
```

---

## 验证安装

```bash
# 1. 检查插件
/plugin list ecc@ecc

# 2. 测试命令
/plan "测试命令"

# 3. 检查 Rules
ls ~/.claude/rules/common/

# 4. 运行安全扫描
/security-scan
```

---

## 卸载

```bash
# 禁用插件
/plugin disable ecc@ecc

# 删除 Rules
rm -rf ~/.claude/rules/common
rm -rf ~/.claude/rules/golang  # 或其他语言

# 删除 Agents
rm ~/.claude/agents/planner.md
# ... 其他 Agents
```

---

## 故障排除

### 钩子重复检测错误

```
检测到重复的钩子文件：./hooks/hooks.json 指向已加载的文件
```

**解决**: 确保 `.claude-plugin/plugin.json` 中**没有** `"hooks"` 字段。

### multi-* 命令不可用

**解决**: 安装 ccg-workflow 运行时：`npx ccg-workflow`

### Rules 未生效

**检查**: 
1. Rules 文件是否在正确目录（`~/.claude/rules/` 或 `.claude/rules/`）
2. 文件名是否以 `.md` 结尾
3. 重启 Claude Code

---

**最后更新**: 2026-04
