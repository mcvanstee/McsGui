/** @file gui_graphicsinstruction.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_GRAPHICS_GUI_GRAPHICSINSTRUCTION_H_
#define MCSGUI_GRAPHICS_GUI_GRAPHICSINSTRUCTION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "McsGui/gui_config.h"


typedef enum
{
    ImageInstruction = 1,
    FillInstruction = 2,
} InstructionType_e;

typedef struct graphics_fill_data_s
{
    bool fillBackground;
    Color_t fillColor;
    Color_t borderColor;
    uint8_t borderThickness;
} GraphicsFillData_s;

typedef struct graphics_image_data_s
{
    uint32_t dataOffset;
    uint32_t dataSize;
} GraphicsImageData_s;

typedef union instruction_data_u
{
    GraphicsFillData_s fillData;
    GraphicsImageData_s imageData;
} InstructionData_u;

typedef struct graphics_instruction_s
{
    InstructionType_e type;
    InstructionData_u instructionData;
    uint16_t xPos;
    uint16_t yPos;
    uint16_t width;
    uint16_t height;
    struct graphics_instruction_s *p_nextInstruction;
} GraphicsInstruction_s;


#if GUI_USE_DYNAMIC_MEMORY
GraphicsInstruction_s *graphics_instruction_new(void);

void graphics_instruction_delete(
        GraphicsInstruction_s *p_graphicsInstruction);
#endif /* GUI_USE_DYNAMIC_MEMORY */

void graphics_instruction_image_init(
        GraphicsInstruction_s *p_instruction,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t dataOffset, const uint32_t dataSize);

void graphics_instruction_fill_init(
        GraphicsInstruction_s *p_instruction,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const Color_t fillColor, const Color_t borderColor,
        const bool fillBackground, const uint8_t borderThickness);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_GRAPHICS_GUI_GRAPHICSINSTRUCTION_H_ */
