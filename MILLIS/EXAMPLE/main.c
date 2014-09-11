/*
	timer2_millis test: STM32L1 family
	USING TIM2 - basic 16 bit timer
	check: stm32l1xx_millis.c
	
	initialize library with:	timer2_millis_init();
*/ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l1xx_conf.h" //insert includes

void gpio_init(void);
void clockCorrection(void);

//STM32L100RCT6-Discovery - clock correction function - SYSCLK = 32MHz, HSI. 
void clockCorrection()
{
	RCC_DeInit();
	RCC_HSICmd(ENABLE);
	
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) != SET)	// Wait until HSI is ready
	{
  }
	 
	FLASH->ACR |= FLASH_ACR_ACC64;		// Enable 64-bit access 
    FLASH->ACR |= FLASH_ACR_PRFTEN;		// Enable Prefetch Buffer 
	FLASH->ACR |= FLASH_ACR_LATENCY;	// Flash 1 wait state 
    
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;	// Power enable
  PWR->CR = PWR_CR_VOS_0;				// Select the Voltage Range 1 (1.8 V) 
  while((PWR->CSR & PWR_CSR_VOSF) != RESET) // Wait until the Voltage Regulator is ready 
  {
  }
	  
	RCC_PLLConfig(RCC_PLLSource_HSI, RCC_PLLMul_4, RCC_PLLDiv_2);	// HSI = 16MHz; 16MHz * 4 / 2 = 32MHz
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET)	// Wait untill PLL is ready
	{
  }
	RCC_PCLK1Config(RCC_HCLK_Div1);			// Configures the Low Speed APB(APB1) clock (PCLK1).
	RCC_PCLK2Config(RCC_HCLK_Div1);			// Configures the High Speed APB(APB2) clock (PCLK2).

	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);	// Configures the System Clock source to PLL
	while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL)	// Wait till PLL is used as system clock source 
  {
  }
}

int main(void)
{	
	RCC_ClocksTypeDef RCC_Clocks;
	
	unsigned long time1 = 0;
	unsigned long time2 = 0;
	unsigned long time3 = 0;
	
	clockCorrection();
	usart1_init();				//initialize USART1 functions
	timer2_millis_init();		//initialize timer and millis functions
	
	printStringLn("Clock correction DONE.");
	printStringLn("GPIO initialized.");	
	printStringLn("USART initialized.");
	printStringLn("MILLIS initialized.");
	
	printStringLn("------------------------------------------------");
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
	printNumberLn(TIM_GetPrescaler(TIM2), DEC);
	
	printString("PERIODE TIM2: ");
	printNumberLn(PERIODE, DEC);
	
	printStringLn("------------------------------------------------");
	
	while(1)
	{  
//		time1 = micros();
//		delay(10);
//		time2 = micros();
//		delay(10);
//		time3 = micros();
//		printStringLn("TAJM: ");
//		printNumberLn(time2 - time1, DEC);
//		printNumberLn(time3 - time2, DEC);
//		//printNumberLn(time1, DEC);
//		//printNumberLn(time2, DEC);
//		//printNumberLn(time3, DEC);
//		
//		//delay(1000);
//		printStringLn("------------------------------------------------");
		
		printNumberLn(millis(), DEC);
		//printNumberLn(micros(), DEC);
		delay(1000);					//[ms]
		//delayMicroseconds(50000);		//[us]
		
		//restartMillis();	//set millis counter to 0.
	}
}
