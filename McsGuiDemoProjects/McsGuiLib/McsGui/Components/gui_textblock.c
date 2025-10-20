#include "gui_textblock.h"

#include <stddef.h>
#include <string.h>

#include "Core/gui_log.h"
#include "Core/gui_memory.h"


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
void textblock_delete(BaseComponent_s *p_textBlockBase)
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
	base_setDimensions(p_textBlock, width, height);
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
    base_setPosition(p_textBlock, x, y);
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
    base_setDimensions(p_textBlock, width, height);
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
    base_setBackground(p_textBlock, color);
    base_setTransparent(p_textBlock, false);
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

	if (p_textBlock->valueChanged != NULL)
    {
        p_textBlock->valueChanged();
    }
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
    base_setBackground(p_textBlock, backColor);
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
    base_setBackground(p_textBlock, backColor);
}


/**
 * @brief Set the TextBlock value changed callback function.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] color.
 *
 */
void textblock_setValueChanged(TextBlock_s *p_textBlock, void (*valueChanged)(void))
{
    p_textBlock->valueChanged = valueChanged;
}


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
void textblock_setHorizontalTextAlignment(TextBlock_s *p_textBlock, const TextAlignment_e alignment)
{
    p_textBlock->base.horizontalAlignment = (uint8_t) alignment;
}


/**
 * @brief Set the TextBlock vertical text alignment.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] alignment.
 *
 */
void textblock_setVerticalTextAlignment(TextBlock_s *p_textBlock, const TextAlignment_e alignment)
{
    p_textBlock->base.verticalAlignment = (uint8_t) alignment;
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
void textblock_setLeftTextPadding(TextBlock_s *p_textBlock, const uint8_t padding)
{
    p_textBlock->base.leftPadding = padding;
}


/**
 * @brief Set the TextBlock right text padding.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] padding.
 *
 */
void textblock_setRightTextPadding(TextBlock_s *p_textBlock, const uint8_t padding)
{
    p_textBlock->base.rightPadding = padding;
}


/**
 * @brief Set the TextBlock top text padding.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] padding.
 *
 */
void textblock_setTopTextPadding(TextBlock_s *p_textBlock, const uint8_t padding)
{
    p_textBlock->base.topPadding = padding;
}


/**
 * @brief Set the TextBlock bottom text padding.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] padding.
 *
 */
void textblock_setBottomTextPadding(TextBlock_s *p_textBlock, const uint8_t padding)
{
    p_textBlock->base.bottomPadding = padding;
}


/*** end of file ***/
