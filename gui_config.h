/** @file gui_config.h
 *
 * @brief McsGui - Configuration file
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_GUI_CONFIG_H_
#define MCSGUI_GUI_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long Color_t;

#define CONFIG_ON  1 /* Enable option */
#define CONFIG_OFF 0 /* Disable option */

#define GUI_EVENT_ARGS_SIZE 4 /* Defines the eventArgs buffer size on GuiEvent_s, must be 4 or greater when using touch */

#define GUI_USE_DYNAMIC_MEMORY (CONFIG_ON)
#define GUI_CONFIG_GRAPHICS_BUFFER_SIZE 50


/*_____________________________________________________
|                                                      |
|          Component configuration options             |
|______________________________________________________|
*/

#define GUI_CONFIG_USE_RADIO_BUTTON_GROUP (CONFIG_ON)
/* This option removes the RadioButtonGroup_s component
/  from the GUI module, when CONFIG_OFF */

#define GUI_CONFIG_USE_LIST_VIEW (CONFIG_ON)
/* This option removes the ListView_s component
/  from the GUI module, when CONFIG_OFF */


/*_____________________________________________________
|                                                      |
|         Checkbox_s configuration options             |
|______________________________________________________|
*/

#define GUI_CONFIG_CHECKBOX_BUTTON_BEHAVIOR 0
/* This option defines the behavior of the button
/
/   0: Checkbox responds to Pressed event
/   1: Checkbox responds to Released event
*/


/*_____________________________________________________
|                                                      |
|        KeyNavigation_s configuration options         |
|______________________________________________________|
*/

#define GUI_CONFIG_KEYNAVIGATION_BUTTON_BEHAVIOR 0
/* This option defines the behavior of the button
/
/   0: KeyNavigation responds to Pressed event
/   1: KeyNavigation responds to Released event
*/


/*_____________________________________________________
|                                                      |
|           ListView_s configuration options           |
|______________________________________________________|
*/

#define GUI_CONFIG_LISTVIEW_BUTTON_BEHAVIOR 0
/* This option defines the behavior of the button
/
/   0: ListView responds to Pressed event
/   1: ListView responds to Released event
*/


/*_____________________________________________________
|                                                      |
|        BaseComponent_s configuration options         |
|______________________________________________________|
*/

#define GUI_CONFIG_USE_STRICT_TYPES (CONFIG_OFF)
/* If
 *
 */

#define GUI_CONFIG_BITMAP_NAME_LENGTH 30
#define GUI_CONFIG_BITMAP_NAME_LENGTH_INC_NULL (GUI_CONFIG_BITMAP_NAME_LENGTH + 1)

/* KeyNavigation
 *
 * Select CONFIG_ON to use key-navigation,
 */
#define GUI_CONFIG_USE_KEY_NAVIGATION (CONFIG_ON)
#define GUI_CONFIG_KEYNAVIGATION_BUTTON_BEHAVIOR 0

/* TouchArea
 *
 */
#define GUI_CONFIG_USE_TOUCH (CONFIG_ON)

/* Margin
 *
 */
#define GUI_CONFIG_USE_MARGIN (CONFIG_ON)

/* Alignment
 *
 */
#define GUI_CONFIG_USE_ALIGNMENT (CONFIG_ON)

/* Background
 *
 */
#define GUI_CONFIG_USE_BACKGROUND (CONFIG_ON)

#define GUI_CONFIG_USE_ON_BEFORE_DISPLAY (CONFIG_ON)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_GUI_CONFIG_H_ */
