/*
	UART1
	PA9 - USART1_TX
	PA10 - USART1_RX
*/ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stm32l1xx_rcc.h>
#include <stm32l1xx_gpio.h>
#include <stm32l1xx_usart.h>
#include <stdio.h>
#include <string.h>
//#include "stdlib.h"

#include <stm32l1xx_usart1.h>

//print WITHOUT new line and carriage return
//void printString(char *data);	//send/print string overserial port USART1.
//void printNumber(int32_t number, uint8_t base);	//send/print SINGED/UNSIGNED int32_t number over serial port USART1.

////print WITH new line and carriage return
//void printStringLn(char *data);	//send/print string overserial port USART1.
//void printNumberLn(int32_t number, uint8_t base);	//send/print SINGED/UNSIGNED number over serial port USART1.
//void printLn(void);	//print new line and carriage return

////send raw data, any type.
//void writeData(void *data, uint8_t dataSize);

int main(void)
{
	uint16_t character = 0;
	char test_string[19] = "This is some text.";
	
	clockCorrection();	// see main folder
	usart1_init();		
	
    while(1)
    {
              
		while( bla != 'x')
		{
			while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)	//wait for cleared flag
			{
				character = USART_ReceiveData(USART1);
			}
        }

		if(character == 'x')
		{
			printStringLn("x received!");
			printStringLn(test_string);
			printNumberLn(2246, DEC);			
			printNumber(-1345, DEC);
			printNumber(bla, DEC);
			printLn();
		}
	    character = '0';

    }
}
