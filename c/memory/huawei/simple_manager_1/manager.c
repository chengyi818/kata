#include <stdio.h>
#include <stdlib.h>
#include "manager.h"

UINT32 MemInit(void *pMemAddr, UINT32 ulMemSize) {
    printf("Enter MemInit, pMemAddr: %p\n", pMemAddr);
    printf("BLOCK_TOTAL_NUM: %d\n", BLOCK_TOTAL_NUM);
    if (ulMemSize != ULMEMSIZE) {
        printf("total memory size not match\n");
        return 1;
    }
    pMem_Manager = (Mem_Manager*)pMemAddr;
    pMem_Manager->FreeBlkNum = BLOCK_TOTAL_NUM;
    pMem_Manager->UsedBlkNum = 0;
    UINT32 i = 0;

    for(i=0; i<BLOCK_TOTAL_NUM; i++){
        pMem_Manager->BlkArray[i].id = i;
        pMem_Manager->BlkArray[i].addr = (void *)(((char *)pMemAddr) + (MANAGER_MEMORY_SIZE + i*BLOCK_SIZE));
    }

    return 0;
}

void* MemAlloc(UINT32 size) {
    if(size <= 0 || size > BLOCK_SIZE){
        printf("alloc size: %d, param must lager than 0 and less than %d\n", size, BLOCK_SIZE);
        return 0;
    }
    if(pMem_Manager->UsedBlkNum >= BLOCK_TOTAL_NUM) {
        printf("memory all in used\n");
        return 0;
    }

    UINT32 index = pMem_Manager->UsedBlkNum;
    pMem_Manager->FreeBlkNum -= 1;
    pMem_Manager->UsedBlkNum += 1;
    printf("alloc block id: %d, addr: %p\n", pMem_Manager->BlkArray[index].id, pMem_Manager->BlkArray[index].addr);

    return pMem_Manager->BlkArray[index].addr;
}

UINT32 MemFree(void* memory) {
    //check memory addr correct
    UINT32 block_found = 0;
    UINT32 j = 0;
    for(j=0; j < pMem_Manager->UsedBlkNum; j++){
        if(pMem_Manager->BlkArray[j].addr == memory) {
            block_found = 1;
            printf("free block_found, id: %d, addr: %p\n", pMem_Manager->BlkArray[j].id, pMem_Manager->BlkArray[j].addr);
            break;
        }
    }

    if(block_found == 0) {
        printf("memory: %p error\n", memory);
        return 1;
    }

    //move free block to stack top
    Block Temp = pMem_Manager->BlkArray[j];
    pMem_Manager->BlkArray[j] = pMem_Manager->BlkArray[pMem_Manager->UsedBlkNum-1];
    pMem_Manager->BlkArray[pMem_Manager->UsedBlkNum-1] = Temp;

    pMem_Manager->FreeBlkNum += 1;
    pMem_Manager->UsedBlkNum -= 1;

    return 0;
}

UINT32 MemGetMemInfo(UINT32 *pulFreeBlkNum, UINT32 *pulUsedBlkNum) {
    pulFreeBlkNum = &(pMem_Manager->FreeBlkNum);
    pulUsedBlkNum = &(pMem_Manager->UsedBlkNum);
    printf("FreeBlkNum: %d, UsedBlkNum: %d\n", *pulFreeBlkNum, *pulUsedBlkNum);

    return 0;
}


int main(){
    UINT32 *pulFreeBlkNum;
    UINT32 *pulUsedBlkNum;

    void* base_addr = malloc(ULMEMSIZE);
    MemInit(base_addr, ULMEMSIZE);

    void* addr_0 = MemAlloc(-1);
    void* addr_1 = MemAlloc(0);
    void* addr_2 = MemAlloc(1);
    void* addr_3 = MemAlloc(2);
    MemGetMemInfo(pulFreeBlkNum, pulUsedBlkNum);
    void* addr_4 = MemAlloc(3);
    void* addr_5 = MemAlloc(4);
    void* addr_6 = MemAlloc(99999);
    MemGetMemInfo(pulFreeBlkNum, pulUsedBlkNum);

    MemFree(addr_0);
    MemFree(addr_1);
    MemFree(addr_2);
    MemFree(addr_3);
    MemGetMemInfo(pulFreeBlkNum, pulUsedBlkNum);

    void* addr_7 = MemAlloc(1); //should be id: 1
    void* addr_8 = MemAlloc(1); //should be id: 0
    MemGetMemInfo(pulFreeBlkNum, pulUsedBlkNum);


    return 0;
}
