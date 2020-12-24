/** @file gui_graphics_api.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_GRAPHICS_GUI_GRAPHICS_API_H_
#define MCSGUI_GRAPHICS_GUI_GRAPHICS_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "McsGui/Core/gui_fontdata.h"

void graphics_drawRectFillBorder(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const uint32_t borderColor,
        const uint32_t fillColor);

void graphics_drawRectBorder(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const uint32_t borderColor);

void graphics_drawRectFill(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t color);

bool graphics_getBmpFileInfo(
        const char *p_fileName,
        uint16_t *p_out_width, uint16_t *p_out_height,
        uint32_t *p_out_dataOffset, uint32_t *p_out_dataSize);

bool graphics_getCharacterInfo(
        const char character, const FontData_s *p_fontData,
        uint16_t *p_out_width, uint16_t *p_out_height,
        uint32_t *p_out_dataOffset, uint32_t *p_out_dataSize);

void graphics_drawImage(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t dataOffset, const uint32_t dataSize);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_GRAPHICS_GUI_GRAPHICS_API_H_ */


/*** end of file ***/
