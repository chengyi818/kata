/*
 * runqueue.h — Linux Runqueue 任务队列管理器
 *
 * 模拟 Linux 内核的 runqueue 数据结构，管理多优先级任务队列。
 * 基础部分：硬编码严格优先级调度
 * 扩展部分：策略模式 + 装饰器模式实现可插拔调度与过滤
 */

#ifndef RUNQUEUE_H
#define RUNQUEUE_H

#include <stddef.h>

/* ================================================================
 * 常量定义
 * ================================================================ */

#define RQ_MAX_PRIO   5    /* 优先级数量：0(最高) ~ 4(最低)            */
#define RQ_MAX_TASKS  256  /* 单个优先级队列最大任务数                */
#define MAX_TASK_NAME 32   /* 任务名字最大长度                       */

/* nice 值范围（用于 CFS 扩展） */
#define NICE_MIN     (-20)
#define NICE_MAX     19

/* CFS 默认参数 */
#define CFS_DEFAULT_WEIGHT  1024
#define CFS_MIN_GRANULARITY 1000000ULL   /* 1ms，纳秒单位              */
#define CFS_BASE_SLICE      30000000ULL  /* 30ms 默认时间片            */

/* ================================================================
 * 任务状态与数据结构
 * ================================================================ */

typedef enum {
    TASK_RUNNING = 0,   /* 就绪/运行中 */
    TASK_WAITING,       /* 等待事件    */
    TASK_STOPPED        /* 已停止      */
} task_state_t;

typedef struct {
    int  tid;                      /* 任务ID（唯一）                  */
    int  priority;                 /* 优先级 0..RQ_MAX_PRIO-1         */
    int  nice;                     /* nice值 -20..+19                 */
    task_state_t state;            /* 当前状态                        */
    char name[MAX_TASK_NAME];      /* 任务名称                        */

    /* ---- 扩展字段（基础部分可不使用） ---- */
    unsigned long long vruntime;   /* 虚拟运行时间 (ns)，CFS 使用      */
    unsigned int       weight;     /* CFS 权重，由 nice 值计算         */
    unsigned long long exec_time;  /* 累计执行时间 (ns)               */
    int                cpu_id;     /* 亲和 CPU ID（负载均衡用）        */
    void              *ext_data;   /* 扩展数据指针（装饰器使用）       */
} task_t;

/* ================================================================
 * Runqueue 数据结构
 * ================================================================ */

typedef struct {
    /*
     * 基础实现：queues[i] 是一个固定大小的 task_t 数组
     *   - sizes[i]  : 队列 i 的当前长度
     *   - capacities[i] : 队列 i 的容量
     *
     * 提示：扩展时你可能需要将 task_t 数组改为 task_t* 指针数组，
     * 以支持装饰器模式中对同一 task 的共享引用。
     */
    task_t *queues[RQ_MAX_PRIO];
    int     sizes[RQ_MAX_PRIO];
    int     capacities[RQ_MAX_PRIO];
    int     total;                  /* 总任务数                        */

    /* ---- 扩展字段（基础部分不用） ---- */
    unsigned long long min_vruntime; /* CFS：当前最小 vruntime          */
} runqueue_t;

/* ================================================================
 * 基础 API（Part 1 — 必须实现）
 * ================================================================ */

/**
 * rq_init — 初始化 runqueue
 * @rq: 指向未初始化的 runqueue_t
 *
 * 为每个优先级队列分配初始内存（容量 = 64），所有计数器清零。
 */
void rq_init(runqueue_t *rq);

/**
 * rq_enqueue — 将任务加入对应优先级队列
 * @rq:   runqueue
 * @task: 要入队的任务（值拷贝）
 *
 * 根据 task->priority 将任务放入 queues[priority] 的末尾。
 * 只接受 TASK_RUNNING 状态的任务。
 *
 * 返回: 0=成功, -1=队列已满, -2=状态无效, -3=优先级越界
 */
int rq_enqueue(runqueue_t *rq, const task_t *task);

/**
 * rq_dequeue — 按 tid 从 runqueue 中移除任务
 * @rq:  runqueue
 * @tid: 要移除的任务ID
 *
 * 遍历所有优先级队列查找匹配的任务。
 * 找到后，将后面的任务前移（保持顺序）。
 *
 * 返回: 0=成功, -1=未找到
 */
int rq_dequeue(runqueue_t *rq, int tid);

/**
 * rq_pick_next — 选择下一个要执行的任务（严格优先级）
 * @rq: runqueue
 *
 * 调度逻辑（请在此函数内硬编码实现）：
 *   1. 从 prio=0 开始遍历所有优先级
 *   2. 返回第一个非空队列的队首任务
 *   3. 被选中的任务从队列中移除（后面的前移）
 *   4. 如果所有队列为空，返回 NULL
 *
 * 调用者负责释放返回的 task_t* 内存（free）。
 *
 * 返回: 堆上分配的任务副本，或 NULL
 */
task_t *rq_pick_next(runqueue_t *rq);

/**
 * rq_change_priority — 变更任务的优先级和 nice 值
 * @rq:       runqueue
 * @tid:      目标任务ID
 * @new_prio: 新优先级 (0..RQ_MAX_PRIO-1)
 * @new_nice: 新 nice 值 (-20..+19)
 *
 * 从原队列中移除任务，修改其 priority/nice，重新入队到新队列。
 * 保持任务在原队列中的相对顺序（其他任务前移）。
 *
 * 返回: 0=成功, -1=任务未找到, -2=参数越界
 */
int rq_change_priority(runqueue_t *rq, int tid, int new_prio, int new_nice);

/**
 * rq_destroy — 销毁 runqueue，释放所有内存
 * @rq: runqueue
 */
void rq_destroy(runqueue_t *rq);

/**
 * rq_is_empty — 检查 runqueue 是否为空
 * @rq: runqueue
 * 返回: 1=为空, 0=非空
 */
int rq_is_empty(const runqueue_t *rq);

/**
 * rq_size — 返回 runqueue 中的总任务数
 * @rq: runqueue
 */
int rq_size(const runqueue_t *rq);

/* ================================================================
 * 扩展 API（Part 2 — 策略模式 + 装饰器模式）
 * ================================================================ */

/* ---- 策略模式：可插拔的任务选择 ---- */

typedef struct pick_strategy pick_strategy_t;

/**
 * pick_strategy_t — 任务选择策略接口
 *
 * 每种策略实现自己的 pick() 方法。
 * ctx 用于保存策略所需的私有数据（如 CFS 的最小 vruntime 跟踪）。
 */
struct pick_strategy {
    task_t *(*pick)(pick_strategy_t *self, runqueue_t *rq);
    void   *ctx;          /* 策略私有上下文 */
    void  (*destroy)(pick_strategy_t *self);  /* 析构 */
};

/**
 * strategy_strict_priority — 创建严格优先级策略
 *
 * 逻辑与基础版 rq_pick_next 相同。
 * 返回: 堆上分配的策略实例，调用者负责销毁
 */
pick_strategy_t *strategy_strict_priority(void);

/**
 * strategy_cfs — 创建 CFS（完全公平调度）策略
 *
 * 选择 vruntime 最小的 TASK_RUNNING 任务。
 * vruntime 增长公式：vruntime += delta_exec * (NICE_0_WEIGHT / weight)
 * weight 由 nice 值计算：weight = 1024 / (1.25 ^ nice)
 *
 * 返回: 堆上分配的 CFS 策略实例
 */
pick_strategy_t *strategy_cfs(void);

/**
 * strategy_load_balance — 创建带负载均衡的调度策略（加分项）
 *
 * @cpu_id:   当前 CPU ID
 * @num_cpus: CPU 总数
 *
 * 优先选择 cpu_id 亲和的任务，若无则从最繁忙的 CPU 窃取。
 * 返回: 堆上分配的负载均衡策略实例
 */
pick_strategy_t *strategy_load_balance(int cpu_id, int num_cpus);

/**
 * rq_pick_with_strategy — 使用指定策略从 runqueue 中选择任务
 * @rq:       runqueue
 * @strategy: 任务选择策略
 *
 * 委托给 strategy->pick() 完成实际选择。
 * 这是策略模式的入口——runqueue 不关心具体调度算法。
 *
 * 返回: 堆上分配的任务副本，或 NULL
 */
task_t *rq_pick_with_strategy(runqueue_t *rq, pick_strategy_t *strategy);

/* ---- 装饰器模式：可组合的任务过滤器 ---- */

typedef struct task_filter task_filter_t;

/**
 * task_filter_t — 任务过滤器接口（装饰器 + 责任链）
 *
 * accept() 返回 1 表示任务通过此过滤器。
 * next 指向链中的下一个过滤器，形成责任链。
 * ctx 用于保存过滤器的私有数据。
 */
struct task_filter {
    int  (*accept)(task_filter_t *self, const task_t *task);
    task_filter_t *next;   /* 责任链：下一个过滤器 */
    void *ctx;             /* 过滤器私有上下文     */
    void (*destroy)(task_filter_t *self);
};

/**
 * filter_cgroup_cpu — 创建 CPU 配额过滤器
 * @quota_us:  配额 (微秒)，如 50000 = 50ms
 * @period_us: 周期 (微秒)，如 100000 = 100ms
 *
 * 跟踪任务在周期内的 CPU 使用时间，超出配额则拒绝。
 * 返回: 堆上分配的过滤器实例
 */
task_filter_t *filter_cgroup_cpu(unsigned int quota_us, unsigned int period_us);

/**
 * filter_cgroup_mems — 创建内存限制过滤器
 * @max_mem_mb: 内存上限 (MB)
 *
 * 检查任务的 ext_data 中记录的内存使用量，超出则拒绝。
 * 返回: 堆上分配的过滤器实例
 */
task_filter_t *filter_cgroup_mems(unsigned int max_mem_mb);

/**
 * filter_chain — 将两个过滤器串联成责任链
 * @first:  第一个过滤器
 * @second: 第二个过滤器
 *
 * 调用 first->accept()，通过后再调用 second->accept()。
 * 全部通过才算通过。
 *
 * 返回: first（其 next 已指向 second）
 */
task_filter_t *filter_chain(task_filter_t *first, task_filter_t *second);

/**
 * rq_apply_filter — 对 runqueue 应用过滤器链，筛选通过的任务
 * @filter:    过滤器链（可以是单个或链式）
 * @rq:        runqueue
 * @out_tasks: 输出数组（调用者分配，至少 RQ_MAX_TASKS 大小）
 *
 * 遍历 runqueue 中所有任务，对每个任务调用 filter->accept()。
 * 通过的任务指针存入 out_tasks。
 *
 * 返回: 通过过滤的任务数量
 */
int rq_apply_filter(task_filter_t *filter, runqueue_t *rq,
                    task_t *out_tasks[]);

/**
 * rq_update_vruntime — 更新任务的虚拟运行时间（CFS辅助函数）
 * @task:         目标任务
 * @delta_exec:   本次执行的纳秒数
 *
 * 公式: vruntime += delta_exec * NICE_0_WEIGHT / weight
 */
void rq_update_vruntime(task_t *task, unsigned long long delta_exec);

/**
 * nice_to_weight — 将 nice 值转换为 CFS 权重
 * @nice: nice值 (-20..+19)
 *
 * 近似公式: weight ≈ 1024 / (1.25 ^ nice)
 * 返回: 计算出的权重值
 */
unsigned int nice_to_weight(int nice);

#endif /* RUNQUEUE_H */
