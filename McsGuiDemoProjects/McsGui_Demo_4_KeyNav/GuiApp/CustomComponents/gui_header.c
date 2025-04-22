#include "gui_header.h"

#include <stdio.h>

#include "gui_app.h"

#include "stm32l4xx_hal.h"

extern RTC_HandleTypeDef hrtc;

void header_setTitle(file_key_e title)
{
    Label_s titleLabel;
    label_initBmpPosSizeBack(&titleLabel, title, 85, 1, 150, 38, theme_getHeaderColor());
    base_setTopPadding(&titleLabel, 1);
    theme_setTheme(&titleLabel);
    gui_translate(&titleLabel);

    base_display(&titleLabel);
}

void header_updateTime(const bool update)
{
    g_guiApp.updateDateTime = update;
}

void header_updateDateTime(const bool forceUpdate)
{
    static int32_t lastMinute = -1;
    if (!g_guiApp.updateDateTime)
    {
        lastMinute = -1;

        return;
    }

    RTC_DateTypeDef sDate = { 0 };
    RTC_TimeTypeDef sTime = { 0 };
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

    if (forceUpdate || (lastMinute != (int32_t)sTime.Minutes))
    {
        lastMinute = sTime.Minutes;

        TextBlock_s time;
        textblock_initTextPosSize(&time, "00:00", 36, 9, 100, 24);
        sprintf(time.text, "%02d:%02d", sTime.Hours, sTime.Minutes);
        textblock_setFont(&time, theme_getHeaderFont());
        base_setHorizontalAlignment(&time.base, Gui_Align_Left);
        base_setLeftPadding(&time.base, 2);
        base_display(&time.base);
    }
}

void header_drawHeaderBackground(void)
{
    Rectangle_s background;
    rectangle_initFillPosSize(
        &background, theme_getHeaderColor(),
        STYLE_HEADER_X, STYLE_HEADER_Y, STYLE_DISPLAY_WIDTH, STYLE_HEADER_HEIGHT);
    base_display(&background);

    Rectangle_s separatorTop;
    rectangle_initFillPosSize(
        &separatorTop, theme_getSeparatorColor(),
        STYLE_HEADER_X, SYTLE_HEADER_SEPARATOR_Y, STYLE_DISPLAY_WIDTH, STYLE_HEADER_SEPARATOR_HEIGHT);
    base_display(&separatorTop);

    Label_s clock;
    label_initBmpPosSize(
        &clock, FILE_KEY_ICON_CLOCK,
        STYLE_HEADER_X, STYLE_HEADER_Y, STYLE_HEADER_ICON_WIDTH, STYLE_HEADER_ICON_HEIGHT);
    theme_setTheme(&clock.base);
    base_display(&clock.base);

    Label_s wifi;
    label_initBmpPosSize(
        &wifi, FILE_KEY_ICON_WIFI,
        (STYLE_DISPLAY_WIDTH - STYLE_HEADER_ICON_WIDTH), STYLE_HEADER_Y, STYLE_HEADER_ICON_HEIGHT, STYLE_HEADER_HEIGHT);
    theme_setTheme(&wifi.base);
    base_display(&wifi.base);

    header_updateDateTime(true);
}
