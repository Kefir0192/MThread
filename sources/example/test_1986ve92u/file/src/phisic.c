﻿#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"

/*
 * ЗАПОМНИ ! Сначала нужно включить тактирование модуля, а уж потом его инициализировать и так всегда !
 * */

/*
================================================================//
=================           WDG             ====================//
================================================================//
*/


/*
================================================================//
=================           PORT            ====================//
================================================================//
*/

//--------------------------------------------------------------//
// Инициализация PORT
//--------------------------------------------------------------//
void Port_Init(void)
{
    // ЗАПОМНИ ! Сначала нужно включить тактирование модуля, а уж потом его инициализировать и так всегда !
    // включаем тактирование порта A, B, C, D
    MDR_RST_CLK->PER_CLOCK	|= BIT29 | BIT21 | BIT22 | BIT23 | BIT24 | BIT25;

    // 00 – зарезервировано (передатчик отключен) !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    MDR_PORTA->PWR 			= 0xffff;               // 11 – максимально быстрый фронт (порядка 10 нс)
    MDR_PORTC->PWR 			= 0xffff;               // 11 – максимально быстрый фронт (порядка 10 нс)
    MDR_PORTD->PWR 			= 0xffff;               // 11 – максимально быстрый фронт (порядка 10 нс)
    MDR_PORTE->PWR 			= 0xffff;               // 11 – максимально быстрый фронт (порядка 10 нс)

    //
    // TEST_PIN_PE6_ON
    //////////////////////////////////////////////////////////////////
    MDR_PORTE->OE			|= BIT6;                // 1 – выход
    MDR_PORTE->ANALOG		|= BIT6;                // 1 – цифровой
    MDR_PORTE->RXTX         |= BIT6;                // Данные для выдачи на выводы порта

    //
    // TEST_PIN_PE6_ON
    //////////////////////////////////////////////////////////////////
    MDR_PORTE->OE			|= BIT7;                // 1 – выход
    MDR_PORTE->ANALOG		|= BIT7;                // 1 – цифровой
    MDR_PORTE->RXTX         |= BIT7;                // Данные для выдачи на выводы порта

    MDR_PORTC->OE			|= BIT1;                // 1 – выход
    MDR_PORTC->ANALOG		|= BIT1;                // 1 – цифровой
    MDR_PORTC->RXTX         |= BIT1;                // Данные для выдачи на выводы порта
}

/*
================================================================//
=================           TIMER           ====================//
================================================================//
*/

/*
================================================================//
=================        SPI_Slave_ap       ====================//
================================================================//
*/

/*
================================================================//
=================            I2C            ====================//
================================================================//
*/

