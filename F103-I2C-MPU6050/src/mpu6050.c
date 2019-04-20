/*
 * mpu6050.c
 *
 *  Created on: 17 Nis 2019
 *  Author: Mustafa Kabakçý
 *  @brief	 B6 - MPU6050 SCL
 *  @brief	 B7 - MPU6050 SDA
 */

#include "mpu6050.h"
#include "i2c.h"

extern uint8_t received[14];

/**
 * @brief  : Reading temperature value
 * @param  : None
 * @retval : float - temp
 */
float MPU6050Temp(void)
{
	int16_t tempTemp = 0;

	i2cRead(MPU6050Address, TEMP_OUT_H, 2);
	tempTemp |= received[0] << 8 | received[1];
	float temp = ((float)tempTemp / 340.0) + 36.53;

	return temp;
}

#if !(SELECT_FUNCTION)


float accel[3], gyro[3];

/**
 * @brief  : Reading accelerometer value
 * @param  : None
 * @retval : None - Read values from global variable accel[3]
 */
void MPU6050Accel(void)
{
	int16_t accelRaw[3] = {0};

	i2cRead(MPU6050Address, ACCEL_XOUT_H, 2);
	accelRaw[0] |= received[0] << 8 | received[1];
	accelRaw[0] = ~accelRaw[0] + 1;
	accel[0] = (float)accelRaw[0] / 16384.0;

	i2cRead(MPU6050Address, ACCEL_YOUT_H, 2);
	accelRaw[1] |= received[0] << 8 | received[1];
	accelRaw[1] = ~accelRaw[1] + 1;
	accel[1] = (float)accelRaw[1] / 16384.0;

	i2cRead(MPU6050Address, ACCEL_ZOUT_H, 2);
	accelRaw[2] |= received[0] << 8 | received[1];
	accelRaw[2] = ~accelRaw[2] + 1;
	accel[2] = (float)accelRaw[2] / 16384.0;
}

/**
 * @brief  : Reading gyroscope value
 * @param  : None
 * @retval : None - Read values from global variable gyro[3]
 */
void MPU6050Gyro(void)
{
	int16_t gyroRaw[3] = {0};

	i2cRead(MPU6050Address, GYRO_XOUT_H, 2);
	gyroRaw[0] |= received[0] << 8 | received[1];
	gyroRaw[0] = ~gyroRaw[0] + 1;
	gyro[0] = (float)gyroRaw[0] / 131.0;

	i2cRead(MPU6050Address, GYRO_YOUT_H, 2);
	gyroRaw[1] |= received[0] << 8 | received[1];
	gyroRaw[1] = ~gyroRaw[1] + 1;
	gyro[1] = (float)gyroRaw[1] / 131.0;

	i2cRead(MPU6050Address, GYRO_ZOUT_H, 2);
	gyroRaw[2] |= received[0] << 8 | received[1];
	gyroRaw[2] = ~gyroRaw[2] + 1;
	gyro[2] = (float)gyroRaw[2] / 131.0;
}

#endif

#if SELECT_FUNCTION

/**
 * @brief  : Reading accelerometer x-axis value
 * @param  : None
 * @retval : Float - accelX
 */
float MPU6050AccelX(void)
{
	int16_t accelRaw = 0;

	i2cRead(MPU6050Address, ACCEL_XOUT_H, 2);
	accelRaw |= received[0] << 8 | received[1];
	accelRaw = ~accelRaw + 1;
	float accelX = (float)accelRaw / 16384.0;

	return accelX;
}


/**
 * @brief  : Reading accelerometer y-axis value
 * @param  : None
 * @retval : Float - accelY
 */
float MPU6050AccelY(void)
{
	int16_t accelRaw = 0;

	i2cRead(MPU6050Address, ACCEL_YOUT_H, 2);
	accelRaw |= received[0] << 8 | received[1];
	accelRaw = ~accelRaw + 1;
	float accelY = (float)accelRaw / 16384.0;

	return accelY;
}


/**
 * @brief  : Reading accelerometer z-axis value
 * @param  : None
 * @retval : Float - accelZ
 */
float MPU6050AccelZ(void)
{
	int16_t accelRaw = 0;

	i2cRead(MPU6050Address, ACCEL_ZOUT_H, 2);
	accelRaw |= received[0] << 8 | received[1];
	accelRaw = ~accelRaw + 1;
	float accelZ = (float)accelRaw / 16384.0;

	return accelZ;
}


/**
 * @brief  : Reading gyroscope x-axis value
 * @param  : None
 * @retval : Float - gyroX
 */
float MPU6050GyroX(void)
{
	int16_t gyroRaw = 0;

	i2cRead(MPU6050Address, GYRO_XOUT_H, 2);
	gyroRaw |= received[0] << 8 | received[1];
	gyroRaw = ~gyroRaw + 1;
	float gyroX = (float)gyroRaw / 131.0;

	return gyroX;
}


/**
 * @brief  : Reading gyroscope y-axis value
 * @param  : None
 * @retval : Float - gyroY
 */
float MPU6050GyroY(void)
{
	int16_t gyroRaw = 0;

	i2cRead(MPU6050Address, GYRO_YOUT_H, 2);
	gyroRaw |= received[0] << 8 | received[1];
	gyroRaw = ~gyroRaw + 1;
	float gyroY = (float)gyroRaw / 131.0;

	return gyroY;
}


/**
 * @brief  : Reading gyroscope z-axis value
 * @param  : None
 * @retval : Float - gyroZ
 */
float MPU6050GyroZ(void)
{
	int16_t gyroRaw = 0;

	i2cRead(MPU6050Address, GYRO_ZOUT_H, 2);
	gyroRaw |= received[0] << 8 | received[1];
	gyroRaw = ~gyroRaw + 1;
	float gyroZ = (float)gyroRaw / 131.0;

	return gyroZ;
}

#endif
