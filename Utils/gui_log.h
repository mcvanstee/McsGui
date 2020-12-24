/** @file gui_log.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_UTILS_GUI_LOG_H_
#define MCSGUI_UTILS_GUI_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

#define GUI_LOG_MAX_MESSAGE_LENGTH 50
#define GUI_LOG_MAX_MESSAGE_LENGTH_INC_NULL (GUI_LOG_MAX_MESSAGE_LENGTH + 1)

#define GUI_LOG_LEVEL_ERROR 0
#define GUI_LOG_LEVEL_WARNING 1
#define GUI_LOG_LEVEL_INFO 2
#define GUI_LOG_LEVEL_DEBUG 3

void gui_log_write(const uint8_t logLevel, const char *p_message);
void gui_log_writeUInt(const uint8_t logLevel, const char *p_message, const uint32_t number);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_UTILS_GUI_LOG_H_ */


/*** end of file ***/
