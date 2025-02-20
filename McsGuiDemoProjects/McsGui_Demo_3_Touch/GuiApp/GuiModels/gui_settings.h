#ifndef GUIMODELS_GUI_SETTINGS_H_
#define GUIMODELS_GUI_SETTINGS_H_

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#define DISPLAY_DEFAULT_BRIGTHNESS 100

typedef struct
{
    uint8_t language;
    uint8_t temperatureUnit;
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

bool settings_getSaveData(void);
uint32_t settings_getInterval(void);
uint32_t settings_getMaxDataPoints(void);

void settings_setSaveData(bool saveData);
void settings_setInterval(uint32_t interval);
void settings_setMaxDataPoints(uint32_t maxDataPoints);

#endif /* GUIMODELS_GUI_SETTINGS_H_ */
