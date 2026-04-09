/**
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#include "gui_image.h"

#include "stm32l4xx_hal.h"

#include "main.h"
#include "FatFs/ff.h"
#include "display_api.h"
#include "display_hal.h"
#include "fs_file_search.h"
#include "fs_font_search.h"
#include "fs_version.h"
#include "fs_pixeldata_rle_a.h"
#include "Graphics/gui_graphics_api.h"
#include "Core/gui_log.h"

#define MAX_BUFFER_SIZE_PIXELS 256
#define MAX_FILE_PATH_LENGTH 50
#define MAX_FILE_PATH_LENGTH_INC_NULL (MAX_FILE_PATH_LENGTH + 1)

#define GUI_IMAGE_FILE GUI_IMAGE_DIRECTORY FS_IMAGE_FILE_NAME

static void gui_image_drawImageFromSD_RLE(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t dataAddress);
static void gui_image_drawImageFromSD_RLE_A(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t dataAddress,
        const uint32_t foreColor, const uint32_t backColor);
static void gui_image_drawImageFromCode16BitBus(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t dataAddress,
        const uint32_t foreColor, const uint32_t backColor);

static FIL m_imageFile;
static bool m_imageFileOpen = false;


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
        const uint32_t dataAddress, const uint8_t dataLocation
#if GUI_CONFIG_USE_BITMAP_COLORS
        , const uint32_t foreColor, const uint32_t backColor
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */
        )
{
    if (FS_DATA_LOCATION_1 == dataLocation)
    {
        gui_image_drawImageFromCode16BitBus(xPos, yPos, width, height, dataAddress, foreColor, backColor);
    }
    else if (FS_DATA_LOCATION_0 == dataLocation)
    {
        if (!m_imageFileOpen)
        {
            gui_log_error("gui_image_fileNotOpen");
            return;
        }

        switch (fs_getCompression(dataLocation))
        {
            case RLE:
                gui_image_drawImageFromSD_RLE(xPos, yPos, width, height, dataAddress);
                break;
            case RLE_ALPHA:
                gui_image_drawImageFromSD_RLE_A(xPos, yPos, width, height, dataAddress, foreColor, backColor);
                break;
            default:
                /* TODO all pixels stored */
                return;
        }
    }
    else
    {
        /* Invalid data location */
        return;
    }
}

static void gui_image_drawImageFromCode16BitBus(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t dataAddress,
        const uint32_t foreColor, const uint32_t backColor)
{
    fs_pixeldata_info_s pixelDataInfo = {0};
    pixelDataInfo.readIndex = dataAddress;
    pixelDataInfo.foreColor = foreColor;
    pixelDataInfo.backColor = backColor;
    pixelDataInfo.pixelsToRead =  width * height;

    display_setAddressWindow(xPos, yPos, width, height);
    display_hal_startDataTransmission();
    fs_transferPixels(&pixelDataInfo, display_hal_writePixels);
    display_hal_stopDataTransmission();
}

static void gui_image_drawImageFromSD_RLE(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t dataAddress)
{
    f_lseek(&m_imageFile, dataAddress);

    display_setAddressWindow(xPos, yPos, width, height);
    display_hal_startDataTransmission();

    uint32_t pixelsToTransfer = width * height;

    while (pixelsToTransfer > 0)
    {
        uint8_t pixeldata[3] = {0};
        UINT bytesRead = 0;
        f_read(&m_imageFile, pixeldata, sizeof(pixeldata), &bytesRead);

        uint8_t noOfPixels = pixeldata[0];
        uint16_t *p_color = (uint16_t*)&pixeldata[1];

        display_hal_writePixels(*p_color, noOfPixels);

        if (pixelsToTransfer > noOfPixels)
        {
            pixelsToTransfer -= noOfPixels;
        }
        else
        {
            pixelsToTransfer = 0;
        }
    }

    display_hal_stopDataTransmission();
}

static void gui_image_drawImageFromSD_RLE_A(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t dataAddress,
        const uint32_t foreColor, const uint32_t backColor)
{
    f_lseek(&m_imageFile, dataAddress);

    display_setAddressWindow(xPos, yPos, width, height);
    display_hal_startDataTransmission();

    uint32_t pixelsToTransfer = width * height;

    while (pixelsToTransfer > 0)
    {
        uint8_t pixeldata[2] = {0};
        UINT bytesRead = 0;
        f_read(&m_imageFile, pixeldata, sizeof(pixeldata), &bytesRead);

        const uint16_t noOfPixels = pixeldata[0];
        const uint8_t pixel = pixeldata[1];
        const uint16_t color = fs_getPixelColor(foreColor, backColor, pixel);

        display_hal_writePixels(color, noOfPixels);

        if (pixelsToTransfer > noOfPixels)
        {
            pixelsToTransfer -= noOfPixels;
        }
        else
        {
            pixelsToTransfer = 0;
        }
    }

    display_hal_stopDataTransmission();
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
    file_search_result_e result = fs_getFileInfo(bmpKey, p_properties, GUI_CONFIG_NUMBER_OF_PROPERTIES, &fsFileInfo, p_out_dataLocation);
    const bool fileFound = (result == FILE_SEARCH_OK);

    *p_out_width = fsFileInfo.width;
    *p_out_height = fsFileInfo.height;
    *p_out_dataOffset = fsFileInfo.dataOffset;

    return fileFound;
}

bool graphics_getCharacterInfo(
        const char character, const FontData_s *p_fontData,
        uint16_t *p_out_width, uint16_t *p_out_height,
        uint32_t *p_out_dataOffset, uint8_t *p_out_dataLocation)
{
    /* Get the character info from the filesystem. */
    fs_char_info_s char_info = {0};
    const bool charFound = fs_getCharInfo(character, p_fontData->font, &char_info, p_out_dataLocation);

    *p_out_width = char_info.width;
    *p_out_height = char_info.height;
    *p_out_dataOffset = char_info.dataOffset;

    return charFound;
}

void graphics_drawImage(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t dataOffset, const uint8_t dataLocation
#if GUI_CONFIG_USE_BITMAP_COLORS
        , const uint32_t foreColor, const uint32_t backColor
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */
)
{
    /* Draw bmp data on display */
    gui_image_drawImage(xPos, yPos, width, height, dataOffset, dataLocation, foreColor, backColor);
}

/*** end of file ***/
