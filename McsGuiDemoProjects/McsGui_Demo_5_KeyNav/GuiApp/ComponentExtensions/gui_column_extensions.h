#ifndef COMPONENTEXTENSIONS_GUI_COLUMN_EXTENSIONS_H_
#define COMPONENTEXTENSIONS_GUI_COLUMN_EXTENSIONS_H_

#include "gui_theme.h"
#include "gui_checkbox_label.h"

Column_s *gui_addRadioButtonColumn(View_s *p_view);
CheckboxLabel_s *gui_addCheckboxLabel(Column_s *p_column, RadioGroup_s *p_radioGroup, const file_key_e text);

#endif /* COMPONENTEXTENSIONS_GUI_COLUMN_EXTENSIONS_H_ */
