#include "gui_settings.h"

#include "utils_data.h"

static void settings_setToDefault(void);

static GuiSettings_s m_settings;


GuiSettings_s settings_getSettings(void)
{
    return m_settings;
}

void settings_setSettings(GuiSettings_s settings)
{
    m_settings = settings;
}

static void settings_setToDefault(void)
{
    m_settings.language = Language_English;
    m_settings.temperatureUnit = TemperatureUnit_Celsius;
    m_settings.showTime = true;
    m_settings.showDate = true;
    m_settings.displayBrightness = DISPLAY_DEFAULT_BRIGTHNESS;
    m_settings.saveData = false;
    m_settings.interval = 1;
    m_settings.maxDataPoints = 10;
    m_settings.gainX = 1.0f;
    m_settings.gainY = 1.0f;
    m_settings.offsetX = 0;
    m_settings.offsetY = 0;
}

void settings_save(void)
{
    utils_data_saveStruct("Settings/settings.dat", &m_settings, sizeof(GuiSettings_s));
}

void settings_load(void)
{
    if (!utils_data_loadStruct("Settings/settings.dat", &m_settings, sizeof(GuiSettings_s)))
    {
        settings_setToDefault();
    }
}

bool settings_getSaveData(void)
{
    return m_settings.saveData;
}

Language_e settings_getLanguage(void)
{
    return m_settings.language;
}

TemperatureUnit_e settings_getTemperatureUnit(void)
{
    return m_settings.temperatureUnit;
}

uint8_t settings_getDisplayBrightness(void)
{
    return m_settings.displayBrightness;
}

bool settings_getShowDate(void)
{
    return m_settings.showDate;
}

bool settings_getShowTime(void)
{
    return m_settings.showTime;
}

uint32_t settings_getInterval(void)
{
    return m_settings.interval;
}

uint32_t settings_getMaxDataPoints(void)
{
    return m_settings.maxDataPoints;
}

void settings_setLanguage(const Language_e language)
{
    m_settings.language = language;
}

void settings_setTemperatureUnit(const TemperatureUnit_e temperatureUnit)
{
    m_settings.temperatureUnit = temperatureUnit;
}

void settings_setDisplayBrightness(const uint8_t brightness)
{
    m_settings.displayBrightness = brightness;
}

void settings_setShowDate(const bool showDate)
{
    m_settings.showDate = showDate;
}

void settings_setShowTime(const bool showTime)
{
    m_settings.showTime = showTime;
}

void settings_setSaveData(bool saveData)
{
    m_settings.saveData = saveData;
}

void settings_setInterval(uint32_t interval)
{
    m_settings.interval = interval;
}

void settings_setMaxDataPoints(uint32_t maxDataPoints)
{
    m_settings.maxDataPoints = maxDataPoints;
}
