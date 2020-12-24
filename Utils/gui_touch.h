/** @file gui_touch.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_UTILS_GUI_TOUCH_H_
#define MCSGUI_UTILS_GUI_TOUCH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "McsGui/gui_config.h"

#if GUI_CONFIG_USE_TOUCH

#include <stdbool.h>
#include <stdint.h>

#include "McsGui/Core/gui_event.h"

/** @struct Touch_s
 *
 * @brief The Touch_s struct can be added to a BaseComponent_ to enable a touch area
 * on the component. The active touch area is within the rectangle:
 *
 *      (x,y)________
 *          | active |
 *   height | touch  |
 *          | area   |
 *          |________|
 *            width
 *
 */
typedef struct touch_s
{
    uint16_t xPos;      /**< x-position of the touch area. */
    uint16_t yPos;      /**< y-position of the touch area. */
    uint16_t width;     /**< width of the touch area. */
    uint16_t height;    /**< height of the touch area. */
    void (*onTouchPressed)(void *p_baseComponent);      /**< Callback function called when the touch area is pressed. */
    void (*onTouchReleased)(void *p_baseComponent);     /**< Callback function called when the touch area is released. */
} Touch_s;

#if GUI_USE_DYNAMIC_MEMORY
Touch_s *touch_new(void);

void touch_delete(Touch_s *p_touch);
#endif /* GUI_USE_DYNAMIC_MEMORY */

void touch_init(Touch_s *p_touch);
void touch_init_1(
        Touch_s *p_touch,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height);

void touch_setOnPressed(Touch_s *p_touch, void (*onTouchPressed)(void *p_baseComponent));
void touch_setOnReleased(Touch_s *p_touch, void (*onTouchReleased)(void *p_baseComponent));
bool touch_isInTouchArea(const Touch_s *p_touch, const GuiEvent_s *p_event);
bool touch_handleEvent(const Touch_s *p_touch, void *p_baseComponent, const GuiEvent_s *p_event);

#endif /* GUI_CONFIG_USE_TOUCH */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_UTILS_GUI_TOUCH_H_ */


/*** end of file ***/
