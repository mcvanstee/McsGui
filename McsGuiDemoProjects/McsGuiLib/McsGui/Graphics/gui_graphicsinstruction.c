#include "gui_graphicsinstruction.h"

#include <stddef.h>


static inline void graphic_instructions_init(
        GraphicsInstruction_s *p_instruction,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const InstructionType_e type);

void graphics_instruction_image_init(
        GraphicsInstruction_s *p_instruction,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t dataOffset, const uint32_t dataSize)
{
    graphic_instructions_init(
            p_instruction, xPos, yPos,
            width, height, ImageInstruction);

    p_instruction->instructionData.imageData.dataOffset = dataOffset;
    p_instruction->instructionData.imageData.dataSize = dataSize;
}

void graphics_instruction_fill_init(
        GraphicsInstruction_s *p_instruction,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const Color_t fillColor, const Color_t borderColor,
        const bool fillBackground, const uint8_t borderThickness,
		const uint8_t radius)
{
    graphic_instructions_init(
            p_instruction, xPos, yPos,
            width, height, FillInstruction);

    p_instruction->instructionData.fillData.fillColor = fillColor;
    p_instruction->instructionData.fillData.borderColor = borderColor;
    p_instruction->instructionData.fillData.fillBackground = fillBackground;
    p_instruction->instructionData.fillData.borderThickness = borderThickness;
    p_instruction->instructionData.fillData.radius = radius;
}

static inline void graphic_instructions_init(
        GraphicsInstruction_s *p_instruction,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const InstructionType_e type)
{
    p_instruction->type = type;
    p_instruction->xPos = xPos;
    p_instruction->yPos = yPos;
    p_instruction->width = width;
    p_instruction->height = height;
}


/*** end of file ***/
