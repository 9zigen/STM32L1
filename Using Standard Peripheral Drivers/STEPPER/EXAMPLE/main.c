/*
	stm32l1xx_stepper.c examle project
	Stepper motor used in this example:	http://arduino-info.wikispaces.com/SmallSteppers
	
*/
#include "main.h"

stepper_struct stepper1;

int main(void)
{	
	systick_millis_init();	
	UART_Init(); 
	
	printStringLn("UART initialized!");
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
	gpio_pinSetup(GPIOB, S3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_10MHz);
	gpio_pinSetup_interrupt(GPIOB, S3, EXTI_Trigger_Falling, 0, 2);		
	gpio_pinSetup(GPIOB, S4, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_10MHz);
	gpio_pinSetup_interrupt(GPIOB, S4, EXTI_Trigger_Falling, 0, 2);		

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
	stepperInit_4pin(&stepper1);
	
	//speed setter method:
	setSpeed(&stepper1, 400);	//Sets the speed in pulses per second
	
	while(1)
  {  
		//moveToTargetPosOptimally(&stepper1);
		step(&stepper1, 10000);
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
