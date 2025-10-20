#include "set_time_view.h"

#include "gui_app.h"
#include "gui_custom_components.h"

#include "stm32l4xx_hal.h"

#include "settings_view.h"

#define STV_INPUT_HH_ID 1
#define STV_INPUT_MM_ID 2

static void stv_create(View_s *p_view);
static void stv_saveTime(void);

extern RTC_HandleTypeDef hrtc;

void set_time_view_navigateTo(void)
{
    view_navigateTo(gui_app_getView(), stv_create);
}

static void stv_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_TIME);

    Pane_s *p_pane = pane_newInit();
    view_addComponent(p_view, p_pane);

    RTC_DateTypeDef sDate = { 0 };
    RTC_TimeTypeDef sTime = { 0 };
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

    Row_s *p_timeInput = row_newInit();
    row_setSpacing(p_timeInput, 5);
    base_addNewInitAnchor(p_timeInput);
    anchor_setCenterInParent(p_timeInput, p_pane);
    view_addComponent(p_view, p_timeInput);

    SpinnerInput_s *p_hh = spinner_input_new();
    spinner_input_initValues(p_hh, sTime.Hours, 0, 23);
    spinner_input_setLeadingZeros(p_hh, 2);
    base_setId(p_hh, STV_INPUT_HH_ID);
    row_addComponent(p_timeInput, p_hh);

    TextBlock_s *p_colon = textblock_newInit();
    textblock_setFont(p_colon, FONT_KEY_ROBOTO_22_R);
    theme_setPaneTextBlock(p_colon);
    textblock_setText(p_colon, ":");
    row_addComponent(p_timeInput, p_colon);

    SpinnerInput_s *p_mm = spinner_input_new();
    spinner_input_initValues(p_mm, sTime.Minutes, 0, 59);
    spinner_input_setLeadingZeros(p_mm, 2);
    base_setId(p_mm, STV_INPUT_MM_ID);
    row_addComponent(p_timeInput, p_mm);

    Row_s *p_footer = gui_addFooterButtonRow(p_view);
    FooterButton_s *p_backButton = gui_addFooterButton(
            p_footer, FILE_KEY_ICON_ARROW_BACK, settings_view_navigateTo);
    gui_addFooterSpacer(p_footer);
    FooterButton_s *p_saveButton = gui_addFooterButton(
            p_footer, FILE_KEY_ICON_CHECKMARK_LARGE, stv_saveTime);
    base_setFocus(p_backButton, true);

    keynav_up(p_backButton, p_hh);
    keynav_up(p_saveButton, p_mm);

    keynav_down(p_hh, p_backButton);
    keynav_down(p_mm, p_saveButton);

    keynav_connectLeftRight(p_hh, p_mm);
    keynav_connectLeftRight(p_backButton, p_saveButton);
}

static void stv_saveTime(void)
{
    View_s *p_view = gui_app_getView();

    SpinnerInput_s *p_hh = (SpinnerInput_s*) view_getComponentById(p_view, STV_INPUT_HH_ID);
    SpinnerInput_s *p_mm = (SpinnerInput_s*) view_getComponentById(p_view, STV_INPUT_MM_ID);

    RTC_DateTypeDef sDate = { 0 };
    RTC_TimeTypeDef sTime = { 0 };
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

    sTime.Hours = spinner_input_getValue(p_hh);
    sTime.Minutes = spinner_input_getValue(p_mm);

    HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

    header_updateDateTime(true);

    settings_view_navigateTo();
}
