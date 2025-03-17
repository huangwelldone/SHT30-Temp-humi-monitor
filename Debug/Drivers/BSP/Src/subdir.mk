################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Src/bsp_sht30.c \
../Drivers/BSP/Src/font.c \
../Drivers/BSP/Src/oled.c 

OBJS += \
./Drivers/BSP/Src/bsp_sht30.o \
./Drivers/BSP/Src/font.o \
./Drivers/BSP/Src/oled.o 

C_DEPS += \
./Drivers/BSP/Src/bsp_sht30.d \
./Drivers/BSP/Src/font.d \
./Drivers/BSP/Src/oled.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Src/%.o Drivers/BSP/Src/%.su Drivers/BSP/Src/%.cyclo: ../Drivers/BSP/Src/%.c Drivers/BSP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Src

clean-Drivers-2f-BSP-2f-Src:
	-$(RM) ./Drivers/BSP/Src/bsp_sht30.cyclo ./Drivers/BSP/Src/bsp_sht30.d ./Drivers/BSP/Src/bsp_sht30.o ./Drivers/BSP/Src/bsp_sht30.su ./Drivers/BSP/Src/font.cyclo ./Drivers/BSP/Src/font.d ./Drivers/BSP/Src/font.o ./Drivers/BSP/Src/font.su ./Drivers/BSP/Src/oled.cyclo ./Drivers/BSP/Src/oled.d ./Drivers/BSP/Src/oled.o ./Drivers/BSP/Src/oled.su

.PHONY: clean-Drivers-2f-BSP-2f-Src

