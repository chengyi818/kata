/*=============================================================================
#     FileName: api.h
#         Desc:
#       Author: ChengYi
#        Email: chengyi818@foxmail.com
#     HomePage:
#      Created: 2017-03-01 13:40:14
#      Version: 0.0.1
#   LastChange: 2017-03-01 13:40:14
#      History:
#               0.0.1 | ChengYi | init
=============================================================================*/

#ifndef __API_H__
#define __API_H__

#include <stdint.h>
#include "basic.h"

INT32 EnableCore(UINT32 core_id);

INT32 AddProc(PROC_ID pid, ProcInfo proc_info);

INT32 SetAffinity(PROC_ID pid, INT8 cpuset_msk);

void SimuSchedule(void);

INT32 QueryCpuStat(UINT32 core_id, UINT32 begin_tick, UINT32 length, PROC_ID array[]);

void Clear(void);

#endif /* __API_H__ */
