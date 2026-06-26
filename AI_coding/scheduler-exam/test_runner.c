/******************************************************************************
 * test_runner.c  —  Automated test harness for the scheduler exam
 *
 * 编译:  gcc -Wall -Wextra -o scheduler scheduler.c test_runner.c -lm
 * 运行:  ./scheduler
 * 保存:  ./scheduler > output.txt
 *
 * 本文件无需修改.  候选人只需确保 scheduler.c 通过所有测试.
 ******************************************************************************/

#include "scheduler.h"

/* ================================================================
 *  Test data  (所有进程同时到达, 便于验证调度正确性)
 * ================================================================ */
static void load_test_processes(Process procs[], int *n)
{
    *n = 4;
    process_init(&procs[0], 1,  0,  5, 0);  /* P0: normal priority */
    process_init(&procs[1], 2,  2,  3, 0);  /* P1: low priority     */
    process_init(&procs[2], 3, -5,  8, 0);  /* P2: high priority    */
    process_init(&procs[3], 4,  0,  6, 0);  /* P3: normal priority  */
}

/* ================================================================
 *  Part 1 — Basic Round-Robin test
 * ================================================================ */
static void test_basic_rr(void)
{
    printf("========================================\n");
    printf("  PART 1: Basic Round-Robin (q=3)\n");
    printf("========================================\n");

    Process procs[MAX_PROCESSES];
    int n;
    load_test_processes(procs, &n);

    round_robin_schedule(procs, n, 3);
    print_schedule_table(procs, n);

    /* Simple sanity checks */
    for (int i = 0; i < n; i++) {
        if (procs[i].completion_time == 0 && procs[i].start_time == -1) {
            printf("[WARN] P%d 似乎未被调度 — "
                   "检查 round_robin_schedule 实现\n", i);
            return;
        }
    }

    printf("Expected avg waiting ~10.00, avg turnaround ~15.50\n");
    printf("(If your output differs, double-check the ready-queue logic)\n");
}

/* ================================================================
 *  Part 2 — Extensible Scheduler: test all strategies
 * ================================================================ */
typedef struct {
    const char   *name;
    SchedStrategy *(*create)(void);
    int            quantum;   /* only used by RR */
} StrategyEntry;

static void test_extended_strategies(void)
{
    printf("\n========================================\n");
    printf("  PART 2: Extensible Scheduler\n");
    printf("========================================\n");

    /* --------  helper: create RR with quantum = 3 -------- */
    SchedStrategy *maker_rr_q3(void) {
        return create_rr_strategy(3);
    }

    StrategyEntry strategies[] = {
        { "FCFS",             create_fcfs_strategy,     0 },
        { "SJF (non-preempt)", create_sjf_strategy,      0 },
        { "SRTF (preempt)",    create_srtf_strategy,     0 },
        { "Priority (preempt)",create_priority_strategy, 0 },
        { "RR (q=3)",          maker_rr_q3,             3 },
        { "CFS-Simplified",    create_cfs_strategy,      0 },
        { NULL, NULL, 0 }
    };

    for (StrategyEntry *e = strategies; e->name != NULL; e++) {
        /* fresh processes for each strategy */
        Process procs[MAX_PROCESSES];
        int n;
        load_test_processes(procs, &n);

        SchedulerContext ctx;
        scheduler_init(&ctx, procs, n);

        SchedStrategy *st = e->create();
        if (st == NULL) {
            printf("\n--- %s ---\n", e->name);
            printf("[SKIP] Strategy not yet implemented "
                   "(constructor returns NULL)\n");
            scheduler_destroy(&ctx);
            continue;
        }

        scheduler_set_strategy(&ctx, st);

        printf("\n--- %s ---\n", e->name);
        scheduler_run(&ctx);
        print_schedule_table(ctx.processes, ctx.n);

        /* Quick sanity: every process should have a completion_time */
        int ok = 1;
        for (int i = 0; i < n; i++) {
            if (ctx.processes[i].completion_time == 0 &&
                ctx.processes[i].start_time == -1) {
                ok = 0;
                break;
            }
        }
        if (!ok)
            printf("[WARN] Some processes were not scheduled!\n");

        scheduler_destroy(&ctx);
    }
}

/* ================================================================
 *  OCP verification  (informational)
 * ================================================================ */
static void test_ocp_check(void)
{
    printf("\n========================================\n");
    printf("  OCP VERIFICATION CHECKLIST\n");
    printf("========================================\n");
    printf("Adding a new strategy (e.g. MLFQ) requires:\n");
    printf("  [ ] A new select function   (new .c file OK)\n");
    printf("  [ ] A new creator function  (new .c file OK)\n");
    printf("  [ ] NO change to SchedStrategy struct\n");
    printf("  [ ] NO change to select_func signature\n");
    printf("  [ ] NO change to SchedulerContext struct\n");
    printf("  [ ] NO change to scheduler_run()\n");
    printf("  [ ] NO change to scheduler_init() / destroy()\n");
    printf("\nIf ALL boxes above are checked, OCP is satisfied.\n\n");
}

/* ================================================================
 *  main
 * ================================================================ */
int main(void)
{
    test_basic_rr();
    test_extended_strategies();
    test_ocp_check();
    return 0;
}
