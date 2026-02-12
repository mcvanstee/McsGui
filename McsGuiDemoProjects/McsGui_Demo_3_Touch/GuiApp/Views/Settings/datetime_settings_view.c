#include "datetime_settings_view.h"

#include "gui_app.h"
#include "gui_settings.h"
#include "gui_custom_components.h"

#include "settings_view.h"


#define GROUP_BOX_WIDTH 416
#define GROUP_BOX_HEIGHT 240


static void dsv_create(View_s *p_view);
static void dsv_addDateTimeContent(GroupBox_s *p_dateTimeGB);
static CheckboxLabel_s *dsv_addSwitchLabel(Column_s *p_column, const file_key_e text);
static void dsv_timeSwitchChanged(CheckboxLabel_s *p_checkboxLabel);
static void dsv_dateSwitchChanged(CheckboxLabel_s *p_checkboxLabel);
static void dsv_navigateBack(void);


void datetime_settings_view_navigateTo(void)
{
    view_navigateTo(gui_app_getView(), dsv_create);
}

static void dsv_create(View_s *p_view)
{
    gui_app_clearView();

    Item_s *p_item = item_newInit();
    base_setPosition(p_item, STYLE_VIEW_X, STYLE_VIEW_Y);
    base_setDimensions(p_item, STYLE_VIEW_WIDTH, STYLE_DISPLAY_HEIGHT);
    view_addComponent(p_view, p_item);

    GroupBox_s *p_dateTimeGB = group_box_newInitTitleSize(FILE_KEY_TITLE_DATE_TIME, GROUP_BOX_WIDTH, GROUP_BOX_HEIGHT);
    base_addNewInitAnchor(p_dateTimeGB);
    anchor_setTopAnchor(p_dateTimeGB, p_item, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_dateTimeGB, p_item, Gui_Anchor_Left);
    anchor_setTopMargin(p_dateTimeGB, 20);
    anchor_setLeftMargin(p_dateTimeGB, 10);
    view_addComponent(p_view, p_dateTimeGB);

    dsv_addDateTimeContent(p_dateTimeGB);

    Button_s *p_backButton = button_new();
    button_initBmp(p_backButton, FILE_KEY_ICON_BACK);
    button_setOnReleasedEvent(p_backButton, dsv_navigateBack);
    base_addNewInitTouch(p_backButton);
    base_setDimensions(p_backButton, 50, 50);
    base_addNewInitAnchor(p_backButton);
    anchor_setBottomAnchor(p_backButton, p_item, Gui_Anchor_Bottom);
    anchor_setRightAnchor(p_backButton, p_item, Gui_Anchor_Right);
    anchor_setBottomMargin(p_backButton, 5);
    anchor_setRightMargin(p_backButton, 10);
    view_addComponent(p_view, p_backButton);
}

static void dsv_addDateTimeContent(GroupBox_s *p_dateTimeGB)
{
    Column_s *p_column = column_newInit();
    column_setSpacing(p_column, 6);
    base_addNewInitAnchor(p_column);
    anchor_setLeftAnchor(p_column, p_dateTimeGB, Gui_Anchor_Left);
    anchor_setTopAnchor(p_column, p_dateTimeGB, Gui_Anchor_Top);
    anchor_setLeftMargin(p_column, 10);
    anchor_setTopMargin(p_column, 16);
    group_box_addComponent(p_dateTimeGB, p_column);

    const file_key_e labelTime = settings_getShowTime() ? FILE_KEY_TEXT_SHOW_TIME : FILE_KEY_TEXT_HIDE_TIME;
    const file_key_e labelDate = settings_getShowDate() ? FILE_KEY_TEXT_SHOW_DATE : FILE_KEY_TEXT_HIDE_DATE;

    CheckboxLabel_s *p_timeSwitch = dsv_addSwitchLabel(p_column, labelTime);
    CheckboxLabel_s *p_dateSwitch = dsv_addSwitchLabel(p_column, labelDate);
    p_timeSwitch->labelWidth = 120;
    p_dateSwitch->labelWidth = 120;
    checkbox_setSelection(&p_timeSwitch->checkBox, settings_getShowTime());
    checkbox_setSelection(&p_dateSwitch->checkBox, settings_getShowDate());
    checkbox_label_setOnSelectionChanged(p_timeSwitch, dsv_timeSwitchChanged);
    checkbox_label_setOnSelectionChanged(p_dateSwitch, dsv_dateSwitchChanged);
}

static CheckboxLabel_s *dsv_addSwitchLabel(Column_s *p_column, const file_key_e text)
{
    CheckboxLabel_s *p_checkboxLabel = checkbox_label_new();
    checkbox_label_initSwitch(p_checkboxLabel, text);
    column_addComponent(p_column, p_checkboxLabel);

    return p_checkboxLabel;
}

static void dsv_timeSwitchChanged(CheckboxLabel_s *p_checkboxLabel)
{
    if (p_checkboxLabel->checkBox.checked)
    {
        p_checkboxLabel->label = FILE_KEY_TEXT_SHOW_TIME;
    }
    else
    {
        p_checkboxLabel->label = FILE_KEY_TEXT_HIDE_TIME;
    }

    settings_setShowTime(p_checkboxLabel->checkBox.checked);
    checkbox_label_displayLabel(p_checkboxLabel);
}

static void dsv_dateSwitchChanged(CheckboxLabel_s *p_checkboxLabel)
{
    if (p_checkboxLabel->checkBox.checked)
    {
        p_checkboxLabel->label = FILE_KEY_TEXT_SHOW_DATE;
    }
    else
    {
        p_checkboxLabel->label = FILE_KEY_TEXT_HIDE_DATE;
    }

    settings_setShowDate(p_checkboxLabel->checkBox.checked);
    checkbox_label_displayLabel(p_checkboxLabel);
}

static void dsv_navigateBack(void)
{
    settings_save();
    settings_view_navigateTo();
}
