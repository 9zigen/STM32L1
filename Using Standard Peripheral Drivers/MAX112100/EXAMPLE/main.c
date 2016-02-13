/**
  ******************************************************************************
  * @file    Project/STM32L1xx_StdPeriph_Templates/main.c 
  * @author  Domen Jurkovic
  * @version V1
  * @date    05-Nov-2015
  * @brief   Main program body
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SHIFT	5
#define AV_RATE	10
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

int main(void)
{
	int32_t result;
	int32_t av_result;
	uint8_t i = 0;
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	systick_millis_init();	
	UART_Init();
	
	//LEDS
	gpio_pinSetup(GPIOC, GPIO_Pin_8, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_40MHz);
	GPIO_ResetBits(GPIOC, GPIO_Pin_8);
	
	MAX11210_init();
	
	printLn();
	printStringLn("------------------------------------------------");
	printStringLn("System initialized. Initialized jebote!");
		
	MAX11210_set_meas_mode(MODE_SINGLE);
	
	for(i = 0; i < 5; i ++){
		MAX11210_start_meas(MEASURE_10_SPS);
		MAX11210_read_result();
	}
	
	MAX11210_calibration();

	printString("\t SCOC:");
	printNumberLn( MAX11210_read_reg(SCOC), DEC);
	printString( "\tSOC:");
	printNumberLn(MAX11210_read_reg(SOC), DEC);
	printString("\t SCGC:");
	printNumberLn(MAX11210_read_reg(SCGC), DEC);
	printString("\t SGC:");
	printNumberLn(MAX11210_read_reg(SGC), DEC);
		
	while (1)
  {
		for(i = 0; i < AV_RATE; i++){
			MAX11210_start_meas(MEASURE_10_SPS);	
			result = MAX11210_read_result() & 0x00FFFFFF;
			if((result >> 23) == 0){
			}
			else{		//negativna cifra
				result = result << 8;
				result  = ~result + 1;
				result  = result >> 8;
				
				result = -result;
			}
			av_result += result;
			result=0;
		}
		
		av_result = av_result / AV_RATE ;
		printNumberLn(av_result >> SHIFT, DEC);
		av_result = 0;
		
		//printString(USART1, "DATA: ");
		
		/*
		MAX11210_start_meas(MEASURE_10_SPS);
		result = MAX11210_read_result() & 0x00FFFFFF;
		if((result >> 23) == 0){
			printNumberLn(USART1, result >> SHIFT, DEC);	//pozitivna cifra
		}
		else{		//negativna cifra
			result = result << 8;
			result  = ~result + 1;
			result  = result >> 8;
			printNumberLn(USART1, -result >> SHIFT, DEC);
		}*/
		
		//printNumberLn(USART1, MAX11210_meas_status(), DEC);
		
  }
}
/**
  * @}
  */







