#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"

void HardFault_Handler(void)
{
    while(1)
    {
        GPIOA->ODR |= GPIO_ODR_4;
        __ASM("nop");
    }
}

const ISR_VECTOR POINTER_ITERRAPT ArrayInterrapt[] = {
    /*----------Core Exceptions------------------------------------------------ */
    //NMI_Handler,
    (POINTER_ITERRAPT)STACK_TOP,    /*!< The initial stack pointer              */
    Reset_Handler,                  /*!< Reset Handler                          */
    loop, // NMI_Handler,
    loop, // HardFault_Handler,
    0, 0, 0, 0, 0, 0, 0,
    loop, // SVC_Handler,
    0, 0,
    PendSV_Handler,
    SysTick_Handler,

    loop, // WWDG_IRQHandler,
    0,
    loop, // RTC_IRQHandler,
    loop, // FLASH_IRQHandler,
    loop, // RCC_IRQHandler,
    loop, // EXTI0_1_IRQHandler,
    loop, // EXTI2_3_IRQHandler,
    loop, // EXTI4_15_IRQHandler,
    0,
    loop, // DMA1_Channel1_IRQHandler,
    loop, // DMA1_Channel2_3_IRQHandler,
    loop, // DMA1_Channel4_5_IRQHandler,
    loop, // ADC1_IRQHandler,
    loop, // TIM1_BRK_UP_TRG_COM_IRQHandler,
    loop, // TIM1_CC_IRQHandler,
    0,
    loop, // TIM3_IRQHandler,
    0, 0,
    loop, // TIM14_IRQHandler,
    loop, // TIM15_IRQHandler,
    loop, // TIM16_IRQHandler,
    loop, // TIM17_IRQHandler,
    loop, // I2C1_IRQHandler,
    loop, // I2C2_IRQHandler,
    loop, // SPI1_IRQHandler,
    loop, // SPI2_IRQHandler,
    loop, // USART1_IRQHandler,
    loop, // USART2_IRQHandler,
    0, 0, 0,
    loop, // BootRAM          
	/* @0x108. This is for boot in RAM mode for STM32F0xx devices. */
};

// Функция заглушка
__attribute__ ((section(".loop")))
void loop(void)
{
    while(1)
    {
        __ASM("nop");
    }
}

// .rodata — глобальные и статические переменные;
// .data — глобальные и статические переменные;
void ro_data_init(void *pStartOUT, void *pStartIN, void *pEndIN)
{
    while(pStartIN != pEndIN) *((uint8_t *)pStartIN++) = *((uint8_t *)pStartOUT++);
}
// .bss — глобальные и статические переменные, которые при старте содержат нулевое значение.
void bss_init(void *pStartIN, void *pEndIN)
{
    void *p = 0x00;
    while(p++ != pEndIN) *((uint8_t *)pStartIN++) = 0x00;
}

// Начало
void Reset_Handler(void)
{
    // .rodata — глобальные и статические переменные;
    ro_data_init(&_start_rodata_copi, &_start_rodata, &_end_rodata);
    // .data — глобальные и статические переменные;
    ro_data_init(&_start_data_copi, &_start_data, &_end_data);
    // .bss — глобальные и статические переменные, которые при старте содержат нулевое значение.
    bss_init(&_start_bss, &_size_bss);
    // Начало работы
    main();
    // Выход из main
}
