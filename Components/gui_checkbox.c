#include "gui_checkbox.h"

#include <stddef.h>

#include "McsGui/Utils/gui_memory.h"
#include "gui_radiogroup.h"

#if GUI_USE_DYNAMIC_MEMORY
/**
 * @brief Creates a new malloced checkbox component.
 * @return Pointer to the malloced  memory.
 *
 * @warning The returned component is not initialized.
 */
Checkbox_s *checkbox_new(void)
{
    return gui_mem_malloc(sizeof(Checkbox_s));
}
#endif /* GUI_USE_DYNAMIC_MEMORY */


/**
 * @brief Delete the checkbox component. This function calls the gui_mem_free function to free the allocated memory.
 * @param[in] p_checkboxBase Pointer to the Checkbox component to be freed.
 */
void checkbox_delete(BaseComponent_s *p_checkboxBase)
{
    base_clear(p_checkboxBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_checkboxBase, sizeof(Checkbox_s));
    p_checkboxBase = NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Initialize the checkbox component to the default values.
 * @param[in] p_checkbox Pointer to the checkbox component.
 *
 */
void checkbox_init(Checkbox_s *p_checkbox)
{
    base_initImageComp(&p_checkbox->base, checkbox_delete);
    p_checkbox->base.onHandleEvent = checkbox_handleEvent;
    p_checkbox->onSelectionChanged = NULL;
    p_checkbox->checked = false;
#if GUI_CONFIG_USE_RADIO_BUTTON_GROUP
    p_checkbox->p_radioGroupBase = NULL;
#endif /* GUI_CONFIG_USE_RADIO_BUTTON_GROUP */
#if !GUI_USE_DYNAMIC_MEMORY
    p_checkbox->bmpName[0] = '\0';
    p_checkbox->base.p_bmpName = p_checkbox->bmpName;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Initialize the checkbox component to the given values.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] p_bmpName Pointer to the bmp-name.
 * @param[in] xPos.
 * @param[in] yPos.
 *
 */
void checkbox_init_1(
        Checkbox_s *p_checkbox, const char *p_bmpName,
        const uint16_t xPos, const uint16_t yPos)
{
    checkbox_init(p_checkbox);
    base_setBmp(&p_checkbox->base, p_bmpName);
    base_setPosition(&p_checkbox->base, xPos, yPos);
}


/**
 * @brief Initialize the checkbox component to the given values.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] p_bmpName Pointer to the bmp-name.
 * @param[in] xPos.
 * @param[in] yPos.
 * @param[in] width.
 * @param[in] height.
 *
 */
void checkbox_init_2(
        Checkbox_s *p_checkbox, const char *p_bmpName,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height)
{
    checkbox_init_1(p_checkbox, p_bmpName, xPos, yPos);
    p_checkbox->base.width = width;
    p_checkbox->base.height = height;
}


/**
 * @brief Set the on-selection-changed callback function.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] onSelectionChanged Pointer to the callback function, with a Checkbox_s pointer variable.
 *
 */
void checkbox_setOnSelectionchanged(Checkbox_s *p_checkbox, void (*onSelectionChanged)(Checkbox_s *p_checkboxChanged))
{
    p_checkbox->onSelectionChanged = onSelectionChanged;
}


/**
 * @brief Set the selection of the checkbox. The checked propertie is set and the onSelectionChanged callback function is called.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] selected
 *
 */
void checkbox_setSelection(Checkbox_s *p_checkbox, const bool selected)
{
    p_checkbox->checked = selected;

    if (p_checkbox->onSelectionChanged != NULL)
    {
        p_checkbox->onSelectionChanged(p_checkbox);
    }
}

bool checkbox_handleEvent(BaseComponent_s *p_checkboxBase, const GuiEvent_s *p_event)
{
    Checkbox_s *p_checkbox = (Checkbox_s *)p_checkboxBase;
    bool eventHandled = false;

#if GUI_CONFIG_CHECKBOX_BUTTON_BEHAVIOR == 1
    if ((GUI_EVENT_KEY_ENTER_RELEASE == p_event->event) ||
        (GUI_EVENT_TOUCH_RELEASED == p_event->event))
#else
    if ((GUI_EVENT_KEY_ENTER_PRESS == p_event->event) ||
        (GUI_EVENT_TOUCH_PRESSED == p_event->event))
#endif
    {
#if GUI_CONFIG_USE_RADIO_BUTTON_GROUP
        if (p_checkbox->p_radioGroupBase != NULL)
        {
            eventHandled = radiogroup_handleButtonPressed(
                    p_checkbox->p_radioGroupBase, p_checkbox);
        }
        else
#endif /* GUI_CONFIG_USE_RADIO_BUTTON_GROUP */
        {
            checkbox_setSelection(p_checkbox, !p_checkbox->checked);
            eventHandled = true;
        }
    }
#if GUI_CONFIG_USE_KEY_NAVIGATION
    else if (keynav_handleEvent(p_checkboxBase->p_keyNavigation, p_event))
    {
        base_setFocus(p_checkboxBase, false);
        eventHandled = true;
    }
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

    return eventHandled;
}

#if GUI_CONFIG_USE_KEY_NAVIGATION
/**
 * @brief Set the on-focus-changed callback function.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] onFocusChanged Pointer to the callback function, with a BaseComponent_s pointer variable.
 *
 */
void checkbox_setOnFocusChanged(Checkbox_s *p_checkbox, void (*onFocusChanged)(BaseComponent_s *p_base))
{
    p_checkbox->base.onFocusChanged = onFocusChanged;
}
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */


/*** end of file ***/
