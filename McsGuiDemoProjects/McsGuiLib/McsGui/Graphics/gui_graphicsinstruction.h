/** @file gui_graphicsinstruction.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2023, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_GRAPHICS_GUI_GRAPHICSINSTRUCTION_H_
#define MCSGUI_GRAPHICS_GUI_GRAPHICSINSTRUCTION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "gui_config.h"


typedef enum
{
    ImageInstruction = 1,
    FillInstruction = 2,
} InstructionType_e;


typedef struct graphics_fill_data_s
{
    Color_t fillColor;
    Color_t borderColor;
    bool fillBackground;
    uint8_t borderThickness;
    uint8_t radius;
#if GUI_USE_EXTERNAL_DISPLAY
} __attribute__((__packed__)) GraphicsFillData_s;
#else
} GraphicsFillData_s;
#endif /* GUI_USE_EXTERNAL_DISPLAY */


typedef struct graphics_image_data_s
{
    uint32_t dataOffset;
#if GUI_CONFIG_USE_BITMAP_COLORS
    Color_t foreColor;
    Color_t backColor;
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */
    uint8_t dataLocation;
#if GUI_USE_EXTERNAL_DISPLAY
} __attribute__((__packed__)) GraphicsImageData_s;
#else
} GraphicsImageData_s;
#endif /* GUI_USE_EXTERNAL_DISPLAY */


typedef union instruction_data_u
{
    GraphicsFillData_s fillData;
    GraphicsImageData_s imageData;
#if GUI_USE_EXTERNAL_DISPLAY
} __attribute__((__packed__)) InstructionData_u;
#else
} InstructionData_u;
#endif /* GUI_USE_EXTERNAL_DISPLAY */


typedef struct graphics_instruction_s
{
	InstructionType_e type;
    InstructionData_u instructionData;
    uint16_t xPos;
    uint16_t yPos;
    uint16_t width;
    uint16_t height;
#if GUI_USE_EXTERNAL_DISPLAY
} __attribute__((__packed__)) GraphicsInstruction_s;
#else
} GraphicsInstruction_s;
#endif /* GUI_USE_EXTERNAL_DISPLAY */

void graphics_instruction_image_init(
    GraphicsInstruction_s *p_instruction,
    const uint16_t xPos, const uint16_t yPos,
    const uint16_t width, const uint16_t height,
    const uint32_t dataOffset, const uint8_t dataLocation
#if GUI_CONFIG_USE_BITMAP_COLORS
    , const Color_t foreColor, const Color_t backColor
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */
);

void graphics_instruction_fill_init(
        GraphicsInstruction_s *p_instruction,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const Color_t fillColor, const Color_t borderColor,
        const bool fillBackground, const uint8_t borderThickness,
		const uint8_t radius);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_GRAPHICS_GUI_GRAPHICSINSTRUCTION_H_ */
