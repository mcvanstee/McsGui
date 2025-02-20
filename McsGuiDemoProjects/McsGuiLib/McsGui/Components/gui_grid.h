/** @file gui_grid.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef COMPONENTS_GUI_GRID_H_
#define COMPONENTS_GUI_GRID_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gui_config.h"
#include "Core/gui_basecomponent.h"

typedef struct gui_grid_s
{
    BaseComponent_s base;
    uint8_t rows;
    uint8_t columns;
    uint8_t columnSpacing;
    uint8_t rowSpacing;
    uint8_t componentCount;
    uint16_t cellWidth;
    uint16_t cellHeight;
} Grid_s;

Grid_s *grid_new(void);
Grid_s *grid_newInit(void);

void grid_delete(BaseComponent_s *p_gridBase);
void grid_init(Grid_s *p_grid);

void grid_setRows(Grid_s *p_grid, uint8_t rows);
void grid_setColumns(Grid_s *p_grid, uint8_t columns);
void grid_setColumnSpacing(Grid_s *p_grid, uint8_t columnSpacing);
void grid_setRowSpacing(Grid_s *p_grid, uint8_t rowSpacing);
void grid_setCellWidth(Grid_s *p_grid, uint16_t cellWidth);
void grid_setCellHeight(Grid_s *p_grid, uint16_t cellHeight);
void grid_addComponent(Grid_s *p_grid, void *p_component);

BaseComponent_s *grid_getComponent(Grid_s *p_grid, uint8_t row, uint8_t column);
BaseComponent_s *grid_getComponentAtIndex(Grid_s *p_grid, uint8_t index);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* COMPONENTS_GUI_GRID_H_ */


/*** end of file ***/
