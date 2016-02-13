#include "stm32l1xx_hal_rotary_encoder_CubeMX.h"

/*
HOW TO USE THIS DRIVER:
This driver is written to be used with CubeMX.

1. In CubeMX set interrupt:
	1.a: Chose any interrupt capable pin and set it as GPIO_EXTIx.
	1.b: Name this pin as ENC1_A.
		Note: if you are using multiple rotary encoders, name this pins as ENC1_A, ENC2_A, ENC3_A, ...
	
	1.c: Chose any other pin and set it as input: GPIO_Input
	1.d: Name this pin as ENC1_B
		Note: if you are using multiple rotary encoders, name this pins as ENC1_B, ENC2_B, ENC3_B, ...

2. In CubeMX set interrupts ant their priorities:
	2.a: In Configuration navigate to GPIO and set all ENCx_A pins:
		GPIO mode: External Interrupt Mode with Rising/Falling edge trigger detection
	2.b: Set pull-up and pull-down resistors according to your hardware. 
		If you are using pull-ups, common pin of encoder should be connected to GND. (And vice versa).
	
	2.c: In Configuration navigate to NVIC and enable all corresponding "EXTI lineX interrupt" pins.
		Set up priority and subpriority to your needs.
		Example, if your chosen pin ENC1_A is GPIO_PIN_2, enable "EXTI line2 interrupt".
	
2. In main.c init rotary encoder by:
	2.a: Create global encoder data structure:
		Example: rot_enc_data_t	encoder1;
	
	2.b: Call init function with all assigned pins according to "mxconstants.h"
		Encoder_Init(&encoder1, ENC1_A_GPIO_Port, ENC1_A_Pin, ENC1_B_GPIO_Port, ENC1_B_Pin);
		
	2.3: Add	Encoder_CalculateData() with corresponding encoder data structure
		to interrupt handler in "stm32l1xx_it.c":
		Example: void EXTI2_IRQHandler(void){
							// USER CODE BEGIN EXTI2_IRQn 0
							Encoder_CalculateData(&encoder1);
							// USER CODE END EXTI2_IRQn 0
							HAL_GPIO_EXTI_IRQHandler(encoder1.gpio_A_pin);
						}
							
		Also, add		"extern rot_enc_data_t	encoder1;" 	at the top of "stm32l1xx_it.c" so compiler sees it.
		
3. Use library (example):
	Encoder_SetIncDir(&encoder1, rot_enc_inc_cw);
	if(Encoder_GetState(rot_enc_data_t* rot_enc_data)){  //do something }
	Encoder_SetAbsToZero(&encoder1);

Once this procedure is completed, you can change pins in CubeMX as you wish (almost).
*/

/***************************************************************************/
/*
	Init function.
		rot_enc_data - global encoder data structure.
		Add pins and ports according to "mxconstants.h" file
*/
void Encoder_Init(rot_enc_data_t* rot_enc_data, GPIO_TypeDef* rot_enc_gpio_A_port, uint16_t rot_enc_gpio_A_pin, GPIO_TypeDef* rot_enc_gpio_B_port, uint16_t rot_enc_gpio_B_pin){
	rot_enc_data->gpio_A_port = rot_enc_gpio_A_port;
	rot_enc_data->gpio_B_port = rot_enc_gpio_B_port;
	rot_enc_data->gpio_A_pin = rot_enc_gpio_A_pin;
	rot_enc_data->gpio_B_pin = rot_enc_gpio_B_pin;
	
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
	Absoulte value is incremented/decremented by difference value, except if Encoder_SetAbsToZero() was used before. 
*/
int32_t Encoder_GetState(rot_enc_data_t* rot_enc_data){
	int32_t difference = rot_enc_data->diff_rot;
	
	if(rot_enc_data->_manual_reset == 1){
		rot_enc_data->diff_rot = 0;
		rot_enc_data->_manual_reset = 0;
	}
	else{
		rot_enc_data->abs_rot += rot_enc_data->diff_rot;
		rot_enc_data->diff_rot = 0;
	}
	
	return difference;
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
				}
				else{
					rot_enc_data->diff_rot++;
				}
			}
			else{
				if (rot_enc_data->inc_dir == rot_enc_inc_cw){	// Increment mode
					rot_enc_data->diff_rot++;
				}
				else{
					rot_enc_data->diff_rot--;
				}
			}
		}
	}
}

/*
	Set current rotary encoder position to zero. 
	A change in encoder position is calculated from zero.
*/
void Encoder_SetAbsToZero(rot_enc_data_t* rot_enc_data){
	rot_enc_data->diff_rot = - rot_enc_data->abs_rot;
	rot_enc_data->abs_rot = 0;
	rot_enc_data->_manual_reset = 1;
}

