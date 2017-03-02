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

    ProcInfo procA;
    procA.type = SCHED_FIFO;
    procA.exec_start = 0;
    procA.exec_length = 5;
    procA.priority = 13;

    ProcInfo procB;
    procB.type = SCHED_NORMAL;
    procB.exec_start = 3;
    procB.exec_length = 10;
    procB.weight = WEIGHT_MID;

    //Exam 1 Pass
    /*
     *EnableCore(0);
     *AddProc(0, procA);
     *SimuSchedule();
     *Clear();
     */

    //Exam 2 pass
    /*
     *EnableCore(0);
     *AddProc(2, procB);
     *SetAffinity(2, 0x1);
     *SimuSchedule();
     *Clear();
     */

    //Exam 3 pass
    /*
     *EnableCore(0);
     *EnableCore(1);
     *AddProc(0, procA);
     *AddProc(1, procB);
     *SimuSchedule();
     *Clear();
     */

    //Exam 4
    EnableCore(0);
    EnableCore(1);
    EnableCore(3);

    AddProc(0, procA);
    AddProc(3, procB);
    AddProc(4, procA);
    AddProc(5, procB);

    SetAffinity(3, 0x1);

    SimuSchedule();

    Clear();

    return 0;
}
