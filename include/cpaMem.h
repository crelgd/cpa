#pragma once

#ifdef __cplusplus
extern "C" {
#endif

char* MoveArray(char* Arr, size_t Size, int SplitCount, size_t Offset);
char* StructToArray(void* Struct, size_t StructSize);
char* ElementToArray(CPAELEMENT* El);

#ifdef __cplusplus
}
#endif
