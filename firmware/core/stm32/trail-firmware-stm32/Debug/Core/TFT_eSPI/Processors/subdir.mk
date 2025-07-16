################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/TFT_eSPI/Processors/TFT_eSPI_STM32.c 

OBJS += \
./Core/TFT_eSPI/Processors/TFT_eSPI_STM32.o 

C_DEPS += \
./Core/TFT_eSPI/Processors/TFT_eSPI_STM32.d 


# Each subdirectory must supply rules for building sources it contributes
Core/TFT_eSPI/Processors/%.o Core/TFT_eSPI/Processors/%.su Core/TFT_eSPI/Processors/%.cyclo: ../Core/TFT_eSPI/Processors/%.c Core/TFT_eSPI/Processors/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-TFT_eSPI-2f-Processors

clean-Core-2f-TFT_eSPI-2f-Processors:
	-$(RM) ./Core/TFT_eSPI/Processors/TFT_eSPI_STM32.cyclo ./Core/TFT_eSPI/Processors/TFT_eSPI_STM32.d ./Core/TFT_eSPI/Processors/TFT_eSPI_STM32.o ./Core/TFT_eSPI/Processors/TFT_eSPI_STM32.su

.PHONY: clean-Core-2f-TFT_eSPI-2f-Processors

