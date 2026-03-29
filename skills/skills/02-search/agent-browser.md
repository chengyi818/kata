# agent-browser

## 问题背景

需要自动化操作网页（抓取内容、截图、填写表单等），但不想手写 Playwright 或 Puppeteer 代码。agent-browser 将浏览器操作封装为简单的命令，让 AI 直接控制浏览器完成任务。

## 安装

```bash
git clone --depth 1 --filter=blob:none --sparse https://github.com/openclaw/skills.git /tmp/openclaw-skills
cd /tmp/openclaw-skills
git sparse-checkout set skills/adastraabyssoque/agent-browser-with-camoufox
cp -r skills/adastraabyssoque/agent-browser-with-camoufox ~/.config/opencode/skills/agent-browser
rm -rf /tmp/openclaw-skills
```

Skill 复制到 `~/.config/opencode/skills/` 后，OpenCode 会自动识别，无需额外配置。

## 命令说明

| 命令 | 功能 |
|------|------|
| `navigate` | 打开指定 URL，加载目标页面 |
| `click` | 点击页面中的指定元素（按钮、链接等） |
| `type` | 在输入框中输入文字 |
| `screenshot` | 对当前页面截图并保存 |
| `snapshot` | 获取页面结构快照，供后续分析 |
| `extract` | 提取页面中的文本内容 |

## 使用示例

```
agent-browser navigate https://example.com
agent-browser type "#search" "关键词"
agent-browser click ".submit-btn"
agent-browser screenshot
```

## 适用场景

- 自动化表单填写与提交
- 网页内容抓取与数据采集
- 定期截图监控页面变化
- 无头浏览器批处理任务
