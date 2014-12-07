 /*
 ===============================================================================
								##### STM32L1-discovery board: millis #####
																c file
	timer_millis: STM32L1 family
	USING TIM2 - basic 16 bit timer
 ===============================================================================
 * @date    26-November-2014
 * @author  Domen Jurkovic
 
 * initialize library with: timer2_millis_init();
 * 10us "reliable" resolution. 
 
 */

/* Includes ------------------------------------------------------------------*/
#include <stm32l1xx_millis.h>

// #define DELAY_US_PRECISION

volatile uint32_t timer2_millis = 0;

/*
	Timer 2 initialization.
*/
void timer2_millis_init()
{
	TIM_TimeBaseInitTypeDef timer2_millis;
	RCC_ClocksTypeDef system_freq;
	uint32_t timer_freq;
	uint32_t timer_prescaler;
	uint32_t timer_periode;
		
	RCC_GetClocksFreq(&system_freq);	//get system clocks
	timer_freq = system_freq.PCLK1_Frequency;	//TIM2 clock 
	timer_prescaler = INCREMENT_RESOLUTION * (timer_freq / 1000000);	//example: Prescaler = 1[us] * 32[MHz] = 32; 32(prescaler) * 31.25ns = 1us;
	timer_periode = 1000 / INCREMENT_RESOLUTION;	// 1000us=1ms
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//check smt32l1xx_rcc.c
	timer2_millis.TIM_Prescaler = timer_prescaler;
	timer2_millis.TIM_CounterMode = TIM_CounterMode_Up;
	timer2_millis.TIM_Period = timer_periode -1;						
	timer2_millis.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &timer2_millis);
	
	EnableTimerInterrupt();
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);	//check smt32l1xx_tim.c
	
	TIM_Cmd(TIM2, ENABLE);
}	

/*
	Timer 2 interrupt initialization.
*/
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
// This number will overflow (go back to zero), after approximately 49 days.
uint32_t millis()
{
	return timer2_millis;
}

// Return microseconds from timer initialization or timer reset
// This number will overflow (go back to zero), after approximately 70 minutes
uint32_t micros(void) 
{
	uint64_t microseconds = ((uint64_t)timer2_millis) * 1000;
	uint64_t timer2_current_value = (uint64_t)(TIM_GetCounter(TIM2));
	microseconds += timer2_current_value * INCREMENT_RESOLUTION;
	
	//return (uint32_t)(microseconds);	
	return (uint32_t)(microseconds);	
}

// Wait in this function for specific amount of time.
// param: unsigned long [milliseconds]
// #define DELAY_US_PRECISION for microsecond resolution. 
// NOTE: There is no compensation for time that code and other system calls consume!
void delay(uint32_t ms)
{
	#ifdef DELAY_US_PRECISION
		uint64_t current_time = 0;
		uint64_t delay_millis = ((timer2_millis + ms)* 1000) + (TIM_GetCounter(TIM2)*INCREMENT_RESOLUTION);	//micros() + ms*1000
	
		while ( current_time < delay_millis){
		current_time = (timer2_millis*1000 + (TIM_GetCounter(TIM2)*INCREMENT_RESOLUTION));
	}
	#else
		uint32_t delay_millis = timer2_millis;
		delay_millis += ms;
		while (timer2_millis < delay_millis){
			__nop();
		}
	#endif
	
}


// Wait in this function for specific amount of time. 
// param: unsigned long [microseconds], multiplier of INCREMENT_RESOLUTION * 10
void delayMicroseconds(uint32_t us)
{
	uint32_t delay_micros = micros();
	delay_micros += us;
	while (micros() < delay_micros);
}

// Restart timer to 0. Doesn't STOP timer. 
void restartMillis(void)
{
	timer2_millis = 0;
	TIM_SetCounter(TIM2, 0);
}

