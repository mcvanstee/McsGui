#include "gui_textblock.h"

#include <stddef.h>

#include "McsGui/Utils/gui_memory.h"


#if GUI_USE_DYNAMIC_MEMORY
/**
 * @brief Creates a new malloced TextBlock component.
 * @return Pointer to the malloced memory.
 *
 * @warning The returned component is not initialized.
 *
 */
TextBlock_s *textblock_new(void)
{
    return gui_mem_malloc(sizeof(TextBlock_s));
}
#endif /* GUI_USE_DYNAMIC_MEMORY */


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
    p_textBlockBase = NULL;
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
    base_initTextComp(&p_textBlock->base, &p_textBlock->fontData, textblock_delete);
#if !GUI_USE_DYNAMIC_MEMORY
    p_textBlock->bmpName[0] = '\0';
    p_textBlock->base.p_bmpName = p_textBlock->bmpName;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Initialize the TextBlock component to the given values.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] p_text.
 * @param[in] xPos.
 * @param[in] yPos.
 *
 */
void textblock_init_1(
        TextBlock_s *p_textBlock, const char *p_text,
        const uint16_t xPos, const uint16_t yPos)
{
    textblock_init(p_textBlock);
    base_setBmp(p_textBlock, p_text);
    base_setPosition(p_textBlock, xPos, yPos);
}


/**
 * @brief Initialize the TextBlock component to the given values.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] p_text.
 * @param[in] xPos.
 * @param[in] yPos.
 * @param[in] width.
 * @param[in] height.
 *
 */
void textblock_init_2(
        TextBlock_s *p_textBlock, const char *p_text,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height)
{
    textblock_init_1(p_textBlock, p_text, xPos, yPos);
    base_setDimensions(p_textBlock, width, height);
}


/**
 * @brief Initialize the TextBlock component to the given values.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] p_text.
 * @param[in] xPos.
 * @param[in] yPos.
 * @param[in] width.
 * @param[in] height.
 * @param[in] color background color.
 *
 */
void textblock_init_3(
        TextBlock_s *p_textBlock, const char *p_text,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const Color_t color)
{
    textblock_init_2(p_textBlock, p_text, xPos, yPos, width, height);
    base_setBackground(p_textBlock, color);
}


/**
 * @brief Set the TextBlock text.
 * @param[in] p_textBlock Pointer to the TextBlock component.
 * @param[in] p_text.
 *
 */
void textblock_setText(TextBlock_s *p_textBlock, const char *p_text)
{
    base_setBmp(p_textBlock, p_text);
}


/*** end of file ***/
