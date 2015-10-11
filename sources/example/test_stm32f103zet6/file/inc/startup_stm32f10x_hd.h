#ifndef STARTUP_H
#define STARTUP_H

#define STACK_TOP 0x2000FFFF
#define ISR_VECTOR __attribute__ ((section(".isr_vector")))
#define DATA_FLASH __attribute__ ((section(".data_flash")))

typedef void (*POINTER_ITERRAPT)(void);

/*----------Declaration of the default fault handlers-------------------------*/
void loop(void);
/* System exception vector handler */
void Reset_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void WWDG_IRQHandler(void);
void PVD_IRQHandler(void);
void RTC_IRQHandler(void);
void FLASH_IRQHandler(void);
void RCC_IRQHandler(void);
void EXTI0_1_IRQHandler(void);
void EXTI2_3_IRQHandler(void);
void EXTI4_15_IRQHandler(void);
void TS_IRQHandler(void);
void DMA1_Channel1_IRQHandler(void);
void DMA1_Channel2_3_IRQHandler(void);
void DMA1_Channel4_5_IRQHandler(void);
void ADC1_COMP_IRQHandler(void);
void TIM1_BRK_UP_TRG_COM_IRQHandler(void);
void TIM1_CC_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM6_DAC_IRQHandler(void);
void TIM14_IRQHandler(void);
void TIM15_IRQHandler(void);
void TIM16_IRQHandler(void);
void TIM17_IRQHandler(void);
void I2C1_IRQHandler(void);
void I2C2_IRQHandler(void);
void SPI1_IRQHandler(void);
void SPI2_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void CEC_IRQHandler(void);
void BootRAM(void);

extern const ISR_VECTOR POINTER_ITERRAPT ArrayInterrapt[];

extern void *_start_rodata_copi, *_start_rodata, *_end_rodata,
                *_start_data_copi, *_start_data, *_end_data,
                *_start_bss_copi, *_start_bss, *_end_bss, *_size_bss;

#endif // STARTUP_H

