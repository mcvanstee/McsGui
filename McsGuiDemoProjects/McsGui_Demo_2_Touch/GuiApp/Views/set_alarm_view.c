#include "set_alarm_view.h"

#include "gui_app.h"
#include "gui_custom_components.h"

#include "main_view.h"
#include "confirm_dialog.h"

#define SAV_INPUT_ID 1

static void set_alarm_view_create(View_s *p_view);
static void sav_saveAlarm(void);
static void sav_activateAlarm(void);

void set_alarm_view_navigateTo(void)
{
    view_navigateTo(&g_guiApp.view, set_alarm_view_create);
}

static void set_alarm_view_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_ALARM);

    Pane_s *p_pane = pane_newInit();
    view_addComponent(p_view, p_pane);

    NumberInput_s *p_numberInput = num_input_newInit();
    num_input_setValue(p_numberInput, 1);
    num_input_setMinimumValue(p_numberInput, 1);
    num_input_setMaximumValue(p_numberInput, 60);
    base_setId(p_numberInput, SAV_INPUT_ID);
    base_addNewInitAnchor(p_numberInput);
    anchor_setCenterInParent(p_numberInput, p_pane);

    Label_s *p_alarmText = label_new();
    label_initBmp(p_alarmText, FILE_KEY_TEXT_PANE_SET_ALARM_IN);
    theme_setTheme(p_alarmText);
    base_addNewInitAnchor(p_alarmText);
    anchor_setRightAnchor(p_alarmText, p_numberInput, Gui_Anchor_Left);
    anchor_setRightMargin(p_alarmText, 10);
    anchor_setVerticalCenter(p_alarmText, p_numberInput);

    Label_s *p_minutesText = label_new();
    label_initBmp(p_minutesText, FILE_KEY_TEXT_PANE_TIME_MM);
    theme_setTheme(p_minutesText);
    base_addNewInitAnchor(p_minutesText);
    anchor_setLeftAnchor(p_minutesText, p_numberInput, Gui_Anchor_Right);
    anchor_setLeftMargin(p_minutesText, 10);
    anchor_setVerticalCenter(p_minutesText, p_numberInput);

    view_addComponent(p_view, p_numberInput);
    view_addComponent(p_view, p_alarmText);
    view_addComponent(p_view, p_minutesText);

    Row_s *p_footer = gui_addFooterButtonRow(p_view);
    gui_addFooterButton(p_footer, FILE_KEY_ICON_BUTTON_ARROW_BACK, mainview_navigateTo);
    gui_addFooterSpacer(p_footer);
    gui_addFooterButton(p_footer, FILE_KEY_ICON_BUTTON_CHECKMARK_LARGE, sav_saveAlarm);
}

static void sav_saveAlarm(void)
{
    NumberInput_s *p_numberInput = (NumberInput_s*)view_getComponentById(&g_guiApp.view, SAV_INPUT_ID);
    gui_app_setAlarmTime(p_numberInput->value);
    confirm_dialog_show(FILE_KEY_TITLE_ALARM, FILE_KEY_TEXT_PANE_ACTIVATE_ALARM, sav_activateAlarm, mainview_navigateTo);
}

static void sav_activateAlarm(void)
{
    gui_app_activateAlarm();
    mainview_navigateTo();
}
