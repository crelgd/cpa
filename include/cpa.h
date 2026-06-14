// Copyright (c) crelgd 2026
// Подробнее в файле LICENSE.txt

#pragma once

#include "cpaType.h"

#define CPA_MAGIC_SIGN          "~__CPA*"
#define CPA_MAGIC_SIGN_SIZE     7

typedef struct {
    char* File;
    size_t FileSize;
    int FileCount;
    int DirCount;
} CPAFILE;

// Заголовок архива
//
typedef struct {

    // Заголовок обычно 0x7E 0x5F 0x5F 0x43 0x50 0x41 0x2A
    //                   ~    _    _    C    P    A    *
    char        Sign[7];

    // Версия формата
    // Текущая версия 0x00 (те v0)
    //
    uint8_t     Version;

    // Общее количество файлов в текущем архиве
    //
    uint32_t    FileCount;

    // Общее количество директорий в текущем архиве
    //
    uint32_t    DirCount;

} CPASIGN;

// Определение элемента (файла или каталога) в пространстве 
// директории
//
typedef struct {

    // Тип элемента (директория 0x00, файл 0xFF)
    //
    uint8_t     Type;

    // Указатель на начало текущего элемента
    //
    // (В случае с указаным типом - директория, указатель
    // указывает на начало пространства директорий
    // (Размер пространства элементов)
    //
    uint32_t*   ElementPtr;

    // Байтовое значение представляющее флаг для
    // определения импортированого элемента
    // в случае если IsImport равняется 0xFF 
    // текущий элемент должен содержать реализацию в другом архиве
    //
    uint8_t     IsImport;

    // Строка названия элемент
    //
    wchar_t*    ElementName;

} CPAELEMENT;

typedef struct {

    // Размер пространства директории не включая данную переменную
    //
    uint32_t    EnvSize;

    CPAELEMENT* Element;

} CPADIRENV;

