#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "api.h"

typedef struct physical_block {
    UINT64 base_addr;
    UINT64 block_id;
    UINT64 block_status; // 0 means free, 1 means be allocated
    struct physical_block* next;
} PHYSICAL_BLOCK_T;

typedef struct physical_manager {
    UINT64 block_base_addr;
    UINT64 total_block_num;
    UINT64 free_block_num;
    UINT64 used_block_num;
    PHYSICAL_BLOCK_T* pBlock_Used;
    PHYSICAL_BLOCK_T* pBlock_Free;
} PHYSICAL_MANAGER_T;

typedef struct buffer {
    UINT64 buffer_id;
    struct buffer *next;
} BUFFER_T;

typedef struct logical_block {
    UINT64 block_id;
    UINT64 block_base_addr;
    BUFFER_T *pBuffer_Used;
    BUFFER_T *pBuffer_Free;
    BUFFER_T *pBuffer_Locked;
    struct logical_block* next;
} LOGICAL_BLOCK_T;

typedef struct logical_manager {
    UINT64 logical_pool_id;
    UINT64 buffer_size;
    UINT64 free_buffer_num;
    UINT64 used_buffer_num;
    UINT64 used_block_num;
    UINT64 LowLine;
    UINT64 HighLine;
    UINT64 MaxBufferAllow;
    LOGICAL_BLOCK_T* pLogical_Block;
    struct logical_manager* next;
    PHYSICAL_MANAGER_T* pPhysical_manager;
} LOGICAL_MANAGER_T;

typedef struct memory_manager {
    PHYSICAL_MANAGER_T* pPhysical_manager;
    LOGICAL_MANAGER_T* pLogical_manager;
} MEMORY_MANAGER_T;

UINT64 check_BMU_PhyPoolInit_parm(UINT64 uwPhyPoolIndex);

UINT64 calculate_PhyPoolInit_block_num(UINT64 uwMemAddr, UINT64 uwMemSize, UINT64* pTotal_block_num, UINT64* pBlock_base_addr);

UINT64 check_PhyPool_after_init(MEMORY_MANAGER_T* pMemory_Manager);
#endif /* __MANAGER_H__ */
