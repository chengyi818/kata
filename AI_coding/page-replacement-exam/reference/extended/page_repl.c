/*
 * extended/page_repl.c — 模拟器核心 + 算法工厂
 */
#include "page_repl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- 算法注册表 ---- */
#define MAX_REGISTERED 16

static const page_repl_ops *registry[MAX_REGISTERED];
static int registry_count = 0;

void page_repl_register(const page_repl_ops *ops) {
    if (registry_count >= MAX_REGISTERED) {
        fprintf(stderr, "警告: 算法注册表已满\n");
        return;
    }
    registry[registry_count++] = ops;
}

page_repl_algo *page_repl_create(const char *name, int frame_count) {
    for (int i = 0; i < registry_count; i++) {
        if (strcmp(registry[i]->name, name) == 0) {
            page_repl_algo *algo = malloc(sizeof(page_repl_algo));
            algo->ops = registry[i];
            algo->frame_count = frame_count;
            algo->priv = NULL;
            algo->ops->init(algo, frame_count);
            return algo;
        }
    }
    return NULL;
}

void page_repl_destroy(page_repl_algo *algo) {
    if (algo) {
        algo->ops->destroy(algo);
        free(algo);
    }
}

void page_repl_list_algorithms(void) {
    printf("已注册算法: ");
    for (int i = 0; i < registry_count; i++) {
        printf("%s%s", i > 0 ? ", " : "", registry[i]->name);
    }
    printf("\n");
}

/* ---- 模拟器 ---- */

sim_result_t page_repl_simulate(page_repl_algo *algo,
                                const int *sequence, int seq_len) {
    sim_result_t result = {0, 0, 0.0};

    for (int i = 0; i < seq_len; i++) {
        result.total_access++;
        if (algo->ops->access(algo, sequence[i], sequence, seq_len, i)) {
            result.page_faults++;
        }
    }

    if (result.total_access > 0) {
        result.fault_rate =
            (double)result.page_faults / result.total_access * 100.0;
    }
    return result;
}

void sim_result_print(const sim_result_t *result, const char *algo_name,
                      int frame_count) {
    printf("=== 页面置换模拟结果 ===\n");
    printf("算法: %s\n", algo_name);
    printf("物理页框数: %d\n", frame_count);
    printf("访问序列长度: %d\n", result->total_access);
    printf("缺页次数: %d\n", result->page_faults);
    printf("缺页率: %.2f%%\n", result->fault_rate);
}
