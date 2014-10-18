/*
 ===============================================================================
            ##### STM32L1-discovery board: USART1 communication#####
								c file
 ===============================================================================
 * @date    18-Oct-2014
 * @author  schperplata
 * 
 * initialize library with:	init_usart(USART1, GPIOA, 9600); 
 * usart_RXint_init(); currently unsuported. 
 * 8 data bits, 1 stop bit, no parity check, no hardware flow control, RX and TX always ON. 
 */

/* Includes ------------------------------------------------------------------*/
#include <stm32l1xx.h>
#include <string.h>

/* Initialize USART
* USARTx: USART1, USART2, USART3    
* GPIOx: where x can be (A..H) to select the GPIO peripheral.
* GPIO Pins:
Pins:   |USART1: (APB2)  |USART2(APB1)  |USART3(APB1)   |
TX:     |PA9,    PB6     |PA2           |PB10,  PC10    |TX
RX:     |PA10,   PB7     |PA3           |PB11,  PC11    |RX
* baud_rate: 9600, 19200, 38400, 57600, 115200 ... check docs.
*/
void init_usart(USART_TypeDef* USARTx, GPIO_TypeDef* GPIOx, uint32_t baud_rate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
        
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    
    if(USARTx == USART1){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
        if(GPIOx == GPIOA){
            RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
            
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
            GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 | GPIO_Pin_10;
        }
        else {
            if(GPIOx == GPIOB){
                RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
                
                GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
                GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
                GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
            }      
        }
    }
    else if(USARTx == USART2){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
        
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
        GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2 | GPIO_Pin_3;
    }
    else{
        if(USARTx == USART3){
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
            if(GPIOx == GPIOB){
                RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
             
                GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
                GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
                GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
            }
            else{
                if(GPIOx == GPIOC){
                    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
                    
                    GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
                    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);
                    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
                }      
            }
        }
    }
    
    /* Configure USARTx pins:  Rx and Tx ----------------------------*/
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOx, &GPIO_InitStructure);

	USART_StructInit(&USART_InitStructure); //fills usart struct with default values
    USART_InitStructure.USART_BaudRate = baud_rate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	    
    USART_Init(USARTx, &USART_InitStructure);
    //USART_OverSampling8Cmd(USART1, ENABLE);	//Use this if there is no clock correction function
	USART_Cmd(USARTx, ENABLE);
}

/*
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
  
    // Configure USART1 pins:  Rx and Tx ----------------------------
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
*/

/*
	Send/print character/string over USART1. 
	Printable data for viewing on terminal.
	Call this function:		printString(USART1, "data");
	Data must be string.
*/
void printString(USART_TypeDef* USARTx, char *data)	
{
	uint16_t i;
	uint16_t str_length = strlen(data);
	for(i = 0; i < str_length; i++)
	{
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);	//wait for cleared flag
		USART_SendData(USARTx, data[i]);
	}
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);	//wait for cleared flag
}

/*
	This is "private" function. It is used by other functions like: printNumber(int32_t number, uint8_t base). 
	However, it can be used by user.
	Send/print unsigned number over USART1. 
	Printable data for viewing on terminal.
	Call this function:		printUnsignedNumber(number, DEC);		printUnsignedNumber(USART1, 2246, DEC);	
	Base: DEC, HEX, OCT, BIN
	Data must be number, int32_t.
*/
void printUnsignedNumber(USART_TypeDef* USARTx, uint32_t n, uint8_t base)	
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

	printString(USARTx, str); 
}

/*
	Send/print new line and carriage return over USART1.
	Printable data for viewing on terminal.
	Call this function:		printLn(USART1);
*/
void printLn(USART_TypeDef* USARTx)	
{
	printString(USARTx, "\n\r");
}

/*
	Send/print unsigned or signed number over USART1. 
	Printable data for viewing on terminal.
	Call this function:		printNumber(USART1, number, DEC);		printNumber(USART1, 2246, DEC);	
	Base: DEC, HEX, OCT, BIN
	Data must be number, int32_t.
*/
void printNumber(USART_TypeDef* USARTx, int32_t number, uint8_t base)	
{
	if (number < 0) 
	{
		printString(USARTx, "-");
		number = -number;
		printUnsignedNumber(USARTx, number, base);
	}
	else 
	{
		printUnsignedNumber(USARTx,number, base);
	}
}

/*
	Send/print character/string over USART1, add new line and carriage return at the end of function. 
	Printable data for viewing on terminal.
	Call this function:		printStringLn(USART1, "data");
	Data must be string.
*/
void printStringLn(USART_TypeDef* USARTx, char *data)	//send string overserial port USART1.
{
	uint16_t i;
	uint16_t str_length = strlen(data);
	for(i = 0; i < str_length; i++)
	{
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);	//wait for cleared flag
		USART_SendData(USARTx, data[i]);
	}
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);	//wait for cleared flag
	printLn(USARTx);
}

/*
	Send/print unsigned or signed number over USART1, add new line and carriage return at the end of function.  
	Printable data for viewing on terminal.
	Call this function:		printNumberLn(USART1, number, DEC);		printNumberLn(USART1, 2246, DEC);	
	Base: DEC, HEX, OCT, BIN
	Data must be number, int32_t.
*/
void printNumberLn(USART_TypeDef* USARTx, int32_t number, uint8_t base)	//send SINGED/UNSIGNED number over serial port USART1.
{
	if (number < 0) 
	{
		printString(USARTx, "-");
		number = -number;
		printUnsignedNumber(USARTx, number, base);
	}
	else 
	{
		printUnsignedNumber(USARTx, number, base);
	}
	printLn(USARTx);
}

/*
	Send raw data over USART1. 
	Not "printable" data.
	Call this function:		writeData(USARTx, &data, sizeof(data));
	Data can be any type.
*/
void writeData(USART_TypeDef* USARTx, void *data, uint8_t dataSize)	
{
  uint8_t i, d;
  
  d = dataSize/2;
 
  for(i = 0; i < d; i++)
  {
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);	//wait for cleared flag
	USART_SendData(USARTx, *( ((uint16_t *)data) + i ) );
  }
  
  while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);	//wait for cleared flag
}
