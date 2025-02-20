#ifndef UTILS_GUI_UTILS_UNIT_CONVERTER_H_
#define UTILS_GUI_UTILS_UNIT_CONVERTER_H_

#include <stdint.h>
#include <math.h>

typedef enum
{
    TemperatureUnit_Celsius = 0,
    TemperatureUnit_Fahrenheit,
} TemperatureUnit_e;

float_t unit_converter_celsiusToFahrenheit(float_t celsius);
void unit_converter_temperatureToStr(char *p_str, int32_t strLength, float_t temperature);
void unit_converter_getTemperatureStr(char *p_str, int32_t strLength, float_t temperature_C, TemperatureUnit_e unit);

#endif /* UTILS_GUI_UTILS_UNIT_CONVERTER_H_ */
