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
#include "test.h"

Proc_Manager *pProc_Manager;

int main(void) {
    pProc_Manager = (Proc_Manager*)malloc(sizeof(Proc_Manager));
    pProc_Manager->core_num = 0;
    pProc_Manager->proc_num = 0;
    pProc_Manager->curr_timestamp = 0;
    pProc_Manager->pRunQueue = NULL;
    pProc_Manager->pCore = NULL;

    test_demo_0();

    return 0;
}

