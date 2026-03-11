/** @file gui_touch.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_CORE_GUI_TOUCH_H_
#define MCSGUI_CORE_GUI_TOUCH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gui_config.h"

#if GUI_CONFIG_USE_TOUCH

#include <stdbool.h>
#include <stdint.h>

#include "Core/gui_event.h"

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
typedef struct
{
    uint16_t x;      /**< x-position of the touch area. */
    uint16_t y;      /**< y-position of the touch area. */
    uint16_t width;     /**< width of the touch area. */
    uint16_t height;    /**< height of the touch area. */
    void (*onPressed)(void *p_baseComponent);      /**< Callback function called when the touch area is pressed. */
    void (*pressed)(void *p_baseComponent);      /**< Callback function called when the touch area is pressed. */
    void (*onReleased)(void *p_baseComponent);     /**< Callback function called when the touch area is released. */
} Touch_s;

Touch_s *touch_new(void);
void touch_delete(Touch_s *p_touch);
void touch_init(Touch_s *p_touch);
void touch_init_1(
        Touch_s *p_touch,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height);

void touch_setOnPressed(Touch_s *p_touch, void (*onPressed)(void *p_baseComponent));
void touch_setPressed(Touch_s *p_touch, void (*pressed)(void *p_baseComponent));
void touch_setOnReleased(Touch_s *p_touch, void (*onReleased)(void *p_baseComponent));
void touch_setTouchArea(
		Touch_s *p_touch,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height);
bool touch_isInTouchArea(const Touch_s *p_touch, const GuiEvent_s *p_event);
bool touch_handleEvent(const Touch_s *p_touch, void *p_baseComponent, const GuiEvent_s *p_event);

#endif /* GUI_CONFIG_USE_TOUCH */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_CORE_GUI_TOUCH_H_ */


/*** end of file ***/
