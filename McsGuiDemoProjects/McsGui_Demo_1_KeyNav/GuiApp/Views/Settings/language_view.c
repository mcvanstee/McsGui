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

    Column_s *p_columnLeft = column_newInit();
    column_setSpacing(p_columnLeft, 3);
    base_addNewInitAnchor(p_columnLeft);
    anchor_setLeftAnchor(p_columnLeft, p_pane, Gui_Anchor_Left);
    anchor_setTopAnchor(p_columnLeft, p_pane, Gui_Anchor_Top);
    anchor_setLeftMargin(p_columnLeft, 10);
    anchor_setTopMargin(p_columnLeft, 15);
    view_addComponent(p_view, p_columnLeft);

    Column_s *p_columnRight = column_newInit();
    column_setSpacing(p_columnRight, 3);
    base_addNewInitAnchor(p_columnRight);
    anchor_setLeftAnchor(p_columnRight, p_columnLeft, Gui_Anchor_Right);
    anchor_setTopAnchor(p_columnRight, p_columnLeft, Gui_Anchor_Top);
    anchor_setLeftMargin(p_columnRight, 50);
    view_addComponent(p_view, p_columnRight);

    RadioGroup_s *p_radioGroup = radiogroup_newInit();
    radiogroup_setOnSelectionChanged(p_radioGroup, lv_rgSelectionChanged);

    CheckboxLabel_s *p_englishCheckBox = gui_addCheckboxLabel(p_columnLeft, p_radioGroup, FILE_KEY_TEXT_PANE_ENGLISH);
    CheckboxLabel_s *p_dutchCheckBox = gui_addCheckboxLabel(p_columnLeft, p_radioGroup, FILE_KEY_TEXT_PANE_DUTCH);
    CheckboxLabel_s *p_germanCheckBox = gui_addCheckboxLabel(p_columnLeft, p_radioGroup, FILE_KEY_TEXT_PANE_GERMAN);
    CheckboxLabel_s *p_frenchCheckBox = gui_addCheckboxLabel(p_columnLeft, p_radioGroup, FILE_KEY_TEXT_PANE_FRENCH);
    CheckboxLabel_s *p_spanishCheckBox = gui_addCheckboxLabel(p_columnLeft, p_radioGroup, FILE_KEY_TEXT_PANE_SPANISH);

    CheckboxLabel_s *p_italianCheckBox = gui_addCheckboxLabel(p_columnRight, p_radioGroup, FILE_KEY_TEXT_PANE_ITALIAN);
    CheckboxLabel_s *p_russianCheckBox = gui_addCheckboxLabel(p_columnRight, p_radioGroup, FILE_KEY_TEXT_PANE_RUSSIAN);
    CheckboxLabel_s *p_chineseCheckBox = gui_addCheckboxLabel(p_columnRight, p_radioGroup, FILE_KEY_TEXT_PANE_CHINESE_SIM);
    CheckboxLabel_s *p_japaneseCheckBox = gui_addCheckboxLabel(p_columnRight, p_radioGroup, FILE_KEY_TEXT_PANE_JAPANESE);
    CheckboxLabel_s *p_koreanCheckBox = gui_addCheckboxLabel(p_columnRight, p_radioGroup, FILE_KEY_TEXT_PANE_KOREAN);

    radiogroup_setSelectedAtIndex(p_radioGroup, g_guiApp.language);

    Row_s *p_footer = gui_addFooterButtonRow(p_view);
    FooterButton_s *p_footerBackButton = gui_addFooterButton(p_footer, FILE_KEY_ICON_BUTTON_ARROW_BACK, settings_view_navigateTo);
    gui_addFooterSpacer(p_footer);
    gui_addFooterSpacer(p_footer);
    base_setFocus(p_footerBackButton, true);

    keynav_connectLeftRight(p_englishCheckBox, p_italianCheckBox);
    keynav_connectLeftRight(p_dutchCheckBox, p_russianCheckBox);
    keynav_connectLeftRight(p_germanCheckBox, p_chineseCheckBox);
    keynav_connectLeftRight(p_frenchCheckBox, p_japaneseCheckBox);
    keynav_connectLeftRight(p_spanishCheckBox, p_koreanCheckBox);

    keynav_connectUpDown(p_englishCheckBox, p_dutchCheckBox);
    keynav_connectUpDown(p_dutchCheckBox, p_germanCheckBox);
    keynav_connectUpDown(p_germanCheckBox, p_frenchCheckBox);
    keynav_connectUpDown(p_frenchCheckBox, p_spanishCheckBox);
    keynav_connectUpDown(p_spanishCheckBox, p_footerBackButton);

    keynav_connectUpDown(p_italianCheckBox, p_russianCheckBox);
    keynav_connectUpDown(p_russianCheckBox, p_chineseCheckBox);
    keynav_connectUpDown(p_chineseCheckBox, p_japaneseCheckBox);
    keynav_connectUpDown(p_japaneseCheckBox, p_koreanCheckBox);
    keynav_down(p_koreanCheckBox, p_footerBackButton);

    view_addComponent(p_view, p_radioGroup);
}

static void lv_rgSelectionChanged(RadioGroup_s *p_radioGroup)
{
    g_guiApp.language = radiogroup_getSelectedIndex(p_radioGroup);
    header_setTitle(FILE_KEY_TITLE_LANGUAGE);
}
