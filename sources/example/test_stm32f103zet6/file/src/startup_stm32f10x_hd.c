#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"

void HardFault_Handler(void)
{
    while(1)
    {
        GPIOE->ODR ^= GPIO_ODR_ODR2;
        __ASM("nop");
    }
}

const ISR_VECTOR POINTER_ITERRAPT ArrayInterrapt[] = {
    /*----------Core Exceptions STM32F0xx devices------------------------------ */
    //NMI_Handler,
    (POINTER_ITERRAPT)STACK_TOP,    /*!< The initial stack pointer              */
    Reset_Handler,                  /*!< Reset Handler                          */
    loop, // NMI_Handler,           /*!< NMI Handler                            */
    HardFault_Handler,              /*!< Hard Fault Handler                     */
    loop, // MemManage_Handler      /*!< MPU Fault Handler                      */
    loop, // BusFault_Handler       /*!< Bus Fault Handler                      */
    loop, // UsageFault_Handler     /*!< Usage Fault Handler                    */
    0, 0, 0, 0,
    loop, // SVC_Handler            /*!< SVCall Handler                         */
    loop, // DebugMon_Handler       /*!< Debug Monitor Handler                  */
    0,
    PendSV_Handler,                 /*!< PendSV Handler                         */
    SysTick_Handler,                /*!< SysTick Handler                        */

    /*----------External Interrupts-------------------------------------------- */
    loop, // WWDG_IRQHandler            // Window Watchdog
    loop, // PVD_IRQHandler             // PVD through EXTI Line detect
    loop, // TAMPER_IRQHandler          // Tamper
    loop, // RTC_IRQHandler             // RTC
    loop, // FLASH_IRQHandler           // Flash
    loop, // RCC_IRQHandler             // RCC
    loop, // EXTI0_IRQHandler           // EXTI Line 0
    loop, // EXTI1_IRQHandler           // EXTI Line 1
    loop, // EXTI2_IRQHandler           // EXTI Line 2
    loop, // EXTI3_IRQHandler           // EXTI Line 3
    loop, // EXTI4_IRQHandler           // EXTI Line 4
    loop, // DMA1_Channel1_IRQHandler   // DMA1 Channel 1
    loop, // DMA1_Channel2_IRQHandler   // DMA1 Channel 2
    loop, // DMA1_Channel3_IRQHandler   // DMA1 Channel 3
    loop, // DMA1_Channel4_IRQHandler   // DMA1 Channel 4
    loop, // DMA1_Channel5_IRQHandler   // DMA1 Channel 5
    loop, // DMA1_Channel6_IRQHandler   // DMA1 Channel 6
    loop, // DMA1_Channel7_IRQHandler   // DMA1 Channel 7
    loop, // ADC1_2_IRQHandler          // ADC1 & ADC2
    loop, // USB_HP_CAN1_TX_IRQHandler  // USB High Priority or CAN1 TX
    loop, // USB_LP_CAN1_RX0_IRQHandler // USB Low  Priority or CAN1 RX0
    loop, // CAN1_RX1_IRQHandler        // CAN1 RX1
    loop, // CAN1_SCE_IRQHandler        // CAN1 SCE
    loop, // EXTI9_5_IRQHandler         // EXTI Line 9..5
    loop, // TIM1_BRK_IRQHandler        // TIM1 Break
    loop, // TIM1_UP_IRQHandler         // TIM1 Update
    loop, // TIM1_TRG_COM_IRQHandler    // TIM1 Trigger and Commutation
    loop, // TIM1_CC_IRQHandler         // TIM1 Capture Compare
    loop, // TIM2_IRQHandler            // TIM2
    loop, // TIM3_IRQHandler            // TIM3
    loop, // TIM4_IRQHandler            // TIM4
    loop, // I2C1_EV_IRQHandler         // I2C1 Event
    loop, // I2C1_ER_IRQHandler         // I2C1 Error
    loop, // I2C2_EV_IRQHandler         // I2C2 Event
    loop, // I2C2_ER_IRQHandler         // I2C2 Error
    loop, // SPI1_IRQHandler            // SPI1
    loop, // SPI2_IRQHandler            // SPI2
    loop, // USART1_IRQHandler          // USART1
    loop, // USART2_IRQHandler          // USART2
    loop, // USART3_IRQHandler          // USART3
    loop, // EXTI15_10_IRQHandler       // EXTI Line 15..10
    loop, // RTCAlarm_IRQHandler        // RTC Alarm through EXTI Line
    loop, // USBWakeUp_IRQHandler       // USB Wakeup from suspend
    loop, // TIM8_BRK_IRQHandler        // TIM8 Break
    loop, // TIM8_UP_IRQHandler         // TIM8 Update
    loop, // TIM8_TRG_COM_IRQHandler    // TIM8 Trigger and Commutation
    loop, // TIM8_CC_IRQHandler         // TIM8 Capture Compare
    loop, // ADC3_IRQHandler            // ADC3
    loop, // FSMC_IRQHandler            // FSMC
    loop, // SDIO_IRQHandler            // SDIO
    loop, // TIM5_IRQHandler            // TIM5
    loop, // SPI3_IRQHandler            // SPI3
    loop, // UART4_IRQHandler           // UART4
    loop, // UART5_IRQHandler           // UART5
    loop, // TIM6_IRQHandler            // TIM6
    loop, // TIM7_IRQHandler            // TIM7
    loop, // DMA2_Channel1_IRQHandler   // DMA2 Channel1
    loop, // DMA2_Channel2_IRQHandler   // DMA2 Channel2
    loop, // DMA2_Channel3_IRQHandler   // DMA2 Channel3
    loop, // DMA2_Channel4_5_IRQHandler // DMA2 Channel4 & Channel5
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
