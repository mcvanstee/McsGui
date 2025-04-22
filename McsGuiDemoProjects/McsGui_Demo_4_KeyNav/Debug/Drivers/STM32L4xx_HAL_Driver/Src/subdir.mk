################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_mmc.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_mmc_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sd.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sd_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_sdmmc.c 

OBJS += \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc_ex.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_mmc.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_mmc_ex.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc_ex.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sd.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sd_ex.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi_ex.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim_ex.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_sdmmc.o 

C_DEPS += \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc_ex.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_mmc.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_mmc_ex.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc_ex.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sd.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sd_ex.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi_ex.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim_ex.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_sdmmc.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32L4xx_HAL_Driver/Src/%.o Drivers/STM32L4xx_HAL_Driver/Src/%.su Drivers/STM32L4xx_HAL_Driver/Src/%.cyclo: ../Drivers/STM32L4xx_HAL_Driver/Src/%.c Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L496xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Display" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Display/ST7789" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/System" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Logging" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/Image" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/System/FatFs" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/System/Hal" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Style" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGuiLib/McsGui" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGuiLib/McsGui/ExternalDisplay" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGuiLib/McsGui/Graphics" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGuiLib/McsGui/Utils" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/CustomComponents" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Views" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Views/Settings" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/ComponentExtensions" -I"C:/Development/IRL_Development/ST_Projects/McsGui_Project/McsGui/McsGuiDemoProjects/McsGui_Demo_4_KeyNav/GuiApp/Views/Setup" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-STM32L4xx_HAL_Driver-2f-Src

clean-Drivers-2f-STM32L4xx_HAL_Driver-2f-Src:
	-$(RM) ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc_ex.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc_ex.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc_ex.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc_ex.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_mmc.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_mmc.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_mmc.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_mmc.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_mmc_ex.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_mmc_ex.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_mmc_ex.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_mmc_ex.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc_ex.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc_ex.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc_ex.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc_ex.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sd.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sd.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sd.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sd.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sd_ex.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sd_ex.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sd_ex.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sd_ex.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi.o
	-$(RM) ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi_ex.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi_ex.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi_ex.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi_ex.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim_ex.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim_ex.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim_ex.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim_ex.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.su ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_sdmmc.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_sdmmc.d ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_sdmmc.o ./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_sdmmc.su

.PHONY: clean-Drivers-2f-STM32L4xx_HAL_Driver-2f-Src

