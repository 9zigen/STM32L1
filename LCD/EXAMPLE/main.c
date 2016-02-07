/**
  ******************************************************************************
  * @file    lcd test
  * @author  Domen Jurkovic
  * @version V1
  * @date    3-Feb-2016
  * @brief   Main program body
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

int main(void)
{
	//small Damogran Labs logo
	//xxx - doesn't care;
	uint8_t custom_char[] = {
        0x00,	   // xxx 00000
        0x0F,
        0x13,
        0x11,
        0x11,
        0x0E,
        0x00,
        0x00 
    };
	RCC_ClocksTypeDef RCC_Clocks;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	systick_millis_init();	
	UART_Init(); 
	
	//LEDS
	gpio_pinSetup(GPIOC, GPIO_Pin_9, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_40MHz);
	GPIO_WriteBit(GPIOC, GPIO_Pin_9, Bit_SET);
	
	printLn();
	printStringLn("------------------------------------------------");
	printStringLn("System initialized. Initialized jebote!");
		
	RCC_GetClocksFreq(&RCC_Clocks);
	printString("SYSCLK_Frequency: ");
	printNumberLn(RCC_Clocks.SYSCLK_Frequency, DEC); 
	printStringLn("------------------------------------------------");
	
	//Initialize LCD
	LCD_Init(2, 20);
	
	//Put string to LCD
	LCD_PrintString(0, 0, "DamogranLabs STM32L1");
	
	LCD_PrintString(1, 0, "F:");
	LCD_PrintFloat(1, 2, 12.0753);
	
	LCD_PrintString(1, 12, "N:");
	LCD_PrintFloat(1, 14, 123456);
	
	LCD_CreateChar(0, custom_char);
	LCD_PutCustom(1,10, 0);
	
	while (1)
  {
		GPIO_ToggleBits(GPIOC, GPIO_Pin_9);
		delay(1000);
  }
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
