################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GuiApp/Views/Setup/interval_view.c \
../GuiApp/Views/Setup/limits_view.c \
../GuiApp/Views/Setup/setup_view.c 

OBJS += \
./GuiApp/Views/Setup/interval_view.o \
./GuiApp/Views/Setup/limits_view.o \
./GuiApp/Views/Setup/setup_view.o 

C_DEPS += \
./GuiApp/Views/Setup/interval_view.d \
./GuiApp/Views/Setup/limits_view.d \
./GuiApp/Views/Setup/setup_view.d 


# Each subdirectory must supply rules for building sources it contributes
GuiApp/Views/Setup/%.o GuiApp/Views/Setup/%.su GuiApp/Views/Setup/%.cyclo: ../GuiApp/Views/Setup/%.c GuiApp/Views/Setup/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L496xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Display" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Display/ST7789" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/System" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Logging" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Image" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/System/FatFs" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/System/Hal" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Style" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGuiLib/McsGui" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGuiLib/McsGui/ExternalDisplay" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGuiLib/McsGui/Graphics" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGuiLib/McsGui/Utils" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/CustomComponents" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Views" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Views/Settings" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/ComponentExtensions" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Views/Setup" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-GuiApp-2f-Views-2f-Setup

clean-GuiApp-2f-Views-2f-Setup:
	-$(RM) ./GuiApp/Views/Setup/interval_view.cyclo ./GuiApp/Views/Setup/interval_view.d ./GuiApp/Views/Setup/interval_view.o ./GuiApp/Views/Setup/interval_view.su ./GuiApp/Views/Setup/limits_view.cyclo ./GuiApp/Views/Setup/limits_view.d ./GuiApp/Views/Setup/limits_view.o ./GuiApp/Views/Setup/limits_view.su ./GuiApp/Views/Setup/setup_view.cyclo ./GuiApp/Views/Setup/setup_view.d ./GuiApp/Views/Setup/setup_view.o ./GuiApp/Views/Setup/setup_view.su

.PHONY: clean-GuiApp-2f-Views-2f-Setup

