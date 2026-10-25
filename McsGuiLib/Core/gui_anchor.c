#include "gui_anchor.h"

#if GUI_CONFIG_USE_ANCHOR

#include <stddef.h>

#include "gui_basecomponent.h"
#include "gui_log.h"
#include "gui_memory.h"


#if !GUI_USE_DYNAMIC_MEMORY
static bool staticAnchorMemInUse[GUI_CONFIG_ANCHOR_BUFFER_SIZE] = {0};
static Anchor_s staticAnchorMem[GUI_CONFIG_ANCHOR_BUFFER_SIZE] = {0};
#endif /* GUI_USE_DYNAMIC_MEMORY */

/**
 * @brief Creates a new Anchor struct.
 * @return Pointer to the memory.
 *
 * @warning The returned struct is not initialized.
 */
Anchor_s *anchor_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
return gui_mem_malloc(sizeof(GuiAnchor_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_ANCHOR_BUFFER_SIZE; i++)
    {
        if (!staticAnchorMemInUse[i])
        {
            staticAnchorMemInUse[i] = true;

            return &staticAnchorMem[i];
        }
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No Anchor_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Delete the Anchor struct. This function calls the gui_mem_free function to free the allocated memory.
 * @param[in] p_anchor Pointer to the GuiAnchor_s sturct to be freed.
 *
 */
void anchor_delete(Anchor_s *p_anchor)
{
    if (p_anchor != NULL)
    {
#if GUI_USE_DYNAMIC_MEMORY
        gui_mem_free(p_anchor, sizeof(GuiAnchor_s));
#else
        for (uint32_t i = 0; i < GUI_CONFIG_ANCHOR_BUFFER_SIZE; i++)
        {
            if (&staticAnchorMem[i] == p_anchor)
            {
                staticAnchorMemInUse[i] = false;
                break;
            }
        }
#endif /* GUI_USE_DYNAMIC_MEMORY */
    }
}


/**
 * @brief Initializes the Anchor struct to default values.
 * @param[in] p_anchor Pointer to the GuiAnchor_s struct to be initialized.
 *
 */
void anchor_init(Anchor_s *p_anchor)
{
    p_anchor->p_horizontalAnchorToBase = NULL;
    p_anchor->p_verticalAnchorToBase = NULL;
    p_anchor->horizontalAnchorPosTo = Gui_Anchor_None;
    p_anchor->verticalAnchorPosTo = Gui_Anchor_None;
    p_anchor->horizontalAnchorPosition = Gui_Anchor_None;
    p_anchor->verticalAnchorPosition = Gui_Anchor_None;
    p_anchor->leftMargin = 0;
    p_anchor->rightMargin = 0;
    p_anchor->topMargin = 0;
    p_anchor->bottomMargin = 0;
    p_anchor->parentAnchor = Gui_Anchor_None;
}


/**
 * @brief Set the anchor to the right side of the base component.
 * @param[in] p_anchor Pointer to the GuiAnchor_s struct.
 * @param[in] p_anchorToBase Pointer to the base component to anchor to.
 * @param[in] anchorToPosition Position to anchor to.
 *
 */
void anchor_setLeftAnchor(void *p_anchoredComponent, void *p_anchorToComponent, AnchorPosition_e anchorToPosition)
{
	Anchor_s *p_anchor = ((BaseComponent_s*)p_anchoredComponent)->p_anchor;

	if (p_anchor == NULL)
	{
		return;
	}

    p_anchor->p_horizontalAnchorToBase = (BaseComponent_s *)p_anchorToComponent;
    p_anchor->horizontalAnchorPosTo = anchorToPosition;
    p_anchor->horizontalAnchorPosition = Gui_Anchor_Left;
}


/**
 * @brief Set the anchor to the left side of the base component.
 * @param[in] p_anchor Pointer to the GuiAnchor_s struct.
 * @param[in] p_anchorToBase Pointer to the base component to anchor to.
 * @param[in] anchorToPosition Position to anchor to.
 *
 */
void anchor_setRightAnchor(void *p_anchoredComponent, void *p_anchorToComponent, AnchorPosition_e anchorToPosition)
{
	Anchor_s *p_anchor = ((BaseComponent_s*)p_anchoredComponent)->p_anchor;

	if (p_anchor == NULL)
	{
		return;
	}

    p_anchor->p_horizontalAnchorToBase = (BaseComponent_s*)p_anchorToComponent;
    p_anchor->horizontalAnchorPosTo = anchorToPosition;
    p_anchor->horizontalAnchorPosition = Gui_Anchor_Right;
}


/**
 * @brief Set the anchor to the top side of the base component.
 * @param[in] p_anchor Pointer to the GuiAnchor_s struct.
 * @param[in] p_anchorToBase Pointer to the base component to anchor to.
 * @param[in] anchorToPosition Position to anchor to.
 *
 */
void anchor_setTopAnchor(void *p_anchoredComponent, void *p_anchorToComponent, AnchorPosition_e anchorToPosition)
{
	Anchor_s *p_anchor = ((BaseComponent_s*)p_anchoredComponent)->p_anchor;

	if (p_anchor == NULL)
	{
		return;
	}

    p_anchor->p_verticalAnchorToBase = (BaseComponent_s*)p_anchorToComponent;
    p_anchor->verticalAnchorPosTo = anchorToPosition;
    p_anchor->verticalAnchorPosition = Gui_Anchor_Top;
}


/**
 * @brief Set the anchor to the bottom side of the base component.
 * @param[in] p_anchor Pointer to the GuiAnchor_s struct.
 * @param[in] p_anchorToBase Pointer to the base component to anchor to.
 * @param[in] anchorToPosition Position to anchor to.
 *
 */
void anchor_setBottomAnchor(void *p_anchoredComponent, void *p_anchorToComponent, AnchorPosition_e anchorToPosition)
{
	Anchor_s *p_anchor = ((BaseComponent_s*)p_anchoredComponent)->p_anchor;

	if (p_anchor == NULL)
	{
		return;
	}

    p_anchor->p_verticalAnchorToBase = (BaseComponent_s*)p_anchorToComponent;
    p_anchor->verticalAnchorPosTo = anchorToPosition;
    p_anchor->verticalAnchorPosition = Gui_Anchor_Bottom;
}


/**
 * @brief Set the anchor to fill the parent component.
 * @param[in] p_anchor Pointer to the GuiAnchor_s struct.
 * @param[in] p_anchorToBase Pointer to the base component to anchor to.
 *
 */
void anchor_setFillParent(void *p_anchoredComponent, void *p_anchorToComponent)
{
	Anchor_s *p_anchor = ((BaseComponent_s*)p_anchoredComponent)->p_anchor;

	if (p_anchor == NULL)
	{
		return;
	}

    p_anchor->p_horizontalAnchorToBase = (BaseComponent_s*)p_anchorToComponent;
    p_anchor->p_verticalAnchorToBase = (BaseComponent_s*)p_anchorToComponent;
    p_anchor->parentAnchor = Gui_Anchor_Fill_Parent;
}


/**
 * @brief Set the anchor to center in the parent component.
 * @param[in] p_anchor Pointer to the GuiAnchor_s struct.
 * @param[in] p_anchorToBase Pointer to the base component to anchor to.
 *
 */
void anchor_setCenterInParent(void *p_anchoredComponent, void *p_anchorToComponent)
{
	Anchor_s *p_anchor = ((BaseComponent_s*)p_anchoredComponent)->p_anchor;

	if (p_anchor == NULL)
	{
		return;
	}

    p_anchor->p_horizontalAnchorToBase = (BaseComponent_s*)p_anchorToComponent;
    p_anchor->p_verticalAnchorToBase = (BaseComponent_s*)p_anchorToComponent;
    p_anchor->parentAnchor = Gui_Anchor_Center_In_Parent;
}


/**
 * @brief Set the anchor to center horizontally in the parent component.
 * @param[in] p_anchor Pointer to the GuiAnchor_s struct.
 * @param[in] p_anchorToBase Pointer to the base component to anchor to.
 *
 */
void anchor_setHorizontalCenter(void *p_anchoredComponent, void *p_anchorToComponent)
{
	Anchor_s *p_anchor = ((BaseComponent_s*)p_anchoredComponent)->p_anchor;

	if (p_anchor == NULL)
	{
		return;
	}

    p_anchor->p_horizontalAnchorToBase = (BaseComponent_s*)p_anchorToComponent;
    p_anchor->horizontalAnchorPosTo = Gui_Anchor_Horizontal_Center;
    p_anchor->horizontalAnchorPosition = Gui_Anchor_Horizontal_Center;
}


/**
 * @brief Set the anchor to center vertically in the parent component.
 * @param[in] p_anchor Pointer to the GuiAnchor_s struct.
 * @param[in] p_anchorToBase Pointer to the base component to anchor to.
 *
 */
void anchor_setVerticalCenter(void *p_anchoredComponent, void *p_anchorToComponent)
{
	Anchor_s *p_anchor = ((BaseComponent_s*)p_anchoredComponent)->p_anchor;

	if (p_anchor == NULL)
	{
		return;
	}

    p_anchor->p_verticalAnchorToBase = (BaseComponent_s*)p_anchorToComponent;
    p_anchor->verticalAnchorPosTo = Gui_Anchor_Vertical_Center;
    p_anchor->verticalAnchorPosition = Gui_Anchor_Vertical_Center;
}


/**
 * @brief Set the margins for the anchor.
 * @param[in] p_anchor Pointer to the GuiAnchor_s struct.
 * @param[in] left Left margin value.
 * @param[in] top Top margin value.
 * @param[in] right Right margin value.
 * @param[in] bottom Bottom margin value.
 *
 */
void anchor_setMargin(void *p_anchoredComponent, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)
{
    Anchor_s *p_anchor = ((BaseComponent_s*) p_anchoredComponent)->p_anchor;

    if (p_anchor == NULL)
    {
        return;
    }

    p_anchor->leftMargin = left;
    p_anchor->topMargin = top;
    p_anchor->rightMargin = right;
    p_anchor->bottomMargin = bottom;
}


/**
 * @brief Set the left margin of the anchor.
 * @param[in] p_anchor Pointer to the GuiAnchor_s struct.
 * @param[in] margin Margin value.
 *
 */
void anchor_setLeftMargin(void *p_anchoredComponent, uint16_t margin)
{
	Anchor_s *p_anchor = ((BaseComponent_s*)p_anchoredComponent)->p_anchor;

	if (p_anchor == NULL)
	{
		return;
	}

    p_anchor->leftMargin = margin;
}


/**
 * @brief Set the right margin of the anchor.
 * @param[in] p_anchor Pointer to the GuiAnchor_s struct.
 * @param[in] margin Margin value.
 *
 */
void anchor_setRightMargin(void *p_anchoredComponent, uint16_t margin)
{
	Anchor_s *p_anchor = ((BaseComponent_s*)p_anchoredComponent)->p_anchor;

	if (p_anchor == NULL)
	{
		return;
	}

    p_anchor->rightMargin = margin;
}


/**
 * @brief Set the top margin of the anchor.
 * @param[in] p_anchor Pointer to the GuiAnchor_s struct.
 * @param[in] margin Margin value.
 *
 */
void anchor_setTopMargin(void *p_anchoredComponent, uint16_t margin)
{
	Anchor_s *p_anchor = ((BaseComponent_s*)p_anchoredComponent)->p_anchor;

	if (p_anchor == NULL)
	{
		return;
	}

    p_anchor->topMargin = margin;
}


/**
 * @brief Set the bottom margin of the anchor.
 * @param[in] p_anchor Pointer to the GuiAnchor_s struct.
 * @param[in] margin Margin value.
 *
 */
void anchor_setBottomMargin(void *p_anchoredComponent, uint16_t margin)
{
	Anchor_s *p_anchor = ((BaseComponent_s*)p_anchoredComponent)->p_anchor;

	if (p_anchor == NULL)
	{
		return;
	}

    p_anchor->bottomMargin = margin;
}

#endif /* GUI_CONFIG_USE_ANCHOR */


/*** end of file ***/

