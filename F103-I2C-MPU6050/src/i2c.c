/*
 * i2c.c
 *
 *  Created on: 17 Nis 2019
 *  Author: Mustafa Kabakçý
 *  @brief	 B6 - I2C1 SCL
 *  @brief	 B7 - I2C1 SDA
 */

#include "i2c.h"
#include "stm32f10x.h"

/*
 * @brief	delay function for purpose
 * @param	delay	: integer value it's like millisecond
 * retval	None
 */
void delayms(uint32_t delay)
{
	for(uint32_t j = 0; j < delay; j++)
	{
		uint16_t i = 0;
		while(i < 6000)
		{
			i++;
		}
	}

}


/*
 * @brief	I2C read function through I2C1 channel
 * @param	devAddr : Device address which device to communicate
 * @param	regAddr	: Register address which data want to read
 * @param	size	: How many bytes that wants to read
 * @retval	None - Reading values are at the global variable received[14]
 */
void i2cRead(uint8_t devAddr, uint8_t regAddr, uint8_t size)
{
	//I2C1->OAR1 |= ( 0x68 << 1);

	// Set ACK and Start then control start bit
	I2C1->CR1 |= I2C_CR1_START | I2C_CR1_ACK;
	while(!(I2C1->SR1 & I2C_SR1_SB));

	// say "hello, i want to write" then control if address is matched
	I2C1->DR = (devAddr << 1 | 0);
	while(!(I2C1->SR1 & I2C_SR1_ADDR)| !(I2C1->SR2 & I2C_SR2_BUSY));

	// sending to data address that i want to read
	I2C1->DR = regAddr;
	while(!(I2C1->SR1 & I2C_SR1_TXE));

	// restart required for changing mode to reading mode
	I2C1->CR1 |= I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB));

	// say "hello, i want to read data from data address that i just send" then control if address is matched
	I2C1->DR = (devAddr << 1 | 1);
	while(!(I2C1->SR1 & I2C_SR1_ADDR) | !(I2C1->SR2 & I2C_SR2_BUSY));

	// this part is needed for reading multiple bytes
	if(size > 1)
	{
		for(uint8_t i = 0; i < size - 1; i++)
		{
			while(!(I2C1->SR1 & I2C_SR1_RXNE));
			received[i] = I2C1->DR;
		}
	}

	// stop communication and read last byte
	I2C1->CR1 &= ~I2C_CR1_ACK;
	I2C1->CR1 |= I2C_CR1_STOP;
	while(I2C1->CR1 & I2C_CR1_STOP);
	received[size - 1] = I2C1->DR;
	delayms(1);
}


/*
 * @brief	I2C write function through I2C1 channel
 * @param	devAddr : Device address which device to communicate
 * @param	regAddr	: Register address which data want to write
 * @param	data	: Writing data to devAddr/regAddr
 * @retval	None
 */
void i2cWrite(uint8_t devAddr, uint8_t regAddr, uint8_t data)
{
	// Set ACK and Start then control start bit
	I2C1->CR1 |= I2C_CR1_START | I2C_CR1_ACK;
	while(!(I2C1->SR1 & I2C_SR1_SB));

	// say "hello, i want to write" then control if address is matched
	I2C1->DR = (devAddr << 1 | 0);
	while(!(I2C1->SR1 & I2C_SR1_ADDR)| !(I2C1->SR2 & I2C_SR2_BUSY));

	// sending to data address that i want to read
	I2C1->DR = regAddr;
	while(!(I2C1->SR1 & I2C_SR1_TXE));

	// sending to data that i want to read
	I2C1->DR = data;
	while(!(I2C1->SR1 & I2C_SR1_TXE));

	// stop communication and read last byte
	I2C1->CR1 &= ~I2C_CR1_ACK;
	I2C1->CR1 |= I2C_CR1_STOP;
	while(I2C1->CR1 & I2C_CR1_STOP);
	delayms(1);
}


/*
 * @brief	Initializes the I2C1
 * @param	None
 * @retval	None
 */
void i2cInitialization(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	// GPIO Settings | Alternate Function | Open Drain | 50MHz
	GPIOB->CRL |= GPIO_CRL_CNF6 | GPIO_CRL_MODE6;
	GPIOB->CRL |= GPIO_CRL_CNF7 | GPIO_CRL_MODE7;

	delayms(100);

	// I2C Initialization
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	I2C1->CR2 |= 50; // 50MHz
	//I2C1->CCR |= I2C_CCR_FS;
	I2C1->CCR |= 180;	// 100 kHz
	//I2C1->CCR |= 45;	// 400 kHz
	I2C1->TRISE |= 51;
	I2C1->CR1 |= I2C_CR1_PE;

	delayms(100);
}
