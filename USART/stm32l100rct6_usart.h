 /*
 ===============================================================================
            ##### STM32L1-discovery board: USART1 communication #####
								header file
 ===============================================================================
 * @date    18-Oct-2014
 * @author  schperplata
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L100RCT6_USART_H
#define __STM32L100RCT6_USART_H

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

// Initialize USART
void init_usart(USART_TypeDef* USARTx, GPIO_TypeDef* GPIOx, uint32_t baud_rate); 
	 
// Initialize USART1 with receive interrupt
//void usart1_RXint_init(void);
	
//print WITHOUT new line and carriage return
void printString(USART_TypeDef* USARTx, char *data);	//send/print string overserial port USART1.
void printNumber(USART_TypeDef* USARTx, int32_t number, uint8_t base);	//send/print SINGED/UNSIGNED int32_t number over serial port USART1.

//print WITH new line and carriage return
void printStringLn(USART_TypeDef* USARTx, char *data);	//send/print string overserial port USART1.
void printNumberLn(USART_TypeDef* USARTx, int32_t number, uint8_t base);	//send/print SINGED/UNSIGNED number over serial port USART1.
void printLn(USART_TypeDef* USARTx);	//print new line and carriage return

//send raw data, any type.
void writeData(USART_TypeDef* USARTx, void *data, uint8_t dataSize);

//"private" function. Can be used if needed.
void printUnsignedNumber(USART_TypeDef* USARTx, uint32_t n, uint8_t base);	//send/print UNSIGNED uint32_t over serial port USART1.

#ifdef __cplusplus
}
#endif

#endif /* __STM32L100RCT6_USART_H */
