#include "gui_button.h"

#include <stddef.h>
#include <string.h>

#include "Core/gui_log.h"
#include "Core/gui_memory.h"

static void button_delete(BaseComponent_s *p_buttonBase);
static bool button_handleEvent(BaseComponent_s *p_buttonBase, const GuiEvent_s *p_event);

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
static void button_delete(BaseComponent_s *p_buttonBase)
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


/**
 * @brief Display the button component.
 * @param[in] p_button Pointer to the button component.
 *
 */
void button_display(Button_s *p_button)
{
    base_display(&p_button->base);
}


/**
 * @brief Set the button id.
 * @param[in] p_button Pointer to the button component.
 * @param[in] id Id of the button.
 *
 */
void button_setId(Button_s *p_button, const uint32_t id)
{
    if (id > 0)
    {
        p_button->base.id = id;
    }
}


/**
 * @brief Set the button bmp-key.
 * @param[in] p_button Pointer to the button component.
 * @param[in] bmpKey Bmp-key of the button.
 *
 */
void button_setBmpKey(Button_s *p_button, const uint32_t bmpKey)
{
    p_button->base.bmpKey = bmpKey;
}


/**
 * @brief Set the button x-position.
 * @param[in] p_button Pointer to the button component.
 * @param[in] x x-position of the button.
 *
 */
void button_setX(Button_s *p_button, const uint16_t x)
{
    base_setX(&p_button->base, x);
}


/**
 * @brief Set the button y-position.
 * @param[in] p_button Pointer to the button component.
 * @param[in] y y-position of the button.
 *
 */
void button_setY(Button_s *p_button, const uint16_t y)
{
    base_setY(&p_button->base, y);
}


/**
 * @brief Set the button width.
 * @param[in] p_button Pointer to the button component.
 * @param[in] width Width of the button.
 *
 */
void button_setWidth(Button_s *p_button, const uint16_t width)
{
    base_setWidth(&p_button->base, width);
}


/**
 * @brief Set the button height.
 * @param[in] p_button Pointer to the button component.
 * @param[in] height Height of the button.
 *
 */
void button_setHeight(Button_s *p_button, const uint16_t height)
{
    base_setHeight(&p_button->base, height);
}


/**
 * @brief Set the button position.
 * @param[in] p_button Pointer to the button component.
 * @param[in] x x-position of the button.
 * @param[in] y y-position of the button.
 *
 */
void button_setPosition(Button_s *p_button, const uint16_t x, const uint16_t y)
{
    base_setPosition(&p_button->base, x, y);
}


/**
 * @brief Set the button size.
 * @param[in] p_button Pointer to the button component.
 * @param[in] width Width of the button.
 * @param[in] height Height of the button.
 *
 */
void button_setSize(Button_s *p_button, const uint16_t width, const uint16_t height)
{
    base_setSize(&p_button->base, width, height);
}


/**
 * @brief Set the button visibility.
 * @param[in] p_button Pointer to the button component.
 * @param[in] visible Whether the button should be visible or not.
 *
 */
void button_setVisible(Button_s *p_button, const bool visible)
{
    base_setVisible(&p_button->base, visible);
}


/**
 * @brief Set the button background color.
 * @param[in] p_button Pointer to the button component.
 * @param[in] color Background color of the button.
 *
 */
void button_setBackgroundColor(Button_s *p_button, const Color_t color)
{
    p_button->base.backgroundColor = color;
}


/**
 * @brief Set the button draw-background flag.
 * @param[in] p_button Pointer to the button component.
 * @param[in] drawBackground Draw-background flag of the button.
 *
 */
void button_setDrawBackground(Button_s *p_button, const bool drawBackground)
{
    p_button->base.drawBackground = drawBackground;
}


#if GUI_CONFIG_USE_BITMAP_COLORS
/**
 * @brief Set the button foreground color.
 * @param[in] p_button Pointer to the button component.
 * @param[in] color Foreground color of the button.
 *
 */
void button_setForegroundColor(Button_s *p_button, const Color_t color)
{
    p_button->base.foregroundColor = color;
}
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */


/**
 * @brief Set the button bmp-alignment.
 * @param[in] p_button Pointer to the button component.
 * @param[in] horizontalAlignment Horizontal alignment of the button.
 * @param[in] verticalAlignment Vertical alignment of the button.
 *
 */
void button_setBmpAlignment(Button_s *p_button, const GuiAlignment_e horizontalAlignment, const GuiAlignment_e verticalAlignment)
{
    p_button->base.horizontalAlignment = (uint8_t)horizontalAlignment;
    p_button->base.verticalAlignment = (uint8_t)verticalAlignment;
}


/**
 * @brief Set the horizontal alignment of the button bitmap.
 * @param[in] p_button Pointer to the button component.
 * @param[in] horizontalAlignment Horizontal alignment of the bitmap.
 *
 */
void button_setBmpHorizontalAlignment(Button_s *p_button, const GuiAlignment_e horizontalAlignment)
{
    p_button->base.horizontalAlignment = (uint8_t) horizontalAlignment;
}


/**
 * @brief Set the vertical alignment of the button bitmap.
 * @param[in] p_button Pointer to the button component.
 * @param[in] verticalAlignment Vertical alignment of the bitmap.
 *
 */
void button_setBmpVerticalAlignment(Button_s *p_button, const GuiAlignment_e verticalAlignment)
{
    p_button->base.verticalAlignment = (uint8_t) verticalAlignment;
}


/**
 * @brief Set the padding of the button bitmap.
 * @param[in] p_button Pointer to the button component.
 * @param[in] left Left padding of the bitmap.
 * @param[in] top Top padding of the bitmap.
 * @param[in] right Right padding of the bitmap.
 * @param[in] bottom Bottom padding of the bitmap.
 *
 */
void button_setBmpPadding(Button_s *p_button, const uint8_t left, const uint8_t top, const uint8_t right, const uint8_t bottom)
{
    p_button->base.leftPadding = left;
    p_button->base.rightPadding = right;
    p_button->base.topPadding = top;
    p_button->base.bottomPadding = bottom;
}


/**
 * @brief Set the left padding of the button bitmap.
 * @param[in] p_button Pointer to the button component.
 * @param[in] padding Left padding of the bitmap.
 *
 */
void button_setBmpLeftPadding(Button_s *p_button, const uint8_t padding)
{
    p_button->base.leftPadding = padding;
}


/**
 * @brief Set the right padding of the button bitmap.
 * @param[in] p_button Pointer to the button component.
 * @param[in] padding Right padding of the bitmap.
 *
 */
void button_setBmpRightPadding(Button_s *p_button, const uint8_t padding)
{
    p_button->base.rightPadding = padding;
}


/**
 * @brief Set the top padding of the button bitmap.
 * @param[in] p_button Pointer to the button component.
 * @param[in] padding Top padding of the bitmap.
 *
 */
void button_setBmpTopPadding(Button_s *p_button, const uint8_t padding)
{
    p_button->base.topPadding = padding;
}


/**
 * @brief Set the bottom padding of the button bitmap.
 * @param[in] p_button Pointer to the button component.
 * @param[in] padding Bottom padding of the bitmap.
 *
 */
void button_setBmpBottomPadding(Button_s *p_button, const uint8_t padding)
{
    p_button->base.bottomPadding = padding;
}


static bool button_handleEvent(BaseComponent_s *p_buttonBase, const GuiEvent_s *p_event)
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
