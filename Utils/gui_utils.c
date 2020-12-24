#include "gui_utils.h"

#include <string.h>

void gui_utils_setBPMProperty(
        const char *p_bmpName,
        const char *p_property, const uint8_t propertyLength,
        const char *p_value, const uint8_t valueLength)
{
    char *p_str = strstr(p_bmpName, p_property);
    if (p_str != NULL)
    {
        p_str += propertyLength;
        memcpy(p_str, p_value, valueLength);
    }
}


/*** end of file ***/
