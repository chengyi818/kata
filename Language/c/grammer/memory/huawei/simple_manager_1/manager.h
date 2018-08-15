#include <stdint.h>

#define ULMEMSIZE (10*1024*1024) //total memory size 10MB
#define USER_MEMORY_SIZE (9*1024*1024) // user memory 9MB
#define MANAGER_MEMORY_SIZE (1*1024*2014) // 1M to manager user memory
#define BLOCK_SIZE (1024*2) //2KB
#define BLOCK_TOTAL_NUM (USER_MEMORY_SIZE / BLOCK_SIZE) // 4608

typedef uint32_t UINT32;

typedef struct Block{
    void* addr;
    UINT32 id;
}Block;

typedef struct Mem_Manager{
    UINT32 FreeBlkNum;
    UINT32 UsedBlkNum;
    Block BlkArray[BLOCK_TOTAL_NUM];
}Mem_Manager;

Mem_Manager *pMem_Manager;

UINT32 MemInit(void *pMemAddr, UINT32 ulMemSize);

void* MemAlloc(UINT32 size);

UINT32 MemFree(void* memory);

UINT32 MemGetMemInfo(UINT32 *pulFreeBlkNum, UINT32 *pulUsedBlkNum);
