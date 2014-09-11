/*
 ===============================================================================
            ##### STM32L1-discovery board: USART1 communication#####
								c file
 ===============================================================================
 * @date    2-March-2014
 * @author  schperplata
 
 * initialize library with:	usart1_init(); usart1_RXint_init(); 
 
 */

/* Includes ------------------------------------------------------------------*/
#include <stm32l1xx.h>
#include <string.h>

// Initialize USART1
void usart1_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
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

	USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	    
    USART_Init(USART1, &USART_InitStructure);
    //USART_OverSampling8Cmd(USART1, ENABLE);	//Use this if there is no clock correction function
	USART_Cmd(USART1, ENABLE);
}

// Initialize USART1 with receive interrupt
void usart1_RXint_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
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

	USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//enable USART1 interrupt - Receive Data register not empty interrupt.
	
	//USART_OverSampling8Cmd(USART1, ENABLE);	//Use this if there is no clock correction function
	USART_Cmd(USART1, ENABLE);
}

/*
	Send/print character/string over USART1. 
	Printable data for viewing on terminal.
	Call this function:		printString("data");
	Data must be string.
*/
void printString(char *data)	
{
	uint16_t i;
	uint16_t str_length = strlen(data);
	for(i = 0; i < str_length; i++)
	{
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	//wait for cleared flag
		USART_SendData(USART1, data[i]);
	}
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	//wait for cleared flag
}

/*
	This is "private" function. It is used by other functions like: printNumber(int32_t number, uint8_t base). 
	However, it can be used by user.
	Send/print unsigned number over USART1. 
	Printable data for viewing on terminal.
	Call this function:		printUnsignedNumber(number, DEC);		printUnsignedNumber(2246, DEC);	
	Base: DEC, HEX, OCT, BIN
	Data must be number, int32_t.
*/
void printUnsignedNumber(uint32_t n, uint8_t base)	
{
	char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
    char *str = &buf[sizeof(buf) - 1];
	unsigned long m;
	char c;
  *str = '\0';

  //prevent crash if called with base == 1
  if (base < 2) base = 10;

  do 
	{
    m = n;
    n /= base;
    c = m - base * n;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
	} while(n);

	printString(str); 
}

/*
	Send/print new line and carriage return over USART1.
	Printable data for viewing on terminal.
	Call this function:		printLn();
*/
void printLn(void)	
{
	printString("\n\r");
}

/*
	Send/print unsigned or signed number over USART1. 
	Printable data for viewing on terminal.
	Call this function:		printNumber(number, DEC);		printNumber(2246, DEC);	
	Base: DEC, HEX, OCT, BIN
	Data must be number, int32_t.
*/
void printNumber(int32_t number, uint8_t base)	
{
	if (number < 0) 
	{
		printString("-");
		number = -number;
		printUnsignedNumber(number, base);
	}
	else 
	{
		printUnsignedNumber(number, base);
	}
}

/*
	Send/print character/string over USART1, add new line and carriage return at the end of function. 
	Printable data for viewing on terminal.
	Call this function:		printStringLn("data");
	Data must be string.
*/
void printStringLn(char *data)	//send string overserial port USART1.
{
	uint16_t i;
	uint16_t str_length = strlen(data);
	for(i = 0; i < str_length; i++)
	{
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	//wait for cleared flag
		USART_SendData(USART1, data[i]);
	}
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	//wait for cleared flag
	printLn();
}

/*
	Send/print unsigned or signed number over USART1, add new line and carriage return at the end of function.  
	Printable data for viewing on terminal.
	Call this function:		printNumberLn(number, DEC);		printNumberLn(2246, DEC);	
	Base: DEC, HEX, OCT, BIN
	Data must be number, int32_t.
*/
void printNumberLn(int32_t number, uint8_t base)	//send SINGED/UNSIGNED number over serial port USART1.
{
	if (number < 0) 
	{
		printString("-");
		number = -number;
		printUnsignedNumber(number, base);
	}
	else 
	{
		printUnsignedNumber(number, base);
	}
	printLn();
}

/*
	Send raw data over USART1. 
	Not "printable" data.
	Call this function:		writeData(&data, sizeof(data));
	Data can be any type.
*/
void writeData(void *data, uint8_t dataSize)	
{
  uint8_t i, d;
  
  d = dataSize/2;
 
  for(i = 0; i < d; i++)
  {
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	//wait for cleared flag
	USART_SendData(USART1, *( ((uint16_t *)data) + i ) );
  }
  
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	//wait for cleared flag
}
