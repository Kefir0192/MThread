#include "inc/GlobalIncludeFile.h"
#include "inc/main.h"
#include "inc/phisic.h"
#include "inc/MThread_inc/mthread_task.h"
#include "inc/MThread_inc/mmutex.h"


//------------------------------------------------------
//  Инициализация скорости работы МК
//------------------------------------------------------
void Oscillator_int(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    GPIOC->MODER |= (GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
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


struct Mmutex MutexA = {
    NULL,
    0
};

uint32_t stack_a[64];
uint32_t stack_b[64];

uint32_t vA = 5, vB;

void Thread_A(void *pVoid)
{
    while(1) {
        eMutex_lock(&MutexA);

        Delay(0x10000);
        GPIOC->ODR ^= GPIO_ODR_8;

        Delay(0x10000);
        GPIOC->ODR ^= GPIO_ODR_8;

        Delay(0x10000);
        GPIOC->ODR ^= GPIO_ODR_8;

        Delay(0x10000);
        GPIOC->ODR ^= GPIO_ODR_8;

        eMutex_unlock(&MutexA);
    }
}

void Thread_B(void *pVoid)
{
    while(1) {
        eMutex_lock(&MutexA);

        Delay(0x10000);
        GPIOC->ODR ^= GPIO_ODR_9;

        Delay(0x10000);
        GPIOC->ODR ^= GPIO_ODR_9;

        Delay(0x10000);
        GPIOC->ODR ^= GPIO_ODR_9;

        Delay(0x10000);
        GPIOC->ODR ^= GPIO_ODR_9;

        eMutex_unlock(&MutexA);
    }
}


int main(void)
{
    //  Инициализация
    Init_Hardware();


    eTask_Create(&eTask_Element[0], Thread_A, &stack_a[63], 64, &vA);
    eTask_Create(&eTask_Element[1], Thread_B, &stack_b[63], 64, &vB);

    eStart_Schedule();

    while(1) {


    }
}
