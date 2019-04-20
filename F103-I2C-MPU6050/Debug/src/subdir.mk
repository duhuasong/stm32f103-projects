################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/i2c.c \
../src/main.c \
../src/mpu6050.c \
../src/syscalls.c \
../src/system_stm32f10x.c 

OBJS += \
./src/i2c.o \
./src/main.o \
./src/mpu6050.o \
./src/syscalls.o \
./src/system_stm32f10x.o 

C_DEPS += \
./src/i2c.d \
./src/main.d \
./src/mpu6050.d \
./src/syscalls.d \
./src/system_stm32f10x.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F1 -DSTM32F101C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -I"C:/Users/muka/eclipse-workspace/STM32SW/F103-I2C-MPU6050/StdPeriph_Driver/inc" -I"C:/Users/muka/eclipse-workspace/STM32SW/F103-I2C-MPU6050/inc" -I"C:/Users/muka/eclipse-workspace/STM32SW/F103-I2C-MPU6050/CMSIS/device" -I"C:/Users/muka/eclipse-workspace/STM32SW/F103-I2C-MPU6050/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


