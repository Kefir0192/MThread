#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"
#include <task.h>
#include <mutex.h>
#include <delay.h>

// GPIOD->ODR = LED_BLUE | LED_ORANGE | LED_RED | LED_GREEN;

struct Mmutex MutexA;

uint32_t stack_a[128];
uint32_t stack_b[128];

uint32_t vA = 5, vB;

void Thread_A(void *pVoid)
{
    while(1) {
        eMutex_lock(&MutexA);

        GPIOD->ODR ^= LED_BLUE;
        Delay(0x10000);
        Delay(0x10000);
        Delay(0x10000);

        GPIOD->ODR ^= LED_BLUE;
        Delay(0x10000);
        Delay(0x10000);
        Delay(0x10000);

        eMutex_unlock(&MutexA);
    }
}

void Thread_B(void *pVoid)
{
    while(1) {
        eMutex_lock(&MutexA);

        GPIOD->ODR ^= LED_ORANGE;
        Delay(0x10000);
        Delay(0x10000);
        Delay(0x10000);

        GPIOD->ODR ^= LED_ORANGE;
        Delay(0x10000);
        Delay(0x10000);
        Delay(0x10000);

        eMutex_unlock(&MutexA);
    }
}
