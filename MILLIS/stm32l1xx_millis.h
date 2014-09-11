/*
 ===============================================================================
                ##### STM32L1-discovery board: millis #####
								                  c file
	timer_millis: STM32L1 family
	USING TIM2 - basic 16 bit timer
 ===============================================================================
 * @date    13-August-2014
 * @author  schperplata
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L1xx_MILLIS_H
#define __STM32L1xx_MILLIS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stm32l1xx.h>

/*
	This library depends on system clock. To calculate system clock use smt32l1xx_rcc.c library. 
	
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);
	printString("SYSCLK_Frequency: ");	printNumberLn(RCC_Clocks.SYSCLK_Frequency, DEC); 
	printString("HCLK_Frequency: ");	printNumberLn(RCC_Clocks.HCLK_Frequency, DEC); 
	printString("PCLK1_Frequency: ");	printNumberLn(RCC_Clocks.PCLK1_Frequency, DEC); 
	printString("PCLK2_Frequency: ");	printNumberLn(RCC_Clocks.PCLK2_Frequency, DEC); 
	printString("SYSCLKSource: ");		printNumberLn(RCC_GetSYSCLKSource(), DEC);
*/

#define F_TIMER 	32	  //change to system frequency
#define RESOLUTION	20	//in microseconds [us]. Timer increments every RESOLUTION us

#define PERIODE		(1000 / RESOLUTION)	// in 1ms there is PERIODE of clock cycles
#define PRESCALER	((F_TIMER * 1000)/(PERIODE + 1))	// Every PRESCALER clock cycle, timer is incremented

// ------------------------------------------------------------------------
// Timer 2 initialization.
void timer2_millis_init(void);

// "private" function. Timer 2 interrupt.
void EnableTimerInterrupt(void);
// ------------------------------------------------------------------------

// Return milliseconds from timer initialization or timer reset
unsigned long millis(void);

// Return microseconds from timer initialization or timer reset
unsigned long micros(void);

// Wait in this function for specific amount of time. Resolution is RESOLUTION. 
// param: unsigned long [milliseconds], multiplier of RESOLUTION
void delay(unsigned long ms);

// Wait in this function for specific amount of time. Resolution is RESOLUTION. param = unsigned long [microseconds]
// param: unsigned long [microseconds], multiplier of RESOLUTION
void delayMicroseconds(unsigned long us);

// Restart timer to 0. Doesn't STOP timer. 
void restartMillis(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32L1xx_USART1_H */
