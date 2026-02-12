#ifndef UTILS_GUI_UTILS_UNIT_CONVERTER_H_
#define UTILS_GUI_UTILS_UNIT_CONVERTER_H_

#include <stdint.h>
#include <math.h>

#include "fs_file_search.h"

float_t unit_converter_celsiusToFahrenheit(float_t celsius);
void unit_converter_temperatureToStr(char *p_str, int32_t strLength, float_t temperature);
void unit_converter_getTemperatureStr(char *p_str, int32_t strLength, float_t temperature_C);
file_key_e unit_converter_getTemperatureUnitFileKey(void);

#endif /* UTILS_GUI_UTILS_UNIT_CONVERTER_H_ */
