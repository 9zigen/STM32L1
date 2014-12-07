 /*
 ===============================================================================
				##### STM32L1-discovery board: millis #####
								c file
	timer_millis: STM32L1 family
	USING TIM2 - basic 16 bit timer
 ===============================================================================
 * @date    24-November-2014
 * @author  Domen Jurkovic
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L1xx_MILLIS_H
#define __STM32L1xx_MILLIS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stm32l1xx.h>
#include <stm32l1xx_rcc.h>
#include <stm32l1xx_tim.h>
#include <misc.h>
	 
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

#define INCREMENT_RESOLUTION	1	//in microseconds [us]. Timer increments every INCREMENT_RESOLUTION us

// "private" function. Timer 2 initialization.
void timer2_millis_init(void);

// "private" function. Timer 2 interrupt.
void EnableTimerInterrupt(void);
// ------------------------------------------------------------------------

// Return milliseconds from timer initialization or timer reset
uint32_t millis(void);

// Return microseconds from timer initialization or timer reset
uint32_t micros(void);

// Wait in this function for specific amount of time.
// param: uint32_t [milliseconds]
// #define DELAY_US_PRECISION for microsecond resolution. 
//		NOTE: There is no compensation for time that code and other system calls consume!
void delay(uint32_t ms);

// Wait in this function for specific amount of time. Resolution is INCREMENT_RESOLUTION. param = unsigned long [microseconds]
// param: unsigned long [microseconds], multiplier of INCREMENT_RESOLUTION
void delayMicroseconds(uint32_t us);

// Restart timer to 0. Doesn't STOP timer. 
void restartMillis(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32L1xx_MILLIS_H */
