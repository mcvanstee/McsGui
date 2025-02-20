/** @file gui_column.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef COMPONENTS_GUI_COLUMN_H_
#define COMPONENTS_GUI_COLUMN_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gui_config.h"
#include "Core/gui_basecomponent.h"

typedef struct gui_column_s
{
    BaseComponent_s base;   // Base component
    uint8_t spacing;        // Spacing between components in pixels
    uint8_t componentCount; // Number of components in the column
    uint8_t cellHeight;     // Height of the cell in pixels, if 0 the height is calculated based on the components
} Column_s;

Column_s *column_new(void);
Column_s *column_newInit(void);

void column_delete(BaseComponent_s *p_columnBase);
void column_init(Column_s *p_column);

void column_setSpacing(Column_s *p_column, uint8_t spacing);
void column_addComponent(Column_s *p_column, void *p_component);

BaseComponent_s *column_getComponent(Column_s *p_column, uint8_t index);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* COMPONENTS_GUI_COLUMN_H_ */
