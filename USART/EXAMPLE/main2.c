/*
	USART library test program. 
*/ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l1xx_conf.h" //insert includes

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
    clockCorrection();
    
    init_usart(USART1, GPIOA, 9600);
    printStringLn(USART1, "Clock correction DONE.");
    timer2_millis_init();
    printStringLn(USART1, "Timer millis DONE.");
    
	while(1)
    {  
        printString(USART1, "Millis: ");
        printNumberLn(USART1, millis(), DEC);
		delay(1000);
    }
}
