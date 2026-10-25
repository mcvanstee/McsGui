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
 * @brief Get the selection of the checkbox.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @return true if the checkbox is selected, false otherwise.
 *
 */
bool checkbox_isChecked(Checkbox_s *p_checkbox)
{
    return p_checkbox->checked;
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


/**
 * @brief Display the checkbox component.
 * @param[in] p_checkbox Pointer to the checkbox component.
 *
 */
void checkbox_display(Checkbox_s *p_checkbox)
{
    base_display(&p_checkbox->base);
}


/**
 * @brief Set the id of the checkbox.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] id Id of the checkbox.
 *
 */
void checkbox_setId(Checkbox_s *p_checkbox, const uint8_t id)
{
    if (id > 0)
    {
        p_checkbox->base.id = id;
    }
}


/**
 * @brief Set the bmp-key of the checkbox.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] bmpKey Bmp-key of the checkbox.
 *
 */
void checkbox_setBmpKey(Checkbox_s *p_checkbox, const uint32_t bmpKey)
{
    p_checkbox->base.bmpKey = bmpKey;
}


/**
 * @brief Set the x-position of the checkbox.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] x x-position of the checkbox.
 *
 */
void checkbox_setX(Checkbox_s *p_checkbox, const uint16_t x)
{
    base_setX(&p_checkbox->base, x);
}


/**
 * @brief Set the y-position of the checkbox.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] y y-position of the checkbox.
 *
 */
void checkbox_setY(Checkbox_s *p_checkbox, const uint16_t y)
{
    base_setY(&p_checkbox->base, y);
}


/**
 * @brief Set the width of the checkbox.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] width Width of the checkbox.
 *
 */
void checkbox_setWidth(Checkbox_s *p_checkbox, const uint16_t width)
{
    base_setWidth(&p_checkbox->base, width);
}


/**
 * @brief Set the height of the checkbox.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] height Height of the checkbox.
 *
 */
void checkbox_setHeight(Checkbox_s *p_checkbox, const uint16_t height)
{
    base_setHeight(&p_checkbox->base, height);
}


/**
 * @brief Set the position of the checkbox.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] x x-position of the checkbox.
 * @param[in] y y-position of the checkbox.
 *
 */
void checkbox_setPosition(Checkbox_s *p_checkbox, const uint16_t x, const uint16_t y)
{
    base_setPosition(&p_checkbox->base, x, y);
}


/**
 * @brief Set the size of the checkbox.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] width Width of the checkbox.
 * @param[in] height Height of the checkbox.
 *
 */
void checkbox_setSize(Checkbox_s *p_checkbox, const uint16_t width, const uint16_t height)
{
    base_setSize(&p_checkbox->base, width, height);
}


/**
 * @brief Set the visibility of the checkbox.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] visible Whether the checkbox should be visible.
 *
 */
void checkbox_setVisible(Checkbox_s *p_checkbox, const bool visible)
{
    base_setVisible(&p_checkbox->base, visible);
}


/**
 * @brief Set the background color of the checkbox.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] color Background color of the checkbox.
 *
 */
void checkbox_setBackgroundColor(Checkbox_s *p_checkbox, const Color_t color)
{
    p_checkbox->base.backgroundColor = color;
}


/**
 * @brief Set whether the background of the checkbox should be drawn.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] drawBackground Whether the background should be drawn.
 *
 */
void checkbox_setDrawBackground(Checkbox_s *p_checkbox, const bool drawBackground)
{
    p_checkbox->base.drawBackground = drawBackground;
}


/**
 * @brief Set the foreground color of the checkbox.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] color Foreground color of the checkbox.
 *
 */
#if GUI_CONFIG_USE_BITMAP_COLORS
void checkbox_setForegroundColor(Checkbox_s *p_checkbox, const Color_t color)
{
    p_checkbox->base.foregroundColor = color;
}
#endif /* GUI_CONFIG_USE_BITMAP_COLORS */


#if GUI_CONFIG_USE_FILE_PROPERTIES
/**
 * @brief Set a property of the checkbox bitmap.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] propertyKey Property key of the bitmap.
 * @param[in] propertyValue Property value of the bitmap.
 *
 */
void checkbox_setBmpProperty(Checkbox_s *p_checkbox, const uint8_t propertyKey, const uint8_t propertyValue)
{
    base_setBmpProperty(&p_checkbox->base, propertyKey, propertyValue);
}
#endif /* GUI_CONFIG_USE_FILE_PROPERTIES */

/**
 * @brief Set the bitmap alignment of the checkbox.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] horizontalAlignment Horizontal alignment of the bitmap.
 * @param[in] verticalAlignment Vertical alignment of the bitmap.
 *
 */
void checkbox_setBmpAlignment(Checkbox_s *p_checkbox, const GuiAlignment_e horizontalAlignment, const GuiAlignment_e verticalAlignment)
{
    p_checkbox->base.horizontalAlignment = (uint8_t)horizontalAlignment;
    p_checkbox->base.verticalAlignment = (uint8_t)verticalAlignment;
}


/**
 * @brief Set the horizontal alignment of the checkbox bitmap.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] horizontalAlignment Horizontal alignment of the bitmap.
 *
 */
void checkbox_setBmpHorizontalAlignment(Checkbox_s *p_checkbox, const GuiAlignment_e horizontalAlignment)
{
    p_checkbox->base.horizontalAlignment = (uint8_t)horizontalAlignment;
}


/**
 * @brief Set the vertical alignment of the checkbox bitmap.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] verticalAlignment Vertical alignment of the bitmap.
 *
 */
void checkbox_setBmpVerticalAlignment(Checkbox_s *p_checkbox, const GuiAlignment_e verticalAlignment)
{
    p_checkbox->base.verticalAlignment = (uint8_t)verticalAlignment;
}


/**
 * @brief Set the padding of the checkbox bitmap.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] left Left padding of the bitmap.
 * @param[in] top Top padding of the bitmap.
 * @param[in] right Right padding of the bitmap.
 * @param[in] bottom Bottom padding of the bitmap.
 *
 */
void checkbox_setBmpPadding(Checkbox_s *p_checkbox, const uint8_t left, const uint8_t top, const uint8_t right, const uint8_t bottom)
{
    p_checkbox->base.leftPadding = left;
    p_checkbox->base.rightPadding = right;
    p_checkbox->base.topPadding = top;
    p_checkbox->base.bottomPadding = bottom;
}


/**
 * @brief Set the left padding of the checkbox bitmap.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] padding Left padding of the bitmap.
 *
 */
void checkbox_setBmpLeftPadding(Checkbox_s *p_checkbox, const uint8_t padding)
{
    p_checkbox->base.leftPadding = padding;
}


/**
 * @brief Set the right padding of the checkbox bitmap.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] padding Right padding of the bitmap.
 *
 */
void checkbox_setBmpRightPadding(Checkbox_s *p_checkbox, const uint8_t padding)
{
    p_checkbox->base.rightPadding = padding;
}


/**
 * @brief Set the top padding of the checkbox bitmap.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] padding Top padding of the bitmap.
 *
 */
void checkbox_setBmpTopPadding(Checkbox_s *p_checkbox, const uint8_t padding)
{
    p_checkbox->base.topPadding = padding;
}


/**
 * @brief Set the bottom padding of the checkbox bitmap.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] padding Bottom padding of the bitmap.
 *
 */
void checkbox_setBmpBottomPadding(Checkbox_s *p_checkbox, const uint8_t padding)
{
    p_checkbox->base.bottomPadding = padding;
}


#if GUI_CONFIG_USE_ANCHOR
/**
* @brief Add a new anchor to the checkbox component.
* @param[in] p_checkbox Pointer to the checkbox component.
* @param[in] p_anchor Pointer to the anchor.
*
*/
void checkbox_addAnchor(Checkbox_s *p_checkbox, Anchor_s *p_anchor)
{
    base_addAnchor(&p_checkbox->base, p_anchor);
}


/**
* @brief Add a new anchor to the checkbox component. The anchor is initialized with default values.
* @param[in] p_checkbox Pointer to the checkbox component.
*
*/
void checkbox_addNewInitAnchor(Checkbox_s *p_checkbox)
{
    base_addNewInitAnchor(&p_checkbox->base);
}
#endif /* GUI_CONFIG_USE_ANCHOR */


#if GUI_CONFIG_USE_KEY_NAVIGATION
/**
 * @brief Add a KeyNavigation to the checkbox.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] p_keyNavigation Pointer to the KeyNavigation component.
 *
 */
void checkbox_addKeyNavigation(Checkbox_s *p_checkbox, KeyNavigation_s *p_keyNavigation)
{
    base_addKeyNavigation(&p_checkbox->base, p_keyNavigation);
}


/**
 * @brief Add a new KeyNavigation to the checkbox using dynamic memory, (gui_mem_malloc).
 * The new KeyNavigation struct is initialized.
 * @param[in] p_checkbox Pointer to the checkbox component.
 *
 */
void checkbox_addNewInitKeyNavigation(Checkbox_s *p_checkbox)
{
    base_addNewInitKeyNavigation(&p_checkbox->base);
}


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

#if GUI_CONFIG_USE_TOUCH
/**
 * @brief Add a Touch to the checkbox.
 * @param[in] p_checkbox Pointer to the checkbox component.
 * @param[in] p_touch Pointer to the Touch component.
 *
 */
void checkbox_addTouch(Checkbox_s *p_checkbox, Touch_s *p_touch)
{
    base_addTouch(&p_checkbox->base, p_touch);
}


/**
 * @brief Add a new Touch to the checkbox using dynamic memory, (gui_mem_malloc).
 * The new Touch struct is initialized.
 * @param[in] p_checkbox Pointer to the checkbox component.
 *
 */
void checkbox_addNewInitTouch(Checkbox_s *p_checkbox)
{
    base_addNewInitTouch(&p_checkbox->base);
}
#endif /* GUI_CONFIG_USE_TOUCH */


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


/*** end of file ***/
