/*
 * mpu6050.h
 *
 *  Created on: 17 Nis 2019
 *  Author: Mustafa Kabakçý
 *  @brief	 B6 - MPU6050 SCL
 *  @brief	 B7 - MPU6050 SDA
 */

#ifndef MPU6050_H_
#define MPU6050_H_

/*************************************************/
/* Macros with reference to MPU6050 Register Map */
/*-----------------------------------------------*/

#define MPU6050Address 0x68
#define PWR_MGMT_1 	   0x6B
#define WHO_AM_I 	   0x75
#define MPU6050_WAKEUP 0x00
#define MPU6050_SLEEP  0x40
#define TEMP_OUT_H	   0x41
#define TEMP_OUT_L	   0x42
#define ACCEL_XOUT_H   0x3B
#define ACCEL_XOUT_L   0x3C
#define ACCEL_YOUT_H   0x3D
#define ACCEL_YOUT_L   0x3E
#define ACCEL_ZOUT_H   0x3F
#define ACCEL_ZOUT_L   0x40
#define GYRO_XOUT_H	   0x43
#define GYRO_XOUT_L	   0x44
#define GYRO_YOUT_H	   0x45
#define GYRO_YOUT_L	   0x46
#define GYRO_ZOUT_H	   0x47
#define GYRO_ZOUT_L	   0x48
#define SMPRT_DIV	   0x19


/**
 * @brief  : Reading temperature value
 * @param  : None
 * @retval : float - temp
 */
float MPU6050Temp(void);


/*
 * Reading 3 axis and returning them like float *axis[] needs
 * memory allocation and deallocation because of that i use
 * global variables. If someone needs more space-friendly code
 * i wrote another functions on purpose that maybe needed.
 */
#define SELECT_FUNCTION 1

#if !(SELECT_FUNCTION)

/**
 * @brief  : Reading accelerometer value
 * @param  : None
 * @retval : None - Read values from global variable accel[3]
 */
void MPU6050Accel(void);


/**
 * @brief  : Reading gyroscope value
 * @param  : None
 * @retval : None - Read values from global variable gyro[3]
 */
void MPU6050Gyro(void);

#endif


#if SELECT_FUNCTION

/**
 * @brief  : Reading accelerometer x-axis value
 * @param  : None
 * @retval : Float - accelX
 */
float MPU6050AccelX(void);


/**
 * @brief  : Reading accelerometer y-axis value
 * @param  : None
 * @retval : Float - accelY
 */
float MPU6050AccelY(void);


/**
 * @brief  : Reading accelerometer z-axis value
 * @param  : None
 * @retval : Float - accelZ
 */
float MPU6050AccelZ(void);


/**
 * @brief  : Reading gyroscope x-axis value
 * @param  : None
 * @retval : Float - gyroX
 */
float MPU6050GyroX(void);


/**
 * @brief  : Reading gyroscope y-axis value
 * @param  : None
 * @retval : Float - gyroY
 */
float MPU6050GyroY(void);


/**
 * @brief  : Reading gyroscope z-axis value
 * @param  : None
 * @retval : Float - gyroZ
 */
float MPU6050GyroZ(void);

#endif

#endif /* MPU6050_H_ */
