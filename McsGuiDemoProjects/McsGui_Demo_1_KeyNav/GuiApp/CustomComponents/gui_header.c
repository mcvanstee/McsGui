#include "gui_header.h"

#include <stdio.h>

#include "gui_app.h"

#include "stm32l4xx_hal.h"

extern RTC_HandleTypeDef hrtc;

void header_setTitle(file_key_e title)
{
    Label_s titleLabel;
    label_initBmpPosSizeBack(&titleLabel, title, 120, 0, 240, 40, theme_getHeaderColor());
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

    if (!forceUpdate && (lastMinute == (int32_t)sTime.Minutes))
    {
        return;
    }

    lastMinute = sTime.Minutes;

    TextBlock_s time;
    textblock_initTextPosSize(&time, "00:00", 37, 8, 100, 24);
    sprintf(time.text, "%02d:%02d", sTime.Hours, sTime.Minutes);

    textblock_setFont(&time, theme_getHeaderFontSmall());
    base_setHorizontalAlignment(&time.base, Gui_Align_Left);
    base_setLeftPadding(&time.base, 2);
    base_display(&time.base);

    return;
}

void header_showAlarm(const bool showAlarm)
{
    if (showAlarm)
    {
        Label_s alarmLabel;
        label_initBmpPosSize(&alarmLabel, FILE_KEY_ICON_HEADER_BELL, STYLE_DISPLAY_WIDTH - 70, 0, 40, 40);
        theme_setTheme(&alarmLabel);
        base_display(&alarmLabel);
    }
    else
    {
        Rectangle_s rect;
        rectangle_initFillPosSize(&rect, theme_getHeaderColor(), STYLE_DISPLAY_WIDTH - 70, 0, 30, 40);
        base_display(&rect);
    }
}
