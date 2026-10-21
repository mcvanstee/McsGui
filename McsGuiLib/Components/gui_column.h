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

void column_init(Column_s *p_column);

void column_setSpacing(Column_s *p_column, const uint8_t spacing);
void column_setCellHeight(Column_s *p_column, const uint16_t cellHeight);
void column_addComponent(Column_s *p_column, void *p_component);

BaseComponent_s *column_getComponentAtIndex(Column_s *p_column, const uint8_t index);

void column_setX(Column_s *p_column, const uint16_t x);
void column_setY(Column_s *p_column, const uint16_t y);
void column_setPosition(Column_s *p_column, const uint16_t x, const uint16_t y);

void column_setVisible(Column_s *p_column, const bool visible);
void column_setBackgroundColor(Column_s *p_column, const Color_t color);
void column_setDrawBackground(Column_s *p_column, const bool drawBackground);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* COMPONENTS_GUI_COLUMN_H_ */
