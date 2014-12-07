/*
	stm32l1xx_stepper.c examle project
	Stepper motor used in this example:	http://arduino-info.wikispaces.com/SmallSteppers
	
*/
#include "main.h"

stepper_struct stepper1;

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
	timer2_millis_init();	
	init_usart(USART1, GPIOA, 57600); 
	printStringLn(USART1, "UART initialized!");
	//LEDS
	gpio_pinSetup(GPIOC, D1, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_10MHz);
	gpio_pinSetup(GPIOC, D2, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_10MHz);
	gpio_pinSetup(GPIOA, LED1, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_10MHz);
	gpio_pinSetup(GPIOA, LED2, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_10MHz);
	gpio_pinSetup(GPIOA, LED3, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_10MHz);
	gpio_pinSetup(GPIOA, LED4, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_10MHz);
	
	//BUTTON
	gpio_pinSetup(GPIOC, S1, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_10MHz);
	gpio_pinSetup(GPIOC, S2, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_10MHz);
	gpio_pinSetup(GPIOB, S3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_10MHz);
	gpio_pinSetup(GPIOB, S4, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_10MHz);
	//exti B3, B4 - interrupts
	gpio_pinEXTI_Setup(EXTI_PortSourceGPIOB, S3_EXTI, EXTI_Line0, EXTI_Mode_Interrupt, EXTI_Trigger_Falling, ENABLE);
	gpio_pinNVIC_Setup(EXTI_Line0, 0x0F, 0x0F, ENABLE);
	gpio_pinEXTI_Setup(EXTI_PortSourceGPIOB, S4_EXTI, EXTI_Line1, EXTI_Mode_Interrupt, EXTI_Trigger_Falling, ENABLE);
	gpio_pinNVIC_Setup(EXTI_Line1, 0x0F, 0x0F, ENABLE);

	//Fill in stepper motor struct
	stepper1.motor_pin_1_bank = GPIOA;
	stepper1.motor_pin_1 = GPIO_Pin_4;
	stepper1.motor_pin_2_bank = GPIOA;
	stepper1.motor_pin_2 = GPIO_Pin_5;
	stepper1.motor_pin_3_bank = GPIOA;
	stepper1.motor_pin_3 = GPIO_Pin_6;
	stepper1.motor_pin_4_bank = GPIOA;
	stepper1.motor_pin_4 = GPIO_Pin_7;
	stepper1.use_half_step = USE_HALF_STEP;
	stepper1.maintain_position = DONT_MAINTAIN_POS;		//MAINTAIN_POS;
	stepper1.move_optimally = MOVE_OPTIMALLY;		//MAINTAIN_POS;
	stepperInit_4pin(&stepper1);
	
	//speed setter method:
	setSpeed(&stepper1, 700);	//Sets the speed in pulses per second
	
	while(1)
  {  
		moveToTargetPosOptimally(&stepper1);
  }
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
    {	
		EXTI_ClearFlag(EXTI_Line0);
		stepper1.target_step_number = 100;
		GPIO_ToggleBits(GPIOC, D1);
	}
}
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
    {	
		EXTI_ClearFlag(EXTI_Line1);
		stepper1.target_step_number = -510;
		GPIO_ToggleBits(GPIOC, D2);
	}
}
