#include "set_time_view.h"

#include "gui_app.h"
#include "gui_custom_components.h"

#include "stm32l4xx_hal.h"

#include "settings_view.h"

#define STV_INPUT_HH_1_ID 1
#define STV_INPUT_HH_2_ID 2
#define STV_INPUT_MM_1_ID 3
#define STV_INPUT_MM_2_ID 4


static void stv_create(View_s *p_view);
static void stv_saveTime(void);

extern RTC_HandleTypeDef hrtc;

void set_time_view_navigateTo(void)
{
    view_navigateTo(&g_guiApp.view, stv_create);
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

    uint8_t hh1 = sTime.Hours / 10;
    uint8_t hh2 = sTime.Hours % 10;
    uint8_t mm1 = sTime.Minutes / 10;
    uint8_t mm2 = sTime.Minutes % 10;

    Row_s *p_timeInput = row_newInit();
    row_setSpacing(p_timeInput, 2);
    base_addNewInitAnchor(p_timeInput);
    anchor_setCenterInParent(p_timeInput, p_pane);
    view_addComponent(p_view, p_timeInput);

    DigitInput_s *p_hh1 = digit_input_newInit();
    digit_input_setValue(p_hh1, hh1);
    digit_input_setMaxValue(p_hh1, 2);
    base_setId(p_hh1, STV_INPUT_HH_1_ID);
    row_addComponent(p_timeInput, p_hh1);

    DigitInput_s *p_hh2 = digit_input_newInit();
    digit_input_setValue(p_hh2, hh2);
    base_setId(p_hh2, STV_INPUT_HH_2_ID);
    row_addComponent(p_timeInput, p_hh2);

    TextBlock_s *p_colon = textblock_newInit();
    textblock_setFont(p_colon, theme_getDefaultFont());
    textblock_setText(p_colon, ":");
    row_addComponent(p_timeInput, p_colon);

    DigitInput_s *p_mm1 = digit_input_newInit();
    digit_input_setValue(p_mm1, mm1);
    digit_input_setMaxValue(p_mm1, 5);
    base_setId(p_mm1, STV_INPUT_MM_1_ID);
    row_addComponent(p_timeInput, p_mm1);

    DigitInput_s *p_mm2 = digit_input_newInit();
    digit_input_setValue(p_mm2, mm2);
    base_setId(p_mm2, STV_INPUT_MM_2_ID);
    row_addComponent(p_timeInput, p_mm2);

    Row_s *p_footer = gui_addFooterButtonRow(p_view);
    FooterButton_s *p_backButton = gui_addFooterButton(p_footer,
            FILE_KEY_ICON_BTN_ARROW_BACK, settings_view_navigateTo);
    gui_addFooterSpacer(p_footer);
    FooterButton_s *p_saveButton = gui_addFooterButton(p_footer,
            FILE_KEY_ICON_BTN_CHECKMARK_LARGE, stv_saveTime);
    base_setFocus(p_backButton, true);

    keynav_up(p_backButton, p_hh1);
    keynav_up(p_saveButton, p_mm2);

    keynav_down(p_hh1, p_backButton);
    keynav_down(p_mm2, p_saveButton);

    keynav_left(p_mm2, p_mm2);
    keynav_left(p_mm2, p_hh2);
    keynav_left(p_hh2, p_hh1);

    keynav_right(p_hh1, p_hh2);
    keynav_right(p_hh2, p_mm1);
    keynav_right(p_mm1, p_mm2);

    keynav_right(p_backButton, p_saveButton);
    keynav_left(p_saveButton, p_backButton);
}

static void stv_saveTime(void)
{
    RTC_DateTypeDef sDate = { 0 };
    RTC_TimeTypeDef sTime = { 0 };
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

    DigitInput_s *p_hh1 = (DigitInput_s *)view_getComponentById(&g_guiApp.view, STV_INPUT_HH_1_ID);
    DigitInput_s *p_hh2 = (DigitInput_s *)view_getComponentById(&g_guiApp.view, STV_INPUT_HH_2_ID);
    DigitInput_s *p_mm1 = (DigitInput_s *)view_getComponentById(&g_guiApp.view, STV_INPUT_MM_1_ID);
    DigitInput_s *p_mm2 = (DigitInput_s *)view_getComponentById(&g_guiApp.view, STV_INPUT_MM_2_ID);

    sTime.Hours = p_hh1->value * 10 + p_hh2->value;
    sTime.Minutes = p_mm1->value * 10 + p_mm2->value;

    HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

    header_updateDateTime(true);

    settings_view_navigateTo();
}
