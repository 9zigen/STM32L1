STM32L1
===================

Here are some functions and custom libraries for beginners. Most of them should work out of the box, but some of them were created for specific hardware, so be sure to check GPIOs and other defines. 
Contact me if there is any problems. All examples were tested with STM32L100-Discovery board and CubeMX. 

1. UART: Arduino-like serial print of data (integers, floats, strings, raw data, ...)
Init UART with CubeMX and edit only _send_byte() and _receive_byte() functions. 
Print functions:
	printStringLn("String with new line");
	printLn();	// only new line
	printNumberLn(1234567890, DEC); // BIN, HEX
	printFloatLn(123.456);
	...

2. LCD: Liquid Crystal Display
With CubeMX or without.
Example
	LCD_Init(2, 20);
	
	LCD_PrintString(0, 0, "Damogran Labs");
	LCD_PrintFloat(1, 0, 12.0753);
	LCD_PrintNumber(1, 12, 10);
	LCD_CreateChar(0, custom_char);
	LCD_PutCustom(1,10, 0);
	...
	
3. Rotary encoder
With CubeMX or without.
Example:
	Encoder_Init(&encoder1, GPIOA, GPIO_PIN_2, GPIOA, GPIO_PIN_3);
	Encoder_GetState(&encoder1);
	...
	
4. Delay us
Microsecond delay. Not really accurate, but good enough for LCD driver.


