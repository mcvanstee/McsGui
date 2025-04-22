#ifndef COMPONENTEXTENSIONS_GUI_LISTVIEW_EXTENSIONS_H_
#define COMPONENTEXTENSIONS_GUI_LISTVIEW_EXTENSIONS_H_

#include "mcsgui.h"
#include "fs_file_search.h"

ListView_s *listview_ext_newNavigationListView(void);
void listview_ext_addNavigationItem(ListView_s *p_listView, file_key_e icon, file_key_e text, void (*p_onPressed)(void));

ListView_s *listview_ext_newRadioListView(void);
void listview_ext_addRadioItem(
    ListView_s *p_listView, file_key_e text, RadioGroup_s *p_radioGroup);

void listview_ext_activeNavigationItemChanged(ListView_s *p_listView);

#endif /* COMPONENTEXTENSIONS_GUI_LISTVIEW_EXTENSIONS_H_ */
