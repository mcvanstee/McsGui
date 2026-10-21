#include "gui_textblock.h"

#include <stddef.h>
#include <string.h>

#include "Core/gui_log.h"
#include "Core/gui_memory.h"

static void textblock_delete(BaseComponent_s *p_textBlockBase);

#if !GUI_USE_DYNAMIC_MEMORY
static bool staticTextBMemInUse[GUI_CONFIG_TEXTBLOCK_BUFFER_SIZE] = {0};
static TextBlock_s staticTextBMem[GUI_CONFIG_TEXTBLOCK_BUFFER_SIZE] = {0};
#endif /* GUI_USE_DYNAMIC_MEMORY */

/**
 * @brief Creates a new malloced TextBlock component.
 * @return Pointer to the malloced memory.
 *
 * @warning The returned component is not initialized.
 *
 */
TextBlock_s *textblock_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(TextBlock_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_TEXTBLOCK_BUFFER_SIZE; i++)
    {
    	if (!staticTextBMemInUse[i])
    	{
    		staticTextBMemInUse[i] = true;

    		return &staticTextBMem[i];
    	}
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No TextBlock_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Creates a new TextBlock_s component and initializes it to default values.
 * @return Pointer to the TextBlock_s component.
 *
 */
TextBlock_s *textblock_newInit(void)
{
	TextBlock_s *p_textBlock = textblock_new();
	textblock_init(p_textBlock);

	return p_textBlock;
}


/**
 * @brief Delete the TextBlock component. This functions calls the gui_mem_free function to free the allocated memory.
 * @param[in] p_textBlockBase Pointer to the TextBlock component to be freed.
 *
 */
static void textblock_delete(BaseComponent_s *p_textBlockBase)
{
    base_clear(p_textBlockBase);

#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_textBlockBase, sizeof(TextBlock_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_TEXTBLOCK_BUFFER_SIZE; i++)
    {
    	if (&staticTextBMem[i].base == p_textBlockBase)
    	{
    		staticTextBMemInUse[i] = false;
    		break;
    	}
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Initialize the TextBlock component to the default values.
 * @param[in] p_textBlock Pointer to the TextBlock component to be freed.
 *
 */
void textblock_init(TextBlock_s *p_textBlock)
{
    fontdata_init(&p_textBlock->fontData);
    base_initTextComp(&p_textBlock->base, p_textBlock->text, &p_textBlock->fontData, textblock_delete);
    p_textBlock->text[0] = '\0';
    p_textBlock->valueChanged = NULL;
    p_textBlock->base.onHandleEvent = NULL;
}


/**
 * @brief Initialize the TextBlock component to the given values.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] p_text.
 *
 */
void textblock_initText(TextBlock_s *p_textBlock, const char *p_text)
{
	textblock_init(p_textBlock);
	strncpy(p_textBlock->text, p_text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH);
}


/**
 * @brief Initialize the TextBlock component to the given values.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] p_text.
 * @param[in] width.
 * @param[in] height.
 *
 */
void textblock_initTextSize(
        TextBlock_s *p_textBlock, const char *p_text,
        const uint16_t width, const uint16_t height)
{
	textblock_init(p_textBlock);
	strncpy(p_textBlock->text, p_text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH);
	base_setSize(&p_textBlock->base, width, height);
}


/**
 * @brief Initialize the TextBlock component to the given values.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] p_text.
 * @param[in] x x-position.
 * @param[in] y y-position.
 *
 */
void textblock_initTextPos(
        TextBlock_s *p_textBlock, const char *p_text,
        const uint16_t x, const uint16_t y)
{
    textblock_init(p_textBlock);
    strncpy(p_textBlock->text, p_text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH);
    base_setPosition(&p_textBlock->base, x, y);
}


/**
 * @brief Initialize the TextBlock component to the given values.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] p_text.
 * @param[in] x x-position.
 * @param[in] y y-position.
 * @param[in] width.
 * @param[in] height.
 *
 */
void textblock_initTextPosSize(
        TextBlock_s *p_textBlock, const char *p_text,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height)
{
    textblock_initTextPos(p_textBlock, p_text, x, y);
    base_setSize(&p_textBlock->base, width, height);
}


/**
 * @brief Initialize the TextBlock component to the given values.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] p_text.
 * @param[in] x x-position.
 * @param[in] y y-position.
 * @param[in] width.
 * @param[in] height.
 * @param[in] color background color.
 *
 */
void textblock_initTextPosSizeBack(
        TextBlock_s *p_textBlock, const char *p_text,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const Color_t color)
{
    textblock_initTextPosSize(p_textBlock, p_text, x, y, width, height);
    p_textBlock->base.drawBackground = true;
    p_textBlock->base.backgroundColor = color;
}


/**
 * @brief Set the TextBlock text.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] p_text.
 *
 */
void textblock_setText(TextBlock_s *p_textBlock, const char *p_text)
{
	strncpy(p_textBlock->text, p_text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH);
}


/**
 * @brief Set the TextBlock text and notify value changed.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] p_text.
 *
 */
void textblock_setTextNotifyChanged(TextBlock_s *p_textBlock, const char *p_text)
{
    strncpy(p_textBlock->text, p_text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH);

    if (NULL != p_textBlock->valueChanged)
    {
        p_textBlock->valueChanged(p_textBlock);
    }

    if (NULL != p_textBlock->valueChangedEvent)
    {
        p_textBlock->valueChangedEvent();
    }
}


/**
 * @brief Set the TextBlock value changed callback function.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] valueChanged Callback function that is called when the text value of the TextBlock changes. The callback function receives a pointer to the TextBlock component as a parameter.
 *
 */
void textblock_setValueChanged(TextBlock_s *p_textBlock, void (*valueChanged)(TextBlock_s *p_textBlock))
{
    p_textBlock->valueChanged = valueChanged;
}


/**
 * @brief Set the TextBlock value changed event callback function.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] valueChangedEvent.
 *
 */
void textblock_setValueChangedEvent(TextBlock_s *p_textBlock, void (*valueChangedEvent)(void))
{
    p_textBlock->valueChangedEvent = valueChangedEvent;
}


/**
 * @brief Set the TextBlock font.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] font.
 *
 */
void textblock_setFont(TextBlock_s *p_textBlock, const uint8_t font)
{
	p_textBlock->fontData.font = font;
}


#if GUI_CONFIG_USE_BITMAP_COLORS
/**
 * @brief Set the TextBlock font foreground color.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] foreColor.
 *
 */
void textblock_setFontForeColor(TextBlock_s *p_textBlock, const Color_t foreColor)
{
    p_textBlock->fontData.fontColor = foreColor;
}


/**
 * @brief Set the TextBlock font background color.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] backColor.
 *
 */
void textblock_setFontBackColor(TextBlock_s *p_textBlock, const Color_t backColor)
{
    p_textBlock->fontData.backgroundColor = backColor;
    base_setBackgroundColor(&p_textBlock->base, backColor);
}


/**
 * @brief Set the TextBlock font and colors.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] font.
 * @param[in] foreColor.
 * @param[in] backColor.
 *
 */
void textblock_setFontAndColor(TextBlock_s *p_textBlock, const uint8_t font, const Color_t foreColor, const Color_t backColor)
{
    p_textBlock->fontData.font = font;
    p_textBlock->fontData.fontColor = foreColor;
    p_textBlock->fontData.backgroundColor = backColor;
    base_setBackgroundColor(&p_textBlock->base, backColor);
}
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */


/**
 * @brief Set the TextBlock text alignment.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] horizontal alignment.
 * @param[in] vertical alignment.
 *
 */
void textblock_setTextAlignment(TextBlock_s *p_textBlock, const TextAlignment_e horizontal, const TextAlignment_e vertical)
{
    p_textBlock->base.horizontalAlignment = (uint8_t)horizontal;
    p_textBlock->base.verticalAlignment = (uint8_t)vertical;
}


/**
 * @brief Set the TextBlock horizontal text alignment.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] alignment.
 *
 */
void textblock_setTextHorizontalAlignment(TextBlock_s *p_textBlock, const TextAlignment_e alignment)
{
    p_textBlock->base.horizontalAlignment = (uint8_t)alignment;
}


/**
 * @brief Set the TextBlock vertical text alignment.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] alignment.
 *
 */
void textblock_setTextVerticalAlignment(TextBlock_s *p_textBlock, const TextAlignment_e alignment)
{
    p_textBlock->base.verticalAlignment = (uint8_t)alignment;
}


/**
 * @brief Set the TextBlock text padding.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] left padding.
 * @param[in] right padding.
 * @param[in] top padding.
 * @param[in] bottom padding.
 *
 */
void textblock_setTextPadding(TextBlock_s *p_textBlock, const uint8_t left, const uint8_t right, const uint8_t top, const uint8_t bottom)
{
    p_textBlock->base.leftPadding = left;
    p_textBlock->base.rightPadding = right;
    p_textBlock->base.topPadding = top;
    p_textBlock->base.bottomPadding = bottom;
}


/**
 * @brief Set the TextBlock left text padding.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] padding.
 *
 */
void textblock_setTextLeftPadding(TextBlock_s *p_textBlock, const uint8_t padding)
{
    p_textBlock->base.leftPadding = padding;
}


/**
 * @brief Set the TextBlock right text padding.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] padding.
 *
 */
void textblock_setTextRightPadding(TextBlock_s *p_textBlock, const uint8_t padding)
{
    p_textBlock->base.rightPadding = padding;
}


/**
 * @brief Set the TextBlock top text padding.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] padding.
 *
 */
void textblock_setTextTopPadding(TextBlock_s *p_textBlock, const uint8_t padding)
{
    p_textBlock->base.topPadding = padding;
}


/**
 * @brief Set the TextBlock bottom text padding.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] padding.
 *
 */
void textblock_setTextBottomPadding(TextBlock_s *p_textBlock, const uint8_t padding)
{
    p_textBlock->base.bottomPadding = padding;
}


/**
 * @brief Display the TextBlock component.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 *
 */
void textblock_display(TextBlock_s *p_textBlock)
{
    base_display(&p_textBlock->base);
}


/**
 * @brief Set the TextBlock id.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] id Id of the TextBlock component.
 *
 */
void textblock_setId(TextBlock_s *p_textBlock, const uint8_t id)
{
    if (id > 0)
    {
        p_textBlock->base.id = id;
    }
}


/**
 * @brief Set the TextBlock x-position.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] x x-position of the TextBlock component.
 *
 */
void textblock_setX(TextBlock_s *p_textBlock, const uint16_t x)
{
    base_setX(&p_textBlock->base, x);
}


/**
 * @brief Set the y-position of the TextBlock component.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] y y-position of the TextBlock component.
 *
 */
void textblock_setY(TextBlock_s *p_textBlock, const uint16_t y)
{
    base_setY(&p_textBlock->base, y);
}


/**
 * @brief Set the width of the TextBlock component.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] width Width of the TextBlock component.
 *
 */
void textblock_setWidth(TextBlock_s *p_textBlock, const uint16_t width)
{
    base_setWidth(&p_textBlock->base, width);
}


/**
 * @brief Set the height of the TextBlock component.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] height Height of the TextBlock component.
 *
 */
void textblock_setHeight(TextBlock_s *p_textBlock, const uint16_t height)
{
    base_setHeight(&p_textBlock->base, height);
}


/**
 * @brief Set the position of the TextBlock component.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] x x-position of the TextBlock component.
 * @param[in] y y-position of the TextBlock component.
 *
 */
void textblock_setPosition(TextBlock_s *p_textBlock, const uint16_t x, const uint16_t y)
{
    base_setPosition(&p_textBlock->base, x, y);
}


/**
 * @brief Set the size of the TextBlock component.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] width Width of the TextBlock component.
 * @param[in] height Height of the TextBlock component.
 *
 */
void textblock_setSize(TextBlock_s *p_textBlock, const uint16_t width, const uint16_t height)
{
    base_setSize(&p_textBlock->base, width, height);
}


/**
 * @brief Set the visibility of the TextBlock component.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] visible true if the TextBlock component should be visible, false otherwise.
 *
 */
void textblock_setVisible(TextBlock_s *p_textBlock, const bool visible)
{
    p_textBlock->base.visible = visible;
}


/**
 * @brief Set the background color of the TextBlock component.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] color Background color of the TextBlock component.
 *
 */
void textblock_setBackgroundColor(TextBlock_s *p_textBlock, const Color_t color)
{
    p_textBlock->base.backgroundColor = color;
}


/**
 * @brief Set the drawBackground flag of the TextBlock component.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] drawBackground If true, background is drawn when onDisplay is called.
 *
 */
void textblock_setDrawBackground(TextBlock_s *p_textBlock, const bool drawBackground)
{
    p_textBlock->base.drawBackground = drawBackground;
}


/*** end of file ***/
