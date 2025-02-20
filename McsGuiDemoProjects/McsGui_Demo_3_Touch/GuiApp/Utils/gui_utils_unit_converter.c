#include "gui_utils_unit_converter.h"

#include <stdio.h>

float_t unit_converter_celsiusToFahrenheit(float_t celsius)
{
    return (celsius * 9 / 5) + 32;
}

void unit_converter_temperatureToStr(char *p_str, int32_t strLength, float_t temperature)
{
    p_str[0] = '\0';
    const int32_t tempInt = (int32_t)temperature;
    const int32_t tempFrac = (int32_t)((temperature - tempInt) * 10);
    snprintf(p_str, strLength, "%ld.%ld", tempInt, tempFrac);
}

void unit_converter_getTemperatureStr(char *p_str, int32_t strLength, float_t temperature_C, TemperatureUnit_e unit)
{
    float_t temperature = temperature_C;

    if (unit == TemperatureUnit_Fahrenheit)
    {
        temperature = unit_converter_celsiusToFahrenheit(temperature_C);
    }

    unit_converter_temperatureToStr(p_str, strLength, temperature);
}
