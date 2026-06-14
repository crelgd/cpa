// Copyright (c) crelgd 2026
// Подробнее в файле LICENSE.txt

#pragma once

#define _CPAAPI_ __declspec(dllexport)

#ifdef __cplusplus

#   include <cstdint>

#else

#   include <stdint.h>
#   include <stdlib.h>
#   include <stdio.h>
#   include <string.h>

#endif

#ifdef __DEBUG
#   define LOG(_msg) printf(_msg)
#else
#   define LOG(_msg)
#endif

enum CPAERR {
    CPA_ERR,
    CPA_OK
};

