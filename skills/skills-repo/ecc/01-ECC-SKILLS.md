# Everything Claude Code - Skills 清单

> **来源**: [affaan-m/everything-claude-code](https://github.com/affaan-m/everything-claude-code)
> 
> **版本**: 2026-04 更新
> 
> **项目状态**: 140K+ stars, 21K+ forks, Anthropic 黑客松获胜作品

---

## 概述

ECC (Everything Claude Code) 提供 181+ Skills、36 个 Agents、47 个 Commands，经过 10+ 个月高强度生产环境验证。

本清单筛选出适合嵌入式/Linux 开发的 Skills，已排除前端/设计/媒体类。

---

## 语言专属编码标准

| 编号 | Skill | 用途 | 嵌入式场景 |
|:----:|-------|------|------------|
| ECC-001 | **cpp-coding-standards** | C++ Core Guidelines 编码规范 | 内核模块/C++ 嵌入式项目 |
| ECC-002 | **cpp-testing** | GoogleTest + CMake/CTest 测试框架 | C++ 单元测试/集成测试 |
| ECC-003 | **rust-reviewer** | Rust 代码审查与安全分析 | Rust 嵌入式/内核开发 |
| ECC-004 | **rust-build-resolver** | Rust/Cargo 构建错误修复 | Rust 编译错误诊断 |
| ECC-005 | **perl-patterns** | Perl 5.36+ 惯用写法 | 内核脚本/构建脚本 |
| ECC-006 | **perl-testing** | Test2::V0 + prove + Devel::Cover | Perl 脚本 TDD 测试 |
| ECC-007 | **perl-security** | 污点模式分析 + 安全 I/O | Perl 脚本安全加固 |
| ECC-008 | **python-patterns** | Python 惯用写法与最佳实践 | Python 工具脚本 |
| ECC-009 | **python-testing** | pytest 测试框架集成 | Python 单元测试 |

---

## 数据库与后端模式

| 编号 | Skill | 用途 | 嵌入式场景 |
|:----:|-------|------|------------|
| ECC-010 | **postgres-patterns** | PostgreSQL 查询优化与索引策略 | 嵌入式数据库优化 |
| ECC-011 | **database-migrations** | Prisma/Drizzle/Django/Go迁移模式 | 数据库版本管理 |
| ECC-012 | **api-design** | REST API 设计、分页、错误响应 | IoT 设备 API 设计 |
| ECC-013 | **deployment-patterns** | CI/CD、Docker、健康检查、回滚 | 嵌入式容器部署 |
| ECC-014 | **docker-patterns** | Docker Compose、网络、数据卷、容器安全 | 容器化开发环境 |

---

## 安全与质量管控

| 编号 | Skill | 用途 | 嵌入式场景 |
|:----:|-------|------|------------|
| ECC-015 | **security-scan** | 集成 AgentShield 安全审计（1282 项测试） | 代码安全扫描 |
| ECC-016 | **plankton-code-quality** | 基于钩子的实时代码质量管控 | 提交前质量检查 |
| ECC-017 | **security-review** | 安全检查清单与漏洞分析 | 安全编码审查 |
| ECC-018 | **cost-aware-llm-pipeline** | LLM 成本优化、模型路由、预算跟踪 | Token 用量优化 |

---

## 工作流增强

| 编号 | Skill | 用途 | 嵌入式场景 |
|:----:|-------|------|------------|
| ECC-019 | **search-first** | 先调研再编码工作流 | 避免重复造轮子 |
| ECC-020 | **autonomous-loops** | 自主循环模式：顺序流水线/PR 循环/DAG 编排 | 自动化任务编排 |
| ECC-021 | **configure-ecc** | 交互式安装向导 | 初次配置辅助 |
| ECC-022 | **skill-stocktake** | 技能与命令质量审计 | 清理过期 Skills |
| ECC-023 | **regex-vs-llm-structured-text** | 文本解析：正则与 LLM 选型决策框架 | 日志/配置文件解析 |
| ECC-024 | **content-hash-cache-pattern** | SHA-256 内容哈希缓存 | 固件包/镜像校验 |

---

## 持续学习系统

| 编号 | Skill | 用途 | 嵌入式场景 |
|:----:|-------|------|------------|
| ECC-025 | **continuous-learning-v2** | 基于本能的学习，附带置信度评分 | 跨会话调试经验记忆 |
| ECC-026 | **iterative-retrieval** | 为子智能体渐进式优化上下文 | 复杂调试上下文管理 |
| ECC-027 | **verification-loop** | 持续验证机制与评分器 | 编译/测试自动化验证 |

---

## 框架专属（按需安装）

| 编号 | Skill | 用途 | 嵌入式场景 |
|:----:|-------|------|------------|
| ECC-028 | **django-patterns** | Django 模型/视图/ORM 模式 | Python Web API（设备管理） |
| ECC-029 | **django-security** | Django 安全最佳实践 | Web 接口安全 |
| ECC-030 | **django-tdd** | Django TDD 工作流 | Python 后端测试 |
| ECC-031 | **laravel-patterns** | Laravel 架构模式 | PHP 设备管理后端 |
| ECC-032 | **laravel-security** | Laravel 安全最佳实践 | PHP 后端安全 |
| ECC-033 | **springboot-patterns** | Java Spring Boot 模式 | Java 嵌入式后端 |
| ECC-034 | **springboot-security** | Spring Boot 安全配置 | Java 后端安全 |

---

## 安装方式

### 插件安装（推荐）

```bash
/plugin marketplace add affaan-m/everything-claude-code
/plugin install ecc@ecc
```

### 手动安装

```bash
git clone https://github.com/affaan-m/everything-claude-code.git
cd everything-claude-code
npm install
./install.sh --profile full
```

### npx 快捷安装

```bash
npx ecc-install typescript  # 或 python/golang/rust/cpp/perl
```

---

## 相关文档

- [ECC-AGENTS.md](ECC-AGENTS.md) - 36 个专用 Agents 详解
- [ECC-COMMANDS.md](ECC-COMMANDS.md) - 47 个 Commands 详解
- [ECC-RULES.md](ECC-RULES.md) - 规范文件与 Hooks 详解
- [ECC-INSTALL.md](ECC-INSTALL.md) - 完整安装指南
- [ECC-TOOLS.md](ECC-TOOLS.md) - 生态系统工具（AgentShield 等）

---

## 数据来源

| 来源 | 链接 |
|------|------|
| GitHub 仓库 | https://github.com/affaan-m/everything-claude-code |
| ECC 简明指南 | https://x.com/affaanmustafa/status/2012378465664745795 |
| ECC 详细指南 | https://x.com/affaanmustafa/status/2014040193557471352 |
| AgentShield 指南 | https://x.com/affaanmustafa/status/2033263813387223421 |

---

**最后更新**: 2026-04
