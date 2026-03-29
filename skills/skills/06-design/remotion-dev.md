# remotion-dev

## 问题背景

产品演示视频传统上需要 After Effects 等专业工具，成本高且难以版本控制。本 skill 基于 Remotion 框架，用 React 代码定义动画，支持 Git 管理和自动化渲染。

## 安装

```bash
mkdir -p ~/.config/opencode/skills/remotion-dev
# 需手动创建 SKILL.md 文件，内容参考下方"使用方式"章节
```

CLI 依赖：

```bash
npm install remotion @remotion/cli
```

## 命令

### 创建动画项目

```
remotion-init <项目名>
```

生成 Remotion 项目脚手架，包含基础 Composition 和示例动画。

### 文字排版动画

```
add-scene --type title
```

添加文字入场/出场动画场景，支持逐字显示、淡入、滑入等效果。

### 转场效果

```
add-transition --effect fade
```

在场景间添加转场，支持 `fade`、`slide`、`wipe`、`zoom` 等类型。

### 基础动画

```
add-animation --element logo --effect spring
```

为指定元素添加物理动画（弹性、缓动、弹跳），可配置参数。

### 渲染输出

```
remotion-render --format mp4
```

渲染最终视频，支持 `mp4`、`webm` 格式，可指定分辨率和帧率。
