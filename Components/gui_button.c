#include "gui_button.h"

#include <stddef.h>

#include "McsGui/Utils/gui_memory.h"


#if GUI_USE_DYNAMIC_MEMORY
/**
 * @brief Creates a new malloced Button component.
 * @return Pointer to the malloced  memory.
 *
 * @warning The returned component is not initialized.
 */
Button_s *button_new(void)
{
    return gui_mem_malloc(sizeof(Button_s));
}
#endif /* GUI_USE_DYNAMIC_MEMORY */


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
    p_buttonBase = NULL;
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
    p_button->onReleased = NULL;
#if !GUI_USE_DYNAMIC_MEMORY
    p_button->bmpName[0] = '\0';
    p_button->base.p_bmpName = p_button->bmpName;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Initialize the Button_s to the given values.
 * params[in] p_button Pointer to the button component.
 * params[in] p_bmpName Pointer to the bmp-name.
 * params[in] xPos.
 * params[in] yPos.
 *
 */
void button_init_1(
        Button_s *p_button, const char *p_bmpName,
        const uint16_t xPos, const uint16_t yPos)
{
    button_init(p_button);
    p_button->base.xPos = xPos;
    p_button->base.yPos = yPos;
    base_setBmp(&p_button->base, p_bmpName);
}


/**
 * @brief Initialize the Button_s to the given values.
 * params[in] p_button Pointer to the button component.
 * params[in] p_bmpName Pointer to the bmp-name.
 * params[in] xPos.
 * params[in] yPos.
 * params[in] width.
 * params[in] height.
 *
 */
void button_init_2(
        Button_s *p_button, const char *p_bmpName,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height)
{
    button_init_1(p_button, p_bmpName, xPos, yPos);
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
 * @brief Set the on-release callback function.
 * @param[in] p_button Pointer to the button component.
 * @param[in] onTouchReleased Pointer to the callback function, with a Button_s pointer variable.
 *
 */
void button_setOnReleased(Button_s *p_button, void (*onReleased)(Button_s *p_buttonReleased))
{
    p_button->onReleased = onReleased;
}

bool button_handleEvent(BaseComponent_s *p_buttonBase, const GuiEvent_s *p_event)
{
    Button_s *p_button = (Button_s *)p_buttonBase;
    bool eventHandled = false;

#if GUI_CONFIG_USE_TOUCH
    bool isInTouchArea = touch_isInTouchArea(p_buttonBase->p_touch, p_event);
#endif /* GUI_CONFIG_USE_TOUCH */

    if ((GUI_EVENT_KEY_ENTER_PRESS == p_event->event) &&
        (p_button->onPressed != NULL))
    {
        p_button->onPressed(p_button);
        eventHandled = true;
    }
    else if ((GUI_EVENT_KEY_ENTER_RELEASE == p_event->event) &&
             (p_button->onReleased != NULL))
    {
        p_button->onReleased(p_button);
        eventHandled = true;
    }
#if GUI_CONFIG_USE_KEY_NAVIGATION
    else if (keynav_handleEvent(p_buttonBase->p_keyNavigation, p_event))
    {
        base_setFocus(p_buttonBase, false);
        eventHandled = true;
    }
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */
#if GUI_CONFIG_USE_TOUCH
    else if ((GUI_EVENT_TOUCH_PRESSED == p_event->event) &&
             isInTouchArea &&
             (p_button->onPressed != NULL))
    {
        p_button->onPressed(p_button);
        eventHandled = true;
    }
    else if ((GUI_EVENT_TOUCH_RELEASED == p_event->event) &&
             isInTouchArea &&
             (p_button->onReleased != NULL))
    {
        p_button->onReleased(p_button);
        eventHandled = true;
    }
#endif /* GUI_CONFIG_USE_TOUCH */

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
