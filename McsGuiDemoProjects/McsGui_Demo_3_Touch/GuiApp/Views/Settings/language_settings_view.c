#include "language_settings_view.h"

#include "gui_app.h"
#include "gui_settings.h"
#include "gui_custom_components.h"

#include "settings_view.h"


#define GROUP_BOX_LARGE_WIDTH 416
#define GROUP_BOX_HEIGHT 240

#define LSV_LANGUAGE_GROUP_BOX_ID 1


static void lsv_create(View_s *p_view);
static void lsv_addLanguageContent(GroupBox_s *p_languageGB);
static void lsv_languageChanged(RadioGroup_s *p_radioGroup);
static CheckboxLabel_s *sv_addCheckboxLabel(
        Column_s *p_column, RadioGroup_s *p_radioGroup, const file_key_e text);
static void lsv_navigateBack(void);


void language_settings_view_navigateTo(void)
{
    view_navigateTo(gui_app_getView(), lsv_create);
}

static void lsv_create(View_s *p_view)
{
    gui_app_clearView();

    Item_s *p_item = item_newInit();
    base_setPosition(p_item, STYLE_VIEW_X, STYLE_VIEW_Y);
    base_setDimensions(p_item, STYLE_VIEW_WIDTH, STYLE_DISPLAY_HEIGHT);
    view_addComponent(p_view, p_item);

    GroupBox_s *p_languageGB = group_box_newInitTitleSize(
            FILE_KEY_TITLE_LANGUAGE, GROUP_BOX_LARGE_WIDTH, GROUP_BOX_HEIGHT);
    base_addNewInitAnchor(p_languageGB);
    base_setId(p_languageGB, LSV_LANGUAGE_GROUP_BOX_ID);
    anchor_setTopAnchor(p_languageGB, p_item, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_languageGB, p_item, Gui_Anchor_Left);
    anchor_setTopMargin(p_languageGB, 20);
    anchor_setLeftMargin(p_languageGB, 10);
    lsv_addLanguageContent(p_languageGB);
    view_addComponent(p_view, p_languageGB);

    Button_s *p_backButton = button_new();
    button_initBmp(p_backButton, FILE_KEY_ICON_BACK);
    button_setOnReleasedEvent(p_backButton, lsv_navigateBack);
    base_addNewInitTouch(p_backButton);
    base_setDimensions(p_backButton, 50, 50);
    base_addNewInitAnchor(p_backButton);
    anchor_setBottomAnchor(p_backButton, p_item, Gui_Anchor_Bottom);
    anchor_setRightAnchor(p_backButton, p_item, Gui_Anchor_Right);
    anchor_setBottomMargin(p_backButton, 5);
    anchor_setRightMargin(p_backButton, 10);
    view_addComponent(p_view, p_backButton);
}

static void lsv_addLanguageContent(GroupBox_s *p_languageGB)
{
    Column_s *p_columnLeft = column_newInit();
    column_setSpacing(p_columnLeft, 4);
    base_addNewInitAnchor(p_columnLeft);
    anchor_setLeftAnchor(p_columnLeft, p_languageGB, Gui_Anchor_Left);
    anchor_setTopAnchor(p_columnLeft, p_languageGB, Gui_Anchor_Top);
    anchor_setLeftMargin(p_columnLeft, 10);
    anchor_setTopMargin(p_columnLeft, 16);
    group_box_addComponent(p_languageGB, p_columnLeft);

    Column_s *p_columnRight = column_newInit();
    column_setSpacing(p_columnRight, 4);
    base_addNewInitAnchor(p_columnRight);
    anchor_setLeftAnchor(p_columnRight, p_columnLeft, Gui_Anchor_Right);
    anchor_setTopAnchor(p_columnRight, p_columnLeft, Gui_Anchor_Top);
    group_box_addComponent(p_languageGB, p_columnRight);

    RadioGroup_s *p_radioGroup = radiogroup_newInit();
    radiogroup_setOnSelectionChanged(p_radioGroup, lsv_languageChanged);
    group_box_addComponent(p_languageGB, p_radioGroup);

    sv_addCheckboxLabel(p_columnLeft, p_radioGroup, FILE_KEY_TEXT_ENGLISH);
    sv_addCheckboxLabel(p_columnLeft, p_radioGroup, FILE_KEY_TEXT_DUTCH);
    sv_addCheckboxLabel(p_columnLeft, p_radioGroup, FILE_KEY_TEXT_GERMAN);
    sv_addCheckboxLabel(p_columnLeft, p_radioGroup, FILE_KEY_TEXT_FRENCH);
    sv_addCheckboxLabel(p_columnLeft, p_radioGroup, FILE_KEY_TEXT_SPANISH);
    sv_addCheckboxLabel(p_columnLeft, p_radioGroup, FILE_KEY_TEXT_ITALIAN);
    sv_addCheckboxLabel(p_columnRight, p_radioGroup, FILE_KEY_TEXT_RUSSIAN);
    sv_addCheckboxLabel(p_columnRight, p_radioGroup, FILE_KEY_TEXT_CHINESE_SIM);
    sv_addCheckboxLabel(p_columnRight, p_radioGroup, FILE_KEY_TEXT_JAPANESE);
    sv_addCheckboxLabel(p_columnRight, p_radioGroup, FILE_KEY_TEXT_KOREAN);
    radiogroup_setSelectedAtIndex(p_radioGroup, (int8_t)settings_getLanguage());
}

static CheckboxLabel_s *sv_addCheckboxLabel(
        Column_s *p_column, RadioGroup_s *p_radioGroup, const file_key_e text)
{
    CheckboxLabel_s *p_checkboxLabel = checkbox_label_new();
    checkbox_label_init_1(p_checkboxLabel, text);
    column_addComponent(p_column, p_checkboxLabel);
    radiogroup_addButton(p_radioGroup, &p_checkboxLabel->checkBox);

    return p_checkboxLabel;
}

static void lsv_languageChanged(RadioGroup_s *p_radioGroup)
{
    settings_setLanguage((Language_e)radiogroup_getSelectedIndex(p_radioGroup));
    GroupBox_s *p_languageGB = (GroupBox_s *)view_getComponentById(gui_app_getView(), LSV_LANGUAGE_GROUP_BOX_ID);

    Rectangle_s background;
    rectangle_initFillPosSize(
        &background, COLOR_BACKGROUND,
        p_languageGB->rect.base.x + 5, p_languageGB->rect.base.y - 10,
        120, 20);

    base_display(&background);
    base_display(p_languageGB);
}

static void lsv_navigateBack(void)
{
    settings_save();
    settings_view_navigateTo();
}
