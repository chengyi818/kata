#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define MAX_PROCESSES  64
#define NICE_0_LOAD   1024

/* ================================================================
 * Process structure
 *
 * Fields align with Linux task_struct scheduling concepts:
 *   priority  → nice value (-20 highest, 19 lowest)
 *   weight    → CFS weight derived from nice (prio_to_weight[])
 *   vruntime  → virtual runtime (CFS fair scheduling metric)
 * ================================================================ */
typedef struct {
    int    pid;
    int    priority;         /* nice value: -20 (highest) ~ 19 (lowest) */
    int    burst_time;       /* total CPU burst required */
    int    remaining_time;   /* remaining CPU burst */
    int    arrival_time;     /* when the process enters the system */
    int    start_time;       /* first time scheduled (-1 if never) */
    int    completion_time;  /* finished at this time */
    int    waiting_time;     /* = turnaround_time - burst_time */
    int    turnaround_time;  /* = completion_time - arrival_time */
    double vruntime;         /* virtual runtime (CFS metric) */
    int    weight;           /* CFS weight (looked up from nice) */
} Process;

/* ================================================================
 * PART 1 — Basic Round-Robin Scheduler
 *
 * This is a stand-alone, monolithic implementation.  Candidates
 * hard-code the RR algorithm inside round_robin_schedule().
 * ================================================================ */

void process_init(Process *p, int pid, int priority,
                  int burst, int arrival);

void round_robin_schedule(Process processes[], int n, int time_quantum);

double avg_waiting_time(const Process processes[], int n);

double avg_turnaround_time(const Process processes[], int n);

void print_schedule_table(const Process processes[], int n);

/* ================================================================
 * PART 2 — Extensible Scheduler (Strategy + Template Method)
 *
 * The candidate refactors the stand-alone scheduler into a
 * framework where the *scheduling policy* is a pluggable strategy
 * and the *scheduling loop* is a template method.
 * ================================================================ */

/* ---- Strategy interface (vtable pattern in C) ---- */

typedef struct SchedStrategy SchedStrategy;

/*
 * select_func — every scheduling tick the framework asks the
 *               strategy which process should run next.
 *
 * Parameters:
 *   data         – strategy-private state (e.g. RR quantum)
 *   processes[]  – all processes (entire array)
 *   n            – number of processes
 *   ready[]      – ready[i] != 0  ⇔ process i is ready
 *   current_time – elapsed simulation ticks
 *   current      – index of process currently on CPU, -1 if idle
 *   slice_used   – consecutive ticks current has been running
 *
 * Returns:  index of next process, or -1 if nothing ready
 */
typedef int (*select_func)(void *data,
                           Process processes[], int n,
                           int ready[],
                           int current_time,
                           int current,
                           int slice_used);

struct SchedStrategy {
    const char *name;              /* human-readable label */
    void       *data;             /* strategy-private state */
    select_func select_next;      /* the policy decision */
    void      (*destroy)(SchedStrategy *self);
};

/* ---- Scheduler context (hosts the template method) ---- */

typedef struct {
    Process        *processes;
    int             n;
    int             current_time;
    int             current_proc;    /* index or -1 (idle) */
    int             slice_used;
    int            *ready;           /* ready[i] in {0,1} */
    int            *completed;       /* completed[i] in {0,1} */
    int             done_count;
    SchedStrategy  *strategy;
} SchedulerContext;

/* Template method — invariant scheduling loop               */
/* The loop skeleton never changes; policy decisions are     */
/* delegated to ctx->strategy->select_next().                */
void scheduler_init(SchedulerContext *ctx,
                    Process processes[], int n);

void scheduler_destroy(SchedulerContext *ctx);

void scheduler_set_strategy(SchedulerContext *ctx,
                            SchedStrategy *strategy);

void scheduler_run(SchedulerContext *ctx);

/* ---- Strategy constructors (factory functions) ---- */

SchedStrategy *create_fcfs_strategy(void);
SchedStrategy *create_sjf_strategy(void);       /* non-preemptive */
SchedStrategy *create_srtf_strategy(void);      /* preemptive SJF  */
SchedStrategy *create_priority_strategy(void);  /* preemptive       */
SchedStrategy *create_rr_strategy(int quantum);
SchedStrategy *create_cfs_strategy(void);       /* simplified CFS   */

/* ---- CFS helpers ---- */

int    priority_to_weight(int priority);
double vruntime_delta(int weight);

#endif /* SCHEDULER_H */
