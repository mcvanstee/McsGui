/** @file gui_button.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_COMPONENTS_GUI_BUTTON_H_
#define MCSGUI_COMPONENTS_GUI_BUTTON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gui_config.h"
#include "Core/gui_basecomponent.h"


typedef struct button_s
{
    BaseComponent_s base;
    void (*onPressed)(struct button_s *p_button);   // Callback function called when the button is pressed.
    void (*pressed)(struct button_s *p_button);     // Callback function called when the button is pressed.
    void (*onReleased)(struct button_s *p_button);  // Callback function called when the button is released.
    void (*onPressedEvent)(void);                   // Callback function called when the button is pressed.
    void (*pressedEvent)(void);                     // Callback function called when the button is pressed.
    void (*onReleasedEvent)(void);                  // Callback function called when the button is released.
} Button_s;


Button_s *button_new(void);
Button_s *button_newInit(void);

void button_init(Button_s *p_button);
void button_initBmp(Button_s *p_button, const uint32_t bmpKey);
void button_initBmpPos(
        Button_s *p_button, const uint32_t bmpKey,
        const uint16_t x, const uint16_t y);
void button_initBmpPosSize(
        Button_s *p_button, const uint32_t bmpKey,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height);

void button_setOnPressed(Button_s *p_button, void (*onPressed)(Button_s *p_buttonPressed));
void button_setPressed(Button_s *p_button, void (*pressed)(Button_s *p_buttonPressed));
void button_setOnReleased(Button_s *p_button, void (*onReleased)(Button_s *p_buttonReleased));
void button_setOnPressedEvent(Button_s *p_button, void (*onPressedEvent)(void));
void button_setPressedEvent(Button_s *p_button, void (*pressedEvent)(void));
void button_setOnReleasedEvent(Button_s *p_button, void (*onReleasedEvent)(void));

void button_display(Button_s *p_button);
void button_setId(Button_s *p_button, const uint32_t id);
void button_setBmpKey(Button_s *p_button, const uint32_t bmpKey);

void button_setX(Button_s *p_button, const uint16_t x);
void button_setY(Button_s *p_button, const uint16_t y);
void button_setWidth(Button_s *p_button, const uint16_t width);
void button_setHeight(Button_s *p_button, const uint16_t height);
void button_setPosition(Button_s *p_button, const uint16_t x, const uint16_t y);
void button_setSize(Button_s *p_button, const uint16_t width, const uint16_t height);

void button_setVisible(Button_s *p_button, const bool visible);
void button_setBackgroundColor(Button_s *p_button, const Color_t color);
void button_setDrawBackground(Button_s *p_button, const bool drawBackground);
#if GUI_CONFIG_USE_BITMAP_COLORS
void button_setForegroundColor(Button_s *p_button, const Color_t color);
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */

void button_setBmpAlignment(Button_s *p_button, const GuiAlignment_e horizontalAlignment, const GuiAlignment_e verticalAlignment);
void button_setBmpHorizontalAlignment(Button_s *p_button, const GuiAlignment_e horizontalAlignment);
void button_setBmpVerticalAlignment(Button_s *p_button, const GuiAlignment_e verticalAlignment);

void button_setBmpPadding(Button_s *p_button, const uint8_t left, const uint8_t top, const uint8_t right, const uint8_t bottom);
void button_setBmpLeftPadding(Button_s *p_button, const uint8_t padding);
void button_setBmpRightadding(Button_s *p_button, const uint8_t padding);
void button_setBmpTopPadding(Button_s *p_button, const uint8_t padding);
void button_setBmpBottomPadding(Button_s *p_button, const uint8_t padding);

#if GUI_CONFIG_USE_KEY_NAVIGATION
void button_setOnFocusChanged(Button_s *p_button, void (*onFocusChanged)(BaseComponent_s *p_base));
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_BUTTON_H_ */


/*** end of file ***/
