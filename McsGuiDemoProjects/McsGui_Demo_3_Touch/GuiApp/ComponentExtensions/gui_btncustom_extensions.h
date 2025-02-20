#ifndef COMPONENTEXTENSIONS_GUI_BTNCUSTOM_EXTENSIONS_H_
#define COMPONENTEXTENSIONS_GUI_BTNCUSTOM_EXTENSIONS_H_

#include "gui_button_custom.h"
#include "fs_file_search.h"


ButtonCustom_s* custom_cmp_createIconNavButton(
    const file_key_e icon, const file_key_e text, void (*onReleased)(void));

#endif /* COMPONENTEXTENSIONS_GUI_BTNCUSTOM_EXTENSIONS_H_ */
