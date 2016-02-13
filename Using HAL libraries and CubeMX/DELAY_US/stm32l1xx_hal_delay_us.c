 /*
 
 ===============================================================================
							Microsecond delay
 ===============================================================================
 * @date    31-Jan-2016
 * @author  Domen Jurkovic
 
 * initialize library with: delay_us_init();
 * for 1MHz or more	core frequency clock
 
 * This library doesn't generate precise us delay, so be careful - take a few us more/less
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_delay_us.h"

uint32_t us_multiplier;

// init delay 
void delay_us_init(void) {
    us_multiplier = HAL_RCC_GetSysClockFreq() / 1000000; //For 1 us delay, we need to divide with 1M */
}

// delay function: micros >= 1;   
void delay_us(uint32_t micros){
	micros *= us_multiplier;
	
	//substitute 8 cycles for each call of asm code below == //micros /= 8; 
	__asm(" mov r0, micros \n"
	"loop: subs r0, #8 \n"
	" bhi loop \n");
}
