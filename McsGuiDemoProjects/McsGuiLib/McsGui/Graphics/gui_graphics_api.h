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

#include "Core/gui_fontdata.h"

extern void graphics_drawRectFillBorder(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const uint32_t borderColor,
        const uint8_t radius, const uint32_t fillColor);

extern void graphics_drawRectBorder(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const uint32_t borderColor,
        const uint8_t radius);

extern void graphics_drawRectFill(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint8_t radius, const uint32_t color);

extern bool graphics_getBmpFileInfo(
        const uint32_t bmpKey, const uint8_t *p_properties,
        uint16_t *p_out_width, uint16_t *p_out_height,
        uint32_t *p_out_dataOffset, uint8_t *p_out_dataLocation
        );

extern bool graphics_getCharacterInfo(
        const char character, const FontData_s *p_fontData,
        uint16_t *p_out_width, uint16_t *p_out_height,
        uint32_t *p_out_dataOffset);

extern void graphics_drawImage(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t dataOffset, const uint8_t dataLocation
#if GUI_CONFIG_USE_BITMAP_COLORS
        , const uint32_t foreColor, const uint32_t backColor
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */
        );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_GRAPHICS_GUI_GRAPHICS_API_H_ */


/*** end of file ***/
