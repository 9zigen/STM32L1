/*
	UART1
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


////print WITHOUT new line and carriage return
//void printString(char *data);	//send/print string overserial port USART1.
//void printNumber(int32_t number, uint8_t base);	//send/print SINGED/UNSIGNED int32_t number over serial port USART1.

////print WITH new line and carriage return
//void printStringLn(char *data);	//send/print string overserial port USART1.
//void printNumberLn(int32_t number, uint8_t base);	//send/print SINGED/UNSIGNED number over serial port USART1.
//void printLn(void);	//print new line and carriage return

////send raw data, any type.
//void writeData(void *data, uint8_t dataSize);
void usart_init()
{
	USART_InitTypeDef USART_InitStructure;
	
	USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	    
    USART_Init(USART1, &USART_InitStructure);
    USART_OverSampling8Cmd(USART1, ENABLE); //?!?
	USART_Cmd(USART1, ENABLE);
}

void gpio_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
  
    /* Configure USART1 pins:  Rx and Tx ----------------------------*/
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


int main(void)
{
	uint16_t bla = 0;
	char testni_niz_znakov[10] = "majkemi ti";
		
	gpio_init();
	usart_init();
	
	
    while(1)
    {
              
		while( bla != 'x')
		{
			while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)	//wait for cleared flag
			{
				bla = USART_ReceiveData(USART1);
			}
        }
		
		
		if(bla == 'x')
		{

			printStringLn("gnoj na kubik");
			printStringLn(testni_niz_znakov);
			printNumberLn(2246, DEC);			
			printNumber(-1345, DEC);
			printNumber(bla, DEC);
			printLn();
			
			
		}
		
        bla = '0';
		    
    }
}


