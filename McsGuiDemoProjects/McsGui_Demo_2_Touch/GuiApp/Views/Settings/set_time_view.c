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

    Row_s *p_timeInput = row_newInit();
    row_setSpacing(p_timeInput, 2);
    base_addNewInitAnchor(p_timeInput);
    anchor_setCenterInParent(p_timeInput, p_pane);
    view_addComponent(p_view, p_timeInput);

    NumberInput_s *p_hhInput = num_input_newInit();
    num_input_setValue(p_hhInput, sTime.Hours);
    num_input_setMinimumValue(p_hhInput, 0);
    num_input_setMaximumValue(p_hhInput, 23);
    num_input_setOrientation(p_hhInput, NumberInput_Orientation_Vertical);
    base_setId(p_hhInput, STV_INPUT_HH_ID);
    row_addComponent(p_timeInput, p_hhInput);

    TextBlock_s *p_colon = textblock_newInit();
    textblock_setFont(p_colon, theme_getDefaultFont());
    textblock_setText(p_colon, ":");
    row_addComponent(p_timeInput, p_colon);

    NumberInput_s *p_mmInput = num_input_newInit();
    num_input_setValue(p_mmInput, sTime.Minutes);
    num_input_setMinimumValue(p_mmInput, 0);
    num_input_setMaximumValue(p_mmInput, 59);
    num_input_setOrientation(p_mmInput, NumberInput_Orientation_Vertical);
    base_setId(p_mmInput, STV_INPUT_MM_ID);
    row_addComponent(p_timeInput, p_mmInput);

    Row_s *p_footer = gui_addFooterButtonRow(p_view);
    gui_addFooterButton(p_footer, FILE_KEY_ICON_BTN_ARROW_BACK, settings_view_navigateTo);
    gui_addFooterSpacer(p_footer);
    gui_addFooterButton(p_footer, FILE_KEY_ICON_BTN_CHECKMARK_LARGE, stv_saveTime);
}

static void stv_saveTime(void)
{
    RTC_DateTypeDef sDate = { 0 };
    RTC_TimeTypeDef sTime = { 0 };
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

    NumberInput_s *p_hh = (NumberInput_s *)view_getComponentById(&g_guiApp.view, STV_INPUT_HH_ID);
    NumberInput_s *p_mm = (NumberInput_s *)view_getComponentById(&g_guiApp.view, STV_INPUT_MM_ID);

    sTime.Hours = p_hh->value;
    sTime.Minutes = p_mm->value;

    HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

    header_updateDateTime(true);

    settings_view_navigateTo();
}
