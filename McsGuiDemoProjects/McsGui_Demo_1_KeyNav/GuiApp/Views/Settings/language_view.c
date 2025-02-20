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

    CheckboxLabel_s *p_englishCheckBox = gui_addCheckboxLabel(p_column, p_radioGroup, FILE_KEY_TEXT_DFT_ENGLISH);
    CheckboxLabel_s *p_dutchCheckBox = gui_addCheckboxLabel(p_column, p_radioGroup, FILE_KEY_TEXT_DFT_DUTCH);
    CheckboxLabel_s *p_germanCheckBox = gui_addCheckboxLabel(p_column, p_radioGroup, FILE_KEY_TEXT_DFT_GERMAN);
    radiogroup_setSelectedAtIndex(p_radioGroup, g_guiApp.language);

    Row_s *p_footer = gui_addFooterButtonRow(p_view);
    FooterButton_s *p_footerBackButton = gui_addFooterButton(p_footer, FILE_KEY_ICON_BTN_ARROW_BACK, settings_view_navigateTo);
    gui_addFooterSpacer(p_footer);
    gui_addFooterSpacer(p_footer);
    base_setFocus(p_footerBackButton, true);

    keynav_down(p_englishCheckBox, p_dutchCheckBox);
    keynav_down(p_dutchCheckBox, p_germanCheckBox);
    keynav_down(p_germanCheckBox, p_footerBackButton);

    keynav_up(p_footerBackButton, p_germanCheckBox);
    keynav_up(p_germanCheckBox, p_dutchCheckBox);
    keynav_up(p_dutchCheckBox, p_englishCheckBox);

    view_addComponent(p_view, p_radioGroup);

    //gui_showLogo();
}

static void lv_rgSelectionChanged(RadioGroup_s *p_radioGroup)
{
    g_guiApp.language = radiogroup_getSelectedIndex(p_radioGroup);
    header_setTitle(FILE_KEY_TITLE_LANGUAGE);
}
