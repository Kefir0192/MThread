#ifndef STARTUP_1986VE92_H
#define STARTUP_1986VE92_H

#define STACK_TOP 0x20008000
#define ISR_VECTOR __attribute__ ((section(".isr_vector")))

typedef void (*POINTER_ITERRAPT)(void);

/*----------Declaration of the default fault handlers-------------------------*/
void loop(void);
/* System exception vector handler */
void Reset_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void CAN1_IRQHandler(void);
void CAN2_IRQHandler(void);
void USB_IRQHandler(void);
void DMA_IRQHandler(void);
void UART1_IRQHandler(void);
void UART2_IRQHandler(void);
void SSP1_IRQHandler(void);
void I2C_IRQHandler(void);
void POWER_IRQHandler(void);
void WWDG_IRQHandler(void);
void Timer1_IRQHandler(void);
void Timer2_IRQHandler(void);
void Timer3_IRQHandler(void);
void ADC_IRQHandler(void);
void COMPARATOR_IRQHandler(void);
void SSP2_IRQHandler(void);
void BACKUP_IRQHandler(void);
void EXT_INT1_IRQHandler(void);
void EXT_INT2_IRQHandler(void);
void EXT_INT3_IRQHandler(void);
void EXT_INT4_IRQHandler(void);

extern const ISR_VECTOR POINTER_ITERRAPT ArrayInterrapt[];

extern void *_start_rodata_copi, *_start_rodata, *_end_rodata,
            *_start_data_copi, *_start_data, *_end_data,
            *_start_bss_copi, *_start_bss, *_end_bss, *_size_bss;

#endif // STARTUP_1986VE92_H

