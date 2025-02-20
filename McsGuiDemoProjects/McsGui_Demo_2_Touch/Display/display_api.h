#ifndef DISPLAY_DISPLAY_API_H_
#define DISPLAY_DISPLAY_API_H_

#include "display_driver.h"

typedef enum
{
	DisplayDriver_ST7789 = 0,
	DisplayDriver_ILI9486 = 1,
	DisplayDriver_ILI9341 = 2
} DisplayDriver_e;

#define BACKLIGHT_BRIGHTNESS_MIN 1
#define BACKLIGHT_BRIGHTNESS_1 5
#define BACKLIGHT_BRIGHTNESS_2 10
#define BACKLIGHT_BRIGHTNESS_3 20
#define BACKLIGHT_BRIGHTNESS_4 30
#define BACKLIGHT_BRIGHTNESS_5 40
#define BACKLIGHT_BRIGHTNESS_6 50
#define BACKLIGHT_BRIGHTNESS_7 60
#define BACKLIGHT_BRIGHTNESS_8 70
#define BACKLIGHT_BRIGHTNESS_9 80
#define BACKLIGHT_BRIGHTNESS_MAX 100

bool display_init(
		DisplayDriver_e driver, uint16_t width, uint16_t height,
		DisplayOrientation_e orientation, bool invert);
DisplayOrientation_e display_getOrientation(void);
DisplaySize_s display_getSizePixels(void);
DisplaySize_s display_getDefaultSizePixels(void);
uint16_t display_getWidthPixels(void);
uint16_t display_getHeightPixels(void);
uint16_t display_convertToRGB565(const uint32_t rgb);
void display_setOrientation(const DisplayOrientation_e orientation);
bool display_setAddressWindow(
		const uint16_t x, const uint16_t y,
		const uint16_t width, const uint16_t height);

void display_fillScreen(const uint32_t color);
void display_drawPixel(const uint16_t x, const uint16_t y, const uint32_t color);
void display_drawLine(
        const uint16_t x, const uint16_t y,
        const uint16_t x1, const uint16_t y1,
        const uint32_t color);

void display_drawHorizontalLine(
        const uint16_t x, const uint16_t y,
        const uint16_t length, const uint32_t color);

void display_drawVerticalLine(
        const uint16_t x, const uint16_t y,
        const uint16_t length, const uint32_t color);

void display_drawRectangleFill(
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const uint32_t color);

void display_drawRectangleFillBorder(
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const uint16_t borderThickness,
        const uint32_t color, const uint32_t borderColor);

void display_drawRectangleBorder(
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const uint16_t borderThickness, const uint32_t color);

void display_drawRoundRectangleFill(
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const uint16_t radius,
        const uint32_t color);

void display_drawRoundRectangleFillBorder(
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const uint16_t radius, const uint8_t borderThickness,
        const uint32_t color, const uint32_t borderColor);

void display_drawRoundRectangleBorder(
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const uint16_t radius, const uint8_t borderThickness,
		const uint32_t color);

void display_drawCircleBorder(
        const uint16_t x, const uint16_t y,
        const uint16_t radius, const uint32_t color);

void display_drawCircleFill(
        const uint16_t x, const uint16_t y,
        const uint16_t radius, const uint32_t color);

void display_drawImageDataU16(
        const uint16_t x, const uint16_t y,
        const uint16_t imagePixelWidth, const uint16_t imagePixelHeight,
        const uint16_t *p_imageData);

void display_setBacklight(const uint8_t brightness);

#endif /* DISPLAY_DISPLAY_API_H_ */


/*** end of file ***/
