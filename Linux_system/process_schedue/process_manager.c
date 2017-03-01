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

#include <stdio.h>
#include <stdlib.h>
#include "process_manager.h"

extern Proc_Manager *pProc_Manager;

UINT32 check_Enable_Core_parm(UINT32 core_id) {
    return API_RTN_OK;
}

Core* create_core(UINT32 core_id) {
    printf("create core_id: %d\n", core_id);
    Core* pCore_temp = (Core*)malloc(sizeof(Core));

    pCore_temp->core_id = core_id;
    pCore_temp->pHistory = NULL;
    pCore_temp->curr_prio = 0xFFFFFFFF;
    pCore_temp->curr = NULL;
    pCore_temp->Next = NULL;
    pCore_temp->Pre = NULL;

    return pCore_temp;
}

UINT32 insert_core(Core* pCore_temp) {
    if(pProc_Manager->pCore == NULL) {
        pProc_Manager->pCore =pCore_temp;
    } else {
        Core* pTemp = pProc_Manager->pCore;
        while(pTemp->Next != NULL)
            pTemp=pTemp->Next;
        pTemp->Next = pCore_temp;
        pCore_temp->Pre = pTemp;
    }

    pProc_Manager->core_num += 1;
    return API_RTN_OK;
}


UINT32 check_AddProc_parm(PROC_ID pid, ProcInfo proc_info) {
    return API_RTN_OK;
}

Task_Struct* create_task_struct(PROC_ID pid, ProcInfo proc_info) {
    printf("create Task_Struct id: %d\n", pid);
    Task_Struct* pTask_Struct_temp = (Task_Struct*)malloc(sizeof(Task_Struct));
    pTask_Struct_temp->pid = pid;
    pTask_Struct_temp->state = PREPARE;
    pTask_Struct_temp->type = proc_info.type;
    pTask_Struct_temp->cpuset_msk = 0xFF;
    pTask_Struct_temp->belong_core_id = 0xFFFFFFFF;

    pTask_Struct_temp->exec_start = proc_info.exec_start;
    pTask_Struct_temp->exec_length = proc_info.exec_length;
    pTask_Struct_temp->exec_used = 0;

    if(proc_info.type == SCHED_NORMAL) {
        pTask_Struct_temp->weight = proc_info.weight;
        pTask_Struct_temp->priority = 0xFFFFFFFF;
    } else {
        pTask_Struct_temp->weight = WEIGHT_NONE;
        pTask_Struct_temp->priority = proc_info.priority;
    }
    __effective_prio(pTask_Struct_temp);

    pTask_Struct_temp->Next = NULL;
    pTask_Struct_temp->Pre = NULL;

    return pTask_Struct_temp;
}

UINT32 insert_proc(Task_Struct * pTask_Struct) {
    if(pProc_Manager->pRunQueue == NULL) {
        pProc_Manager->pRunQueue =pTask_Struct;
    } else {
        Task_Struct* pTemp = pProc_Manager->pRunQueue;
        while(pTemp->Next != NULL)
            pTemp=pTemp->Next;
        pTemp->Next = pTask_Struct;
        pTask_Struct->Pre = pTemp;
    }
    pProc_Manager->proc_num += 1;

    return API_RTN_OK;
}


UINT32 check_SetAffinity_parm(PROC_ID pid, INT8 cpuset_msk) {
    return API_RTN_OK;
}

UINT32 set_proc_affinity(PROC_ID pid, INT8 cpuset_msk) {
    Task_Struct* pTask_Struct_temp = __select_task_struct(pid);
    pTask_Struct_temp->cpuset_msk = cpuset_msk;
    return API_RTN_OK;
}

bool is_runqueue_over() {
    bool ret = true;
    Task_Struct* pTask_Struct_temp = pProc_Manager->pRunQueue;
    if(pTask_Struct_temp == NULL) {
        ret = true;
    } else {
        while(pTask_Struct_temp != NULL) {
            if(pTask_Struct_temp->state != STOPPED) {
                ret = false;
                break;
            }
            pTask_Struct_temp = pTask_Struct_temp->Next;
        }
    }
    return ret;
}

bool is_time_window() {
    if(pProc_Manager->curr_timestamp % VRUNTIME_WINDOW == 0) {
        return true;
    } else {
        return false;
    }
}

void clear_proc_belong_cpu() {
    Task_Struct* pTask_Struct_temp = pProc_Manager->pRunQueue;
    if(pTask_Struct_temp == NULL) {
        return;
    } else {
        while(pTask_Struct_temp != NULL) {
            pTask_Struct_temp->belong_core_id = 0xFFFFFFFF;
            pTask_Struct_temp = pTask_Struct_temp->Next;
        }
    }
}

void refresh_all_core() {
    Core* pCore_temp = pProc_Manager->pCore;
    if(pCore_temp == NULL) {
        return;
    } else {
        while(pCore_temp != NULL) {
            pCore_temp->curr = NULL;
            pCore_temp->curr_prio = 0xFFFFFFFF;
            pCore_temp = pCore_temp->Next;
        }
    }
}

void refresh_all_proc() {
    Task_Struct* pTask_Struct_temp = pProc_Manager->pRunQueue;
    if(pTask_Struct_temp == NULL) {
        return;
    } else {
        while(pTask_Struct_temp != NULL) {
            __effective_prio(pTask_Struct_temp);
            pTask_Struct_temp = pTask_Struct_temp->Next;
        }
    }
}

void sort_for_all_proc() {
    Task_Struct* pTask_Struct_start = pProc_Manager->pRunQueue;
    if(pTask_Struct_start == NULL) {
        return;
    } else {
        Task_Struct* pTask_Struct_end = pTask_Struct_start->Next;
        while(pTask_Struct_start->Next != NULL) {
            while(pTask_Struct_end != NULL) {
                if(pTask_Struct_start->real_priority > pTask_Struct_end->real_priority) {
                    __switch_task_struct(pTask_Struct_start, pTask_Struct_end);
                }
                pTask_Struct_end = pTask_Struct_end->Next;
            }
            pTask_Struct_start = pTask_Struct_start->Next;
            pTask_Struct_end = pTask_Struct_start->Next;
        }
    }

    //Test
    Task_Struct* pTask_Struct_temp = pProc_Manager->pRunQueue;
    if(pTask_Struct_temp == NULL) {
        return;
    } else {
        printf("after sort_for_all_proc\n");
        while(pTask_Struct_temp != NULL) {
            printf("pid: %d, real_priority: %d\n", pTask_Struct_temp->pid, pTask_Struct_temp->real_priority);
            pTask_Struct_temp = pTask_Struct_temp->Next;
        }
    }
}

void sort_for_all_core() {
    Core* pCore_start = pProc_Manager->pCore;
    if(pCore_start == NULL) {
        return;
    } else {
        Core* pCore_end = pCore_start->Next;
        while(pCore_start->Next != NULL) {
            while(pCore_end != NULL) {
                if(pCore_start->curr_prio < pCore_end->curr_prio) {
                    __switch_core(pCore_start, pCore_end);
                }
                pCore_end = pCore_end->Next;
            }
            pCore_start = pCore_start->Next;
            pCore_end = pCore_start->Next;
        }
    }

    //Test
    Core* pCore_temp = pProc_Manager->pCore;
    if(pCore_temp == NULL) {
        return;
    } else {
        printf("after sort_for_all_proc\n");
        while(pCore_temp != NULL) {
            printf("core_id: %d, curr_prio: %d\n", pCore_temp->core_id, pCore_temp->curr_prio);
            pCore_temp = pCore_temp->Next;
        }
    }
}

void update_prio_all_core() {
    Core* pCore_temp = pProc_Manager->pCore;
    if(pCore_temp == NULL) {
        return;
    } else {
        while(pCore_temp != NULL) {
            __update_prio_per_core(pCore_temp);
            pCore_temp = pCore_temp->Next;
        }
    }

}

void __update_prio_per_core(Core* pCore_temp) {
    Task_Struct* pTask_Struct_temp = pProc_Manager->pRunQueue;
    if(pTask_Struct_temp == NULL) {
        return;
    } else {
        while(pTask_Struct_temp != NULL) {
            if(pTask_Struct_temp->belong_core_id == pCore_temp->core_id) {
                if(pCore_temp->curr_prio > pTask_Struct_temp->real_priority) {
                    pCore_temp->curr_prio = pTask_Struct_temp->real_priority;
                }
            }
            pTask_Struct_temp = pTask_Struct_temp->Next;
        }
    }
}

UINT32 try_to_clear_core_list() {
    Core* pTemp = __pop_core_list();
    while(pTemp != NULL) {
        __try_to_clear_core(pTemp);
        pTemp = __pop_core_list();
    }
    return API_RTN_OK;
}

UINT32 try_to_clear_runqueue() {
    Task_Struct* pTask_Struct_temp = __pop_runqueue();
    while(pTask_Struct_temp != NULL) {
        free(pTask_Struct_temp);
        pTask_Struct_temp = __pop_runqueue();
    }

    return API_RTN_OK;
}

UINT32 __effective_prio(Task_Struct* pTask_Struct) {
    if(pTask_Struct->exec_used == pTask_Struct->exec_length) {
        //进程已经运行完了
        pTask_Struct->real_priority = 0xFFFFFFFF;
        pTask_Struct->state = STOPPED;
    } else if (pTask_Struct->exec_start < pProc_Manager->curr_timestamp){
        //进程还没有准备好
        pTask_Struct->real_priority = 0xFFFFFFFF;
        pTask_Struct->state = PREPARE;
    } else {
        if(pTask_Struct->type == SCHED_FIFO) {
            pTask_Struct->real_priority = pTask_Struct->priority;
        } else {
            pTask_Struct->real_priority = NORMAL_TASK_PRIO_OFFSET + (pTask_Struct->exec_used * 400) / pTask_Struct->weight;
        }
        pTask_Struct->state = RUNNING;
    }

    printf("task: %d, real_priority: %u\n", pTask_Struct->pid, pTask_Struct->real_priority);

    return API_RTN_OK;
}

Task_Struct* __select_task_struct(PROC_ID pid) {
    Task_Struct* pTask_Struct_temp = pProc_Manager->pRunQueue;
    while(pTask_Struct_temp != NULL) {
        if(pTask_Struct_temp->pid == pid)
            return pTask_Struct_temp;
        pTask_Struct_temp = pTask_Struct_temp->Next;
    }
    return NULL;
}

void __try_to_clear_core(Core* pCore_Temp) {
    History* pHistory_Temp = __pop_history_list(pCore_Temp);
    while(pHistory_Temp != NULL) {
        free(pHistory_Temp);
        pHistory_Temp = __pop_history_list(pCore_Temp);
    }
    free(pCore_Temp);
}

Core* __pop_core_list() {
    Core* pCore_Temp = NULL;
    if(pProc_Manager->pCore == NULL) {
        return pCore_Temp;
    } else {
        pCore_Temp = pProc_Manager->pCore;
        pProc_Manager->pCore = pCore_Temp->Next;
    }
    return pCore_Temp;
}

History* __pop_history_list(Core* pCore_Temp) {
    History* pHistory_Temp = NULL;
    if(pCore_Temp->pHistory == NULL) {
        return pHistory_Temp;
    } else {
        pHistory_Temp = pCore_Temp->pHistory;
        pCore_Temp->pHistory = pHistory_Temp->Next;
    }
    return pHistory_Temp;
}

Task_Struct* __pop_runqueue() {
    Task_Struct* pTask_Struct_temp = NULL;
    if(pProc_Manager->pRunQueue == NULL) {
        return pTask_Struct_temp;
    } else {
        pTask_Struct_temp = pProc_Manager->pRunQueue;
        pProc_Manager->pRunQueue = pTask_Struct_temp->Next;
    }
    return pTask_Struct_temp;
}

void show_history() {
    Core* pCore = pProc_Manager->pCore;
    while(pCore != NULL) {
        __show_history_per_core(pCore);
        pCore = pCore->Next;
    }
}


void __show_history_per_core(Core* pCore) {
    History* pHistory_Temp = pCore->pHistory;
    printf("Core_id: %d\t", pCore->core_id);
    while(pHistory_Temp != NULL) {
        printf("%d\t", pHistory_Temp->pid);
        pHistory_Temp = pHistory_Temp->Next;
    }
    printf("\n");
}


void __switch_task_struct(Task_Struct* pTask_Struct_start, Task_Struct* pTask_Struct_end) {
    if(pTask_Struct_start->Pre != NULL) {
        pTask_Struct_start->Pre->Next = pTask_Struct_end;
    }
    if(pTask_Struct_start->Next != pTask_Struct_end) {
        pTask_Struct_start->Next->Pre = pTask_Struct_end;
    }
    if(pTask_Struct_end->Next != NULL) {
        pTask_Struct_end->Next->Pre = pTask_Struct_start;
    }
    if(pTask_Struct_end->Pre != pTask_Struct_start) {
        pTask_Struct_end->Pre->Next = pTask_Struct_start;
    }

    Task_Struct* pTask_Struct_temp = NULL;
    if(pTask_Struct_start->Next != pTask_Struct_end) {
        pTask_Struct_temp = pTask_Struct_start->Pre;
        pTask_Struct_start->Pre = pTask_Struct_end->Pre;
        pTask_Struct_end->Pre = pTask_Struct_temp;

        pTask_Struct_temp = pTask_Struct_start->Next;
        pTask_Struct_start->Next = pTask_Struct_end->Next;
        pTask_Struct_end->Next = pTask_Struct_temp;
    } else {
        pTask_Struct_temp = pTask_Struct_start->Pre;
        pTask_Struct_start->Pre = pTask_Struct_end;
        pTask_Struct_end->Pre = pTask_Struct_temp;

        pTask_Struct_temp = pTask_Struct_end->Next;
        pTask_Struct_end->Next = pTask_Struct_start;
        pTask_Struct_start->Next = pTask_Struct_temp;
    }
}

void __switch_core(Core* pCore_start, Core* pCore_end) {
    Fix bug
    Core* pCore_temp = pCore_start->Pre;
    pCore_start->Pre = pCore_end->Pre;
    pCore_temp->Pre = pCore_temp;

    pCore_temp = pCore_start->Next;
    pCore_start->Next = pCore_end->Next;
    pCore_end->Next = pCore_temp;
}
