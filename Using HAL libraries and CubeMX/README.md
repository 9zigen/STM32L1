STM32L1
===================

Here are some functions and custom libraries using HAL drivers and code generation tool CubeMX. Most of them should work out of the box. All examples were tested with STM32L100-Discovery board and CubeMX. 

1. UART: Arduino-like serial print of data (integers, floats, strings, raw data, ...)
Init UART with CubeMX and edit only _send_byte() and _receive_byte() functions according to your chosen UART driver.
Print functions:
	- printStringLn("String with new line");
	- printLn();	// only new line
	- printNumberLn(1234567890, DEC); // BIN, HEX
	- printFloatLn(123.456);
	- ...

2. LCD: Liquid Crystal Display
Use with CubeMX or without.
Example
	- LCD_Init(2, 20);
	- LCD_PrintString(0, 0, "Damogran Labs");
	- LCD_PrintFloat(1, 0, 12.0753);
	- LCD_PrintNumber(1, 12, 10);
	- LCD_CreateChar(0, custom_char);
	- LCD_PutCustom(1,10, 0);
	- ...
	
3. Rotary encoder
Use with CubeMX or without.
Example:
	- Encoder_Init(&encoder1, GPIOA, GPIO_PIN_2, GPIOA, GPIO_PIN_3);
	- Encoder_GetState(&encoder1);
	- ...
	
4. Delay us
Microsecond delay. Not really accurate delay, but good enough for simple tasks, like LCD driver.

5. Button handler
Polling button handler. It can register pressed buton, long press and buton release.
Example:
	- buttonInit(&S1_struct, S1_GPIO_Port, S1_Pin, GPIO_PIN_RESET, 30, 2000);
	- if(buttonUpdate(&S1_struct) == isPressed){
		// button was/is pressed
		}	
	

