#ifndef UTILS_GUI_UTILS_TIME_CONVERTER_H_
#define UTILS_GUI_UTILS_TIME_CONVERTER_H_

#include "stm32l4xx_hal.h"

uint32_t time_converter_rtcTimeToTimeStamp(RTC_TimeTypeDef *p_time, RTC_DateTypeDef *p_date);

#endif /* UTILS_GUI_UTILS_TIME_CONVERTER_H_ */
