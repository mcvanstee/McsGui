#ifndef DISPLAY_DRIVER_H_
#define DISPLAY_DRIVER_H_

#include <stdbool.h>
#include <stdint.h>


typedef enum
{
    Portrait = 0,
    Landscape = 1,
    PortraitFlip = 2,
    LandscapeFlip = 3
} DisplayOrientation_e;

typedef struct
{
	uint16_t width;
	uint16_t height;
} DisplaySize_s;

typedef struct
{
	uint16_t defaultWidth;
	uint16_t defaultHeight;
	DisplaySize_s displaySize;
	uint8_t orientation;
	bool (*init)(void);
	bool (*setAddressWindow)(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height);
	void (*setOrientation)(const DisplayOrientation_e orientation);
	void (*invertDisplay)(const bool invert);
} DisplayDriver_s;

#endif /* DISPLAY_DRIVER_H_ */
