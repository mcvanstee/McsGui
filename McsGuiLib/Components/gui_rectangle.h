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

#include "gui_config.h"
#include "Core/gui_basecomponent.h"


typedef struct rectangle_s
{
    BaseComponent_s base;
    BorderData_s borderData;
} Rectangle_s;


Rectangle_s *rectangle_new(void);
Rectangle_s *rectangle_newInit(void);

void rectangle_delete(BaseComponent_s *p_rectangleBase);
void rectangle_init(Rectangle_s *p_rectangle);

void rectangle_initFillSize(
        Rectangle_s *p_rectangle, const Color_t color,
        const uint16_t width, const uint16_t height);

void rectangle_initFillPosSize(
        Rectangle_s *p_rectangle, const Color_t color,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height);

void rectangle_initFillBorderSize(
        Rectangle_s *p_rectangle, const Color_t color,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const Color_t borderColor);

void rectangle_initFillBorderPosSize(
        Rectangle_s *p_rectangle, const Color_t color,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const Color_t borderColor);

void rectangle_initBorderSize(
        Rectangle_s *p_rectangle,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const Color_t borderColor);

void rectangle_initBorderPosSize(
        Rectangle_s *p_rectangle,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const Color_t borderColor);

void rectangle_displayDirect(Rectangle_s *p_rectangle);
void rectangle_setColor(Rectangle_s *p_rectangle, const Color_t color);
void rectangle_showBorderOnly(Rectangle_s *p_rectangle, const bool showBorderOnly);
void rectangle_setBorderColor(Rectangle_s *p_rectangle, const Color_t color);
void rectangle_setBorderThickness(Rectangle_s *p_rectangle, const uint8_t thickness);
void rectangle_setRadius(Rectangle_s *p_rectangle, const uint8_t radius);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_RECTANGLE_H_ */


/*** end of file ***/
