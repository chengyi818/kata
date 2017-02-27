#include <stdio.h>
#include <stdlib.h>

#include "manager.h"

#define PHYPOOLSIZE (1024*1024*10) // 10M
#define __TEST__

UINT64 BMU_PhyPoolInit(UINT64 uwPhyPoolIndex, UINT64 uwMemAddr, UINT64 uwMemSize, UINT64* puwPhyPoolHandle) {
    UINT64 i;
    UINT64 total_block_num;
    UINT64 block_base_addr;

    if(check_BMU_PhyPoolInit_parm(uwPhyPoolIndex)) {
        printf("check_BMU_PhyPoolInit_parm error\n");
        return 1;
    }

    calculate_PhyPoolInit_block_num(uwMemAddr, uwMemSize, &total_block_num, &block_base_addr);

    //malloc memory_manager
    MEMORY_MANAGER_T* pMemory_Manager = (MEMORY_MANAGER_T*)malloc(sizeof(MEMORY_MANAGER_T));
    pMemory_Manager->pLogical_manager = NULL;
    PHYSICAL_MANAGER_T* pPhysical_manager = (PHYSICAL_MANAGER_T*)malloc(sizeof(PHYSICAL_MANAGER_T));
    pMemory_Manager->pPhysical_manager = pPhysical_manager;
    pPhysical_manager->block_base_addr = block_base_addr;
    pPhysical_manager->total_block_num = total_block_num;
    pPhysical_manager->free_block_num = total_block_num;
    pPhysical_manager->used_block_num = 0;
    pPhysical_manager->pBlock_Used = NULL;
    pPhysical_manager->pBlock_Free = NULL;

    //alloc physical blocks
    for(i=0; i<total_block_num; i++) {
        PHYSICAL_BLOCK_T* pTemp_Block = (PHYSICAL_BLOCK_T*)malloc(sizeof(PHYSICAL_BLOCK_T));
        pTemp_Block->base_addr = block_base_addr + i*BLOCK_SIZE;
        pTemp_Block->block_id = i;
        pTemp_Block->block_status = 0;
        pTemp_Block->next = NULL;

        //link temp block to free linked list
        if(pPhysical_manager->pBlock_Free == NULL) {
            pPhysical_manager->pBlock_Free = pTemp_Block;
        } else {
            PHYSICAL_BLOCK_T* pTemp = pPhysical_manager->pBlock_Free;
            while( pTemp->next != NULL){
                pTemp = pTemp->next;
            }
            pTemp->next = pTemp_Block;
        }
    }

    *puwPhyPoolHandle = (UINT64)(pMemory_Manager);

    check_PhyPool_after_init(pMemory_Manager);

    return 0;
}

UINT64 BMU_LogicPoolCreate(UINT64 uwPhyPoolHandle, UINT64 uwBuffSize, UINT64 uwBuffNum, UINT64 *puwLogicPoolHandle, UINT64 LowLine, UINT64 HighLine) {
    UINT64 used_block_num;
    UINT64 buffer_num_per_block;

    printf("BMU_LogicPoolCreate called.\n");
    //check parm
    //1. 同一大小的逻辑池不允许建立多个
    //2. buffsize必须1k对齐,且小于BLOCK_SIZE
    //3. 0<=lowline<HighLine<uwBuffNum

    MEMORY_MANAGER_T* pMemory_Manager = (MEMORY_MANAGER_T*)(uwPhyPoolHandle);
    //calculate block_num needed
    buffer_num_per_block = BLOCK_SIZE / uwBuffSize;
    used_block_num = HighLine / buffer_num_per_block + 1;

    //Test
    printf("free_block_num: %lu\n", pMemory_Manager->pPhysical_manager->free_block_num);
    printf("used_block_num: %lu\n", used_block_num);

    //alloc Logical_manager
    LOGICAL_MANAGER_T* pLogical_manager = (LOGICAL_MANAGER_T*)malloc(sizeof(LOGICAL_MANAGER_T));

    //calculate logical_pool_id
    if (pMemory_Manager->pLogical_manager == NULL) {
        pLogical_manager->logical_pool_id = 0;
    } else {
        LOGICAL_MANAGER_T* pTemp = pMemory_Manager->pLogical_manager;
        while(pTemp->next != NULL) {
            pTemp = pTemp->next;
        }
        pLogical_manager->logical_pool_id = pTemp->logical_pool_id + 1;
    }

    return 0;
}

int main() {
    UINT64 test_addr = (UINT64)malloc(PHYPOOLSIZE);
    UINT64* puwPhyPoolHandle = (UINT64*)malloc(sizeof(UINT64));

    BMU_PhyPoolInit(0, test_addr, PHYPOOLSIZE, puwPhyPoolHandle);
    printf("*************************************************\n");
    UINT64 uwBuffSize_256 = 1024*256; // 256k
    UINT64* puwLogicPoolHandle_256 = (UINT64*)malloc(sizeof(UINT64));
    //max buf: 10, LowLine:3, HighLine: 7
    BMU_LogicPoolCreate(*puwPhyPoolHandle, uwBuffSize_256, 10, puwLogicPoolHandle_256, 3, 7);

    return 0;
}
