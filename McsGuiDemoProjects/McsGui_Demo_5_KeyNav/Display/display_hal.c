#include "display_hal.h"

#include "display_driver.h"
#include <stdbool.h>

#include "main.h"


/* Constants */
#define DISPLAY_SPI_TIMEOUT 1000

/* Private function declarations */
static inline void display_hal_commandMode(void);
static inline void display_hal_writeGpioBus(const uint16_t data, const int32_t length);


void display_hal_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    display_hal_chipSelectHigh();
    display_hal_dataMode();
}

void display_hal_sendCommand(uint8_t command)
{
    display_hal_commandMode();
    display_hal_chipSelectLow();
    display_hal_writeGpioBus(command, 1);
    display_hal_chipSelectHigh();
}

void display_hal_sendCommandData(uint8_t command, const uint8_t *p_data, const uint8_t dataLength)
{
    display_hal_commandMode();
    display_hal_chipSelectLow();
    display_hal_writeGpioBus(command, 1);
    display_hal_chipSelectHigh();

    display_hal_dataMode();
    display_hal_chipSelectLow();

    for (uint8_t i = 0; i < dataLength; i++)
    {
        display_hal_writeGpioBus(p_data[i], 1);
    }

    display_hal_chipSelectHigh();
}

void display_hal_writeColor(const uint16_t color, const int32_t noOfpixels)
{
    display_hal_dataMode();
    display_hal_chipSelectLow();
    display_hal_writeGpioBus(color, noOfpixels);
    display_hal_chipSelectHigh();
}

void display_hal_startDataTransmission(void)
{
    display_hal_dataMode();
    display_hal_chipSelectLow();
}

void display_hal_writePixels(const uint16_t color, const int32_t noOfpixels)
{
    display_hal_writeGpioBus(color, noOfpixels);
}

void display_hal_stopDataTransmission(void)
{
    display_hal_chipSelectHigh();
}

static inline void display_hal_writeGpioBus(const uint16_t data, const int32_t length)
{
    GPIOE->BSRR = (~data << 16) | data; // Set data pins
    GPIOA->BRR = (uint32_t)GPIO_PIN_5; // Set CLK low

    for (int32_t i = 0; i < length; i++)
    {
        // Toggle CLK
        GPIOA->BSRR = (uint32_t) GPIO_PIN_5; // Set CLK high
        GPIOA->BRR = (uint32_t) GPIO_PIN_5;  // Set CLK low
    }
}

void display_hal_backlightOn(void)
{
	display_hal_setBacklight(100);
}

void display_hal_backlightOff(void)
{
	display_hal_setBacklight(0);
}

void display_hal_setBacklight(const uint8_t percentage)
{
}

void display_hal_delay(const uint32_t delay)
{
	HAL_Delay(delay);
}

void display_hal_chipSelectHigh(void)
{
	HAL_GPIO_WritePin(Display_CS_GPIO_Port, Display_CS_Pin, GPIO_PIN_SET);
}

void display_hal_chipSelectLow(void)
{
	HAL_GPIO_WritePin(Display_CS_GPIO_Port, Display_CS_Pin, GPIO_PIN_RESET);
}

void display_hal_dataMode(void)
{
	HAL_GPIO_WritePin(Display_DC_GPIO_Port, Display_DC_Pin, GPIO_PIN_SET);
}

static inline void display_hal_commandMode(void)
{
	HAL_GPIO_WritePin(Display_DC_GPIO_Port, Display_DC_Pin, GPIO_PIN_RESET);
}

void display_hal_resetHigh(void)
{
    HAL_GPIO_WritePin(Display_Reset_GPIO_Port, Display_Reset_Pin, GPIO_PIN_SET);
}

void display_hal_resetLow(void)
{
	HAL_GPIO_WritePin(Display_Reset_GPIO_Port, Display_Reset_Pin, GPIO_PIN_RESET);
}

void display_hal_powerOn(void)
{
}

void display_hal_powerOff(void)
{
}


/*** end of file ***/
