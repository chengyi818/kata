/*
 * extended/lru.c — LRU (最近最少使用) 页面置换算法
 *
 * 换出策略: 选择最长时间未被访问的页面换出
 * 实现: 为每个页框维护最后访问时间戳，换出时选时间戳最小的
 * 时间复杂度: 命中O(n), 缺页O(n) — n为页框数
 */
#include "page_repl.h"
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *frames;
    int *last_used;    /* 每个页框的最后访问时间戳, -1表示空 */
    int timestamp;     /* 逻辑时钟，每次访问递增 */
} lru_priv_t;

static void lru_init(page_repl_algo *algo, int frame_count) {
    lru_priv_t *p = malloc(sizeof(lru_priv_t));
    p->frames = malloc(frame_count * sizeof(int));
    p->last_used = malloc(frame_count * sizeof(int));
    for (int i = 0; i < frame_count; i++) {
        p->frames[i] = -1;
        p->last_used[i] = -1;
    }
    p->timestamp = 0;
    algo->priv = p;
}

static int lru_access(page_repl_algo *algo, int page,
                      const int *seq, int seq_len, int pos) {
    (void)seq; (void)seq_len; (void)pos;
    lru_priv_t *p = algo->priv;
    int fc = algo->frame_count;

    /* 查找命中 */
    for (int i = 0; i < fc; i++) {
        if (p->frames[i] == page) {
            p->last_used[i] = p->timestamp++;
            return 0;
        }
    }

    /* 缺页 — 找到换出目标 */
    int victim = 0;
    int oldest = INT_MAX;

    for (int i = 0; i < fc; i++) {
        if (p->frames[i] == -1) {
            victim = i;
            break;
        }
        if (p->last_used[i] < oldest) {
            oldest = p->last_used[i];
            victim = i;
        }
    }

    p->frames[victim] = page;
    p->last_used[victim] = p->timestamp++;
    return 1;
}

static void lru_destroy(page_repl_algo *algo) {
    lru_priv_t *p = algo->priv;
    free(p->frames);
    free(p->last_used);
    free(p);
}

const page_repl_ops lru_ops = {
    .name    = "LRU",
    .init    = lru_init,
    .access  = lru_access,
    .destroy = lru_destroy,
};

__attribute__((constructor))
static void lru_register(void) {
    page_repl_register(&lru_ops);
}
