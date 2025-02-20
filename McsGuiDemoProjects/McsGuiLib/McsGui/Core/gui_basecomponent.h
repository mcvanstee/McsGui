/** @file gui_basecomponent.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020 Marijn van Stee, all right reserved.
 */

#ifndef MCSGUI_CORE_GUI_BASECOMPONENT_H_
#define MCSGUI_CORE_GUI_BASECOMPONENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "gui_config.h"
#include "gui_event.h"
#include "gui_border_data.h"
#include "gui_fontdata.h"
#include "Utils/gui_action.h"
#include "Utils/gui_anchor.h"
#include "Utils/gui_keynavigation.h"
#include "Utils/gui_touch.h"


/** @enum GuiAlignment_e
 *
 *
 */
typedef enum
{
  Gui_Align_Left = 1,   /**/
  Gui_Align_Right = 2,  /**/
  Gui_Align_Center = 3, /**/
  Gui_Align_Top = 4,    /**/
  Gui_Align_Bottom = 5  /**/
} GuiAlignment_e;


typedef enum
{
    Gui_Visibility_Visible = 0,
    Gui_Visibility_Hidden = 1,
} GuiVisibility_e;


/** @enum BaseComponentType_e
 *
 *
 */
typedef enum
{
    BaseType_Parent = 0, /**< Component type to hold children components, only background can be drawn if transparent = false */
    BaseType_Image = 1,  /**< Component type to hold a Bitmap, background can be drawn if transparent = false */
    BaseType_Fill = 2,   /**< Component type to hold a Rectangle */
    BaseType_Text = 3    /**< Component type to hold text, background can be drawn if transparent = false */
} BaseComponentType_e;

typedef struct
{
    uint16_t x;
    uint16_t y;
} GuiPoint_s;

typedef struct
{
    uint16_t width;
    uint16_t height;
} GuiSize_s;

/** @struct BaseComponent_s
 *
 * @brief
 *
 */
typedef struct base_component_s
{
    BaseComponentType_e baseType;   /**< Type of the BaseComponent */
    uint16_t x;                     /**< X position */
    uint16_t y;                     /**< Y position */
    uint16_t width;                 /**< Width */
    uint16_t height;                /**< Height */
    uint32_t bmpKey;
#if GUI_CONFIG_USE_FILE_PROPERTIES
    uint8_t properties[GUI_CONFIG_NUMBER_OF_PROPERTIES];
#endif /* GUI_CONFIG_USE_FILE_PROPERTIES */
    char *p_text;                /**< String, pointer to dynamic text buffer */
    bool visible;                   /**< If visible component is displayed when onDisplay is called */
    void *p_data;                   /**< Depending on BaseType, NULL, FillData_s or TextData_s */
    bool transparent;
    Color_t background;
    void (*onDelete)(struct base_component_s *p_base);
    bool (*onHandleEvent)(struct base_component_s *p_base, const GuiEvent_s *p_event);
    void (*onDisplay)(struct base_component_s *p_base);
    struct base_component_s *p_parent;               /**< Pointer to the parent if added in a childlist */
    struct base_component_s *p_childList;            /**< Pointer to the list of child components */
    struct base_component_s *p_nextBaseComponent;    /**< Pointer to the next BaseComponent if used in a list */
    uint8_t horizontalAlignment;    /**< Horizontal alignment relative to parent if added as child */
    uint8_t verticalAlignment;      /**< Vertical alignment relative to parent if added as child */
    uint8_t leftPadding;
    uint8_t rightPadding;
    uint8_t topPadding;
    uint8_t bottomPadding;
    uint8_t memToFree;
    uint8_t id;
    GuiAction_s *p_action;
#if GUI_CONFIG_USE_ANCHOR
    GuiAnchor_s *p_anchor;
#endif /* GUI_CONFIG_USE_ANCHOR */
#if GUI_CONFIG_USE_KEY_NAVIGATION
    KeyNavigation_s *p_keyNavigation;
    bool focused; /**< Component has focus */
    void (*onFocusChanged)(struct base_component_s *p_base);
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */
#if GUI_CONFIG_USE_TOUCH
    Touch_s *p_touch;
#endif /* GUI_CONFIG_USE_TOUCH */
#if GUI_CONFIG_USE_ON_BEFORE_DISPLAY
    void (*onBeforeDisplay)(struct base_component_s *p_base);
#endif /* GUI_CONFIG_USE_ON_BEFORE_DISPLAY */
} BaseComponent_s;


void base_initParentComp(
        BaseComponent_s *p_base,
        void (*onDeleteComponent)(BaseComponent_s *p_baseToDelete));

void base_initImageComp(
        BaseComponent_s *p_base,
        void (*onDeleteComponent)(BaseComponent_s *p_baseToDelete));

void base_initFillComp(
        BaseComponent_s *p_base,
        BorderData_s *p_borderData,
        void (*onDeleteComponent)(BaseComponent_s *p_baseToDelete));

void base_initTextComp(
        BaseComponent_s *p_base,
        char *p_text,
        FontData_s *p_fontData,
        void (*onDeleteComponent)(BaseComponent_s *p_baseToDelete));

void base_clear(BaseComponent_s *p_base);
void base_clearChildList(BaseComponent_s *p_base);
void base_addChild(BaseComponent_s *p_parentBase, BaseComponent_s *p_childBase);
void base_display(void *p_component);

void base_setBmpKey(void *p_component, const uint32_t fileKey);
void base_setXPos(void *p_component, const uint16_t x);
void base_setYPos(void *p_component, const uint16_t y);
void base_setWidth(void *p_component, const uint16_t width);
void base_setHeight(void *p_component, const uint16_t height);
void base_setPosition(void *p_component, const uint16_t x, const uint16_t y);
void base_setDimensions(void *p_component, const uint16_t width, const uint16_t height);
void base_setSize(void *p_component, const uint16_t width, const uint16_t height);
void base_setProperty(void *p_component, const uint8_t propertyKey, const uint8_t propertyValue);
void base_setBackground(void *p_component, const Color_t color);
void base_setTransparent(void *p_component, const bool transparent);
void base_setVisibility(void *p_component, const GuiVisibility_e visibility);
void base_setVisible(void *p_component, const bool visible);
void base_setId(void *p_component, const uint8_t id);
void base_setOnDelete(void *p_component, void (*onDelete)(BaseComponent_s *p_base));
void base_setOnDisplay(void *p_component, void (*onDisplay)(BaseComponent_s *p_base));
void base_setOnHandleEvent(void *p_component, bool (*onHandleEvent)(BaseComponent_s *p_base, const GuiEvent_s *p_event));

GuiVisibility_e base_getVisibility(void *p_component);

bool base_iterateNextChild(BaseComponent_s *p_parentBase, BaseComponent_s **p_iterator);
void base_executeForEachChild(BaseComponent_s *p_parentBase, void(*functionToExecute)(void *p_childBase));

/* BMP Alignment */
void base_setAlignment(void *p_component, const GuiAlignment_e horizontal, const GuiAlignment_e vertical);
void base_setHorizontalAlignment(void *p_component, const GuiAlignment_e alignment);
void base_setVerticalAlignment(void *p_component, const GuiAlignment_e alignment);

void base_setPadding(void *p_component, const uint8_t left, const uint8_t top, const uint8_t right, const uint8_t bottom);
void base_setLeftPadding(void *p_component, const uint8_t padding);
void base_setTopPadding(void *p_component, const uint8_t padding);
void base_setRightPadding(void *p_component, const uint8_t padding);
void base_setBottomPadding(void *p_component, const uint8_t padding);

#if GUI_CONFIG_USE_ON_BEFORE_DISPLAY
void base_setOnBeforeDisplay(void *p_component, void (*onBeforeDisplay)(BaseComponent_s *p_base));
#endif /* GUI_CONFIG_USE_ON_BEFORE_DISPLAY */

#if GUI_CONFIG_USE_ANCHOR
void base_addAnchor(void *p_component, GuiAnchor_s *p_anchor);
void base_addNewInitAnchor(void *p_component);
#endif /* GUI_CONFIG_USE_ANCHOR */

#if GUI_CONFIG_USE_KEY_NAVIGATION
void base_addKeyNavigation(void *p_component, KeyNavigation_s *p_keyNavigation);
void base_addNewInitKeyNavigation(void *p_component);
bool base_setActiveFocus(void *p_component);
void base_setFocus(void *p_component, const bool focus);
void base_setFocusNotifyChanged(void *p_component, const bool focus);
void base_setOnFocusChanged(void *p_component, void (*onFocusChanged)(BaseComponent_s *p_base));
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

#if GUI_CONFIG_USE_TOUCH
void base_addTouch(void *p_component, Touch_s *p_touch);
void base_addNewInitTouch(void *p_component);
#endif /* GUI_CONFIG_USE_TOUCH */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_CORE_GUI_BASECOMPONENT_H_ */


/*** end of file ***/
