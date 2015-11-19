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
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    GPIOD->MODER |= GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 |
        GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;
}
