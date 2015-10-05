#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"
#include <task.h>
#include <mutex.h>



//------------------------------------------------------
// Инициализация скорости работы МК
//------------------------------------------------------
void Oscillator_int(void)
{
    MDR_RST_CLK->HS_CONTROL = 0x1;                  // Бит управления HSE осциллятором: 1 – включен
    MDR_RST_CLK->PLL_CONTROL = (BIT2 | (8 << 8));   // (2) Бит включения PLL: 1 – PLL включена;
                                                    // (11...8) Коэффициент умножения для CPU PLL: PLLCPUo = PLLCPUi x (PLLCPUMUL+1)
    while(!(MDR_RST_CLK->CLOCK_STATUS & 0x02));     // ждем когда PLL выйдет в раб. режим

    MDR_RST_CLK->CPU_CLOCK = (    BIT1              // (1…0)    Биты выбора источника для CPU_C1: 10 – HSE
                                | BIT2              // (2)      Биты выбора источника для CPU_C2: 1 – PLLCPUo
                                | (0 << 4)          // (7…4)    Биты выбора делителя для CPU_C3: 0xxx – CPU_C3 = CPU_C2
                                | BIT8);            // (9…8)    Биты выбора источника для HCLK: 01 – CPU_C3
}

//------------------------------------------------------
// Инициализация
//------------------------------------------------------
void Init_Hardware(void)
{
    // NVIC - смещаем таблицу векторов прерываний (начало памяти программ)
    SCB->VTOR = 0x08000000;
    // Инициализация скорости работы МК
    Oscillator_int();
    // Инициализация PORT
    Port_Init();
    //
    __enable_irq();
}

uint32_t stack_a[64];
uint32_t stack_b[64];

uint32_t vA = 5, vB;
mmutex *MutexA = NULL;

void Thread_A(void *pVoid)
{
    while(1) {
        Delay(0x80000);
        MDR_PORTE->RXTX ^= BIT6;
    }
}

void Thread_B(void *pVoid)
{
    while(1) {
        Delay(0x40000);
        MDR_PORTE->RXTX ^= BIT7;
    }
}



//------------------------------------------------------
// MAIN
//------------------------------------------------------
int main(void)
{
    // Инициализация
    Init_Hardware();

    NVIC_SetPriority(PendSV_IRQn, 0xff);
    NVIC_SetPriority(SysTick_IRQn, 0xff);

    uint8_t current_min_priority = 0;
    uint8_t current_priority = 0;

    eTask_Create(&eTask_Element[0], Thread_A, &stack_a[63], 64, &vA);
    eTask_Create(&eTask_Element[1], Thread_B, &stack_b[63], 64, &vB);

    eStart_Schedule();

    while(1)
    {

    }
    return 0;
}
