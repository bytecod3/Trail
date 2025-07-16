################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/TFT_eSPI/Fonts/Font16.c \
../Core/TFT_eSPI/Fonts/Font32rle.c \
../Core/TFT_eSPI/Fonts/Font64rle.c \
../Core/TFT_eSPI/Fonts/Font72rle.c \
../Core/TFT_eSPI/Fonts/Font72x53rle.c \
../Core/TFT_eSPI/Fonts/Font7srle.c \
../Core/TFT_eSPI/Fonts/glcdfont.c 

OBJS += \
./Core/TFT_eSPI/Fonts/Font16.o \
./Core/TFT_eSPI/Fonts/Font32rle.o \
./Core/TFT_eSPI/Fonts/Font64rle.o \
./Core/TFT_eSPI/Fonts/Font72rle.o \
./Core/TFT_eSPI/Fonts/Font72x53rle.o \
./Core/TFT_eSPI/Fonts/Font7srle.o \
./Core/TFT_eSPI/Fonts/glcdfont.o 

C_DEPS += \
./Core/TFT_eSPI/Fonts/Font16.d \
./Core/TFT_eSPI/Fonts/Font32rle.d \
./Core/TFT_eSPI/Fonts/Font64rle.d \
./Core/TFT_eSPI/Fonts/Font72rle.d \
./Core/TFT_eSPI/Fonts/Font72x53rle.d \
./Core/TFT_eSPI/Fonts/Font7srle.d \
./Core/TFT_eSPI/Fonts/glcdfont.d 


# Each subdirectory must supply rules for building sources it contributes
Core/TFT_eSPI/Fonts/%.o Core/TFT_eSPI/Fonts/%.su Core/TFT_eSPI/Fonts/%.cyclo: ../Core/TFT_eSPI/Fonts/%.c Core/TFT_eSPI/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-TFT_eSPI-2f-Fonts

clean-Core-2f-TFT_eSPI-2f-Fonts:
	-$(RM) ./Core/TFT_eSPI/Fonts/Font16.cyclo ./Core/TFT_eSPI/Fonts/Font16.d ./Core/TFT_eSPI/Fonts/Font16.o ./Core/TFT_eSPI/Fonts/Font16.su ./Core/TFT_eSPI/Fonts/Font32rle.cyclo ./Core/TFT_eSPI/Fonts/Font32rle.d ./Core/TFT_eSPI/Fonts/Font32rle.o ./Core/TFT_eSPI/Fonts/Font32rle.su ./Core/TFT_eSPI/Fonts/Font64rle.cyclo ./Core/TFT_eSPI/Fonts/Font64rle.d ./Core/TFT_eSPI/Fonts/Font64rle.o ./Core/TFT_eSPI/Fonts/Font64rle.su ./Core/TFT_eSPI/Fonts/Font72rle.cyclo ./Core/TFT_eSPI/Fonts/Font72rle.d ./Core/TFT_eSPI/Fonts/Font72rle.o ./Core/TFT_eSPI/Fonts/Font72rle.su ./Core/TFT_eSPI/Fonts/Font72x53rle.cyclo ./Core/TFT_eSPI/Fonts/Font72x53rle.d ./Core/TFT_eSPI/Fonts/Font72x53rle.o ./Core/TFT_eSPI/Fonts/Font72x53rle.su ./Core/TFT_eSPI/Fonts/Font7srle.cyclo ./Core/TFT_eSPI/Fonts/Font7srle.d ./Core/TFT_eSPI/Fonts/Font7srle.o ./Core/TFT_eSPI/Fonts/Font7srle.su ./Core/TFT_eSPI/Fonts/glcdfont.cyclo ./Core/TFT_eSPI/Fonts/glcdfont.d ./Core/TFT_eSPI/Fonts/glcdfont.o ./Core/TFT_eSPI/Fonts/glcdfont.su

.PHONY: clean-Core-2f-TFT_eSPI-2f-Fonts

