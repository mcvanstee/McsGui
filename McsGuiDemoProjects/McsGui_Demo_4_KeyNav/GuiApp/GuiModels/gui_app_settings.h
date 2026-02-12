#ifndef GUIMODELS_GUI_APP_SETTINGS_H_
#define GUIMODELS_GUI_APP_SETTINGS_H_

#include <stdint.h>
#include <stdbool.h>

#include "gui_theme.h"
#include "gui_measurement_setup.h"

#define DISPLAY_DEFAULT_BRIGTHNESS 100

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
    TemperatureUnit_e temperatureUnit;
    uint8_t displayBrightness;
    GuiThemeSettings_s themeSettings;
    GuiMeasurementSetup_s measurementSetup;
} GuiAppSettings_s;


void settings_load(void);
void settings_save(void);

GuiAppSettings_s settings_getSettings(void);
Language_e settings_getLanguage(void);
TemperatureUnit_e settings_getTemperatureUnit(void);
uint8_t settings_getDisplayBrightness(void);

void settings_setLanguage(const Language_e language);
void settings_setTemperatureUnit(const TemperatureUnit_e temperatureUnit);
void settings_setDisplayBrightness(const uint8_t brightness);

#endif /* GUIMODELS_GUI_APP_SETTINGS_H_ */
