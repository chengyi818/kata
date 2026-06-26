/******************************************************************************
 * scheduler.c  –  Process Scheduler Simulator (Skeleton)
 *
 * AI辅助编程机试题 — 考生需要完成本文件中所有 TODO 标记的部分。
 *
 * 文件结构:
 *   1. 公共辅助函数          (已实现)
 *   2. Part 1: round_robin_schedule  (TODO — 基础部分)
 *   3. Part 2: Strategy 实现         (TODO — 扩展部分)
 *   4. Part 2: Template Method       (TODO — 扩展部分)
 *   5. Part 3: 设计文档              (TODO — 写在文件顶部注释中)
 *
 * 编译:  gcc -Wall -Wextra -o scheduler scheduler.c test_runner.c -lm
 ******************************************************************************/

#include "scheduler.h"

/* ================================================================
 * CFS weight lookup table  (Linux kernel sched/prio_to_weight)
 *
 *  index = nice + 20    (nice ∈ [-20, 19])
 * ================================================================ */
static const int prio_to_weight[40] = {
    /* -20 */ 88761, 71755, 56483, 46273, 36291,
    /* -15 */ 29154, 23254, 18705, 14949, 11916,
    /* -10 */  9548,  7620,  6100,  4904,  3906,
    /*  -5 */  3121,  2501,  1991,  1586,  1277,
    /*   0 */  1024,   820,   655,   526,   423,
    /*   5 */   335,   272,   215,   172,   137,
    /*  10 */   110,    87,    70,    56,    45,
    /*  15 */    36,    29,    23,    18,    15,
};


/* ================================================================
 *  Common helpers  (pre-implemented — do NOT modify)
 * ================================================================ */

void process_init(Process *p, int pid, int priority,
                  int burst, int arrival)
{
    p->pid             = pid;
    p->priority        = priority;
    p->burst_time      = burst;
    p->remaining_time  = burst;
    p->arrival_time    = arrival;
    p->start_time      = -1;
    p->completion_time = 0;
    p->waiting_time    = 0;
    p->turnaround_time = 0;
    p->vruntime        = 0.0;
    p->weight          = priority_to_weight(priority);
}

double avg_waiting_time(const Process processes[], int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++) sum += processes[i].waiting_time;
    return sum / n;
}

double avg_turnaround_time(const Process processes[], int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++) sum += processes[i].turnaround_time;
    return sum / n;
}

void print_schedule_table(const Process processes[], int n)
{
    printf("\n%-6s %-6s %-8s %-9s %-7s %-12s %-9s %-12s\n",
           "Proc", "PID", "Burst", "Arrival", "Start",
           "Completion", "Waiting", "Turnaround");
    printf("------ ------ -------- --------- ------- "
           "------------ --------- ------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%-5d %-6d %-8d %-9d %-7d %-12d %-9d %-12d\n",
               i, processes[i].pid,
               processes[i].burst_time,
               processes[i].arrival_time,
               processes[i].start_time,
               processes[i].completion_time,
               processes[i].waiting_time,
               processes[i].turnaround_time);
    }
    printf("\nAverage Waiting Time:    %.2f\n",
           avg_waiting_time(processes, n));
    printf("Average Turnaround Time: %.2f\n\n",
           avg_turnaround_time(processes, n));
}

int priority_to_weight(int priority)
{
    if (priority < -20) priority = -20;
    if (priority >  19) priority =  19;
    return prio_to_weight[priority + 20];
}

double vruntime_delta(int weight)
{
    return (double)NICE_0_LOAD / weight;
}


/* ================================================================
 *  PART 1 — Basic Round-Robin Scheduler  [TODO for candidate]
 * ================================================================
 *
 * 实现要求:
 *   - 模拟 Round-Robin 调度过程
 *   - 正确处理不同到达时间 (arrival_time)
 *   - 记录每个进程的 start_time, completion_time,
 *     waiting_time, turnaround_time
 *
 * 提示:
 *   可使用简单的循环队列保存就绪进程索引
 *   ready queue:  int queue[MAX_PROCESSES], head, tail
 *   时间片过期且未完成 → 重新入队
 *   进程完成 → 不重新入队
 *   无可运行进程时 CPU 空闲 (current_time++)
 *
 * 伪代码:
 *   sort processes by arrival_time (stable)
 *   rq = empty queue
 *   for time = 0; all_done == false; time++:
 *       for each process p with arrival_time == time: rq.push(p)
 *       if rq.empty(): continue
 *       proc = rq.pop()
 *       if proc.start_time == -1: proc.start_time = time
 *       run_units = min(time_quantum, proc.remaining_time)
 *       for t = 0; t < run_units; t++:
 *           time++  (or handle in outer loop — both fine)
 *           proc.remaining_time--
 *           for each p with arrival_time == time: rq.push(p)
 *       if proc.remaining_time == 0:
 *           proc.completion_time = time
 *           proc.turnaround_time = time - proc.arrival_time
 *           proc.waiting_time    = turnaround - proc.burst_time
 *       else:
 *           rq.push(proc)
 * ================================================================ */

void round_robin_schedule(Process processes[], int n, int time_quantum)
{
    /*
     * ============================================================
     * TODO: 在此实现 Round-Robin 调度
     * ============================================================
     */

    (void)processes;
    (void)n;
    (void)time_quantum;
}


/* ================================================================
 *  PART 2 — Strategy Implementations  [TODO for candidate]
 *
 * 每个策略必须实现 select_func 签名 (见 scheduler.h).
 * 返回值:  就绪进程的索引, 或 -1 (无可运行进程)
 *
 * 设计约束:
 *   - 策略之间互相独立
 *   - 添加新策略只需新增 creator + select 函数
 *   - 不得修改 SchedStrategy / SchedulerContext / scheduler_run
 * ================================================================ */

/* ---- FCFS — First-Come First-Served (non-preemptive) ---- */
/* 一旦进程开始运行就执行到结束 */

typedef struct {
    int dummy;  /* FCFS 无状态, 仅用于类型一致 */
} FCFSData;

static int fcfs_select(void *data, Process procs[], int n,
                       int ready[], int current_time,
                       int current, int slice_used)
{
    /* ============================================================
     * TODO: FCFS 选择逻辑
     *   if current 还在就绪态: 让它继续运行
     *   else: 选择 ready[] 中索引最小的进程
     * ============================================================ */

    (void)data; (void)procs; (void)n; (void)ready;
    (void)current_time; (void)current; (void)slice_used;
    return -1;
}


/* ---- SJF — Shortest Job First (non-preemptive) ---- */
/* 选择 burst_time 最小的就绪进程, 运行至完成 */

static int sjf_select(void *data, Process procs[], int n,
                      int ready[], int current_time,
                      int current, int slice_used)
{
    /* ============================================================
     * TODO: SJF 非抢占选择逻辑
     *   if current 还在就绪态: 继续运行
     *   else: 选择 burst_time 最小的就绪进程
     *   (burst_time 是原始值, 不是 remaining_time)
     * ============================================================ */

    (void)data; (void)procs; (void)n; (void)ready;
    (void)current_time; (void)current; (void)slice_used;
    return -1;
}


/* ---- SRTF — Shortest Remaining Time First (preemptive) ---- */
/* 每个 tick 都重新选择 remaining_time 最小的进程 */

static int srtf_select(void *data, Process procs[], int n,
                       int ready[], int current_time,
                       int current, int slice_used)
{
    /* ============================================================
     * TODO: SRTF 抢占式选择逻辑
     *   每个 tick 都选择 remaining_time 最小的就绪进程
     *   可能抢占当前运行进程
     * ============================================================ */

    (void)data; (void)procs; (void)n; (void)ready;
    (void)current_time; (void)current; (void)slice_used;
    return -1;
}


/* ---- Priority Scheduling (preemptive) ---- */
/* 每次选择 priority 值最小的进程 (nice 越低, 实际优先级越高) */

static int priority_select(void *data, Process procs[], int n,
                           int ready[], int current_time,
                           int current, int slice_used)
{
    /* ============================================================
     * TODO: 抢占式优先级选择逻辑
     *   每个 tick 选择 priority (nice值) 最小的就绪进程
     *   priority 相同 → 选择 pid 较小的 (FCFS tie-break)
     * ============================================================ */

    (void)data; (void)procs; (void)n; (void)ready;
    (void)current_time; (void)current; (void)slice_used;
    return -1;
}


/* ---- Round Robin (time-slice based) ---- */

typedef struct {
    int quantum;
    int cursor;   /* 下一个搜索起点 (维持 RR 顺序) */
} RRData;

static int rr_select(void *data, Process procs[], int n,
                     int ready[], int current_time,
                     int current, int slice_used)
{
    /* ============================================================
     * TODO: RR 选择逻辑
     *   if current 存在 && 就绪 && slice_used < quantum: return current
     *   else: 从 (current+1)%n 开始循环查找下一个就绪进程
     *   没有其他进程时返回同一进程 (继续运行)
     *   更新 cursor 以维持 RR 顺序
     * ============================================================ */

    (void)data; (void)procs; (void)n; (void)ready;
    (void)current_time; (void)current; (void)slice_used;
    return -1;
}


/* ---- CFS Simplified — Completely Fair Scheduler ---- */
/*
 * CFS 核心思想:
 *   - 每个进程有 vruntime (虚拟运行时间)
 *   - vruntime 增量 = 实际运行时间 × (NICE_0_LOAD / weight)
 *   - 优先级高的进程 weight 大, vruntime 增长慢 → 获得更多 CPU
 *   - 每次调度选择 vruntime 最小的就绪进程
 *
 * 本实现中 vruntime 由模板方法 scheduler_run() 在每个 tick 更新。
 * 本函数仅需选择 vruntime 最小的就绪进程。
 */

static int cfs_select(void *data, Process procs[], int n,
                      int ready[], int current_time,
                      int current, int slice_used)
{
    /* ============================================================
     * TODO: CFS 选择逻辑
     *   遍历所有就绪进程, 返回 vruntime 最小的那个
     *   使用 1e18 作为最小值的初始值 (代替 INFINITY)
     * ============================================================ */

    (void)data; (void)procs; (void)n; (void)ready;
    (void)current_time; (void)current; (void)slice_used;
    return -1;
}


/* ================================================================
 *  Strategy Constructors  [TODO for candidate]
 *
 * 每个构造函数:
 *   1. malloc SchedStrategy + 策略私有数据
 *   2. 设置 name / data / select_next / destroy
 *   3. 返回指针
 * ================================================================ */

static void default_destroy(SchedStrategy *s)
{
    free(s->data);
    free(s);
}

SchedStrategy *create_fcfs_strategy(void)
{
    /* TODO: 创建 FCFS 策略 */
    return NULL;
}

SchedStrategy *create_sjf_strategy(void)
{
    /* TODO: 创建 SJF 策略 */
    return NULL;
}

SchedStrategy *create_srtf_strategy(void)
{
    /* TODO: 创建 SRTF 策略 */
    return NULL;
}

SchedStrategy *create_priority_strategy(void)
{
    /* TODO: 创建 Priority 策略 */
    return NULL;
}

SchedStrategy *create_rr_strategy(int quantum)
{
    /* TODO: 创建 RR 策略, quantum 存入 RRData */
    (void)quantum;
    return NULL;
}

SchedStrategy *create_cfs_strategy(void)
{
    /* TODO: 创建 CFS 策略 */
    return NULL;
}


/* ================================================================
 *  PART 2 — Scheduler Template Method  [TODO for candidate]
 * ================================================================ */

void scheduler_init(SchedulerContext *ctx,
                    Process processes[], int n)
{
    ctx->processes    = processes;
    ctx->n            = n;
    ctx->current_time = 0;
    ctx->current_proc = -1;
    ctx->slice_used   = 0;
    ctx->done_count   = 0;
    ctx->strategy     = NULL;

    ctx->ready     = (int *)calloc((size_t)n, sizeof(int));
    ctx->completed = (int *)calloc((size_t)n, sizeof(int));
}

void scheduler_destroy(SchedulerContext *ctx)
{
    if (ctx->strategy && ctx->strategy->destroy)
        ctx->strategy->destroy(ctx->strategy);
    free(ctx->ready);
    free(ctx->completed);
    ctx->ready     = NULL;
    ctx->completed = NULL;
}

void scheduler_set_strategy(SchedulerContext *ctx,
                            SchedStrategy *strategy)
{
    /* 安全销毁旧策略 */
    if (ctx->strategy && ctx->strategy->destroy)
        ctx->strategy->destroy(ctx->strategy);
    ctx->strategy = strategy;
}

/*
 * scheduler_run() — Template Method (模板方法)
 *
 * 这是调度循环的骨架, 独立于具体算法.
 * 算法相关的决策通过 ctx->strategy->select_next() 委托给策略对象.
 *
 * 模板方法步骤:
 *   while done_count < n:
 *     1. 将 arrival_time <= current_time 的新到达进程标记为 ready
 *     2. 调用 strategy->select_next(...) 获取下一个要运行的进程
 *     3. 如果返回 -1 (没有就绪进程): 空闲, current_time++, continue
 *     4. 如果返回的进程与 current_proc 不同: 上下文切换,
 *        更新 current_proc, 重置 slice_used,
 *        如果首次运行则记录 start_time
 *     5. 运行该进程 1 个时间单位:
 *        - remaining_time--
 *        - vruntime += vruntime_delta(weight)   (CFS 机制)
 *        - slice_used++, current_time++
 *     6. 如果是当前时间单位内新到达的进程, 标记为 ready
 *     7. 如果进程运行结束 (remaining_time == 0):
 *        - completion_time = current_time
 *        - turnaround_time = completion_time - arrival_time
 *        - waiting_time    = turnaround_time - burst_time
 *        - 标记完成, done_count++
 *        - current_proc = -1, slice_used = 0
 *
 * 注意:
 *   - 本函数内部不得出现针对特定算法的 if/else 或 switch
 *   - 所有算法差异由 strategy 封装
 */

void scheduler_run(SchedulerContext *ctx)
{
    /*
     * ============================================================
     * TODO: 实现模板方法调度循环
     * ============================================================
     */

    (void)ctx;
}
