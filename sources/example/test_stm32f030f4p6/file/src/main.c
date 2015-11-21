#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"
#include <task.h>
#include <mutex.h>
#include <delay.h>


//------------------------------------------------------
//  Инициализация скорости работы МК
//------------------------------------------------------
void Oscillator_int(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER |= (GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0);
}


//------------------------------------------------------
//  Инициализация
//------------------------------------------------------
void Init_Hardware(void)
{
    Oscillator_int();
    Port_Init();
    __enable_irq();
}

void Scheduler_ARMv7M(void);

extern uint32_t OS_PSPs;
uint32_t OS_PSPs = 2;

void PendSV_Start(void)
{
    SCB->ICSR |= BIT28;
}


struct Mmutex MutexA;

uint32_t stack_a[64];
uint32_t stack_b[64];

uint32_t vA = 5, vB;

void Thread_A(void *pVoid)
{
    while(1) {
        eMutex_lock(&MutexA);

        Delay(0x10000);
        GPIOA->ODR ^= GPIO_ODR_4;

        Delay(0x10000);
        GPIOA->ODR ^= GPIO_ODR_4;

        Delay(0x10000);
        GPIOA->ODR ^= GPIO_ODR_4;

        Delay(0x10000);
        GPIOA->ODR ^= GPIO_ODR_4;

        eMutex_unlock(&MutexA);
    }
}

void Thread_B(void *pVoid)
{
    while(1) {
        eMutex_lock(&MutexA);

        Delay(0x1000);
        GPIOA->ODR ^= GPIO_ODR_4;

        Delay(0x1000);
        GPIOA->ODR ^= GPIO_ODR_4;

        Delay(0x1000);
        GPIOA->ODR ^= GPIO_ODR_4;

        Delay(0x1000);
        GPIOA->ODR ^= GPIO_ODR_4;

        eMutex_unlock(&MutexA);
    }
}


int main(void)
{
    //  Инициализация
    Init_Hardware();

    eMutex_Create(&MutexA);

    eTask_Create(&eTask_Element[0], Thread_A, &stack_a[63], 64, &vA, 0);
    eTask_Create(&eTask_Element[1], Thread_B, &stack_b[63], 64, &vB, 0);

    eStart_Schedule();


    while(1) {

    }
}
