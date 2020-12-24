#include "gui_label.h"

#include <stddef.h>

#include "McsGui/Utils/gui_memory.h"


#if GUI_USE_DYNAMIC_MEMORY
/**
 * @brief Creates a new malloced label component.
 * @return Pointer to the malloced memory.
 *
 * @warning The returned component is not initialized.
 */
Label_s *label_new(void)
{
    return gui_mem_malloc(sizeof(Label_s));
}
#endif /* GUI_USE_DYNAMIC_MEMORY */


/**
 * @brief Delete the label component. This function calls the gui_mem_free function to free the allocated memory.
 * @param[in] p_labelBase Pointer to the label component to be freed.
 *
 */
void label_delete(BaseComponent_s *p_labelBase)
{
    base_clear(p_labelBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_labelBase, sizeof(Label_s));
    p_labelBase = NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Initialize the label component to the default values.
 * @param[in] p_label Pointer to the label component.
 *
 */
void label_init(Label_s *p_label)
{
    base_initImageComp(&p_label->base, label_delete);
#if !GUI_USE_DYNAMIC_MEMORY
    p_label->base.p_bmpName = p_label->bmpName;
    p_label->base.p_bmpName[0] = '\0';
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Initialize the label component to the given values.
 * @param[in] p_label Pointer to the checkbox component.
 * @param[in] p_bmpName Pointer to the bmp-name.
 * @param[in] xPos.
 * @param[in] yPos.
 *
 */
void label_init_1(
        Label_s *p_label, const char *p_bmpName,
        const uint16_t xPos, const uint16_t yPos)
{
    label_init(p_label);
    base_setPosition(&p_label->base, xPos, yPos);
    base_setBmp(&p_label->base, p_bmpName);
}


/**
 * @brief Initialize the label component to the given values.
 * @param[in] p_label Pointer to the checkbox component.
 * @param[in] p_bmpName Pointer to the bmp-name.
 * @param[in] xPos.
 * @param[in] yPos.
 * @param[in] width.
 * @param[in] height.
 *
 */
void label_init_2(
        Label_s *p_label, const char *p_bmpName,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height)
{
    label_init_1(p_label, p_bmpName, xPos, yPos);
    base_setDimensions(&p_label->base, width, height);
}


/**
 * @brief Initialize the label component to the given values.
 * @param[in] p_label Pointer to the checkbox component.
 * @param[in] p_bmpName Pointer to the bmp-name.
 * @param[in] xPos.
 * @param[in] yPos.
 * @param[in] width.
 * @param[in] height.
 * @param[in]
 *
 */
void label_init_3(
        Label_s *p_label, const char *p_bmpName,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const Color_t background)
{
    label_init_2(p_label, p_bmpName, xPos, yPos, width, height);
    base_setBackground(&p_label->base, background);
}


/*** end of file ***/
