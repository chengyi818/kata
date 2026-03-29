---
name: video-downloader
type: media
tier: 5 - 低优先级
purpose: "视频下载"
---
# video-downloader

## 问题背景

需要下载网页视频用于本地分析或离线观看，但各平台反爬机制严格，手动获取真实地址困难且耗时。

## 安装

```bash
mkdir -p ~/.config/opencode/skills/video-downloader
# 需手动创建 SKILL.md 文件，内容参考下方"使用方式"章节
```

## 命令

### 自动识别平台

输入视频链接，skill 自动识别来源平台（YouTube、Bilibili、Twitter 等）并匹配最优下载策略。

```
download <视频链接>
```

### 下载视频

```
download <链接> --video
```

下载视频文件，支持选择清晰度（720p / 1080p / 4K）。

### 下载音频

```
download <链接> --audio
```

仅提取音频轨道，输出 MP3/M4A 格式，适合播客或音乐下载。

### 指定清晰度

```
download <链接> --quality 1080p
```

可选值：`360p`、`720p`、`1080p`、`4k`，自动选择该清晰度下最优编码。

### 批量下载

```
download <播放列表链接> --playlist
```

下载整个播放列表或合集，自动跳过已存在文件。
