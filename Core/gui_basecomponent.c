#include "Core/gui_basecomponent.h"

#include <stddef.h>
#include <string.h>

#include "Graphics/gui_graphics.h"
#include "Utils/gui_memory.h"

#define BASE_FREE_KEYNAV_FLAG 0x01U
#define BASE_FREE_TOUCH_FLAG 0x02U
#define BASE_FREE_ANCHOR_FLAG 0x04U


/* Private function declarations */
static void base_init(BaseComponent_s *p_base, BaseComponentType_e baseType,
        void (*onDeleteComponent)(BaseComponent_s *p_baseToDelete));
static void base_addBorderData(BaseComponent_s *p_base, BorderData_s *p_borderData);
static void base_addFontData(BaseComponent_s *p_base, FontData_s *p_fontData);


/**
 * @brief Initialize the BaseComponent_s to default values.
 * @param[in] p_base A pointer to the BaseComponent_s to be initialized.
 * @param[in] baseType Type of the BaseComponent_s.
 * @param[in] onDeleteComponent Callback function, called when component is deleted.
 *
 */
static void base_init(
        BaseComponent_s *p_base,
        BaseComponentType_e baseType,
        void (*onDeleteComponent)(BaseComponent_s *p_baseToDelete))
{
    p_base->baseType = baseType;
    p_base->x = 0;
    p_base->y = 0;
    p_base->width = 0;
    p_base->height = 0;
    p_base->bmpKey = 0;
#if GUI_CONFIG_USE_FILE_PROPERTIES
    for (uint32_t i = 0; i < GUI_CONFIG_NUMBER_OF_PROPERTIES; i++)
    {
    	p_base->properties[i] = 0;
    }
#endif /* GUI_CONFIG_USE_FILE_PROPERTIES */
    p_base->visible = true;
    p_base->p_data = NULL;
    p_base->p_text = NULL;
    p_base->transparent = true;
    p_base->background = 0;
    p_base->onDelete = onDeleteComponent;
    p_base->onHandleEvent = NULL;
    p_base->onDisplay = graphics_displayComponent;
    p_base->p_parent = NULL;
    p_base->p_childList = NULL;
    p_base->p_nextBaseComponent = NULL;
    p_base->horizontalAlignment = Gui_Align_Center;
    p_base->verticalAlignment = Gui_Align_Center;
    p_base->leftPadding = 0;
    p_base->topPadding = 0;
    p_base->rightPadding = 0;
    p_base->bottomPadding = 0;
    p_base->memToFree = 0;
    p_base->id = 0;
    p_base->p_action = NULL;
#if GUI_CONFIG_USE_ANCHOR
    p_base->p_anchor = NULL;
#endif /* GUI_CONFIG_USE_ANCHOR */
#if GUI_CONFIG_USE_KEY_NAVIGATION
    p_base->p_keyNavigation = NULL;
    p_base->focused = false;
    p_base->onFocusChanged = NULL;
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */
#if GUI_CONFIG_USE_TOUCH
    p_base->p_touch = NULL;
#endif /* GUI_CONFIG_USE_TOUCH */
#if GUI_CONFIG_USE_ON_BEFORE_DISPLAY
    p_base->onBeforeDisplay = NULL;
#endif /* GUI_CONFIG_USE_ON_BEFORE_DISPLAY */
}

void base_initParentComp(
        BaseComponent_s *p_base,
        void (*onDeleteComponent)(BaseComponent_s *p_baseToDelete))
{
    base_init(p_base, BaseType_Parent, onDeleteComponent);
}


/**
 * @brief Initialize the Base to Image base-component which is able to draw a BMP on the display.
 * @param[in] p_base Pointer to the BaseComponent_s.
 * @param[in] p_fillData Pointer to the FillData_s.
 * @param[in] onDeleteComponent Pointer to the Callback function called when the base is deleted/cleard.
 *
 */
void base_initImageComp(
        BaseComponent_s *p_base,
        void (*onDeleteComponent)(BaseComponent_s *p_baseToDelete))
{
    base_init(p_base, BaseType_Image, onDeleteComponent);
}


/**
 * @brief Initialize the Base to Fill base-component which is able to draw a rectangle on the display.
 * @param[in] p_base Pointer to the BaseComponent_s.
 * @param[in] p_fillData Pointer to the FillData_s.
 * @param[in] onDeleteComponent Pointer to the Callback function called when the base is deleted/cleard.
 *
 */
void base_initFillComp(
        BaseComponent_s *p_base,
        BorderData_s *p_borderData,
        void (*onDeleteComponent)(BaseComponent_s *p_baseToDelete))
{
    base_init(p_base, BaseType_Fill, onDeleteComponent);
    base_addBorderData(p_base, p_borderData);
}


/**
 * @brief Initialize the Base to Text base-component which is able to draw fonts on the display.
 * @param[in] p_base Pointer to the BaseComponent_s.
 * @param[in] p_fontData Pointer to the FontData_s.
 * @param[in] onDeleteComponent Pointer to the Callback function called when the base is deleted/cleard.
 *
 */
void base_initTextComp(
        BaseComponent_s *p_base,
        char *p_text,
        FontData_s *p_fontData,
        void (*onDeleteComponent)(BaseComponent_s *p_baseToDelete))
{
    base_init(p_base, BaseType_Text, onDeleteComponent);
    base_addFontData(p_base, p_fontData);
    p_base->p_text = p_text;
}


/**
 * @brief Add BorderData to the base, if the BaseType is Fill.
 * @param[in] p_base Pointer to the BaseComponent_s.
 * @param[in] p_borderData Pointer to the BorderData_s.
 *
 */
static void base_addBorderData(
        BaseComponent_s *p_base, BorderData_s *p_borderData)
{
    if (BaseType_Fill != p_base->baseType)
    {
        return;
    }

    p_base->p_data = p_borderData;
}


/**
 * @brief Add FontData to the base, if the BaseType is Text.
 * @param[in] p_base Pointer to the BaseComponent_s.
 * @param[in] p_fontData Pointer to the FontData_s.
 *
 */
static void base_addFontData(
        BaseComponent_s *p_base, FontData_s *p_fontData)
{
    if (BaseType_Text != p_base->baseType)
    {
        return;
    }

    p_base->p_data = p_fontData;
}


/**
 * @brief Add Child component to the parent.
 * @param[in] p_parentBase Pointer to the BaseComponent_s of the parent.
 * @param[in] p_childBase Pointer to the BaseComponent_s of the child added to the parent.
 *
 */
void base_addChild(
        BaseComponent_s *p_parentBase, BaseComponent_s *p_childBase)
{
    if (NULL == p_parentBase->p_childList)
    {
    	p_childBase->p_parent = p_parentBase;
        p_parentBase->p_childList = p_childBase;

        return;
    }

    BaseComponent_s *p_iterator = p_parentBase->p_childList;
    while (NULL != p_iterator->p_nextBaseComponent)
    {
        p_iterator = p_iterator->p_nextBaseComponent;
    }

    p_childBase->p_parent = p_parentBase;
    p_iterator->p_nextBaseComponent = p_childBase;
}


void base_display(void *p_component)
{
	BaseComponent_s *p_base = (BaseComponent_s *)p_component;
	p_base->onDisplay(p_base);
}

void base_setBmpKey(
		void *p_component, const uint32_t fileKey)
{
	BaseComponent_s *p_base = (BaseComponent_s *)p_component;
	p_base->bmpKey = fileKey;
}

/**
 * @brief Set x position of the base.
 * @param[in] p_component Pointer to the (base) component.
 * @param[in] x x-position.
 *
 */
void base_setXPos(
        void *p_component, const uint16_t x)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->x = x;

    if (NULL != p_base->p_touch)
    {
    	p_base->p_touch->x = x;
    }
}


/**
 * @brief Set y position of the base.
 * @param[in] p_component Pointer to the (base) component.
 * @param[in] y y-position.
 *
 */
void base_setYPos(
        void *p_component, const uint16_t y)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->y = y;

    if (NULL != p_base->p_touch)
    {
    	p_base->p_touch->y = y;
    }
}


/**
 * @brief Set width of the base.
 * @param[in] p_component Pointer to the (base) component.
 * @param[in] width Width.
 *
 */
void base_setWidth(
        void *p_component, const uint16_t width)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->width = width;

    if (NULL != p_base->p_touch)
    {
    	p_base->p_touch->width = width;
    }
}


/**
 * @brief Set height of the base.
 * @param[in] p_component Pointer to the (base) component.
 * @param[in] height Height.
 *
 */
void base_setHeight(
        void *p_component, const uint16_t height)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->height = height;

    if (NULL != p_base->p_touch)
    {
    	p_base->p_touch->height = height;
    }
}


/**
 * @brief Set the position of the base.
 * @param[in] p_component Pointer to the (base) component.
 * @param[in] x x-position.
 * @param[in] y y-position.
 *
 */
void base_setPosition(
        void *p_component, const uint16_t x, const uint16_t y)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->x = x;
    p_base->y = y;

    if (NULL != p_base->p_touch)
    {
    	p_base->p_touch->x = x;
    	p_base->p_touch->y = y;
    }
}


/**
 * @brief Set the Dimensions of the base.
 * @param[in] p_component Pointer to the (base) component.
 * @param[in] width Width.
 * @param[in] height Height.
 *
 */
void base_setDimensions(
        void *p_component, const uint16_t width, const uint16_t height)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->width = width;
    p_base->height = height;

    if (NULL != p_base->p_touch)
    {
    	p_base->p_touch->width = width;
    	p_base->p_touch->height = height;
    }
}


/**
 * @brief Set the Dimensions of the base.
 * @param[in] p_component Pointer to the (base) component.
 * @param[in] width Width.
 * @param[in] height Height.
 *
 */
void base_setSize(void *p_component, const uint16_t width, const uint16_t height)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->width = width;
    p_base->height = height;

    if (NULL != p_base->p_touch)
    {
        p_base->p_touch->width = width;
        p_base->p_touch->height = height;
    }
}


void base_setProperty(void *p_component, const uint8_t propertyKey, const uint8_t propertyValue)
{
	if (GUI_CONFIG_NUMBER_OF_PROPERTIES <= propertyKey)
	{
		return;
	}

	BaseComponent_s *p_base = (BaseComponent_s *)p_component;
	p_base->properties[propertyKey] = propertyValue;
}


/**
 * @brief Set the background color of the base.
 * @param[in] p_component Pointer the to (base) component.
 * @param[in] color background color.
 *
 */
void base_setBackground(
        void *p_component, const Color_t color)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->transparent = false;
    p_base->background = color;
}

void base_setTransparent(void *p_component, const bool transparent)
{
    BaseComponent_s *p_base = (BaseComponent_s*) p_component;
    p_base->transparent = transparent;
}

void base_setVisibility(void *p_component, const GuiVisibility_e visibility)
{
	BaseComponent_s *p_base = (BaseComponent_s *)p_component;
	p_base->visible = (visibility == Gui_Visibility_Visible);
}

void base_setVisible(void *p_component, const bool visible)
{
	BaseComponent_s *p_base = (BaseComponent_s *)p_component;
	p_base->visible = visible;
}

void base_setId(void *p_component, const uint8_t id)
{
    if (id > 0)
    {
        BaseComponent_s *p_base = (BaseComponent_s*) p_component;
        p_base->id = id;
    }
}

void base_setOnDelete(void *p_component, void (*onDelete)(BaseComponent_s *p_base))
{
    BaseComponent_s *p_base = (BaseComponent_s*) p_component;
    p_base->onDelete = onDelete;
}

void base_setOnDisplay(void *p_component, void (*onDisplay)(BaseComponent_s *p_base))
{
    BaseComponent_s *p_base = (BaseComponent_s*) p_component;
    p_base->onDisplay = onDisplay;
}

void base_setOnHandleEvent(void *p_component, bool (*onHandleEvent)(BaseComponent_s *p_base, const GuiEvent_s *p_event))
{
    BaseComponent_s *p_base = (BaseComponent_s*) p_component;
    p_base->onHandleEvent = onHandleEvent;
}

GuiVisibility_e base_getVisibility(void *p_component)
{
    BaseComponent_s *p_base = (BaseComponent_s*) p_component;
    return (p_base->visible) ? Gui_Visibility_Visible : Gui_Visibility_Hidden;
}

bool base_iterateNextChild(BaseComponent_s *p_parentBase, BaseComponent_s **p_iterator)
{
	if (p_parentBase->p_childList == NULL)
	{
		*p_iterator = NULL;

		return false;
	}

	if (*p_iterator == NULL)
	{
		*p_iterator = p_parentBase->p_childList;

		return true;
	}

	BaseComponent_s *p_temp = *p_iterator;
	*p_iterator = p_temp->p_nextBaseComponent;

	return *p_iterator != NULL;
}

void base_executeForEachChild(BaseComponent_s *p_parentBase, void(*functionToExecute)(void *p_childBase))
{
	BaseComponent_s *p_iterator = p_parentBase->p_childList;
	while (p_iterator != NULL)
	{
		functionToExecute(p_iterator);
		p_iterator = p_iterator->p_nextBaseComponent;
	}
}


/**
 * @brief Set the horizontal and vertical alignment.
 * @param[in] p_component Pointer the to (base) component.
 * @param[in] horizontal alignment.
 * @param[in] vertical alignment.
 *
 */
void base_setAlignment(
        void *p_component, const GuiAlignment_e horizontal, const GuiAlignment_e vertical)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->horizontalAlignment = (uint8_t)horizontal;
    p_base->verticalAlignment = (uint8_t)vertical;
}


/**
 * @brief Set the horizontal alignment.
 * @param[in] p_component Pointer the to (base) component.
 * @param[in] alignment.
 *
 */
void base_setHorizontalAlignment(
        void *p_component, const GuiAlignment_e alignment)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->horizontalAlignment = (uint8_t)alignment;
}


/**
 * @brief Set the vertical alignment.
 * @param[in] p_component Pointer the to (base) component.
 * @param[in] alignment.
 *
 */
void base_setVerticalAlignment(
        void *p_component, const GuiAlignment_e alignment)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->verticalAlignment = (uint8_t)alignment;
}


/**
 * @brief Set the padding.
 * @param[in] p_component Pointer the to (base) component.
 * @param[in] left padding.
 * @param[in] top padding.
 * @param[in] right padding.
 * @param[in] bottom padding.
 *
 */
void base_setPadding(
        void *p_component,
        const uint8_t left, const uint8_t top,
        const uint8_t right, const uint8_t bottom)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->leftPadding = left;
    p_base->topPadding = top;
    p_base->rightPadding = right;
    p_base->bottomPadding = bottom;
}

void base_setLeftPadding(
        void *p_component, const uint8_t padding)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->leftPadding = padding;
}

void base_setTopPadding(
        void *p_component, const uint8_t padding)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->topPadding = padding;
}

void base_setRightPadding(
        void *p_component, const uint8_t padding)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->rightPadding = padding;
}

void base_setBottomPadding(
        void *p_component, const uint8_t padding)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->bottomPadding = padding;
}


#if GUI_CONFIG_USE_ON_BEFORE_DISPLAY
/*
 * @brief Set the onBeforeDisplay callback function, called just before the graphics instruction is added to the buffer.
 * @param[in] p_component Pointer the to (base) component.
 * @param[in] onBeforeDisplay Pointer to the callback function.
 *
 */
void base_setOnBeforeDisplay(
        void *p_component, void (*onBeforeDisplay)(BaseComponent_s *p_base))
{
    BaseComponent_s *p_baseComp = (BaseComponent_s *)p_component;
    p_baseComp->onBeforeDisplay = onBeforeDisplay;
}
#endif /* GUI_CONFIG_USE_ON_BEFORE_DISPLAY */


#if GUI_CONFIG_USE_ANCHOR
/**
 * @brief Add Anchor to the base.
 * @param[in] p_base Pointer to the BaseComponent_s the Anchor is added to.
 * @param[in] p_anchor Pointer to the GuiAnchor_s.
 *
 * @warning Make sure the GuiAnchor_s is initialized.
 *
 */
void base_addAnchor(void *p_component, GuiAnchor_s *p_anchor)
{
    BaseComponent_s *p_base = (BaseComponent_s*) p_component;
    p_base->p_anchor = p_anchor;
}


/**
 * @brief Add a new Anchor to the base using dynamic memory, (gui_mem_malloc).
 * The new Anchor struct is initialized.
 * @param[in] p_base Pointer to the BaseComponent_s the Anchor is added to.
 *
 */
void base_addNewInitAnchor(void *p_component)
{
	BaseComponent_s *p_base = (BaseComponent_s*) p_component;
    p_base->p_anchor = anchor_new();
    p_base->memToFree |= BASE_FREE_ANCHOR_FLAG;
    anchor_init(p_base->p_anchor);
}
#endif /* GUI_CONFIG_USE_ANCHOR */


#if GUI_CONFIG_USE_KEY_NAVIGATION
/**
 * @brief Add KeyNavigation_s to the base.
 * @param[in] p_base Pointer to the BaseComponent_s the KeyNavigation_s is added to.
 * @param[in] p_keyNavigation Pointer to the KeyNavigation_s.
 *
 * @warning Make sure the KeyNavigation_s is initialized.
 *
 */
void base_addKeyNavigation(
        void *p_component, KeyNavigation_s *p_keyNavigation)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->p_keyNavigation = p_keyNavigation;
}


/**
 * @brief Add a new KeyNavigation_s to the base using dynamic memory, (gui_mem_malloc).
 * The new KeyNavigation_s struct is initialized.
 * @param[in] p_base Pointer to the BaseComponent_s the KeyNavigation_s is added to.
 *
 */
void base_addNewInitKeyNavigation(
        void *p_component)
{
	BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->p_keyNavigation = keynav_new();
    p_base->memToFree |= BASE_FREE_KEYNAV_FLAG;
    keynav_init(p_base->p_keyNavigation);
}


/**
 * @brief Set the focus of the base to true.
 * @param[in] p_base Pointer to the BaseComponent_s.
 * @return true if the BaseComponent_s has KeyNavigation_s else false.
 *
 */
bool base_setActiveFocus(void *p_component)
{
	BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    if (NULL != p_base->p_keyNavigation)
    {
        base_setFocusNotifyChanged(p_base, true);

        return true;
    }

    return false;
}


/**
 * @brief Set the focus of the base.
 * @param[in] p_base Pointer to the BaseComponent_s.
 * @param[in] focus Boolean sets the focus.
 *
 */
void base_setFocus(void *p_component, const bool focus)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->focused = focus;
}


/**
 * @brief Set the focus of the base, and calls the onFocusChanged callback function.
 * @param[in] p_base Pointer to the BaseComponent_s.
 * @param[in] focus Boolean sets the focus.
 *
 */
void base_setFocusNotifyChanged(void *p_component, const bool focus)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->focused = focus;

    if (NULL != p_base->onFocusChanged)
    {
        p_base->onFocusChanged(p_base);
    }
}

void base_setOnFocusChanged(void *p_component, void (*onFocusChanged)(BaseComponent_s *p_base))
{
	BaseComponent_s *p_componentBase = (BaseComponent_s *)p_component;
	p_componentBase->onFocusChanged = onFocusChanged;
}

#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

#if GUI_CONFIG_USE_TOUCH
/**
 * @brief Add Touch_s to the base.
 * @param[in] p_base Pointer to the BaseComponent_s the Touch_s is added to.
 * @param[in] p_touch Pointer to the Touch_s.
 *
 * @warning Make sure the Touch_s is initialized.
 *
 */
void base_addTouch(
        void *p_component, Touch_s *p_touch)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->p_touch = p_touch;
    touch_setTouchArea(p_touch, p_base->x, p_base->y, p_base->width, p_base->height);
}


/**
 * @brief Add a new Touch_s to the base using dynamic memory, (gui_mem_malloc).
 * The new Touch_s struct is initialized.
 * @param[in] p_base Pointer to the BaseComponent_s the Touch_s is added to.
 *
 */
void base_addNewInitTouch(void *p_component)
{
	BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->p_touch = touch_new();
    p_base->memToFree |= BASE_FREE_TOUCH_FLAG;
    touch_init_1(p_base->p_touch, p_base->x, p_base->y, p_base->width, p_base->height);
}

#endif /* GUI_CONFIG_USE_TOUCH */

/**
 * @brief Clear the BaseComponet_s.
 * @param[in] p_base Pointer to the BaseComponent_s
 *
 */
void base_clear(
        BaseComponent_s *p_base)
{
    base_clearChildList(p_base);

#if GUI_CONFIG_USE_ANCHOR
    if (BASE_FREE_ANCHOR_FLAG == (p_base->memToFree & BASE_FREE_ANCHOR_FLAG))
    {
        anchor_delete(p_base->p_anchor);
        p_base->p_anchor = NULL;
    }
#endif /* GUI_CONFIG_USE_ANCHOR */

#if GUI_CONFIG_USE_KEY_NAVIGATION
    if (BASE_FREE_KEYNAV_FLAG == (p_base->memToFree & BASE_FREE_KEYNAV_FLAG))
    {
        keynav_delete(p_base->p_keyNavigation);
        p_base->p_keyNavigation = NULL;
    }
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

#if GUI_CONFIG_USE_TOUCH
    if (BASE_FREE_TOUCH_FLAG == (p_base->memToFree & BASE_FREE_TOUCH_FLAG))
    {
        touch_delete(p_base->p_touch);
        p_base->p_touch = NULL;
    }
#endif /* GUI_CONFIG_USE_TOUCH */

    if (p_base->p_action != NULL)
    {
    	gui_disconnectAction(p_base);
    }

#if !GUI_USE_DYNAMIC_MEMORY
    memset(p_base, 0, sizeof(BaseComponent_s));
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

void base_clearChildList(
        BaseComponent_s *p_base)
{
    if (NULL == p_base->p_childList)
    {
        return;
    }

    BaseComponent_s *p_iterator = p_base->p_childList;
    while (p_iterator != NULL)
    {
        BaseComponent_s *p_toDelete = p_iterator;
        p_iterator = p_iterator->p_nextBaseComponent;
        p_toDelete->onDelete(p_toDelete);
    }

    p_base->p_childList = NULL;
}

/*** end of file ***/
