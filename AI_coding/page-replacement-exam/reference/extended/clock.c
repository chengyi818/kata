/*
 * extended/clock.c — Clock (时钟/第二次机会) 页面置换算法
 *
 * 换出策略: 循环扫描页框，给引用位为1的页面"第二次机会"
 *          (清除引用位并跳过), 选择引用位为0的页面换出
 * 实现: 循环数组 + 引用位 + 时钟指针(hand)
 * 时间复杂度: 命中O(n), 缺页平均O(n)
 *
 * 这是 Linux 内核实际使用的近似LRU算法
 */
#include "page_repl.h"
#include <stdlib.h>

typedef struct {
    int  *frames;
    int  *ref_bit;    /* 引用位: 1=最近被访问过, 0=未被访问 */
    int   hand;        /* 时钟指针: 指向下一个候选换出页框 */
    int   loaded;
} clock_priv_t;

static void clock_init(page_repl_algo *algo, int frame_count) {
    clock_priv_t *p = malloc(sizeof(clock_priv_t));
    p->frames  = malloc(frame_count * sizeof(int));
    p->ref_bit = malloc(frame_count * sizeof(int));
    for (int i = 0; i < frame_count; i++) {
        p->frames[i] = -1;
        p->ref_bit[i] = 0;
    }
    p->hand   = 0;
    p->loaded = 0;
    algo->priv = p;
}

static int clock_access(page_repl_algo *algo, int page,
                        const int *seq, int seq_len, int pos) {
    (void)seq; (void)seq_len; (void)pos;
    clock_priv_t *p = algo->priv;
    int fc = algo->frame_count;

    /* 查找命中 — 设置引用位 */
    for (int i = 0; i < fc; i++) {
        if (p->frames[i] == page) {
            p->ref_bit[i] = 1;
            return 0;
        }
    }

    /* 缺页 — 如果有空闲页框，直接使用 */
    if (p->loaded < fc) {
        int slot = p->loaded;
        p->frames[slot] = page;
        p->ref_bit[slot] = 1;
        p->loaded++;
        return 1;
    }

    /* 缺页 — 所有页框已满，Clock算法选择换出页 */
    while (1) {
        if (p->ref_bit[p->hand] == 0) {
            /* 引用位为0，换出此页 */
            p->frames[p->hand] = page;
            p->ref_bit[p->hand] = 1;  /* 新装入的页引用位置1 */
            p->hand = (p->hand + 1) % fc;
            return 1;
        }
        /* 引用位为1 — 给予第二次机会: 清除引用位，移动指针 */
        p->ref_bit[p->hand] = 0;
        p->hand = (p->hand + 1) % fc;
    }
}

static void clock_destroy(page_repl_algo *algo) {
    clock_priv_t *p = algo->priv;
    free(p->frames);
    free(p->ref_bit);
    free(p);
}

const page_repl_ops clock_ops = {
    .name    = "Clock",
    .init    = clock_init,
    .access  = clock_access,
    .destroy = clock_destroy,
};

__attribute__((constructor))
static void clock_register(void) {
    page_repl_register(&clock_ops);
}
