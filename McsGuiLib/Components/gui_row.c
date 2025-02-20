#include "gui_row.h"

#include <stddef.h>

#include "Utils/gui_log.h"
#include "Utils/gui_memory.h"
#include "Graphics/gui_graphics.h"
#include "gui_rectangle.h"

#if !GUI_USE_DYNAMIC_MEMORY
static bool staticRowMemInUse[GUI_CONFIG_ROW_BUFFER_SIZE] = {0};
static Row_s staticRowMem[GUI_CONFIG_ROW_BUFFER_SIZE] = {0};
#endif /* GUI_USE_DYNAMIC_MEMORY */


static void row_display(BaseComponent_s *p_rowBase);


/**
 * @brief Creates a new malloced Row component.
 * @return Pointer to the malloced memory.
 *
 * @warning The returned component is not initialized.
 *
 */
Row_s *row_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
return gui_mem_malloc(sizeof(Row_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_ROW_BUFFER_SIZE; i++)
    {
        if (!staticRowMemInUse[i])
        {
            staticRowMemInUse[i] = true;

            return &staticRowMem[i];
        }
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No Row_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Creates a new Row_s component and initializes it to default values.
 * @return Pointer to the Row_s component.
 *
 */
Row_s *row_newInit(void)
{
    Row_s *p_row = row_new();
    row_init(p_row);

    return p_row;
}


/**
 * @brief Delete the Row component. This functions calls the gui_mem_free function to free the allocated memory.
 * @param[in] p_rowBase Pointer to the Row component to be freed.
 *
 */
void row_delete(BaseComponent_s *p_rowBase)
{
    base_clear(p_rowBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_rowBase, sizeof(Row_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_ROW_BUFFER_SIZE; i++)
    {
        if (&staticRowMem[i].base == p_rowBase)
        {
            staticRowMemInUse[i] = false;
            break;
        }
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Initializes the Row component to default values.
 * @param[in] p_row Pointer to the Row component.
 *
 */
void row_init(Row_s *p_row)
{
    base_initParentComp(&p_row->base, row_delete);
    p_row->base.onDisplay = row_display;
    p_row->spacing = 0;
    p_row->componentCount = 0;
    p_row->cellWidth = 0;
}


/**
 * @brief Set the spacing between the components in the row.
 * @param[in] p_row Pointer to the Row component.
 * @param[in] spacing The spacing between the components.
 *
 */
void row_setSpacing(Row_s *p_row, uint8_t spacing)
{
    p_row->spacing = spacing;
}


/**
 * @brief Set the cell width for the components in the row.
 * @param[in] p_row Pointer to the Row component.
 * @param[in] cellWidth The width of the cell.
 *
 */
void row_setCellWidth(Row_s *p_row, uint8_t cellWidth)
{
    p_row->cellWidth = cellWidth;
}


/**
 * @brief Add a component to the row.
 * @param[in] p_row Pointer to the Row component.
 * @param[in] p_component Pointer to the component to be added.
 *
 */
void row_addComponent(Row_s *p_row, void *p_component)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;

    if (p_row->base.p_childList == NULL)
    {
        p_row->componentCount = 1;
        p_row->base.p_childList = p_base;

        return;
    }

    BaseComponent_s *p_iterator = p_row->base.p_childList;
    while (p_iterator->p_nextBaseComponent != NULL)
    {
        p_iterator = p_iterator->p_nextBaseComponent;
    }

    p_row->componentCount++;
    p_iterator->p_nextBaseComponent = p_base;
}


/**
 * @brief Get a component from the row.
 * @param[in] p_row Pointer to the Row component.
 * @param[in] index The index of the component.
 * @return Pointer to the component.
 *
 */
BaseComponent_s *row_getComponent(Row_s *p_row, uint8_t index)
{
    if ((p_row->base.p_childList == NULL) || (index >= p_row->componentCount))
    {
        return NULL;
    }

    BaseComponent_s *p_iterator = p_row->base.p_childList;

    for (uint8_t i = 0; i < index; i++)
    {
        p_iterator = p_iterator->p_nextBaseComponent;
    }

    return p_iterator;
}


/**
 * @brief Display the Row component.
 * @param[in] p_rowBase Pointer to the Row component.
 *
 */
static void row_display(BaseComponent_s *p_rowBase)
{
    Row_s *p_row = (Row_s*) p_rowBase;
    p_row->base.width = 0;
    uint16_t maxHeight = 0;

    BaseComponent_s *p_iterator = p_row->base.p_childList;
    while (p_iterator != NULL)
    {
        graphics_setSizeFromBmp(p_iterator);

        if (p_iterator->height > maxHeight)
        {
            maxHeight = p_iterator->height;
        }

        p_row->base.width += p_iterator->width;

        p_iterator = p_iterator->p_nextBaseComponent;
    }

    p_row->base.height = maxHeight;

    if (p_row->cellWidth == 0)
    {
        p_row->base.width += p_row->spacing * (p_row->componentCount - 1);
    }
    else
    {
        p_row->base.width = (p_row->cellWidth * p_row->componentCount) + (p_row->spacing * (p_row->componentCount - 1));
    }

#if GUI_CONFIG_USE_ANCHOR
    if (p_row->base.p_anchor != NULL)
    {
        graphics_setPosistionFromAnchor(p_rowBase);
    }
#endif /* GUI_CONFIG_USE_ANCHOR */

    uint16_t x = p_row->base.x;

    p_iterator = p_row->base.p_childList;
    int32_t item = 0;

    while (p_iterator != NULL)
    {
        base_setPosition(p_iterator, x, p_row->base.y);

        p_iterator->height = maxHeight;
#if GUI_CONFIG_USE_TOUCH
		if (p_iterator->p_touch != NULL)
		{
			p_iterator->p_touch->x = p_iterator->x;
			p_iterator->p_touch->y = p_iterator->y;
		}
#endif /* GUI_CONFIG_USE_TOUCH */
        base_display(p_iterator);

        const uint16_t cellWidth = (p_row->cellWidth > 0) ? p_row->cellWidth : p_iterator->width;

        if (!p_rowBase->transparent && (item < (p_row->componentCount - 1)) && (p_row->spacing > 0))
        {
            Rectangle_s rect;
            rectangle_initFillPosSize(&rect, p_rowBase->background,
                    x + cellWidth,
                    p_rowBase->y,
                    p_row->spacing, maxHeight);
            base_display(&rect);
        }

        x += cellWidth + p_row->spacing;
        p_iterator = p_iterator->p_nextBaseComponent;
        item++;
    }
}
