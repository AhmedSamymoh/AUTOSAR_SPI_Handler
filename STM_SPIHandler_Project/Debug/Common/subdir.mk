################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Common/det.c 

OBJS += \
./Common/det.o 

C_DEPS += \
./Common/det.d 


# Each subdirectory must supply rules for building sources it contributes
Common/%.o Common/%.su Common/%.cyclo: ../Common/%.c Common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"O:/02. Courses/STM32AMGAD/StmCube_Workspace/SPIHandler_Project/SPI/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Common

clean-Common:
	-$(RM) ./Common/det.cyclo ./Common/det.d ./Common/det.o ./Common/det.su

.PHONY: clean-Common

