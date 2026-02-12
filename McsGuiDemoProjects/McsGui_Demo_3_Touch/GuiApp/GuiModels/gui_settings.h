#ifndef GUIMODELS_GUI_SETTINGS_H_
#define GUIMODELS_GUI_SETTINGS_H_

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "gui_utils_unit_converter.h"

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

typedef struct
{
    Language_e language;
    TemperatureUnit_e temperatureUnit;
    bool showTime;
    bool showDate;
    uint8_t displayBrightness;
    bool saveData;
    uint32_t interval;
    uint32_t maxDataPoints;
	float_t gainX;
	float_t gainY;
	float_t offsetX;
	float_t offsetY;
} GuiSettings_s;


GuiSettings_s settings_getSettings(void);
void settings_setSettings(GuiSettings_s settings);

void settings_save(void);
void settings_load(void);

Language_e settings_getLanguage(void);
TemperatureUnit_e settings_getTemperatureUnit(void);
uint8_t settings_getDisplayBrightness(void);
bool settings_getShowDate(void);
bool settings_getShowTime(void);
uint32_t settings_getInterval(void);
uint32_t settings_getMaxDataPoints(void);

void settings_setLanguage(const Language_e language);
void settings_setTemperatureUnit(const TemperatureUnit_e temperatureUnit);
void settings_setDisplayBrightness(const uint8_t brightness);
void settings_setShowDate(const bool showDate);
void settings_setShowTime(const bool showTime);

void settings_setSaveData(bool saveData);
void settings_setInterval(uint32_t interval);
void settings_setMaxDataPoints(uint32_t maxDataPoints);

#endif /* GUIMODELS_GUI_SETTINGS_H_ */
