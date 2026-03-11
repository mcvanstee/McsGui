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
        const uint32_t dataOffset, const uint8_t dataLocation
#if GUI_CONFIG_USE_BITMAP_COLORS
        , const Color_t foreColor, const Color_t backColor
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */

#if GUI_USE_EXTERNAL_DISPLAY
    , uint8_t dataType, uint32_t bmpKey
#if GUI_CONFIG_USE_FILE_PROPERTIES
    , uint8_t *p_properties
#endif /* GUI_CONFIG_USE_FILE_PROPERTIES */
#endif /* GUI_USE_EXTERNAL_DISPLAY */
        )
{
    graphic_instructions_init(
            p_instruction, xPos, yPos,
            width, height, ImageInstruction);

    p_instruction->instructionData.imageData.dataOffset = dataOffset;
    p_instruction->instructionData.imageData.dataLocation = dataLocation;
#if GUI_CONFIG_USE_BITMAP_COLORS
    p_instruction->instructionData.imageData.foreColor = foreColor;
    p_instruction->instructionData.imageData.backColor = backColor;
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */

#if GUI_USE_EXTERNAL_DISPLAY
    if (GRAPHICS_DATA_TYPE_BMP == dataType)
    {
        p_instruction->instructionData.imageData.dataType = dataType;
        p_instruction->instructionData.imageData.bmpKey = bmpKey;
    }
    else
    {
        // For font character, the first byte of the bmpKey is the character ASCII value,
        // the second byte is the font key, the last 2 bytes are reserved
        p_instruction->instructionData.imageData.dataType = dataType;
        p_instruction->instructionData.imageData.bmpKey = bmpKey;     // [X] [X] [fontKey] [ASCII]
    }
#if GUI_CONFIG_USE_FILE_PROPERTIES
    if ((GRAPHICS_DATA_TYPE_BMP == dataType) && (GUI_CONFIG_NUMBER_OF_PROPERTIES > 0))
    {
        for (uint8_t i = 0; i < GUI_CONFIG_NUMBER_OF_PROPERTIES; i++)
        {
            p_instruction->instructionData.imageData.properties[i] = p_properties[i];
        }
    }
#endif /* GUI_CONFIG_USE_FILE_PROPERTIES */
#endif /* GUI_USE_EXTERNAL_DISPLAY */

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
