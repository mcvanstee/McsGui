/** @file gui_rectangle.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_COMPONENTS_GUI_RECTANGLE_H_
#define MCSGUI_COMPONENTS_GUI_RECTANGLE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "McsGui/gui_config.h"
#include "McsGui/Core/gui_basecomponent.h"


typedef struct rectangle_s
{
    BaseComponent_s base;
    FillData_s fillData;
} Rectangle_s;


#if GUI_USE_DYNAMIC_MEMORY
Rectangle_s *rectangle_new(void);
#endif /* GUI_USE_DYNAMIC_MEMORY */

void rectangle_delete(BaseComponent_s *p_rectangleBase);
void rectangle_init(Rectangle_s *p_rectangle);
void rectangle_init_1(
        Rectangle_s *p_rectangle, const Color_t color,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height);

void rectangle_init_2(
        Rectangle_s *p_rectangle, const Color_t color,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const Color_t borderColor);

void rectangle_initBorder(
        Rectangle_s *p_rectangle,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const Color_t borderColor);

void rectangle_displayDirect(Rectangle_s *p_rectangle);
void rectangle_setColor(Rectangle_s *p_rectangle, const Color_t color);
void rectangle_setBorderColor(Rectangle_s *p_rectangle, const Color_t color);
void rectangle_setBorderThickness(Rectangle_s *p_rectangle, const uint8_t thickness);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_RECTANGLE_H_ */


/*** end of file ***/
