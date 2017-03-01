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
    INT8 cpuset_msk;
    UINT32 belong_core_id;

    UINT32 exec_start;
    UINT32 exec_length;
    UINT32 exec_used;

    WEIGHT_VAL weight;
    UINT32 priority;
    UINT32 real_priority;

    struct task_struct * Next;
    struct task_struct * Pre;
}Task_Struct;

typedef struct core {
    UINT32 core_id;
    History * pHistory;
    UINT32 curr_prio;
    Task_Struct * curr;
    struct core * Next;
    struct core * Pre;
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

UINT32 check_SetAffinity_parm(PROC_ID pid, INT8 cpuset_msk);
UINT32 set_proc_affinity(PROC_ID pid, INT8 cpuset_msk);

UINT32 try_to_clear_core_list();
UINT32 try_to_clear_runqueue();

UINT32 __effective_prio(Task_Struct*);
Task_Struct* __select_task_struct(PROC_ID pid);

bool is_runqueue_over();
bool is_time_window();
void clear_proc_belong_cpu();
void refresh_all_core();
void refresh_all_proc();
void sort_for_all_proc();
void update_prio_all_core();
void __update_prio_per_core(Core* pCore_temp);
void sort_for_all_core();

void __switch_task_struct(Task_Struct* pTask_Struct_start, Task_Struct* pTask_Struct_end);
void __switch_core(Core* pCore_start, Core*  pCore_end);

Core* __pop_core_list();
History* __pop_history_list(Core* pCore_Temp);
Task_Struct* __pop_runqueue();
void __try_to_clear_core(Core* pCore_Temp);

void show_history();
void __show_history_per_core(Core* pCore);
#endif /* __PROCESS_MANAGER_H__ */
