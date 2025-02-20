#include "gui_column.h"

#include <stddef.h>

#include "Utils/gui_log.h"
#include "Utils/gui_memory.h"
#include "Graphics/gui_graphics.h"
#include "gui_rectangle.h"

#if !GUI_USE_DYNAMIC_MEMORY
static bool staticColumnMemInUse[GUI_CONFIG_COLUMN_BUFFER_SIZE] = {0};
static Column_s staticColumnMem[GUI_CONFIG_COLUMN_BUFFER_SIZE] = {0};
#endif /* GUI_USE_DYNAMIC_MEMORY */


static void column_display(BaseComponent_s *p_columnBase);


/**
 * @brief Creates a new malloced Column component.
 * @return Pointer to the malloced memory.
 *
 * @warning The returned component is not initialized.
 *
 */
Column_s *column_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
return gui_mem_malloc(sizeof(Column_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_COLUMN_BUFFER_SIZE; i++)
    {
        if (!staticColumnMemInUse[i])
        {
            staticColumnMemInUse[i] = true;

            return &staticColumnMem[i];
        }
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No Column_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Delete the Column component. This functions calls the gui_mem_free function to free the allocated memory.
 * @param[in] p_columnBase Pointer to the Column component to be freed.
 *
 */
void column_delete(BaseComponent_s *p_columnBase)
{
    base_clear(p_columnBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_columnBase, sizeof(Column_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_COLUMN_BUFFER_SIZE; i++)
    {
        if (&staticColumnMem[i].base == p_columnBase)
        {
            staticColumnMemInUse[i] = false;
            break;
        }
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Creates a new Column_s component and initializes it to default values.
 * @return Pointer to the Column_s component.
 *
 */
Column_s *column_newInit(void)
{
    Column_s *p_column = column_new();
    column_init(p_column);

    return p_column;
}


/**
 * @brief Initializes the Column_s component to default values.
 * @param p_column Pointer to the component.
 *
 */
void column_init(Column_s *p_column)
{
    base_initParentComp(&p_column->base, column_delete);
    p_column->spacing = 0;
    p_column->componentCount = 0;
    p_column->cellHeight = 0;
    p_column->base.onDisplay = column_display;
}


/**
 * @brief Sets the spacing between the components in the column.
 * @param p_column Pointer to the component.
 * @param spacing The spacing between the components.
 *
 */
void column_setSpacing(Column_s *p_column, uint8_t spacing)
{
    p_column->spacing = spacing;
}


/**
 * @brief Add a component to the Column.
 * @param p_column Pointer to the component.
 * @param p_base Pointer to the component to be added.
 *
 */
void column_addComponent(Column_s *p_column, void *p_base)
{
    BaseComponent_s *p_component = (BaseComponent_s*) p_base;

    if (p_column->base.p_childList == NULL)
    {
        p_column->base.p_childList = p_component;

        return;
    }

    BaseComponent_s *p_iterator = p_column->base.p_childList;
    while (p_iterator->p_nextBaseComponent != NULL)
    {
        p_iterator = p_iterator->p_nextBaseComponent;
    }

    p_iterator->p_nextBaseComponent = p_component;
}


/**
 * @brief Get the component from the Column.
 * @param p_column Pointer to the component.
 * @param index The index of the component.
 * @return Pointer to the component.
 *
 */
BaseComponent_s *column_getComponent(Column_s *p_column, uint8_t index)
{
    if ((p_column->base.p_childList == NULL) || (index >= p_column->componentCount))
    {
        return NULL;
    }

    BaseComponent_s *p_iterator = p_column->base.p_childList;

    for (uint8_t i = 0; i < index; i++)
    {
        p_iterator = p_iterator->p_nextBaseComponent;
    }

    return p_iterator;
}


/**
 * @brief Display the Column component.
 * @param p_columnBase Pointer to the component.
 *
 */
static void column_display(BaseComponent_s *p_columnBase)
{
    Column_s *p_column = (Column_s*) p_columnBase;
    p_column->base.height = 0;
    uint16_t maxWidth = 0;

    BaseComponent_s *p_iterator = p_column->base.p_childList;
    while (p_iterator != NULL)
    {
        graphics_setSizeFromBmp(p_iterator);

        if (p_iterator->width > maxWidth)
        {
            maxWidth = p_iterator->width;
        }

        p_column->base.height += p_iterator->height;

        p_iterator = p_iterator->p_nextBaseComponent;
    }

    if (p_column->cellHeight == 0)
    {
        p_column->base.height += (p_column->componentCount - 1) * p_column->spacing;
    }
    else
    {
        p_column->base.height = (p_column->componentCount * p_column->cellHeight) + ((p_column->componentCount - 1) * p_column->spacing);
    }

    p_column->base.width = maxWidth;

#if GUI_CONFIG_USE_ANCHOR
    if (p_column->base.p_anchor != NULL)
    {
        graphics_setPosistionFromAnchor(p_columnBase);
    }
#endif /* GUI_CONFIG_USE_ANCHOR */

    uint16_t y = p_column->base.y;

    p_iterator = p_column->base.p_childList;
    int32_t item = 0;

    while (p_iterator != NULL)
    {
        base_setPosition(p_iterator, p_column->base.x, y);

        p_iterator->width = maxWidth;
#if GUI_CONFIG_USE_TOUCH
		if (p_iterator->p_touch != NULL)
		{
			p_iterator->p_touch->x = p_iterator->x;
			p_iterator->p_touch->y = p_iterator->y;
		}
#endif /* GUI_CONFIG_USE_TOUCH */
        base_display(p_iterator);

        const uint16_t cellHeight = (p_column->cellHeight > 0) ? p_column->cellHeight : p_iterator->height;

        if (!p_columnBase->transparent && (item < (p_column->componentCount - 1)) && (p_column->spacing > 0))
        {
            Rectangle_s rect;
            rectangle_initFillPosSize(&rect, p_columnBase->background,
                    p_columnBase->x,
                    y + cellHeight,
                    maxWidth, p_column->spacing);
            base_display(&rect);
        }

        y += cellHeight + p_column->spacing;
        p_iterator = p_iterator->p_nextBaseComponent;
        item++;
    }
}

