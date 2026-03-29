# openai-whisper

## 问题背景

音频/视频转文字通常需要调用付费云 API，涉及隐私数据上传。本 skill 使用 OpenAI Whisper 模型本地运行，无需 API Key，数据不出本机。

## 安装

```bash
git clone --depth 1 --filter=blob:none --sparse https://github.com/openclaw/skills.git /tmp/openclaw-skills
cd /tmp/openclaw-skills
git sparse-checkout set skills/czubi1928/openai-whisper-1-0-0
cp -r skills/czubi1928/openai-whisper-1-0-0 ~/.config/opencode/skills/openai-whisper
rm -rf /tmp/openclaw-skills
```

CLI 依赖：

```bash
pip install openai-whisper
```

## 命令

### 语音转文字

```
transcribe <音频/视频文件>
```

将音频或视频文件转录为纯文本，自动检测语言。

### 指定语言

```
transcribe <文件> --language zh
```

手动指定语言代码（`zh` / `en` / `ja` / `fr` 等），提升识别准确率。

### 生成字幕

```
transcribe <文件> --subtitle
```

输出 SRT 格式字幕文件，保留时间戳，可直接导入视频播放器。

### 选择模型

```
transcribe <文件> --model large
```

可选 `tiny`、`base`、`small`、`medium`、`large`，模型越大准确率越高但速度越慢。

### 输出格式

```
transcribe <文件> --output txt
```

支持 `txt`（纯文本）、`srt`（字幕）、`vtt`（Web 字幕）、`json`（带时间戳）。
