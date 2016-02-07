 /*
 ===============================================================================
            ##### STM32L1-discovery board: extra gpio functions #####
								header file
 ===============================================================================
 * @date    18-Oct-2014
 * @author  Domen Jurkovic
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L1xx_GPIO_INIT_H
#define __STM32L1xx_GPIO_INIT_H

/* Includes ------------------------------------------------------------------*/
#include <stm32l1xx.h>

#include <stm32l1xx_gpio.h>
#include <stm32l1xx_exti.h>
#include <stm32l1xx_syscfg.h>
#include <stm32l1xx_rcc.h>
#include <misc.h>


#ifdef __cplusplus
  extern "C" {
#endif

void gpio_pinSetup(GPIO_TypeDef* GPIOx,	uint32_t pinNumber, uint32_t pinMode,	uint8_t pinType, uint8_t pinPull,	uint8_t pinSpeed);
void gpio_pinSetup_AF(GPIO_TypeDef* GPIOx, uint32_t pinNumber, uint8_t GPIO_AF, GPIOOType_TypeDef pinType, GPIOPuPd_TypeDef pinPull, GPIOSpeed_TypeDef pinSpeed);
void gpio_pinSetup_interrupt(GPIO_TypeDef* GPIOx, uint32_t pinNumber, EXTITrigger_TypeDef EXTI_Trigger, uint8_t NVIC_IRQChannelPreemptionPriority, uint8_t NVIC_IRQChannelSubPriority);


#ifdef __cplusplus
}
#endif

#endif /*__STM32L1xx_GPIO_INIT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
