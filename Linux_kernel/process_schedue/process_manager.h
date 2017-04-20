/*=============================================================================
#     FileName: process_manager.h
#         Desc:
#       Author: ChengYi
#        Email: chengyi818@foxmail.com
#     HomePage:
#      Created: 2017-03-01 14:18:50
#      Version: 0.0.1
#   LastChange: 2017-03-01 14:18:50
#      History:
#               0.0.1 | ChengYi | init
=============================================================================*/

#ifndef __PROCESS_MANAGER_H__
#define __PROCESS_MANAGER_H__

#include "basic.h"

#define NORMAL_TASK_PRIO_OFFSET 100
/*进程状态 */
typedef enum {
    PREPARE,
    RUNNING,
    STOPPED
} PROC_STAT;

typedef struct history {
    PROC_ID pid ;
    struct history * Next;
} History;

typedef struct task_struct {
    PROC_ID pid;
    PROC_STAT state;
    SCHED_TYPE type;
    UINT32 affinity;
    UINT32 belong_core_id;

    UINT32 exec_start;
    UINT32 exec_length;
    UINT32 exec_used;
    UINT32 exex_used_per_window;

    WEIGHT_VAL weight;
    UINT32 priority;
    UINT32 real_priority;

    struct task_struct * Next;

    UINT32 be_dispatched;
}Task_Struct;

typedef struct core {
    UINT32 core_id;
    History * pHistory;
    UINT32 curr_rq_prio;

    Task_Struct * curr;
    struct core * Next;
} Core;

typedef struct process_manager{
    UINT32 core_num;
    UINT32 proc_num;
    UINT32 curr_timestamp;

    Task_Struct * pRunQueue;
    Core * pCore;
}Proc_Manager;

UINT32 check_Enable_Core_parm(UINT32 core_id);
Core* create_core(UINT32 core_id);
UINT32 insert_core(Core* pCore);

UINT32 check_AddProc_parm(PROC_ID pid, ProcInfo proc_info);
Task_Struct* create_task_struct(PROC_ID pid, ProcInfo proc_info);
UINT32 insert_proc(Task_Struct * pTask_Struct);

UINT32 check_SetAffinity_parm(PROC_ID pid, UINT32 affinity);
UINT32 set_proc_affinity(PROC_ID pid, UINT32 affinity);

UINT32 __check_proc_info_parm(ProcInfo proc_info);
UINT32 check_QueryCpuStat_parm(UINT32 core_id);

UINT32 try_to_clear_core_list();
UINT32 try_to_clear_runqueue();

UINT32 __effective_prio(Task_Struct*);
Task_Struct* __select_task_struct(PROC_ID pid);
Core* __select_core_by_id(UINT32 core_id);

UINT32 is_runqueue_over();
UINT32 is_time_window();
void clear_proc_belong_cpu();
void refresh_all_core();
void refresh_all_proc();
void sort_for_all_proc();
void update_prio_all_core();
void __update_prio_per_core(Core* pCore_temp);
void sort_for_all_core();

Task_Struct* select_first_no_dispatch_proc();
void dispatch_proc(Task_Struct* pTask_Struct_temp);
UINT32 __is_allowed_by_affinity(Core* pCore_temp, Task_Struct* pTask_Struct_temp);

void scheduler_tick();
void update_all_core_timestamp();
void __add_history_for_curr(Core* pCore);
void __update_timestamp_for_curr_proc(Core* pCore);

UINT32 is_core_free();
UINT32 is_proc_need_dispatch();
Core* __pop_core_list();
History* __pop_history_list(Core* pCore_Temp);
Task_Struct* __pop_runqueue();
void __try_to_clear_core(Core* pCore_Temp);

void show_history();
void __show_history_per_core(Core* pCore);
void __show_runqueue();
void __show_core_list();
void __show_dispatch_result();

Task_Struct *mergeSortedList_Proc(Task_Struct *L1, Task_Struct *L2);
Task_Struct *listMergeSort_Proc(Task_Struct* head);
Core *mergeSortedList_Core(Core *L1, Core *L2);
Core *listMergeSort_Core(Core* head);
#endif /* __PROCESS_MANAGER_H__ */
