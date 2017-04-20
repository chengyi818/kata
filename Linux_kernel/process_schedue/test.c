#include <stdio.h>
#include <string.h>
#include "basic.h"
#include "api.h"

void test_demo_0() {
    UINT32 cid = 0;
    PROC_ID pid;
    INT32 ret;
    ProcInfo aPIF[] = {
        //type, exex_start, exec_length, weight, priority
        {SCHED_FIFO,    2,  1,  WEIGHT_NONE,    0},
        {SCHED_NORMAL,  0,  4,  WEIGHT_MID,     0},
        {SCHED_NORMAL,  2,  2,  WEIGHT_HIGH,    0},
        {SCHED_NORMAL,  8,  2,  WEIGHT_LOW,     0},
    };

    PROC_ID result[11];
    PROC_ID expect[10] = {0, 2, 2, 1, 1, -1, 3, 3, -1, -1};
    printf("开始执行用例\n");

    ret = EnableCore(cid);
    if(API_RTN_OK != ret) {
        printf("EnableCore Test Fail, core_id:%u\n", cid);
    }

    //添加pid信息
    for(pid = 0; pid < (INT8)(sizeof(aPIF)/sizeof(aPIF[0])); pid++) {
        ret = AddProc(pid, aPIF[(UINT32)pid]);
        if(API_RTN_OK != ret) {
            printf("AddProc Test fail, pid %u\n", pid);
        }
    }

    //pid重复添加测试
    ret = AddProc(0, aPIF[0]);
    if(API_RTN_OK == ret) {
        printf("AddProc dumplicate Test fail, pid %u\n", pid);
    }

    SimuSchedule();

    memset(result, -2, sizeof(result));
    ret = QueryCpuStat(cid, 2, 10, result);
    if(ret != API_RTN_OK) {
        printf("QueryCpuStat Test fail, return error\n");
    }
    if(0 != memcmp(expect, result, 10)) {
        printf("QueryCpuStat Test fail, output error\n");
    }
    if(result[10] != -2) {
        printf("QueryCpuStat Test fail, memory overflow\n");
    }

    Clear();
}

void exam1() {
    //Exam 1 Pass
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

    EnableCore(0);
    AddProc(0, procA);
    SimuSchedule();

    Clear();
}

void exam2() {
    //Exam 2 pass
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

    EnableCore(0);
    AddProc(2, procB);
    SetAffinity(2, 0x1);
    SimuSchedule();
    Clear();
}


void exam3() {
    //Exam 3 pass
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

    EnableCore(0);
    EnableCore(1);
    AddProc(0, procA);
    AddProc(1, procB);
    SimuSchedule();
    Clear();
}


void exam4() {
    //Exam 4 pass
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
}

void exam5() {
    ProcInfo procA;
    procA.type = SCHED_FIFO;
    procA.exec_start = 0;
    procA.exec_length = 5;
    procA.priority = 1;

    ProcInfo procB;
    procB.type = SCHED_FIFO;
    procB.exec_start = 0;
    procB.exec_length = 5;
    procB.priority = 3;

    EnableCore(0);
    EnableCore(1);

    AddProc(0, procA);
    AddProc(1, procB);

    SetAffinity(0, 0x3);
    SetAffinity(1, 0x1);

    SimuSchedule();

    Clear();
}

void exam6() {
    ProcInfo procA;
    procA.type = SCHED_FIFO;
    procA.exec_start = 0;
    procA.exec_length = 5;
    procA.priority = 1;

    ProcInfo procB;
    procB.type = SCHED_FIFO;
    procB.exec_start = 0;
    procB.exec_length = 5;
    procB.priority = 2;

    ProcInfo procC;
    procC.type = SCHED_FIFO;
    procC.exec_start = 0;
    procC.exec_length = 5;
    procC.priority = 3;

    EnableCore(0);
    EnableCore(1);
    EnableCore(2);

    AddProc(0, procA);
    AddProc(1, procB);
    AddProc(2, procC);

    SetAffinity(0, 0x7);
    SetAffinity(1, 0x3);
    SetAffinity(2, 0x1);

    SimuSchedule();

    Clear();
}
