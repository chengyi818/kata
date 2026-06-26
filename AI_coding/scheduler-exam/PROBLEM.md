# AI 辅助编程机试题：Linux 进程调度器模拟

**限时**：30 分钟（基础 15 min + 扩展 15 min）  
**语言**：C（契合嵌入式开发），不限其他语言  
**AI 工具**：允许使用 AI 编程助手

---

## 一、背景：Linux CFS 调度器

Linux 自 2.6.23 起使用 **完全公平调度器（CFS）** 替代 O(1) 调度器。

### 核心概念

| 概念 | 说明 |
|------|------|
| **vruntime** | 虚拟运行时间。每个进程有一个虚拟时钟，CPU 密集型进程增长快，I/O 密集型增长慢。CFS 每次选 vruntime **最小**的进程运行 |
| **weight** | 基于 nice 值（-20 ~ 19）计算出的权重。nice 越低（优先级越高），weight 越大，vruntime 增长越**慢**，获得 CPU 越多 |
| **红黑树** | 内核用红黑树按 vruntime 排序所有就绪进程，O(log n) 查找最小节点 |

```
vruntime 增量 = 实际运行时间 × (NICE_0_LOAD / weight)
NICE_0_LOAD = 1024  (nice=0 的基准权重)
```

**例子**：nice=-5 的进程 weight≈3121，每个 tick 的 vruntime 增量仅 ~0.33；nice=5 的进程 weight≈335，增量 ~3.06。前者获得约 9 倍 CPU 时间。

> **优先级方向提醒**：本题中`priority`字段即Linux的nice值（范围-20到19），**数值越小优先级越高**。`priority=-5`的进程比`priority=5`的进程更优先。AI工具经常将此语义搞反——请在实现Priority策略时特别注意。

### 你的任务

从"硬编码单一算法"逐步重构为"支持多策略的可扩展框架"，体会**设计模式**与 **SOLID 原则**在系统软件中的价值。

---

## 二、第一部分：基础实现（~15 分钟）

### 给定文件

| 文件 | 说明 |
|------|------|
| `scheduler.h` | 进程结构体、函数声明（勿修改） |
| `scheduler.c` | 骨架代码，已实现辅助函数，含 `TODO` 标记 |
| `test_runner.c` | 自动化测试（勿修改） |

### 你需要实现

`scheduler.c` 中完成 **`round_robin_schedule()`**：

```c
void round_robin_schedule(Process processes[], int n, int time_quantum);
```

- 模拟 Round Robin 调度，时间片 q = 3
- 正确处理进程到达时间（`arrival_time`）
- 记录每个进程的 `start_time`、`completion_time`、`waiting_time`、`turnaround_time`

**计算公式**：
```
turnaround_time = completion_time - arrival_time
waiting_time    = turnaround_time - burst_time
```

### 测试数据

| 进程 | PID | Priority(nice) | Burst | Arrival |
|------|-----|:---:|:-----:|:-------:|
| P0   | 1   |  0  |  5    | 0       |
| P1   | 2   |  2  |  3    | 0       |
| P2   | 3   | -5  |  8    | 0       |
| P3   | 4   |  0  |  6    | 0       |

### 期望输出（RR q=3）

```
Proc   PID    Burst    Arrival   Start   Completion  Waiting   Turnaround
------ ------ -------- --------- ------- ------------ --------- ------------
P0     1      5        0         0       14           9         14
P1     2      3        0         3       6            3         6
P2     3      8        0         6       22           14        22
P3     4      6        0         9       20           14        20

Average Waiting Time:    10.00
Average Turnaround Time: 15.50
```

### 验收标准

- [ ] Round Robin 正确执行
- [ ] 输出格式与期望一致
- [ ] 等待时间/周转时间计算正确
- [ ] `gcc -Wall -Wextra` 编译无警告

---

## 三、第二部分：扩展重构（~15 分钟）

### 背景

你的 RR 调度器工作正常，但产品经理要求支持**多种调度策略**（FCFS、SJF、优先级调度、CFS），并且要求**添加新策略时不修改核心调度代码**。

### 任务

将你的代码重构为**可扩展的调度框架**，使用以下设计模式：

#### 1. 策略模式（Strategy Pattern）

定义 `SchedStrategy` 接口（已给定），每个具体算法实现该接口：

```c
typedef int (*select_func)(void *data,
                           Process processes[], int n,
                           int ready[],
                           int current_time,
                           int current,
                           int slice_used);

struct SchedStrategy {
    const char *name;
    void       *data;
    select_func select_next;
    void      (*destroy)(SchedStrategy *self);
};
```

#### 2. 模板方法模式（Template Method Pattern）

实现 **`scheduler_run()`**，将调度循环骨架固定，算法差异委托给策略对象：

```
Template Method (scheduler_run):
  while done_count < n:
    标记新到达的进程为 ready
    next = strategy->select_next(...)    ← 变化点
    if next == -1: idle, current_time++, continue  ← 必须推进时间！
    if next != current: 上下文切换
    运行 next 进程 1 tick
    update vruntime (CFS 机制)
    if 进程完成: 记录指标, done_count++
```

#### 3. 实现至少 5 种策略

| 策略 | 抢占类型 | 选择依据 |
|------|:--:|------|
| **FCFS** | 非抢占 | 按 arrival 顺序，先到先服务。**当前进程就绪时不得切换** |
| **SJF** | 非抢占 | burst_time 最小的就绪进程。**当前进程就绪时不得切换** |
| **SRTF** | 抢占 | remaining_time 最小的就绪进程（每 tick 检查，可抢占当前进程） |
| **Priority** | 抢占 | priority(nice) 最小的就绪进程（每 tick 检查，可抢占当前进程） |
| **RR** | 时间片 | 时间片内运行，到期轮转（q=3） |
| **CFS-Simple** | 抢占 | vruntime 最小的就绪进程（每 tick 检查）。注意：**每次tick都必须更新当前运行进程的vruntime**，公式为 `vruntime += NICE_0_LOAD / weight`。遗漏更新将导致CFS行为错误 |

> **重点区分**：非抢占（FCFS、SJF）与抢占（SRTF、Priority、CFS）的关键差异——非抢占策略的`select_next`必须先检查`current`进程是否仍在就绪态，若是则必须返回`current`继续执行，而非重新选择。这是AI辅助编程中高频错误点。 |

#### 4. SOLID 原则体现

| 原则 | 如何体现 |
|------|----------|
| **OCP 开闭原则** | 添加新策略 = 新增 `.c` 文件实现 `SchedStrategy` 接口，不修改 `scheduler_run()`、`SchedulerContext` |
| **LSP 里氏替换** | 任何 `SchedStrategy` 实现可互换，`scheduler_run()` 无需知晓具体策略 |
| **SRP 单一职责** | 每个策略仅负责"选哪个进程"；`scheduler_run()` 仅负责"调度循环骨架" |

### 扩展部分验收标准

- [ ] 6 种策略全部实现且输出正确
- [ ] `scheduler_run()` 内部**不含**任何 `if (algo == ...)` 或 `switch`
- [ ] 添加新策略**不修改** `scheduler.h` 中的接口定义
- [ ] 内存管理正确（`malloc`/`free` 配对，无泄漏）

---

## 四、第三部分：设计文档（在 `scheduler.c` 顶部以块注释形式完成）

### 问题 1：代码坏味道

查看你基础部分的 `round_robin_schedule()`。如果要支持多种算法，这段代码存在哪些设计问题？列举至少 **3 个**。

### 问题 2：开闭原则违反

解释基础部分的设计如何违反**开闭原则（OCP）**。如果需求变为"同时支持 SJF"：
- 需要修改哪些函数？
- 对已有代码造成什么风险？

### 问题 3：设计模式角色

- **策略模式**在你的重构中解决了什么问题？
- **模板方法模式**中哪些部分是"不变的骨架"？哪些是"变化的算法"？
- 如果未来要添加**多级反馈队列（MLFQ）**，你的框架如何支持？需要修改哪些文件？

### 问题 4：重构前后对比

用文字描述重构前和重构后的架构图，指出关键差异。

---

## 五、评分标准（100 分）

| 评分项 | 分值 | 说明 |
|--------|:----:|------|
| 基础 RR 实现 | 25 | 功能正确 15 + 代码质量 10 |
| 策略模式实现 | 25 | 接口使用正确 10 + 各策略实现 15 |
| 模板方法实现 | 15 | scheduler_run 独立性 15 |
| 策略正确性 | 15 | 每种策略输出正确（6 × 2.5） |
| 设计文档 | 15 | 分析深度与准确性 |
| 代码质量 | 5 | 命名、注释、内存管理 |

**加分**：MLFQ +5 | I/O 阻塞模拟 +3 | 甘特图可视化 +2

---

## 六、提交

```bash
# 编译
gcc -Wall -Wextra -o scheduler scheduler.c test_runner.c -lm

# 运行并保存输出
./scheduler > output.txt

# 提交
#   scheduler.c  (含设计文档注释)
#   output.txt
```

---

## 七、提示

### CFS 权重表（已在 `scheduler.c` 中提供）

```c
static const int prio_to_weight[40] = {
    88761, 71755, 56483, 46273, 36291,  /* nice -20 ~ -16 */
    29154, 23254, 18705, 14949, 11916,  /* nice -15 ~ -11 */
     9548,  7620,  6100,  4904,  3906,  /* nice -10 ~  -6 */
     3121,  2501,  1991,  1586,  1277,  /* nice  -5 ~  -1 */
     1024,   820,   655,   526,   423,  /* nice   0 ~   4 */
      335,   272,   215,   172,   137,  /* nice   5 ~   9 */
      110,    87,    70,    56,    45,  /* nice  10 ~  14 */
       36,    29,    23,    18,    15,  /* nice  15 ~  19 */
};
/* 每个 tick: vruntime += 1024.0 / weight[nice+20] */
```

### C 语言中的"OOP"

```c
/* 策略模式的 C 语言实现 = 函数指针表 (vtable) */
SchedStrategy *create_fcfs_strategy(void) {
    SchedStrategy *s = malloc(sizeof(SchedStrategy));
    s->name        = "FCFS";
    s->select_next = fcfs_select;
    s->destroy     = default_destroy;
    s->data        = malloc(sizeof(FCFSData));  /* 策略私有状态 */
    return s;
}
```

### 常见错误

- `completion_time` 的定义：进程**完成时**的时间戳（执行完最后一个 tick 后的时间）
- 进程到达前被错误调度（检查 `arrival_time <= current_time`）
- CPU 空闲时忘记推进 `current_time`
- `remaining_time` 未正确重置（需在每次测试前初始化为 `burst_time`）
- 策略分配的内存未在 `destroy` 中释放

---

**Good luck!**
