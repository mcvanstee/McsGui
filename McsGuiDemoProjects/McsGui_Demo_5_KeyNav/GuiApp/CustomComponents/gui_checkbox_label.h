#ifndef CUSTOMCOMPONENTS_GUI_CHECKBOX_LABEL_H_
#define CUSTOMCOMPONENTS_GUI_CHECKBOX_LABEL_H_

#include "gui_theme.h"

typedef struct
{
    Checkbox_s checkBox;
    file_key_e label;
    KeyNavigation_s keyNavigation;
} CheckboxLabel_s;

CheckboxLabel_s *checkbox_label_new(void);
CheckboxLabel_s *checkbox_label_newInit(void);

void checkbox_label_delete(BaseComponent_s *p_checkboxLabelBase);
void checkbox_label_init(CheckboxLabel_s *p_checkboxLabel);
void checkbox_label_initLabel(CheckboxLabel_s *p_checkboxLabel, file_key_e label);

#endif /* CUSTOMCOMPONENTS_GUI_CHECKBOX_LABEL_H_ */
