#include <stdio.h>
#include <stdlib.h>
#include "api.h"
#include "process_manager.h"

extern Proc_Manager *pProc_Manager;

INT32 EnableCore(UINT32 core_id) {
    if(check_Enable_Core_parm(core_id)) {
        printf("check_Enable_Core_parm fail\n");
        return API_RTN_ERROR;
    }

    Core* pCore_temp = create_core(core_id);

    if(insert_core(pCore_temp)) {
        printf("insert_core fail\n");
        return API_RTN_ERROR;
    }

    return API_RTN_OK;
}


INT32 AddProc(PROC_ID pid, ProcInfo proc_info) {
    if(check_AddProc_parm(pid, proc_info)) {
        printf("check_AddProc_parm fail\n");
        return API_RTN_ERROR;
    }

    Task_Struct * pTask_Struct_temp = create_task_struct(pid, proc_info);

    if(insert_proc(pTask_Struct_temp)) {
        printf("insert_proc fail\n");
        return API_RTN_ERROR;
    }

    return API_RTN_OK;
}


INT32 SetAffinity(PROC_ID pid, INT8 cpuset_msk) {
    if(check_SetAffinity_parm(pid, cpuset_msk)) {
        printf("check SetAffinity parm fail\n");
        return API_RTN_ERROR;
    }
    set_proc_affinity(pid, cpuset_msk);

    return API_RTN_OK;
}

void SimuSchedule(void) {
    printf("begin SimuSchedule");
    while(1) {
        //检查整个runqueue是否还有进程需要运行
        if(is_runqueue_over()) {
            printf("all proc run over\n");
            break;
        }

        //检查当前是否是时间窗口
        if(is_time_window()) {
            clear_proc_belong_cpu();
        }

        //更新所有进程的实时优先级和状态
        refresh_all_proc();

        //为所有进程排序,优先级数值小的靠前
        sort_for_all_proc();
        __show_runqueue();

        //恢复所有core的curr
        refresh_all_core();

        //更新所有core的当前优先级
        update_prio_all_core();

        //为所有core排序,优先级数值大的靠前
        sort_for_all_core();
        __show_core_list();

        while(is_core_free() && is_proc_need_dispatch()) {
            //从优先级数值最低的一个进程选择核
            Task_Struct* pTask_Struct_temp = select_first_no_dispatch_proc();
            //考虑过的进程,将be_dispatch置位
            dispatch_proc(pTask_Struct_temp);
        }

        __show_dispatch_result();
        //process_manager的curr_timestamp向前推进一个
        scheduler_tick();
    }
    show_history();
}

void Clear(void) {
    if(try_to_clear_core_list()) {
        printf("clear core list fail\n");
    }
    if(try_to_clear_runqueue()) {
        printf("clear runqueue fail\n");
    }
    pProc_Manager->core_num = 0;
    pProc_Manager->proc_num = 0;
    pProc_Manager->curr_timestamp = 0;
}
