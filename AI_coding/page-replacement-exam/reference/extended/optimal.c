/*
 * extended/optimal.c — Optimal (最佳/理论最优) 页面置换算法
 *
 * 换出策略: 选择在未来最长时间内不会被使用的页面换出
 *           (如果某页面未来不再使用，则优先换出)
 * 注: 此算法需要预知整个访问序列，实际系统中无法实现，
 *     仅作为理论最优上界用于性能评估基准
 *
 * 时间复杂度: 命中O(n), 缺页O(n * m) — n为页框数, m为剩余序列长度
 */
#include "page_repl.h"
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *frames;
    int  loaded;
} optimal_priv_t;

static void optimal_init(page_repl_algo *algo, int frame_count) {
    optimal_priv_t *p = malloc(sizeof(optimal_priv_t));
    p->frames = malloc(frame_count * sizeof(int));
    for (int i = 0; i < frame_count; i++) p->frames[i] = -1;
    p->loaded = 0;
    algo->priv = p;
}

/*
 * 计算page在未来访问序列中的下一次出现位置
 * 从seq[pos+1]开始查找，未找到返回INT_MAX(永不再用)
 */
static int next_use(const int *seq, int seq_len, int pos, int page) {
    for (int i = pos + 1; i < seq_len; i++) {
        if (seq[i] == page) return i;
    }
    return INT_MAX;
}

static int optimal_access(page_repl_algo *algo, int page,
                          const int *seq, int seq_len, int pos) {
    optimal_priv_t *p = algo->priv;
    int fc = algo->frame_count;

    /* 查找命中 */
    for (int i = 0; i < fc; i++) {
        if (p->frames[i] == page) return 0;
    }

    /* 缺页 — 有空闲页框直接使用 */
    if (p->loaded < fc) {
        p->frames[p->loaded++] = page;
        return 1;
    }

    /* 缺页 — 所有页框已满，选择最佳换出目标
     * 对每个页框中的页面，计算其下一次被使用的位置
     * 选择最远的那个换出
     */
    int victim = 0;
    int farthest = -1;

    for (int i = 0; i < fc; i++) {
        int dist = next_use(seq, seq_len, pos, p->frames[i]);
        if (dist > farthest) {
            farthest = dist;
            victim = i;
        }
    }

    p->frames[victim] = page;
    return 1;
}

static void optimal_destroy(page_repl_algo *algo) {
    optimal_priv_t *p = algo->priv;
    free(p->frames);
    free(p);
}

const page_repl_ops optimal_ops = {
    .name    = "Optimal",
    .init    = optimal_init,
    .access  = optimal_access,
    .destroy = optimal_destroy,
};

__attribute__((constructor))
static void optimal_register(void) {
    page_repl_register(&optimal_ops);
}
