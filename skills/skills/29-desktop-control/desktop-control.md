---
name: desktop-control
type: tools
tier: 5 - 低优先级
purpose: "桌面自动化(鼠标/键盘/屏幕控制)"
---
# desktop-control

## 问题背景

AI Agent 需要控制桌面应用程序（非浏览器），如 IDE、文件管理器等，但缺少可靠的 GUI 自动化方案。该技能提供鼠标、键盘和窗口的底层控制能力。

## 安装

```bash
git clone --depth 1 --filter=blob:none --sparse https://github.com/openclaw/skills.git /tmp/openclaw-skills
cd /tmp/openclaw-skills
git sparse-checkout set skills/basillytton/desktop-controls
cp -r skills/basillytton/desktop-controls ~/.config/opencode/skills/desktop-control
rm -rf /tmp/openclaw-skills
```

## 命令说明

### 鼠标控制

移动鼠标到指定坐标、执行左键/右键/双击操作、拖拽选区，支持相对和绝对坐标。

### 键盘输入

模拟键盘输入文本、按下组合快捷键（如 Ctrl+C）、切换输入法，支持中英文混合输入。

### 屏幕截图

捕获全屏或指定区域的截图，返回图像数据用于后续识别和分析。

### 窗口管理

列出当前窗口、切换焦点、最小化/最大化/关闭窗口、获取窗口位置和大小信息。
