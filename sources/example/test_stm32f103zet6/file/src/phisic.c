#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"



//------------------------------------------------------
// Initialize oscillator
//------------------------------------------------------
void Oscillator_Init(void)
{

}

//------------------------------------------------------
// Initialization GPIO
//------------------------------------------------------
void Port_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
    GPIOE->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE2;

    GPIOE->ODR |= GPIO_ODR_ODR0;
    GPIOE->ODR |= GPIO_ODR_ODR2;
}
