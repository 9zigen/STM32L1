 /*
 ===============================================================================
											##### print numbers and strings #####
																	header file
 ===============================================================================
 * @date    1-Feb-2016
 * @author  Domen Jurkovic
 
 * this is template file - include it in your file and modify 
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L1XX_UART_PRINT_H
#define __STM32L1XX_UART_PRINT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx.h"
#include "stdbool.h"
#include "stdint.h"
#include "string.h"	
#include "math.h"

#include "stm32l1xx_gpio_init.h"
	 
//uint8_t base:
#define	DEC	10
#define BIN 2
#define HEX 16
#define OCT 8

/****************************************************************************************/
/* COMMUNICATION FUNCTIONS - change in .c file accordingly to your HW */
/****************************************************************************************/
// initialize UART
void UART_Init(void);
/*
If RX interrupt is used, call 
void USARTx_IRQHandler(){
	while(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET){			// Received characters added to fifo
		USART_ClearITPendingBit(USARTx, USART_IT_RXNE);
		received_data = USART_ReceiveData(USART1); // Receive the character
	}
}
*/

uint32_t _send_byte(uint8_t byte);
uint8_t _receive_byte(void);

/****************************************************************************************/
/* PRINT/WRITE FUNCTIONS */
/****************************************************************************************/
//print WITHOUT new line and carriage return
void printString(char *data);	//send/print string overserial.
void printNumber(int32_t number, uint8_t base);	//send/print SINGED/UNSIGNED int32_t number

//print WITH new line and carriage return
void printStringLn(char *data);	//send/print string.
void printNumberLn(int32_t number, uint8_t base);	//send/print SINGED/UNSIGNED number.
void printLn(void);	//print new line and carriage return

//send raw data, any type.
void writeData(void *data, uint8_t dataSize);

//"private" function. Can be used if needed.
void printUnsignedNumber(uint32_t n, uint8_t base);	//send/print UNSIGNED uint32_t.

void printFloat(float number);
void printFloatLn(float number);


#ifdef __cplusplus
}
#endif

#endif 
