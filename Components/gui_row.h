/** @file gui_row.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef COMPONENTS_GUI_ROW_H_
#define COMPONENTS_GUI_ROW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gui_config.h"
#include "Core/gui_basecomponent.h"

typedef struct gui_row_s
{
    BaseComponent_s base;   // Base component
    uint8_t spacing;        // Spacing between components in pixels
    uint8_t componentCount; // Number of components in the row
    uint8_t cellWidth;      // Width of the cell in pixels, if 0, the width is calculated based on the components
} Row_s;

Row_s *row_new(void);
Row_s *row_newInit(void);

void row_delete(BaseComponent_s *p_rowBase);
void row_init(Row_s *p_row);

void row_setSpacing(Row_s *p_row, uint8_t spacing);
void row_setCellWidth(Row_s *p_row, uint8_t cellWidth);
void row_addComponent(Row_s *p_row, void *p_component);

BaseComponent_s *row_getComponent(Row_s *p_row, uint8_t index);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* COMPONENTS_GUI_ROW_H_ */


/*** end of file ***/
