#include "gui_utils_time_converter.h"

#include <time.h>


uint32_t time_converter_rtcTimeToTimeStamp(RTC_TimeTypeDef *p_time, RTC_DateTypeDef *p_date)
{
    struct tm dateTime = {0};
    dateTime.tm_year = p_date->Year + 100;
    dateTime.tm_mday = p_date->Date;
    dateTime.tm_mon = p_date->Month - 1;
    dateTime.tm_hour = p_time->Hours;
    dateTime.tm_min = p_time->Minutes;
    dateTime.tm_sec = p_time->Seconds;

    return (uint32_t) mktime(&dateTime);
}
