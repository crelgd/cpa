#include "cpaType.h"
#include "cpaFunc.h"

int main(int argc, char* argv[])
{
    CPAFILE* File = cpaAllocNewMem();

    if (!File)
    {
        printf("ERR");
        return 1;
    }

    //FILE* OutFile = fopen("TEST.CPA", "wb+");

    while (1)
    {

    printf("Input the new directory name: ");
    char output[1024];
    fgets(output, 1024, stdin);

    if (memcmp(output, "exit()", 6) == 0)
        break;

    wchar_t DirName[2048];
    mbstowcs(DirName, output, 1024);

    if (cpaNewRootDir(File, DirName, wcslen(DirName) * 2) != CPA_OK)
    {
        printf("ERR");
        return 1;
    }

    }

    for (int i = 0; i < File->FileSize; i++)
    {
        printf("%02X ", File->File[i] & 0xFF);
    }

    printf("\n");

    //fwrite(File, 1, sizeof(File), OutFile);

    cpaDestroyMem(File);
    //fclose(OutFile);

    return 0;
}

