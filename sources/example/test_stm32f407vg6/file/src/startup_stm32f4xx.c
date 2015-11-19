#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"

void HardFault_Handler(void)
{
    while(1)
    {
        GPIOD->ODR = 0x00;
        GPIOD->ODR = LED_RED;
        __ASM("nop");
    }
}

const ISR_VECTOR POINTER_ITERRAPT ArrayInterrapt[] = {
    /*----------Core Exceptions------------------------------------------------ */
    (POINTER_ITERRAPT)STACK_TOP,    /*!< The initial stack pointer              */
    Reset_Handler,                  /*!< Reset Handler                               */
    loop, // NMI_Handler,               /*!< NMI Handler                                 */
    loop, // HardFault_Handler,         /*!< Hard Fault Handler                          */
    loop, // MemManage_Handler,         /*!< MPU Fault Handler                           */
    loop, // BusFault_Handler,          /*!< Bus Fault Handler                           */
    loop, // UsageFault_Handler,        /*!< Usage Fault Handler                         */
    0,0,0,0,                        /*!< Reserved                                    */
    loop, // SVC_Handler,               /*!< SVCall Handler                              */
    loop, // DebugMon_Handler,          /*!< Debug Monitor Handler                       */
    0,                              /*!< Reserved                                    */
    PendSV_Handler,                 /*!< PendSV Handler                              */
    SysTick_Handler,                /*!< SysTick Handler                             */

    /*----------External Exceptions---------------------------------------------*/
    loop, // WWDG_IRQHandler,           /*!<  0: Window WatchDog                         */
    loop, // PVD_IRQHandler,            /*!<  1: PVD through EXTI Line detection         */
    loop, // TAMP_STAMP_IRQHandler,     /*!<  2: Tamper and TimeStamps through the EXTI line*/
    loop, // RTC_WKUP_IRQHandler,       /*!<  3: RTC Wakeup through the EXTI line        */
    loop, // FLASH_IRQHandler,          /*!<  4: FLASH                                   */
    loop, // RCC_IRQHandler,            /*!<  5: RCC                                     */
    loop, // EXTI0_IRQHandler,          /*!<  6: EXTI Line0                              */
    loop, // EXTI1_IRQHandler,          /*!<  7: EXTI Line1                              */
    loop, // EXTI2_IRQHandler,          /*!<  8: EXTI Line2                              */
    loop, // EXTI3_IRQHandler,          /*!<  9: EXTI Line3                              */
    loop, // EXTI4_IRQHandler,          /*!< 10: EXTI Line4                              */
    loop, // DMA1_Stream0_IRQHandler,   /*!< 11: DMA1 Stream 0                           */
    loop, // DMA1_Stream1_IRQHandler,   /*!< 12: DMA1 Stream 1                           */
    loop, // DMA1_Stream2_IRQHandler,   /*!< 13: DMA1 Stream 2                           */
    loop, // DMA1_Stream3_IRQHandler,   /*!< 14: DMA1 Stream 3                           */
    loop, // DMA1_Stream4_IRQHandler,   /*!< 15: DMA1 Stream 4                           */
    loop, // DMA1_Stream5_IRQHandler,   /*!< 16: DMA1 Stream 5                           */
    loop, // DMA1_Stream6_IRQHandler,   /*!< 17: DMA1 Stream 6                           */
    loop, // ADC_IRQHandler,            /*!< 18: ADC1, ADC2 and ADC3s                    */
    loop, // CAN1_TX_IRQHandler,        /*!< 19: CAN1 TX                                 */
    loop, // CAN1_RX0_IRQHandler,       /*!< 20: CAN1 RX0                                */
    loop, // CAN1_RX1_IRQHandler,       /*!< 21: CAN1 RX1                                */
    loop, // CAN1_SCE_IRQHandler,       /*!< 22: CAN1 SCE                                */
    loop, // EXTI9_5_IRQHandler,        /*!< 23: External Line[9:5]s                     */
    loop, // TIM1_BRK_TIM9_IRQHandler,  /*!< 24: TIM1 Break and TIM9                     */
    loop, // TIM1_UP_TIM10_IRQHandler,  /*!< 25: TIM1 Update and TIM10                   */
    loop, // TIM1_TRG_COM_TIM11_IRQHandler,/*!< 26: TIM1 Trigger and Commutation and TIM11*/
    loop, // TIM1_CC_IRQHandler,        /*!< 27: TIM1 Capture Compare                    */
    loop, // TIM2_IRQHandler,           /*!< 28: TIM2                                    */
    loop, // TIM3_IRQHandler,           /*!< 29: TIM3                                    */
    loop, // TIM4_IRQHandler,           /*!< 30: TIM4                                    */
    loop, // I2C1_EV_IRQHandler,        /*!< 31: I2C1 Event                              */
    loop, // I2C1_ER_IRQHandler,        /*!< 32: I2C1 Error                              */
    loop, // I2C2_EV_IRQHandler,        /*!< 33: I2C2 Event                              */
    loop, // I2C2_ER_IRQHandler,        /*!< 34: I2C2 Error                              */
    loop, // SPI1_IRQHandler,           /*!< 35: SPI1                                    */
    loop, // SPI2_IRQHandler,           /*!< 36: SPI2                                    */
    loop, // USART1_IRQHandler,         /*!< 37: USART1                                  */
    loop, // USART2_IRQHandler,         /*!< 38: USART2                                  */
    loop, // USART3_IRQHandler,         /*!< 39: USART3                                  */
    loop, // EXTI15_10_IRQHandler,      /*!< 40: External Line[15:10]s                   */
    loop, // RTC_Alarm_IRQHandler,      /*!< 41: RTC Alarm (A and B) through EXTI Line   */
    loop, // OTG_FS_WKUP_IRQHandler,    /*!< 42: USB OTG FS Wakeup through EXTI line     */
    loop, // TIM8_BRK_TIM12_IRQHandler, /*!< 43: TIM8 Break and TIM12                    */
    loop, // TIM8_UP_TIM13_IRQHandler,  /*!< 44: TIM8 Update and TIM13                   */
    loop, // TIM8_TRG_COM_TIM14_IRQHandler,/*!< 45:TIM8 Trigger and Commutation and TIM14*/
    loop, // TIM8_CC_IRQHandler,        /*!< 46: TIM8 Capture Compare                    */
    loop, // DMA1_Stream7_IRQHandler,   /*!< 47: DMA1 Stream7                            */
    loop, // FSMC_IRQHandler,           /*!< 48: FSMC                                    */
    loop, // SDIO_IRQHandler,           /*!< 49: SDIO                                    */
    loop, // TIM5_IRQHandler,           /*!< 50: TIM5                                    */
    loop, // SPI3_IRQHandler,           /*!< 51: SPI3                                    */
    loop, // UART4_IRQHandler,          /*!< 52: UART4                                   */
    loop, // UART5_IRQHandler,          /*!< 53: UART5                                   */
    loop, // TIM6_DAC_IRQHandler,       /*!< 54: TIM6 and DAC1&2 underrun errors         */
    loop, // TIM7_IRQHandler,           /*!< 55: TIM7                                    */
    loop, // DMA2_Stream0_IRQHandler,   /*!< 56: DMA2 Stream 0                           */
    loop, // DMA2_Stream1_IRQHandler,   /*!< 57: DMA2 Stream 1                           */
    loop, // DMA2_Stream2_IRQHandler,   /*!< 58: DMA2 Stream 2                           */
    loop, // DMA2_Stream3_IRQHandler,   /*!< 59: DMA2 Stream 3                           */
    loop, // DMA2_Stream4_IRQHandler,   /*!< 60: DMA2 Stream 4                           */
    loop, // ETH_IRQHandler,            /*!< 61: Ethernet                                */
    loop, // ETH_WKUP_IRQHandler,       /*!< 62: Ethernet Wakeup through EXTI line       */
    loop, // CAN2_TX_IRQHandler,        /*!< 63: CAN2 TX                                 */
    loop, // CAN2_RX0_IRQHandler,       /*!< 64: CAN2 RX0                                */
    loop, // CAN2_RX1_IRQHandler,       /*!< 65: CAN2 RX1                                */
    loop, // CAN2_SCE_IRQHandler,       /*!< 66: CAN2 SCE                                */
    loop, // OTG_FS_IRQHandler,         /*!< 67: USB OTG FS                              */
    loop, // DMA2_Stream5_IRQHandler,   /*!< 68: DMA2 Stream 5                           */
    loop, // DMA2_Stream6_IRQHandler,   /*!< 69: DMA2 Stream 6                           */
    loop, // DMA2_Stream7_IRQHandler,   /*!< 70: DMA2 Stream 7                           */
    loop, // USART6_IRQHandler,         /*!< 71: USART6                                  */
    loop, // I2C3_EV_IRQHandler,        /*!< 72: I2C3 event                              */
    loop, // I2C3_ER_IRQHandler,        /*!< 73: I2C3 error                              */
    loop, // OTG_HS_EP1_OUT_IRQHandler, /*!< 74: USB OTG HS End Point 1 Out              */
    loop, // OTG_HS_EP1_IN_IRQHandler,  /*!< 75: USB OTG HS End Point 1 In               */
    loop, // OTG_HS_WKUP_IRQHandler,    /*!< 76: USB OTG HS Wakeup through EXTI          */
    loop, // OTG_HS_IRQHandler,         /*!< 77: USB OTG HS                              */
    loop, // DCMI_IRQHandler,           /*!< 53: DCMI                                    */
    loop, // CRYP_IRQHandler,           /*!< 53: CRYP crypto                             */
    loop, // HASH_RNG_IRQHandler,       /*!< 53: Hash and Rng                            */
    loop, // FPU_IRQHandler             /*!< 53: FPU                                     */
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
