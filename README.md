STM32L100-DISCOVERY
===================

Here are some functions and custom libraries for beginners. Most of them should work out of the box, but some of them were created for specific hardware, so be sure to check GPIOs and other defines. 
Contact me for any problems. 

1. GPIO: initialize GPIO wiht single function (e.g. without creating and filling gpio structure).
Example: 
  gpio_pinSetup(GPIOC, LED1, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_Speed_2MHz);
  gpio_pinSetup_AF(GPIOC, CAP1_INPUT_PIN, GPIO_AF_TIM3, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_10MHz);
Works also for setting interrupt pins.

2. MILLIS: Function for initialize TIM2 or systick to create Arduino-like millis function. 
Example:
  systick_millis_init();

3. STEPPER: Stepper motor driver for 2 or 4 pin motors. 
Include functions for optimal move to selected position, home position, ...
Examples included. 

4. USART: Arduino-like serial print of data (integers, floats, strings, raw data, ...)
Example:
  init_usart(USART1, GPIOA, 9600); 
  init_usart_RXint(USART1, GPIOA, 9600, 2, 2);
Supports character RX interrupt mode.

5. MAX11210: 24-bit ADC
Functions for reading 24-bit ADC. 


