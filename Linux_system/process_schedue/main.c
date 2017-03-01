/*=============================================================================
#     FileName: main.c
#         Desc:
#       Author: ChengYi
#        Email: chengyi818@foxmail.com
#     HomePage:
#      Created: 2017-03-01 14:19:12
#      Version: 0.0.1
#   LastChange: 2017-03-01 14:19:12
#      History:
#               0.0.1 | ChengYi | init
=============================================================================*/
#include <stdlib.h>

#include "api.h"
#include "process_manager.h"

Proc_Manager *pProc_Manager;

int main(void) {
    pProc_Manager = (Proc_Manager*)malloc(sizeof(Proc_Manager));
    pProc_Manager->core_num = 0;
    pProc_Manager->proc_num = 0;
    pProc_Manager->curr_timestamp = 0;
    pProc_Manager->pRunQueue = NULL;
    pProc_Manager->pCore = NULL;

    EnableCore(0);
    EnableCore(1);
    EnableCore(3);

    ProcInfo proc0;
    proc0.type = SCHED_FIFO;
    proc0.exec_start = 0;
    proc0.exec_length = 5;
    proc0.priority = 13;

    ProcInfo proc1;
    proc1.type = SCHED_NORMAL;
    proc1.exec_start = 3;
    proc1.exec_length = 5;
    proc1.weight = WEIGHT_MID;

    AddProc(0, proc0);
    AddProc(3, proc1);
    AddProc(4, proc0);
    AddProc(5, proc1);

    SetAffinity(0, 0x1);

    SimuSchedule();

    Clear();

    return 0;
}
