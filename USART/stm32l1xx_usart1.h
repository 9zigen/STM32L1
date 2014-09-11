 /*
 ===============================================================================
            ##### STM32L1-discovery board: USART1 communication #####
								                  header file
 ===============================================================================
 * @date    2-March-2014
 * @author  schperplata
 *
 * Added Arduino-like functions to print numbersand strings to USART1
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L1xx_USART1_H
#define __STM32L1xx_USART1_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stm32l1xx.h>
#include <string.h>

//uint8_t base:
#define	DEC	10
#define BIN 2
#define HEX 16
#define OCT 8

// Initialize USART1
void usart1_init(void); 
	 
// Initialize USART1 with receive interrupt
void usart1_RXint_init(void);
	
//print WITHOUT new line and carriage return
void printString(char *data);	//send/print string overserial port USART1.
void printNumber(int32_t number, uint8_t base);	//send/print SINGED/UNSIGNED int32_t number over serial port USART1.

//print WITH new line and carriage return
void printStringLn(char *data);	//send/print string overserial port USART1.
void printNumberLn(int32_t number, uint8_t base);	//send/print SINGED/UNSIGNED number over serial port USART1.
void printLn(void);	//print new line and carriage return

//send raw data, any type.
void writeData(void *data, uint8_t dataSize);

//"private" function. Can be used if needed.
void printUnsignedNumber(uint32_t n, uint8_t base);	//send/print UNSIGNED uint32_t over serial port USART1.

#ifdef __cplusplus
}
#endif

#endif /* __STM32L1xx_USART1_H */
