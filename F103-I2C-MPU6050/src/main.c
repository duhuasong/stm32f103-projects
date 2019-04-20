/**
  ******************************************************************************
  * @file    main.c
  * @author  Mustafa Kabakçý
  * @version V1.0
  * @date    30-March-2019
  * @brief   Read MPU6050 sensor data through I2C
  ******************************************************************************
*/

#include "i2c.h"
#include "mpu6050.h"

#if !(SELECT_FUNCTION)
extern float accel[3], gyro[3];
float temp;
#endif

#if SELECT_FUNCTION
float accx, gyrz, temp;
#endif

int main(void)
{
	// Initializes I2C1 pins
	i2cInitialization();

	// MPU6050 is at sleep mode by default
	i2cWrite(MPU6050Address, PWR_MGMT_1, MPU6050_WAKEUP);

	while(1)
	{
		// Reading some values
		delayms(1000);

		#if !(SELECT_FUNCTION)
		MPU6050Accel();
		MPU6050Gyro();
		temp = MPU6050Temp();
		#endif

		#if SELECT_FUNCTION
		accx = MPU6050AccelX();
		gyrz = MPU6050GyroZ();
		temp = MPU6050Temp();
		#endif
	}
}
