#include "set_date_view.h"

#include "gui_app.h"
#include "gui_custom_components.h"

#include "stm32l4xx_hal.h"

#include "settings_view.h"

#define STV_INPUT_DATE_ID 1
#define STV_INPUT_MONTH_ID 2
#define STV_INPUT_YEAR_ID 3

static void stv_create(View_s *p_view);
static void stv_saveDate(void);

extern RTC_HandleTypeDef hrtc;

void set_date_view_navigateTo(void)
{
    view_navigateTo(gui_app_getView(), stv_create);
}

static void stv_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_DATE);

    Pane_s *p_pane = pane_newInit();
    view_addComponent(p_view, p_pane);

    RTC_DateTypeDef sDate = { 0 };
    RTC_TimeTypeDef sTime = { 0 };
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

    Row_s *p_row = row_newInit();
    row_setSpacing(p_row, 5);
    base_addNewInitAnchor(p_row);
    anchor_setCenterInParent(p_row, p_pane);
    view_addComponent(p_view, p_row);

    SpinnerInput_s *p_dateInput = spinner_input_new();
    spinner_input_initValues(p_dateInput, sDate.Date, 1, 31);
    spinner_input_setLeadingZeros(p_dateInput, 2);
    base_setId(p_dateInput, STV_INPUT_DATE_ID);
    row_addComponent(p_row, p_dateInput);

    TextBlock_s *p_dateSeparator_1 = textblock_newInit();
    textblock_setText(p_dateSeparator_1, "-");
    textblock_setFontAndColor(p_dateSeparator_1, FONT_KEY_ROBOTO_22_R, theme_getPaneTextColor(), theme_getPaneColor());
    row_addComponent(p_row, p_dateSeparator_1);

    SpinnerInput_s *p_monthInput = spinner_input_new();
    spinner_input_initValues(p_monthInput, sDate.Month, 1, 12);
    spinner_input_setLeadingZeros(p_monthInput, 2);
    base_setId(p_monthInput, STV_INPUT_MONTH_ID);
    row_addComponent(p_row, p_monthInput);

    TextBlock_s *p_dateSeparator_2 = textblock_newInit();
    textblock_setText(p_dateSeparator_2, "-");
    textblock_setFontAndColor(p_dateSeparator_2, FONT_KEY_ROBOTO_22_R, theme_getPaneTextColor(), theme_getPaneColor());
    row_addComponent(p_row, p_dateSeparator_2);

    SpinnerInput_s *p_yearInput = spinner_input_new();
    spinner_input_initValues(p_yearInput, sDate.Year + 2000, 2025, 2099);
    base_setId(p_yearInput, STV_INPUT_YEAR_ID);
    row_addComponent(p_row, p_yearInput);

    Row_s *p_footer = gui_addFooterButtonRow(p_view);
    FooterButton_s *p_backButton = gui_addFooterButton(
            p_footer, FILE_KEY_ICON_ARROW_BACK, settings_view_navigateTo);
    gui_addFooterSpacer(p_footer);
    FooterButton_s *p_saveButton = gui_addFooterButton(
            p_footer, FILE_KEY_ICON_CHECKMARK_LARGE, stv_saveDate);
    base_setFocus(p_backButton, true);

    keynav_up(p_backButton, p_dateInput);
    keynav_up(p_saveButton, p_yearInput);

    keynav_down(p_dateInput, p_backButton);
    keynav_down(p_yearInput, p_saveButton);

    keynav_connectLeftRight(p_dateInput, p_monthInput);
    keynav_connectLeftRight(p_monthInput, p_yearInput);

    keynav_connectLeftRight(p_backButton, p_saveButton);
}

static void stv_saveDate(void)
{
    View_s *p_view = gui_app_getView();

    SpinnerInput_s *p_dateInput = (SpinnerInput_s*) view_getComponentById(p_view, STV_INPUT_DATE_ID);
    SpinnerInput_s *p_monthInput = (SpinnerInput_s*) view_getComponentById(p_view, STV_INPUT_MONTH_ID);
    SpinnerInput_s *p_yearInput = (SpinnerInput_s*) view_getComponentById(p_view, STV_INPUT_YEAR_ID);

    RTC_DateTypeDef sDate = { 0 };
    RTC_TimeTypeDef sTime = { 0 };
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

    sDate.Date = spinner_input_getValue(p_dateInput);
    sDate.Month = spinner_input_getValue(p_monthInput);
    sDate.Year = spinner_input_getValue(p_yearInput) - 2000;

    HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

    header_updateDateTime(true);

    settings_view_navigateTo();
}
