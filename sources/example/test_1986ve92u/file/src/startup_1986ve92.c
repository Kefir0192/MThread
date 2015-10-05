#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"



const ISR_VECTOR POINTER_ITERRAPT ArrayInterrapt[] = {
    /*----------Core Exceptions------------------------------------------------ */
    //NMI_Handler,
    (POINTER_ITERRAPT)STACK_TOP,    /*!< The initial stack pointer              */
    Reset_Handler,                  /*!< Reset Handler                          */
    loop, //NMI_Handler,            /*!< NMI Handler                            */
    loop, //HardFault_Handler,      /*!< Hard Fault Handler                     */
    loop, //MemManage_Handler,      /*!< MPU Fault Handler                      */
    loop, //BusFault_Handler,       /*!< Bus Fault Handler                      */
    loop, //UsageFault_Handler,     /*!< Usage Fault Handler                    */
    0,0,0,0,                        /*!< Reserved                               */
    loop, //SVC_Handler,            /*!< SVCall Handler                         */
    loop, //DebugMon_Handler,       /*!< Debug Monitor Handler                  */
    0,                              /*!< Reserved                               */
    PendSV_Handler,         /*!< PendSV Handler                         */
    SysTick_Handler,        /*!< SysTick Handler                        */

    /*----------External Exceptions---------------------------------------------*/

    loop, //CAN1_IRQHandler,
    loop, //CAN2_IRQHandler,
    loop, //USB_IRQHandler,
    0,0,
    loop, //DMA_IRQHandler,
    loop, //UART1_IRQHandler,
    loop, //UART2_IRQHandler,
    loop, //SSP1_IRQHandler,
    0,
    loop, //I2C_IRQHandler,
    loop, //POWER_IRQHandler,
    loop, //WWDG_IRQHandler,
    0,
    loop, //Timer1_IRQHandler,
    loop, //Timer2_IRQHandler,
    loop, //Timer3_IRQHandler,
    loop, //ADC_IRQHandler,
    0,
    loop, //COMPARATOR_IRQHandler,
    loop, //SSP2_IRQHandler,
    0,0,0,0,0,0,
    loop, //BACKUP_IRQHandler,
    loop, //EXT_INT1_IRQHandler,
    loop, //EXT_INT2_IRQHandler,
    loop, //EXT_INT3_IRQHandler,
    loop, //EXT_INT4_IRQHandler
};

// Функция заглушка
__attribute__ ((section(".loop")))
void loop(void)
{
    while(1);
}

// .rodata — глобальные и статические переменные;
// .data — глобальные и статические переменные;
void ro_data_init(void *pStartOUT, void *pStartIN, void *pEndIN)
{
    while(pStartIN != pEndIN)
        *((uint8_t *)pStartIN++) = *((uint8_t *)pStartOUT++);
}

// .bss — глобальные и статические переменные, которые при старте содержат нулевое значение.
void bss_init(void *pStartIN, void *pEndIN)
{
    void *p = 0x00;
    while(p++ != pEndIN)
        *((uint8_t *)pStartIN++) = 0x00;
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
