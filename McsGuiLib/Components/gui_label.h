/** @file gui_label.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_COMPONENTS_GUI_LABEL_H_
#define MCSGUI_COMPONENTS_GUI_LABEL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gui_config.h"
#include "Core/gui_basecomponent.h"


typedef struct label_s
{
    BaseComponent_s base;
} Label_s;


Label_s *label_new(void);
Label_s *label_newInit(void);

void label_init(Label_s *p_label);
void label_initBmp(Label_s *p_label, const uint32_t bmpKey);
void label_initBmpPos(
        Label_s *p_label, const uint32_t bmpKey,
        const uint16_t x, const uint16_t y);

void label_initBmpPosSize(
        Label_s *p_label, const uint32_t bmpKey,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height);

void label_initBmpPosSizeBack(
        Label_s *p_label, const uint32_t bmpKey,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const Color_t backgroundColor);

void label_display(Label_s *p_label);
void label_setId(Label_s *p_label, const uint32_t id);
void label_setBmpKey(Label_s *p_label, const uint32_t bmpKey);

void label_setX(Label_s *p_label, const uint16_t x);
void label_setY(Label_s *p_label, const uint16_t y);
void label_setWidth(Label_s *p_label, const uint16_t width);
void label_setHeight(Label_s *p_label, const uint16_t height);
void label_setPosition(Label_s *p_label, const uint16_t x, const uint16_t y);
void label_setSize(Label_s *p_label, const uint16_t width, const uint16_t height);

void label_setVisible(Label_s *p_label, const bool visible);
void label_setBackgroundColor(Label_s *p_label, const Color_t color);
void label_setDrawBackground(Label_s *p_label, const bool drawBackground);
#if GUI_CONFIG_USE_BITMAP_COLORS
void label_setForegroundColor(Label_s *p_label, const Color_t color);
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */

void label_setBmpAlignment(Label_s *p_label, const GuiAlignment_e horizontalAlignment, const GuiAlignment_e verticalAlignment);
void label_setBmpHorizontalAlignment(Label_s *p_label, const GuiAlignment_e horizontalAlignment);
void label_setBmpVerticalAlignment(Label_s *p_label, const GuiAlignment_e verticalAlignment);

void label_setBmpPadding(Label_s *p_label, const uint8_t left, const uint8_t top, const uint8_t right, const uint8_t bottom);
void label_setLeftBmpPadding(Label_s *p_label, const uint8_t padding);
void label_setRightBmpPadding(Label_s *p_label, const uint8_t padding);
void label_setTopBmpPadding(Label_s *p_label, const uint8_t padding);
void label_setBottomBmpPadding(Label_s *p_label, const uint8_t padding);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_LABEL_H_ */


/*** end of file ***/
