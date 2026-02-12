#include "gui_app_settings.h"

#include "utils_data.h"

#define SETTINGS_FILE_PATH "Settings/settings.dat"

static void settings_setToDefault(void);

static GuiAppSettings_s m_settings;


void settings_load(void)
{
    if (!utils_data_loadStruct(SETTINGS_FILE_PATH, &m_settings, sizeof(GuiAppSettings_s)))
    {
        settings_setToDefault();
    }

    theme_init(&m_settings.themeSettings);
    measurement_setup_init(&m_settings.measurementSetup);
}

void settings_save(void)
{
    utils_data_saveStruct(SETTINGS_FILE_PATH, &m_settings, sizeof(GuiAppSettings_s));
}

static void settings_setToDefault(void)
{
    m_settings.language = Language_English;
    m_settings.temperatureUnit = TemperatureUnit_Celsius;
    m_settings.displayBrightness = DISPLAY_DEFAULT_BRIGTHNESS;
    theme_setToDefault(&m_settings.themeSettings);
    measurement_setup_setToDefault(&m_settings.measurementSetup);
}

GuiAppSettings_s settings_getSettings(void)
{
    return m_settings;
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
