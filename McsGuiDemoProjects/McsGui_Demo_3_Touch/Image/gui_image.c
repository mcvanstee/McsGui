/**
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#include "gui_image.h"

#include <string.h>

#include "stm32l4xx_hal.h"

#include "FatFs/ff.h"
#include "display_api.h"
#include "display_hal.h"
#include "fs_file_search.h"
#include "fs_font_search.h"
#include "fs_version.h"
#include "Graphics/gui_graphics_api.h"

#define MAX_BUFFER_SIZE_PIXELS 256
#define MAX_BUFFER_SIZE_BYTES (MAX_BUFFER_SIZE_PIXELS * 2)
#define MAX_FILE_PATH_LENGTH 50
#define MAX_FILE_PATH_LENGTH_INC_NULL (MAX_FILE_PATH_LENGTH + 1)

#define GUI_IMAGE_FILE GUI_IMAGE_DIRECTORY FS_IMAGE_FILE_NAME


static FIL m_imageFile;
static bool m_imageFileOpen = false;

static volatile uint16_t m_dataBuffer_1[MAX_BUFFER_SIZE_PIXELS];
static volatile uint16_t m_dataBuffer_2[MAX_BUFFER_SIZE_PIXELS];

bool gui_image_initialize(void)
{
    if (!m_imageFileOpen)
    {
        FRESULT imageFileOpenResult = f_open(&m_imageFile, GUI_IMAGE_FILE, (FA_OPEN_EXISTING | FA_READ));
        m_imageFileOpen = (FR_OK == imageFileOpenResult);
    }

    return m_imageFileOpen;
}

void gui_image_drawImage(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t dataAddress, const uint32_t dataSize)
{
    volatile uint32_t bytesToTransfer = dataSize;
    volatile uint16_t *p_readBuffer = m_dataBuffer_1;
    volatile uint16_t *p_writeBuffer = m_dataBuffer_2;

    f_lseek(&m_imageFile, dataAddress);

    display_setAddressWindow(xPos, yPos, width, height);

    if (MAX_BUFFER_SIZE_BYTES >= dataSize)
    {
        UINT bytesRead = 0;

    	f_read(&m_imageFile, (uint16_t *)m_dataBuffer_1, dataSize, &bytesRead);
    	display_hal_writePixelData((uint16_t *)m_dataBuffer_1, bytesToTransfer / FS_BYTES_PER_PIXEL);

        return;
    }

    while (bytesToTransfer)
    {
        UINT bytesRead = 0;
        UINT bytesToRead = 0;

        if (bytesToTransfer > MAX_BUFFER_SIZE_BYTES)
        {
            bytesToRead = MAX_BUFFER_SIZE_BYTES;
            bytesToTransfer -= MAX_BUFFER_SIZE_BYTES;
        }
        else
        {
            bytesToRead = bytesToTransfer;
            bytesToTransfer = 0;
        }

        f_read(&m_imageFile, (uint16_t *)p_readBuffer, bytesToRead, &bytesRead);

        if (p_readBuffer == m_dataBuffer_1)
        {
			p_readBuffer = m_dataBuffer_2;
			p_writeBuffer = m_dataBuffer_1;
		}
        else
        {
			p_readBuffer = m_dataBuffer_1;
			p_writeBuffer = m_dataBuffer_2;
		}

        display_hal_writePixelData((uint16_t *)p_writeBuffer, bytesRead / FS_BYTES_PER_PIXEL);
    }
}

bool fs_readData(const int32_t offset, uint8_t *p_out_data, const int32_t size)
{
	UINT bytesRead = 0;

	f_lseek(&m_imageFile, offset);
	f_read(&m_imageFile, p_out_data, size, &bytesRead);

	return (bytesRead == size);
}


/* McsGui lower layer API these functions need to implement in your application. */

#if GUI_CONFIG_USE_FILE_PROPERTIES
#if GUI_CONFIG_NUMBER_OF_PROPERTIES < FS_MAX_FILE_PROPERTIES
#error "GUI_CONFIG_NUMBER_OF_PROPERTIES must be greater than or equal to FS_MAX_FILE_PROPERTIES"
#endif /* GUI_CONFIG_NUMBER_OF_PROPERTIES < FS_MAX_FILE_PROPERTIES */
#endif /* GUI_CONFIG_USE_FILE_PROPERTIES */


void graphics_drawRectFillBorder(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const uint32_t borderColor,
        const uint8_t radius, const uint32_t fillColor)
{
    /* Draw a filled rectangle with a border. */
    if (radius == 0)
    {
        display_drawRectangleFillBorder(
                xPos, yPos, width, height, borderThickness, fillColor, borderColor);
    }
    else
    {
        display_drawRoundRectangleFillBorder(
                xPos, yPos, width, height,
                radius, borderThickness, fillColor, borderColor);
    }
}

void graphics_drawRectBorder(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const uint32_t borderColor,
        const uint8_t radius)
{
    /* Draw a square border */
    if (radius == 0)
    {
        display_drawRectangleBorder(
                xPos, yPos, width, height, borderThickness, borderColor);
    }
    else
    {
        display_drawRoundRectangleBorder(
                xPos, yPos, width, height, radius,
                borderThickness, borderColor);
    }
}

void graphics_drawRectFill(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint8_t radius, const uint32_t color)
{
    /* Draw a filled rectangle */
    if (radius == 0)
    {
        display_drawRectangleFill(xPos, yPos, width, height, color);
    }
    else
    {
        display_drawRoundRectangleFill(xPos, yPos, width, height, radius, color);
    }
}

bool graphics_getBmpFileInfo(
      const uint32_t bmpKey, const uint8_t *p_properties,
        uint16_t *p_out_width, uint16_t *p_out_height,
        uint32_t *p_out_dataOffset, uint32_t *p_out_dataSize)
{
    /* Get the bmp info from the filesystem. */
    fs_file_info_s fsFileInfo = {0};
    file_search_result_e result = fs_getFileInfo(bmpKey, p_properties, FS_MAX_FILE_PROPERTIES, &fsFileInfo);
    const bool fileFound = (result == FILE_SEARCH_OK);

    *p_out_width = fsFileInfo.width;
    *p_out_height = fsFileInfo.height;
    *p_out_dataOffset = fsFileInfo.dataOffset;
    *p_out_dataSize = FS_BYTES_PER_PIXEL * fsFileInfo.width * fsFileInfo.height;

    return fileFound;
}

bool graphics_getCharacterInfo(
        const char character, const FontData_s *p_fontData,
        uint16_t *p_out_width, uint16_t *p_out_height,
        uint32_t *p_out_dataOffset, uint32_t *p_out_dataSize)
{
    /* Get the character info from the filesystem. */
    fs_char_info_s char_info = {0};
    const bool charFound = fs_getCharInfo(character, p_fontData->font, &char_info);

    *p_out_width = char_info.width;
    *p_out_height = char_info.height;
    *p_out_dataOffset = char_info.dataOffset;
    *p_out_dataSize = FS_BYTES_PER_PIXEL * char_info.width * char_info.height;

    return charFound;
}

void graphics_drawImage(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t dataOffset, const uint32_t dataSize)
{
    /* Draw bmp data on display */
    gui_image_drawImage(xPos, yPos, width, height, dataOffset, dataSize);
}
