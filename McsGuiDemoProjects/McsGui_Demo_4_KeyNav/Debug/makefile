################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include System/Hal/subdir.mk
-include System/FatFs/subdir.mk
-include System/subdir.mk
-include Logging/subdir.mk
-include Image/subdir.mk
-include GuiApp/Views/Setup/subdir.mk
-include GuiApp/Views/Settings/subdir.mk
-include GuiApp/Views/subdir.mk
-include GuiApp/Style/subdir.mk
-include GuiApp/CustomComponents/subdir.mk
-include GuiApp/ComponentExtensions/subdir.mk
-include GuiApp/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Display/ST7789/subdir.mk
-include Display/ILI9486/subdir.mk
-include Display/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := McsGui_Demo_4_KeyNav
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
McsGui_Demo_4_KeyNav.elf \

MAP_FILES += \
McsGui_Demo_4_KeyNav.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
McsGui_Demo_4_KeyNav.list \


# All Target
all: main-build

# Main-build Target
main-build: McsGui_Demo_4_KeyNav.elf secondary-outputs

# Tool invocations
McsGui_Demo_4_KeyNav.elf McsGui_Demo_4_KeyNav.map: $(OBJS) $(USER_OBJS) C:\Development\IRL_Development\ST_Projects\McsGui_Project\McsGui\McsGuiDemoProjects\McsGui_Demo_4_KeyNav\STM32L496ZGTXP_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "McsGui_Demo_4_KeyNav.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Development\IRL_Development\ST_Projects\McsGui_Project\McsGui\McsGuiDemoProjects\McsGui_Demo_4_KeyNav\STM32L496ZGTXP_FLASH.ld" --specs=nosys.specs -Wl,-Map="McsGui_Demo_4_KeyNav.map" -Wl,--gc-sections -static -L"C:\Development\IRL_Development\ST_Projects\McsGui_Project\McsGui\McsGuiDemoProjects\McsGuiLib\Debug" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

McsGui_Demo_4_KeyNav.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "McsGui_Demo_4_KeyNav.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) McsGui_Demo_4_KeyNav.elf McsGui_Demo_4_KeyNav.list McsGui_Demo_4_KeyNav.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
