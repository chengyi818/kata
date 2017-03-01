#ifndef __BASIC_H__
#define __BASIC_H__

#define API_RTN_OK 0
#define API_RTN_ERROR 1

#define LIMIT_OF_CORES 8 //合法core id: 0~7
#define LIMIT_OF_PROCESS 128 //合法pid: 0~127

#define LIMIT_OF_FIFO_PRIO 16 //合法的FIFO优先级: 0~15

#define VRUNTIME_WINDOW 10 //每10个tick组成一个时间窗

#ifndef INT8
typedef char INT8;
#endif

#ifndef UINT8
typedef unsigned char UINT8;
#endif

#ifndef INT16
typedef short INT16;
#endif

#ifndef UINT16
typedef unsigned short UINT16;
#endif

#ifndef INT32
typedef int INT32;
#endif

#ifndef UINT32
typedef unsigned int UINT32;
#endif

#ifndef INT64
typedef long long INT64;
#endif

#ifndef UINT64
typedef unsigned long long UINT64;
#endif

typedef INT8 PROC_ID; // -1表示错误,0~127合法

/*进程调度策略*/
typedef enum {
    SCHED_NORMAL,
    SCHED_FIFO,
    SCHED_BUTT
}SCHED_TYPE;

/*NORMAL进程的调度权重*/
typedef enum {
    WEIGHT_LOW = 1,
    WEIGHT_MID = 2,
    WEIGHT_HIGH = 4,
    WEIGHT_NONE
}WEIGHT_VAL;

typedef struct ProcInfo_Tag {
    SCHED_TYPE type; //进程调度策略
    UINT32 exec_start; //进入ready的时刻
    UINT32 exec_length; //运行的时间长度,单位tick.完成后返回stopped态
    WEIGHT_VAL weight; //Normal进程取值: 4/2/1
    UINT32 priority; //FIFO进程取值: 0~15
} ProcInfo;

#endif /* __BASIC_H__ */
