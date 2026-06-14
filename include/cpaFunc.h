#pragma once

#include "cpa.h"

#ifdef __cplusplus
extern "C" {
#endif

_CPAAPI_ CPAFILE* cpaAllocNewMem();
_CPAAPI_ void cpaDestroyMem(CPAFILE* File);

_CPAAPI_ int cpaNewRootDir(CPAFILE* File, wchar_t* NewDirName, size_t NewDirNameSize);

_CPAAPI_ uint32_t GetDirCount(CPAFILE* File);
_CPAAPI_ void SetDirCount(CPAFILE* File, uint32_t DirCount);
_CPAAPI_ uint32_t GetRootEnvSize(CPAFILE* File);
void SetRootEnvSize(CPAFILE* File, uint32_t EnvSize);

#ifdef __cplusplus
}
#endif

