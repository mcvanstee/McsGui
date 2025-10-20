#ifndef COMPONENTEXTENSIONS_GUI_ROW_EXTENSIONS_H_
#define COMPONENTEXTENSIONS_GUI_ROW_EXTENSIONS_H_

#include "gui_theme.h"
#include "gui_footer_button.h"

Row_s *gui_addFooterButtonRow(View_s *p_view);
FooterButton_s *gui_addFooterButton(Row_s *p_row, const file_key_e icon, void (*onPressed)(void));
void gui_addFooterSpacer(Row_s *p_row);

#endif /* COMPONENTEXTENSIONS_GUI_ROW_EXTENSIONS_H_ */
