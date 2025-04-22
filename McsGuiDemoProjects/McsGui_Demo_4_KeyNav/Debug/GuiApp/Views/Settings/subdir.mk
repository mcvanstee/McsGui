################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GuiApp/Views/Settings/brightness_view.c \
../GuiApp/Views/Settings/language_view.c \
../GuiApp/Views/Settings/settings_view.c \
../GuiApp/Views/Settings/theme_view.c \
../GuiApp/Views/Settings/units_view.c 

OBJS += \
./GuiApp/Views/Settings/brightness_view.o \
./GuiApp/Views/Settings/language_view.o \
./GuiApp/Views/Settings/settings_view.o \
./GuiApp/Views/Settings/theme_view.o \
./GuiApp/Views/Settings/units_view.o 

C_DEPS += \
./GuiApp/Views/Settings/brightness_view.d \
./GuiApp/Views/Settings/language_view.d \
./GuiApp/Views/Settings/settings_view.d \
./GuiApp/Views/Settings/theme_view.d \
./GuiApp/Views/Settings/units_view.d 


# Each subdirectory must supply rules for building sources it contributes
GuiApp/Views/Settings/%.o GuiApp/Views/Settings/%.su GuiApp/Views/Settings/%.cyclo: ../GuiApp/Views/Settings/%.c GuiApp/Views/Settings/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L496xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Display" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Display/ST7789" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/System" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Logging" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Image" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/System/FatFs" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/System/Hal" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Style" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGuiLib/McsGui" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGuiLib/McsGui/ExternalDisplay" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGuiLib/McsGui/Graphics" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGuiLib/McsGui/Utils" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/CustomComponents" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Views" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Views/Settings" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/ComponentExtensions" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Views/Setup" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-GuiApp-2f-Views-2f-Settings

clean-GuiApp-2f-Views-2f-Settings:
	-$(RM) ./GuiApp/Views/Settings/brightness_view.cyclo ./GuiApp/Views/Settings/brightness_view.d ./GuiApp/Views/Settings/brightness_view.o ./GuiApp/Views/Settings/brightness_view.su ./GuiApp/Views/Settings/language_view.cyclo ./GuiApp/Views/Settings/language_view.d ./GuiApp/Views/Settings/language_view.o ./GuiApp/Views/Settings/language_view.su ./GuiApp/Views/Settings/settings_view.cyclo ./GuiApp/Views/Settings/settings_view.d ./GuiApp/Views/Settings/settings_view.o ./GuiApp/Views/Settings/settings_view.su ./GuiApp/Views/Settings/theme_view.cyclo ./GuiApp/Views/Settings/theme_view.d ./GuiApp/Views/Settings/theme_view.o ./GuiApp/Views/Settings/theme_view.su ./GuiApp/Views/Settings/units_view.cyclo ./GuiApp/Views/Settings/units_view.d ./GuiApp/Views/Settings/units_view.o ./GuiApp/Views/Settings/units_view.su

.PHONY: clean-GuiApp-2f-Views-2f-Settings

