#include "units_view.h"

#include "gui_app.h"

#include "settings_view.h"

static void untv_create(View_s *p_view);
static void untv_rgSelectionChanged(RadioGroup_s *p_radioGroup);

void units_view_navigateTo(void)
{
    view_navigateTo(&g_guiApp.view, untv_create);
}

static void untv_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_UNITS);

    RadioGroup_s *p_radioGroup = radiogroup_newInit();
    radiogroup_setOnSelectionChanged(p_radioGroup, untv_rgSelectionChanged);
    view_addComponent(p_view, p_radioGroup);

    ListView_s *p_listView = listview_ext_newRadioListView();
    listview_ext_addNavigationItem(p_listView, FILE_KEY_ICON_ARROW_BACK, FILE_KEY_TEXT_BACK, settings_view_navigateBackTo);
    listview_ext_addRadioItem(p_listView, FILE_KEY_TEXT_DEG_CEL, p_radioGroup);
    listview_ext_addRadioItem(p_listView, FILE_KEY_TEXT_DEG_FAR, p_radioGroup);
    listview_setActiveIndex(p_listView, 0);
    base_setFocus(p_listView, true);
    view_addComponent(p_view, p_listView);

    radiogroup_setSelectedAtIndex(p_radioGroup, g_guiApp.temperatureUnit);
}

static void untv_rgSelectionChanged(RadioGroup_s *p_radioGroup)
{
    const int8_t selectedIndex = radiogroup_getSelectedIndex(p_radioGroup);

    if (selectedIndex == 0)
    {
        g_guiApp.temperatureUnit = TemperatureUnit_Celsius;
    }
    else
    {
        g_guiApp.temperatureUnit = TemperatureUnit_Fahrenheit;
    }
}
