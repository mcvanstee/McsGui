#include "gui_touch.h"

#if GUI_CONFIG_USE_TOUCH
#include <stddef.h>

#include "gui_memory.h"

#if (GUI_EVENT_ARGS_SIZE < 4)
#error "GUI event args must be greater then 4 when using touch"
#endif


/* Private function declarations */
static inline bool touch_xPosInArea(const Touch_s *p_touch, const uint16_t *p_xPos);
static inline bool touch_yPosInArea(const Touch_s *p_touch, const uint16_t *p_yPos);


#if GUI_USE_DYNAMIC_MEMORY
/**
 * @brief Creates a new malloced Touch_s struct.
 * @return Pointer to the malloced memory.
 *
 * @warning The returned struct is not initialized.
 */
Touch_s *touch_new(void)
{
    return gui_mem_malloc(sizeof(Touch_s));
}


/**
 * @brief Delete the Touch struct. This function calls the gui_mem_free function to free the allocated memory.
 * @param[in] p_touch Pointer to the Touch_s struct to be freed.
 */
void touch_delete(Touch_s *p_touch)
{
    if (p_touch != NULL)
    {
        gui_mem_free(p_touch, sizeof(Touch_s));
        p_touch = NULL;
    }
}
#endif /* GUI_USE_DYNAMIC_MEMORY */


/**
 * @brief Initialize the Touch struct to the default values.
 * @param[in] p_touch Pointer to the Touch_s struct.
 */
void touch_init(Touch_s *p_touch)
{
    p_touch->xPos = 0;
    p_touch->yPos = 0;
    p_touch->width = 0;
    p_touch->height = 0;
    p_touch->onTouchPressed = NULL;
    p_touch->onTouchReleased = NULL;
}


/**
 * @brief Initialize the Touch struct to the values passed into the parameters.
 * @param[in] p_touch Pointer to the Touch_s struct.
 * @param[in] xPos
 * @param[in] yPos
 * @param[in] width
 * @param[in] height
 *
 */
void touch_init_1(
        Touch_s *p_touch,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height)
{
    p_touch->xPos = xPos;
    p_touch->yPos = yPos;
    p_touch->width = width;
    p_touch->height = height;
    p_touch->onTouchPressed = NULL;
    p_touch->onTouchReleased = NULL;
}


/**
 * @brief Set the on-pressed callback function.
 * @param[in] p_touch Pointer to the Touch_s struct.
 * @param[in] onTouchPressed Pointer to the callback function, with a BaseComponent_s pointer varaiable.
 *
 */
void touch_setOnPressed(Touch_s *p_touch, void (*onTouchPressed)(void *p_baseComponent))
{
    p_touch->onTouchPressed = onTouchPressed;
}


/**
 * @brief Set the on-release callback function.
 * @param[in] p_touch Pointer to the Touch_s struct.
 * @param[in] onTouchReleased Pointer to the callback function, with a BaseComponent_s pointer varaiable.
 *
 */
void touch_setOnReleased(Touch_s *p_touch, void (*onTouchReleased)(void *p_baseComponent))
{
    p_touch->onTouchReleased = onTouchReleased;
}


/**
 * @brief Check if the position pressed is in the touch area.
 * @param[in] p_touch Pointer to the Touch_s struct.
 * @param[in] p_event Pointer to GuiEvent_s struct which eventArgs holds the position touched.
 * @return Return true if the position is in the touch area, else false.
 */
bool touch_isInTouchArea(const Touch_s *p_touch, const GuiEvent_s *p_event)
{
    if ((p_touch == NULL) ||
        (p_event == NULL) ||
        (p_touch->width == 0) ||
        (p_touch->height == 0))
    {
        return false;
    }

    uint16_t xPos = ((uint16_t)p_event->eventArgs[0] << 8);
    xPos += p_event->eventArgs[1];

    uint16_t yPos = ((uint16_t)p_event->eventArgs[2] << 8);
    yPos += p_event->eventArgs[3];

    bool xPosInTouchArea = touch_xPosInArea(p_touch, &xPos);
    bool yPosInTouchArea = touch_yPosInArea(p_touch, &yPos);

    return xPosInTouchArea && yPosInTouchArea;
}


/**
 * @brief Handles a GuiEvent_s if the event is in the touch area.
 * @param[in] p_touch Pointer to the Touch_s struct.
 * @param[in] p_baseComponent Pointer to the BaseComponent_s holding the p_touch struct.
 * @param[in] p_event Pointer to GuiEvent_s struct
 * @return Return true if the event is handled, else false.
 *
 */
bool touch_handleEvent(const Touch_s *p_touch, void *p_baseComponent, const GuiEvent_s *p_event)
{
    bool eventHanded = false;
    if ((GUI_EVENT_TOUCH_PRESSED == p_event->event) &&
        (p_touch->onTouchPressed != NULL))
    {
        p_touch->onTouchPressed(p_baseComponent);
        eventHanded = true;
    }
    else if ((GUI_EVENT_TOUCH_RELEASED == p_event->event))
    {
        p_touch->onTouchReleased(p_baseComponent);
        eventHanded = true;
    }

    return eventHanded;
}

static inline bool touch_xPosInArea(const Touch_s *p_touch, const uint16_t *p_xPos)
{
    return (*p_xPos >= p_touch->xPos) &&
           (*p_xPos <= (p_touch->xPos + p_touch->width));
}

static inline bool touch_yPosInArea(const Touch_s *p_touch, const uint16_t *p_yPos)
{
    return (*p_yPos >= p_touch->yPos) &&
           (*p_yPos <= (p_touch->yPos + p_touch->height));
}
#endif /* GUI_CONFIG_USE_TOUCH */

/*** end of file ***/
