#include "gui_label.h"

#include <stddef.h>
#include <string.h>

#include "Core/gui_log.h"
#include "Core/gui_memory.h"

static void label_delete(BaseComponent_s *p_labelBase);

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
static void label_delete(BaseComponent_s *p_labelBase)
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
    base_setSize(&p_label->base, width, height);
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
        const Color_t backgroundColor)
{
    label_initBmpPosSize(p_label, bmpKey, x, y, width, height);
    base_setBackgroundColor(&p_label->base, backgroundColor);
    base_setDrawBackground(&p_label->base, true);
}


/**
 * @brief Display the label component.
 * @param[in] p_label Pointer to the label component.
 *
 */
void label_display(Label_s *p_label)
{
    base_display(&p_label->base);
}


/**
 * @brief Set the id of the label.
 * @param[in] p_label Pointer to the label component.
 * @param[in] id Id of the label.
 *
 */
void label_setId(Label_s *p_label, const uint32_t id)
{
    if (id > 0)
    {
        p_label->base.id = id;
    }
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


/**
 * @brief Set the x-position of the label.
 * @param[in] p_label Pointer to the label component.
 * @param[in] x x-position of the label.
 *
 */
void label_setX(Label_s *p_label, const uint16_t x)
{
    base_setX(&p_label->base, x);
}


/**
 * @brief Set the y-position of the label.
 * @param[in] p_label Pointer to the label component.
 * @param[in] y y-position of the label.
 *
 */
void label_setY(Label_s *p_label, const uint16_t y)
{
    base_setY(&p_label->base, y);
}


/**
 * @brief Set the width of the label.
 * @param[in] p_label Pointer to the label component.
 * @param[in] width Width of the label.
 *
 */
void label_setWidth(Label_s *p_label, const uint16_t width)
{
    base_setWidth(&p_label->base, width);
}


/**
 * @brief Set the height of the label.
 * @param[in] p_label Pointer to the label component.
 * @param[in] height Height of the label.
 *
 */
void label_setHeight(Label_s *p_label, const uint16_t height)
{
    base_setHeight(&p_label->base, height);
}


/**
 * @brief Set the position of the label.
 * @param[in] p_label Pointer to the label component.
 * @param[in] x x-position of the label.
 * @param[in] y y-position of the label.
 *
 */
void label_setPosition(Label_s *p_label, const uint16_t x, const uint16_t y)
{
    base_setPosition(&p_label->base, x, y);
}


/**
 * @brief Set the size of the label.
 * @param[in] p_label Pointer to the label component.
 * @param[in] width Width of the label.
 * @param[in] height Height of the label.
 *
 */
void label_setSize(Label_s *p_label, const uint16_t width, const uint16_t height)
{
    base_setSize(&p_label->base, width, height);
}


/**
 * @brief Set the visibility of the label.
 * @param[in] p_label Pointer to the label component.
 * @param[in] visible Whether the label should be visible or not.
 *
 */
void label_setVisible(Label_s *p_label, const bool visible)
{
    base_setVisible(&p_label->base, visible);
}


/**
 * @brief Set the background color of the label.
 * @param[in] p_label Pointer to the label component.
 * @param[in] color Background color of the label.
 *
 */
void label_setBackgroundColor(Label_s *p_label, const Color_t color)
{
    p_label->base.backgroundColor = color;
}


/**
 * @brief Set whether the background of the label should be drawn.
 * @param[in] p_label Pointer to the label component.
 * @param[in] drawBackground Whether the background should be drawn.
 *
 */
void label_setDrawBackground(Label_s *p_label, const bool drawBackground)
{
    p_label->base.drawBackground = drawBackground;
}


#if GUI_CONFIG_USE_BITMAP_COLORS
/**
 * @brief Set the foreground color of the label.
 * @param[in] p_label Pointer to the label component.
 * @param[in] color Foreground color of the label.
 *
 */
void label_setForegroundColor(Label_s *p_label, const Color_t color)
{
    p_label->base.foregroundColor = color;
}
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */


/**
 * @brief Set the alignment of the label bitmap.
 * @param[in] p_label Pointer to the label component.
 * @param[in] horizontalAlignment Horizontal alignment of the bitmap.
 * @param[in] verticalAlignment Vertical alignment of the bitmap.
 *
 */
void label_setBmpAlignment(Label_s *p_label, const GuiAlignment_e horizontalAlignment, const GuiAlignment_e verticalAlignment)
{
    p_label->base.horizontalAlignment = (uint8_t) horizontalAlignment;
    p_label->base.verticalAlignment = (uint8_t) verticalAlignment;
}


/**
 * @brief Set the horizontal alignment of the label bitmap.
 * @param[in] p_label Pointer to the label component.
 * @param[in] horizontalAlignment Horizontal alignment of the bitmap.
 *
 */
void label_setBmpHorizontalAlignment(Label_s *p_label, const GuiAlignment_e horizontalAlignment)
{
    p_label->base.horizontalAlignment = (uint8_t) horizontalAlignment;
}


/**
 * @brief Set the vertical alignment of the label bitmap.
 * @param[in] p_label Pointer to the label component.
 * @param[in] verticalAlignment Vertical alignment of the bitmap.
 */
void label_setBmpVerticalAlignment(Label_s *p_label, const GuiAlignment_e verticalAlignment)
{
    p_label->base.verticalAlignment = (uint8_t) verticalAlignment;
}


/**
 * @brief Set the padding of the label bitmap.
 * @param[in] p_label Pointer to the label component.
 * @param[in] left Left padding of the bitmap.
 * @param[in] top Top padding of the bitmap.
 * @param[in] right Right padding of the bitmap.
 * @param[in] bottom Bottom padding of the bitmap.
 *
 */
void label_setBmpPadding(Label_s *p_label, const uint8_t left, const uint8_t top, const uint8_t right, const uint8_t bottom)
{
    p_label->base.leftPadding = left;
    p_label->base.rightPadding = right;
    p_label->base.topPadding = top;
    p_label->base.bottomPadding = bottom;
}


/**
 * @brief Set the horizontal padding of the label bitmap.
 * @param[in] p_label Pointer to the label component.
 * @param[in] horizontalPadding Horizontal padding of the bitmap.
 *
 */
void label_setBmpLeftPadding(Label_s *p_label, const uint8_t padding)
{
    p_label->base.leftPadding = padding;
}


/**
 * @brief Set the horizontal padding of the label bitmap.
 * @param[in] p_label Pointer to the label component.
 * @param[in] horizontalPadding Horizontal padding of the bitmap.
 *
 */
void label_setBmpRightPadding(Label_s *p_label, const uint8_t padding)
{
    p_label->base.rightPadding = padding;
}


/**
 * @brief Set the vertical padding of the label bitmap.
 * @param[in] p_label Pointer to the label component.
 * @param[in] verticalPadding Vertical padding of the bitmap.
 *
 */
void label_setBmpTopPadding(Label_s *p_label, const uint8_t padding)
{
    p_label->base.topPadding = padding;
}


/**
 * @brief Set the vertical padding of the label bitmap.
 * @param[in] p_label Pointer to the label component.
 * @param[in] verticalPadding Vertical padding of the bitmap.
 *
 */
void label_setBmpBottomPadding(Label_s *p_label, const uint8_t padding)
{
    p_label->base.bottomPadding = padding;
}

/*** end of file ***/
