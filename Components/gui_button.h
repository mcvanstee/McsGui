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

#include "McsGui/gui_config.h"
#include "McsGui/Core/gui_basecomponent.h"


typedef struct button_s
{
    BaseComponent_s base;
    void (*onPressed)(struct button_s *p_button);
    void (*onReleased)(struct button_s *p_button);
#if !GUI_USE_DYNAMIC_MEMORY
    char bmpName[GUI_CONFIG_BITMAP_NAME_LENGTH_INC_NULL];
#endif /* GUI_USE_DYNAMIC_MEMORY */
} Button_s;


#if GUI_USE_DYNAMIC_MEMORY
Button_s *button_new(void);
#endif /* GUI_USE_DYNAMIC_MEMORY */
void button_delete(BaseComponent_s *p_buttonBase);
void button_init(Button_s *p_button);
void button_init_1(
        Button_s *p_button, const char *p_bmpName,
        const uint16_t xPos, const uint16_t yPos);

void button_init_2(
        Button_s *p_button, const char *p_bmpName,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height);

void button_setOnPressed(Button_s *p_button, void (*onPressed)(Button_s *p_buttonPressed));
void button_setOnReleased(Button_s *p_button, void (*onReleased)(Button_s *p_buttonReleased));
bool button_handleEvent(BaseComponent_s *p_buttonBase, const GuiEvent_s *p_event);

#if GUI_CONFIG_USE_KEY_NAVIGATION
void button_setOnFocusChanged(Button_s *p_button, void (*onFocusChanged)(BaseComponent_s *p_base));
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_BUTTON_H_ */


/*** end of file ***/
