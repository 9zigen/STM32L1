 /*
 ===============================================================================
 Button driver: c file
 ===============================================================================
 * @date    16-Feb-2016
 * @author  Domen Jurkovic
  
 */

#include "stm32l1xx_hal_buttons.h"

/*	HOW TO USE THIS DRIVER
	1. Comment/uncomment BUTTON_CubeMX in stm32l1xx_hal_buttons.h if you are using CubeMX code generation tool.
	
	2. Init button structure in main.c
		Example: button_struct_t nameOfYourButton;
	
	3. Init buttons
		Example: buttonInit(&nameOfYourButton, GPIOA, GPIO_PIN_0, GPIO_PIN_RESET, 30, 2000);
		In this example, PA0 pin is pulled up by internal pull up resistor. After 30 ms it is registered as pressed,
		after 2 seconds it is registered as long pressed.
		
	4. Add button handler in your code
		Example: 
			if(buttonUpdate(&nameOfYourButton) == isPressed){
				//todo if button is pressed
			}
		Note: isPressed could be changed according to button_state_t typedef in stm32l1xx_hal_buttons.h file
		
Note: Typical debounce time for buttons depends on switch quality and use of external capacitors. 
30ms should do the trick.
*/
/******************************************************************************/

/* Button init function
	button_struct - button structure with all parameters.
	GPIO_Port - GPIOA, GPIOB, GPIOC
	GPIO_Pin - GPIO_PIN_0, ..., GPIO_PIN_15
	active_state - GPIO_PIN_RESET, GPIO_PIN_SET (This is the state of input read with HAL_GPIO_ReadPin() when button is pressed
	debounce_time - time in miliseconds that button must be pressed to be flagged as isPressed
	long_press_time - time in miliseconds that button must be pressed to be flagged as isPressedLong
	
	Note: If CubeMX is used, GPIO_Port, GPIO_Pin, should match defines in "mxconstants.h" file.
*/
void buttonInit(button_struct_t *button_struct, GPIO_TypeDef* GPIO_Port, uint32_t GPIO_Pin, GPIO_PinState active_state, uint32_t debounce_time, uint32_t long_press_time){
	#ifdef BUTTON_CubeMX

	#else
		GPIO_InitTypeDef GPIO_InitStruct;
		
		if(GPIO_Port == GPIOA) __GPIOA_CLK_ENABLE();  
		if(GPIO_Port == GPIOB) __GPIOB_CLK_ENABLE();
		if(GPIO_Port == GPIOC) __GPIOC_CLK_ENABLE();
						
		GPIO_InitStruct.Pin = GPIO_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		
		if(active_state == GPIO_PIN_RESET){
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			
		}else{
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
		}	
		HAL_GPIO_Init(GPIO_Port, &GPIO_InitStruct);
	#endif
	
	button_struct->GPIO_Pin = GPIO_Pin;
	button_struct->GPIO_Port = GPIO_Port;
	button_struct->debounce_time = debounce_time;
	button_struct->long_press_time = long_press_time;
	button_struct->active_state = active_state;
	
	button_struct->_on_press_time = 0;
	button_struct->_previous_state = button_off;
	button_struct->_state_changed = 0;
	button_struct->_state = noEvent;
}

/* Button handler - update and return current status of button
	return value: 
		noEvent - no pin state change
		stateChanged - pin state changed but not debounced or long pressed jet
		isPressed - button is pressed for more than debounce_time
		isPressedLong - button is pressed for more than long_press_time
		isReleased - button was released (unpressed)

	This function should be polled frequently, at least a few times in debounce_time.

*/
button_state_t buttonUpdate(button_struct_t *button_struct){
	_phy_state_t state = _button_state(button_struct);	// get button state
	button_state_t return_status;
	
	
	// is state different than previous?
	if(state != button_struct->_previous_state){	// state is	different
		// is button currently pressed?
		if(state == button_on){	
			button_struct->_on_press_time = HAL_GetTick(); // get current time
			button_struct->_state_changed = 1;	// state is changed
			button_struct->_previous_state = button_on;
		} 
		else{	// button state = button_off, prevous state = button_on
			// was button released after minimum debounce time?
			if(HAL_GetTick() >= (button_struct->_on_press_time + button_struct->debounce_time)){	
				button_struct->_state = isReleased;
				return_status = button_struct->_state;
				button_struct->_previous_state = button_off;
			} 
			else{	//nothing to report, although there was a change in button state
				return_status =  stateChanged;
			}
		}
	}
	else{	// button is in the same state than before
		// is button currently pressed?
		if(state == button_on){	// state = button_on, prevous state = button_on
			// is button pressed more than long_press_time?
			if(HAL_GetTick() >= (button_struct->_on_press_time + button_struct->long_press_time)){	
				button_struct->_state = isPressedLong;
				return_status = button_struct->_state;
			} 
			else{	
				// is button pressed more than debounce_time?
				if(HAL_GetTick() >= (button_struct->_on_press_time + button_struct->debounce_time)){	
				button_struct->_state = isPressed;
				return_status = button_struct->_state;
				}
				else{	// button is still pressed but not enough time
					return_status = noEvent; 
				}
			}
		}
		else{	// button is in the same state than before -  off state
			return_status = noEvent;
		}
	}
	
	return return_status;
}


/**********************************************************/
/*	PRIVATE FUNCTIONS */
/**********************************************************/
/* Low level GPIO read routine.
button_on - button is currently read as pressed
*/
_phy_state_t _button_state(button_struct_t *button_struct){
	if(HAL_GPIO_ReadPin(button_struct->GPIO_Port, button_struct->GPIO_Pin) == button_struct->active_state){
		return button_on;
	}
	else{
		return button_off;
	}
}

