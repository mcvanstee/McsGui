#ifndef CUSTOMCOMPONENTS_GUI_CHECKBOX_LABEL_H_
#define CUSTOMCOMPONENTS_GUI_CHECKBOX_LABEL_H_

#include "mcsgui.h"
#include "fs_file_search.h"

typedef struct checkbox_label_s
{
    Checkbox_s checkBox;
    file_key_e label;
    uint16_t labelWidth;
    uint8_t labelPadding;
    Touch_s touch;
    void (*onSelectionChanged)(struct checkbox_label_s *p_checkboxLabel);
} CheckboxLabel_s;

CheckboxLabel_s *checkbox_label_new(void);
CheckboxLabel_s *checkbox_label_newInit(void);

void checkbox_label_delete(BaseComponent_s *p_checkboxLabelBase);
void checkbox_label_init(CheckboxLabel_s *p_checkboxLabel);
void checkbox_label_init_1(CheckboxLabel_s *p_checkboxLabel, file_key_e label);
void checkbox_label_initSwitch(CheckboxLabel_s *p_checkboxLabel, file_key_e label);
void checkbox_label_displayLabel(CheckboxLabel_s *p_checkboxLabel);

void checkbox_label_setOnSelectionChanged(
		CheckboxLabel_s *p_checkboxLabel, void (*onSelectionChanged)(CheckboxLabel_s *p_checkboxLabel));

#endif /* CUSTOMCOMPONENTS_GUI_CHECKBOX_LABEL_H_ */
