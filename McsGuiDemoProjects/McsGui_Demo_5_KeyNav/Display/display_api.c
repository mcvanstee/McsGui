#include "display_api.h"

#include <stdlib.h>

#include "display_hal.h"

typedef enum
{
    CIRCLE_SIDE_RIGHT = 0,
    CIRCLE_SIDE_LEFT = 1,
    CIRCLE_SIDE_BOTH = 2
} circle_side_e;


typedef enum
{
    CIRCLE_CORNER_UPPER_LEFT = 0x01,
    CIRCLE_CORNER_UPPER_RIGHT = 0x02,
    CIRCLE_CORNER_LOWER_LEFT = 0x04,
    CIRCLE_CORNER_LOWER_RIGHT = 0x08,
} circle_corner_e;


//#define DISPLAY_COLOR_REVERSE_BYTES

/* Extern declarations */
extern bool ST7789_init(DisplayDriver_s *p_driver);
extern bool ILI9486_init(DisplayDriver_s *p_driver);
//extern bool ILI9341_init(DisplayDriver_s *p_driver);


/* Private function declarations */
static inline uint16_t display_getRGB565(const uint32_t color);
static void display_drawCircleFillSide(
        const uint16_t x, const uint16_t y,
        const uint16_t radius, const circle_side_e side,
        const uint16_t stretchY, const uint32_t color);
static void display_drawCircleCorner(
        const uint16_t x, const uint16_t y,
        const uint16_t radius, const circle_corner_e corner,
        const uint32_t color);
static inline int32_t display_sgn(const int32_t x);

static DisplayDriver_s m_displayDriver;

bool display_init(
		DisplayDriver_e driver, uint16_t width, uint16_t height,
		DisplayOrientation_e orientation, bool invert)
{
	display_hal_powerOn();
	display_hal_init();

	bool initialized = false;
	m_displayDriver.defaultWidth = width;
	m_displayDriver.defaultHeight = height;

	switch (driver)
	{
		case DisplayDriver_ST7789:
			initialized = ST7789_init(&m_displayDriver);
			break;
		case DisplayDriver_ILI9486:
			initialized = ILI9486_init(&m_displayDriver);
			break;
		case DisplayDriver_ILI9341:
			//initialized = ILI9341_init(&m_displayDriver);
			break;
		default:
			break;
	}

	m_displayDriver.setOrientation(orientation);
	m_displayDriver.invertDisplay(invert);

	return initialized;
}

DisplayOrientation_e display_getOrientation(void)
{
    return m_displayDriver.orientation;
}

DisplaySize_s display_getSizePixels(void)
{
	return m_displayDriver.displaySize;
}

DisplaySize_s display_getDefaultSizePixels(void)
{
	DisplaySize_s size = {0};
	size.width = m_displayDriver.defaultWidth;
	size.height = m_displayDriver.defaultHeight;

	return size;
}

uint16_t display_getWidthPixels(void)
{
	return m_displayDriver.displaySize.width;
}

uint16_t display_getHeightPixels(void)
{
	return m_displayDriver.displaySize.height;
}

uint16_t display_convertToRGB565(const uint32_t rgb)
{
	const uint16_t color = display_getRGB565(rgb);

	return color;
}

void display_setOrientation(const DisplayOrientation_e orientation)
{
	m_displayDriver.setOrientation(orientation);
}

bool display_setAddressWindow(
		const uint16_t x, const uint16_t y,
		const uint16_t width, const uint16_t height)
{
	return m_displayDriver.setAddressWindow(x, y, width, height);
}

void display_fillScreen(const uint32_t color)
{
	display_drawRectangleFill(
    		0u, 0u, m_displayDriver.displaySize.width, m_displayDriver.displaySize.height, color);
}

void display_drawPixel(const uint16_t x, const uint16_t y, const uint32_t color)
{
    const uint16_t color565 = display_getRGB565(color);
    const bool isInAddressWindow = m_displayDriver.setAddressWindow(x, y, 1u, 1u);

    if (isInAddressWindow)
    {
        display_hal_writeColor(color565, 1);
    }
}

void display_drawLine(
        const uint16_t x, const uint16_t y,
        const uint16_t x1, const uint16_t y1,
        const uint32_t color)
{
    const int32_t dx = x1 - x;      /* the horizontal distance of the line */
    const int32_t dy = y1 - y;      /* the vertical distance of the line */
    const uint32_t dxAbs = (uint32_t)abs(dx);
    const uint32_t dyAbs = (uint32_t)abs(dy);
    const int32_t sdx = display_sgn(dx);
    const int32_t sdy = display_sgn(dy);
    uint32_t xPos = dyAbs >> 1;
    uint32_t yPos = dxAbs >> 1;
    int32_t pixelX = x;
    int32_t pixelY = y;

    display_drawPixel((uint16_t)pixelX, (uint16_t)pixelY, color);

    if (dxAbs >= dyAbs) /* the line is more horizontal than vertical */
    {
        for (uint32_t i = 0; i < dxAbs; i++)
        {
            yPos += dyAbs;
            if (yPos >= dxAbs)
            {
                yPos -= dxAbs;
                pixelY += sdy;
            }

            pixelX += sdx;
            display_drawPixel((uint16_t)pixelX, (uint16_t)pixelY, color);
        }
    }
    else /* the line is more vertical than horizontal */
    {
        for (uint32_t i = 0; i < dyAbs; i++)
        {
            xPos += dxAbs;
            if (xPos >= dyAbs)
            {
                xPos -= dyAbs;
                pixelX += sdx;
            }

            pixelY += sdy;
            display_drawPixel((uint16_t)pixelX, (uint16_t)pixelY, color);
        }
    }
}

void display_drawHorizontalLine(
        const uint16_t x, const uint16_t y,
        const uint16_t length, const uint32_t color)
{
    const uint16_t color565 = display_getRGB565(color);
    const bool isInAddressWindow = m_displayDriver.setAddressWindow(x, y, length, 1u);

    if (isInAddressWindow)
    {
        display_hal_writeColor(color565, length);
    }
}

void display_drawVerticalLine(
        const uint16_t x, const uint16_t y,
        const uint16_t length, const uint32_t color)
{
    const uint16_t color565 = display_getRGB565(color);
    const bool isInAddressWindow = m_displayDriver.setAddressWindow(x, y, 1u, length);

    if (isInAddressWindow)
    {
        display_hal_writeColor(color565, length);
    }
}

void display_drawRectangleFill(
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const uint32_t color)
{
	const uint32_t noOfPixels = width * height;
    const uint16_t color565 = display_getRGB565(color);
    const bool isInAddressWindow = m_displayDriver.setAddressWindow(x, y, width, height);

    if (isInAddressWindow)
    {
        display_hal_writeColor(color565, noOfPixels);
    }
}

void display_drawRectangleFillBorder(
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const uint16_t borderThickness,
        const uint32_t color, const uint32_t borderColor)
{
    if (((width / 2u) <= borderThickness) ||
        ((height / 2u) <= borderThickness))
    {
        return;
    }

    display_drawRectangleBorder(x, y, width, height, borderThickness, borderColor);
    display_drawRectangleFill((x + borderThickness), (y + borderThickness),
            (width - (2u * borderThickness)), (height - (2u * borderThickness)), color);
}

void display_drawRectangleBorder(
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const uint16_t borderThickness, const uint32_t color)
{
    if (borderThickness == 1u)
    {
        display_drawHorizontalLine(x, y, width, color);
        display_drawHorizontalLine(x, ((y + height) - 1u), width, color);
        display_drawVerticalLine(x, y, height, color);
        display_drawVerticalLine(((x + width) - 1u), y, height, color);
    }
    else if (borderThickness > 1u)
    {
        display_drawRectangleFill(x, y, width, borderThickness, color);
        display_drawRectangleFill(x, (y + borderThickness), borderThickness,
                                  (height - (2u * borderThickness)), color);
        display_drawRectangleFill(((x + width) - borderThickness), (y + borderThickness),
                                  borderThickness, (height - (2u * borderThickness)), color);
        display_drawRectangleFill(x, ((y + height) - borderThickness), width, borderThickness, color);
    }
    else
    {
        // Border thickness is 0.
    }
}

void display_drawRoundRectangleFill(
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const uint16_t radius,
        const uint32_t color)
{
    display_drawRectangleFill((x + radius), y, width - ((2u * radius)), height, color);

    const uint16_t rightCircleX = ((x + width) - radius) - 1u;
    const uint16_t rightCircleY = (y + radius);
    const uint16_t rightStretchY = (height - (2u * radius) - 1u);

    display_drawCircleFillSide(
            rightCircleX, rightCircleY, radius, CIRCLE_SIDE_RIGHT, rightStretchY, color);

    const uint16_t leftCircleX = x + radius;
    const uint16_t leftCircleY = y + radius;
    const uint16_t leftStretchY = height - (2u * radius) - 1u;

    display_drawCircleFillSide(
            leftCircleX, leftCircleY, radius, CIRCLE_SIDE_LEFT, leftStretchY, color);
}

void display_drawRoundRectangleFillBorder(
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const uint16_t radius, const uint8_t borderThickness,
        const uint32_t color, const uint32_t borderColor)
{
    display_drawRoundRectangleFill(x, y, width, height, radius, color);
    display_drawRoundRectangleBorder(x, y, width, height, radius, borderThickness, borderColor);
}

void display_drawRoundRectangleBorder(
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const uint16_t radius, const uint8_t borderThickness,
		const uint32_t color)
{
    const uint16_t radiusLength = (2 *(radius) );

    if (borderThickness == 1u)
    {
        display_drawHorizontalLine(x + radius, y, width - radiusLength, color); // Top
        display_drawHorizontalLine((x + radius), (y + height - 1), (width - radiusLength), color); // Bottom
        display_drawVerticalLine(x, (y + radius), (height - radiusLength), color); // Left
        display_drawVerticalLine(((x + width - 1)), (y + radius), (height - radiusLength), color); // Right

        display_drawCircleCorner(
                (x + radius), (y + radius), radius, CIRCLE_CORNER_UPPER_LEFT, color);
        display_drawCircleCorner(
                (x + width - radius - 1), (y + radius), radius, CIRCLE_CORNER_UPPER_RIGHT, color);
        display_drawCircleCorner(
                (x + width - radius - 1), (y + height - radius - 1), radius, CIRCLE_CORNER_LOWER_RIGHT, color);
        display_drawCircleCorner(
                (x + radius), (y + height - radius - 1), radius, CIRCLE_CORNER_LOWER_LEFT, color);
    }
    else if (borderThickness > 1u)
    {
        display_drawRectangleFill(x + radius, y, width - radiusLength, borderThickness, color); // Top
        display_drawRectangleFill((x + radius), (y + height - borderThickness), (width - radiusLength), borderThickness, color); // Bottom
        display_drawRectangleFill(x, (y + radius), borderThickness, (height - radiusLength), color); // Left
        display_drawRectangleFill((x + width - borderThickness), (y + radius), borderThickness, (height - radiusLength), color); // Right

        display_drawCircleCorner(
                (x + radius), (y + radius), radius, CIRCLE_CORNER_UPPER_LEFT, color);
        display_drawCircleCorner(
                (x + width - radius - 1), (y + radius), radius, CIRCLE_CORNER_UPPER_RIGHT, color);
        display_drawCircleCorner(
                (x + width - radius - 1), (y + height - radius - 1), radius, CIRCLE_CORNER_LOWER_RIGHT, color);
        display_drawCircleCorner(
                (x + radius), (y + height - radius - 1), radius, CIRCLE_CORNER_LOWER_LEFT, color);

        for (uint8_t i = 1; i < borderThickness; i++)
        {
            display_drawCircleCorner(
                    (x + radius + i), (y + radius + i), radius, CIRCLE_CORNER_UPPER_LEFT, color);
            display_drawCircleCorner(
                    (x + radius + i - 1), (y + radius + i), radius, CIRCLE_CORNER_UPPER_LEFT, color);
            display_drawCircleCorner(
                    (x + radius + i), (y + radius + i - 1), radius, CIRCLE_CORNER_UPPER_LEFT, color);

            display_drawCircleCorner(
                    (x + width - radius - i - 1), (y + radius + i), radius, CIRCLE_CORNER_UPPER_RIGHT, color);
            display_drawCircleCorner(
                    (x + width - radius - i - 1), (y + radius + i), radius, CIRCLE_CORNER_UPPER_RIGHT, color);
            display_drawCircleCorner(
                    (x + width - radius - i - 1), (y + radius + i - 1), radius, CIRCLE_CORNER_UPPER_RIGHT, color);

            display_drawCircleCorner(
                    (x + width - radius - i - 1), (y + height - radius - i), radius, CIRCLE_CORNER_LOWER_RIGHT, color);
            display_drawCircleCorner(
                    (x + width - radius - i - 1), (y + height - radius - i), radius, CIRCLE_CORNER_LOWER_RIGHT, color);
            display_drawCircleCorner(
                    (x + width - radius - i - 1), (y + height - radius - i - 1), radius, CIRCLE_CORNER_LOWER_RIGHT, color);

            display_drawCircleCorner(
                    (x + radius + i), (y + height - radius - i), radius, CIRCLE_CORNER_LOWER_LEFT, color);
            display_drawCircleCorner(
                    (x + radius + i - 1), (y + height - radius - i), radius, CIRCLE_CORNER_LOWER_LEFT, color);
            display_drawCircleCorner(
                    (x + radius + i), (y + height - radius - i - 1), radius, CIRCLE_CORNER_LOWER_LEFT, color);
        }
    }
    else
    {
        // Border thickness is 0.
    }
}

void display_drawCircleBorder(
        const uint16_t x, const uint16_t y,
        const uint16_t radius, const uint32_t color)
{
    int32_t Q = (int32_t)radius;
    int32_t f = 1 - Q;
    int32_t ddFx = 1;
    int32_t ddFy = -(2 * Q);
    int32_t P = 0;

    display_drawPixel((x + (uint16_t)Q), y, color);
    display_drawPixel((x - (uint16_t)Q), y, color);
    display_drawPixel(x, (y - (uint16_t)Q), color);
    display_drawPixel(x, (y + (uint16_t)Q), color);

    while (P < Q)
    {
        if (f >= 0)
        {
            Q--;
            ddFy += 2;
            f += ddFy;
        }

        P++;
        ddFx += 2;
        f += ddFx;

        display_drawPixel((x + (uint16_t)P), (y + (uint16_t)Q), color);
        display_drawPixel((x - (uint16_t)P), (y + (uint16_t)Q), color);
        display_drawPixel((x - (uint16_t)P), (y - (uint16_t)Q), color);
        display_drawPixel((x + (uint16_t)P), (y - (uint16_t)Q), color);

        display_drawPixel((x + (uint16_t)Q), (y + (uint16_t)P), color);
        display_drawPixel((x - (uint16_t)Q), (y + (uint16_t)P), color);
        display_drawPixel((x - (uint16_t)Q), (y - (uint16_t)P), color);
        display_drawPixel((x + (uint16_t)Q), (y - (uint16_t)P), color);
    }
}

void display_drawCircleFill(
        const uint16_t x, const uint16_t y,
        const uint16_t radius, const uint32_t color)
{
    display_drawVerticalLine(x, (y - radius), ((2u * radius) + 1u), color);
    display_drawCircleFillSide(x, y, radius, CIRCLE_SIDE_BOTH, 40u, color);
}

void display_setBacklight(const uint8_t brightness)
{
	if (brightness > 100)
	{
		return;
	}

	display_hal_setBacklight(brightness);
}

static inline uint16_t display_getRGB565(const uint32_t color)
{
    const uint8_t r = (color & 0x00FF0000u) >> 16;
    const uint8_t g = (color & 0x0000FF00u) >> 8;
    const uint8_t b = color & 0x000000FFu;
    const uint16_t rgb565 = ((r >> 3) << 11) + ((g >> 2) << 5) + (b >> 3);

#ifdef DISPLAY_COLOR_REVERSE_BYTES
    uint16_t colorRev = (rgb565 & 0x00FFu);
    colorRev <<= 8;
    colorRev += (rgb565 & 0xFF00u) >> 8;

    return colorRev;
#else
    return rgb565;
#endif /* DISPLAY_COLOR_REVERSE_BYTES */
}

static void display_drawCircleFillSide(
        const uint16_t x, const uint16_t y,
        const uint16_t radius, const circle_side_e side,
        const uint16_t stretchY, const uint32_t color)
{
    int32_t Q = (int32_t)radius;
    int32_t f = 1 - Q;
    int32_t ddFx = 1;
    int32_t ddFy = -(2 * Q);
    int32_t P = 0;
    const uint16_t stretch = stretchY +  1u;

    while (P < Q)
    {
        if (f >= 0)
        {
            Q--;
            ddFy += 2;
            f += ddFy;
        }

        P++;
        ddFx += 2;
        f += ddFx;

        if ((side == CIRCLE_SIDE_BOTH) || (side == CIRCLE_SIDE_LEFT))
        {
            display_drawVerticalLine((x - (uint16_t)P), (y - (uint16_t)Q), ((2u * (uint16_t)Q) + stretch), color);
            display_drawVerticalLine((x - (uint16_t)Q), (y - (uint16_t)P), ((2u * (uint16_t)P) + stretch), color);
        }

        if ((side == CIRCLE_SIDE_BOTH) || (side == CIRCLE_SIDE_RIGHT))
        {
            display_drawVerticalLine((x + (uint16_t)P), (y - (uint16_t)Q), ((2u * (uint16_t)Q) + stretch), color);
            display_drawVerticalLine((x + (uint16_t)Q), (y - (uint16_t)P), ((2u * (uint16_t)P) + stretch), color);
        }
    }
}

static void display_drawCircleCorner(
        const uint16_t x, const uint16_t y,
        const uint16_t radius, const circle_corner_e corner,
        const uint32_t color)
{
    int32_t Q = (int32_t)radius;
    int32_t f = 1 - Q;
    int32_t ddFx = 1;
    int32_t ddFy = -(2 * Q);
    int32_t P = 0;

    while (P < Q)
    {
        if (f >= 0)
        {
            Q--;
            ddFy += 2;
            f += ddFy;
        }

        P++;
        ddFx += 2;
        f += ddFx;

        if (CIRCLE_CORNER_LOWER_RIGHT == corner)
        {
            display_drawPixel((x + (uint16_t)P), (y + (uint16_t)Q), color);
            display_drawPixel((x + (uint16_t)Q), (y + (uint16_t)P), color);
        }
        else if (CIRCLE_CORNER_UPPER_RIGHT == corner)
        {
            display_drawPixel((x + (uint16_t)P), (y - (uint16_t)Q), color);
            display_drawPixel((x + (uint16_t)Q), (y - (uint16_t)P), color);
        }
        else if (CIRCLE_CORNER_LOWER_LEFT == corner)
        {
            display_drawPixel((x - (uint16_t)Q), (y + (uint16_t)P), color);
            display_drawPixel((x - (uint16_t)P), (y + (uint16_t)Q), color);
        }
        else if (CIRCLE_CORNER_UPPER_LEFT == corner)
        {
            display_drawPixel((x - (uint16_t)Q), (y - (uint16_t)P), color);
            display_drawPixel((x - (uint16_t)P), (y - (uint16_t)Q), color);
        }
        else
        {
        }
    }
}

static inline int32_t display_sgn(const int32_t x)
{
    return ((x < 0) ? -1 : ((x > 0) ? 1 : 0));
}

/*** end of file ***/
