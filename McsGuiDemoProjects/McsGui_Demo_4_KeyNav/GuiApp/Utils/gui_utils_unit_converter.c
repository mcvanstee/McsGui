#include "gui_utils_unit_converter.h"

#include <stdio.h>

#include "gui_app_settings.h"


float_t unit_converter_celsiusToFahrenheit(float_t celsius)
{
    return (celsius * 9.0f / 5.0f) + 32.0f;
}

void unit_converter_temperatureToStr(char *p_str, int32_t strLength, float_t temperature)
{
    p_str[0] = '\0';
    const int32_t tempInt = (int32_t)temperature;
    const int32_t tempFrac = (int32_t)((temperature - tempInt) * 10);
    snprintf(p_str, strLength, "%ld.%ld", tempInt, tempFrac);
}

void unit_converter_getTemperatureStr(char *p_str, int32_t strLength, float_t temperature_C)
{
    const TemperatureUnit_e unit = settings_getTemperatureUnit();

    if (unit == TemperatureUnit_Fahrenheit)
    {
        temperature_C = unit_converter_celsiusToFahrenheit(temperature_C);
    }

    unit_converter_temperatureToStr(p_str, strLength, temperature_C);
}

file_key_e unit_converter_getTemperatureUnitFileKey(void)
{
    const TemperatureUnit_e unit = settings_getTemperatureUnit();

    return (unit == TemperatureUnit_Celsius) ? FILE_KEY_TEXT_DEG_CEL : FILE_KEY_TEXT_DEG_FAR;
}
