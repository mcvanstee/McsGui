#ifndef COMPONENTEXTENSIONS_GUI_CHECKBOX_EXTENSIONS_H_
#define COMPONENTEXTENSIONS_GUI_CHECKBOX_EXTENSIONS_H_

#include "mcsgui.h"
#include "fs_file_search.h"


Checkbox_s *custom_cmp_createCheckbox(
    const uint32_t bmpKey, bool checked, void (*onSelectionChanged)(Checkbox_s *p_checkboxChanged));

#endif /* COMPONENTEXTENSIONS_GUI_CHECKBOX_EXTENSIONS_H_ */
