/**
  ******************************************************************************
  * @file    UART, RX INTERRUPT UART test
  * @author  Domen Jurkovic
  * @version V1
  * @date    6-Feb-2016
  * @brief   Main program body
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

int main(void)
{
	RCC_ClocksTypeDef RCC_Clocks;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	systick_millis_init();	
	UART_Init(); 
	
	//LED
	gpio_pinSetup(GPIOC, GPIO_Pin_9, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_40MHz);
	GPIO_WriteBit(GPIOC, GPIO_Pin_9, Bit_SET);
	
	printLn();
	printStringLn("------------------------------------------------");
	printStringLn("System initialized.");
		
	RCC_GetClocksFreq(&RCC_Clocks);
	printString("SYSCLK_Frequency: ");
	printNumberLn(RCC_Clocks.SYSCLK_Frequency, DEC); 
	printString("Is your clock: ");
	printFloat(32.0000);
	printStringLn("MHz???");
	
	while (1)
  {
		GPIO_ToggleBits(GPIOC, GPIO_Pin_9);
		printNumberLn(millis()/1000, DEC); 
		delay(1000);
		
  }
}

void USART1_IRQHandler(){
	while(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){			// Received characters added to fifo
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		
		// Receive the character
		if(USART_ReceiveData(USART1) == 'x'){			
			printStringLn("uart in interrupt");    
		} 
	}
}

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
