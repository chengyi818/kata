#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "api.h"

typedef struct memory_manager {
    UINT64* puwPhyPoolHandle;




} MEMORY_MANAGER_T;

typedef struct physical_block {
    UINT64 block_id;
    UINT64 block_status; // 0 means free, 1 means be allocated
    struct physical_block* next;
} PHYSICAL_BLOCK_T;

typedef struct physical_manager {
    UINT64 total_block_num;
    UINT64 free_block_num;
    UINT64 used_block_num;
    PHYSICAL_BLOCK_T* pPHYSICAL_BLOCK_HEAD;
} PHYSICAL_MANAGER_T;


#endif /* __MANAGER_H__ */
