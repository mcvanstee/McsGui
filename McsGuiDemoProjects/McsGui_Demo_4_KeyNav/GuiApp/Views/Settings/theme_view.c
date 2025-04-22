#include "theme_view.h"

#include "gui_app.h"

#include "settings_view.h"

static void tv_create(View_s *p_view);
static void tv_rgSelectionChanged(RadioGroup_s *p_radioGroup);

void theme_view_navigateTo(void)
{
    view_navigateTo(&g_guiApp.view, tv_create);
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

    radiogroup_setSelectedAtIndex(p_radioGroup, g_guiApp.theme.theme);
}

static void tv_rgSelectionChanged(RadioGroup_s *p_radioGroup)
{
    const int8_t selectedIndex = radiogroup_getSelectedIndex(p_radioGroup);

    if (selectedIndex == 0)
    {
        g_guiApp.theme.theme = PROPERTY_THEME_VALUE_LIGHT;
    }
    else
    {
        g_guiApp.theme.theme = PROPERTY_THEME_VALUE_DARK;
    }

    gui_drawBackground();
    theme_view_navigateTo();
}
