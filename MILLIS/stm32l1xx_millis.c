 /*
 ===============================================================================
                  ##### STM32L1-discovery board: millis #####
							                  	c file
	timer_millis: STM32L1 family
	USING TIM2 - basic 16 bit timer
 ===============================================================================
 * @date    13-August-2014
 * @author  schperplata
 *
 * initialize library with:	timer2_millis_init();
 *
 */

/* Includes ------------------------------------------------------------------*/
#include <stm32l1xx.h>

volatile unsigned long timer2_millis = 0;

//	Timer 2 initialization.
void timer2_millis_init()
{
	TIM_TimeBaseInitTypeDef timer2_millis;	
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//check smt32l1xx_rcc.c

	timer2_millis.TIM_Prescaler = PRESCALER;
	timer2_millis.TIM_CounterMode = TIM_CounterMode_Up;
	timer2_millis.TIM_Period = PERIODE;						
	timer2_millis.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &timer2_millis);
	
	EnableTimerInterrupt();
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);	//check smt32l1xx_tim.c
	
	TIM_Cmd(TIM2, ENABLE);
}	


//	Timer 2 interrupt initialization.
void EnableTimerInterrupt()
{
    NVIC_InitTypeDef timer2_millis_int;
    timer2_millis_int.NVIC_IRQChannel = TIM2_IRQn;
    timer2_millis_int.NVIC_IRQChannelPreemptionPriority = 10;
    timer2_millis_int.NVIC_IRQChannelSubPriority = 0;
    timer2_millis_int.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&timer2_millis_int);
}

void TIM2_IRQHandler()
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
      TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		  timer2_millis++;	//increment every 1ms
	  }
}
// ------------------------------------------------------------------------

// Return milliseconds from timer initialization or timer reset
unsigned long millis()
{
	return timer2_millis;
}

// Return microseconds from timer initialization or timer reset
unsigned long micros(void) 
{
	unsigned long microseconds = timer2_millis * 1000;
	unsigned long timer2_current_value = 0;
	
	__disable_irq();
	timer2_current_value = TIM_GetCounter(TIM2);
	__enable_irq();	
	
	microseconds += (timer2_current_value * RESOLUTION);
	
	return microseconds;
}

// Wait in this function for specific amount of time. Resolution is RESOLUTION. 
// param: unsigned long [milliseconds], multiplier of RESOLUTION
void delay(unsigned long ms)
{
	unsigned long start = micros();
	unsigned long delay = start + (ms * 1000) - RESOLUTION;		// - RESOLUTION: experimental correction 
	while (micros() <= delay);
}

// Wait in this function for specific amount of time. Resolution is RESOLUTION. param = unsigned long [microseconds]
// param: unsigned long [microseconds], multiplier of RESOLUTION
void delayMicroseconds(unsigned long us)
{
	unsigned long start = micros();
	unsigned long delay = start + us - RESOLUTION;		// - RESOLUTION: experimental correction 
	while (micros() <= delay);
}

// Restart timer to 0. Doesn't STOP timer. 
void restartMillis(void)
{
	__disable_irq();
	timer2_millis = 0;
	TIM_SetCounter(TIM2, 0);
	__enable_irq();
}
