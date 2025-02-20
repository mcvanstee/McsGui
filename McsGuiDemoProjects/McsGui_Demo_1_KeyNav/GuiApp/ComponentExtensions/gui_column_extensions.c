#include "gui_column_extensions.h"

Column_s *gui_addRadioButtonColumn(View_s *p_view)
{
    Column_s *p_column = column_newInit();
    column_setSpacing(p_column, 10);
    base_setPosition(&p_column->base, 20, 55);
    view_addComponent(p_view, p_column);

    return p_column;
}

CheckboxLabel_s *gui_addCheckboxLabel(Column_s *p_column, RadioGroup_s *p_radioGroup, const file_key_e text)
{
    CheckboxLabel_s *p_checkboxLabel = checkbox_label_new();
    checkbox_label_initLabel(p_checkboxLabel, text);
    column_addComponent(p_column, p_checkboxLabel);
    radiogroup_addButton(p_radioGroup, &p_checkboxLabel->checkBox);

    return p_checkboxLabel;
}
