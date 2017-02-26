#include <stdio.h>
#include <stdlib.h>

#include "api.h"
#include "manager.h"

#define PHYPOOLSIZE 1024*1024*10 // 10M
#define BLOCK_SIZE 1024*1024*1 // 1M

UINT64 BMU_PhyPoolInit(UINT64 uwPhyPoolIndex, UINT64 uwMemAddr, UINT64 uwMemSize, UINT64* puwPhyPoolHandle) {
    if(uwPhyPoolIndex != 0) {
        printf("input uwPhyPoolIndex: %lu\n error", uwPhyPoolIndex);
        return 1;
    }
    printf("BMU_PhyPoolInit called.\n");
    printf("uwMemAddr: %lu\n", uwMemAddr);





    return 0;
}


int main() {
    UINT64 base_addr = (UINT64)malloc(PHYPOOLSIZE);
    UINT64* puwPhyPoolHandle = NULL;

    BMU_PhyPoolInit(0, base_addr, BLOCK_SIZE, puwPhyPoolHandle);

    return 0;
}
