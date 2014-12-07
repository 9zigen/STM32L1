/**
  ******************************************************************************
  * @file    stm32l1xx_stepper.h
  * @author  Domen Jurkovic
  * @version V1
  * @date    7-December-2014
  * @brief   This file provides functions to manage the
  *          2 and/or 4 pin stepper motor
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L1XX_STEPPER_H_
#define __STM32L1XX_STEPPER_H_

/* Includes ------------------------------------------------------------------*/
#include <stm32l1xx.h>
#include <stm32l1xx_gpio.h>
#include <stm32l1xx_rcc.h>
#include <stm32l1xx_tim.h>
#include <misc.h>

#include <stm32l1xx_gpio_init.h>

#ifdef __cplusplus
  extern "C" {
#endif

// user must define if optimal move is used
#define STEPS_PER_MOTOR_REVOLUTION	4076
#define EXTERNAL_GEAR_RATIO					1		// gear of external ratio
#define CW_CORRECTION_PULSES				0		// number of correction pulses when moving clock-wise
#define CCW_CORRECTION_PULSES				0		// number of correction pulses when moving counter-clock-wise
		
//other driver defines
#define USE_HALF_STEP	1
#define MAINTAIN_POS	1
#define DONT_MAINTAIN_POS	0
#define MOVE_OPTIMALLY			1 		
#define DONT_MOVE_OPTIMALLY	0
#define STEPS_PER_REVOLUTION	STEPS_PER_MOTOR_REVOLUTION*EXTERNAL_GEAR_RATIO	// number of steps per revolution of the last gear
#define HALF_OF_STEPS_PER_REVOLUTION	STEPS_PER_REVOLUTION/2
		
//timer config		
#define TIM3_INCREMENT_RESOLUTION	125	// in microseconds [us]. Timer increments every INCREMENT_RESOLUTION us
#define DEFAULT_PPS 500								// default pulses per second		

		
typedef enum
{
	DIRECTION_CCW  = 0,   // < Counter-Clockwise
	DIRECTION_CW = 1  		// < Clockwise
} direction_t;

typedef struct
{ 
	// user must define these variables
	GPIO_TypeDef* motor_pin_1_bank; // pin1
	uint32_t motor_pin_1;
	GPIO_TypeDef* motor_pin_2_bank;	// pin2
	uint32_t motor_pin_2;
	GPIO_TypeDef* motor_pin_3_bank;	// pin3
	uint32_t motor_pin_3;
	GPIO_TypeDef* motor_pin_4_bank;	// pin4
	uint32_t motor_pin_4;				
	uint8_t use_half_step;			// 1 when the StepperEx motor is to be driven with half steps (only 4-wire)
	uint8_t maintain_position;	// MAINTAIN_POS to hold position after last step
	
	// stepper motor "private variables" - asigned in stepperInit_ function
	uint8_t number_of_steps;  // total number of steps this motor can take
	uint8_t pin_count;        // whether you're driving the motor with 2 or 4 pins
	uint32_t stepper_speed;   // speed in pulses per second
	uint8_t step_number;      // which step the motor is on
		
	direction_t direction;		// Direction of rotation
	int32_t target_step_number;		// target step number
	uint32_t home_position;				// home position; default = 0;
	int32_t current_step_number;	// current number of steps from home position. +/-
	
	uint8_t move_optimally;				// move optimally 
	int32_t steps_per_revolution;	// steps in one output shaft rotation
}stepper_struct;

// set stepper: GPIO pins, USE_HALF_STEP, DONT_MAINTAIN_POS
void stepperInit_2pin(stepper_struct* current_stepper);
void stepperInit_4pin(stepper_struct* current_stepper);

void setSpeed(stepper_struct* current_stepper, uint32_t pulsesPerSecond);	// set speed- pulsesPerSecond: 1<
void setHomePosition(stepper_struct* current_stepper);			// set home position
void moveToHomePosition(stepper_struct* current_stepper);		// move to home position

// blocking move function.
void step(stepper_struct* current_stepper, int steps_to_move);

// blocking move function. Allow change of target position
void moveToTargetPos(stepper_struct* current_stepper);

// blocking move function. Allow change of target position, move optimally
void moveToTargetPosOptimally(stepper_struct* current_stepper);

// convert angle to pulses - relative to stepper motor defines
int32_t angleToPulses(int32_t angle);

/* "private function" */
// step motor
void stepMotor(stepper_struct* current_stepper, int this_step);

// set timer 3 for delay and interrupt setup.
void timer3_init( void );		
		
#ifdef __cplusplus
}
#endif

#endif /* __STM32L1XX_STEPPER_H_ */

