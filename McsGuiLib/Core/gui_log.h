/** @file gui_log.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_CORE_GUI_LOG_H_
#define MCSGUI_CORE_GUI_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define GUI_LOG_LEVEL_ERROR 0
#define GUI_LOG_LEVEL_WARNING 1
#define GUI_LOG_LEVEL_INFO 2
#define GUI_LOG_LEVEL_DEBUG 3


extern void gui_log_write(const uint8_t logLevel, const char *p_message);
void gui_log_error(const char *p_message);
void gui_log_warning(const char *p_message);
void gui_log_debug(const char *p_message);
void gui_log_info(const char *p_message);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_CORE_GUI_LOG_H_ */


/*** end of file ***/
