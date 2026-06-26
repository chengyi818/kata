/*
 * extended/fifo.c — FIFO (先进先出) 页面置换算法
 *
 * 换出策略: 选择驻留时间最长的页面换出
 * 实现: 维护循环队列指针 next_victim
 * 时间复杂度: 命中O(n), 缺页O(n) — 其中n为页框数
 */
#include "page_repl.h"
#include <stdlib.h>

typedef struct {
    int *frames;
    int next_victim;
    int loaded;
} fifo_priv_t;

static void fifo_init(page_repl_algo *algo, int frame_count) {
    fifo_priv_t *p = malloc(sizeof(fifo_priv_t));
    p->frames = malloc(frame_count * sizeof(int));
    for (int i = 0; i < frame_count; i++) p->frames[i] = -1;
    p->next_victim = 0;
    p->loaded = 0;
    algo->priv = p;
}

static int fifo_access(page_repl_algo *algo, int page,
                       const int *seq, int seq_len, int pos) {
    (void)seq; (void)seq_len; (void)pos; /* 未使用 */
    fifo_priv_t *p = algo->priv;
    int fc = algo->frame_count;

    for (int i = 0; i < fc; i++) {
        if (p->frames[i] == page) return 0;
    }

    if (p->loaded < fc) {
        p->frames[p->loaded++] = page;
    } else {
        p->frames[p->next_victim] = page;
        p->next_victim = (p->next_victim + 1) % fc;
    }
    return 1;
}

static void fifo_destroy(page_repl_algo *algo) {
    fifo_priv_t *p = algo->priv;
    free(p->frames);
    free(p);
}

const page_repl_ops fifo_ops = {
    .name    = "FIFO",
    .init    = fifo_init,
    .access  = fifo_access,
    .destroy = fifo_destroy,
};

/* 自动注册 — 通过gcc constructor在main()之前执行 */
__attribute__((constructor))
static void fifo_register(void) {
    page_repl_register(&fifo_ops);
}
