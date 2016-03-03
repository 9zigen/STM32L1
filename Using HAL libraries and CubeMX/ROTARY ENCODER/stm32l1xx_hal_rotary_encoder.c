#include "stm32l1xx_hal_rotary_encoder.h"

/*
HOW TO USE THIS DRIVER:
This driver is written to be used without CubeMX, although it can be used with. 

1. According to current interrupt priority group - HAL_NVIC_SetPriorityGrouping() user must define
preemption priority and sub priority by changing values 
	#define ENCODER_PREEMPT_PRIORITY
	#define ENCODER_SUB_PRIORITY
	
2. Init rotary encoder by:
	2.a: Creating global encoder data structure:
		Example: rot_enc_data_t	encoder1;
	
	2.b: Call init function with all assigned pins and ports:
		Example: Encoder_Init(&encoder1, GPIOA, GPIO_PIN_2, GPIOA, GPIO_PIN_3);
		Note: first pin (in example above GPIO_PIN_2) is configured as interrupt pin.

	2.3: Create external interrupt handler according to your chosen interrupt pin (in example above GPIO_PIN_2)
		void EXTIx_IRQHandler(void)...
		Inside interrupt routine, user must call Encoder_CalculateData() with corresponding encoder data structure
		Example: void EXTI2_IRQHandler(void){
								Encoder_CalculateData(&encoder1);
								HAL_GPIO_EXTI_IRQHandler(encoder1.gpio_A_pin);
							}
							
		Note 1: For correct interrupt handler, check system file: stm32l100xc.h
		(or take a look at switch() statement in Encoder_Init() for STM32L100.
		
		Note 2: It is recommended, that interrupt function is placed in file with other interrupt 
		routines, eg. stm32l1xx_it.c. In this case, add in .c file (on the top):
		Example: extern rot_enc_data_t	encoder1;
		
3. Use library (example):
	Encoder_SetIncDir(&encoder1, rot_enc_inc_cw);
	if(Encoder_GetState(rot_enc_data_t* rot_enc_data)){  //do something }
	Encoder_SetAbsToZero(&encoder1);
*/

#define ENCODER_PREEMPT_PRIORITY 2
#define ENCODER_SUB_PRIORITY 0

/***************************************************************************/
/*
	Init function.
		rot_enc_data - global encoder data structure.
		rot_enc_gpio_A_port, rot_enc_gpio_A_pin - interrupt pin A of encoder
		rot_enc_gpio_B_port, rot_enc_gpio_B_pin - "normal" input pin B of encoder
*/
void Encoder_Init(rot_enc_data_t* rot_enc_data, GPIO_TypeDef* rot_enc_gpio_A_port, uint16_t rot_enc_gpio_A_pin, GPIO_TypeDef* rot_enc_gpio_B_port, uint16_t rot_enc_gpio_B_pin) {
	GPIO_InitTypeDef GPIO_InitStruct;
	IRQn_Type irqn;
	
	rot_enc_data->gpio_A_port = rot_enc_gpio_A_port;
	rot_enc_data->gpio_B_port = rot_enc_gpio_B_port;
	rot_enc_data->gpio_A_pin = rot_enc_gpio_A_pin;
	rot_enc_data->gpio_B_pin = rot_enc_gpio_B_pin;
	
	// pin A, interrupt pin
	GPIO_InitStruct.Pin = rot_enc_data->gpio_A_pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(rot_enc_data->gpio_A_port, &GPIO_InitStruct);
	
	// pin B
	GPIO_InitStruct.Pin = rot_enc_data->gpio_B_pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(rot_enc_data->gpio_B_port, &GPIO_InitStruct);
	
	switch(rot_enc_data->gpio_A_pin)
	{
		case GPIO_PIN_0: irqn = EXTI0_IRQn; break;
		case GPIO_PIN_1: irqn = EXTI1_IRQn; break;
		case GPIO_PIN_2: irqn = EXTI2_IRQn; break;
		case GPIO_PIN_3: irqn = EXTI3_IRQn; break;
		case GPIO_PIN_4: irqn = EXTI4_IRQn; break;
		case GPIO_PIN_5: case GPIO_PIN_6: case GPIO_PIN_7: case GPIO_PIN_8: case GPIO_PIN_9: irqn = EXTI9_5_IRQn; break;
		case GPIO_PIN_10: case GPIO_PIN_11: case GPIO_PIN_12: case GPIO_PIN_13: case GPIO_PIN_14: case GPIO_PIN_15: irqn = EXTI15_10_IRQn; break;
	}
		
	// EXTI interrupt init
  HAL_NVIC_SetPriority(irqn, 2, 0);
  HAL_NVIC_EnableIRQ(irqn);
	
	rot_enc_data->inc_dir = rot_enc_inc_cw;	// default mode is CW-increment
	rot_enc_data->_last_pin_A_status = 1;
	
	rot_enc_data->abs_rot = 0;
	rot_enc_data->diff_rot = 0;
}

/*
	Set increment direction to CW or CCW
*/	
void Encoder_SetIncDir(rot_enc_data_t* rot_enc_data, rot_enc_inc_dir_t rot_enc_direction){
	rot_enc_data->inc_dir = rot_enc_direction;
}

/*
	Returns difference from the last time this function was called.
	Difference is than reseted.
*/
int32_t Encoder_GetState(rot_enc_data_t* rot_enc_data){
	int32_t difference = rot_enc_data->diff_rot;

	rot_enc_data->diff_rot = 0;
	return difference;
}

/*
	Set current rotary encoder position to zero. 
	A change in encoder position is calculated from zero.
*/
void Encoder_SetAbsToZero(rot_enc_data_t* rot_enc_data){
	rot_enc_data->diff_rot = - rot_enc_data->abs_rot;
	rot_enc_data->abs_rot = 0;
}

/*
	This function should be called in pin A interrupt routine.
	Function detects rotation and direction of rotary encoder.
	Difference is incremented/decremented according to increment mode.
*/
void Encoder_CalculateData(rot_enc_data_t* rot_enc_data){
	uint8_t current_A_pin_state, current_B_pin_state;
	
	current_A_pin_state = HAL_GPIO_ReadPin(rot_enc_data->gpio_A_port, rot_enc_data->gpio_A_pin);
	current_B_pin_state = HAL_GPIO_ReadPin(rot_enc_data->gpio_B_port, rot_enc_data->gpio_B_pin);
	
	// Check for difference betwen current state and last state
	if (current_A_pin_state != rot_enc_data->_last_pin_A_status){
		rot_enc_data->_last_pin_A_status = current_A_pin_state;
		
		if (rot_enc_data->_last_pin_A_status == 0){
			if (current_B_pin_state == 1){
				if (rot_enc_data->inc_dir == rot_enc_inc_cw){	// Increment mode
					rot_enc_data->diff_rot--;
					rot_enc_data->abs_rot--;
				}
				else{
					rot_enc_data->diff_rot++;
					rot_enc_data->abs_rot++;
				}
			}
			else{
				if (rot_enc_data->inc_dir == rot_enc_inc_cw){	// Increment mode
					rot_enc_data->diff_rot++;
					rot_enc_data->abs_rot++;
				}
				else{
					rot_enc_data->diff_rot--;
					rot_enc_data->abs_rot--;
				}
			}
		}
	}
}

