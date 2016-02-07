/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include <stm32l1xx.h>
#include <stm32l1xx_it.h>

/*	Include custom drivers/libs/functions  */
#include <custom.h>
#include <stm32l1xx_gpio_init.h>
#include <systick_millis.h>
#include <stm32l1xx_uart_print.h>
#include <stm32l1xx_stepper.h>


//"shield"
#define LED1 GPIO_Pin_4	//GPIOA, PA4
#define LED2 GPIO_Pin_5	//GPIOA, PA5
#define LED3 GPIO_Pin_6	//GPIOA, PA6
#define LED4 GPIO_Pin_7	//GPIOA, PA7

#define S1 GPIO_Pin_4	//GPIOC, PC4
#define S2 GPIO_Pin_5	//GPIOC, PC5
#define S3 GPIO_Pin_0	//GPIOB, PB0
#define S4 GPIO_Pin_1	//GPIOB, PB1

//onboard leds and buttons
#define D1 GPIO_Pin_9	//GPIOC, PC9 - GREEN
#define D2 GPIO_Pin_8	//GPIOC, P89 - BLUE


#endif /* __MAIN_H */

