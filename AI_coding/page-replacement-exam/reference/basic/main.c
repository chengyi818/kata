/*
 * basic/main.c — 基础部分参考实现
 * 简单的FIFO页面置换模拟器，单文件，无抽象层
 * 展示基础部分预期的代码质量
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAGES 1024

typedef struct {
    int *frames;
    int frame_count;
    int next_victim;   /* FIFO: 下一个被换出的页框索引 */
    int loaded;        /* 已装载的页数 */
    int page_faults;
    int total_access;
} fifo_sim_t;

void fifo_sim_init(fifo_sim_t *sim, int frame_count) {
    sim->frames = malloc(frame_count * sizeof(int));
    sim->frame_count = frame_count;
    sim->next_victim = 0;
    sim->loaded = 0;
    sim->page_faults = 0;
    sim->total_access = 0;
    for (int i = 0; i < frame_count; i++) {
        sim->frames[i] = -1; /* -1 表示空页框 */
    }
}

void fifo_sim_destroy(fifo_sim_t *sim) {
    free(sim->frames);
}

int fifo_sim_access(fifo_sim_t *sim, int page) {
    sim->total_access++;

    /* 查找页面是否已在页框中 */
    for (int i = 0; i < sim->frame_count; i++) {
        if (sim->frames[i] == page) {
            return 0; /* 命中 */
        }
    }

    /* 缺页 */
    sim->page_faults++;

    if (sim->loaded < sim->frame_count) {
        /* 有空闲页框，直接装入 */
        sim->frames[sim->loaded] = page;
        sim->loaded++;
    } else {
        /* 所有页框已满，换出next_victim指向的页面 */
        sim->frames[sim->next_victim] = page;
        sim->next_victim = (sim->next_victim + 1) % sim->frame_count;
    }
    return 1; /* 缺页 */
}

void fifo_sim_print_result(const fifo_sim_t *sim, const char *algo_name) {
    double fault_rate = sim->total_access > 0
        ? (double)sim->page_faults / sim->total_access * 100.0
        : 0.0;

    printf("=== 页面置换模拟结果 ===\n");
    printf("算法: %s\n", algo_name);
    printf("物理页框数: %d\n", sim->frame_count);
    printf("访问序列长度: %d\n", sim->total_access);
    printf("缺页次数: %d\n", sim->page_faults);
    printf("缺页率: %.2f%%\n", fault_rate);
}

int parse_sequence(const char *input, int *seq, int max_len) {
    int len = 0;
    const char *p = input;
    while (*p && len < max_len) {
        /* 跳过空格 */
        while (*p == ' ' || *p == '\t' || *p == '\n') p++;
        if (!*p) break;

        char *end;
        long val = strtol(p, &end, 10);
        if (end == p) break; /* 无法解析 */

        seq[len++] = (int)val;
        p = end;
    }
    return len;
}

int main(int argc, char *argv[]) {
    int frame_count = 4;
    const char *input_str = NULL;

    if (argc >= 2) {
        frame_count = atoi(argv[1]);
    }
    if (argc >= 3) {
        input_str = argv[2];
    }

    /* 默认测试序列 — Belady异常经典序列 */
    const char *default_seq = "7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1";
    if (!input_str) input_str = default_seq;

    int sequence[MAX_PAGES];
    int seq_len = parse_sequence(input_str, sequence, MAX_PAGES);

    if (seq_len == 0) {
        fprintf(stderr, "错误: 无法解析访问序列\n");
        return 1;
    }
    if (frame_count <= 0) {
        fprintf(stderr, "错误: 页框数必须大于0\n");
        return 1;
    }

    fifo_sim_t sim;
    fifo_sim_init(&sim, frame_count);

    printf("访问序列: ");
    for (int i = 0; i < seq_len; i++) {
        printf("%d ", sequence[i]);
        fifo_sim_access(&sim, sequence[i]);
    }
    printf("\n\n");

    fifo_sim_print_result(&sim, "FIFO");
    fifo_sim_destroy(&sim);
    return 0;
}
