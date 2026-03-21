#!/bin/bash
# OpenCode Skill 安装脚本
# 用法: bash install-skill.sh <skill-name> [author]
# 安装到 ~/.config/opencode/skills/

set -e

SKILL_NAME="$1"
AUTHOR="$2"
TARGET_DIR="$HOME/.config/opencode/skills/$SKILL_NAME"
REPO_URL="https://github.com/openclaw/skills.git"

if [ -z "$SKILL_NAME" ]; then
  echo "用法: bash install-skill.sh <skill-name> [author]"
  echo "示例: bash install-skill.sh summarize steipete"
  echo "      bash install-skill.sh self-improving-agent pskoett"
  exit 1
fi

# 如果已安装，跳过
if [ -d "$TARGET_DIR" ]; then
  echo "[SKIP] $SKILL_NAME 已安装于 $TARGET_DIR"
  exit 0
fi

# 方法 1: 从 openclaw/skills 仓库 sparse-checkout (如果指定了 author)
if [ -n "$AUTHOR" ]; then
  echo "[INFO] 从 openclaw/skills 仓库安装 $AUTHOR/$SKILL_NAME ..."
  TMP_DIR=$(mktemp -d)
  git clone --depth 1 --filter=blob:none --sparse "$REPO_URL" "$TMP_DIR" 2>/dev/null
  cd "$TMP_DIR"
  git sparse-checkout set "skills/$AUTHOR/$SKILL_NAME" 2>/dev/null

  if [ -d "skills/$AUTHOR/$SKILL_NAME" ]; then
    cp -r "skills/$AUTHOR/$SKILL_NAME" "$TARGET_DIR"
    rm -rf "$TMP_DIR"
    echo "[OK] $SKILL_NAME 已安装到 $TARGET_DIR"
    exit 0
  else
    rm -rf "$TMP_DIR"
    echo "[WARN] 在 openclaw/skills 仓库中未找到 $AUTHOR/$SKILL_NAME"
  fi
fi

# 方法 2: 搜索 GitHub 独立仓库
echo "[INFO] 搜索 GitHub 独立仓库 ..."
REPO_CANDIDATES=$(curl -s "https://api.github.com/search/repositories?q=$SKILL_NAME+in:name&per_page=5" 2>/dev/null | \
  python3 -c "
import sys, json
d = json.load(sys.stdin)
for r in d.get('items', []):
    if '$SKILL_NAME' in r['name'].lower():
        print(f\"{r['full_name']} | {r['stargazers_count']} | {r.get('description','')[:50]}\")
" 2>/dev/null)

if [ -n "$REPO_CANDIDATES" ]; then
  echo "找到以下仓库:"
  echo "$REPO_CANDIDATES"
  FIRST_REPO=$(echo "$REPO_CANDIDATES" | head -1 | cut -d'|' -f1 | tr -d ' ')
  echo "[INFO] 尝试从 $FIRST_REPO 克隆 ..."
  git clone --depth 1 "https://github.com/$FIRST_REPO.git" "$TARGET_DIR" 2>/dev/null
  if [ -f "$TARGET_DIR/SKILL.md" ]; then
    echo "[OK] $SKILL_NAME 已安装到 $TARGET_DIR"
    exit 0
  fi
fi

# 方法 3: 手动创建目录 (用户需自行添加 SKILL.md)
echo "[INFO] 创建空 Skill 目录，请手动添加 SKILL.md"
mkdir -p "$TARGET_DIR"
echo "[TODO] 请将 SKILL.md 放入 $TARGET_DIR/"
echo "       或运行: code $TARGET_DIR/SKILL.md"
