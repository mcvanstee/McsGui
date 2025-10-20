#include "gui_checkbox.h"

#include <stddef.h>

#include "Core/gui_log.h"
#include "Core/gui_memory.h"
#include "gui_radiogroup.h"

#if !GUI_USE_DYNAMIC_MEMORY
static bool staticCBMemInUse[GUI_CONFIG_CHECKBOX_BUFFER_SIZE] = {0};
static Checkbox_s staticCBMem[GUI_CONFIG_CHECKBOX_BUFFER_SIZE] = {0};
#endif /* GUI_USE_DYNAMIC_MEMORY */


/**
 * @brief Creates a new malloced checkbox component.
 * @return Pointer to the malloced  memory.
 *
 * @warning The returned component is not initialized.
 */
Checkbox_s *checkbox_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(Checkbox_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_CHECKBOX_BUFFER_SIZE; i++)
    {
    	if (!staticCBMemInUse[i])
    	{
    		staticCBMemInUse[i] = true;

    		return &staticCBMem[i];
    	}
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No Checkbox_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Creates a new Checkbox_s component and initializes it to default values.
 * @return Pointer to the Checkbox_s component.
 *
 */
Checkbox_s *checkbox_newInit(void)
{
	Checkbox_s *p_checkbox = checkbox_new();
	checkbox_init(p_checkbox);

	return p_checkbox;
}


/**
 * @brief Delete the checkbox component. This function calls the gui_mem_free function to free the allocated memory.
 * @param[in] p_checkboxBase Pointer to the Checkbox component to be freed.
 */
void checkbox_delete(BaseComponent_s *p_checkboxBase)
{
    base_clear(p_checkboxBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_checkboxBase, sizeof(Checkbox_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_CHECKBOX_BUFFER_SIZE; i++)
    {
    	if (&staticCBMem[i].base == p_checkboxBase)
    	{
    		staticCBMemInUse[i] = false;
    		break;
    	}
    }
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
    p_checkbox->p_nextInGroup = NULL;
    p_checkbox->p_radioGroupBase = NULL;
#endif /* GUI_CONFIG_USE_RADIO_BUTTON_GROUP */
}


/**
 * @brief Initialize the checkbox component to the given values.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] x x-position of the checkbox.
 * @param[in] y y-position of the checkbox.
 *
 */
void checkbox_initBmp(Checkbox_s *p_checkbox, const uint32_t bmpKey)
 {
	checkbox_init(p_checkbox);
	p_checkbox->base.bmpKey = bmpKey;
}


/**
 * @brief Initialize the checkbox component to the given values.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] p_bmpName Pointer to the bmp-name.
 * @param[in] x x-position of the checkbox.
 * @param[in] y y-position of the checkbox.
 *
 */
void checkbox_initBmpPos(
        Checkbox_s *p_checkbox, const uint32_t bmpKey,
        const uint16_t x, const uint16_t y)
{
    checkbox_init(p_checkbox);
    p_checkbox->base.bmpKey = bmpKey;
    base_setPosition(&p_checkbox->base, x, y);
}


/**
 * @brief Initialize the checkbox component to the given values.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] p_bmpName Pointer to the bmp-name.
 * @param[in] x x-position of the checkbox.
 * @param[in] y y-position of the checkbox.
 * @param[in] width.
 * @param[in] height.
 *
 */
void checkbox_initBmpPosSize(
        Checkbox_s *p_checkbox, const uint32_t bmpKey,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height)
{
    checkbox_initBmpPos(p_checkbox, bmpKey, x, y);
    p_checkbox->base.width = width;
    p_checkbox->base.height = height;
}


/**
 * @brief Set the on-selection-changed callback function.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] onSelectionChanged Pointer to the callback function, with a Checkbox_s pointer variable.
 *
 */
void checkbox_setOnSelectionChanged(Checkbox_s *p_checkbox, void (*onSelectionChanged)(Checkbox_s *p_checkboxChanged))
{
    p_checkbox->onSelectionChanged = onSelectionChanged;
}


/**
 * @brief Set the selection of the checkbox.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] selected
 *
 */
void checkbox_setSelection(Checkbox_s *p_checkbox, const bool selected)
{
    p_checkbox->checked = selected;
}


/**
 * @brief Set the selection of the checkbox. The checked propertie is set and the onSelectionChanged callback function is called.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] selected
 *
 */
void checkbox_setSelectionNotifyChanged(Checkbox_s *p_checkbox, const bool selected)
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
        (GUI_EVENT_TOUCH_ON_RELEASED == p_event->event))
#else
    if ((GUI_EVENT_KEY_ENTER_PRESS == p_event->event) ||
        (GUI_EVENT_TOUCH_ON_PRESSED == p_event->event))
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
            checkbox_setSelectionNotifyChanged(p_checkbox, !p_checkbox->checked);
            eventHandled = true;
        }
    }

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
