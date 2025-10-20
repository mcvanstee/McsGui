#ifndef GUI_APP_H_
#define GUI_APP_H_

#include "gui_header.h"
#include "gui_theme.h"
#include "Core/gui_log.h"


#define GUI_APP_LOG_MESSAGE_LENGTH 255
#define GUI_APP_LOG_MESSAGE_LENGTH_INC_NULL (GUI_APP_LOG_MESSAGE_LENGTH + 1)
#define CUSTOM_GUI_EVENT_MEASUREMENT_READY 100

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

typedef struct
{
    Language_e language;
    GuiThemeSetting_s themeSetting;
    TemperatureUnit_e temperatureUnit;
    bool updateDateTime;
    bool alarmActive;
    uint8_t alarmTime_mm;
    uint32_t alarmTime_ms;
    uint8_t displayBrightness;
    View_s view;
} GuiApplication_s;


void gui_app_start(void);
void gui_app_showFooterLogo(void);
void gui_app_drawBackground(void);
void gui_app_drawHeaderBackground(void);
void gui_app_drawFooterBackground(void);
void gui_app_clearView(void);
void gui_app_translate(void *p_component);
void gui_app_setAlarmTime(const uint8_t alarmTime_mm);
void gui_app_activateAlarm(void);
bool gui_app_updateDateTime(void);

View_s* gui_app_getView(void);
Language_e gui_app_getLanguage(void);
TemperatureUnit_e gui_app_getTemperatureUnit(void);
uint8_t gui_app_getDisplayBrightness(void);

void gui_app_setLanguage(const Language_e language);
void gui_app_setTemperatureUnit(const TemperatureUnit_e temperatureUnit);
void gui_app_setUpdateDateTime(const bool update);
void gui_app_setDisplayBrightness(const uint8_t brightness);


#endif /* GUI_APP_H_ */
