# AI辅助编程弱点预埋清单（面试官参考）

> 本题共预埋 **3** 个AI编程常见弱点，用于区分"真正理解系统编程的候选人"与"盲目复制AI输出的候选人"。

---

## 弱点 1：非抢占策略误写成抢占式

**嵌入位置**：`PROBLEM.md` 第二部分 策略表 + 重点区分提示块

**AI典型行为**：
- 所有策略的`select_next()`实现逻辑相同：每tick都重新遍历选进程
- FCFS/SJF的select函数忽略"当前进程就绪时应继续执行"的非抢占语义
- 导致FCFS行为退化为某种优先抢占式调度，输出与预期不符

**好候选人行为**：
- 非抢占策略的select第一步检查：`if (current != -1 && ready[current]) return current;`
- 当前进程未完成前不切换，只有进程完成（不再ready）时才选下一个
- 抢占策略则不然：每tick重新竞争，可能被新进程抢占

**检测方法**：
- FCFS输出：进程按arrival顺序执行到完成，中间不切换
- SJF输出：与FCFS不同（进程按burst时间短优先），但同样不抢占
- 检查`fcfs_select`和`sjf_select`中是否包含`if (current ready) return current`逻辑
- 若所有策略select实现结构相同，说明候选人未理解抢占/非抢占差异

---

## 弱点 2：CFS vruntime更新遗漏

**嵌入位置**：`PROBLEM.md` 第二部分 策略表CFS行 + 模板方法伪代码注释

**AI典型行为**：
- CFS策略的select函数能选出vruntime最小的进程
- 但`scheduler_run()`模板方法中忘记每次tick更新`vruntime`
- vruntime永远为0，CFS退化为优先级调度（按数组顺序选第一个进程）
- 或只在一个地方更新（如进程完成时），导致CFS行为错误

**好候选人行为**：
- `scheduler_run()`模板方法中，每执行1 tick后执行：
  ```c
  ctx->processes[current].vruntime += vruntime_delta(ctx->processes[current].weight);
  ```
- 理解CFS核心：vruntime是持续累积的公平性度量，必须在**每个tick**更新
- 能正确区分：select函数只管"选谁"，模板方法负责"跑了多少时间"

**检测方法**：
- 运行CFS策略，不同nice值的进程应有明显不同的CPU时间分配比例
- 若所有进程CPU时间均分（nice差异不影响），说明vruntime未正确更新
- 检查`scheduler_run()`中是否有`vruntime += ...`语句
- nice=-5的进程（weight=3121）应比nice=5的进程（weight=335）获得约9倍CPU时间

---

## 弱点 3：空闲CPU时时间不推进

**嵌入位置**：`PROBLEM.md` 第二部分 模板方法伪代码

**AI典型行为**：
- `scheduler_run()`模板方法中，当`select_next()`返回-1（无就绪进程）时：
  ```c
  if (next == -1) continue;  // 错误！时间未推进
  ```
- `current_time`不递增，下一个tick仍是同一时刻
- 检查arrival_time的条件 `arrival_time <= current_time` 永远不变
- 导致死循环：进程永远无法到达，CPU永远空闲

**好候选人行为**：
- 空闲时正确推进仿真时钟：
  ```c
  if (next == -1) {
      current_time++;
      continue;
  }
  ```
- 理解仿真时间推进是独立于进程执行的概念
- 能正确处理所有进程arrival_time>0的场景

**检测方法**：
- 使用arrival_time>0的测试数据，程序不应死循环
- 设置所有进程arrival_time=100，验证能正确空闲100 ticks后开始调度
- 超时检测：若程序运行超过2秒仍未输出结果，大概率存在此bug

---

## 评分建议

| 候选人类别 | 典型表现 | 建议判分 |
|-----------|---------|---------|
| 仅复制AI输出 | 3个弱点全中：所有策略行为相似、CFS无效、空闲死循环 | 基础分30%以下 |
| 部分审查AI输出 | 修正了1-2个弱点，有抢占/非抢占区分但CFS更新可能遗漏 | 基础分50-70% |
| 深度审查AI输出 | 3个弱点全部规避，6种策略输出正确且互不相同 | 基础分80%以上 |
