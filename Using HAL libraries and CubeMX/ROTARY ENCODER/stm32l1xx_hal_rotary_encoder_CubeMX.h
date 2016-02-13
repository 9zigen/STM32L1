
#ifndef __STM32L1XX_ROTARY_ECODER_CUBEMX_H
#define __STM32L1XX_ROTARY_ECODER_CUBEMX_H

#include "stm32l1xx_hal.h"
#include "mxconstants.h"

typedef enum {
	rot_enc_inc_cw,			// CW pulse = +1
	rot_enc_inc_ccw			// CW pulse = -1
} rot_enc_inc_dir_t;

typedef struct {
	// pin A (interrupt pin), pin B
	uint16_t gpio_A_pin;					//  GPIO pin for rotary encoder A pin
	GPIO_TypeDef* gpio_A_port;		//  GPIOx
	uint16_t gpio_B_pin;					//  GPIO pin for rotary encoder B pin
	GPIO_TypeDef* gpio_B_port;		//  GPIOx
	
	rot_enc_inc_dir_t inc_dir;		//  Increment direction (CW or CCW)
	int32_t abs_rot;							//  Absolute rotation from beginning
	int32_t diff_rot;							//  Difference in rotation from last check
		
	//private
	uint8_t _last_pin_A_status;		//  Last state of pin A
	uint8_t _manual_reset;				//  Flag if Encoder_SetAbsToZero() was called
	
} rot_enc_data_t;

void Encoder_Init(rot_enc_data_t* rot_enc_data, GPIO_TypeDef* rot_enc_gpio_A_port, uint16_t rot_enc_gpio_A_pin, GPIO_TypeDef* rot_enc_gpio_B_port, uint16_t rot_enc_gpio_B_pin);

void Encoder_SetIncDir(rot_enc_data_t* rot_enc_data, rot_enc_inc_dir_t rot_enc_direction);
int32_t Encoder_GetState(rot_enc_data_t* rot_enc_data);
void Encoder_CalculateData(rot_enc_data_t* rot_enc_data);
void Encoder_SetAbsToZero(rot_enc_data_t* rot_enc_data);


#endif 


