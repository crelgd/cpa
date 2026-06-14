#include "cpa.h"
#include "cpaMem.h"
#include "cpaType.h"

char* MoveArray(char* Arr, size_t Size, int SplitCount, size_t Offset)
{
    char* NArr = realloc(Arr, Size + SplitCount);
    
    if (!NArr)
        return NULL;

    char ToWrite = NArr[Offset];

    for (int i = 0; i < ((Size + SplitCount) - Offset) - 1; i++)
    {
        char Next = NArr[Offset+i+1];
        NArr[Offset+i+1] = ToWrite;
        ToWrite = Next;
    }

    return NArr;
}

char* StructToArray(void* Struct, size_t StructSize)
{
    char* OUT = malloc(StructSize);

    if (!OUT)
        return NULL;

    memcpy(OUT, Struct, StructSize);

    return OUT;
}

char* ElementToArray(CPAELEMENT* El)
{
    char* OUT = malloc(6);

    memcpy(OUT, &El->Type, 1);
    memcpy(OUT + 1, &El->ElementPtr, 4);
    memcpy(OUT + 5, &El->IsImport, 1);

    return OUT;
}
