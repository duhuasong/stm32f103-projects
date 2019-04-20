/*
 * i2c.h
 *
 *  Created on: 17 Nis 2019
 *  Author: Mustafa Kabakçý
 *  @brief	 B6 - I2C1 SCL
 *  @brief	 B7 - I2C1 SDA
 */

#ifndef I2C_H_
#define I2C_H_

#include "stdint.h"

uint8_t received[14];

/*
 * @brief	Initializes the I2C1
 * @param	None
 * @retval	None
 */
void i2cInitialization(void);


/*
 * @brief	I2C read function through I2C1 channel
 * @param	devAddr : Device address which device to communicate
 * @param	regAddr	: Register address which data want to read
 * @param	size	: How many bytes that wants to read
 * @retval	None - Reading values are at the global variable received[14]
 */
void i2cRead(uint8_t devAddr, uint8_t regAddr, uint8_t size);


/*
 * @brief	I2C write function through I2C1 channel
 * @param	devAddr : Device address which device to communicate
 * @param	regAddr	: Register address which data want to write
 * @param	data	: Writing data to devAddr/regAddr
 * @retval	None
 */
void i2cWrite(uint8_t devAddr, uint8_t regAddr, uint8_t data);

/*
 * @brief	delay function for purpose
 * @param	delay	: integer value it's like millisecond
 * retval	None
 */
void delayms(uint32_t delay);

#endif /* I2C_H_ */
