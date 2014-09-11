/**
  ******************************************************************************
  * @file    stm32l1xx_gpio.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    22-February-2013
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the GPIO peripheral:           
  *           + Initialization and Configuration
  *           + GPIO Read and Write
  *           + GPIO Alternate functions configuration
  *
  * schperplata: there are custom functions at the bottom of this file:
  *
  *
  *
  * 
  *  @verbatim
    ===========================================================================
                         ##### How to use this driver #####
    ===========================================================================
      [..]
      (#) Enable the GPIO AHB clock using RCC_AHBPeriphClockCmd()
      (#) Configure the GPIO pin(s) using GPIO_Init()
          Four possible configuration are available for each pin:
         (++) Input: Floating, Pull-up, Pull-down.
         (++) Output: Push-Pull (Pull-up, Pull-down or no Pull)
              Open Drain (Pull-up, Pull-down or no Pull).
              In output mode, the speed is configurable: Very Low, Low,
              Medium or High.
         (++) Alternate Function: Push-Pull (Pull-up, Pull-down or no Pull)
              Open Drain (Pull-up, Pull-down or no Pull).
         (++) Analog: required mode when a pin is to be used as ADC channel,
              DAC output or comparator input.
      (#) Peripherals alternate function:
          (++) For ADC, DAC and comparators, configure the desired pin in 
               analog mode using GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AN
          (++) For other peripherals (TIM, USART...):
              (+++) Connect the pin to the desired peripherals' Alternate 
                    Function (AF) using GPIO_PinAFConfig() function.
              (+++) Configure the desired pin in alternate function mode using
                    GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
              (+++) Select the type, pull-up/pull-down and output speed via 
                    GPIO_PuPd, GPIO_OType and GPIO_Speed members.
              (+++) Call GPIO_Init() function.
      (#) To get the level of a pin configured in input mode use GPIO_ReadInputDataBit()
      (#) To set/reset the level of a pin configured in output mode use
          GPIO_SetBits()/GPIO_ResetBits()
      (#) During and just after reset, the alternate functions are not 
          active and the GPIO pins are configured in input floating mode
          (except JTAG pins).
      (#) The LSE oscillator pins OSC32_IN and OSC32_OUT can be used as 
          general-purpose (PC14 and PC15, respectively) when the LSE
          oscillator is off. The LSE has priority over the GPIO function.
      (#) The HSE oscillator pins OSC_IN/OSC_OUT can be used as 
          general-purpose PH0 and PH1, respectively, when the HSE 
          oscillator is off. The HSE has priority over the GPIO function.
    @endverbatim
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_rcc.h"

/** @addtogroup STM32L1xx_StdPeriph_Driver
  * @{
  */

/** @defgroup GPIO 
  * @brief GPIO driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup GPIO_Private_Functions
  * @{
  */

/** @defgroup GPIO_Group1 Initialization and Configuration
 *  @brief   Initialization and Configuration
 *
@verbatim   
 ===============================================================================
                    ##### Initialization and Configuration #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the GPIOx peripheral registers to their default reset 
  *         values.
  *         By default, The GPIO pins are configured in input floating mode
  *         (except JTAG pins).
  * @param  GPIOx: where x can be (A..H) to select the GPIO peripheral.
  * @retval None
  */
void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  if(GPIOx == GPIOA)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOA, DISABLE);  
  }
  else if(GPIOx == GPIOB)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOB, DISABLE);
  }
  else if(GPIOx == GPIOC)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOC, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOC, DISABLE);
  }
  else if(GPIOx == GPIOD)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOD, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOD, DISABLE);
  }
  else if(GPIOx == GPIOE)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOE, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOE, DISABLE);
  }
  else if(GPIOx == GPIOF)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOF, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOF, DISABLE);
  }
  else if(GPIOx == GPIOG)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOG, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOG, DISABLE);
  }   
  else
  {
    if(GPIOx == GPIOH)
    {
      RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOH, ENABLE);
      RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOH, DISABLE);
    }
  }
}

/**
  * @brief  Initializes the GPIOx peripheral according to the specified 
  *         parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (A..H) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that 
  *         contains the configuration information for the specified GPIO
  *         peripheral.

  * @retval None
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;
  
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
  assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));

  /* -------------------------Configure the port pins---------------- */
  /*-- GPIO Mode Configuration --*/
  for (pinpos = 0x00; pinpos < 0x10; pinpos++)
  {
    pos = ((uint32_t)0x01) << pinpos;

    /* Get the port pins position */
    currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

    if (currentpin == pos)
    {
      GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));

      GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));

      if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF))
      {
        /* Check Speed mode parameters */
        assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));

        /* Speed mode configuration */
        GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinpos * 2));
        GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << (pinpos * 2));

        /*Check Output mode parameters */
        assert_param(IS_GPIO_OTYPE(GPIO_InitStruct->GPIO_OType));

        /* Output mode configuration */
        GPIOx->OTYPER  &= ~((GPIO_OTYPER_OT_0) << ((uint16_t)pinpos)) ;
        GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << ((uint16_t)pinpos));
      }

      /* Pull-up Pull down resistor configuration */
      GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
      GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
    }
  }
}

/**
  * @brief  Fills each GPIO_InitStruct member with its default value.
  * @param  GPIO_InitStruct : pointer to a GPIO_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
  /* Reset GPIO init structure parameters values */
  GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct->GPIO_Speed = GPIO_Speed_400KHz;
  GPIO_InitStruct->GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct->GPIO_PuPd = GPIO_PuPd_NOPULL;
}

/**
  * @brief  Locks GPIO Pins configuration registers.
  *         The locked registers are GPIOx_MODER, GPIOx_OTYPER, GPIOx_OSPEEDR,
  *         GPIOx_PUPDR, GPIOx_AFRL and GPIOx_AFRH.
  *         The configuration of the locked GPIO pins can no longer be modified
  *         until the next reset.
  * @param  GPIOx: where x can be (A..H) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  __IO uint32_t tmp = 0x00010000;
  
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  tmp |= GPIO_Pin;
  /* Set LCKK bit */
  GPIOx->LCKR = tmp;
  /* Reset LCKK bit */
  GPIOx->LCKR =  GPIO_Pin;
  /* Set LCKK bit */
  GPIOx->LCKR = tmp;
  /* Read LCKK bit*/
  tmp = GPIOx->LCKR;
  /* Read LCKK bit*/
  tmp = GPIOx->LCKR;
}

/**
  * @}
  */

/** @defgroup GPIO_Group2 GPIO Read and Write
 *  @brief   GPIO Read and Write
 *
@verbatim   
 ===============================================================================
                      ##### GPIO Read and Write #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A..H) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to read.
  *   This parameter can be GPIO_Pin_x where x can be (0..15).
  * @retval The input port pin value.
  */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;
  
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
  * @brief  Reads the specified GPIO input data port.
  * @param  GPIOx: where x can be (A..H) to select the GPIO peripheral.
  * @retval GPIO input data port value.
  */
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  return ((uint16_t)GPIOx->IDR);
}

/**
  * @brief  Reads the specified output data port bit.
  * @param  GPIOx: where x can be (A..H) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the port bit to read.
  *   This parameter can be GPIO_Pin_x where x can be (0..15).
  * @retval The output port pin value.
  */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  
  if ((GPIOx->ODR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
  * @brief  Reads the specified GPIO output data port.
  * @param  GPIOx: where x can be (A..H) to select the GPIO peripheral.
  * @retval GPIO output data port value.
  */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  return ((uint16_t)GPIOx->ODR);
}

/**
  * @brief  Sets the selected data port bits.
  * @param  GPIOx: where x can be (A..H) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @note  This functions uses GPIOx_BSRR register to allow atomic read/modify 
  *        accesses. In this way, there is no risk of an IRQ occurring between
  *        the read and the modify access.
  * @retval None
  */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  GPIOx->BSRRL = GPIO_Pin;
}

/**
  * @brief  Clears the selected data port bits.
  * @param  GPIOx: where x can be (A..H) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @note  This functions uses GPIOx_BSRR register to allow atomic read/modify 
  *        accesses. In this way, there is no risk of an IRQ occurring between
  *        the read and the modify access.
  * @retval None
  */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  GPIOx->BSRRH = GPIO_Pin;
}

/**
  * @brief  Sets or clears the selected data port bit.
  * @param  GPIOx: where x can be (A..H) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *   This parameter can be one of GPIO_Pin_x where x can be (0..15).
  * @param  BitVal: specifies the value to be written to the selected bit.
  *   This parameter can be one of the BitAction enum values:
  *     @arg Bit_RESET: to clear the port pin
  *     @arg Bit_SET: to set the port pin
  * @retval None
  */
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_BIT_ACTION(BitVal));
  
  if (BitVal != Bit_RESET)
  {
    GPIOx->BSRRL = GPIO_Pin;
  }
  else
  {
    GPIOx->BSRRH = GPIO_Pin ;
  }
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIOx: where x can be (A..H) to select the GPIO peripheral.
  * @param  PortVal: specifies the value to be written to the port output data 
  *                  register.
  * @retval None
  */
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  GPIOx->ODR = PortVal;
}

/**
  * @brief  Toggles the specified GPIO pins..
  * @param  GPIOx: where x can be (A..H) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the pins to be toggled.
  * @retval None
  */
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  GPIOx->ODR ^= GPIO_Pin;
}

/**
  * @}
  */

/** @defgroup GPIO_Group3 GPIO Alternate functions configuration functions
 *  @brief   GPIO Alternate functions configuration functions
 *
@verbatim   
 ===============================================================================
          ##### GPIO Alternate functions configuration functions #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Changes the mapping of the specified pin.
  * @param  GPIOx: where x can be (A..H) to select the GPIO peripheral.
  * @param  GPIO_PinSource: specifies the pin for the Alternate function.
  *   This parameter can be GPIO_PinSourcex where x can be (0..15).
  * @param  GPIO_AFSelection: selects the pin to used as Alternat function.
  *   This parameter can be one of the following values:
  *     @arg GPIO_AF_RTC_50Hz: RTC 50/60 Hz synchronization
  *     @arg GPIO_AF_MCO: Microcontroller clock output
  *     @arg GPIO_AF_RTC_AF1: Time stamp, Tamper, Alarm A out, Alarm B out,
  *                           512 Hz clock output (with an LSE oscillator of 32.768 kHz)
  *     @arg GPIO_AF_WKUP: wakeup
  *     @arg GPIO_AF_SWJ: SWJ (SW and JTAG)
  *     @arg GPIO_AF_TRACE: Connect TRACE pins to AF0 (default after reset)
  *     @arg GPIO_AF_TIM2c: Connect TIM2 pins to AF1
  *     @arg GPIO_AF_TIM3: Connect TIM3 pins to AF2
  *     @arg GPIO_AF_TIM4: Connect TIM4 pins to AF2
  *     @arg GPIO_AF_TIM5: Connect TIM5 pins to AF2
  *     @arg GPIO_AF_TIM9: Connect TIM9 pins to AF3
  *     @arg GPIO_AF_TIM10: Connect TIM10 pins to AF3
  *     @arg GPIO_AF_TIM11: Connect TIM11 pins to AF3
  *     @arg GPIO_AF_I2C1: Connect I2C1 pins to AF4
  *     @arg GPIO_AF_I2C2: Connect I2C2 pins to AF4
  *     @arg GPIO_AF_SPI1: Connect SPI1 pins to AF5
  *     @arg GPIO_AF_SPI2: Connect SPI2/I2S2 pins to AF5
  *     @arg GPIO_AF_SPI3: Connect SPI3/I2S3 pins to AF6
  *     @arg GPIO_AF_USART1: Connect USART1 pins to AF7
  *     @arg GPIO_AF_USART2: Connect USART2 pins to AF7
  *     @arg GPIO_AF_USART3: Connect USART3 pins to AF7
  *     @arg GPIO_AF_UART4: Connect UART4 pins to AF8
  *     @arg GPIO_AF_UART5: Connect UART5 pins to AF8
  *     @arg GPIO_AF_USB: Connect USB pins to AF10
  *     @arg GPIO_AF_LCD: Connect LCD pins to AF11
  *     @arg GPIO_AF_FSMC: Connect FSMC pins to AF12
  *     @arg GPIO_AF_SDIO: Connect SDIO pins to AF12
  *     @arg GPIO_AF_RI: Connect RI pins to AF14
  *     @arg GPIO_AF_EVENTOUT: Cortex-M3 EVENTOUT signal
  * @note The pin should already been configured in Alternate Function mode(AF)
  *        using GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
  * @note Please refer to the Alternate function mapping table in the device 
  *        datasheet for the detailed mapping of the system and peripherals'
  *        alternate function I/O pins.  
  * @note EVENTOUT is not mapped on PH0, PH1 and PH2.  
  * @retval None
  */
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF)
{
  uint32_t temp = 0x00;
  uint32_t temp_2 = 0x00;
  
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
  assert_param(IS_GPIO_AF(GPIO_AF));
  
  temp = ((uint32_t)(GPIO_AF) << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4)) ;
  GPIOx->AFR[GPIO_PinSource >> 0x03] &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4)) ;
  temp_2 = GPIOx->AFR[GPIO_PinSource >> 0x03] | temp;
  GPIOx->AFR[GPIO_PinSource >> 0x03] = temp_2;
}

// -----------------------------------------------------------------------------------//
/*	Custom GPIO functions	*/

/*
	GPIOx: where x can be (A..H) to select the GPIO peripheral.
	pinNumber: GPIO_Pin_0 ... GPIO_Pin_15, GPIO_Pin_All
	pinMode: GPIO_Mode_IN, GPIO_Mode_OUT
	pinType: GPIO_OType_PP, GPIO_OType_OD - sets the pin type to push / pull  or open drain
	pinPull: GPIO_PuPd_NOPULL, GPIO_PuPd_UP, GPIO_PuPd_DOWN
	pinSpeed: GPIO_Speed_400KHz, GPIO_Speed_2MHz, GPIO_Speed_10MHz, GPIO_Speed_40MHz
	
	gpio_pinSetup(GPIOC, GPIO_Pin_8, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_Speed_2MHz);
*/
void gpio_pinSetup(GPIO_TypeDef* GPIOx, uint32_t pinNumber, GPIOMode_TypeDef pinMode, GPIOOType_TypeDef pinType, GPIOPuPd_TypeDef pinPull, GPIOSpeed_TypeDef pinSpeed)
{
	GPIO_InitTypeDef GPIO_setup;
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

	if(GPIOx == GPIOA)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	}
	else if(GPIOx == GPIOB)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	}
	else if(GPIOx == GPIOC)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	}
	else if(GPIOx == GPIOD)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	}
	else if(GPIOx == GPIOE)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	}
	else if(GPIOx == GPIOF)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	}
	else if(GPIOx == GPIOG)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOG, ENABLE);
	}   
	else
	{
		if(GPIOx == GPIOH)
		{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOH, ENABLE);
		}
	}
	
	GPIO_setup.GPIO_Pin = pinNumber;
	GPIO_setup.GPIO_Mode = pinMode;
	GPIO_setup.GPIO_OType = pinType;
	GPIO_setup.GPIO_PuPd = pinPull;
	GPIO_setup.GPIO_Speed = pinSpeed;
	GPIO_Init(GPIOx, &GPIO_setup);
}

/*
	GPIOx: where x can be (A..H) to select the GPIO peripheral.
	pinNumber: GPIO_Pin_0 ... GPIO_Pin_15, GPIO_Pin_All
	GPIO_AF: stm32l1xx_gpio.c, search GPIO_AFSelection.
	pinType: GPIO_OType_PP, GPIO_OType_OD - sets the pin type to push / pull  or open drain
	pinPull: GPIO_PuPd_NOPULL, GPIO_PuPd_UP, GPIO_PuPd_DOWN
	pinSpeed: GPIO_Speed_400KHz, GPIO_Speed_2MHz, GPIO_Speed_10MHz, GPIO_Speed_40MHz

	gpio_pinSetup_AF(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_Speed_2MHz);
*/
void gpio_pinSetup_AF(GPIO_TypeDef* GPIOx, uint32_t pinNumber, uint8_t GPIO_AF, GPIOOType_TypeDef pinType, GPIOPuPd_TypeDef pinPull, GPIOSpeed_TypeDef pinSpeed)
{
	GPIO_InitTypeDef GPIO_setup;
	uint32_t pinSource = 0;
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

	if(GPIOx == GPIOA)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	}
	else if(GPIOx == GPIOB)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	}
	else if(GPIOx == GPIOC)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	}
	else if(GPIOx == GPIOD)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	}
	else if(GPIOx == GPIOE)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	}
	else if(GPIOx == GPIOF)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	}
	else if(GPIOx == GPIOG)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOG, ENABLE);
	}   
	else
	{
		if(GPIOx == GPIOH)
		{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOH, ENABLE);
		}
	}
	switch(pinNumber)
	{
		case GPIO_Pin_0: pinSource = GPIO_PinSource0; break;
		case GPIO_Pin_1: pinSource = GPIO_PinSource1; break;
		case GPIO_Pin_2: pinSource = GPIO_PinSource2; break;
		case GPIO_Pin_3: pinSource = GPIO_PinSource3; break;
		case GPIO_Pin_4: pinSource = GPIO_PinSource4; break;
		case GPIO_Pin_5: pinSource = GPIO_PinSource5; break;
		case GPIO_Pin_6: pinSource = GPIO_PinSource6; break;
		case GPIO_Pin_7: pinSource = GPIO_PinSource7; break;
		case GPIO_Pin_8: pinSource = GPIO_PinSource8; break;
		case GPIO_Pin_9: pinSource = GPIO_PinSource9; break;
		case GPIO_Pin_10: pinSource = GPIO_PinSource10; break;
		case GPIO_Pin_11: pinSource = GPIO_PinSource11; break;
		case GPIO_Pin_12: pinSource = GPIO_PinSource12; break;
		case GPIO_Pin_13: pinSource = GPIO_PinSource13; break;
		case GPIO_Pin_14: pinSource = GPIO_PinSource14; break;
		case GPIO_Pin_15: pinSource = GPIO_PinSource15; break;
	}
	
	GPIO_PinAFConfig(GPIOx, pinSource, GPIO_AF);
	
	GPIO_setup.GPIO_Pin = pinNumber;
	GPIO_setup.GPIO_Mode = GPIO_Mode_AF;
	GPIO_setup.GPIO_OType = pinType;
	GPIO_setup.GPIO_PuPd = pinPull;
	GPIO_setup.GPIO_Speed = pinSpeed;
	GPIO_Init(GPIOx, &GPIO_setup);
	
}

/*
	EXTI_PortSourceGPIOx: where x can be (A..H) to select the GPIO peripheral.
	EXTI_PinSourcex: EXTI_PinSource0 ... EXTI_PinSource15
	EXTI_LineX: EXTI_Line0 ... EXTI_Line15; EXTI_Line16-23 for special functions 
	EXTI_Mode: EXTI_Mode_Interrupt, EXTI_Mode_Event
	EXTI_Trigger: EXTI_Trigger_Rising, EXTI_Trigger_Falling, EXTI_Trigger_Rising_Falling
	EXTI_LineCmd: Specifies the new state of the selected EXTI lines: ENABLE or DISABLE

	gpio_pinEXTI_Setup(EXTI_PortSourceGPIOA, EXTI_PinSource0, EXTI_Line0, EXTI_Mode_Interrupt, EXTI_Trigger_Rising, ENABLE);
*/
void gpio_pinEXTI_Setup(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex, uint32_t EXTI_LineX, uint8_t EXTI_Mode, uint8_t EXTI_Trigger, FunctionalState EXTI_LineCmd)
{
	EXTI_InitTypeDef EXTI_InitStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);		//SYSCFG APB clock must be enabled to get write access to SYSCFG_EXTICRx  registers
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOx, EXTI_PinSourcex);
	
	EXTI_InitStructure.EXTI_Line = EXTI_LineX;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger;
	EXTI_InitStructure.EXTI_LineCmd = EXTI_LineCmd;
	EXTI_Init(&EXTI_InitStructure);	
}

/*
	EXTI_LineX: EXTI_Line0 ... EXTI_Line15; EXTI_Line16-23 for special functions 
	NVIC_IRQChannelPreemptionPriority: can be a value between 0 and 15
	NVIC_IRQChannelSubPriority: can be a value between 0 and 15
	NVIC_IRQChannelCmd: ENABLE or DISABLE

	gpio_pinNVIC_Setup(EXTI_Line0, 0x0F, 0x0F, ENABLE);
*/
void gpio_pinNVIC_Setup(uint32_t EXTI_LineX, uint8_t NVIC_IRQChannelPreemptionPriority, uint8_t NVIC_IRQChannelSubPriority, FunctionalState NVIC_IRQChannelCmd)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	IRQn_Type EXTIx_IRQn;
	
	switch(EXTI_LineX)
	{
		case EXTI_Line0: EXTIx_IRQn = EXTI0_IRQn; break;
		case EXTI_Line1: EXTIx_IRQn = EXTI1_IRQn; break;
		case EXTI_Line2: EXTIx_IRQn = EXTI2_IRQn; break;
		case EXTI_Line3: EXTIx_IRQn = EXTI3_IRQn; break;
		case EXTI_Line4: EXTIx_IRQn = EXTI4_IRQn; break;
		case (EXTI_Line5 | EXTI_Line6 | EXTI_Line7 | EXTI_Line8 | EXTI_Line9): EXTIx_IRQn = EXTI9_5_IRQn; break;
		case (EXTI_Line10 | EXTI_Line11 | EXTI_Line12 | EXTI_Line13 | EXTI_Line14 | EXTI_Line15): EXTIx_IRQn = EXTI15_10_IRQn; break;
	}
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTIx_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriority;
	NVIC_InitStructure.NVIC_IRQChannelCmd = NVIC_IRQChannelCmd;
	NVIC_Init(&NVIC_InitStructure);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
