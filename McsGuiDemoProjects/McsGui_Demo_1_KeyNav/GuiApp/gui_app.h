#ifndef GUI_APP_H_
#define GUI_APP_H_

#include "gui_header.h"
#include "gui_theme.h"
#include "Utils/gui_log.h"


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

typedef enum
{
    TemperatureUnit_Celsius = 0,
    TemperatureUnit_Fahrenheit,
} TemperatureUnit_e;

#define CUSTOM_GUI_EVENT_MEASUREMENT_READY 100

typedef struct
{
    Language_e language;
    GuiTheme_s theme;
    TemperatureUnit_e temperatureUnit;
    bool updateDateTime;
    bool alarmActive;
    uint8_t alarmTime_mm;
    uint32_t alarmTime_ms;
    uint8_t displayBrightness;
    View_s view;
} GuiApplication_s;

extern GuiApplication_s g_guiApp;

void gui_app_start(void);
void gui_showFooterLogo(void);
void gui_drawBackground(void);
void gui_drawHeaderBackground(void);
void gui_drawFooterBackground(void);
void gui_clearView(void);
void gui_translate(void *p_component);
void gui_app_setAlarmTime(const uint8_t alarmTime_mm);
void gui_app_activateAlarm(void);

#endif /* GUI_APP_H_ */
