# AI辅助编程弱点预埋清单（面试官参考）

> 本题共预埋 **3** 个AI编程常见弱点，用于区分"真正理解系统编程的候选人"与"盲目复制AI输出的候选人"。

---

## 弱点 1：队列元素前移时memmove长度计算错误

**嵌入位置**：`PROBLEM.md` Part 1 函数表 → C语言陷阱提示块

**AI典型行为**：
- 从队列中删除元素后，前移后续元素时：
  ```c
  memmove(&queue[idx], &queue[idx+1], (size - idx) * sizeof(task_t));  // 错误：多移一个
  ```
  或：
  ```c
  memmove(&queue[idx], &queue[idx+1], size - idx);  // 错误：缺少 sizeof
  ```
- 导致：最后一个位置残留垃圾数据，或memmove覆盖越界

**好候选人行为**：
- 正确公式：`memmove(&queue[idx], &queue[idx+1], (sizes[i] - idx - 1) * sizeof(task_t))`
- `sizes[i] - idx - 1` 计算剩余元素个数，`* sizeof(task_t)` 计算字节数
- 删除后正确递减 `sizes[i]` 和 `rq->total`

**检测方法**：
- 入队5个任务，删除中间3个（位置1、2、3），检查队列一致性
- `valgrind` 检测是否有堆越界读写
- 多次入队/出队后，`rq_pick_next` 不应返回垃圾数据

---

## 弱点 2：过滤链只检查第一个filter

**嵌入位置**：`PROBLEM.md` Part 2 filter_chain → 验证提示块

**AI典型行为**：
- `rq_apply_filter` 只调用 `filter->accept(task)`，不遍历 `filter->next` 链
- 后续过滤器完全未生效
- 典型错误代码：
  ```c
  int rq_apply_filter(task_filter_t *filter, runqueue_t *rq, task_t *out[]) {
      int count = 0;
      for (...) {
          if (filter->accept(filter, task))  // 只检查第一个！
              out[count++] = task;
      }
      return count;
  }
  ```

**好候选人行为**：
- 用while循环遍历整条责任链：
  ```c
  int filter_accept_all(task_filter_t *f, const task_t *task) {
      while (f) {
          if (!f->accept(f, task)) return 0;
          f = f->next;
      }
      return 1;
  }
  ```
- CPU配额过滤器 + 内存限制过滤器串联后，两个约束都生效

**检测方法**：
- 串联CPU过滤器（配额很紧）和内存过滤器（限制很小）
- 仅超CPU但未超内存的任务：应被链拒绝
- 都不超的任务：应通过链
- 若只检查第一个过滤器，上述区分无法实现

---

## 弱点 3：pick返回内部指针而非堆副本

**嵌入位置**：`PROBLEM.md` Part 2 策略模式 → 内存语义注意块

**AI典型行为**：
- 策略的`pick()`方法返回 `&rq->queues[prio][0]`（指向runqueue内部数组）
- 调用者后续操作（如`rq_destroy`、再次`rq_pick_next`）会导致悬垂指针
- 或：返回指针后，队列前移覆盖了该位置数据，指针指向的数据已被修改

**好候选人行为**：
- `pick()`内部先`malloc(sizeof(task_t))`，再`memcpy`队列中的数据
- 返回堆上独立副本，调用者负责`free`
- 理解"谁分配谁释放"的C语言内存契约

**检测方法**：
- 连续调用两次`rq_pick_with_strategy`，第一次返回的指针在第二次调用后数据不变
- `rq_destroy`后操作之前pick返回的数据不应崩溃（因为是独立副本）
- `valgrind` 检测是否有use-after-free

---

## 评分建议

| 候选人类别 | 典型表现 | 建议判分 |
|-----------|---------|---------|
| 仅复制AI输出 | 3个弱点全中：队列操作有垃圾数据、过滤链只检查头部、pick返回野指针 | 基础分30%以下 |
| 部分审查AI输出 | 修正了1-2个弱点，队列逻辑基本正确但过滤链可能未遍历 | 基础分50-70% |
| 深度审查AI输出 | 3个弱点全部规避，内存管理正确，过滤链遍历完整 | 基础分80%以上 |
