#ifndef GUI_APP_H_
#define GUI_APP_H_

#include "mcsgui.h"
#include "colors.h"
#include "fonts.h"
#include "fs_file_search.h"
#include "fs_font_search.h"
#include "Utils/gui_log.h"
#include "gui_utils_unit_converter.h"

#include "stm32l4xx_hal.h"

typedef enum
{
    Language_English = 0,
    Language_Dutch,
    Lanugage_German,
    Language_French,
    Language_Spanish,
    Language_Italian,
    Language_Russian,
    Language_Chinese,
    Language_Japanese,
    Language_Korean,
} Language_e;

#define GUI_APP_LOG_MESSAGE_LENGTH 255
#define GUI_APP_LOG_MESSAGE_LENGTH_INC_NULL (GUI_APP_LOG_MESSAGE_LENGTH + 1)
#define CUSTOM_GUI_EVENT_MEASREMANT_READY 101
#define CUSTOM_GUI_EVENT_UPDATE_DATE_TIME 102
#define CUSTOM_GUI_EVENT_REC_NUMBER_CHANGED 103

#define CONTROL_BAR_ID 100

typedef struct
{
    Language_e language;
    TemperatureUnit_e temperatureUnit;
    bool showTime;
    bool showDate;
    uint8_t displayBrightness;
    View_s view;
} GuiApplication_s;

extern GuiApplication_s g_guiApp;

void gui_app_start(void);
void gui_app_clearView(void);
void gui_app_drawBackground(void);
void gui_app_translate(void *p_component);
void gui_app_setVisibiltyControlBar(const bool visible);

uint32_t gui_app_getTimeStamp(void);
uint32_t gui_app_convertTimeStampToSeconds(RTC_TimeTypeDef *p_time, RTC_DateTypeDef *p_date);

#endif /* GUI_APP_H_ */
