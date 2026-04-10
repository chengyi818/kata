# Everything Claude Code - Commands 清单

> **总数**: 47 个传统斜杠命令
> 
> **说明**: 优先使用 Skills，但 Commands 在快速操作时更便捷

---

## 核心开发命令（6 个）

| 编号 | 命令 | 用途 | 嵌入式场景 |
|:----:|------|------|------------|
| ECC-CMD-001 | `/tdd` | 测试驱动开发工作流 | 驱动单元测试 |
| ECC-CMD-002 | `/plan` | 实现规划与任务分解 | 开发计划制定 |
| ECC-CMD-003 | `/e2e` | 生成端到端测试 | 集成测试编写 |
| ECC-CMD-004 | `/code-review` | 代码质量审查 | 补丁审查 |
| ECC-CMD-005 | `/build-fix` | 修复构建错误 | 交叉编译调试 |
| ECC-CMD-006 | `/refactor-clean` | 清理无效代码 | 代码重构 |

---

## 持续学习命令（9 个）

| 编号 | 命令 | 用途 | 嵌入式场景 |
|:----:|------|------|------------|
| ECC-CMD-007 | `/learn` | 会话中提取模式 | 调试经验沉淀 |
| ECC-CMD-008 | `/learn-eval` | 提取、评估并保存模式 | 高质量经验记忆 |
| ECC-CMD-009 | `/checkpoint` | 保存验证状态 | 长任务状态保存 |
| ECC-CMD-010 | `/verify` | 运行验证循环 | 编译/测试验证 |
| ECC-CMD-011 | `/instinct-status` | 查看已学习本能 | 知识回顾 |
| ECC-CMD-012 | `/instinct-import` | 导入本能 | 团队知识共享 |
| ECC-CMD-013 | `/instinct-export` | 导出本能 | 知识分享 |
| ECC-CMD-014 | `/evolve` | 将本能聚类为技能 | 工作流沉淀 |
| ECC-CMD-015 | `/prune` | 删除过期待处理本能 | 知识清理 |

---

## 多智能体编排命令（6 个）

> ⚠️ 需要额外安装 `ccg-workflow` 运行时：`npx ccg-workflow`

| 编号 | 命令 | 用途 | 嵌入式场景 |
|:----:|------|------|------------|
| ECC-CMD-016 | `/multi-plan` | 多智能体任务拆解 | 复杂任务并行化 |
| ECC-CMD-017 | `/multi-execute` | 多智能体工作流编排 | 大规模开发协作 |
| ECC-CMD-018 | `/multi-backend` | 后端多服务编排 | 微服务开发 |
| ECC-CMD-019 | `/multi-frontend` | 前端多服务编排 | 前端开发 |
| ECC-CMD-020 | `/multi-workflow` | 通用多服务工作流 | 自定义工作流 |
| ECC-CMD-021 | `/orchestrate` | 多智能体协同调度 | 任务编排 |

---

## 语言专属命令（5 个）

| 编号 | 命令 | 用途 | 嵌入式场景 |
|:----:|------|------|------------|
| ECC-CMD-022 | `/go-review` | Go 代码审查 | Go 项目审查 |
| ECC-CMD-023 | `/go-test` | Go TDD 工作流 | Go 测试编写 |
| ECC-CMD-024 | `/go-build` | 修复 Go 构建错误 | Go 编译调试 |
| ECC-CMD-025 | `/python-review` | Python 代码审查 | Python 脚本审查 |
| ECC-CMD-026 | `/skill-create` | 从 Git 历史生成技能 | 工作流沉淀 |

---

## 运维与工具命令（8 个）

| 编号 | 命令 | 用途 | 嵌入式场景 |
|:----:|------|------|------------|
| ECC-CMD-027 | `/setup-pm` | 配置包管理器 | npm/pnpm/yarn 切换 |
| ECC-CMD-028 | `/pm2` | PM2 服务生命周期管理 | Node.js 服务管理 |
| ECC-CMD-029 | `/sessions` | 会话历史管理 | 上下文管理 |
| ECC-CMD-030 | `/eval` | 按标准评估 | 质量评估 |
| ECC-CMD-031 | `/test-coverage` | 测试覆盖率分析 | 覆盖率检查 |
| ECC-CMD-032 | `/update-docs` | 更新文档 | 文档维护 |
| ECC-CMD-033 | `/update-codemaps` | 更新代码映射 | 代码导航优化 |
| ECC-CMD-034 | `/security-scan` | 集成 AgentShield 安全审计 | 安全扫描 |

---

## 其他命令（13 个）

| 编号 | 命令 | 用途 |
|:----:|------|------|
| ECC-CMD-035 | `/learn` | 会话中提取模式 |
| ECC-CMD-036 | `/checkpoint` | 保存验证状态 |
| ECC-CMD-037 | `/verify` | 运行验证循环 |
| ECC-CMD-038 | `/eval` | 按标准评估 |
| ECC-CMD-039 | `/test-coverage` | 测试覆盖率分析 |
| ECC-CMD-040 | `/update-docs` | 更新文档 |
| ECC-CMD-041 | `/update-codemaps` | 更新代码映射 |
| ECC-CMD-042 | `/sessions` | 会话历史管理 |
| ECC-CMD-043 | `/orchestrate` | 多智能体协同调度 |
| ECC-CMD-044 | `/pm2` | PM2 服务管理 |
| ECC-CMD-045 | `/setup-pm` | 包管理器配置 |
| ECC-CMD-046 | `/instinct-status` | 本能状态查看 |
| ECC-CMD-047 | `/evolve` | 本能聚类为技能 |

---

## 使用示例

```bash
# 开始 TDD 开发
/tdd "实现 SPI 驱动"

# 规划功能实现
/plan "添加设备树解析功能"

# 代码审查
/code-review "检查 spi_driver.c 的变更"

# 安全扫描
/security-scan

# 查看学习到的本能
/instinct-status
```

---

**最后更新**: 2026-04
