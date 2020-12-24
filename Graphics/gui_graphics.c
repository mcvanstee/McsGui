#include "gui_graphics.h"

#include <stddef.h>
#include <string.h>

#include "McsGui/Graphics/gui_graphics_api.h"
#include "McsGui/Utils/gui_log.h"


/* Private function declarations */
static inline void graphics_flushFillInstructions(const GraphicsInstruction_s *p_instruction);
static void graphics_addCompWithChilds(BaseComponent_s *p_baseComponent);
static void graphics_addFillInstruction(BaseComponent_s *p_baseComponent);
static void graphics_addTextInstruction(BaseComponent_s *p_baseComponent);
static void graphics_addImageInstruction(BaseComponent_s *p_baseComponent);
static void graphics_addBackgroundFill(const BaseComponent_s *p_baseComponent);
static inline void graphics_addOptimizedBackgroundFill(const BaseComponent_s *p_base, const GraphicsInstruction_s *p_bmp);
static inline void graphics_addOptimizedFillInstruction(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const Color_t color);

static void graphics_queueGraphicsInstruction(GraphicsInstruction_s *p_instruction);
static inline void graphics_clearInstructionList(void);

#if GUI_CONFIG_USE_ALIGNMENT
static void graphics_alignBmp(const BaseComponent_s *p_baseComponent,
        GraphicsInstruction_s *p_instruction);
#endif /* GUI_CONFIG_USE_ALIGNMENT */

static void graphics_alignText(
        GraphicsInstruction_s *p_firstCharInstruction,
        const uint16_t totalTextWidth,
        const BaseComponent_s *p_baseComponent);


/* Global variables */
#if GUI_USE_DYNAMIC_MEMORY
static GraphicsInstruction_s *p_graphicsInstructionList = NULL;
static GraphicsInstruction_s *p_lastAddedInstruction = NULL;
#else

typedef struct GraphicsBuffer_s
{
    uint16_t bufferLength;
    GraphicsInstruction_s buffer[GUI_CONFIG_GRAPHICS_BUFFER_SIZE];
} GraphicsBuffer_s;

static GraphicsBuffer_s graphicsBuffer;

#endif /* GUI_USE_DYNAMIC_MEMORY */


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
    else if ((p_base->baseType == BaseType_Text) &&
             (p_base->p_bmpName != NULL))
    {
        graphics_addTextInstruction(p_base);
    }
    else if ((p_base->baseType == BaseType_Image) &&
             (p_base->p_bmpName != NULL))
    {
        graphics_addImageInstruction(p_base);
    }
    else
    {
        gui_log_write(GUI_LOG_LEVEL_ERROR, "graphics_NoValidBaseType");
    }
}

void graphics_flushDisplayUpdates(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    if (p_graphicsInstructionList == NULL)
    {
        return;
    }

    GraphicsInstruction_s *p_iterator = p_graphicsInstructionList;

    while (p_iterator != NULL)
    {
        switch (p_iterator->type)
        {
            case ImageInstruction:
                graphics_drawImage(
                        p_iterator->xPos, p_iterator->yPos,
                        p_iterator->width, p_iterator->height,
                        p_iterator->instructionData.imageData.dataOffset,
                        p_iterator->instructionData.imageData.dataSize);
                break;
            case FillInstruction:
                graphics_flushFillInstructions(p_iterator);
                break;
            default:
                gui_log_write(GUI_LOG_LEVEL_ERROR, "graphics_NoValidInstruction");
                break;
        }

        p_iterator = p_iterator->p_nextInstruction;
    }
#else
    if (graphicsBuffer.bufferLength == 0)
    {
        return;
    }

    for (int_fast16_t i = 0; i < graphicsBuffer.bufferLength; i++)
    {
        GraphicsInstruction_s *p_instruction = &graphicsBuffer.buffer[i];
        switch (p_instruction->type)
        {
            case ImageInstruction:
                graphics_drawImage(
                        p_instruction->xPos, p_instruction->yPos,
                        p_instruction->width, p_instruction->height,
                        p_instruction->instructionData.imageData.dataOffset,
                        p_instruction->instructionData.imageData.dataSize);
                break;
            case FillInstruction:
                graphics_flushFillInstructions(p_instruction);
                break;
            default:
                gui_log_write(GUI_LOG_LEVEL_ERROR, "graphics_NoValidInstruction");
                break;
        }
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */

    graphics_clearInstructionList();
}

static inline void graphics_flushFillInstructions(const GraphicsInstruction_s *p_instruction)
{
    const GraphicsFillData_s *p_fillData = &p_instruction->instructionData.fillData;

    if (p_fillData->borderThickness == 0)
    {
        graphics_drawRectFill(
                p_instruction->xPos, p_instruction->yPos,
                p_instruction->width, p_instruction->height,
                p_fillData->fillColor);
    }
    else if (p_fillData->fillBackground)
    {
        graphics_drawRectFillBorder(
                p_instruction->xPos, p_instruction->yPos,
                p_instruction->width, p_instruction->height,
                p_fillData->borderThickness, p_fillData->borderColor,
                p_fillData->fillColor);
    }
    else if (!p_fillData->fillBackground)
    {
        graphics_drawRectBorder(
                p_instruction->xPos, p_instruction->yPos,
                p_instruction->width, p_instruction->height,
                p_fillData->borderThickness, p_fillData->borderColor);
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
    else if ((p_baseComponent->baseType == BaseType_Text) &&
             (p_baseComponent->p_bmpName != NULL))
    {
        graphics_addTextInstruction(p_baseComponent);
    }
    else if ((p_baseComponent->baseType == BaseType_Image) &&
             (p_baseComponent->p_bmpName != NULL))
    {
        graphics_addImageInstruction(p_baseComponent);
    }
    else
    {
        if (p_baseComponent->baseType != BaseType_Parent)
        {
            // Error no valid baseType or p_bmpName is null
            gui_log_write(GUI_LOG_LEVEL_ERROR, "graphics_NoValidChildBaseType");
        }
    }

    BaseComponent_s *p_iterator = p_baseComponent->p_childList;
    while (p_iterator != NULL)
    {
        graphics_displayComponent(p_iterator);
        p_iterator = p_iterator->p_nextBaseComponent;
    }
}

static void graphics_addFillInstruction(BaseComponent_s *p_baseComponent)
{
    FillData_s *p_fillData = (FillData_s *)p_baseComponent->p_data;

#if GUI_USE_DYNAMIC_MEMORY
    GraphicsInstruction_s *p_newInstruction = graphics_instruction_new();
#else
    GraphicsInstruction_s instruction;
    instruction.xPos = 0;

    GraphicsInstruction_s *p_newInstruction = &instruction;
#endif /* GUI_USE_DYNAMIC_MEMORY */

#if GUI_CONFIG_USE_ON_BEFORE_DISPLAY
    if (p_baseComponent->onBeforeDisplay != NULL)
    {
        p_baseComponent->onBeforeDisplay(p_baseComponent);
    }
#endif /* GUI_CONFIG_USE_ON_BEFORE_DISPLAY */

    graphics_instruction_fill_init(
            p_newInstruction,
            p_baseComponent->xPos, p_baseComponent->yPos,
            p_baseComponent->width, p_baseComponent->height,
            p_baseComponent->background, p_fillData->borderColor,
            !p_baseComponent->transparent, p_fillData->borderThickness);

    graphics_queueGraphicsInstruction(p_newInstruction);
}

static void graphics_addTextInstruction(BaseComponent_s *p_baseComponent)
{
    if (!p_baseComponent->transparent)
    {
        graphics_addBackgroundFill(p_baseComponent);
    }

    GraphicsInstruction_s *p_firstCharacterInstruction = NULL;
    uint16_t characterXPos = p_baseComponent->xPos;
    size_t bmpNameLength = strlen(p_baseComponent->p_bmpName);

#if GUI_CONFIG_USE_ON_BEFORE_DISPLAY
    if (p_baseComponent->onBeforeDisplay != NULL)
    {
        p_baseComponent->onBeforeDisplay(p_baseComponent);
    }
#endif /* GUI_CONFIG_USE_ON_BEFORE_DISPLAY */

    for (uint_fast16_t charIndex = 0; charIndex < bmpNameLength; charIndex++)
    {
        FontData_s *p_fontData = (FontData_s *)p_baseComponent->p_data;
        uint16_t fontWidth = 0;
        uint16_t fontHeight = 0;
        uint32_t fontDataOffset = 0;
        uint32_t fontDataSize = 0;

        bool charInfoFound = graphics_getCharacterInfo(
                p_baseComponent->p_bmpName[charIndex],
                p_fontData,
                &fontWidth,
                &fontHeight,
                &fontDataOffset,
                &fontDataSize);

        if (charInfoFound)
        {
#if GUI_USE_DYNAMIC_MEMORY
            GraphicsInstruction_s *p_newCharacterInstruction = graphics_instruction_new();
#else
            GraphicsInstruction_s instruction;
            instruction.xPos = 0;

            GraphicsInstruction_s *p_newCharacterInstruction = &instruction;
#endif /* GUI_USE_DYNAMIC_MEMORY */

            graphics_instruction_image_init(
                    p_newCharacterInstruction,
                    characterXPos, p_baseComponent->yPos,
                    fontWidth, fontHeight,
                    fontDataOffset, fontDataSize);

            if (p_firstCharacterInstruction == NULL)
            {
                p_firstCharacterInstruction = p_newCharacterInstruction;
            }

            graphics_queueGraphicsInstruction(p_newCharacterInstruction);

            characterXPos += p_newCharacterInstruction->width;
        }
        else
        {
            gui_log_write(GUI_LOG_LEVEL_ERROR, "graphics_charInfoNotFound");
        }
    }

    uint_fast16_t totalTextWidth = (uint16_t)(characterXPos - p_baseComponent->xPos);
    graphics_alignText(p_firstCharacterInstruction, (uint16_t)totalTextWidth, p_baseComponent);
}

static void graphics_addImageInstruction(BaseComponent_s *p_baseComponent)
{
    uint16_t width = 0;
    uint16_t height = 0;
    uint32_t dataOffset = 0;
    uint32_t dataSize = 0;

#if GUI_CONFIG_USE_ON_BEFORE_DISPLAY
    if (p_baseComponent->onBeforeDisplay != NULL)
    {
        p_baseComponent->onBeforeDisplay(p_baseComponent);
    }
#endif /* GUI_CONFIG_USE_ON_BEFORE_DISPLAY */

    bool bmpFound = graphics_getBmpFileInfo(
            p_baseComponent->p_bmpName, &width, &height,
            &dataOffset, &dataSize);

    bool baseTransparent = p_baseComponent->transparent;

    if (bmpFound)
    {
#if GUI_USE_DYNAMIC_MEMORY
        GraphicsInstruction_s *p_newInstruction = graphics_instruction_new();
#else
        GraphicsInstruction_s instruction;
        instruction.xPos = 0;

        GraphicsInstruction_s *p_newInstruction = &instruction;
#endif /* GUI_USE_DYNAMIC_MEMORY */
        graphics_instruction_image_init(
                p_newInstruction,
                p_baseComponent->xPos, p_baseComponent->yPos,
                width, height, dataOffset, dataSize);

#if GUI_CONFIG_USE_ALIGNMENT
        graphics_alignBmp(p_baseComponent, p_newInstruction);
#endif /* GUI_CONFIG_USE_ALIGNMENT */

        if (!baseTransparent)
        {
            graphics_addOptimizedBackgroundFill(p_baseComponent, p_newInstruction);
        }

        graphics_queueGraphicsInstruction(p_newInstruction);
    }
    else
    {
        if (!baseTransparent)
        {
            graphics_addBackgroundFill(p_baseComponent);
        }
        else
        {
            gui_log_write(GUI_LOG_LEVEL_ERROR, "graphics_bmpFileInfoNotFound");
        }
    }
}

static void graphics_addBackgroundFill(const BaseComponent_s *p_baseComponent)
{
#if GUI_USE_DYNAMIC_MEMORY
    GraphicsInstruction_s *p_newInstruction = graphics_instruction_new();
#else
    GraphicsInstruction_s instruction;
    instruction.xPos = 0;

    GraphicsInstruction_s *p_newInstruction = &instruction;
#endif /* GUI_USE_DYNAMIC_MEMORY */

    graphics_instruction_fill_init(
            p_newInstruction,
            p_baseComponent->xPos, p_baseComponent->yPos,
            p_baseComponent->width, p_baseComponent->height,
            p_baseComponent->background, 0,
            true, 0);

    graphics_queueGraphicsInstruction(p_newInstruction);
}

static inline void graphics_addOptimizedBackgroundFill(
        const BaseComponent_s *p_base,
        const GraphicsInstruction_s *p_bmp)
{
    uint16_t baseX1 = p_base->xPos;
    uint16_t baseX2 = p_base->xPos + p_base->width;
    uint16_t baseY1 = p_base->yPos;
    uint16_t baseY2 = p_base->yPos + p_base->height;

    uint16_t bmpX1 = p_bmp->xPos;
    uint16_t bmpX2 = p_bmp->xPos + p_bmp->width;
    uint16_t bmpY1 = p_bmp->yPos;
    uint16_t bmpY2 = p_bmp->yPos + p_bmp->height;

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

    if ((bmpX1 > baseX1) &&
        (bmpY1 > baseY1) &&
        (bmpX2 < baseX2) &&
        (bmpY2 < baseY2)) // graphics_isInCenter
    {
        graphics_addOptimizedFillInstruction(
                p_base->xPos, p_base->yPos,
                p_base->width, (uint16_t)(bmpY1 - baseY1),
                p_base->background);

        graphics_addOptimizedFillInstruction(
                p_base->xPos, bmpY1,
                (uint16_t)(bmpX1 - baseX1), p_bmp->height,
                p_base->background);

        graphics_addOptimizedFillInstruction(
                bmpX2, bmpY1,
                (uint16_t)(baseX2 - bmpX2), p_bmp->height,
                p_base->background);

        graphics_addOptimizedFillInstruction(
                p_base->xPos, bmpY2,
                p_base->width, (uint16_t)(baseY2 - bmpY2),
                p_base->background);
    }
    else
    {
        graphics_addOptimizedFillInstruction(
                p_base->xPos, p_base->yPos,
                p_base->width, p_base->height,
                p_base->background);
    }
}

static inline void graphics_addOptimizedFillInstruction(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const Color_t color)
{
#if GUI_USE_DYNAMIC_MEMORY
    GraphicsInstruction_s *p_instruction = graphics_instruction_new();
#else
    GraphicsInstruction_s instruction;
    instruction.xPos = 0;

    GraphicsInstruction_s *p_instruction = &instruction;
#endif /* GUI_USE_DYNAMIC_MEMORY */

    graphics_instruction_fill_init(
            p_instruction,
            xPos, yPos, width, height,
            color, 0, true, 0);

    graphics_queueGraphicsInstruction(p_instruction);
}

static void graphics_queueGraphicsInstruction(GraphicsInstruction_s *p_instruction)
{
#if GUI_USE_DYNAMIC_MEMORY
    if (p_graphicsInstructionList == NULL)
    {
        p_graphicsInstructionList = p_instruction;
        p_lastAddedInstruction = p_instruction;
    }
    else
    {
        p_lastAddedInstruction->p_nextInstruction = p_instruction;
        p_lastAddedInstruction = p_instruction;
    }
#else
    if (graphicsBuffer.bufferLength >= GUI_CONFIG_GRAPHICS_BUFFER_SIZE)
    {
        graphics_flushDisplayUpdates();
    }

    memcpy(&graphicsBuffer.buffer[graphicsBuffer.bufferLength],
           p_instruction, sizeof(GraphicsInstruction_s));

    graphicsBuffer.bufferLength += 1;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

static inline void graphics_clearInstructionList(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    GraphicsInstruction_s *p_iterator = p_graphicsInstructionList;

    while (p_iterator != NULL)
    {
        GraphicsInstruction_s *p_toDelete = p_iterator;
        p_iterator = p_iterator->p_nextInstruction;

        graphics_instruction_delete(p_toDelete);
    }

    p_graphicsInstructionList = NULL;
    p_lastAddedInstruction = NULL;
#else
    graphicsBuffer.bufferLength = 0;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

#if GUI_CONFIG_USE_ALIGNMENT
static void graphics_alignBmp(
        const BaseComponent_s *p_baseComponent,
        GraphicsInstruction_s *p_instruction)
{
    if ((p_baseComponent->width <= p_instruction->width) ||
        (p_baseComponent->height <= p_instruction->height))
    {
        return;
    }

    switch (p_baseComponent->horizontalAlignment)
    {
    case AlignLeft:
#if GUI_CONFIG_USE_MARGIN
        p_instruction->xPos += p_baseComponent->leftMargin;
#endif /* GUI_CONFIG_USE_MARGIN */
        break;
    case AlignCenter:
        p_instruction->xPos += (uint16_t)((p_baseComponent->width - p_instruction->width) / 2);
#if GUI_CONFIG_USE_MARGIN
        p_instruction->xPos += p_baseComponent->leftMargin;
        p_instruction->xPos -= p_baseComponent->rightMargin;
#endif /* GUI_CONFIG_USE_MARGIN */
        break;
    case AlignRight:
        p_instruction->xPos += (uint16_t)(p_baseComponent->width - p_instruction->width);
#if GUI_CONFIG_USE_MARGIN
        p_instruction->xPos -= p_baseComponent->rightMargin;
#endif /* GUI_CONFIG_USE_MARGIN */
        break;
    default:
        break;
    }

    switch (p_baseComponent->verticalAlignment)
    {
    case AlignTop:
#if GUI_CONFIG_USE_MARGIN
        p_instruction->yPos += p_baseComponent->topMargin;
#endif /* GUI_CONFIG_USE_MARGIN */
        break;
    case AlignCenter:
        p_instruction->yPos += (uint16_t)((p_baseComponent->height - p_instruction->height) / 2);
#if GUI_CONFIG_USE_MARGIN
        p_instruction->yPos += p_baseComponent->topMargin;
        p_instruction->yPos -= p_baseComponent->bottomMargin;
#endif /* GUI_CONFIG_USE_MARGIN */
        break;
    case AlignBottom:
        p_instruction->yPos += (uint16_t)(p_baseComponent->height - p_instruction->height);
#if GUI_CONFIG_USE_MARGIN
        p_instruction->yPos -= p_baseComponent->bottomMargin;
#endif /* GUI_CONFIG_USE_MARGIN */
        break;
    default:
        break;
    }
}

#endif /* GUI_CONFIG_USE_ALIGNMENT */


#if GUI_CONFIG_USE_ALIGNMENT
static void graphics_alignText(
        GraphicsInstruction_s *p_firstCharInstruction,
        const uint16_t totalTextWidth,
        const BaseComponent_s *p_baseComponent)
{
    uint16_t fontHeight = p_firstCharInstruction->height;
    int32_t horizontalTextOffset = 0;
    int32_t verticalTextOffset = 0;

    switch (p_baseComponent->horizontalAlignment)
    {
    case AlignLeft:
#if GUI_CONFIG_USE_MARGIN
        horizontalTextOffset += p_baseComponent->leftMargin;
#endif /* GUI_CONFIG_USE_MARGIN */
        break;
    case AlignCenter:
        horizontalTextOffset += ((p_baseComponent->width - totalTextWidth) / 2);
#if GUI_CONFIG_USE_MARGIN
        horizontalTextOffset += p_baseComponent->leftMargin;
        horizontalTextOffset -= p_baseComponent->rightMargin;
#endif /* GUI_CONFIG_USE_MARGIN */
        break;
    case AlignRight:
        horizontalTextOffset += (p_baseComponent->width - totalTextWidth);
#if GUI_CONFIG_USE_MARGIN
        horizontalTextOffset -= p_baseComponent->rightMargin;
#endif /* GUI_CONFIG_USE_MARGIN */
        break;
    default:
        break;
    }

    switch (p_baseComponent->verticalAlignment)
    {
    case AlignTop:
#if GUI_CONFIG_USE_MARGIN
        verticalTextOffset += p_baseComponent->topMargin;
#endif /* GUI_CONFIG_USE_MARGIN */
        break;
    case AlignCenter:
        verticalTextOffset += ((p_baseComponent->height - fontHeight) / 2);
#if GUI_CONFIG_USE_MARGIN
        verticalTextOffset += p_baseComponent->topMargin;
        verticalTextOffset -= p_baseComponent->bottomMargin;
#endif /* GUI_CONFIG_USE_MARGIN */
        break;
    case AlignBottom:
        verticalTextOffset += (p_baseComponent->height - fontHeight);
#if GUI_CONFIG_USE_MARGIN
        verticalTextOffset -= p_baseComponent->bottomMargin;
#endif /* GUI_CONFIG_USE_MARGIN */
        break;
    default:
        break;
    }

    GraphicsInstruction_s *p_iterator = p_firstCharInstruction;
    while (p_iterator != NULL)
    {
        p_iterator->yPos += (uint16_t)verticalTextOffset;
        p_iterator->xPos += (uint16_t)horizontalTextOffset;
        p_iterator = p_iterator->p_nextInstruction;
    }
}

#endif /* GUI_CONFIG_USE_ALIGNMENT */


/*** end of file ***/
