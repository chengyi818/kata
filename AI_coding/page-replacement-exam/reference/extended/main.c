/*
 * extended/main.c — 扩展版本演示程序
 *
 * 编译: make
 * 运行: ./page_sim [帧数] [算法名] [序列字符串]
 * 示例: ./page_sim 3 FIFO "7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1"
 */
#include "page_repl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAGES 1024

static int parse_sequence(const char *input, int *seq, int max_len) {
    int len = 0;
    const char *p = input;
    while (*p && len < max_len) {
        while (*p == ' ' || *p == '\t' || *p == '\n') p++;
        if (!*p) break;
        char *end;
        long val = strtol(p, &end, 10);
        if (end == p) break;
        seq[len++] = (int)val;
        p = end;
    }
    return len;
}

int main(int argc, char *argv[]) {
    int frame_count = 4;
    const char *algo_name = "FIFO";
    const char *input_str = "7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1";

    if (argc >= 2) frame_count = atoi(argv[1]);
    if (argc >= 3) algo_name   = argv[2];
    if (argc >= 4) input_str   = argv[3];

    if (frame_count <= 0) {
        fprintf(stderr, "错误: 页框数必须 > 0\n");
        return 1;
    }

    int sequence[MAX_PAGES];
    int seq_len = parse_sequence(input_str, sequence, MAX_PAGES);

    if (seq_len == 0) {
        fprintf(stderr, "错误: 访问序列为空或无法解析\n");
        return 1;
    }

    /* 列出所有可用算法 */
    page_repl_list_algorithms();

    /* 通过工厂创建算法实例 */
    page_repl_algo *algo = page_repl_create(algo_name, frame_count);
    if (!algo) {
        fprintf(stderr, "错误: 未知算法 '%s'\n", algo_name);
        return 1;
    }

    /* 运行模拟 */
    printf("\n访问序列: ");
    for (int i = 0; i < seq_len; i++) printf("%d ", sequence[i]);
    printf("\n\n");

    sim_result_t result = page_repl_simulate(algo, sequence, seq_len);
    sim_result_print(&result, algo->ops->name, frame_count);

    page_repl_destroy(algo);
    return 0;
}
