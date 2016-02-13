/**
  ******************************************************************************
  * @author  Domen Jurkovic
  * @version V1
  * @date    3-Feb-2016
  * @brief   Main program body
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"


void timer7_us_init(void){
	TIM_TimeBaseInitTypeDef tim_base_init_structure;
			
	// TIM7 clock enable 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	
	tim_base_init_structure.TIM_Prescaler = 0;
	tim_base_init_structure.TIM_CounterMode = TIM_CounterMode_Up;
	tim_base_init_structure.TIM_Period = 0xFFFF;
	tim_base_init_structure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM7, &tim_base_init_structure);
}

int main(void)
{
  uint32_t stop_time;
	uint32_t start_time;
	
	RCC_ClocksTypeDef RCC_Clocks;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	systick_millis_init();	
	UART_Init(); 
	
	timer7_us_init();
	delay_us_init();	
	
	
	//LEDS
	gpio_pinSetup(GPIOC, GPIO_Pin_8, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_40MHz);
	GPIO_WriteBit(GPIOC, GPIO_Pin_8, Bit_SET);
	
	//CLOCK OUTPUT PA8
	gpio_pinSetup_AF(GPIOA, GPIO_Pin_8, GPIO_AF_MCO, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_40MHz);
	RCC_MCOConfig(RCC_MCOSource_SYSCLK, RCC_MCODiv_1);
	
	
	printLn();
	printStringLn("------------------------------------------------");
	printStringLn("System initialized.");
		
	RCC_GetClocksFreq(&RCC_Clocks);
	printString("SYSCLK_Frequency: ");
	printNumberLn(RCC_Clocks.SYSCLK_Frequency, DEC); 

	printString("HCLK_Frequency: ");
	printNumberLn(RCC_Clocks.HCLK_Frequency, DEC); 
	
	printString("PCLK1_Frequency: ");
	printNumberLn(RCC_Clocks.PCLK1_Frequency, DEC); 
	
	printString("PCLK2_Frequency: ");
	printNumberLn(RCC_Clocks.PCLK2_Frequency, DEC); 
	
	printString("SYSCLKSource: ");
	printNumberLn(RCC_GetSYSCLKSource(), DEC);
	
	printString("PRESCALER TIM2: ");
	printNumberLn(TIM_GetPrescaler(TIM3), DEC);
	printStringLn("------------------------------------------------");
	
	while (1)
  {
		GPIO_ToggleBits(GPIOC, GPIO_Pin_8);
	
		TIM_SetCounter(TIM7, 0);
		TIM_Cmd(TIM7, ENABLE);
		start_time = TIM_GetCounter(TIM7);
		
		delay_us(25);
	
		stop_time = TIM_GetCounter(TIM7);
		TIM_Cmd(TIM7, DISABLE);
		printNumberLn(stop_time - start_time, DEC);
		
		delay(100);
		printNumberLn(millis(), DEC);
  }
}


