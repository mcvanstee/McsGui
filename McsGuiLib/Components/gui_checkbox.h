/** @file gui_checkbox.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_COMPONENTS_GUI_CHECKBOX_H_
#define MCSGUI_COMPONENTS_GUI_CHECKBOX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "gui_config.h"
#include "Core/gui_basecomponent.h"


typedef struct checkbox_s
{
    BaseComponent_s base;
    bool checked;
    void (*onSelectionChanged)(struct checkbox_s *p_checkbox);
#if GUI_CONFIG_USE_RADIO_BUTTON_GROUP
    struct checkbox_s *p_nextInGroup;
    BaseComponent_s *p_radioGroupBase;
#endif /* GUI_CONFIG_USE_RADIO_BUTTON_GROUP */
} Checkbox_s;


Checkbox_s *checkbox_new(void);
Checkbox_s *checkbox_newInit(void);

void checkbox_init(Checkbox_s *p_checkbox);
void checkbox_initBmp(Checkbox_s *p_checkbox, const uint32_t bmpKey);
void checkbox_initBmpPos(
        Checkbox_s *p_checkbox, const uint32_t bmpKey,
        const uint16_t x, const uint16_t y);

void checkbox_initBmpPosSize(
        Checkbox_s *p_checkbox, uint32_t bmpKey,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height);

bool checkbox_isChecked(Checkbox_s *p_checkbox);

void checkbox_setOnSelectionChanged(Checkbox_s *p_checkbox, void (*onSelectionChanged)(Checkbox_s *p_checkboxChanged));
void checkbox_setSelection(Checkbox_s *p_checkbox, const bool selected);
void checkbox_setSelectionNotifyChanged(Checkbox_s *p_checkbox, const bool selected);

void checkbox_display(Checkbox_s *p_checkbox);
void checkbox_setId(Checkbox_s *p_checkbox, const uint32_t id);
void checkbox_setBmpKey(Checkbox_s *p_checkbox, const uint32_t bmpKey);

void checkbox_setX(Checkbox_s *p_checkbox, const uint16_t x);
void checkbox_setY(Checkbox_s *p_checkbox, const uint16_t y);
void checkbox_setWidth(Checkbox_s *p_checkbox, const uint16_t width);
void checkbox_setHeight(Checkbox_s *p_checkbox, const uint16_t height);
void checkbox_setPosition(Checkbox_s *p_checkbox, const uint16_t x, const uint16_t y);
void checkbox_setSize(Checkbox_s *p_checkbox, const uint16_t width, const uint16_t height);

void checkbox_setVisible(Checkbox_s *p_checkbox, const bool visible);
void checkbox_setBackgroundColor(Checkbox_s *p_checkbox, const Color_t color);
void checkbox_setDrawBackground(Checkbox_s *p_checkbox, const bool drawBackground);
#if GUI_CONFIG_USE_BITMAP_COLORS
void checkbox_setForegroundColor(Checkbox_s *p_checkbox, const Color_t color);
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */

void checkbox_setBmpAlignment(Checkbox_s *p_checkbox, const GuiAlignment_e horizontalAlignment, const GuiAlignment_e verticalAlignment);
void checkbox_setBmpHorizontalAlignment(Checkbox_s *p_checkbox, const GuiAlignment_e horizontalAlignment);
void checkbox_setBmpVerticalAlignment(Checkbox_s *p_checkbox, const GuiAlignment_e verticalAlignment);

void checkbox_setBmpPadding(Checkbox_s *p_checkbox, const uint8_t left, const uint8_t top, const uint8_t right, const uint8_t bottom);
void checkbox_setLeftBmpPadding(Checkbox_s *p_checkbox, const uint8_t padding);
void checkbox_setRightBmpPadding(Checkbox_s *p_checkbox, const uint8_t padding);
void checkbox_setTopBmpPadding(Checkbox_s *p_checkbox, const uint8_t padding);
void checkbox_setBottomBmpPadding(Checkbox_s *p_checkbox, const uint8_t padding);

#if GUI_CONFIG_USE_KEY_NAVIGATION
void checkbox_setOnFocusChanged(Checkbox_s *p_checkbox, void (*onFocusChanged)(BaseComponent_s *p_base));
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_CHECKBOX_H_ */


/*** end of file ***/
