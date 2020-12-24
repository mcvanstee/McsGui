/** @file gui_radiogroup.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_COMPONENTS_GUI_RADIOGROUP_H_
#define MCSGUI_COMPONENTS_GUI_RADIOGROUP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "McsGui/gui_config.h"
#include "McsGui/Core/gui_basecomponent.h"
#include "gui_checkbox.h"


typedef struct radio_group_s
{
    BaseComponent_s base;
    int8_t numberOfButtons;
    void (*onSelectionChanged)(struct radio_group_s *p_radioGroup);
} RadioGroup_s;


#if GUI_USE_DYNAMIC_MEMORY
RadioGroup_s *radiogroup_new(void);
#endif /* GUI_USE_DYNAMIC_MEMORY */

void radiogroup_delete(BaseComponent_s *p_radioGroupBase);
void radiogroup_init(RadioGroup_s *p_radioGroup);
void radiogroup_addButton(RadioGroup_s *p_radioGroup, Checkbox_s *p_checkbox);
void radiogroup_setOnSelectionChg(RadioGroup_s *p_radioGroup, void (*onSelectionChanged)(RadioGroup_s *p_radioGroupChanged));
void radiogroup_setSelected(RadioGroup_s *p_radioGroup, Checkbox_s *p_checkboxToSelect);
void radiogroup_setSelectedAtIndex(RadioGroup_s *p_radioGroup, const int8_t index);
Checkbox_s *radiogroup_getSelected(RadioGroup_s *p_radioGroup);
Checkbox_s *radiogroup_getButtonAtIndex(RadioGroup_s *p_radioGroup, const int8_t index);
int8_t radiogroup_getSelectedIndex(RadioGroup_s *p_radioGroup);
bool radiogroup_handleButtonPressed(BaseComponent_s *p_radioGroupBase, Checkbox_s *p_checkboxPressed);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_RADIOGROUP_H_ */


/*** end of file ***/
