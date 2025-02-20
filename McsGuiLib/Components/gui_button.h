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
    void (*onPressed)(struct button_s *p_button);    // Callback function called when the button is pressed.
    void (*pressed)(struct button_s *p_button);    // Callback function called when the button is pressed.
    void (*onReleased)(struct button_s *p_button);    // Callback function called when the button is released.
    void (*onPressedEvent)(void);    // Callback function called when the button is pressed.
    void (*pressedEvent)(void);    // Callback function called when the button is pressed.
    void (*onReleasedEvent)(void);    // Callback function called when the button is released.
} Button_s;


Button_s *button_new(void);
Button_s *button_newInit(void);

void button_delete(BaseComponent_s *p_buttonBase);
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

bool button_handleEvent(BaseComponent_s *p_buttonBase, const GuiEvent_s *p_event);

#if GUI_CONFIG_USE_KEY_NAVIGATION
void button_setOnFocusChanged(Button_s *p_button, void (*onFocusChanged)(BaseComponent_s *p_base));
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_BUTTON_H_ */


/*** end of file ***/
