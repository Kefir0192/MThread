#ifndef GLOBALINCLUDEFILE_H_INCLUDED
#define GLOBALINCLUDEFILE_H_INCLUDED
/*
    Структура
    +-----------------------------------------------------------------------+
    |                       GlobalIncludeFile.h                             |
    +-----------------------------------------------------------------------+
    |                       Phisic.c Phisic.h                               |
    +-----------------------------------------------------------------------+
    |                                                                       |
    +-----------------------------------------------------------------------+
    |                       main.c   main.h                                 |
    +-----------------------------------------------------------------------+
*/
#include "MDR32Fx.h"
#include "startup_1986ve92.h"

#define NULL                (0x0000)

#define BIT0                (0x0001)
#define BIT1                (0x0002)
#define BIT2                (0x0004)
#define BIT3                (0x0008)
#define BIT4                (0x0010)
#define BIT5                (0x0020)
#define BIT6                (0x0040)
#define BIT7                (0x0080)
#define BIT8                (0x0100)
#define BIT9                (0x0200)
#define BITA                (0x0400)
#define BITB                (0x0800)
#define BITC                (0x1000)
#define BITD                (0x2000)
#define BITE                (0x4000)
#define BITF                (0x8000)

#define BIT10               (0x0400)
#define BIT11               (0x0800)
#define BIT12               (0x1000)
#define BIT13               (0x2000)
#define BIT14               (0x4000)
#define BIT15               (0x8000)

#define BIT16               (0x10000)
#define BIT17               (0x20000)
#define BIT18               (0x40000)
#define BIT19               (0x80000)
#define BIT20               (0x100000)
#define BIT21               (0x200000)
#define BIT22               (0x400000)
#define BIT23               (0x800000)
#define BIT24               (0x1000000)
#define BIT25               (0x2000000)
#define BIT26               (0x4000000)
#define BIT27               (0x8000000)
#define BIT28               (0x10000000)
#define BIT29               (0x20000000)
#define BIT30               (0x40000000)
#define BIT31               (0x80000000)

#define RETURN_H_3(a)       (((a)>>24)&0xff)
#define RETURN_H_2(a)       (((a)>>16)&0xff)
#define RETURN_H_1(a)       (((a)>>8)&0xff)
#define RETURN_H_0(a)       ((a)&0xff)

#define RETURN_H(a)         (((a)>>8)&0xff)
#define RETURN_L(a)         ((a)&0xff)

#define COMBINE(H, L)       (((H) << 8) | (L))

enum BOOL {
    FALSE = 0,
    TRUE
};

#endif // GLOBALINCLUDEFILE_H_INCLUDED
