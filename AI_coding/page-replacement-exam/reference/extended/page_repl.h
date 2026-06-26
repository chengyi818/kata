/*
 * extended/page_repl.h — 页面置换算法抽象接口（策略模式 + 工厂模式）
 *
 * 设计要点:
 *   - 使用C语言函数指针表(vtable)模拟多态 — Linux内核VFS惯用法
 *   - 策略接口(page_repl_ops)定义算法契约
 *   - 工厂函数支持按名称创建算法实例 — 满足开闭原则
 *   - 模拟器核心依赖抽象接口 — 满足依赖反转原则
 */
#ifndef PAGE_REPL_H
#define PAGE_REPL_H

#ifdef __cplusplus
extern "C" {
#endif

/* 前向声明 */
struct page_repl_algo;

/* ================================================================
 * 策略接口 (Strategy Interface) — C语言vtable模式
 * ================================================================ */
typedef struct {
    const char *name;   /* 算法名称，用于工厂查找 */

    /* 初始化算法内部状态，分配资源 */
    void (*init)(struct page_repl_algo *algo, int frame_count);

    /*
     * 处理一次页面访问
     * 返回: 0 = 命中(hit), 1 = 缺页(fault)
     * sequence/seq_len/pos : 仅Optimal算法需要(预知未来访问序列)
     *   其他算法忽略这些参数(传NULL/0/0即可)
     */
    int  (*access)(struct page_repl_algo *algo, int page,
                   const int *sequence, int seq_len, int pos);

    /* 释放算法持有的所有资源 */
    void (*destroy)(struct page_repl_algo *algo);
} page_repl_ops;

/* ================================================================
 * Context — 算法实例
 * ================================================================ */
typedef struct page_repl_algo {
    const page_repl_ops *ops;   /* 指向策略接口实现 */
    int frame_count;            /* 物理页框数量 */
    void *priv;                 /* 算法私有数据 */
} page_repl_algo;

/* ================================================================
 * 工厂函数 (Factory)
 * ================================================================ */

/* 按名称创建算法实例，成功返回非NULL，失败返回NULL */
page_repl_algo *page_repl_create(const char *name, int frame_count);

/* 销毁算法实例，释放所有资源 */
void page_repl_destroy(page_repl_algo *algo);

/* 注册自定义算法 — 支持外部扩展（无需修改page_repl.c） */
void page_repl_register(const page_repl_ops *ops);

/* 列出所有已注册的算法名称（调试用） */
void page_repl_list_algorithms(void);

/* ================================================================
 * 模拟器
 * ================================================================ */

typedef struct {
    int total_access;   /* 总访问次数 */
    int page_faults;    /* 缺页次数 */
    double fault_rate;  /* 缺页率 (百分比) */
} sim_result_t;

/* 运行模拟: 使用指定算法和访问序列，返回统计结果 */
sim_result_t page_repl_simulate(page_repl_algo *algo,
                                const int *sequence, int seq_len);

/* 打印模拟结果 */
void sim_result_print(const sim_result_t *result, const char *algo_name,
                      int frame_count);

#ifdef __cplusplus
}
#endif

#endif /* PAGE_REPL_H */
