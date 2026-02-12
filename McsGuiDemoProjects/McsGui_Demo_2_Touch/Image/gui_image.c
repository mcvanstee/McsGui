/**
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#include "gui_image.h"

#include <string.h>

#include "stm32l4xx_hal.h"

#include "main.h"
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

static inline void gui_image_updatePixelsToTransfer(volatile uint32_t *p_pixelsToTransfer, uint32_t *p_pixelsToRead);
static inline void gui_image_swapBuffers(void);

static FIL m_imageFile;
static bool m_imageFileOpen = false;

static uint16_t m_dataBuffer_1[MAX_BUFFER_SIZE_PIXELS];
static uint16_t m_dataBuffer_2[MAX_BUFFER_SIZE_PIXELS];
static uint16_t *m_p_readBuffer;
static uint16_t *m_p_writeBuffer;

bool gui_image_initialize(void)
{
    if (!m_imageFileOpen)
    {
        FRESULT imageFileOpenResult = f_open(&m_imageFile, GUI_IMAGE_FILE, (FA_OPEN_EXISTING | FA_READ));
        m_imageFileOpen = (FR_OK == imageFileOpenResult);
    }

    return m_imageFileOpen;
}

static void gui_image_drawImage(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t dataAddress)
{
    volatile uint32_t pixelsToTransfer = width * height;
    m_p_readBuffer = m_dataBuffer_1;
    m_p_writeBuffer = m_dataBuffer_2;

    f_lseek(&m_imageFile, dataAddress);

    display_setAddressWindow(xPos, yPos, width, height);

    while (pixelsToTransfer)
    {
        uint32_t pixelsToRead = 0;
        gui_image_updatePixelsToTransfer(&pixelsToTransfer, &pixelsToRead);

        UINT bytesRead = 0;

        f_read(&m_imageFile, m_p_readBuffer, (pixelsToRead * FS_BYTES_PER_PIXEL), &bytesRead);
        gui_image_swapBuffers();
        display_hal_writePixelData(m_p_writeBuffer, bytesRead / FS_BYTES_PER_PIXEL);
    }
}

static inline void gui_image_updatePixelsToTransfer(volatile uint32_t *p_pixelsToTransfer, uint32_t *p_pixelsToRead)
{
    if (*p_pixelsToTransfer > MAX_BUFFER_SIZE_PIXELS)
    {
        *p_pixelsToRead = MAX_BUFFER_SIZE_PIXELS;
        *p_pixelsToTransfer -= MAX_BUFFER_SIZE_PIXELS;
    }
    else
    {
        *p_pixelsToRead = *p_pixelsToTransfer;
        *p_pixelsToTransfer = 0;
    }
}

static inline void gui_image_swapBuffers(void)
{
    if (m_p_readBuffer == m_dataBuffer_1)
    {
        m_p_readBuffer = m_dataBuffer_2;
        m_p_writeBuffer = m_dataBuffer_1;
    }
    else
    {
        m_p_readBuffer = m_dataBuffer_1;
        m_p_writeBuffer = m_dataBuffer_2;
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
        uint32_t *p_out_dataOffset, uint8_t *p_out_dataLocation)
{
    /* Get the bmp info from the filesystem. */
    fs_file_info_s fsFileInfo = {0};
    file_search_result_e result = fs_getFileInfo(bmpKey, p_properties, FS_MAX_FILE_PROPERTIES, &fsFileInfo, p_out_dataLocation);
    const bool fileFound = (result == FILE_SEARCH_OK);

    *p_out_width = fsFileInfo.width;
    *p_out_height = fsFileInfo.height;
    *p_out_dataOffset = fsFileInfo.dataOffset;

    return fileFound;
}

bool graphics_getCharacterInfo(
        const char character, const FontData_s *p_fontData,
        uint16_t *p_out_width, uint16_t *p_out_height,
        uint32_t *p_out_dataOffset)
{
    /* Get the character info from the filesystem. */
    fs_char_info_s char_info = {0};
    const bool charFound = fs_getCharInfo(character, p_fontData->font, &char_info);

    *p_out_width = char_info.width;
    *p_out_height = char_info.height;
    *p_out_dataOffset = char_info.dataOffset;

    return charFound;
}

void graphics_drawImage(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t dataOffset
#if GUI_CONFIG_USE_BITMAP_COLORS
        , const uint8_t dataLocation
        , const uint32_t foreColor, const uint32_t backColor
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */
)
{
    /* Draw bmp data on display */
    gui_image_drawImage(xPos, yPos, width, height, dataOffset);
}
