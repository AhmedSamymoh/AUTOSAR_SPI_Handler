################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../COM/MCAL/SPI/src/Spi.c \
../COM/MCAL/SPI/src/Spi_Cfg.c 

OBJS += \
./COM/MCAL/SPI/src/Spi.o \
./COM/MCAL/SPI/src/Spi_Cfg.o 

C_DEPS += \
./COM/MCAL/SPI/src/Spi.d \
./COM/MCAL/SPI/src/Spi_Cfg.d 


# Each subdirectory must supply rules for building sources it contributes
COM/MCAL/SPI/src/%.o COM/MCAL/SPI/src/%.su COM/MCAL/SPI/src/%.cyclo: ../COM/MCAL/SPI/src/%.c COM/MCAL/SPI/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"O:/02. Courses/STM32AMGAD/StmCube_Workspace/SPIHandler_Project/SPI/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-COM-2f-MCAL-2f-SPI-2f-src

clean-COM-2f-MCAL-2f-SPI-2f-src:
	-$(RM) ./COM/MCAL/SPI/src/Spi.cyclo ./COM/MCAL/SPI/src/Spi.d ./COM/MCAL/SPI/src/Spi.o ./COM/MCAL/SPI/src/Spi.su ./COM/MCAL/SPI/src/Spi_Cfg.cyclo ./COM/MCAL/SPI/src/Spi_Cfg.d ./COM/MCAL/SPI/src/Spi_Cfg.o ./COM/MCAL/SPI/src/Spi_Cfg.su

.PHONY: clean-COM-2f-MCAL-2f-SPI-2f-src

