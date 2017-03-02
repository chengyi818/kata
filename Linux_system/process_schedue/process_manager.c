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
    if(core_id > LIMIT_OF_CORES) {
        printf("input core_id: %u out of range\n", core_id);
        return API_RTN_ERROR;
    }
    Core* pCore_temp = __select_core_by_id(core_id);
    if(pCore_temp) {
        printf("input core_id: %u dumplicate\n", core_id);
        return API_RTN_ERROR;
    }

    return API_RTN_OK;
}

Core* create_core(UINT32 core_id) {
    printf("create core_id: %d\n", core_id);
    Core* pCore_temp = (Core*)malloc(sizeof(Core));

    pCore_temp->core_id = core_id;
    pCore_temp->pHistory = NULL;
    pCore_temp->curr_rq_prio = 0xFFFFFFFF;
    pCore_temp->curr = NULL;
    pCore_temp->Next = NULL;

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
    }

    pProc_Manager->core_num += 1;
    return API_RTN_OK;
}


UINT32 check_AddProc_parm(PROC_ID pid, ProcInfo proc_info) {
    if(pid < 0) {
        printf("input pid: %d out of range\n", pid);
        return API_RTN_ERROR;
    }
    Task_Struct* pTask_Struct_temp = __select_task_struct(pid);
    if(pTask_Struct_temp) {
        printf("input pid: %d dumplicate\n", pid);
        return API_RTN_ERROR;
    }
    if(!__check_proc_info_parm(proc_info)) {
        printf("check proc_info parm fail\n");
        return API_RTN_ERROR;
    }

    return API_RTN_OK;
}

UINT32 __check_proc_info_parm(ProcInfo proc_info) {
    /*
     *if(pr)
     */
    return 1;
}

Task_Struct* create_task_struct(PROC_ID pid, ProcInfo proc_info) {
    printf("create Task_Struct id: %d\n", pid);
    Task_Struct* pTask_Struct_temp = (Task_Struct*)malloc(sizeof(Task_Struct));
    pTask_Struct_temp->pid = pid;
    pTask_Struct_temp->state = PREPARE;
    pTask_Struct_temp->type = proc_info.type;
    pTask_Struct_temp->affinity = 0xFFFFFFFF;
    pTask_Struct_temp->belong_core_id = 0xFFFFFFFF;
    pTask_Struct_temp->be_dispatched = 0;

    pTask_Struct_temp->exec_start = proc_info.exec_start;
    pTask_Struct_temp->exec_length = proc_info.exec_length;
    pTask_Struct_temp->exec_used = 0;
    pTask_Struct_temp->exex_used_per_window = 0;

    if(proc_info.type == SCHED_NORMAL) {
        pTask_Struct_temp->weight = proc_info.weight;
        pTask_Struct_temp->priority = 0xFFFFFFFF;
    } else {
        pTask_Struct_temp->weight = WEIGHT_NONE;
        pTask_Struct_temp->priority = proc_info.priority;
    }
    __effective_prio(pTask_Struct_temp);

    pTask_Struct_temp->Next = NULL;

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
    }
    pProc_Manager->proc_num += 1;

    return API_RTN_OK;
}


UINT32 check_SetAffinity_parm(PROC_ID pid, UINT32 affinity) {
    return API_RTN_OK;
}

UINT32 set_proc_affinity(PROC_ID pid, UINT32 affinity) {
    Task_Struct* pTask_Struct_temp = __select_task_struct(pid);
    pTask_Struct_temp->affinity = (UINT32)affinity;
    return API_RTN_OK;
}

UINT32 is_runqueue_over() {
    UINT32 ret = 1;
    Task_Struct* pTask_Struct_temp = pProc_Manager->pRunQueue;
    if(pTask_Struct_temp == NULL) {
        ret = 1;
    } else {
        while(pTask_Struct_temp != NULL) {
            if(pTask_Struct_temp->state != STOPPED) {
                ret = 0;
                break;
            }
            pTask_Struct_temp = pTask_Struct_temp->Next;
        }
    }
    return ret;
}

UINT32 is_time_window() {
    if(pProc_Manager->curr_timestamp % VRUNTIME_WINDOW == 0) {
        return 1;
    } else {
        return 0;
    }
}

void clear_proc_belong_cpu() {
    Task_Struct* pTask_Struct_temp = pProc_Manager->pRunQueue;
    if(pTask_Struct_temp == NULL) {
        return;
    } else {
        while(pTask_Struct_temp != NULL) {
            pTask_Struct_temp->belong_core_id = 0xFFFFFFFF;
            pTask_Struct_temp->exex_used_per_window = 0;
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
            pCore_temp->curr_rq_prio = 0xFFFFFFFF;
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
            pTask_Struct_temp->be_dispatched = 0;
            __effective_prio(pTask_Struct_temp);
            pTask_Struct_temp = pTask_Struct_temp->Next;
        }
    }
}

void sort_for_all_proc() {
    pProc_Manager->pRunQueue = listMergeSort_Proc(pProc_Manager->pRunQueue);
}

void sort_for_all_core() {
    pProc_Manager->pCore = listMergeSort_Core(pProc_Manager->pCore);
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
    pCore_temp->curr_rq_prio = 0xFFFFFFFF;
    Task_Struct* pTask_Struct_temp = pProc_Manager->pRunQueue;
    if(pTask_Struct_temp == NULL) {
        return;
    } else {
        while(pTask_Struct_temp != NULL) {
            if(pTask_Struct_temp->belong_core_id == pCore_temp->core_id &&
                    pTask_Struct_temp->state == RUNNING) {
                if(pCore_temp->curr_rq_prio > pTask_Struct_temp->real_priority) {
                    pCore_temp->curr_rq_prio = pTask_Struct_temp->real_priority;
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
    } else if (pTask_Struct->exec_start > pProc_Manager->curr_timestamp){
        //进程还没有准备好
        pTask_Struct->real_priority = 0xFFFFFFFF;
        pTask_Struct->state = PREPARE;
    } else {
        if(pTask_Struct->type == SCHED_FIFO) {
            pTask_Struct->real_priority = pTask_Struct->priority;
        } else {
            pTask_Struct->real_priority = NORMAL_TASK_PRIO_OFFSET + (pTask_Struct->exex_used_per_window * 400) / pTask_Struct->weight;
        }
        pTask_Struct->state = RUNNING;
    }

    /*printf("task: %d, real_priority: %u\n", pTask_Struct->pid, pTask_Struct->real_priority);*/

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

Core* __select_core_by_id(UINT32 core_id) {
    Core* pCore_Temp = pProc_Manager->pCore;
    if( pCore_Temp == NULL) {
        return pCore_Temp;
    } else {
        while(pCore_Temp != NULL) {
            if(pCore_Temp->core_id == core_id)
                return pCore_Temp;
            pCore_Temp = pCore_Temp->Next;
        }
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
    Core* pCore_Temp = pProc_Manager->pCore;
    if(pCore_Temp == NULL) {
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
    printf("show_history\n");
    while(pCore != NULL) {
        __show_history_per_core(pCore);
        pCore = pCore->Next;
    }
}

void __show_history_per_core(Core* pCore) {
    History* pHistory_Temp = pCore->pHistory;
    printf("Core_id: %d\n", pCore->core_id);
    while(pHistory_Temp != NULL) {
        printf("%d\t", pHistory_Temp->pid);
        pHistory_Temp = pHistory_Temp->Next;
    }
    printf("\n");
}

UINT32 is_core_free() {
    UINT32 ret = 0;
    Core* pCore_temp = pProc_Manager->pCore;
    while(pCore_temp != NULL) {
        if(pCore_temp->curr == NULL) {
            ret = 1;
            break;
        }
        pCore_temp = pCore_temp->Next;
    }

    return ret;
}

UINT32 is_proc_need_dispatch() {
    UINT32 ret = 0;
    Task_Struct* pTask_Struct_temp = pProc_Manager->pRunQueue;
    while(pTask_Struct_temp != NULL) {
        if(pTask_Struct_temp->state == RUNNING && !pTask_Struct_temp->be_dispatched) {
            ret = 1;
            break;
        }
        pTask_Struct_temp = pTask_Struct_temp->Next;
    }
    return ret;
}

Task_Struct* select_first_no_dispatch_proc() {
    Task_Struct* pTask_Struct_temp = pProc_Manager->pRunQueue;
    while(pTask_Struct_temp != NULL) {
        if(pTask_Struct_temp->state == RUNNING && !pTask_Struct_temp->be_dispatched) {
            break;
        }
        pTask_Struct_temp = pTask_Struct_temp->Next;
    }
    if(pTask_Struct_temp != NULL) {
        printf("try to dispatch_proc: %d\n", pTask_Struct_temp->pid);
    }
    return pTask_Struct_temp;
}

void dispatch_proc(Task_Struct* pTask_Struct_temp) {
    pTask_Struct_temp->be_dispatched = 1;
    UINT32 belong_core_id = pTask_Struct_temp->belong_core_id;

    if(belong_core_id != 0xFFFFFFFF) {
        Core* pCore_temp = __select_core_by_id(belong_core_id);
        if(pCore_temp->curr == NULL) {
            pCore_temp->curr = pTask_Struct_temp;
            return;
        } else {
            return;
        }
    } else {
        Core* pCore_temp = pProc_Manager->pCore;
        while(pCore_temp != NULL) {
            if(pCore_temp->curr == NULL && __is_allowed_by_affinity(pCore_temp, pTask_Struct_temp)) {
                pCore_temp->curr = pTask_Struct_temp;
                break;
            }
            pCore_temp = pCore_temp->Next;
        }
        return;
    }
}

UINT32 __is_allowed_by_affinity(Core* pCore_temp, Task_Struct* pTask_Struct_temp) {
    UINT32 core_id = pCore_temp->core_id;
    UINT32 affinity = pTask_Struct_temp->affinity;
    if( (1<<core_id) & affinity)
        return 1;
    else
        return 0;
}

void scheduler_tick(){
    pProc_Manager->curr_timestamp += 1;
    //更新所有core的历史记录
    update_all_core_timestamp();
}

void update_all_core_timestamp() {
    //更新所有被运行的进程的所有时间片信息和所属cpu,清除be_dispatch标志位
    Core* pCore = pProc_Manager->pCore;
    while(pCore != NULL) {
        __add_history_for_curr(pCore);
        __update_timestamp_for_curr_proc(pCore);
        pCore = pCore->Next;
    }
}

void __add_history_for_curr(Core* pCore) {
    History* pHistory_Temp = (History*)malloc(sizeof(History));
    pHistory_Temp->Next = NULL;

    if(pCore->curr) {
        pHistory_Temp->pid = pCore->curr->pid;
    } else {
        pHistory_Temp->pid = -1;
    }

    if(pCore->pHistory == NULL) {
        pCore->pHistory = pHistory_Temp;
    } else {
        History* pTemp = pCore->pHistory;
        while(pTemp->Next != NULL)
            pTemp = pTemp->Next;

        pTemp->Next = pHistory_Temp;
    }
}

void __update_timestamp_for_curr_proc(Core* pCore) {
    if(pCore->curr) {
        pCore->curr->exec_used += 1;
        pCore->curr->exex_used_per_window += 1;
        pCore->curr->belong_core_id = pCore->core_id;
    }
}

void __show_runqueue() {
    Task_Struct* pTask_Struct_temp = pProc_Manager->pRunQueue;
    if(pTask_Struct_temp == NULL) {
        return;
    } else {
        printf("\n");
        while(pTask_Struct_temp != NULL) {
            printf("pid: %d, real_priority: 0x%x\n", pTask_Struct_temp->pid, pTask_Struct_temp->real_priority);
            pTask_Struct_temp = pTask_Struct_temp->Next;
        }
    }
}

void __show_core_list() {
    Core* pCore_temp = pProc_Manager->pCore;
    if(pCore_temp == NULL) {
        return;
    } else {
        printf("\n");
        while(pCore_temp != NULL) {
            printf("core_id: %d, curr_rq_prio: 0x%x\n", pCore_temp->core_id, pCore_temp->curr_rq_prio);
            pCore_temp = pCore_temp->Next;
        }
    }
}

Task_Struct *mergeSortedList_Proc(Task_Struct *L1, Task_Struct *L2) {
    Task_Struct dummy;
    Task_Struct *p1 = &dummy;
    Task_Struct *p2 = L2;
    dummy.Next = L1;
    while(p1->Next != NULL && p2 != NULL) {
        if(p1->Next->real_priority > p2->real_priority) {
            L2 = p2->Next;
            p2->Next = p1->Next;
            p1->Next = p2;
            p1 = p2;
            p2 = L2;
        } else {
            p1 = p1->Next;
        }
    }
    if(p1->Next == NULL) {
        p1->Next = p2;
    }

    return dummy.Next;
}

Task_Struct *listMergeSort_Proc(Task_Struct* head) {
    if(head == NULL || head->Next == NULL) {
        return head;
    }
    Task_Struct* slow = head;
    Task_Struct* fast = head;
    while(fast->Next != NULL && fast->Next->Next != NULL) {
        fast = fast->Next->Next;
        slow = slow->Next;
    }

    Task_Struct *leftHead = head;
    Task_Struct *rightHead = slow->Next;
    slow->Next = NULL;

    leftHead = listMergeSort_Proc(leftHead);
    rightHead = listMergeSort_Proc(rightHead);

    return mergeSortedList_Proc(leftHead, rightHead);
}


Core *mergeSortedList_Core(Core *L1, Core *L2) {
    Core dummy;
    Core *p1 = &dummy;
    Core *p2 = L2;
    dummy.Next = L1;
    while(p1->Next != NULL && p2 != NULL) {
        if(p1->Next->curr_rq_prio < p2->curr_rq_prio) {
            L2 = p2->Next;
            p2->Next = p1->Next;
            p1->Next = p2;
            p1 = p2;
            p2 = L2;
        } else {
            p1 = p1->Next;
        }
    }
    if(p1->Next == NULL) {
        p1->Next = p2;
    }

    return dummy.Next;
}

Core *listMergeSort_Core(Core* head) {
    if(head == NULL || head->Next == NULL) {
        return head;
    }
    Core* slow = head;
    Core* fast = head;
    while(fast->Next != NULL && fast->Next->Next != NULL) {
        fast = fast->Next->Next;
        slow = slow->Next;
    }

    Core *leftHead = head;
    Core *rightHead = slow->Next;
    slow->Next = NULL;

    leftHead = listMergeSort_Core(leftHead);
    rightHead = listMergeSort_Core(rightHead);

    return mergeSortedList_Core(leftHead, rightHead);
}


void __show_dispatch_result() {
    printf("curr_timestamp: %d, dispatch_result: \n", pProc_Manager->curr_timestamp);
    Core* pCore_temp = pProc_Manager->pCore;
    if(pCore_temp == NULL) {
        return;
    } else {
        while(pCore_temp != NULL) {
            if(pCore_temp->curr)
                printf("core_id: %d\t, curr pid: %d\n", pCore_temp->core_id, pCore_temp->curr->pid);
            pCore_temp = pCore_temp->Next;
        }
    }
    printf("*****************************");
}

UINT32 check_QueryCpuStat_parm(UINT32 core_id) {
    return 1;
}
