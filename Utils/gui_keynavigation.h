/** @file gui_keynavigation.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_UTILS_GUI_KEYNAVIGATION_H_
#define MCSGUI_UTILS_GUI_KEYNAVIGATION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "McsGui/gui_config.h"

#if GUI_CONFIG_USE_KEY_NAVIGATION

#include <stdbool.h>

#include "McsGui/Core/gui_event.h"


/** @struct KeyNavigation_s
 *
 * @brief The KeyNavigation_s struct can be added to a BaseComponent_s to enable keynavigation on the
 * component.
 *
 */
typedef struct key_kavigation_s
{
    void *left;     /**< Pointer to the component which get active focus when the key left is pressed. */
    void *up;       /**< Pointer to the component which get active focus when the key up is pressed. */
    void *right;    /**< Pointer to the component which get active focus when the key right is pressed. */
    void *down;     /**< Pointer to the component which get active focus when the key down is pressed. */
} KeyNavigation_s;


#if GUI_USE_DYNAMIC_MEMORY
KeyNavigation_s *keynav_new(void);
void keynav_delete(KeyNavigation_s *p_keyNavigation);
#endif /* GUI_USE_DYNAMIC_MEMORY */

void keynav_init(KeyNavigation_s *p_keyNavigation);
bool keynav_handleEvent(KeyNavigation_s *p_keyNavigation, const GuiEvent_s *p_event);
void keynav_left(void *p_from, void *p_to);
void keynav_up(void *p_from, void *p_to);
void keynav_right(void *p_from, void *p_to);
void keynav_down(void *p_from, void *p_to);

#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_UTILS_GUI_KEYNAVIGATION_H_ */


/*** end of file ***/
