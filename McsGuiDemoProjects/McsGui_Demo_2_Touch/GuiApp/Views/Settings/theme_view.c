#include "theme_view.h"

#include "gui_app.h"
#include "gui_custom_components.h"

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

    Pane_s *p_pane = pane_newInit();
    view_addComponent(p_view, p_pane);

    Column_s *p_column = gui_addRadioButtonColumn(p_view);
    RadioGroup_s *p_radioGroup = radiogroup_newInit();
    radiogroup_setOnSelectionChanged(p_radioGroup, tv_rgSelectionChanged);

    gui_addCheckboxLabel(p_column, p_radioGroup, FILE_KEY_TEXT_DFT_THEME_LIGHT);
    gui_addCheckboxLabel(p_column, p_radioGroup, FILE_KEY_TEXT_DFT_THEME_DARK);

    if (g_guiApp.theme.theme == PROPERTY_THEME_VALUE_LIGHT)
    {
        radiogroup_setSelectedAtIndex(p_radioGroup, 0);
    }
    else
    {
        radiogroup_setSelectedAtIndex(p_radioGroup, 1);
    }

    Row_s *p_footer = gui_addFooterButtonRow(p_view);
    gui_addFooterButton(p_footer, FILE_KEY_ICON_BTN_ARROW_BACK, settings_view_navigateTo);
    gui_addFooterSpacer(p_footer);
    gui_addFooterSpacer(p_footer);

    view_addComponent(p_view, p_radioGroup);
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
