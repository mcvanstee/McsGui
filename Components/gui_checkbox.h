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

#include "McsGui/gui_config.h"
#include "McsGui/Core/gui_basecomponent.h"


typedef struct checkbox_s
{
    BaseComponent_s base;
    bool checked;
    void (*onSelectionChanged)(struct checkbox_s *p_checkbox);
#if GUI_CONFIG_USE_RADIO_BUTTON_GROUP
    BaseComponent_s *p_radioGroupBase;
#endif /* GUI_CONFIG_USE_RADIO_BUTTON_GROUP */
#if !GUI_USE_DYNAMIC_MEMORY
    char bmpName[GUI_CONFIG_BITMAP_NAME_LENGTH_INC_NULL];
#endif /* GUI_USE_DYNAMIC_MEMORY */
} Checkbox_s;


#if GUI_USE_DYNAMIC_MEMORY
Checkbox_s *checkbox_new(void);
#endif /* GUI_USE_DYNAMIC_MEMORY */
void checkbox_delete(BaseComponent_s *p_checkboxBase);
void checkbox_init(Checkbox_s *p_checkbox);
void checkbox_init_1(
        Checkbox_s *p_checkbox, const char *p_bmpName,
        const uint16_t xPos, const uint16_t yPos);

void checkbox_init_2(
        Checkbox_s *p_checkbox, const char *p_bmpName,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height);

void checkbox_setOnSelectionchanged(Checkbox_s *p_checkbox, void (*onSelectionChanged)(Checkbox_s *p_checkboxChanged));
void checkbox_setSelection(Checkbox_s *p_checkbox, const bool selected);
bool checkbox_handleEvent(BaseComponent_s *p_checkboxBase, const GuiEvent_s *p_event);

#if GUI_CONFIG_USE_KEY_NAVIGATION
void checkbox_setOnFocusChanged(Checkbox_s *p_checkbox, void (*onFocusChanged)(BaseComponent_s *p_base));
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_CHECKBOX_H_ */


/*** end of file ***/
