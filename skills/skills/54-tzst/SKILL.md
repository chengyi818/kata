---
name: tzst
description: Use when Zstandard 压缩/解压工具，适合内核镜像/固件包 - 内核镜像压缩、固件包解压、rootfs 打包。
tier: 低优先级-开发工具
source: skills.sh (19.9K 安装)
---

# tzst

> **编号**: 52
> **梯队**: 低优先级-开发工具
> **来源**: skills.sh (19.9K 安装)

## 解决的问题

内核镜像/固件包体积大，压缩解压耗时。zstd 比 gzip 更快。19.9K 安装量。

## 适用场景

Zstandard 压缩/解压工具，适合内核镜像/固件包

**嵌入式场景**: 内核镜像压缩、固件包解压、rootfs 打包。

## 安装方法

skills.sh: npx skills add xixu-me/skills@tzst -g -y

## 使用方法

使用 zstd 压缩/解压文件，支持多线程、高压缩比。内核镜像和固件包常用格式。

## 嵌入式开发场景

内核镜像压缩、固件包解压、rootfs 打包。

## 相关 Skill

参考 [opencode-skill-list.md](../opencode-skill-list.md) 获取完整清单和学习路径。
