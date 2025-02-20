#include "gui_touch.h"

#if GUI_CONFIG_USE_TOUCH
#include <stddef.h>

#include "gui_memory.h"


#if !GUI_USE_DYNAMIC_MEMORY
static bool staticTouchMemInUse[GUI_CONFIG_TOUCH_BUFFER_SIZE] = {0};
static Touch_s staticTouchMem[GUI_CONFIG_TOUCH_BUFFER_SIZE] = {0};
#endif /* GUI_USE_DYNAMIC_MEMORY */

#if (GUI_EVENT_ARGS_SIZE < 4)
#error "GUI event args must be greater then 4 when using touch"
#endif


/* Private function declarations */
static inline bool touch_xPosInArea(const Touch_s *p_touch, const uint16_t *p_xPos);
static inline bool touch_yPosInArea(const Touch_s *p_touch, const uint16_t *p_yPos);



/**
 * @brief Creates a new malloced Touch_s struct.
 * @return Pointer to the malloced memory.
 *
 * @warning The returned struct is not initialized.
 */
Touch_s *touch_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(Touch_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_TOUCH_BUFFER_SIZE; i++)
    {
    	if (!staticTouchMemInUse[i])
    	{
    		staticTouchMemInUse[i] = true;

    		return &staticTouchMem[i];
    	}
    }

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Delete the Touch struct. This function calls the gui_mem_free function to free the allocated memory.
 * @param[in] p_touch Pointer to the Touch_s struct to be freed.
 */
void touch_delete(Touch_s *p_touch)
{
    if (p_touch != NULL)
    {
#if GUI_USE_DYNAMIC_MEMORY
        gui_mem_free(p_touch, sizeof(Touch_s));
#else
        for (uint32_t i = 0; i < GUI_CONFIG_TOUCH_BUFFER_SIZE; i++)
        {
        	if (&staticTouchMem[i] == p_touch)
        	{
        		staticTouchMemInUse[i] = false;

        		break;
        	}
        }
#endif /* GUI_USE_DYNAMIC_MEMORY */
        p_touch = NULL;
    }
}


/**
 * @brief Initialize the Touch struct to the default values.
 * @param[in] p_touch Pointer to the Touch_s struct.
 */
void touch_init(Touch_s *p_touch)
{
    p_touch->x = 0;
    p_touch->y = 0;
    p_touch->width = 0;
    p_touch->height = 0;
    p_touch->onPressed = NULL;
    p_touch->pressed = NULL;
    p_touch->onReleased = NULL;
}


/**
 * @brief Initialize the Touch struct to the values passed into the parameters.
 * @param[in] p_touch Pointer to the Touch_s struct.
 * @param[in] x
 * @param[in] y
 * @param[in] width
 * @param[in] height
 *
 */
void touch_init_1(
        Touch_s *p_touch,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height)
{
    p_touch->x = x;
    p_touch->y = y;
    p_touch->width = width;
    p_touch->height = height;
    p_touch->onPressed = NULL;
    p_touch->pressed = NULL;
    p_touch->onReleased = NULL;
}


/**
 * @brief Set the on-pressed callback function.
 * @param[in] p_touch Pointer to the Touch_s struct.
 * @param[in] onPressed Pointer to the callback function, with a BaseComponent_s pointer varaiable.
 *
 */
void touch_setOnPressed(Touch_s *p_touch, void (*onPressed)(void *p_baseComponent))
{
    p_touch->onPressed = onPressed;
}


/**
 * @brief Set the pressed callback function.
 * @param[in] p_touch Pointer to the Touch_s struct.
 * @param[in] pressed Pointer to the callback function, with a BaseComponent_s pointer varaiable.
 *
 */
void touch_setPressed(Touch_s *p_touch, void (*pressed)(void *p_baseComponent))
{
	p_touch->pressed = pressed;
}


/**
 * @brief Set the on-release callback function.
 * @param[in] p_touch Pointer to the Touch_s struct.
 * @param[in] onReleased Pointer to the callback function, with a BaseComponent_s pointer varaiable.
 *
 */
void touch_setOnReleased(Touch_s *p_touch, void (*onReleased)(void *p_baseComponent))
{
    p_touch->onReleased = onReleased;
}


void touch_setTouchArea(
		Touch_s *p_touch,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height)
{
	p_touch->x = x;
	p_touch->y = y;
	p_touch->width = width;
	p_touch->height = height;
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

    uint16_t xPos = ((uint16_t)p_event->eventArgs[1] << 8);
    xPos += p_event->eventArgs[0];

    uint16_t yPos = ((uint16_t)p_event->eventArgs[3] << 8);
    yPos += p_event->eventArgs[2];

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
    bool eventHanded = true;
    if ((GUI_EVENT_TOUCH_ON_PRESSED == p_event->event) &&
        (p_touch->onPressed != NULL))
    {
        p_touch->onPressed(p_baseComponent);
    }
    else if ((GUI_EVENT_TOUCH_PRESSED == p_event->event) &&
    		(p_touch->pressed != NULL))
    {
    	p_touch->pressed(p_baseComponent);
    }
    else if ((GUI_EVENT_TOUCH_ON_RELEASED == p_event->event) &&
    		(p_touch->onReleased != NULL))
    {
        p_touch->onReleased(p_baseComponent);
    }
    else
    {
    	eventHanded = false;
    }

    return eventHanded;
}

static inline bool touch_xPosInArea(const Touch_s *p_touch, const uint16_t *p_xPos)
{
    return (*p_xPos >= p_touch->x) &&
           (*p_xPos <= (p_touch->x + p_touch->width));
}

static inline bool touch_yPosInArea(const Touch_s *p_touch, const uint16_t *p_yPos)
{
    return (*p_yPos >= p_touch->y) &&
           (*p_yPos <= (p_touch->y + p_touch->height));
}
#endif /* GUI_CONFIG_USE_TOUCH */

/*** end of file ***/
