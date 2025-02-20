#include "gui_button.h"

#include <stddef.h>
#include <string.h>

#include "Utils/gui_log.h"
#include "Utils/gui_memory.h"


#if !GUI_USE_DYNAMIC_MEMORY
static bool staticButtonMemInUse[GUI_CONFIG_BUTTON_BUFFER_SIZE] = {0};
static Button_s staticButtonMem[GUI_CONFIG_BUTTON_BUFFER_SIZE] = {0};
#endif /* GUI_USE_DYNAMIC_MEMORY */

/**
 * @brief Creates a new malloced Button component.
 * @return Pointer to the malloced memory.
 *
 * @warning The returned component is not initialized.
 */
Button_s *button_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(Button_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_BUTTON_BUFFER_SIZE; i++)
    {
    	if (!staticButtonMemInUse[i])
    	{
    		staticButtonMemInUse[i] = true;

    		return &staticButtonMem[i];
    	}
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No Button_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Creates a new Button_s component and initializes it to default values.
 * @return Pointer to the Button_s component.
 *
 */
Button_s *button_newInit(void)
{
	Button_s *p_newButton = button_new();
	button_init(p_newButton);

	return p_newButton;
}


/**
 * @brief Delete the Button component. This function calls the gui_mem_free function to free the allocated memory.
 * @param[in] p_buttonBase Pointer to the Button component to be freed.
 *
 */
void button_delete(BaseComponent_s *p_buttonBase)
{
    base_clear(p_buttonBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_buttonBase, sizeof(Button_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_BUTTON_BUFFER_SIZE; i++)
    {
    	if (&staticButtonMem[i].base == p_buttonBase)
    	{
    		memset(&staticButtonMem[i], 0, sizeof(Button_s));
    		staticButtonMemInUse[i] = false;
    		break;
    	}
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Initialize the Button_s to the default values,
 * base is initialized to a image-component so it can hold a bmp,
 * base->onDelete calls button_delete when deleted and
 * onHandleEvent calls button_handleEvent when a event is posted to the GUI.
 * params[in] p_button Pointer to the button component.
 *
 */
void button_init(Button_s *p_button)
{
    base_initImageComp(&p_button->base, button_delete);
    p_button->base.onHandleEvent = button_handleEvent;
    p_button->onPressed = NULL;
    p_button->pressed = NULL;
    p_button->onReleased = NULL;
    p_button->onPressedEvent = NULL;
    p_button->pressedEvent = NULL;
    p_button->onReleasedEvent = NULL;
}


/**
 * @brief Initialize the Button_s to the given values.
 * params[in] p_button Pointer to the button component.
 * params[in] p_bmpName Pointer to the bmp-name.
 *
 */
void button_initBmp(Button_s *p_button, const uint32_t bmpKey)
{
    button_init(p_button);
    p_button->base.bmpKey = bmpKey;
}

/**
 * @brief Initialize the Button_s to the given values.
 * params[in] p_button Pointer to the button component.
 * params[in] p_bmpName Pointer to the bmp-name.
 * params[in] x x-position of the button.
 * params[in] y y-position of the button.
 *
 */
void button_initBmpPos(
        Button_s *p_button, const uint32_t bmpKey,
        const uint16_t x, const uint16_t y)
{
    button_init(p_button);
    p_button->base.x = x;
    p_button->base.y = y;
    p_button->base.bmpKey = bmpKey;
}


/**
 * @brief Initialize the Button_s to the given values.
 * params[in] p_button Pointer to the button component.
 * params[in] p_bmpName Pointer to the bmp-name.
 * params[in] x x-position of the button.
 * params[in] y y-position of the button.
 * params[in] width.
 * params[in] height.
 *
 */
void button_initBmpPosSize(
        Button_s *p_button, const uint32_t bmpKey,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height)
{
    button_initBmpPos(p_button, bmpKey, x, y);
    p_button->base.width = width;
    p_button->base.height = height;
}


/**
 * @brief Set the on-pressed callback function.
 * @param[in] p_button Pointer to the button component.
 * @param[in] onTouchPressed Pointer to the callback function, with a Button_s pointer variable.
 *
 */
void button_setOnPressed(Button_s *p_button, void (*onPressed)(Button_s *p_buttonPressed))
{
    p_button->onPressed = onPressed;
}


/**
 * @brief Set the pressed callback function.
 * @param[in] p_button Pointer to the button component.
 * @param[in] onTouchPressed Pointer to the callback function, with a Button_s pointer variable.
 *
 */
void button_setPressed(Button_s *p_button, void (*pressed)(Button_s *p_buttonPressed))
{
	p_button->pressed = pressed;
}


/**
 * @brief Set the on-release callback function.
 * @param[in] p_button Pointer to the button component.
 * @param[in] onTouchReleased Pointer to the callback function, with a Button_s pointer variable.
 *
 */
void button_setOnReleased(Button_s *p_button, void (*onReleased)(Button_s *p_buttonReleased))
{
    p_button->onReleased = onReleased;
}


/**
 * @brief Set the on-pressed-event callback function.
 * @param[in] p_button Pointer to the button component.
 * @param[in] onTouchPressed Pointer to the callback function.
 *
 */
void button_setOnPressedEvent(Button_s *p_button, void (*onPressedEvent)(void))
{
	p_button->onPressedEvent = onPressedEvent;
}


/**
 * @brief Set the pressed-event callback function.
 * @param[in] p_button Pointer to the button component.
 * @param[in] onTouchPressed Pointer to the callback function.
 *
 */
void button_setPressedEvent(Button_s *p_button, void (*pressedEvent)(void))
{
	p_button->onPressedEvent = pressedEvent;
}


/**
 * @brief Set the on-release-event callback function.
 * @param[in] p_button Pointer to the button component.
 * @param[in] onTouchReleased Pointer to the callback function.
 *
 */
void button_setOnReleasedEvent(Button_s *p_button, void (*onReleasedEvent)(void))
{
	p_button->onReleasedEvent = onReleasedEvent;
}

bool button_handleEvent(BaseComponent_s *p_buttonBase, const GuiEvent_s *p_event)
{
    Button_s *p_button = (Button_s *)p_buttonBase;
    bool eventHandled = true;

#if GUI_CONFIG_USE_TOUCH
    bool isInTouchArea = touch_isInTouchArea(p_buttonBase->p_touch, p_event);
#endif /* GUI_CONFIG_USE_TOUCH */

    if ((GUI_EVENT_KEY_ENTER_PRESS == p_event->event) &&
       ((NULL != p_button->onPressed) || (NULL != p_button->onPressedEvent)))
    {
    	if (NULL != p_button->onPressed)
    	{
    		p_button->onPressed(p_button);
    	}

    	if (NULL != p_button->onPressedEvent)
    	{
    		p_button->onPressedEvent();
    	}
    }
    else if ((GUI_EVENT_KEY_ENTER_RELEASE == p_event->event) &&
            ((NULL != p_button->onReleased) || (NULL != p_button->onReleasedEvent)))
    {
    	if (NULL != p_button->onReleased)
    	{
    		p_button->onReleased(p_button);
    	}

    	if (NULL != p_button->onReleasedEvent)
    	{
    		p_button->onReleasedEvent();
    	}
    }
    else

#if GUI_CONFIG_USE_TOUCH
     if ((GUI_EVENT_TOUCH_ON_PRESSED == p_event->event) &&
            isInTouchArea &&
		    ((NULL != p_button->onPressed) || (NULL != p_button->onPressedEvent)))
	{
		if (NULL != p_button->onPressed)
		{
			p_button->onPressed(p_button);
		}

		if (NULL != p_button->onPressedEvent)
		{
			p_button->onPressedEvent();
		}
	}
    else if ((GUI_EVENT_TOUCH_PRESSED == p_event->event) &&
    		isInTouchArea &&
			((NULL != p_button->pressed) || (NULL != p_button->pressedEvent)))
	{
    	if (NULL != p_button->pressed)
    	{
    		p_button->pressed(p_button);
    	}

    	if (NULL != p_button->pressedEvent)
    	{
    		p_button->pressedEvent();
    	}
	}
    else if ((GUI_EVENT_TOUCH_ON_RELEASED == p_event->event) &&
    		isInTouchArea &&
			((NULL != p_button->onReleased) || (NULL != p_button->onReleasedEvent)))
	{
		if (NULL != p_button->onReleased)
		{
			p_button->onReleased(p_button);
		}

		if (NULL != p_button->onReleasedEvent)
		{
			p_button->onReleasedEvent();
		}
    }
    else
#endif /* GUI_CONFIG_USE_TOUCH */
    {
    	eventHandled = false;
    }

    return eventHandled;
}

#if GUI_CONFIG_USE_KEY_NAVIGATION
/**
 * @brief Set the on-focus-changed callback function.
 * @param[in] p_button Pointer to the button component.
 * @param[in] onFocusChanged Pointer to the callback function, with a BaseComponent_s pointer variable.
 *
 */
void button_setOnFocusChanged(Button_s *p_button, void (*onFocusChanged)(BaseComponent_s *p_base))
{
    p_button->base.onFocusChanged = onFocusChanged;
}
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */


/*** end of file ***/
