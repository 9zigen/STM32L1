/*
  function examples
*/

void gpioSetup()
{
	// LEDS
	gpio_pinSetup(GPIOC, LED1, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_Speed_2MHz);
	gpio_pinSetup(GPIOC, LED2, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_Speed_2MHz);
	
	gpio_pinSetup(GPIOA, REED_RELAY, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_Speed_10MHz);
	
	// Timer TIM3 gpio AF config
	gpio_pinSetup_AF(GPIOC, CAP1_INPUT_PIN, GPIO_AF_TIM3, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_10MHz);

  // ADC_IN15 on pin PC5
  gpio_pinSetup(GPIOC, GPIO_Pin_5, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_2MHz);    

	//Set GPIO OUTPUT default values
  GPIO_ResetBits(GPIOC, LED1);
	GPIO_SetBits(GPIOC, LED1);
}
