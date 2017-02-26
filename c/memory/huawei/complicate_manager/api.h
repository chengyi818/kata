#include <stdint.h>

#ifndef __API_H__
#define __API_H__

typedef uint32_t UINT32;
typedef uint64_t UINT64;

typedef struct Bmu_LogicPool_Info {
    UINT64 uwLogicPoolHandle;
    UINT64 uwUsdTotalBlockNum;
    UINT64 uwFreeBuffNum;
    UINT64 uwUsdBuffNum;
} BMU_LOGICPOOL_INFO_STRU;

typedef struct Bmu_PhyPool_INFO {
    UINT64 uwPhyPoolHandle;
    UINT64 uwTotalBlockNum;
    UINT64 uwFreeBlockNum;
    UINT64 uwLogicBlockNum;
    BMU_LOGICPOOL_INFO_STRU* pstrLogicPoolInfo;
} BMU_PHYPOOL_INFO_STRU;

//uwPyhPoolIndex always be zero,means Physical pool only one
UINT64 BMU_PyhPoolInit(UINT64 uwPyhPoolIndex, UINT64 uwMemAddr, UINT64 uwMemSize, UINT64* puwPhyPoolHandle);

UINT64 BMU_LogicPoolCreate(UINT64 puwPhyPoolHandle, UINT64 uwBuffSize, UINT64 uwBuffNum, UINT64 *puwLogicPoolHandle, UINT64 LowLine, UINT64 HighLine);

UINT64 BMU_LogicPoolDel(UINT64 uwLogicPoolHandle);

UINT64 BMU_MemAlloc(UINT64 puwLogicPoolHandle, UINT64* puwMemAddr);

UINT64 BMU_MemFree(UINT64 uwLogicPoolHandle, UINT64* puwMemAddr);

UINT64 BMU_PhyPoolInfoShow(UINT64 puwPhyPoolHandle, BMU_PHYPOOL_INFO_STRU* pstrPhyPoolInfo);

#endif /* __API_H__ */

