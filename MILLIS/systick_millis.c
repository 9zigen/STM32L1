 /*
 ===============================================================================
				##### STM32F0-discovery board: millis #####
	c file
	timer_millis: STM32L1 family
	Using systick
 ===============================================================================
 * @date    5-Jan-2015
 * @author  Domen Jurkovic
 
 * initialize library with: systick_millis_init();
 * 10us "reliable" resolution. 
 
 */

/* Includes ------------------------------------------------------------------*/
#include <systick_millis.h>

// #define DELAY_US_PRECISION

#define CTRL_TICKINT_Set	0x00000002
#define CTRL_TICKINT_Reset	0xFFFFFFFD

volatile uint32_t systick_millis = 0;

void systick_millis_init()
{
	RCC_ClocksTypeDef system_clocks;
	uint32_t system_freq;
	uint32_t timer_prescaler;
			
	RCC_GetClocksFreq(&system_clocks);	// get system clocks
	system_freq = system_clocks.SYSCLK_Frequency;	// system clock
	timer_prescaler = INCREMENT_RESOLUTION * (system_freq / 1000000);	//example: Prescaler = 1[us] * 48[MHz] = 48; 
	
	SysTick_Config(timer_prescaler);
	NVIC_SetPriority(SysTick_IRQn, 2);
}	

void SysTick_Handler(void)  
{
  systick_millis++;
}

// ------------------------------------------------------------------------

// Return milliseconds from timer initialization or timer reset
// This number will overflow (go back to zero), after approximately 49 days.
uint32_t millis()
{
	return systick_millis;
}

// Wait in this function for specific amount of time.
// param: unsigned long [milliseconds]
void delay(uint32_t ms)
{
	uint32_t delay_millis = systick_millis;
	delay_millis += ms;
	while (systick_millis < delay_millis){
			__nop();
		}
}

// Restart systick_millis to 0. Doesn't STOP timer. 
void restartMillis(void)
{
	systick_millis = 0;
	delay(1);
	systick_millis = 0;

}

//Enables or disables the SysTick Interrupt: ENABLE or DISABLE.
void SysTick_ITConfig(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    SysTick->CTRL |= CTRL_TICKINT_Set;
  }
  else
  {
    SysTick->CTRL &= CTRL_TICKINT_Reset;
  }
}
