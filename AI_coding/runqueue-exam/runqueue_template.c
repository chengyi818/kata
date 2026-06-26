/*
 * runqueue_template.c — 任务队列管理器（候选人实现模板）
 *
 * 本文件包含：
 *   1. 已提供: rq_init, rq_destroy, rq_is_empty, rq_size（辅助函数）
 *   2. 待实现: rq_enqueue, rq_dequeue, rq_pick_next, rq_change_priority
 *   3. 待实现: 策略模式 + 装饰器模式（扩展部分）
 *   4. 已提供: 测试 main()
 *
 * 实现说明：
 *   - 基础部分请使用硬编码的 for 循环实现优先级遍历
 *   - 扩展部分请使用策略模式/装饰器模式重构
 *   - 所有 TODO 标记的位置需要你填写代码
 *   - 不要修改函数签名
 */

#include "runqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================================================================
 * 辅助函数（已提供，可直接使用）
 * ================================================================ */

void rq_init(runqueue_t *rq)
{
    memset(rq, 0, sizeof(*rq));
    for (int i = 0; i < RQ_MAX_PRIO; i++) {
        rq->capacities[i] = 64;
        rq->queues[i] = (task_t *)malloc(sizeof(task_t) * rq->capacities[i]);
        rq->sizes[i] = 0;
    }
    rq->total = 0;
    rq->min_vruntime = 0;
}

void rq_destroy(runqueue_t *rq)
{
    for (int i = 0; i < RQ_MAX_PRIO; i++) {
        free(rq->queues[i]);
        rq->queues[i] = NULL;
        rq->sizes[i] = 0;
        rq->capacities[i] = 0;
    }
    rq->total = 0;
}

int rq_is_empty(const runqueue_t *rq)
{
    return rq->total == 0;
}

int rq_size(const runqueue_t *rq)
{
    return rq->total;
}

/* ================================================================
 * 基础部分 — 待实现函数
 * ================================================================ */

/**
 * TODO-1: rq_enqueue — 将任务加入对应优先级队列
 *
 * 步骤:
 *   1. 校验: priority 在 [0, RQ_MAX_PRIO) 范围内
 *   2. 校验: task->state 必须为 TASK_RUNNING
 *   3. 检查 queues[priority] 是否已满
 *   4. 将 task 追加到 queues[priority][sizes[priority]] 位置
 *   5. 更新 sizes[priority] 和 total
 *
 * 提示: 使用 memcpy 复制 task 内容到队列中
 */
int rq_enqueue(runqueue_t *rq, const task_t *task)
{
    /* ===== 你的代码从这里开始 ===== */

    /* TODO: 参数校验 */

    /* TODO: 容量检查 */

    /* TODO: 将 task 追加到对应优先级队列末尾 */

    /* TODO: 更新计数 */

    /* ===== 你的代码到这里结束 ===== */
    return -1;  /* 替换为正确的返回值 */
}

/**
 * TODO-2: rq_dequeue — 按 tid 从 runqueue 中移除任务
 *
 * 步骤:
 *   1. 遍历所有优先级队列 (prio = 0..RQ_MAX_PRIO-1)
 *   2. 在每个队列中遍历查找匹配的 tid
 *   3. 找到后: 将后续元素前移一位（memmove）
 *   4. 更新 sizes[prio] 和 total
 *   5. 如果未找到，返回 -1
 */
int rq_dequeue(runqueue_t *rq, int tid)
{
    /* ===== 你的代码从这里开始 ===== */

    /* TODO: 遍历所有优先级队列 */

    /* TODO: 在每个队列中查找匹配的 tid */

    /* TODO: 找到后，将后面元素前移 */

    /* TODO: 更新计数并返回 0 */

    /* ===== 你的代码到这里结束 ===== */
    return -1;
}

/**
 * TODO-3: rq_pick_next — 严格优先级调度（硬编码实现）
 *
 * 【重要】请在此函数内直接用 for 循环实现优先级遍历！
 * 扩展部分会将此逻辑重构为策略模式。
 *
 * 步骤:
 *   1. 从 prio=0 到 prio=RQ_MAX_PRIO-1 遍历
 *   2. 找到第一个 sizes[i] > 0 的队列
 *   3. 取该队列的队首任务 queues[i][0]
 *   4. 用 malloc 分配一个新的 task_t，复制队首任务的内容
 *   5. 将队列中后续元素前移（覆盖队首），更新 sizes[i] 和 total
 *   6. 返回分配的任务副本
 *   7. 如果所有队列为空，返回 NULL
 *
 * 调用者负责 free 返回的指针。
 */
task_t *rq_pick_next(runqueue_t *rq)
{
    /* ===== 你的代码从这里开始 ===== */

    /* TODO: 遍历优先级队列 prio = 0, 1, 2, 3, 4 */

    /* TODO: 找到第一个非空队列 */

    /* TODO: 取出队首任务，复制一份 */

    /* TODO: 前移剩余任务，更新计数 */

    /* ===== 你的代码到这里结束 ===== */
    return NULL;
}

/**
 * TODO-4: rq_change_priority — 变更任务优先级和 nice 值
 *
 * 步骤:
 *   1. 校验 new_prio 在 [0, RQ_MAX_PRIO) 范围内
 *   2. 校验 new_nice 在 [NICE_MIN, NICE_MAX] 范围内
 *   3. 遍历所有队列查找 tid 对应的任务
 *   4. 找到后: 复制任务，从旧队列移除（前移）
 *   5. 修改 priority 和 nice
 *   6. 调用 rq_enqueue 加入新队列
 *   7. 未找到则返回 -1
 */
int rq_change_priority(runqueue_t *rq, int tid, int new_prio, int new_nice)
{
    /* ===== 你的代码从这里开始 ===== */

    /* TODO: 参数校验 */

    /* TODO: 查找任务 */

    /* TODO: 从旧队列移除 */

    /* TODO: 修改属性并重新入队 */

    /* ===== 你的代码到这里结束 ===== */
    return -1;
}

/* ================================================================
 * 扩展部分 — 策略模式 + 装饰器模式（待实现）
 *
 * 提示:
 *   1. 先定义策略结构体（含 pick 函数指针和私有数据）
 *   2. 实现至少2种策略: strict_priority, cfs
 *   3. 将原 rq_pick_next 的逻辑迁移到 strict_priority 策略中
 *   4. 实现过滤器结构体（accept 函数指针 + next 链）
 *   5. 实现至少2种过滤器: cgroup_cpu, cgroup_mems
 * ================================================================ */

/* ---- 策略模式实现 ---- */

pick_strategy_t *strategy_strict_priority(void)
{
    /* TODO: 创建并返回严格优先级策略实例 */
    return NULL;
}

pick_strategy_t *strategy_cfs(void)
{
    /* TODO: 创建并返回 CFS 策略实例 */
    /* 提示: CFS 选择 vruntime 最小的 RUNNING 任务 */
    return NULL;
}

pick_strategy_t *strategy_load_balance(int cpu_id, int num_cpus)
{
    /* TODO (加分): 创建并返回负载均衡策略实例 */
    return NULL;
}

task_t *rq_pick_with_strategy(runqueue_t *rq, pick_strategy_t *strategy)
{
    /* TODO: 委托给 strategy->pick() */
    return NULL;
}

/* ---- 装饰器模式实现 ---- */

task_filter_t *filter_cgroup_cpu(unsigned int quota_us, unsigned int period_us)
{
    /* TODO: 创建 CPU 配额过滤器 */
    /* 提示: 在过滤器私有数据中跟踪 CPU 使用时间 */
    return NULL;
}

task_filter_t *filter_cgroup_mems(unsigned int max_mem_mb)
{
    /* TODO: 创建内存限制过滤器 */
    return NULL;
}

task_filter_t *filter_chain(task_filter_t *first, task_filter_t *second)
{
    /* TODO: 将 second 链接到 first 的 next，返回 first */
    return NULL;
}

int rq_apply_filter(task_filter_t *filter, runqueue_t *rq, task_t *out_tasks[])
{
    /* TODO: 遍历 runqueue 所有任务，筛选通过过滤器的任务 */
    return 0;
}

/* ---- 工具函数 ---- */

unsigned int nice_to_weight(int nice)
{
    /*
     * CFS 权重近似公式: weight ≈ 1024 / (1.25 ^ nice)
     *
     * 简化实现（查表法，精度足够）：
     */
    static const unsigned int weight_table[40] = {
        /* nice = -20 */ 88761,
        /* nice = -19 */ 71755,
        /* nice = -18 */ 56483,
        /* nice = -17 */ 46273,
        /* nice = -16 */ 36291,
        /* nice = -15 */ 29154,
        /* nice = -14 */ 23254,
        /* nice = -13 */ 18705,
        /* nice = -12 */ 14949,
        /* nice = -11 */ 11916,
        /* nice = -10 */  9548,
        /* nice =  -9 */  7620,
        /* nice =  -8 */  6100,
        /* nice =  -7 */  4904,
        /* nice =  -6 */  3906,
        /* nice =  -5 */  3121,
        /* nice =  -4 */  2501,
        /* nice =  -3 */  1991,
        /* nice =  -2 */  1586,
        /* nice =  -1 */  1277,
        /* nice =   0 */  1024,   /* NICE_0_WEIGHT */
        /* nice =  +1 */   820,
        /* nice =  +2 */   655,
        /* nice =  +3 */   526,
        /* nice =  +4 */   423,
        /* nice =  +5 */   335,
        /* nice =  +6 */   272,
        /* nice =  +7 */   215,
        /* nice =  +8 */   172,
        /* nice =  +9 */   137,
        /* nice = +10 */   110,
        /* nice = +11 */    87,
        /* nice = +12 */    70,
        /* nice = +13 */    56,
        /* nice = +14 */    45,
        /* nice = +15 */    36,
        /* nice = +16 */    29,
        /* nice = +17 */    23,
        /* nice = +18 */    18,
        /* nice = +19 */    15,
    };
    if (nice < NICE_MIN || nice > NICE_MAX)
        return CFS_DEFAULT_WEIGHT;
    return weight_table[nice - NICE_MIN];
}

void rq_update_vruntime(task_t *task, unsigned long long delta_exec)
{
    /*
     * vruntime 增长公式:
     *   vruntime += delta_exec * (NICE_0_WEIGHT / weight)
     *
     * 含义: nice 值越高(权重越低), vruntime 增长越快,
     *       调度器认为它已获得更多"虚拟时间", 因此更少被选中.
     */
    if (task->weight == 0)
        task->weight = CFS_DEFAULT_WEIGHT;

    task->vruntime += delta_exec * CFS_DEFAULT_WEIGHT / task->weight;
}

/* ================================================================
 * 测试用例（已提供）
 * ================================================================ */

static int test_base_runqueue(void)
{
    printf("========== 基础功能测试 ==========\n");

    runqueue_t rq;
    rq_init(&rq);

    /* 创建测试任务 */
    task_t t1 = { .tid = 1, .priority = 2, .nice = 0,
                  .state = TASK_RUNNING, .name = "task_low" };
    task_t t2 = { .tid = 2, .priority = 0, .nice = -5,
                  .state = TASK_RUNNING, .name = "task_high" };
    task_t t3 = { .tid = 3, .priority = 1, .nice = 5,
                  .state = TASK_RUNNING, .name = "task_mid" };
    task_t t4 = { .tid = 4, .priority = 0, .nice = -10,
                  .state = TASK_RUNNING, .name = "task_higher" };

    /* 入队 */
    printf("[TEST] enqueue... ");
    int ok = 1;
    ok &= (rq_enqueue(&rq, &t1) == 0);
    ok &= (rq_enqueue(&rq, &t2) == 0);
    ok &= (rq_enqueue(&rq, &t3) == 0);
    ok &= (rq_enqueue(&rq, &t4) == 0);
    printf("%s (total=%d)\n", ok ? "PASS" : "FAIL", rq_size(&rq));

    /* 验证出队顺序：严格优先级 → 先prio=0(FIFO), 再prio=1, 再prio=2 */
    printf("[TEST] pick_next order... ");

    task_t *p1 = rq_pick_next(&rq);   /* 应返回 t2 (prio=0, 先入队) */
    task_t *p2 = rq_pick_next(&rq);   /* 应返回 t4 (prio=0, 后入队) */
    task_t *p3 = rq_pick_next(&rq);   /* 应返回 t3 (prio=1)         */
    task_t *p4 = rq_pick_next(&rq);   /* 应返回 t1 (prio=2)         */
    task_t *p5 = rq_pick_next(&rq);   /* 应返回 NULL                */

    ok = 1;
    ok &= (p1 != NULL && p1->tid == 2);
    ok &= (p2 != NULL && p2->tid == 4);
    ok &= (p3 != NULL && p3->tid == 3);
    ok &= (p4 != NULL && p4->tid == 1);
    ok &= (p5 == NULL);
    ok &= (rq_is_empty(&rq));

    printf("%s\n", ok ? "PASS" : "FAIL");
    if (!ok) {
        printf("  p1 tid=%d (expected 2)\n", p1 ? p1->tid : -1);
        printf("  p2 tid=%d (expected 4)\n", p2 ? p2->tid : -1);
        printf("  p3 tid=%d (expected 3)\n", p3 ? p3->tid : -1);
        printf("  p4 tid=%d (expected 1)\n", p4 ? p4->tid : -1);
    }

    free(p1); free(p2); free(p3); free(p4);

    /* 测试 enqueue 边界情况 */
    printf("[TEST] boundary: empty dequeue... ");
    task_t *empty = rq_pick_next(&rq);
    printf("%s\n", empty == NULL ? "PASS" : "FAIL");
    free(empty);

    printf("[TEST] boundary: invalid state... ");
    task_t t_bad = { .tid = 99, .priority = 0, .nice = 0,
                     .state = TASK_WAITING, .name = "bad" };
    int ret = rq_enqueue(&rq, &t_bad);
    printf("%s (ret=%d)\n", ret != 0 ? "PASS" : "FAIL", ret);

    rq_destroy(&rq);
    return ok ? 0 : 1;
}

static int test_priority_change(void)
{
    printf("\n========== 优先级变更测试 ==========\n");

    runqueue_t rq;
    rq_init(&rq);

    task_t t1 = { .tid = 10, .priority = 3, .nice = 0,
                  .state = TASK_RUNNING, .name = "t10" };
    task_t t2 = { .tid = 20, .priority = 1, .nice = 0,
                  .state = TASK_RUNNING, .name = "t20" };

    rq_enqueue(&rq, &t1);
    rq_enqueue(&rq, &t2);

    /* 将 t1 的优先级提升到 0，应该比 t2 先出 */
    printf("[TEST] change priority... ");
    int ret = rq_change_priority(&rq, 10, 0, -5);
    printf("%s (ret=%d)\n", ret == 0 ? "PASS" : "FAIL", ret);

    task_t *p = rq_pick_next(&rq);
    printf("[TEST] after change, first pick is t10... ");
    printf("%s (tid=%d)\n", (p && p->tid == 10) ? "PASS" : "FAIL",
           p ? p->tid : -1);
    free(p);

    rq_destroy(&rq);
    return 0;
}

int main(void)
{
    int failures = 0;
    failures += test_base_runqueue();
    failures += test_priority_change();

    printf("\n===================================\n");
    if (failures == 0) {
        printf("  基础部分全部通过!\n");
        printf("  请继续实现扩展部分（策略模式 + 装饰器模式）\n");
    } else {
        printf("  基础部分存在 %d 个失败，请修复后继续\n", failures);
    }
    printf("===================================\n");

    return failures;
}
