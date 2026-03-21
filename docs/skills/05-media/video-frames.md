# video-frames

## 问题背景

需要从视频中提取关键帧用于分析、封面制作或数据采集，手动截图效率低且不精确。本 skill 基于 ffmpeg 实现批量帧提取。

## 安装

```bash
mkdir -p ~/.config/opencode/skills/video-frames
# 需手动创建 SKILL.md 文件，内容参考下方"使用方式"章节
```

需要系统已安装 ffmpeg。

```bash
brew install ffmpeg
# 或
apt install ffmpeg
```

## 命令

### 按间隔提取帧

```
extract <视频文件> --interval 5
```

每 5 秒提取一帧，输出为图片序列（PNG/JPG）。

### 提取指定时间段

```
extract <视频文件> --from 00:01:30 --to 00:02:00
```

从 1 分 30 秒到 2 分钟之间提取所有帧。

### 提取单帧

```
extract <视频文件> --at 00:01:45
```

提取指定时间点的单张画面。

### 指定输出格式

```
extract <视频文件> --interval 1 --format jpg
```

输出格式支持 `png`（无损）或 `jpg`（体积小），默认 png。

### 指定输出目录

```
extract <视频文件> --interval 3 --output ./frames/
```

将提取的帧保存到指定目录，文件按时间戳命名。
