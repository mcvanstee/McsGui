################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../System/FatFs/diskio.c \
../System/FatFs/ff.c \
../System/FatFs/ffsystem.c \
../System/FatFs/ffunicode.c 

OBJS += \
./System/FatFs/diskio.o \
./System/FatFs/ff.o \
./System/FatFs/ffsystem.o \
./System/FatFs/ffunicode.o 

C_DEPS += \
./System/FatFs/diskio.d \
./System/FatFs/ff.d \
./System/FatFs/ffsystem.d \
./System/FatFs/ffunicode.d 


# Each subdirectory must supply rules for building sources it contributes
System/FatFs/%.o System/FatFs/%.su System/FatFs/%.cyclo: ../System/FatFs/%.c System/FatFs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L496xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Display" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Display/ST7789" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/System" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Logging" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Image" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/System/FatFs" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/System/Hal" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Style" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGuiLib/McsGui" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGuiLib/McsGui/ExternalDisplay" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGuiLib/McsGui/Graphics" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGuiLib/McsGui/Utils" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/CustomComponents" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Views" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Views/Settings" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/ComponentExtensions" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Views/Setup" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-System-2f-FatFs

clean-System-2f-FatFs:
	-$(RM) ./System/FatFs/diskio.cyclo ./System/FatFs/diskio.d ./System/FatFs/diskio.o ./System/FatFs/diskio.su ./System/FatFs/ff.cyclo ./System/FatFs/ff.d ./System/FatFs/ff.o ./System/FatFs/ff.su ./System/FatFs/ffsystem.cyclo ./System/FatFs/ffsystem.d ./System/FatFs/ffsystem.o ./System/FatFs/ffsystem.su ./System/FatFs/ffunicode.cyclo ./System/FatFs/ffunicode.d ./System/FatFs/ffunicode.o ./System/FatFs/ffunicode.su

.PHONY: clean-System-2f-FatFs

