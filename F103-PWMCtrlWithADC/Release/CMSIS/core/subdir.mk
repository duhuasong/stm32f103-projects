################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/core/core_cm3.c 

OBJS += \
./CMSIS/core/core_cm3.o 

C_DEPS += \
./CMSIS/core/core_cm3.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/core/%.o: ../CMSIS/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F1 -DSTM32F101C8Tx -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -I"C:/Users/muka/eclipse-workspace/STM32SW/F103-PWMCtrlWithADC/StdPeriph_Driver/inc" -I"C:/Users/muka/eclipse-workspace/STM32SW/F103-PWMCtrlWithADC/inc" -I"C:/Users/muka/eclipse-workspace/STM32SW/F103-PWMCtrlWithADC/CMSIS/device" -I"C:/Users/muka/eclipse-workspace/STM32SW/F103-PWMCtrlWithADC/CMSIS/core" -O3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


