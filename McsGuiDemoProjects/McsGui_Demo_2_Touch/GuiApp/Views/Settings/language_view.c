#include "language_view.h"

#include "gui_app.h"
#include "gui_custom_components.h"

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

    Pane_s *p_pane = pane_newInit();
    view_addComponent(p_view, p_pane);

    Column_s *p_column = gui_addRadioButtonColumn(p_view);
    RadioGroup_s *p_radioGroup = radiogroup_newInit();
    radiogroup_setOnSelectionChanged(p_radioGroup, lv_rgSelectionChanged);

    gui_addCheckboxLabel(p_column, p_radioGroup, FILE_KEY_TEXT_DFT_ENGLISH);
    gui_addCheckboxLabel(p_column, p_radioGroup, FILE_KEY_TEXT_DFT_DUTCH);
    gui_addCheckboxLabel(p_column, p_radioGroup, FILE_KEY_TEXT_DFT_GERMAN);
    radiogroup_setSelectedAtIndex(p_radioGroup, g_guiApp.language);

    Row_s *p_footer = gui_addFooterButtonRow(p_view);
    gui_addFooterButton(p_footer, FILE_KEY_ICON_BTN_ARROW_BACK, settings_view_navigateTo);
    gui_addFooterSpacer(p_footer);
    gui_addFooterSpacer(p_footer);

    view_addComponent(p_view, p_radioGroup);
}

static void lv_rgSelectionChanged(RadioGroup_s *p_radioGroup)
{
    g_guiApp.language = radiogroup_getSelectedIndex(p_radioGroup);
    header_setTitle(FILE_KEY_TITLE_LANGUAGE);
}
