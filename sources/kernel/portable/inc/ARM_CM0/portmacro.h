#ifndef MTHREAD_PORT
#define MTHREAD_PORT



#include "globalincludefile.h"



// Системные макросы
//------------------------------------------------------
#define PORT_ASM_NOP()      {  __ASM("nop");        }



// Минимальный размер стека в словах (слово - 4 байта)
//------------------------------------------------------
#define PORT_MINIMUM_SIZE_STACK_WORD    16
// Делитель системного таймера
//------------------------------------------------------
#define PORT_DIVIDER_SYSTEM_TIMER       80000
// Атомарное сохранение
//------------------------------------------------------
#define PORT_ATOMIC_SAVE(a, b)          { a = b; }
// Прерывание системного таймера
//------------------------------------------------------
#define PORT_SYS_TICK_HANDLER   SysTick_Handler
// Прерывание сохранение/восстановление контекста
//------------------------------------------------------
#define PORT_SCHEDULE_HANDLER   PendSV_Handler



// Прерывание системного таймера
//------------------------------------------------------
void PORT_SYS_TICK_HANDLER(void);
// Прерывание сохранение/восстановление контекста
//------------------------------------------------------
void PORT_SCHEDULE_HANDLER(void);
// Инициализация стека задачи
//------------------------------------------------------
uint32_t* port_Initialise_Stack(void (*pTack)(void *pVoid), uint32_t *pStack, uint32_t Size_Stack, void *pParameters);
// Запустить шедулер
//------------------------------------------------------
void port_Start_Schedule(uint32_t* pStack);
// Программное прерывание Schedule
//------------------------------------------------------
void port_Inquiry_Interruption(void);
// Сброс системного таймера
//------------------------------------------------------
void port_Reset_SysTick(void);


uint8_t port_atomic_exchange(uint8_t *pCurrent, uint8_t updated);

// Начало критической секции обеспечивающая атомарность
//------------------------------------------------------
void port_Start_Critical_Section_Mutex(void);
// Конец критической секции обеспечивающая атомарность
//------------------------------------------------------
void port_End_Critical_Section_Mutex(void);



#endif // MTHREAD_PORT

