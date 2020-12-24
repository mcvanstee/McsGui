#include "gui_keynavigation.h"

#if GUI_CONFIG_USE_KEY_NAVIGATION

#include <stddef.h>

#include "McsGui/Core/gui_basecomponent.h"
#include "McsGui/Utils/gui_memory.h"

#if GUI_USE_DYNAMIC_MEMORY
/**
 * @brief Creates a new malloced KeyNavigation struct.
 * @return Pointer to the malloced memory.
 *
 * @warning The returned struct is not initialized.
 */
KeyNavigation_s *keynav_new(void)
{
    return gui_mem_malloc(sizeof(KeyNavigation_s));
}


/**
 * @brief Delete the KeyNavigation struct. This function calls the gui_mem_free function to free the allocated memory.
 * @param[in] p_keyNavigation Pointer to the KeyNavigation_s sturct to be freed.
 *
 */
void keynav_delete(KeyNavigation_s *p_keyNavigation)
{
    if (p_keyNavigation != NULL)
    {
        gui_mem_free(p_keyNavigation, sizeof(KeyNavigation_s));
        p_keyNavigation = NULL;
    }
}
#endif /* GUI_USE_DYNAMIC_MEMORY */


/**
 * @brief Initialize the KeyNavigation struct to the default values.
 * @param[in] p_keyNavigation Pointer to the KeyNavigation struct.
 *
 */
void keynav_init(KeyNavigation_s *p_keyNavigation)
{
    p_keyNavigation->left = NULL;
    p_keyNavigation->up = NULL;
    p_keyNavigation->right = NULL;
    p_keyNavigation->down = NULL;
}


/**
 * @brief Handles a GuiEvent_s if the event is a key pressed or released. The
 * event will be handled if the component expected to be get focused is not NULL.
 * @param[in] p_keyNavigation Pointer to the KeyNavigation struct.
 * @param[in] p_event Pointer to the GuiEvent struct.
 * @return Return true if the event is handled, else false.
 *
 */
bool keynav_handleEvent(KeyNavigation_s *p_keyNavigation, const GuiEvent_s *p_event)
{
    bool eventHandled = false;
    if (p_keyNavigation == NULL)
    {
        return eventHandled;
    }

    switch (p_event->event)
    {
#if GUI_CONFIG_KEYNAVIGATION_BUTTON_BEHAVIOR == 1
    case GUI_EVENT_KEY_LEFT_RELEASE:
        if (p_keyNavigation->left != NULL)
        {
            eventHandled = base_setActiveFocus(p_keyNavigation->left);
        }
        break;
    case GUI_EVENT_KEY_UP_RELEASE:
        if (p_keyNavigation->up != NULL)
        {
            eventHandled = base_setActiveFocus(p_keyNavigation->up);
        }
        break;
    case GUI_EVENT_KEY_RIGHT_RELEASE:
        if (p_keyNavigation->right != NULL)
        {
            eventHandled = base_setActiveFocus(p_keyNavigation->right);
        }
        break;
    case GUI_EVENT_KEY_DOWN_RELEASE:
        if (p_keyNavigation->down != NULL)
        {
            eventHandled = base_setActiveFocus(p_keyNavigation->down);
        }
        break;
#else
    case GUI_EVENT_KEY_LEFT_PRESS:
        if (p_keyNavigation->left != NULL)
        {
            eventHandled = base_setActiveFocus(p_keyNavigation->left);
        }
        break;
    case GUI_EVENT_KEY_UP_PRESS:
        if (p_keyNavigation->up != NULL)
        {
            eventHandled = base_setActiveFocus(p_keyNavigation->up);
        }
        break;
    case GUI_EVENT_KEY_RIGHT_PRESS:
        if (p_keyNavigation->right != NULL)
        {
            eventHandled = base_setActiveFocus(p_keyNavigation->right);
        }
        break;
    case GUI_EVENT_KEY_DOWN_PRESS:
        if (p_keyNavigation->down != NULL)
        {
            eventHandled = base_setActiveFocus(p_keyNavigation->down);
        }
        break;
    default:
        break;
#endif
    }

    return eventHandled;
}


/**
 * @brief Connects two components. When the key event left is posted to the Gui
 * the the p_from component is unfocused, and p_to component gets focused.
 * @param[in] p_from Component which has focus.
 * @param[in] p_to Component which will receive focus.
 *
 */
void keynav_left(void *p_from, void *p_to)
{
    BaseComponent_s *p_fromComponent = (BaseComponent_s *)p_from;
    if (p_fromComponent->p_keyNavigation != NULL)
    {
        p_fromComponent->p_keyNavigation->left = p_to;
    }
}


/**
 * @brief Connects two components. When the key event up is posted to the Gui
 * the the p_from component is unfocused, and p_to component gets focused.
 * @param[in] p_from Component which has focus.
 * @param[in] p_to Component which will receive focus.
 *
 */
void keynav_up(void *p_from, void *p_to)
{
    BaseComponent_s *p_fromComponent = (BaseComponent_s *)p_from;
    if (p_fromComponent->p_keyNavigation != NULL)
    {
        p_fromComponent->p_keyNavigation->up = p_to;
    }
}


/**
 * @brief Connects two components. When the key event right is posted to the Gui
 * the the p_from component is unfocused, and p_to component gets focused.
 * @param[in] p_from Component which has focus.
 * @param[in] p_to Component which will receive focus.
 *
 */
void keynav_right(void *p_from, void *p_to)
{
    BaseComponent_s *p_fromComponent = (BaseComponent_s *)p_from;
    if (p_fromComponent->p_keyNavigation != NULL)
    {
        p_fromComponent->p_keyNavigation->right = p_to;
    }
}


/**
 * @brief Connects two components. When the key event down is posted to the Gui
 * the the p_from component is unfocused, and p_to component gets focused.
 * @param[in] p_from Component which has focus.
 * @param[in] p_to Component which will receive focus.
 *
 */
void keynav_down(void *p_from, void *p_to)
{
    BaseComponent_s *p_fromComponent = (BaseComponent_s *)p_from;
    if (p_fromComponent->p_keyNavigation != NULL)
    {
        p_fromComponent->p_keyNavigation->down = p_to;
    }
}

#endif /* GUI_CONFIG_USE_KEYNAVIGATION */


/*** end of file ***/
