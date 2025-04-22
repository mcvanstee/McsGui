################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32l496zgtxp.s 

OBJS += \
./Core/Startup/startup_stm32l496zgtxp.o 

S_DEPS += \
./Core/Startup/startup_stm32l496zgtxp.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Display" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Display/ST7789" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/System" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Logging" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Image" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/System/FatFs" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/System/Hal" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Style" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/CustomComponents" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Views" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Views/Settings" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/ComponentExtensions" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Views/Setup" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32l496zgtxp.d ./Core/Startup/startup_stm32l496zgtxp.o

.PHONY: clean-Core-2f-Startup

