################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SPI/src/Spi.c 

OBJS += \
./SPI/src/Spi.o 

C_DEPS += \
./SPI/src/Spi.d 


# Each subdirectory must supply rules for building sources it contributes
SPI/src/%.o SPI/src/%.su SPI/src/%.cyclo: ../SPI/src/%.c SPI/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-SPI-2f-src

clean-SPI-2f-src:
	-$(RM) ./SPI/src/Spi.cyclo ./SPI/src/Spi.d ./SPI/src/Spi.o ./SPI/src/Spi.su

.PHONY: clean-SPI-2f-src

