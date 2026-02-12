#include "theme_view.h"

#include "gui_app.h"

#include "settings_view.h"

static void tv_create(View_s *p_view);
static void tv_rgSelectionChanged(RadioGroup_s *p_radioGroup);

void theme_view_navigateTo(void)
{
    view_navigateTo(gui_app_getView(), tv_create);
}

static void tv_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_THEME);

    RadioGroup_s *p_radioGroup = radiogroup_newInit();
    radiogroup_setOnSelectionChanged(p_radioGroup, tv_rgSelectionChanged);
    view_addComponent(p_view, p_radioGroup);

    ListView_s *p_listView = listview_ext_newRadioListView();
    listview_ext_addNavigationItem(p_listView, FILE_KEY_ICON_ARROW_BACK, FILE_KEY_TEXT_BACK, settings_view_navigateBackTo);
    listview_ext_addRadioItem(p_listView, FILE_KEY_TEXT_THEME_LIGHT, p_radioGroup);
    listview_ext_addRadioItem(p_listView, FILE_KEY_TEXT_THEME_DARK, p_radioGroup);
    listview_setActiveIndex(p_listView, 0);
    base_setFocus(p_listView, true);
    view_addComponent(p_view, p_listView);

    const int8_t index = (int8_t)theme_getGuiTheme();
    radiogroup_setSelectedAtIndex(p_radioGroup, index);
}

static void tv_rgSelectionChanged(RadioGroup_s *p_radioGroup)
{
    const GuiTheme_e theme = (GuiTheme_e)radiogroup_getSelectedIndex(p_radioGroup);
    theme_setGuiTheme(theme);

    gui_app_drawBackground();
    theme_view_navigateTo();
}
