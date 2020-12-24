#include "McsGui/Core/gui_basecomponent.h"

#include <stddef.h>
#include <string.h>

#include "McsGui/Graphics/gui_graphics.h"
#include "McsGui/Utils/gui_memory.h"

#define BASE_FREE_KEYNAV_FLAG 0x01U
#define BASE_FREE_TOUCH_FLAG 0x02U


/* Private function declarations */
static void base_init(BaseComponent_s *p_base, BaseComponentType_e baseType,
        void (*onDeleteComponent)(BaseComponent_s *p_baseToDelete));
static void base_addFillData(BaseComponent_s *p_base, FillData_s *p_fillData);
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
    p_base->xPos = 0;
    p_base->yPos = 0;
    p_base->width = 0;
    p_base->height = 0;
    p_base->visible = true;
    p_base->p_bmpName = NULL;
    p_base->p_data = NULL;
    p_base->transparent = true;
    p_base->background = 0;
    p_base->onDelete = onDeleteComponent;
    p_base->onHandleEvent = NULL;
    p_base->onDisplay = graphics_displayComponent;
    p_base->p_parent = NULL;
    p_base->p_childList = NULL;
    p_base->p_nextBaseComponent = NULL;
#if GUI_CONFIG_USE_ALIGNMENT
    p_base->horizontalAlignment = AlignCenter;
    p_base->verticalAlignment = AlignCenter;
#if GUI_CONFIG_USE_MARGIN
    p_base->leftMargin = 0;
    p_base->topMargin = 0;
    p_base->rightMargin = 0;
    p_base->bottomMargin = 0;
#endif /* GUI_CONFIG_USE_MARGIN */
#endif /* GUI_CONFIG_USE_ALIGNMENT */
    p_base->memToFree = 0;
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
        FillData_s *p_fillData,
        void (*onDeleteComponent)(BaseComponent_s *p_baseToDelete))
{
    base_init(p_base, BaseType_Fill, onDeleteComponent);
    base_addFillData(p_base, p_fillData);
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
        FontData_s *p_fontData,
        void (*onDeleteComponent)(BaseComponent_s *p_baseToDelete))
{
    base_init(p_base, BaseType_Text, onDeleteComponent);
    base_addFontData(p_base, p_fontData);
}


/**
 * @brief Add FillData to the base, if the BaseType is Fill.
 * @param[in] p_base Pointer to the BaseComponent_s.
 * @param[in] p_fillData Pointer to the FillData_s.
 *
 */
static void base_addFillData(
        BaseComponent_s *p_base, FillData_s *p_fillData)
{
    if (BaseType_Fill != p_base->baseType)
    {
        return;
    }

    p_base->p_data = p_fillData;
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


/**
 * @brief Set x position of the base.
 * @param[in] p_component Pointer to the (base) component.
 * @param[in] xPos x position.
 *
 */
void base_setXPos(
        void *p_component, const uint16_t xPos)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->xPos = xPos;
}


/**
 * @brief Set y position of the base.
 * @param[in] p_component Pointer to the (base) component.
 * @param[in] yPos y position.
 *
 */
void base_setYPos(
        void *p_component, const uint16_t yPos)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->yPos = yPos;
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
}


/**
 * @brief Set the position of the base.
 * @param[in] p_component Pointer to the (base) component.
 * @param[in] xPos x position.
 * @param[in] yPos y position.
 *
 */
void base_setPosition(
        void *p_component, const uint16_t xPos, const uint16_t yPos)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->xPos = xPos;
    p_base->yPos = yPos;
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
}


/**
 * @brief Set the bmp name of the base.
 * @param[in] p_component Pointer the to (base) component.
 * @param[in] p_bmpName Pointer to the string holding the bmp name.
 *
 */
void base_setBmp(
        void *p_component, const char *p_bmpName)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;

#if GUI_USE_DYNAMIC_MEMORY
    if (NULL != p_base->p_bmpName)
    {
        size_t sizeOfMemToFree = strlen(p_base->p_bmpName) + 1;
        gui_mem_free(p_base->p_bmpName, sizeOfMemToFree);
    }

    size_t bmpNameSize = strlen(p_bmpName) + 1;
    p_base->p_bmpName = gui_mem_malloc(bmpNameSize);
    (void)strncpy(p_base->p_bmpName, p_bmpName, bmpNameSize);
#else
    if (NULL != p_base->p_bmpName)
    {
        (void)strcpy(p_base->p_bmpName, p_bmpName);
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
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


#if GUI_CONFIG_USE_ALIGNMENT

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


#if GUI_CONFIG_USE_MARGIN
/**
 * @brief Set the margin.
 * @param[in] p_component Pointer the to (base) component.
 * @param[in] left margin.
 * @param[in] top margin.
 * @param[in] right margin.
 * @param[in] bottom margin.
 *
 */
void base_setMargin(
        void *p_component,
        const uint8_t left, const uint8_t top,
        const uint8_t right, const uint8_t bottom)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->leftMargin = left;
    p_base->topMargin = top;
    p_base->rightMargin = right;
    p_base->bottomMargin = bottom;
}

void base_setLeftMargin(
        void *p_component, const uint8_t margin)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->leftMargin = margin;
}

void base_setTopMargin(
        void *p_component, const uint8_t margin)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->topMargin = margin;
}

void base_setRightMargin(
        void *p_component, const uint8_t margin)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->rightMargin = margin;
}

void base_setBottomMargin(
        void *p_component, const uint8_t margin)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    p_base->bottomMargin = margin;
}

#endif /* GUI_CONFIG_USE_MARGIN */

#endif /* GUI_CONFIG_USE_ALIGNMENT */

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


#if GUI_USE_DYNAMIC_MEMORY
/**
 * @brief Add a new KeyNavigation_s to the base using dynamic memory, (gui_mem_malloc).
 * The new KeyNavigation_s struct is initialized.
 * @param[in] p_base Pointer to the BaseComponent_s the KeyNavigation_s is added to.
 *
 */
void base_addNewInitKeyNavigation(
        BaseComponent_s *p_base)
{
    p_base->p_keyNavigation = keynav_new();
    p_base->memToFree |= BASE_FREE_KEYNAV_FLAG;
    keynav_init(p_base->p_keyNavigation);
}
#endif /* GUI_USE_DYNAMIC_MEMORY */


/**
 * @brief Set the focus of the base to true.
 * @param[in] p_base Pointer to the BaseComponent_s.
 * @return true if the BaseComponent_s has KeyNavigation_s else false.
 *
 */
bool base_setActiveFocus(
        BaseComponent_s *p_base)
{
    if (NULL != p_base->p_keyNavigation)
    {
        base_setFocus(p_base, true);

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
void base_setFocus(
        BaseComponent_s *p_base, const bool focus)
{
    p_base->focused = focus;

    if (NULL != p_base->onFocusChanged)
    {
        p_base->onFocusChanged(p_base);
    }
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
}


#if GUI_USE_DYNAMIC_MEMORY
/**
 * @brief Add a new Touch_s to the base using dynamic memory, (gui_mem_malloc).
 * The new Touch_s struct is initialized.
 * @param[in] p_base Pointer to the BaseComponent_s the Touch_s is added to.
 *
 */
void base_addNewInitTouch(
        BaseComponent_s *p_base)
{
    p_base->p_touch = touch_new();
    p_base->memToFree |= BASE_FREE_TOUCH_FLAG;
    touch_init(p_base->p_touch);
}
#endif /* GUI_USE_DYNAMIC_MEMORY */

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
    base_clearBmp(p_base);

#if GUI_USE_DYNAMIC_MEMORY
#if GUI_CONFIG_USE_KEY_NAVIGATION
    if (BASE_FREE_KEYNAV_FLAG == (p_base->memToFree & BASE_FREE_KEYNAV_FLAG))
    {
        keynav_delete(p_base->p_keyNavigation);
    }
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

#if GUI_CONFIG_USE_TOUCH
    if (BASE_FREE_TOUCH_FLAG == (p_base->memToFree & BASE_FREE_TOUCH_FLAG))
    {
        touch_delete(p_base->p_touch);
    }
#endif /* GUI_CONFIG_USE_TOUCH */

#else

#if GUI_CONFIG_USE_KEY_NAVIGATION
    p_base->p_keyNavigation = NULL;
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

#if GUI_CONFIG_USE_TOUCH
    p_base->p_touch = NULL;
#endif /* GUI_CONFIG_USE_TOUCH */

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

void base_clearBmp(
        const BaseComponent_s *p_base)
{
    if (NULL == p_base->p_bmpName)
    {
        return;
    }

#if GUI_USE_DYNAMIC_MEMORY
    size_t sizeOfMemToFree = strlen(p_base->p_bmpName) + 1;
    gui_mem_free(p_base->p_bmpName, sizeOfMemToFree);
#else
    p_base->p_bmpName[0] = '\0';
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/*** end of file ***/
