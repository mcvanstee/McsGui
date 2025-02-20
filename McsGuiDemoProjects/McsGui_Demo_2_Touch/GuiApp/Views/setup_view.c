#include "setup_view.h"

#include <stdio.h>

#include "gui_app.h"
#include "gui_custom_components.h"

#include "main_view.h"

static void setup_view_create(View_s *p_view);
static void sv_rgSelectionChanged(RadioGroup_s *p_radioGroup);

void setup_view_navigateTo(void)
{
    view_navigateTo(&g_guiApp.view, setup_view_create);
}

static void setup_view_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_SETUP);

    Pane_s *p_pane = pane_newInit();
    view_addComponent(p_view, p_pane);

    Column_s *p_column = gui_addRadioButtonColumn(p_view);
    RadioGroup_s *p_radioGroup = radiogroup_newInit();
    radiogroup_setOnSelectionChanged(p_radioGroup, sv_rgSelectionChanged);
    view_addComponent(p_view, p_radioGroup);

    gui_addCheckboxLabel(p_column, p_radioGroup, FILE_KEY_TEXT_DFT_DEG_CEL);
    gui_addCheckboxLabel(p_column, p_radioGroup, FILE_KEY_TEXT_DFT_DEG_FAR);

    if (g_guiApp.temperatureUnit == TemperatureUnit_Celsius)
    {
        radiogroup_setSelectedAtIndex(p_radioGroup, 0);
    }
    else
    {
        radiogroup_setSelectedAtIndex(p_radioGroup, 1);
    }

    Row_s *p_footer = gui_addFooterButtonRow(p_view);
    gui_addFooterButton(p_footer, FILE_KEY_ICON_BTN_ARROW_BACK, mainview_navigateTo);
    gui_addFooterSpacer(p_footer);
    gui_addFooterSpacer(p_footer);
}

static void sv_rgSelectionChanged(RadioGroup_s *p_radioGroup)
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
