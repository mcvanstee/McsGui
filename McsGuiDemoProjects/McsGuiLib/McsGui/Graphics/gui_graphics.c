#include "gui_graphics.h"

#include <stddef.h>
#include <string.h>

#include "Graphics/gui_graphics_api.h"
#include "Core/gui_log.h"

#if GUI_USE_EXTERNAL_DISPLAY
    #include "ExternalDisplay/external_display.h"
#endif /* GUI_USE_EXTERNAL_DISPLAY */

#define FILE_KEY_NONE 0U

/* Private function declarations */
static inline void graphics_flushFillInstructions(const GraphicsInstruction_s *p_instruction);
static void graphics_addCompWithChilds(BaseComponent_s *p_baseComponent);
static void graphics_addFillInstruction(BaseComponent_s *p_baseComponent);
static void graphics_addTextInstruction(BaseComponent_s *p_baseComponent);
static void graphics_addImageInstruction(BaseComponent_s *p_baseComponent);
static void graphics_addBackgroundFill(const BaseComponent_s *p_baseComponent);
static inline void graphics_addOptimizedBackgroundFill(
        uint16_t xBase, uint16_t yBase, uint16_t widthBase, uint16_t heightBase,
        uint16_t xBmp, uint16_t yBmp, uint16_t widthBmp, uint16_t heightBmp,
        const Color_t color);
static inline void graphics_addOptimizedFillInstruction(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const Color_t color);
static void graphics_addOptBackEqualWidth(
        const uint16_t baseX1, const uint16_t baseX2, const uint16_t baseY1, const uint16_t baseY2,
        const uint16_t bmpY1, const uint16_t bmpY2,
        const Color_t color);
static void graphics_addOptBackEqualHeight(
        const uint16_t baseX1,const uint16_t baseX2, const uint16_t baseY1, const uint16_t baseY2,
        const uint16_t bmpX1, const uint16_t bmpX2,
        const Color_t color);
static void grapics_addOptBackLeft(
        const uint16_t baseX1, const uint16_t baseX2, const uint16_t baseY1, const uint16_t baseY2,
        const uint16_t bmpX2, const uint16_t bmpY1, const uint16_t bmpY2,
        const Color_t color);
static void grapics_addOptBackRight(
        const uint16_t baseX1, const uint16_t baseX2, const uint16_t baseY1, const uint16_t baseY2,
        const uint16_t bmpX1, const uint16_t bmpX2, const uint16_t bmpY1, const uint16_t bmpY2,
        const Color_t color);
static void graphics_addOptBackCenterTopBottom(
        const uint16_t baseX1, const uint16_t baseX2, const uint16_t baseY1, const uint16_t baseY2,
        const uint16_t bmpX1, const uint16_t bmpX2, const uint16_t bmpY1, const uint16_t bmpY2,
        const Color_t color);

static inline GuiSize_s graphics_getTextSize(const char *p_text, const size_t strlen, const FontData_s *p_fontData);

static void graphics_queueGraphicsInstruction(GraphicsInstruction_s *p_instruction);
static inline void graphics_clearInstructionList(void);
static void graphics_alignBmp(const BaseComponent_s *p_baseComponent,
        GraphicsInstruction_s *p_instruction);
static GuiSize_s graphics_getTextOffset(
        const BaseComponent_s *p_baseComponent, const uint16_t totalTextWidth, const uint16_t fontHeight);

/* Global variables */
typedef struct GraphicsBuffer_s
{
    uint16_t bufferLength;
    GraphicsInstruction_s buffer[GUI_CONFIG_GRAPHICS_BUFFER_SIZE];
} GraphicsBuffer_s;

static GraphicsBuffer_s graphicsBuffer;


void graphics_displayComponent(BaseComponent_s *p_base)
{
    if (!p_base->visible)
    {
        return;
    }

    if (p_base->p_childList != NULL)
    {
        graphics_addCompWithChilds(p_base);
    }
    else if ((p_base->baseType == BaseType_Fill) &&
             (p_base->p_data != NULL))
    {
        graphics_addFillInstruction(p_base);
    }
    else if (p_base->baseType == BaseType_Text)
    {
        graphics_addTextInstruction(p_base);
    }
    else if (p_base->baseType == BaseType_Image)
    {
        graphics_addImageInstruction(p_base);
    }
    else if (p_base->baseType == BaseType_Parent)
    {
    }
    else
    {
        gui_log_write(GUI_LOG_LEVEL_ERROR, "graphics_NoValidBaseType");
    }
}


void graphics_flushDisplayUpdates(void)
{
    if (graphicsBuffer.bufferLength == 0)
    {
        return;
    }

    for (int32_t i = 0; i < graphicsBuffer.bufferLength; i++)
    {
        GraphicsInstruction_s *p_instruction = &graphicsBuffer.buffer[i];
        switch (p_instruction->type)
        {
            case ImageInstruction:
                graphics_drawImage(
                        p_instruction->xPos, p_instruction->yPos,
                        p_instruction->width, p_instruction->height,
                        p_instruction->instructionData.imageData.dataOffset,
                        p_instruction->instructionData.imageData.dataLocation
#if GUI_CONFIG_USE_BITMAP_COLORS
                        ,
                        p_instruction->instructionData.imageData.foreColor,
                        p_instruction->instructionData.imageData.backColor
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */
                        );
                break;
            case FillInstruction:
                graphics_flushFillInstructions(p_instruction);
                break;
            default:
                gui_log_write(GUI_LOG_LEVEL_ERROR, "graphics_NoValidInstruction");
                break;
        }
    }

#if GUI_USE_EXTERNAL_DISPLAY
    ed_updateDisplay(graphicsBuffer.buffer, graphicsBuffer.bufferLength);
#endif /* GUI_USE_EXTERNAL_DISPLAY */

    graphics_clearInstructionList();
}


void graphics_setSizeFromBmp(BaseComponent_s *p_base)
{
    if ((p_base->baseType == BaseType_Image) && (p_base->bmpKey != FILE_KEY_NONE))
    {
        uint16_t width = 0;
        uint16_t height = 0;
        uint32_t dataOffset = 0;
        uint8_t dataLocation = 0;

        const bool bmpFound = graphics_getBmpFileInfo(
                p_base->bmpKey, p_base->properties, &width, &height, &dataOffset, &dataLocation);

        if (bmpFound)
        {
            if ((p_base->width == 0) || (p_base->width < width))
            {
                p_base->width = width;
            }

            if ((p_base->height == 0) || (p_base->height < height))
            {
                p_base->height = height;
            }
        }
        else if (p_base->bmpKey != FILE_KEY_NONE)
        {
            gui_log_write(GUI_LOG_LEVEL_DEBUG, "graphics_FileNotFound_setSizeFromBmp");
        }
        else
        {
            // File key is not set
        }
    }
    else if (p_base->baseType == BaseType_Text)
    {
        const size_t bmpNameLength = strlen(p_base->p_text);

        if (bmpNameLength == 0)
        {
            return;
        }

        const GuiSize_s size = graphics_getTextSize(p_base->p_text, bmpNameLength, (FontData_s *)p_base->p_data);

        if ((p_base->width == 0) || (p_base->width < size.width))
        {
            p_base->width = size.width;
        }

        if ((p_base->height == 0) || (p_base->height < size.height))
        {
            p_base->height = size.height;
        }
    }
    else
    {
    }
}


static inline void graphics_flushFillInstructions(const GraphicsInstruction_s *p_instruction)
{
    const GraphicsFillData_s *p_fillData = &p_instruction->instructionData.fillData;

    if (p_fillData->borderThickness == 0)
    {
        graphics_drawRectFill(
                p_instruction->xPos, p_instruction->yPos,
                p_instruction->width, p_instruction->height,
                p_fillData->radius, p_fillData->fillColor);
    }
    else if (p_fillData->fillBackground)
    {
        graphics_drawRectFillBorder(
                p_instruction->xPos, p_instruction->yPos,
                p_instruction->width, p_instruction->height,
                p_fillData->borderThickness, p_fillData->borderColor,
                p_fillData->radius, p_fillData->fillColor);
    }
    else if (!p_fillData->fillBackground)
    {
        graphics_drawRectBorder(
                p_instruction->xPos, p_instruction->yPos,
                p_instruction->width, p_instruction->height,
                p_fillData->borderThickness, p_fillData->borderColor,
                p_fillData->radius);
    }
    else
    {
        gui_log_write(GUI_LOG_LEVEL_ERROR, "graphics_NoValidFillInstruction");
    }
}


static void graphics_addCompWithChilds(BaseComponent_s *p_baseComponent)
{
    if ((p_baseComponent->baseType == BaseType_Parent) &&
        (!p_baseComponent->transparent))
    {
        graphics_addBackgroundFill(p_baseComponent);
    }
    else if ((p_baseComponent->baseType == BaseType_Fill) &&
             (p_baseComponent->p_data != NULL))
    {
        graphics_addFillInstruction(p_baseComponent);
    }
    else if (p_baseComponent->baseType == BaseType_Text)
    {
        graphics_addTextInstruction(p_baseComponent);
    }
    else if (p_baseComponent->baseType == BaseType_Image)
    {
        graphics_addImageInstruction(p_baseComponent);
    }
    else
    {
        if (p_baseComponent->baseType != BaseType_Parent)
        {
            // Error no valid baseType or p_bmpName is null
            //
            gui_log_write(GUI_LOG_LEVEL_ERROR, "graphics_NoValidChildBaseType");
        }
    }

    BaseComponent_s *p_iterator = p_baseComponent->p_childList;
    while (p_iterator != NULL)
    {
        if (p_iterator->visible)
        {
            p_iterator->onDisplay(p_iterator);
        }

        p_iterator = p_iterator->p_nextBaseComponent;
    }
}


static void graphics_addFillInstruction(BaseComponent_s *p_base)
{
    BorderData_s *p_borderData = (BorderData_s *)p_base->p_data;

    GraphicsInstruction_s instruction = {0};
    instruction.xPos = 0;

#if GUI_CONFIG_USE_ON_BEFORE_DISPLAY
    if (p_base->onBeforeDisplay != NULL)
    {
        p_base->onBeforeDisplay(p_base);
    }
#endif /* GUI_CONFIG_USE_ON_BEFORE_DISPLAY */

#if GUI_CONFIG_USE_ANCHOR
    if (NULL != p_base->p_anchor)
    {
        graphics_setPosistionFromAnchor(p_base);

#if GUI_CONFIG_USE_TOUCH
        if (NULL != p_base->p_touch)
        {
            p_base->p_touch->x = p_base->x;
            p_base->p_touch->y = p_base->y;

            if (p_base->p_touch->width == 0)
            {
                p_base->p_touch->width = p_base->width;
            }

            if (p_base->p_touch->height == 0)
            {
                p_base->p_touch->height = p_base->height;
            }
        }
#endif /* GUI_CONFIG_USE_TOUCH */
    }
#endif /* GUI_CONFIG_USE_ANCHOR */

    graphics_instruction_fill_init(
    		&instruction,
            p_base->x, p_base->y,
            p_base->width, p_base->height,
            p_base->background, p_borderData->borderColor,
            !p_base->transparent, p_borderData->borderThickness,
			p_borderData->radius);

    graphics_queueGraphicsInstruction(&instruction);
}


static void graphics_addTextInstruction(BaseComponent_s *p_baseComponent)
{
#if GUI_CONFIG_USE_ON_BEFORE_DISPLAY
    if (p_baseComponent->onBeforeDisplay != NULL)
    {
        p_baseComponent->onBeforeDisplay(p_baseComponent);
    }
#endif /* GUI_CONFIG_USE_ON_BEFORE_DISPLAY */

	const size_t bmpNameLength = strlen(p_baseComponent->p_text);
	const GuiSize_s size = graphics_getTextSize(p_baseComponent->p_text, bmpNameLength, (FontData_s *)p_baseComponent->p_data);

    if ((p_baseComponent->width == 0) || (p_baseComponent->width < size.width))
    {
        p_baseComponent->width = size.width;
    }

    if ((p_baseComponent->height == 0) || (p_baseComponent->height < size.height))
    {
        p_baseComponent->height = size.height;
    }

#if GUI_CONFIG_USE_ANCHOR
    if (NULL != p_baseComponent->p_anchor)
    {
        graphics_setPosistionFromAnchor(p_baseComponent);

#if GUI_CONFIG_USE_TOUCH
        if (NULL != p_baseComponent->p_touch)
        {
            p_baseComponent->p_touch->x = p_baseComponent->x;
            p_baseComponent->p_touch->y = p_baseComponent->y;

            if (p_baseComponent->p_touch->width == 0)
            {
                p_baseComponent->p_touch->width = p_baseComponent->width;
            }

            if (p_baseComponent->p_touch->height == 0)
            {
                p_baseComponent->p_touch->height = p_baseComponent->height;
            }
        }
#endif /* GUI_CONFIG_USE_TOUCH */
    }
#endif /* GUI_CONFIG_USE_ANCHOR */

    if (bmpNameLength == 0)
    {
        // Clear the background if it is not transparent
        //
        if (!p_baseComponent->transparent && (p_baseComponent->width > 0) && (p_baseComponent->height > 0))
        {
            graphics_addBackgroundFill(p_baseComponent);
        }

        return;
    }

    const GuiSize_s textOffset = graphics_getTextOffset(p_baseComponent, size.width, size.height);

    if (!p_baseComponent->transparent)
    {
        graphics_addOptimizedBackgroundFill(
                p_baseComponent->x, p_baseComponent->y, p_baseComponent->width, p_baseComponent->height,
                (p_baseComponent->x + textOffset.width), (p_baseComponent->y + textOffset.height),
                size.width, size.height,
                p_baseComponent->background);
    }

    uint16_t characterXPos = p_baseComponent->x + textOffset.width;
    FontData_s *p_fontData = (FontData_s *)p_baseComponent->p_data;

    for (uint_fast16_t charIndex = 0; charIndex < bmpNameLength; charIndex++)
    {
        uint16_t fontWidth = 0;
        uint16_t fontHeight = 0;
        uint32_t fontDataOffset = 0;
        uint8_t dataLocation = 0;

        bool charInfoFound = graphics_getCharacterInfo(
                p_baseComponent->p_text[charIndex],
                p_fontData,
                &fontWidth,
                &fontHeight,
                &fontDataOffset,
                &dataLocation);

        if (charInfoFound)
        {
            GraphicsInstruction_s instruction = {0};
            instruction.xPos = 0;

            graphics_instruction_image_init(
            		&instruction,
                    characterXPos, (p_baseComponent->y + textOffset.height),
                    fontWidth, fontHeight,
                    fontDataOffset, dataLocation
#if GUI_CONFIG_USE_BITMAP_COLORS
                    ,
                    p_fontData->fontColor,
                    p_fontData->backgroundColor
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */

#if GUI_USE_EXTERNAL_DISPLAY
                    , GRAPHICS_DATA_TYPE_FONT_CHAR
                    , ((uint8_t)p_baseComponent->p_text[charIndex] << 8) | ((uint8_t)p_fontData->font) // The first byte of the bmpKey is the character ASCII value, the second byte is the font key, the last 2 bytes are reserved
#if GUI_CONFIG_USE_FILE_PROPERTIES
                    , p_baseComponent->properties
#endif /* GUI_CONFIG_USE_FILE_PROPERTIES */
#endif /* GUI_USE_EXTERNAL_DISPLAY */
                    );

            graphics_queueGraphicsInstruction(&instruction);

            characterXPos += instruction.width;
        }
        else
        {
            gui_log_write(GUI_LOG_LEVEL_ERROR, "graphics_charInfoNotFound");
        }
    }
}


static void graphics_addImageInstruction(BaseComponent_s *p_baseComponent)
{
    uint16_t width = 0;
    uint16_t height = 0;
    uint32_t dataOffset = 0;
    uint8_t dataLocation = 0;

#if GUI_CONFIG_USE_ON_BEFORE_DISPLAY
    if (p_baseComponent->onBeforeDisplay != NULL)
    {
        p_baseComponent->onBeforeDisplay(p_baseComponent);
    }
#endif /* GUI_CONFIG_USE_ON_BEFORE_DISPLAY */

    const bool bmpFound = graphics_getBmpFileInfo(
            p_baseComponent->bmpKey,
			p_baseComponent->properties,
			&width, &height,
            &dataOffset,
            &dataLocation
            );

    if (p_baseComponent->width == 0)
    {
        p_baseComponent->width = width;
    }

    if (p_baseComponent->height == 0)
    {
        p_baseComponent->height = height;
    }

#if GUI_CONFIG_USE_ANCHOR
    if (NULL != p_baseComponent->p_anchor)
    {
        graphics_setPosistionFromAnchor(p_baseComponent);

#if GUI_CONFIG_USE_TOUCH
        if (NULL != p_baseComponent->p_touch)
        {
            p_baseComponent->p_touch->x = p_baseComponent->x;
            p_baseComponent->p_touch->y = p_baseComponent->y;

            if (p_baseComponent->p_touch->width == 0)
            {
                p_baseComponent->p_touch->width = p_baseComponent->width;
            }

            if (p_baseComponent->p_touch->height == 0)
            {
                p_baseComponent->p_touch->height = p_baseComponent->height;
            }
        }
#endif /* GUI_CONFIG_USE_TOUCH */
    }
#endif /* GUI_CONFIG_USE_ANCHOR */

    const bool baseTransparent = p_baseComponent->transparent;

    if (bmpFound)
    {
        GraphicsInstruction_s instruction = {0};
        instruction.xPos = 0;

        GraphicsInstruction_s *p_newInstruction = &instruction;

        graphics_instruction_image_init(
                p_newInstruction,
                p_baseComponent->x, p_baseComponent->y,
                width, height, dataOffset, dataLocation
#if GUI_CONFIG_USE_BITMAP_COLORS
                ,
                p_baseComponent->foreColor,
                p_baseComponent->background
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */

#if GUI_USE_EXTERNAL_DISPLAY
                , GRAPHICS_DATA_TYPE_BMP
                , p_baseComponent->bmpKey
#if GUI_CONFIG_USE_FILE_PROPERTIES
                , p_baseComponent->properties
#endif /* GUI_CONFIG_USE_FILE_PROPERTIES */
#endif /* GUI_USE_EXTERNAL_DISPLAY */
                );

        graphics_alignBmp(p_baseComponent, p_newInstruction);

        if (!baseTransparent)
        {
            graphics_addOptimizedBackgroundFill(
                    p_baseComponent->x, p_baseComponent->y, p_baseComponent->width, p_baseComponent->height,
                    p_newInstruction->xPos, p_newInstruction->yPos, p_newInstruction->width, p_newInstruction->height,
                    p_baseComponent->background);
        }

        graphics_queueGraphicsInstruction(p_newInstruction);
    }
    else
    {
        if (!baseTransparent)
        {
            graphics_addBackgroundFill(p_baseComponent);
        }
        else if (p_baseComponent->bmpKey != FILE_KEY_NONE)
        {
            gui_log_write(GUI_LOG_LEVEL_DEBUG, "graphics_FileNotFound");
        }
        else
        {
            // File key is not set
        }
    }
}


static void graphics_addBackgroundFill(const BaseComponent_s *p_baseComponent)
{
    GraphicsInstruction_s instruction = {0};
    instruction.xPos = 0;

    graphics_instruction_fill_init(
    		&instruction,
            p_baseComponent->x, p_baseComponent->y,
            p_baseComponent->width, p_baseComponent->height,
            p_baseComponent->background, 0,
            true, 0, 0);

    graphics_queueGraphicsInstruction(&instruction);
}


// The bitmap is somewhere in the center of the background
//  __________    __________    __________    __________    __________    __________    __________    __________    __________
// |  ______  |  |______|   |  |______    |  |          |  |          |  |  |____|  |  |   |______|  |    ______|  |          |
// | |______| |  |          |  |______|   |  |______    |  |   ____   |  |          |  |          |  |   |______|  |    ______|
// |__________|  |__________|  |__________|  |______|___|  |__|____|__|  |__________|  |__________|  |__________|  |___|______|
//      4              2            3             2              3             3             2             3             2
//
//  __________    __________    __________    __________    __________    __________
// |  |       |  |       |  |  |   |  |   |  |__________|  |          |  |__________|
// |  |       |  |       |  |  |   |  |   |  |          |  |__________|  |__________|
// |__|_______|  |_______|__|  |___|__|___|  |__________|  |__________|  |__________|
//       1            1              2            1             1             2
//
static inline void graphics_addOptimizedBackgroundFill(
        uint16_t xBase, uint16_t yBase, uint16_t widthBase, uint16_t heightBase,
        uint16_t xBmp, uint16_t yBmp, uint16_t widthBmp, uint16_t heightBmp,
        const Color_t color)
{
    if (((widthBase == widthBmp) && (heightBase == heightBmp)) ||
            (widthBmp > widthBase) || (heightBmp > heightBase))
    {
        return;
    }

    const uint16_t baseX1 = xBase;
    const uint16_t baseX2 = xBase + widthBase;
    const uint16_t baseY1 = yBase;
    const uint16_t baseY2 = yBase + heightBase;

    const uint16_t bmpX1 = xBmp;
    const uint16_t bmpX2 = xBmp + widthBmp;
    const uint16_t bmpY1 = yBmp;
    const uint16_t bmpY2 = yBmp + heightBmp;

    if (widthBase == widthBmp)
    {
        graphics_addOptBackEqualWidth(
                baseX1, baseX2, baseY1, baseY2,
                bmpY1, bmpY2,
                color);
    }
    else if (heightBase == heightBmp)
    {
        graphics_addOptBackEqualHeight(
                baseX1, baseX2, baseY1, baseY2,
                bmpX1, bmpX2,
                color);

    }
    else if (baseX1 == bmpX1)
    {
        grapics_addOptBackLeft(
                baseX1, baseX2, baseY1, baseY2,
                bmpX2, bmpY1, bmpY2,
                color);
    }
    else if (baseX2 == bmpX2)
    {
        grapics_addOptBackRight(
                baseX1, baseX2, baseY1, baseY2,
                bmpX1, bmpX2, bmpY1, bmpY2,
                color);

    }
    else if ((baseY1 == bmpY1) || (baseY2 == bmpY2))
    {
        graphics_addOptBackCenterTopBottom(
                baseX1, baseX2, baseY1, baseY2,
                bmpX1, bmpX2, bmpY1, bmpY2,
                color);
    }
    else if ((bmpX1 > baseX1) &&
             (bmpY1 > baseY1) &&
             (bmpX2 < baseX2) &&
             (bmpY2 < baseY2))
    {
        graphics_addOptimizedFillInstruction(
                xBase, yBase,
                widthBase, (uint16_t)(bmpY1 - baseY1),
                color);

        graphics_addOptimizedFillInstruction(
                xBase, bmpY1,
                (uint16_t)(bmpX1 - baseX1), heightBmp,
                color);

        graphics_addOptimizedFillInstruction(
                bmpX2, bmpY1,
                (uint16_t)(baseX2 - bmpX2), heightBmp,
                color);

        graphics_addOptimizedFillInstruction(
                xBase, bmpY2,
                widthBase, (uint16_t)(baseY2 - bmpY2),
                color);
    }
    else
    {
        gui_log_write(GUI_LOG_LEVEL_WARNING, "Cannot add background.");
    }
}


// Possible bitmap locations
//    __________    __________    __________
//   |          |  |__________|  |__________|
//   |__________|  |          |  |__________|
//   |__________|  |__________|  |__________|
//        1             1             2
//
static void graphics_addOptBackEqualWidth(
        const uint16_t baseX1, const uint16_t baseX2, const uint16_t baseY1, const uint16_t baseY2,
        const uint16_t bmpY1, const uint16_t bmpY2,
        const Color_t color)
{
    const uint16_t width = (uint16_t)(baseX2 - baseX1);

    if (baseY1 == bmpY1) // BMP is in the top
    {
        graphics_addOptimizedFillInstruction(
                baseX1, bmpY2,
                width, (uint16_t)(baseY2 - bmpY2),
                color);
    }
    else if (baseY2 == bmpY2) // BMP is in the bottom
    {
        graphics_addOptimizedFillInstruction(
                baseX1, baseY1,
                width, (uint16_t)(bmpY1 - baseY1),
                color);
    }
    else // BMP is in the center
    {
        graphics_addOptimizedFillInstruction(
                baseX1, baseY1,
                width, (uint16_t)(bmpY1 - baseY1),
                color);

        graphics_addOptimizedFillInstruction(
                baseX1, bmpY2,
                width, (uint16_t)(baseY2 - bmpY2),
                color);
    }
}


// Possible bitmap locations
//  __________    __________    __________
// |  |       |  |       |  |  |   |  |   |
// |  |       |  |       |  |  |   |  |   |
// |__|_______|  |_______|__|  |___|__|___|
//       1            1              2
//
static void graphics_addOptBackEqualHeight(
        const uint16_t baseX1, const uint16_t baseX2, const uint16_t baseY1, const uint16_t baseY2,
        const uint16_t bmpX1, const uint16_t bmpX2,
        const Color_t color)
{
    const uint16_t height = (uint16_t)(baseY2 - baseY1);

    if (baseX1 == bmpX1) // BMP is in the left
    {
        graphics_addOptimizedFillInstruction(
                bmpX2, baseY1,
                (uint16_t)(baseX2 - bmpX2), height,
                color);
    }
    else if (baseX2 == bmpX2) // BMP is in the right
    {
        graphics_addOptimizedFillInstruction(
                baseX1, baseY1,
                (uint16_t)(bmpX1 - baseX1), height,
                color);
    }
    else // BMP is in the center
    {
        graphics_addOptimizedFillInstruction(
                baseX1, baseY1,
                (uint16_t)(bmpX1 - baseX1), height,
                color);

        graphics_addOptimizedFillInstruction(
                bmpX2, baseY1,
                (uint16_t)(baseX2 - bmpX2), height,
                color);
    }
}


// Possible bitmap locations
//  __________    __________    __________
// |______|   |  |______    |  |          |
// |          |  |______|   |  |______    |
// |__________|  |__________|  |______|___|
//      2             3             2
//
static void grapics_addOptBackLeft(
        const uint16_t baseX1, const uint16_t baseX2, const uint16_t baseY1, const uint16_t baseY2,
        const uint16_t bmpX2, const uint16_t bmpY1, const uint16_t bmpY2,
        const Color_t color)
{
    const uint16_t width = (uint16_t)(baseX2 - baseX1);

    if (baseY1 == bmpY1) // BMP is in the top
    {
        graphics_addOptimizedFillInstruction(
                bmpX2, baseY1,
                baseX2 - bmpX2, baseY2 - bmpY2,
                color);
        graphics_addOptimizedFillInstruction(
                baseX1, bmpY2,
                width, baseY2 - bmpY2,
                color);
    }
    else if (baseY2 == bmpY2) // BMP is in the bottom
    {
        graphics_addOptimizedFillInstruction(
                baseX1, baseY1,
                width, bmpY1 - baseY1,
                color);
        graphics_addOptimizedFillInstruction(
                bmpX2, bmpY1,
                baseX2 - bmpX2, bmpY2 - bmpY1,
                color);
    }
    else // BMP is in the center
    {
        graphics_addOptimizedFillInstruction(
                baseX1, baseY1,
                width, bmpY1 - baseY1,
                color);
        graphics_addOptimizedFillInstruction(
                bmpX2, bmpY1,
                baseX2 - bmpX2, bmpY2 - bmpY1,
                color);
        graphics_addOptimizedFillInstruction(
                baseX1, bmpY2,
                width, baseY2 - bmpY2,
                color);
    }
}


// Possible bitmap locations
//  __________    __________    __________
// |   |______|  |    ______|  |          |
// |          |  |   |______|  |    ______|
// |__________|  |__________|  |___|______|
//      2             3             2
//
static void grapics_addOptBackRight(
        const uint16_t baseX1, const uint16_t baseX2, const uint16_t baseY1, const uint16_t baseY2,
        const uint16_t bmpX1, const uint16_t bmpX2, const uint16_t bmpY1, const uint16_t bmpY2,
        const Color_t color)
{
    const uint16_t width = (uint16_t) (baseX2 - baseX1);
    const uint16_t height = (uint16_t) (baseY2 - baseY1);

    if (baseY1 == bmpY1) // BMP is in the top
    {
        graphics_addOptimizedFillInstruction(
                baseX1, baseY1,
                bmpX1 - baseX1, height,
                color);
        graphics_addOptimizedFillInstruction(
                baseX1, bmpY2,
                width, baseY2 - bmpY2,
                color);
    }
    else if (baseY2 == bmpY2) // BMP is in the bottom
    {
        graphics_addOptimizedFillInstruction(
                baseX1, baseY1,
                width, bmpY1 - baseY1,
                color);
        graphics_addOptimizedFillInstruction(
                baseX1, bmpY1,
                bmpX1 - baseX1, bmpY2 - bmpY1,
                color);
    }
    else // BMP is in the center
    {
        graphics_addOptimizedFillInstruction(
                baseX1, baseY1,
                width, bmpY1 - baseY1,
                color);
        graphics_addOptimizedFillInstruction(
                baseX1, bmpY1,
                bmpX1 - baseX1, bmpY2 - bmpY1,
                color);
        graphics_addOptimizedFillInstruction(
                baseX1, bmpY2,
                width, baseY2 - bmpY2,
                color);
    }
}


// Possible bitmap locations
//  __________    __________
// |          |  |  |____|  |
// |   ____   |  |          |
// |__|____|__|  |__________|
//      3             3
//
static void graphics_addOptBackCenterTopBottom(
        const uint16_t baseX1, const uint16_t baseX2, const uint16_t baseY1, const uint16_t baseY2,
        const uint16_t bmpX1, const uint16_t bmpX2, const uint16_t bmpY1, const uint16_t bmpY2,
        const Color_t color)
{
    const uint16_t width = (uint16_t) (baseX2 - baseX1);

    if (baseY1 == bmpY1) // BMP is in the top
    {
        graphics_addOptimizedFillInstruction(
                baseX1, baseY1,
                bmpX1 - baseX1, bmpY2 - baseY1,
                color);
        graphics_addOptimizedFillInstruction(
                bmpX2, baseY1,
                baseX2 - bmpX2, bmpY2 - bmpY1,
                color);
        graphics_addOptimizedFillInstruction(
                baseX1, bmpY2,
                width, baseY2 - bmpY2,
                color);
    }
    else if (baseY2 == bmpY2) // BMP is in the bottom
    {
        graphics_addOptimizedFillInstruction(
                baseX1, baseY1,
                width, bmpY1 - baseY1,
                color);
        graphics_addOptimizedFillInstruction(
                baseX1, bmpY1,
                bmpX1 - baseX1, baseY2 - bmpY1,
                color);
        graphics_addOptimizedFillInstruction(
                bmpX2, bmpY1,
                bmpX1 - baseX1, baseY2 - bmpY1,
                color);
    }
    else
    {
    }
}


static inline void graphics_addOptimizedFillInstruction(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const Color_t color)
{
    GraphicsInstruction_s instruction = {0};
    instruction.xPos = 0;

    graphics_instruction_fill_init(
    		&instruction,
            xPos, yPos, width, height,
            color, 0, true, 0, 0);

    graphics_queueGraphicsInstruction(&instruction);
}

static void graphics_queueGraphicsInstruction(GraphicsInstruction_s *p_instruction)
{
    if (graphicsBuffer.bufferLength >= GUI_CONFIG_GRAPHICS_BUFFER_SIZE)
    {
        graphics_flushDisplayUpdates();
    }

    memcpy(&graphicsBuffer.buffer[graphicsBuffer.bufferLength],
           p_instruction, sizeof(GraphicsInstruction_s));

    graphicsBuffer.bufferLength += 1;
}


static inline GuiSize_s graphics_getTextSize(const char *p_text, const size_t strlen, const FontData_s *p_fontData)
{
    GuiSize_s textSize = { 0, 0 };
    uint16_t textWidth = 0;
    uint16_t textHeight = 0;

    for (uint_fast16_t charIndex = 0; charIndex < strlen; charIndex++)
    {
        uint16_t fontWidth = 0;
        uint16_t fontHeight = 0;
        uint32_t fontDataOffset = 0;
        uint8_t dataLocation = 0;

        bool charInfoFound = graphics_getCharacterInfo(p_text[charIndex],
                p_fontData, &fontWidth, &fontHeight, &fontDataOffset, &dataLocation);

        if (charInfoFound)
        {
            textWidth += fontWidth;

            if (fontHeight > textHeight)
            {
                textHeight = fontHeight;
            }
        }
        else
        {
            gui_log_write(GUI_LOG_LEVEL_ERROR, "graphics_charInfoNotFound");
        }
    }

    textSize.width = textWidth;
    textSize.height = textHeight;

    return textSize;
}


#if GUI_CONFIG_USE_ANCHOR
void graphics_setPosistionFromAnchor(BaseComponent_s *p_base)
{
    GuiAnchor_s *p_anchor = p_base->p_anchor;
    uint16_t baseX = p_base->x;
    uint16_t baseY = p_base->y;
    uint16_t baseWidth = p_base->width;
    uint16_t baseHeight = p_base->height;

    if ((Gui_Anchor_None != p_anchor->parentAnchor) && (NULL != p_anchor->p_horizontalAnchorToBase))
    {
        BaseComponent_s *p_parentBase = p_anchor->p_horizontalAnchorToBase;

        switch (p_anchor->parentAnchor)
        {
            case Gui_Anchor_Fill_Parent:
                baseX = p_parentBase->x + p_anchor->leftMargin;
                baseY = p_parentBase->y + p_anchor->topMargin;
                baseWidth = p_parentBase->width - p_anchor->leftMargin - p_anchor->rightMargin;
                baseHeight = p_parentBase->height - p_anchor->topMargin - p_anchor->bottomMargin;
                break;
            case Gui_Anchor_Center_In_Parent:
                baseX = p_parentBase->x
                      + (p_parentBase->width / 2)
                      - (p_base->width / 2)
                      + p_anchor->leftMargin
                      - p_anchor->rightMargin;
                baseY = p_parentBase->y
                      + (p_parentBase->height / 2)
                      - (p_base->height / 2)
                      + p_anchor->topMargin
                      - p_anchor->bottomMargin;
                break;
            default:
                break;
        }

        base_setPosition(p_base, baseX, baseY);
        base_setDimensions(p_base, baseWidth, baseHeight);

        return;
    }

    if ((p_anchor->horizontalAnchorPosition != Gui_Anchor_None) && (NULL != p_anchor->p_horizontalAnchorToBase))
    {
        switch (p_anchor->horizontalAnchorPosition)
        {
            case Gui_Anchor_Left:

                switch (p_anchor->horizontalAnchorPosTo)
                {
                    case Gui_Anchor_Left:
                        baseX = p_anchor->p_horizontalAnchorToBase->x + p_anchor->leftMargin;
                        break;
                    case Gui_Anchor_Right:
                        baseX = p_anchor->p_horizontalAnchorToBase->x
                              + p_anchor->p_horizontalAnchorToBase->width
                              + p_anchor->leftMargin;
                        break;
                    case Gui_Anchor_Horizontal_Center:
                        baseX = p_anchor->p_horizontalAnchorToBase->x
                              + (p_anchor->p_horizontalAnchorToBase->width / 2)
                              + p_anchor->leftMargin
                              - p_anchor->rightMargin;
                        break;
                    default:
                        break;
                }
                break;
            case Gui_Anchor_Right:

                switch (p_anchor->horizontalAnchorPosTo)
                {
                    case Gui_Anchor_Left:
                        baseX = p_anchor->p_horizontalAnchorToBase->x
                              - p_base->width
                              - p_anchor->rightMargin;
                        break;
                    case Gui_Anchor_Right:
                        baseX = p_anchor->p_horizontalAnchorToBase->x
                              + p_anchor->p_horizontalAnchorToBase->width
                              - p_base->width
                              - p_anchor->rightMargin;
                        break;
                    case Gui_Anchor_Horizontal_Center:
                        baseX = p_anchor->p_horizontalAnchorToBase->x
                              + (p_anchor->p_horizontalAnchorToBase->width / 2)
                              + p_anchor->leftMargin
                              - p_anchor->rightMargin;
                        break;
                    default:
                        break;
                }
                break;
            case Gui_Anchor_Horizontal_Center:
                if (p_anchor->horizontalAnchorPosTo
                        == Gui_Anchor_Horizontal_Center)
                {
                    baseX = p_anchor->p_horizontalAnchorToBase->x
                          + (p_anchor->p_horizontalAnchorToBase->width / 2)
                          - (p_base->width / 2)
                          + p_anchor->leftMargin
                          - p_anchor->rightMargin;
                }
                break;
            default:
                break;
        }
    }

    if ((p_anchor->verticalAnchorPosition != Gui_Anchor_None) && (NULL != p_anchor->p_verticalAnchorToBase))
    {
        switch (p_anchor->verticalAnchorPosition)
        {
            case Gui_Anchor_Top:

                switch (p_anchor->verticalAnchorPosTo)
                {
                    case Gui_Anchor_Top:
                        baseY = p_anchor->p_verticalAnchorToBase->y
                              + p_anchor->topMargin;
                        break;
                    case Gui_Anchor_Bottom:
                        baseY = p_anchor->p_verticalAnchorToBase->y
                              + p_anchor->p_verticalAnchorToBase->height
                              + p_anchor->topMargin;
                        break;
                    case Gui_Anchor_Vertical_Center:
                        baseY = p_anchor->p_verticalAnchorToBase->y
                              + (p_anchor->p_verticalAnchorToBase->height / 2)
                              + p_anchor->topMargin
                              - p_anchor->bottomMargin;
                        break;
                    default:
                        break;
                }
                break;
            case Gui_Anchor_Bottom:

                switch (p_anchor->verticalAnchorPosTo)
                {
                    case Gui_Anchor_Top:
                        baseY = p_anchor->p_verticalAnchorToBase->y
                              - p_base->height - p_anchor->bottomMargin;
                        break;
                    case Gui_Anchor_Bottom:
                        baseY = p_anchor->p_verticalAnchorToBase->y
                              + p_anchor->p_verticalAnchorToBase->height
                              - p_base->height - p_anchor->bottomMargin;
                        break;
                    case Gui_Anchor_Vertical_Center:
                        baseY = p_anchor->p_verticalAnchorToBase->y
                              + (p_anchor->p_verticalAnchorToBase->height / 2)
                              + p_anchor->topMargin
                              - p_anchor->bottomMargin;
                        break;
                    default:
                        break;
                }
                break;
            case Gui_Anchor_Vertical_Center:
                if (p_anchor->verticalAnchorPosTo == Gui_Anchor_Vertical_Center)
                {
                    baseY = p_anchor->p_verticalAnchorToBase->y
                          + (p_anchor->p_verticalAnchorToBase->height / 2)
                          - (p_base->height / 2)
                          + p_anchor->topMargin
                          - p_anchor->bottomMargin;
                }
                break;
            default:
                break;
        }
    }

    base_setPosition(p_base, baseX, baseY);
}
#endif /* GUI_CONFIG_USE_ANCHOR */


static inline void graphics_clearInstructionList(void)
{
    graphicsBuffer.bufferLength = 0;
}


static void graphics_alignBmp(
        const BaseComponent_s *p_baseComponent,
        GraphicsInstruction_s *p_instruction)
{
    if ((p_baseComponent->width < p_instruction->width) ||
        (p_baseComponent->height < p_instruction->height))
    {
        return;
    }

    switch (p_baseComponent->horizontalAlignment)
    {
        case Gui_Align_Left:
            p_instruction->xPos += p_baseComponent->leftPadding;
            break;
        case Gui_Align_Center:
            p_instruction->xPos += (uint16_t)((p_baseComponent->width - p_instruction->width) / 2);
            p_instruction->xPos += p_baseComponent->leftPadding;
            p_instruction->xPos -= p_baseComponent->rightPadding;
            break;
        case Gui_Align_Right:
            p_instruction->xPos += (uint16_t)(p_baseComponent->width - p_instruction->width);
            p_instruction->xPos -= p_baseComponent->rightPadding;
            break;
        default:
            break;
    }

    switch (p_baseComponent->verticalAlignment)
    {
        case Gui_Align_Top:
            p_instruction->yPos += p_baseComponent->topPadding;
            break;
        case Gui_Align_Center:
            p_instruction->yPos += (uint16_t)((p_baseComponent->height - p_instruction->height) / 2);
            p_instruction->yPos += p_baseComponent->topPadding;
            p_instruction->yPos -= p_baseComponent->bottomPadding;
            break;
        case Gui_Align_Bottom:
            p_instruction->yPos += (uint16_t)(p_baseComponent->height - p_instruction->height);
            p_instruction->yPos -= p_baseComponent->bottomPadding;
            break;
        default:
            break;
    }
}


static GuiSize_s graphics_getTextOffset(
        const BaseComponent_s *p_baseComponent, const uint16_t totalTextWidth, const uint16_t fontHeight)
{
    int32_t horizontalTextOffset = 0;
    int32_t verticalTextOffset = 0;

    switch (p_baseComponent->horizontalAlignment)
    {
        case Gui_Align_Left:
            horizontalTextOffset += p_baseComponent->leftPadding;
            break;
        case Gui_Align_Center:
            horizontalTextOffset += ((p_baseComponent->width - totalTextWidth) / 2);
            horizontalTextOffset += p_baseComponent->leftPadding;
            horizontalTextOffset -= p_baseComponent->rightPadding;
            break;
        case Gui_Align_Right:
            horizontalTextOffset += (p_baseComponent->width - totalTextWidth);
            horizontalTextOffset -= p_baseComponent->rightPadding;
            break;
        default:
            break;
    }

    switch (p_baseComponent->verticalAlignment)
    {
        case Gui_Align_Top:
            verticalTextOffset += p_baseComponent->topPadding;
            break;
        case Gui_Align_Center:
            verticalTextOffset += ((p_baseComponent->height - fontHeight) / 2);
            verticalTextOffset += p_baseComponent->topPadding;
            verticalTextOffset -= p_baseComponent->bottomPadding;
            break;
        case Gui_Align_Bottom:
            verticalTextOffset += (p_baseComponent->height - fontHeight);
            verticalTextOffset -= p_baseComponent->bottomPadding;
            break;
        default:
            break;
    }

    if (verticalTextOffset < 0)
    {
        verticalTextOffset = 0;
    }

    if (horizontalTextOffset < 0)
    {
        horizontalTextOffset = 0;
    }

    return (GuiSize_s){horizontalTextOffset, verticalTextOffset};
}


/*** end of file ***/
