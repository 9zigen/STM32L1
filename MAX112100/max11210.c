/**
  ******************************************************************************
  * @file    max11210.c
   * @author  Domen Jurkovic
  * @version V1.0
  * @date    18-Nov-2015
  * @brief   This file provides functions for MAX11210
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "max11210.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
	SPI SETUP FUNCTION
	SPI2: 
		NSS:	PB12
		SCK:	PB13
		MISO:	PB14
		MOSI:	PB15
		
*/
void SPI_init(void){
	SPI_InitTypeDef SPI_InitStruct ;
	
	SPI_I2S_DeInit(SPI2);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
	gpio_pinSetup(MAX11210_SPI_BANK, MAX11210_SPI_NSS, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_40MHz);
	GPIO_SetBits(MAX11210_SPI_BANK, MAX11210_SPI_NSS);
	
	gpio_pinSetup_AF(MAX11210_SPI_BANK, MAX11210_SPI_SCK, GPIO_AF_SPI2, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_40MHz);
	gpio_pinSetup_AF(MAX11210_SPI_BANK, MAX11210_SPI_MISO, GPIO_AF_SPI2, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_40MHz);
	gpio_pinSetup_AF(MAX11210_SPI_BANK, MAX11210_SPI_MOSI, GPIO_AF_SPI2, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_40MHz);

	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA =SPI_CPHA_1Edge; 
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStruct);
	
	SPI_Cmd(SPI2, ENABLE);
}

void MAX11210_init(void){
	SPI_init();	
	
	//AD GPIO 1
	gpio_pinSetup(AD_GPIO1_BANK, AD_GPIO1, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_Speed_40MHz);
	//AD GPIO 2
	//gpio_pinSetup(AD_GPIO1_BANK, AD_GPIO2, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_Speed_40MHz);
	//AD GPIO 3
	//gpio_pinSetup(AD_GPIO1_BANK, AD_GPIO3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_Speed_40MHz);
	//AD GPIO 4
	//gpio_pinSetup(AD_GPIO1_BANK, AD_GPIO4, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_Speed_40MHz);
	
	MAX11210_send_command(POWER_DOWN);
	delay(300);
	
	MAX11210_write_reg(CTRL1, 0x1A, 0, 0);
	MAX11210_write_reg(CTRL2, 0xFF, 0, 0);
	
	MAX11210_write_reg(CTRL3, 0x00, 0, 0);	//	NOSYSG NOSYSO NOSCG NOSCO = 0; GAIN = 1;
	MAX11210_write_reg(SOC, 0x0, 0x00, 0x00);
	MAX11210_write_reg(SGC, 0x00, 0x00, 0x00);
	MAX11210_write_reg(SCOC, 0x00, 0x00, 0x00);
	MAX11210_write_reg(SCGC, 0x00, 0x00, 0x00);
	//MAX11210_write_reg(CTRL3, 0x1E, 0, 0);	//	NOSYSG NOSYSO NOSCG NOSCO = 1; GAIN = 1;
	MAX11210_write_reg(CTRL3, 0x1E, 0, 0);	//	NOSYSG NOSYSO NOSCG NOSCO = 1; GAIN = 16;
}
/*
	Read 8 or 24 bit register.
	8bit reg:	STAT1, CTRL1, CTRL2, CTRL3
	24bit reg:	DATA, SOC, SGC, SCOC, SCGC
*/
uint32_t MAX11210_read_reg(uint8_t reg){
	uint8_t read_command = 0xC1;
	uint32_t register_value = 0;
	
	read_command |= (reg << 1);
	GPIO_ResetBits(MAX11210_SPI_BANK, MAX11210_SPI_NSS);
	
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);	//	Wait until the transmit buffer is empty
	SPI_I2S_SendData(SPI2, read_command);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);	//	Wait to receive a byte
	SPI_I2S_ReceiveData(SPI2);	// received dummy byte?
	
	if((reg == STAT1) | (reg == CTRL1) | (reg == CTRL2) | (reg == CTRL3)){	// read 1 byte
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);	//	Wait until the transmit buffer is empty
		SPI_I2S_SendData(SPI2, 0);	//send dummy byte
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);	//wait to receive a byte
		register_value = SPI_I2S_ReceiveData(SPI2);
		
		//register_value = (uint8_t) (~register_value + 1);
	}
	else{	// read 3 bytes
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);	//	Wait until the transmit buffer is empty
		SPI_I2S_SendData(SPI2, 0);	//send dummy byte
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);	//wait to receive a byte
		register_value = SPI_I2S_ReceiveData(SPI2) << 16;
		
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);	//	Wait until the transmit buffer is empty
		SPI_I2S_SendData(SPI2, 0);	//send dummy byte
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);	//wait to receive a byte
		register_value |= SPI_I2S_ReceiveData(SPI2) << 8;
		
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);	//	Wait until the transmit buffer is empty
		SPI_I2S_SendData(SPI2, 0);	//send dummy byte
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);	//wait to receive a byte
		register_value |= SPI_I2S_ReceiveData(SPI2);
	}
	GPIO_SetBits(MAX11210_SPI_BANK, MAX11210_SPI_NSS);
	
	return register_value;
}

/*
	Write 8 or 24 bit register.
	8bit reg: 	CTRL1, CTRL2, CTRL3
	24bit reg:	SOC, SGC, SCOC, SCGC	
*/
void MAX11210_write_reg(uint8_t reg, uint8_t reg_val_HSB, uint8_t reg_val_MSB, uint8_t reg_val_LSB){
	uint8_t write_command = 0xC0;
		
	write_command |= (reg << 1);
	
	GPIO_ResetBits(MAX11210_SPI_BANK, MAX11210_SPI_NSS);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);	//	Wait until the transmit buffer is empty
	SPI_I2S_SendData(SPI2, write_command);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);	//	Wait to receive a byte
	SPI_I2S_ReceiveData(SPI2);	// received dummy byte?
	
	if((reg == STAT1) | (reg == CTRL1) | (reg == CTRL2) | (reg == CTRL3)){	// read 1 byte
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);	//	Wait until the transmit buffer is empty
		SPI_I2S_SendData(SPI2, reg_val_HSB);
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);	//	Wait to receive a byte
		SPI_I2S_ReceiveData(SPI2);	// received dummy byte?
		
	}
	else{
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);	//	Wait until the transmit buffer is empty
		SPI_I2S_SendData(SPI2, reg_val_HSB);
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);	//	Wait to receive a byte
		SPI_I2S_ReceiveData(SPI2);	// received dummy byte?
		
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);	//	Wait until the transmit buffer is empty
		SPI_I2S_SendData(SPI2, reg_val_MSB);
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);	//	Wait to receive a byte
		SPI_I2S_ReceiveData(SPI2);	// received dummy byte?
		
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);	//	Wait until the transmit buffer is empty
		SPI_I2S_SendData(SPI2, reg_val_LSB);
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);	//	Wait to receive a byte
		SPI_I2S_ReceiveData(SPI2);	// received dummy byte?
	}
	
	GPIO_SetBits(MAX11210_SPI_BANK, MAX11210_SPI_NSS);
}

/*
	Send command to MAX11210.
	Commands: 
		SELF_CALIB
		SYS_OFFSET_CALIB
		SYS_GAIN_CALIB
		POWER_DOWN

		MEASURE_1_SPS		
		MEASURE_2p5_SPS
		MEASURE_5_SPS	
		MEASURE_10_SPS
		MEASURE_15_SPS
		MEASURE_30_SPS
		MEASURE_60_SPS
		MEASURE_120_SPS
*/
void MAX11210_send_command(uint8_t command){
	GPIO_ResetBits(MAX11210_SPI_BANK, MAX11210_SPI_NSS);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);	//	Wait until the transmit buffer is empty
	SPI_I2S_SendData(SPI2, command);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);	//	Wait to receive a byte
	SPI_I2S_ReceiveData(SPI2);	// received dummy byte?
	GPIO_SetBits(MAX11210_SPI_BANK, MAX11210_SPI_NSS);
}

/*
	Calibrate MAX11210
*/
void MAX11210_calibration(){
	// clear registers
	MAX11210_write_reg(CTRL3, 0x00, 0, 0);	//	NOSYSG NOSYSO NOSCG NOSCO = 0; GAIN = 1;
	MAX11210_write_reg(SOC, 0x00, 0x00, 0x00);
	MAX11210_write_reg(SGC, 0x00, 0x00, 0x00);
	MAX11210_write_reg(SCOC, 0x00, 0x00, 0x00);
	MAX11210_write_reg(SCGC, 0x00, 0x00, 0x00);
	/*
	//GAIN = 1
	// Enable self calibration registers
	MAX11210_write_reg(CTRL3, 0x18, 0, 0);	//	NOSYSG=1, NOSYSO=1, NOSCG=0, NOSCO=0; GAIN = 1; 
	MAX11210_self_calib();	// Self-calibration
	
	// Enable system offset register
	MAX11210_write_reg(CTRL3, 0x10, 0, 0);	//	NOSYSG=1, NOSYSO=0, NOSCG=0, NOSCO=0; GAIN = 1; 
	MAX11210_sys_offset_calib();	// System-calibration offset
	
	// Enable system gain register
	MAX11210_write_reg(CTRL3, 0x00, 0, 0);	//	NOSYSG=0, NOSYSO=0, NOSCG=0, NOSCO=0; GAIN = 1; 
	MAX11210_sys_gain_calib();	// System-calibration gain
	*/
	
	//GAIN = 16
	// Enable self calibration registers
	MAX11210_write_reg(CTRL3, 0x98, 0, 0);	//	NOSYSG=1, NOSYSO=1, NOSCG=0, NOSCO=0; GAIN = 16; 
	MAX11210_self_calib();	// Self-calibration
	
	// Enable system offset register
	MAX11210_write_reg(CTRL3, 0x90, 0, 0);	//	NOSYSG=1, NOSYSO=0, NOSCG=0, NOSCO=0; GAIN = 16; 
	MAX11210_sys_offset_calib();	// System-calibration offset
	
	// Enable system gain register
	MAX11210_write_reg(CTRL3, 0x80, 0, 0);	//	NOSYSG=0, NOSYSO=0, NOSCG=0, NOSCO=0; GAIN = 16; 
	MAX11210_sys_gain_calib();	// System-calibration gain
	
}

/*
	System self calibration 
		The first level of calibration is the self-calibration where the part performs the required connections to zero and
	full scale internally. 
*/
void MAX11210_self_calib(void){
	MAX11210_send_command(SELF_CALIB);	//SCOC
	delay(300);
}

/*
	System offset calibration
		A second level of calibration is available where the user can calibrate a system zero scale and system full scale
	by presenting a zero-scale signal or a full-scale signal to the input pins and initiating a system zero scale or 
	system gain calibration command.
*/
void MAX11210_sys_offset_calib(void){
	MAX11210_send_command(SYS_OFFSET_CALIB);
	delay(300);
}

/*
	System gain calibration
		A third level of calibration allows for the user to write to the internal calibration registers through the SPI interface
	to achieve any digital offset or scaling the user requires with the following restrictions. The range of digital offset
	correction is QVREF/4. The range of digital gain correction is from 0.5 to 1.5. The resolution of offset correction is 0.5 LSB.

*/
void MAX11210_sys_gain_calib(void){
	MAX11210_send_command(SYS_GAIN_CALIB);
	delay(300);
}

/*
	Set measurement mode
	
*/
void MAX11210_set_meas_mode(uint8_t mode){
	uint8_t _mode = (uint8_t) MAX11210_read_reg(CTRL1);
	_mode &= 0xFD;	// mask CTRL1 register
	_mode |= mode;	
	MAX11210_write_reg(CTRL1, _mode, 0, 0);
}

/*
	Set measurement rate
		MEASURE_1_SPS		
		MEASURE_2p5_SPS
		MEASURE_5_SPS	
		MEASURE_10_SPS
		MEASURE_15_SPS
		MEASURE_30_SPS
		MEASURE_60_SPS
		MEASURE_120_SPS
*/
void MAX11210_start_meas(uint8_t rate){
	MAX11210_send_command(rate);
	// tole se mal precekirej
}
/*
	Read results when RDY bit in status register is 1.
		The RDY ready bit is set to 1 to indicate that a conversion result is available. Reading the DATA register resets the
	RDY bit to 0 only after another conversion has been initiated. If the DATA has not been read before another conversion
	is initiated, the RDY bit remains 1; if the DATA is read before another conversion is initiated, the RDY bit resets to 0. If
	the DATA for the previous conversion is read during a following conversion, the RDY bit is reset immediately after the
	DATA read operation has completed.

	Returns DATA register. User should check status register STAT afterwards.
*/
uint32_t MAX11210_read_result(void){
	
	while((MAX11210_read_reg(STAT1) & 0x0001) != 1){ //wait while RDY is not 1
	}
	return MAX11210_read_reg(DATA);
}

/*
	Check measure status
	Return masked status register STAT1
*/
uint8_t MAX11210_meas_status(void){
	return MAX11210_read_reg(STAT1) & 0x000C;
}



/*****	END OF FILE	****/

