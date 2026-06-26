# AI辅助编程机试题库

基于Linux内核背景的四道AI辅助编程招聘机试题，面向初级工程师，考察设计模式入门与SOLID原则。

**统一约束**：30分钟（基础15min + 扩展15min），默认C语言，不限其他语言，允许使用AI编程工具。

---

## 四道题目横向对比

| 维度 | ① 页面置换算法 | ② 内存分配器 | ③ 进程调度器 | ④ 任务队列管理 |
|------|:--:|:--:|:--:|:--:|
| **目录** | `page-replacement-exam/` | `memory-allocator-exam/` | `scheduler-exam/` | `runqueue-exam/` |
| **内核背景** | 缺页异常/页框淘汰 | Buddy System/Slab | CFS完全公平调度器 | Runqueue/nice值 |
| **基础部分** | 实现FIFO/LRU页面置换模拟器 | 实现First-Fit malloc/free | 实现Round Robin调度 | 实现严格优先级队列管理 |
| **扩展部分** | 重构为可插拔策略架构 | 重构为策略+工厂模式 | 重构为策略+模板方法 | 重构为策略+装饰器模式 |
| **设计模式** | 策略模式 + 工厂模式 | 策略模式 + 工厂模式 | 策略模式 + 模板方法模式 | 策略模式 + 装饰器模式（责任链） |
| **SOLID重点** | OCP + DIP | SRP + OCP + DIP | OCP + LSP + SRP | SRP + OCP + DIP |
| **策略数量** | 4种 (FIFO/LRU/Clock/Optimal) | 4种 (First/Best/Worst/Buddy) | 6种 (FCFS/SJF/SRTF/Priority/RR/CFS) | 2-3种 (Strict/CFS/LoadBalance) |
| **反AI设计** | 硬编码→重构陷阱；设计文档要求自述决策 | Phase Trap + Buddy边界计算易出错 | 硬编码RR→多策略抽象；`scheduler_run()`禁止if/switch | 硬编码循环→策略+过滤器链；设计报告要求AI使用反思 |
| **C代码规模** | ~500行 | ~1500行 | ~700行 | ~700行 |
| **测试用例** | 26个单元测试 | 19个单元测试 | 自动化测试框架（6策略验证） | 内嵌测试用例 |
| **难度** | ⭐⭐⭐ 中等 | ⭐⭐⭐⭐ 较高 | ⭐⭐⭐ 中等 | ⭐⭐⭐ 中等 |

---

## 各题目详细对比

### 设计模式覆盖

| 设计模式 | ① 页面置换 | ② 内存分配 | ③ 调度器 | ④ 任务队列 |
|----------|:--:|:--:|:--:|:--:|
| 策略模式 (Strategy) | ✓ | ✓ | ✓ | ✓ |
| 工厂模式 (Factory) | ✓ | ✓ | — | — |
| 模板方法 (Template Method) | — | — | ✓ | — |
| 装饰器模式 (Decorator) | — | — | — | ✓ |
| 责任链模式 (Chain of Resp.) | — | — | — | ✓ |

### SOLID原则覆盖

| SOLID原则 | ① 页面置换 | ② 内存分配 | ③ 调度器 | ④ 任务队列 |
|-----------|:--:|:--:|:--:|:--:|
| SRP 单一职责 | — | ✓ | ✓ | ✓ |
| OCP 开闭原则 | ✓ | ✓ | ✓ | ✓ |
| LSP 里氏替换 | — | — | ✓ | — |
| ISP 接口隔离 | — | — | — | — |
| DIP 依赖反转 | ✓ | ✓ | — | ✓ |

### 反AI设计的核心机制

| 题目 | 反AI核心机制 | 预埋弱点 | 陷阱清单 |
|------|-------------|---------|:--:|
| ① 页面置换 | 硬编码→重构陷阱；设计文档要求自述决策 | LRU命中忘记更新 / 策略用全局变量 / 输入缺校验 | [AI_WEAKNESSES.md](page-replacement-exam/AI_WEAKNESSES.md) |
| ② 内存分配 | Phase Trap + Buddy System边界计算 | 链表≠物理顺序 / 初始化泄漏 / 缺指针校验 | [AI_WEAKNESSES.md](memory-allocator-exam/AI_WEAKNESSES.md) |
| ③ 进程调度 | 骨架代码+硬编码RR → 6种策略抽象；`scheduler_run()`严格禁止if/switch | 非抢占误写抢占 / CFS vruntime遗漏 / 空闲不推进 | [AI_WEAKNESSES.md](scheduler-exam/AI_WEAKNESSES.md) |
| ④ 任务队列 | 硬编码优先级遍历 → 策略+装饰器双模式；设计报告强制AI使用反思 | memmove算错 / 过滤链只查头 / pick返内部指针 | [AI_WEAKNESSES.md](runqueue-exam/AI_WEAKNESSES.md) |

---

## 选题建议

| 考察重点 | 推荐题目 |
|----------|---------|
| 算法理解（经典CS知识） | ① 页面置换 |
| 数据结构 + 内存管理（贴近嵌入式） | ② 内存分配器 |
| 调度概念广度（最多策略种类） | ③ 进程调度器 |
| 组合模式能力（双模式协同） | ④ 任务队列 |
| 测试完备性（开箱即用） | ② 内存分配器（19个用例）或 ① 页面置换（26个用例） |

---

## 使用方式

每道题目独立目录，结构统一：

```
<topic>-exam/
├── PROBLEM.md               # 题目描述（给候选人）
├── DESIGN_DOC_TEMPLATE.md   # 或 DESIGN_REPORT.md — 设计文档模板
├── AI_WEAKNESSES.md         # AI弱点预埋清单（面试官参考）
├── reference/               # 参考实现（给面试官）
│   ├── basic/               #   基础部分参考代码
│   ├── extended/            #   扩展部分参考代码
│   └── tests/               #   测试代码
├── Makefile                 # 构建系统（部分题目）
└── *.h / *.c                # 骨架代码（部分题目提供候选人起始代码）
```
