---
name: multi-search-engine
type: search
tier: 5 - 低优先级
purpose: "17个搜索引擎集成"
---
# multi-search-engine

## 问题背景

单一搜索引擎覆盖面有限：百度中文结果好但英文弱，Google 国内不可用，Bing 部分功能受限。中英文混合场景需要手动切换引擎，效率低下。

## 安装

```bash
git clone --depth 1 --filter=blob:none --sparse https://github.com/openclaw/skills.git /tmp/openclaw-skills
cd /tmp/openclaw-skills
git sparse-checkout set skills/52yuanchangxing/multi-search-engine-pro
cp -r skills/52yuanchangxing/multi-search-engine-pro ~/.config/opencode/skills/multi-search-engine
rm -rf /tmp/openclaw-skills
```

Skill 复制到 `~/.config/opencode/skills/` 后，OpenCode 会自动识别，无需额外配置。

## 集成引擎

共集成 17 个搜索引擎：

**国内引擎（8 个）**：百度、搜狗、必应中国、360 搜索等

**国际引擎（9 个）**：Google、DuckDuckGo、Bing、Yahoo、Brave Search 等

## 命令说明

自动根据查询内容选择最佳引擎，也可手动指定：

```
搜索"Java 并发编程"                    # 自动选择
multi-search-engine search "query" --engine baidu  # 指定引擎
```

## 适用场景

- 中英文混合查询，需广覆盖
- 对比不同引擎的搜索结果
- 某个引擎不可用时自动降级到备用
- 需要同时获取国内外信息源

## 优势

- 自动语言检测，智能路由到最合适的引擎
- 多引擎结果去重与排序
- 单一 API 对接 17 个引擎，无需分别配置
