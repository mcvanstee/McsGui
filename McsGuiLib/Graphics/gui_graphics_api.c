#include "gui_graphics_api.h"

/* McsGui lower layer API these functions need to implement in your application. */

void graphics_drawRectFillBorder(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const uint32_t borderColor,
        const uint8_t radius, const uint32_t fillColor)
{
    /* Draw a filled rectangle with a border. */
}

void graphics_drawRectBorder(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const uint32_t borderColor,
        const uint8_t radius)
{
    /* Draw a square border */
}

void graphics_drawRectFill(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint8_t radius, const uint32_t color)
{
    /* Draw a filled rectangle */
}

bool graphics_getBmpFileInfo(
        const uint32_t bmpKey, const uint8_t *p_properties,
        uint16_t *p_out_width, uint16_t *p_out_height,
        uint32_t *p_out_dataOffset, uint32_t *p_out_dataSize)
{
    /* Get the bmp info from the filesystem. */
}

bool graphics_getCharacterInfo(
        const char character, const FontData_s *p_fontData,
        uint16_t *p_out_width, uint16_t *p_out_height,
        uint32_t *p_out_dataOffset, uint32_t *p_out_dataSize);

void graphics_drawImage(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t dataOffset, const uint32_t dataSize)
{
    /* Draw bmp data on display */
}


/*** end of file ***/
