#include "cpaFunc.h"
#include "cpaMem.h"

CPAFILE* cpaAllocNewMem()
{
    CPAFILE* File = malloc(sizeof(CPAFILE));

    if (!File) 
        return NULL;
    
    File->File = (char*)malloc(sizeof(CPASIGN)+4);

    if (!File->File)
        return NULL;

    File->FileSize = sizeof(CPASIGN) + 4;

    char OUT[] = {
        0x7e, 0x5f, 0x5f, 0x43, 0x50, 0x41, 0x2a, // заголовок
        0x00,                                     // Версия 
        0x00, 0x00, 0x00, 0x00,                   // Общее количество файлов
        0x00, 0x00, 0x00, 0x00,                   // Общее количество директорий
        0x00, 0x00, 0x00, 0x00                    // Глобальная директория (только
    };                                            // размер пространства)

    memcpy(File->File, OUT, File->FileSize);

    File->DirCount = 0;
    File->FileCount = 0;

    return File;
}

void cpaDestroyMem(CPAFILE* File)
{
    if (File)
    {
        free(File->File);
        free(File);
    }
}

/*
пишет но без создания отдельного пространства
думаю создать функцию для чтения записей в корне и тд
и так создать свободное пронстранство
*/
int cpaNewRootDir(CPAFILE* File, wchar_t* NewDirName, size_t NewDirNameSize)
{
    if (!File) 
        return CPA_ERR;

    uint32_t DirCount = GetDirCount(File);  
    uint32_t RootDirSize = GetRootEnvSize(File);

    CPAELEMENT el;
    el.Type = 0x00;
    el.ElementPtr = 0x02;
    el.IsImport = 0x00;

    uint32_t DirSize = 6;

    char* DirHeader = ElementToArray(&el);
    DirHeader = MoveArray(DirHeader, DirSize, NewDirNameSize, DirSize);
    memcpy(DirHeader + DirSize, NewDirName, NewDirNameSize);

#ifdef __DEBUG

    printf("\tDir Header:\n\tDirSize: %d\n", DirSize);

    for (int i = 0; i < DirSize + NewDirNameSize; i++)
    {
        printf("%02X ", DirHeader[i] & 0xFF);
    }

    printf("\n");

#endif

    File->File = MoveArray(File->File, File->FileSize, DirSize + NewDirNameSize, 20 + RootDirSize);
    memcpy(File->File + 20 + RootDirSize, DirHeader, DirSize + NewDirNameSize);

    SetRootEnvSize(File, RootDirSize+DirSize+NewDirNameSize);
    SetDirCount(File, DirCount+1);

    free(DirHeader);

    File->FileSize += DirSize + NewDirNameSize;

    return CPA_OK;
}

uint32_t GetDirCount(CPAFILE* File)
{
    if (!File) 
        return CPA_ERR;

    uint32_t out;
    memcpy(&out, File->File + 12, 4);
    return out;
}

void SetDirCount(CPAFILE* File, uint32_t DirCount)
{
    if (!File) 
        return CPA_ERR;

    memcpy(File->File + 12, &DirCount, 4);
}

uint32_t GetRootEnvSize(CPAFILE* File)
{
    if (!File) 
        return CPA_ERR;

    uint32_t out;
    memcpy(&out, File->File + 16, 4);
    return out;
}

void SetRootEnvSize(CPAFILE* File, uint32_t EnvSize)
{
    if (!File) 
        return CPA_ERR;

    memcpy(File->File + 16, &EnvSize, 4);
}
