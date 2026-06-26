/*
 * tests/test_page_algo.c — 页面置换算法单元测试
 *
 * 编译: gcc -std=c99 -Wall -o test_page_algo test_page_algo.c \
 *         ../参考实现/extended/page_repl.c ../参考实现/extended/fifo.c \
 *         ../参考实现/extended/lru.c ../参考实现/extended/clock.c \
 *         ../参考实现/extended/optimal.c
 *
 * 运行: ./test_page_algo
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* 直接包含实现文件（测试用），或链接目标文件 */
#include "../参考实现/extended/page_repl.h"

/* ---- 测试框架 ---- */
static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;
static const char *current_suite = "";

#define TEST_SUITE(name) do { current_suite = name; printf("\n[%s]\n", name); } while(0)

static void check_int(const char *desc, int expected, int actual) {
    tests_run++;
    if (expected == actual) {
        printf("  PASS: %s (expected=%d)\n", desc, expected);
        tests_passed++;
    } else {
        printf("  FAIL: %s (expected=%d, got=%d)\n", desc, expected, actual);
        tests_failed++;
    }
}

static void check_double(const char *desc, double expected, double actual, double eps) {
    tests_run++;
    if (fabs(expected - actual) < eps) {
        printf("  PASS: %s (expected=%.2f)\n", desc, expected);
        tests_passed++;
    } else {
        printf("  FAIL: %s (expected=%.2f, got=%.2f)\n", desc, expected, actual);
        tests_failed++;
    }
}

static void check_not_null(const char *desc, void *ptr) {
    tests_run++;
    if (ptr != NULL) {
        printf("  PASS: %s\n", desc);
        tests_passed++;
    } else {
        printf("  FAIL: %s (expected non-NULL)\n", desc);
        tests_failed++;
    }
}

/* ---- 辅助: 运行模拟 ---- */
static sim_result_t run_sim(const char *algo_name, int frames,
                            const int *seq, int len) {
    page_repl_algo *algo = page_repl_create(algo_name, frames);
    sim_result_t r = page_repl_simulate(algo, seq, len);
    page_repl_destroy(algo);
    return r;
}

/* ================================================================
 * 测试用例
 * ================================================================ */

/*
 * 经典参考序列 (Belady异常序列):
 *   7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
 *
 * 已知结果 (3帧):
 *   FIFO    : 15 faults (75.00%)
 *   LRU     : 12 faults (60.00%)
 *   Optimal :  9 faults (45.00%)
 */
static const int classic_seq[] = {
    7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1
};
static const int classic_len = 20;

void test_fifo_classic(void) {
    TEST_SUITE("FIFO — 经典序列 (3帧)");
    sim_result_t r = run_sim("FIFO", 3, classic_seq, classic_len);
    check_int("总访问次数", 20, r.total_access);
    check_int("缺页次数", 15, r.page_faults);
    check_double("缺页率", 75.00, r.fault_rate, 0.01);
}

void test_fifo_belady_anomaly(void) {
    TEST_SUITE("FIFO — Belady异常验证");
    /* 4帧时FIFO的缺页次数反而比3帧多 */
    sim_result_t r3 = run_sim("FIFO", 3, classic_seq, classic_len);
    sim_result_t r4 = run_sim("FIFO", 4, classic_seq, classic_len);

    check_int("3帧缺页次数", 15, r3.page_faults);
    /* Belady异常: 4帧时FIFO为10次, 大于某些3帧序列结果 */
    /* 但对于这个序列, 3帧15次, 4帧10次 — 没有异常 */
    /* 换一个序列来验证 */
    int belady_seq[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    r3 = run_sim("FIFO", 3, belady_seq, 12);
    r4 = run_sim("FIFO", 4, belady_seq, 12);
    check_int("Belady 3帧缺页", 9, r3.page_faults);
    check_int("Belady 4帧缺页(应>3帧)", 10, r4.page_faults);
    if (r4.page_faults > r3.page_faults)
        printf("  INFO: Belady异常已确认 (4帧%d次 > 3帧%d次)\n",
               r4.page_faults, r3.page_faults);
}

void test_lru_classic(void) {
    TEST_SUITE("LRU — 经典序列 (3帧)");
    sim_result_t r = run_sim("LRU", 3, classic_seq, classic_len);
    check_int("总访问次数", 20, r.total_access);
    check_int("缺页次数", 12, r.page_faults);
    check_double("缺页率", 60.00, r.fault_rate, 0.01);
}

void test_optimal_classic(void) {
    TEST_SUITE("Optimal — 经典序列 (3帧)");
    sim_result_t r = run_sim("Optimal", 3, classic_seq, classic_len);
    check_int("总访问次数", 20, r.total_access);
    check_int("缺页次数", 9, r.page_faults);
    check_double("缺页率", 45.00, r.fault_rate, 0.01);
}

void test_clock_basic(void) {
    TEST_SUITE("Clock — 基本功能");
    /* Clock近似LRU，结果应介于FIFO和LRU之间或等于LRU */
    sim_result_t r = run_sim("Clock", 3, classic_seq, classic_len);
    printf("  INFO: Clock 缺页次数=%d (FIFO=15, LRU=12, Optimal=9)\n",
           r.page_faults);
    /* Clock至少应优于FIFO */
    if (r.page_faults <= 15)
        printf("  PASS: Clock 缺页次数 <= FIFO\n");
    else
        printf("  FAIL: Clock 缺页次数 > FIFO\n");
}

/* ---- 边界测试 ---- */

void test_empty_sequence(void) {
    TEST_SUITE("边界 — 空序列");
    int empty[] = {};
    sim_result_t r = run_sim("FIFO", 4, empty, 0);
    check_int("空序列缺页次数", 0, r.page_faults);
    check_double("空序列缺页率", 0.0, r.fault_rate, 0.01);
}

void test_single_frame(void) {
    TEST_SUITE("边界 — 单页框");
    int seq[] = {1, 2, 1, 3, 2};
    /* 单页框下任何不同页都会缺页 */
    sim_result_t r = run_sim("FIFO", 1, seq, 5);
    check_int("单页框序列缺页", 5, r.page_faults);
    check_double("单页框序列缺页率", 100.0, r.fault_rate, 0.01);
}

void test_all_same_pages(void) {
    TEST_SUITE("边界 — 全部相同页号");
    int seq[] = {42, 42, 42, 42, 42};
    sim_result_t r = run_sim("FIFO", 3, seq, 5);
    check_int("全相同页号缺页", 1, r.page_faults); /* 仅首次 */
}

void test_frames_larger_than_sequence(void) {
    TEST_SUITE("边界 — 页框数大于序列长度");
    int seq[] = {1, 2, 3};
    sim_result_t r = run_sim("FIFO", 10, seq, 3);
    check_int("页框大于序列时缺页", 3, r.page_faults);
}

/* ---- 多算法一致性测试 ---- */

void test_algorithms_same_result_full(void) {
    TEST_SUITE("一致性 — 序列唯一时所有算法结果相同");
    /* 当页框数 >= 不同页号数时，所有算法结果应相同 */
    int seq[] = {1, 2, 3, 4, 1, 2, 3, 4};
    sim_result_t r_fifo = run_sim("FIFO", 4, seq, 8);
    sim_result_t r_lru  = run_sim("LRU",  4, seq, 8);
    sim_result_t r_opt  = run_sim("Optimal", 4, seq, 8);

    check_int("FIFO (满帧)", 4, r_fifo.page_faults);
    check_int("LRU  (满帧)", 4, r_lru.page_faults);
    check_int("Optimal (满帧)", 4, r_opt.page_faults);
}

void test_algorithms_all(void) {
    TEST_SUITE("跨算法 — 经典序列不同帧数对比");

    int frame_counts[] = {1, 2, 3, 4, 5};
    const char *algos[] = {"FIFO", "LRU", "Clock", "Optimal"};

    printf("  帧数 | FIFO | LRU  | Clock | Optimal\n");
    printf("  -----+------+------+-------+--------\n");
    for (int fi = 0; fi < 5; fi++) {
        printf("  %4d |", frame_counts[fi]);
        for (int ai = 0; ai < 4; ai++) {
            sim_result_t r = run_sim(algos[ai], frame_counts[fi],
                                     classic_seq, classic_len);
            printf(" %4d |", r.page_faults);
        }
        printf("\n");
    }
}

/* ---- 工厂模式测试 ---- */

void test_factory(void) {
    TEST_SUITE("工厂模式 — 算法注册与创建");

    page_repl_algo *algo;

    algo = page_repl_create("FIFO", 4);
    check_not_null("创建FIFO", algo);
    page_repl_destroy(algo);

    algo = page_repl_create("LRU", 4);
    check_not_null("创建LRU", algo);
    page_repl_destroy(algo);

    algo = page_repl_create("Clock", 4);
    check_not_null("创建Clock", algo);
    page_repl_destroy(algo);

    algo = page_repl_create("Optimal", 4);
    check_not_null("创建Optimal", algo);
    page_repl_destroy(algo);

    algo = page_repl_create("UnknownAlgo", 4);
    if (algo == NULL)
        printf("  PASS: 未知算法返回NULL\n");
    else {
        printf("  FAIL: 未知算法应返回NULL\n");
        page_repl_destroy(algo);
    }
}

/* ---- 内存泄漏检查辅助 ---- */
void test_create_destroy_cycle(void) {
    TEST_SUITE("稳定性 — 多次创建/销毁");
    for (int i = 0; i < 1000; i++) {
        page_repl_algo *algo = page_repl_create("FIFO", 4);
        int seq[] = {7, 0, 1, 2};
        page_repl_simulate(algo, seq, 4);
        page_repl_destroy(algo);
    }
    printf("  PASS: 1000次创建/销毁无崩溃\n");
    tests_passed++;
    tests_run++;
}

/* ---- 主函数 ---- */

int main(void) {
    printf("========================================\n");
    printf("  页面置换算法 — 单元测试\n");
    printf("========================================\n");

    test_fifo_classic();
    test_fifo_belady_anomaly();
    test_lru_classic();
    test_optimal_classic();
    test_clock_basic();

    test_empty_sequence();
    test_single_frame();
    test_all_same_pages();
    test_frames_larger_than_sequence();

    test_algorithms_same_result_full();
    test_algorithms_all();

    test_factory();
    test_create_destroy_cycle();

    printf("\n========================================\n");
    printf("  测试结果: %d/%d 通过, %d 失败\n",
           tests_passed, tests_run, tests_failed);
    printf("========================================\n");

    return tests_failed > 0 ? 1 : 0;
}
