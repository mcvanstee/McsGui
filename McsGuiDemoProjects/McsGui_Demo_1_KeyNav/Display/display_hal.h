/**
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef DISPLAY_HAL_H_
#define DISPLAY_HAL_H_

#include <stdint.h>

/* Constants */
#define DISPLAY_COLOR_BUFFER_SIZE_BYTES 512
#define DISPLAY_COLOR_BUFFER_SIZE_PIXELS (DISPLAY_COLOR_BUFFER_SIZE_BYTES / 2)

void display_hal_init(void);
void display_hal_sendCommand(uint8_t command);
void display_hal_sendU8Data(const uint8_t data);
void display_hal_sendCommandData(uint8_t command, const uint8_t *p_data, const uint8_t dataLength);

void display_hal_writeColor(const uint16_t color, const int32_t pixels);
void display_hal_writePixelData(const uint16_t *p_data, const int32_t pixels);
void display_hal_transmissionFinished(void);

void display_hal_readCmd(uint8_t cmd, uint8_t *p_data, const uint32_t dataLength);
void display_hal_readData(uint8_t *p_data, const uint32_t dataLength);

void display_hal_setBacklight(const uint8_t percentage);
void display_hal_chipSelectHigh(void);
void display_hal_chipSelectLow(void);
void display_hal_resetHigh(void);
void display_hal_resetLow(void);
void display_hal_dataMode(void);
void display_hal_powerOn(void);
void display_hal_powerOff(void);
void display_hal_backlightOn(void);
void display_hal_backlightOff(void);
void display_hal_delay(const uint32_t delay);

#endif /* DISPLAY_HAL_H_ */
