#include "gui_label.h"

#include <stddef.h>
#include <string.h>

#include "Utils/gui_log.h"
#include "Utils/gui_memory.h"


#if !GUI_USE_DYNAMIC_MEMORY
static bool staticLabelMemInUse[GUI_CONFIG_LABEL_BUFFER_SIZE] = {0};
static Label_s staticLabelMem[GUI_CONFIG_LABEL_BUFFER_SIZE] = {0};
#endif /* GUI_USE_DYNAMIC_MEMORY */


/**
 * @brief Creates a new malloced label component.
 * @return Pointer to the malloced memory.
 *
 * @warning The returned component is not initialized.
 */
Label_s *label_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(Label_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_LABEL_BUFFER_SIZE; i++)
    {
    	if (!staticLabelMemInUse[i])
    	{
    		staticLabelMemInUse[i] = true;

    		return &staticLabelMem[i];
    	}
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No Label_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Creates a new Label_s component and initializes it to default values.
 * @return Pointer to the Label_s component.
 *
 */
Label_s *label_newInit(void)
{
	Label_s *p_label = label_new();
	label_init(p_label);

	return p_label;
}


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
#else
    for (uint32_t i = 0; i < GUI_CONFIG_LABEL_BUFFER_SIZE; i++)
    {
    	if (&staticLabelMem[i].base == p_labelBase)
    	{
    		memset(&staticLabelMem[i], 0, sizeof(Label_s));
    		staticLabelMemInUse[i] = false;

    		break;
    	}
    }
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
}


/**
 * @brief Initialize the label component to the given values.
 * @param[in] p_label Pointer to the label component.
 * @param[in] p_bmpName Pointer to the bmp-name.
 *
 */
void label_initBmp(Label_s *p_label, const uint32_t bmpKey)
{
    label_init(p_label);
    p_label->base.bmpKey = bmpKey;
}


/**
 * @brief Initialize the label component to the given values.
 * @param[in] p_label Pointer to the label component.
 * @param[in] p_bmpName Pointer to the bmp-name.
 * @param[in] x x-position of the label.
 * @param[in] y y-position of the label.
 *
 */
void label_initBmpPos(
        Label_s *p_label, const uint32_t bmpKey,
        const uint16_t x, const uint16_t y)
{
    label_init(p_label);
    base_setPosition(&p_label->base, x, y);
    p_label->base.bmpKey = bmpKey;
}


/**
 * @brief Initialize the label component to the given values.
 * @param[in] p_label Pointer to the label component.
 * @param[in] p_bmpName Pointer to the bmp-name.
 * @param[in] x x-position of the label.
 * @param[in] y y-position of the label.
 * @param[in] width.
 * @param[in] height.
 *
 */
void label_initBmpPosSize(
        Label_s *p_label, const uint32_t bmpKey,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height)
{
    label_initBmpPos(p_label, bmpKey, x, y);
    base_setDimensions(&p_label->base, width, height);
}


/**
 * @brief Initialize the label component to the given values.
 * @param[in] p_label Pointer to the label component.
 * @param[in] p_bmpName Pointer to the bmp-name.
 * @param[in] x x-position of the label.
 * @param[in] y y-position of the label.
 * @param[in] width.
 * @param[in] height.
 * @param[in] background. Background color of the label.
 *
 */
void label_initBmpPosSizeBack(
        Label_s *p_label, const uint32_t bmpKey,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const Color_t background)
{
    label_initBmpPosSize(p_label, bmpKey, x, y, width, height);
    base_setBackground(&p_label->base, background);
}


/**
 * @brief Set the bmp-name of the label.
 * @param[in] p_label Pointer to the label component.
 * @param[in] p_bmpName Pointer to the bmp-name.
 *
 */
void label_setBmpKey(Label_s *p_label, const uint32_t bmpKey)
{
    p_label->base.bmpKey = bmpKey;
}


/*** end of file ***/
