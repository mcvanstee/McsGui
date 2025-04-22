#include "language_view.h"

#include "gui_app.h"

#include "settings_view.h"

static void lv_create(View_s *p_view);
static void lv_rgSelectionChanged(RadioGroup_s *p_radioGroup);


void language_view_navigateTo(void)
{
    view_navigateTo(&g_guiApp.view, lv_create);
}

static void lv_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_LANGUAGE);

    RadioGroup_s *p_radioGroup = radiogroup_newInit();
    radiogroup_setOnSelectionChanged(p_radioGroup, lv_rgSelectionChanged);
    view_addComponent(p_view, p_radioGroup);

    ListView_s *p_listView = listview_ext_newRadioListView();
    listview_ext_addNavigationItem(p_listView, FILE_KEY_ICON_ARROW_BACK, FILE_KEY_TEXT_BACK, settings_view_navigateBackTo);
    listview_ext_addRadioItem(p_listView, FILE_KEY_TEXT_ENGLISH, p_radioGroup);
    listview_ext_addRadioItem(p_listView, FILE_KEY_TEXT_DUTCH, p_radioGroup);
    listview_ext_addRadioItem(p_listView, FILE_KEY_TEXT_GERMAN, p_radioGroup);
    listview_ext_addRadioItem(p_listView, FILE_KEY_TEXT_FRENCH, p_radioGroup);
    listview_ext_addRadioItem(p_listView, FILE_KEY_TEXT_SPANISH, p_radioGroup);
    listview_ext_addRadioItem(p_listView, FILE_KEY_TEXT_ITALIAN, p_radioGroup);
    listview_ext_addRadioItem(p_listView, FILE_KEY_TEXT_RUSSIAN, p_radioGroup);
    listview_ext_addRadioItem(p_listView, FILE_KEY_TEXT_CHINESE_SIM, p_radioGroup);
    listview_ext_addRadioItem(p_listView, FILE_KEY_TEXT_JAPANESE, p_radioGroup);
    listview_ext_addRadioItem(p_listView, FILE_KEY_TEXT_KOREAN, p_radioGroup);
    listview_setActiveIndex(p_listView, 0);
    base_setFocus(p_listView, true);
    view_addComponent(p_view, p_listView);

    radiogroup_setSelectedAtIndex(p_radioGroup, g_guiApp.language);
}

static void lv_rgSelectionChanged(RadioGroup_s *p_radioGroup)
{
    g_guiApp.language = radiogroup_getSelectedIndex(p_radioGroup);
    header_setTitle(FILE_KEY_TITLE_LANGUAGE);
}
