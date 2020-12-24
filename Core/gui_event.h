/** @file gui_event.h
 *
 * @brief The struct GuiEvent_s is used to send a event and optionally event arguments to the Gui Module.
 * Gui Events used by the Gui are defined here. You can define custom events in your own file.
 *
 * @warning If you define your own Events. Define them from 101.
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_CORE_GUI_EVENT_H_
#define MCSGUI_CORE_GUI_EVENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "McsGui/gui_config.h"

#define GUI_EVENT_KEY_ENTER_PRESS 1
#define GUI_EVENT_KEY_ENTER_LONG_PRESS 2
#define GUI_EVENT_KEY_ENTER_RELEASE 3

#define GUI_EVENT_KEY_LEFT_PRESS 4
#define GUI_EVENT_KEY_LEFT_LONG_PRESS 5
#define GUI_EVENT_KEY_LEFT_RELEASE 6

#define GUI_EVENT_KEY_UP_PRESS 7
#define GUI_EVENT_KEY_UP_LONG_PRESS 8
#define GUI_EVENT_KEY_UP_RELEASE 9

#define GUI_EVENT_KEY_RIGHT_PRESS 10
#define GUI_EVENT_KEY_RIGHT_LONG_PRESS 11
#define GUI_EVENT_KEY_RIGHT_RELEASE 12

#define GUI_EVENT_KEY_DOWN_PRESS 13
#define GUI_EVENT_KEY_DOWN_LONG_PRESS 14
#define GUI_EVENT_KEY_DOWN_RELEASE 15

#define GUI_EVENT_TOUCH_PRESSED 16
#define GUI_EVENT_TOUCH_RELEASED 17


typedef struct gui_event_s
{
  uint8_t event;
  uint8_t eventArgs[GUI_EVENT_ARGS_SIZE];
} GuiEvent_s;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_CORE_GUI_EVENT_H_ */


/*** end of file ***/
