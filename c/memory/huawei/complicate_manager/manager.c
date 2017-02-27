/*=============================================================================
#     FileName: manager.c
#         Desc:
#       Author: ChengYi
#        Email: chengyi818@foxmail.com
#     HomePage:
#      Created: 2017-02-27 20:00:23
#      Version: 0.0.1
#   LastChange: 2017-02-27 20:00:23
#      History:
#               0.0.1 | ChengYi | init
=============================================================================*/

#include <stdio.h>
#include "manager.h"

UINT64 check_BMU_PhyPoolInit_parm(UINT64 uwPhyPoolIndex) {
    printf("check_BMU_PhyPoolInit_parm called.\n");
    if(uwPhyPoolIndex != 0) {
        printf("input uwPhyPoolIndex: %lu\n error", uwPhyPoolIndex);
        return 1;
    }
    return 0;
}


UINT64 calculate_PhyPoolInit_block_num(UINT64 uwMemAddr, UINT64 uwMemSize, UINT64* pTotal_block_num, UINT64* pBlock_base_addr) {
    printf("calculate_PhyPoolInit_block_num called.\n");
    if(uwMemAddr % BLOCK_SIZE == 0) {
        *pTotal_block_num = uwMemSize/BLOCK_SIZE;
        *pBlock_base_addr = uwMemAddr;
    } else {
        *pTotal_block_num = uwMemSize/BLOCK_SIZE - 1;
        *pBlock_base_addr = ((uwMemAddr>>20) + 1) << 20;
    }
    printf("uwMemAddr: %p\n", (void *)uwMemAddr);
    printf("total_block_num: %lu\n", *pTotal_block_num);
    printf("block_base_addr: %p\n", (void *)*pBlock_base_addr);

    return 0;
}


UINT64 check_PhyPool_after_init(MEMORY_MANAGER_T* pMemory_Manager) {
    //test linked list after alloc
    printf("check_PhyPool_after_init called.\n");
    PHYSICAL_BLOCK_T* pTemp = pMemory_Manager->pPhysical_manager->pBlock_Free;
    while(pTemp != NULL) {
        printf("block id: %lu, block_base_addr: %p\n", pTemp->block_id, (void*)pTemp->base_addr);
        pTemp = pTemp->next;
    }

    return 0;
}
