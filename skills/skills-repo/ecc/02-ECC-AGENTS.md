# Everything Claude Code - Agents 清单

> **总数**: 36 个专用子智能体
> 
> **用途**: 按任务类型委派，专业化处理

---

## 通用 Agents（12 个）

| 编号 | Agent | 用途 | 嵌入式场景 |
|:----:|-------|------|------------|
| ECC-AGENT-001 | **planner** | 功能实现规划 | 开发任务分解 |
| ECC-AGENT-002 | **architect** | 系统架构设计决策 | 驱动/内核架构设计 |
| ECC-AGENT-003 | **tdd-guide** | 测试驱动开发指导 | 单元测试编写 |
| ECC-AGENT-004 | **code-reviewer** | 代码质量与安全审查 | 补丁提交前审查 |
| ECC-AGENT-005 | **security-reviewer** | 漏洞分析与安全建议 | 安全编码审查 |
| ECC-AGENT-006 | **build-error-resolver** | 构建错误修复 | 交叉编译错误诊断 |
| ECC-AGENT-007 | **refactor-cleaner** | 无效代码清理 | 技术债务清理 |
| ECC-AGENT-008 | **doc-updater** | 文档同步更新 | README/注释更新 |
| ECC-AGENT-009 | **docs-lookup** | 文档/API 查阅 | 内核文档查询 |
| ECC-AGENT-010 | **chief-of-staff** | 沟通梳理与文稿起草 | RFC/设计文档撰写 |
| ECC-AGENT-011 | **loop-operator** | 自主循环执行 | 长任务自动化 |
| ECC-AGENT-012 | **harness-optimizer** | 测试框架配置调优 | 测试环境优化 |

---

## 语言专属 Reviewers（14 个）

| 编号 | Agent | 用途 | 嵌入式场景 |
|:----:|-------|------|------------|
| ECC-AGENT-013 | **cpp-reviewer** | C++ 代码审查 | C++ 内核模块审查 |
| ECC-AGENT-014 | **cpp-build-resolver** | C++ 构建错误修复 | CMake/Makefile 调试 |
| ECC-AGENT-015 | **go-reviewer** | Go 代码审查 | Go 微服务审查 |
| ECC-AGENT-016 | **go-build-resolver** | Go 构建错误修复 | Go 编译错误诊断 |
| ECC-AGENT-017 | **python-reviewer** | Python 代码审查 | Python 脚本审查 |
| ECC-AGENT-018 | **rust-reviewer** | Rust 代码审查 | Rust 嵌入式审查 |
| ECC-AGENT-019 | **rust-build-resolver** | Rust 构建错误修复 | Cargo 编译调试 |
| ECC-AGENT-020 | **java-reviewer** | Java/Spring Boot 审查 | Java 后端审查 |
| ECC-AGENT-021 | **java-build-resolver** | Java/Maven/Gradle 构建修复 | Java 编译调试 |
| ECC-AGENT-022 | **kotlin-reviewer** | Kotlin/Android/KMP 审查 | 移动端开发 |
| ECC-AGENT-023 | **kotlin-build-resolver** | Kotlin/Gradle 构建修复 | Android 编译调试 |
| ECC-AGENT-024 | **typescript-reviewer** | TypeScript/JavaScript审查 | 前端/Node.js审查 |
| ECC-AGENT-025 | **database-reviewer** | 数据库/Supabase 审查 | 数据库设计审查 |
| ECC-AGENT-026 | **pytorch-build-resolver** | PyTorch/CUDA 训练错误修复 | AI 模型训练调试 |

---

## 其他 Agents（10 个）

| 编号 | Agent | 用途 |
|:----:|-------|------|
| ECC-AGENT-027 | **e2e-runner** | Playwright 端到端测试执行 |
| ECC-AGENT-028 | **refactor-cleaner** | 死代码清理与重构 |
| ECC-AGENT-029 | **doc-updater** | 文档同步与更新 |
| ECC-AGENT-030 | **docs-lookup** | 官方文档查询 |
| ECC-AGENT-031 | **chief-of-staff** | 沟通与文稿起草 |
| ECC-AGENT-032 | **loop-operator** | 循环任务执行 |
| ECC-AGENT-033 | **harness-optimizer** | 测试框架优化 |
| ECC-AGENT-034 | **database-reviewer** | 数据库设计审查 |
| ECC-AGENT-035 | **typescript-reviewer** | TS/JS代码审查 |
| ECC-AGENT-036 | **pytorch-build-resolver** | PyTorch 错误修复 |

---

## 使用方式

在 ECC 插件安装后，可通过以下命令委派任务：

```bash
# 委派给规划 Agent
/ecc:plan "添加用户认证功能"

# 委派给代码审查 Agent
/ecc:code-review "审查当前 PR 变更"

# 委派给构建错误修复 Agent
/ecc:build-fix "修复编译错误"
```

或使用简短形式（手动安装）：

```bash
/plan "添加用户认证功能"
/code-review "审查当前 PR 变更"
/build-fix "修复编译错误"
```

---

**最后更新**: 2026-04
