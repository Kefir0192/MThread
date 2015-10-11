#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"
#include <task.h>
#include <mutex.h>
#include <delay.h>



struct Mmutex MutexA;

uint32_t stack_a[64];
uint32_t stack_b[64];

uint32_t vA = 5, vB;

void Thread_A(void *pVoid)
{
    while(1) {
        eMutex_lock(&MutexA);

        Delay(0x10000);
        GPIOE->ODR ^= GPIO_ODR_ODR0;

        Delay(0x10000);
        GPIOE->ODR ^= GPIO_ODR_ODR0;

        Delay(0x10000);
        GPIOE->ODR ^= GPIO_ODR_ODR0;

        Delay(0x10000);
        GPIOE->ODR ^= GPIO_ODR_ODR0;

        eMutex_unlock(&MutexA);
    }
}

void Thread_B(void *pVoid)
{
    while(1) {
        eMutex_lock(&MutexA);

        Delay(0x10000);
        GPIOE->ODR ^= GPIO_ODR_ODR2;

        Delay(0x10000);
        GPIOE->ODR ^= GPIO_ODR_ODR2;

        Delay(0x10000);
        GPIOE->ODR ^= GPIO_ODR_ODR2;

        Delay(0x10000);
        GPIOE->ODR ^= GPIO_ODR_ODR2;

        eMutex_unlock(&MutexA);
    }
}
