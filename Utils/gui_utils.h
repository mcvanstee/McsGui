/** @file gui_utils.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_UTILS_GUI_UTILS_H_
#define MCSGUI_UTILS_GUI_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void gui_utils_setBPMProperty(
        const char *p_bmpName,
        const char *p_property, const uint8_t propertyLength,
        const char *p_value, const uint8_t valueLength);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_UTILS_GUI_UTILS_H_ */


/*** end of file ***/
