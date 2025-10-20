#include "gui_grid.h"

#include <stddef.h>

#include "Core/gui_log.h"
#include "Core/gui_memory.h"
#include "Graphics/gui_graphics.h"
#include "gui_rectangle.h"

#if !GUI_USE_DYNAMIC_MEMORY
static bool staticGridMemInUse[GUI_CONFIG_GRID_BUFFER_SIZE] = {0};
static Grid_s staticGridMem[GUI_CONFIG_GRID_BUFFER_SIZE] = {0};
#endif /* GUI_USE_DYNAMIC_MEMORY */


static void grid_display(BaseComponent_s *p_gridBase);


/**
 * @brief Creates a new malloced Grid component.
 * @return Pointer to the malloced memory.
 *
 * @warning The returned component is not initialized.
 *
 */
Grid_s *grid_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(Grid_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_GRID_BUFFER_SIZE; i++)
    {
        if (!staticGridMemInUse[i])
        {
            staticGridMemInUse[i] = true;

            return &staticGridMem[i];
        }
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No Grid_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Creates a new Grid_s component and initializes it to default values.
 * @return Pointer to the Grid_s component.
 *
 */
Grid_s *grid_newInit(void)
{
    Grid_s *p_grid = grid_new();
    grid_init(p_grid);

    return p_grid;
}


/**
 * @brief Delete the Grid_s component. This functions calls the gui_mem_free function to free the allocated memory.
 * @param[in] p_gridBase Pointer to the Grid_s component to be freed.
 *
 */
void grid_delete(BaseComponent_s *p_gridBase)
{
    base_clear(p_gridBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_gridBase, sizeof(Grid_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_GRID_BUFFER_SIZE; i++)
    {
        if (&staticGridMem[i].base == p_gridBase)
        {
            staticGridMemInUse[i] = false;
            break;
        }
    }
    #endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Initializes the Grid_s component to default values.
 * @param[in] p_grid Pointer to the Grid_s component.
 *
 */
void grid_init(Grid_s *p_grid)
{
    base_initParentComp(&p_grid->base, grid_delete);
    p_grid->base.onDisplay = grid_display;

    p_grid->rowSpacing = 0;
    p_grid->columnSpacing = 0;
    p_grid->componentCount = 0;
    p_grid->columns = 1;
    p_grid->rows = 1;
    p_grid->cellWidth = 0;
    p_grid->cellHeight = 0;
}


/**
 * @brief Set the row spacing between the components in the grid.
 * @param[in] p_grid Pointer to the Grid_s component.
 * @param[in] spacing The spacing between the rows.
 *
 */
void grid_setRowSpacing(Grid_s *p_grid, uint8_t spacing)
{
    p_grid->rowSpacing = spacing;
}


/**
 * @brief Set the column spacing between the components in the grid.
 * @param[in] p_grid Pointer to the Grid_s component.
 * @param[in] spacing The spacing between the columns.
 *
 */
void grid_setColumnSpacing(Grid_s *p_grid, uint8_t spacing)
{
    p_grid->columnSpacing = spacing;
}


/**
 * @brief Set the number of columns in the grid.
 * @param[in] p_grid Pointer to the Grid_s component.
 * @param[in] columns The number of columns.
 *
 */
void grid_setColumns(Grid_s *p_grid, uint8_t columns)
{
    p_grid->columns = columns;
}


/**
 * @brief Set the number of rows in the grid.
 * @param[in] p_grid Pointer to the Grid_s component.
 * @param[in] rows The number of rows.
 *
 */
void grid_setRows(Grid_s *p_grid, uint8_t rows)
{
    p_grid->rows = rows;
}


/**
 * @brief Add a component to the grid.
 * @param[in] p_grid Pointer to the Grid_s component.
 * @param[in] p_base Pointer to the component to be added.
 *
 */
void grid_addComponent(Grid_s *p_grid, void *p_base)
{
    BaseComponent_s *p_component = (BaseComponent_s*) p_base;

    if (p_grid->base.p_childList == NULL)
    {
        p_grid->componentCount = 1;
        p_grid->base.p_childList = p_component;

        return;
    }

    BaseComponent_s *p_iterator = p_grid->base.p_childList;
    while (p_iterator->p_nextBaseComponent != NULL)
    {
        p_iterator = p_iterator->p_nextBaseComponent;
    }

    p_grid->componentCount++;
    p_iterator->p_nextBaseComponent = p_component;
}


/**
 * @brief Get a component from the grid.
 * @param[in] p_grid Pointer to the Grid_s component.
 * @param[in] row The row of the component.
 * @param[in] column The column of the component.
 * @return Pointer to the component.
 *
 */
BaseComponent_s *grid_getComponent(Grid_s *p_grid, uint8_t row, uint8_t column)
{
    const uint8_t index = (row * p_grid->columns) + column;

    return grid_getComponentAtIndex(p_grid, index);
}


/**
 * @brief Get a component from the grid.
 * @param[in] p_grid Pointer to the Grid_s component.
 * @param[in] index The index of the component.
 * @return Pointer to the component.
 *
 */
BaseComponent_s* grid_getComponentAtIndex(Grid_s *p_grid, uint8_t index)
{
    if ((p_grid->base.p_childList == NULL) || (index >= p_grid->componentCount))
    {
        return NULL;
    }

    BaseComponent_s *p_iterator = p_grid->base.p_childList;

    for (uint8_t i = 0; i < index; i++)
    {
        if (p_iterator == NULL)
        {
            return NULL;
        }
        else
        {
            p_iterator = p_iterator->p_nextBaseComponent;
        }
    }

    return p_iterator;
}


/**
 * @brief Set the width of the cells in the grid.
 * @param[in] p_grid Pointer to the Grid_s component.
 * @param[in] cellWidth The width of the cells.
 *
 */
void grid_setCellWidth(Grid_s *p_grid, uint16_t cellWidth)
{
    p_grid->cellWidth = cellWidth;
}


/**
 * @brief Set the height of the cells in the grid.
 * @param[in] p_grid Pointer to the Grid_s component.
 * @param[in] cellHeight The height of the cells.
 *
 */
void grid_setCellHeight(Grid_s *p_grid, uint16_t cellHeight)
{
    p_grid->cellHeight = cellHeight;
}


/**
 * @brief Display the Grid component.
 * @param[in] p_gridBase Pointer to the Grid component.
 *
 */
static void grid_display(BaseComponent_s *p_gridBase)
{
    Grid_s *p_grid = (Grid_s*)p_gridBase;

    uint16_t maxWidth = 0;
    uint16_t maxHeight = 0;
    uint16_t columnSpacing = p_grid->columnSpacing;
    uint16_t rowSpacing = p_grid->rowSpacing;
    uint8_t columns = p_grid->columns;
    uint8_t rows = p_grid->rows;

    BaseComponent_s *p_iterator = p_grid->base.p_childList;
    while (p_iterator != NULL)
    {
        graphics_setSizeFromBmp(p_iterator);

        if (p_iterator->width > maxWidth)
        {
            maxWidth = p_iterator->width;
        }

        if (p_iterator->height > maxHeight)
        {
            maxHeight = p_iterator->height;
        }

        p_iterator = p_iterator->p_nextBaseComponent;
    }

    p_grid->base.width = (maxWidth * columns) + (rowSpacing * (columns - 1));
    p_grid->base.height = (maxHeight * rows) + (columnSpacing * (rows - 1));

#if GUI_CONFIG_USE_ANCHOR
    if (p_grid->base.p_anchor != NULL)
    {
        graphics_setPosistionFromAnchor(p_gridBase);
    }
#endif /* GUI_CONFIG_USE_ANCHOR */

    uint16_t x = p_grid->base.x;
    uint16_t y = p_grid->base.y;

    p_iterator = p_grid->base.p_childList;
    for (uint8_t i = 0; i < rows; i++)
    {
        if ((!p_gridBase->transparent) && (i > 0) && (columnSpacing > 0))
        {
            Rectangle_s rect;
            rectangle_initFillPosSize(
                    &rect, p_gridBase->background,
                    x, y + (i * maxHeight) + ((i - 1) * columnSpacing),
                    p_grid->base.width, columnSpacing);
            base_display(&rect);
        }

        for (uint8_t j = 0; j < columns; j++)
        {
            if (p_iterator != NULL)
            {
                p_iterator->x = x + (j * (maxWidth + columnSpacing));
                p_iterator->y = y + (i * (maxHeight + rowSpacing));
                p_iterator->onDisplay(p_iterator);

#if GUI_CONFIG_USE_TOUCH
				if (p_iterator->p_touch != NULL)
				{
					p_iterator->p_touch->x = p_iterator->x;
					p_iterator->p_touch->y = p_iterator->y;
				}
#endif /* GUI_CONFIG_USE_TOUCH */

                p_iterator = p_iterator->p_nextBaseComponent;
            }
            else
            {
                if (!p_gridBase->transparent)
                {
                    Rectangle_s rect;
                    rectangle_initFillPosSize(&rect, p_gridBase->background,
                            x + (j * (maxWidth + columnSpacing)),
                            y + (i * (maxHeight + rowSpacing)),
                            maxWidth, maxHeight);
                    base_display(&rect);
                }
            }

            if ((!p_gridBase->transparent) && (i == 0) && (j < (columns - 1)) && (rowSpacing > 0))
            {
                Rectangle_s rect;
                rectangle_initFillPosSize(&rect, p_gridBase->background,
                        x + ((j + 1) * maxWidth) + (j * rowSpacing),
                        y,
                        rowSpacing,
                        p_grid->base.height);
                base_display(&rect);
            }
        }
    }
}
