# STM32L1
===================

Here are some functions and custom libraries to use with Standard Peripheral Drivers. 
All examples were tested with STM32L100-Discovery board. 

## 1. GPIO: initialize GPIO with single function (e.g. without creating and filling gpio structure).
Example: 
```
	gpio_pinSetup(GPIOC, GPIO_Pin_9, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_40MHz);
	gpio_pinSetup_AF(GPIOA, GPIO_Pin_2, GPIO_AF_TIM9, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_2MHz);
```
Works also for setting interrupt pins.
```
	gpio_pinSetup(GPIOC, GPIO_Pin_4, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_40MHz);
	gpio_pinSetup_interrupt(GPIOC, GPIO_Pin_4, EXTI_Trigger_Falling, 0, 2);		
```

## 2. MILLIS: Function for initializing systick to create Arduino-like millis function.
Example:
```
	systick_millis_init();
	millis();
	delay(50);
```

Microsecond delay added:
```
	delay_us_init();
	delay_us(50);
```

## 3. STEPPER: Stepper motor driver for 2 or 4 pin motors. 
Include functions for optimal move to selected position, home position, ...
Examples included. 

## 4. USART: Arduino-like serial print of data (integers, floats, strings, raw data, ...)
Example:
```
	UART_Init();	//Supports character RX interrupt mode.
	printStringLn("String with new line");
	printLn();	// only new line
	printNumberLn(1234567890, DEC); // BIN, HEX
	printFloatLn(123.456);
	...
```
	
## 5. LCD: Liquid Crystal Display
Example
```
	LCD_Init(2, 20);
	LCD_PrintString(1, 1, "Damogran Labs");
	LCD_PrintFloat(1, 1, 12.0753);
	LCD_PrintNumber(1, 12, 10);
	LCD_CreateChar(0, custom_char);
	LCD_PutCustom(1,10, 0);
```
	
## 6. MAX11210: 24-bit ADC
Functions for reading 24-bit ADC. 


