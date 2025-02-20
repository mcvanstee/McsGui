#ifndef COMPONENTEXTENSIONS_GUI_GRID_EXTENSIONS_H_
#define COMPONENTEXTENSIONS_GUI_GRID_EXTENSIONS_H_

#include "gui_theme.h"
#include "gui_page_button.h"

Grid_s *gui_addPageButtonGrid(View_s *p_view);
PageButton_s *gui_addPageButton(Grid_s *p_grid, const file_key_e icon, const file_key_e text, void (*onPressed)(void));

#endif /* COMPONENTEXTENSIONS_GUI_GRID_EXTENSIONS_H_ */
