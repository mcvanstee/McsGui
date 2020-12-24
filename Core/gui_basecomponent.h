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

#include "McsGui/gui_config.h"
#include "gui_event.h"
#include "gui_filldata.h"
#include "gui_fontdata.h"
#include "McsGui/Utils/gui_keynavigation.h"
#include "McsGui/Utils/gui_touch.h"


/** @enum GuiAlignment_e
 *
 *
 */
typedef enum
{
  AlignLeft = 1,   /**/
  AlignRight = 2,  /**/
  AlignCenter = 3, /**/
  AlignTop = 4,    /**/
  AlignBottom = 5  /**/
} GuiAlignment_e;


/** @enum BaseComponentType_e
 *
 *
 */
typedef enum
{
    BaseType_Parent = 0, /**< Component type to hold children components, only background can be drawn if transparent = true */
    BaseType_Image = 1,  /**< Component type to hold a Bitmap, background can be drawn if transparent = true */
    BaseType_Fill = 2,   /**< Component type to hold a Rectangle */
    BaseType_Text = 3    /**< */
} BaseComponentType_e;

typedef struct text_data_s
{
    uint8_t fontId;
    uint8_t fontFocused;
} TextData_s;


/** @struct BaseComponent_s
 *
 * @brief
 *
 */
typedef struct base_component_s
{
    BaseComponentType_e baseType;   /**< Type of the BaseComponent */
    uint16_t xPos;                  /**< X position */
    uint16_t yPos;                  /**< Y position */
    uint16_t width;                 /**< Width */
    uint16_t height;                /**< Height */
    bool visible;                   /**< If visible component is displayed when onDisplay is called */
    char *p_bmpName;                /**< String, bitmap name */
    void *p_data;                   /**< Depending on BaseType, NULL, FillData_s or TextData_s */
    bool transparent;
    Color_t background;
    void (*onDelete)(struct base_component_s *p_base);
    bool (*onHandleEvent)(struct base_component_s *p_base, const GuiEvent_s *p_event);
    void (*onDisplay)(struct base_component_s *p_base);
    struct base_component_s *p_parent;               /**< Pointer to the parent if added in a childlist */
    struct base_component_s *p_childList;            /**< Pointer to the list of child components */
    struct base_component_s *p_nextBaseComponent;    /**< Pointer to the next BaseComponent if used in a list */
#if GUI_CONFIG_USE_ALIGNMENT
    uint8_t horizontalAlignment;    /**< Horizontal alignment relative to parent if added as child */
    uint8_t verticalAlignment;      /**< Vertical alignment relative to parent if added as child */
#if GUI_CONFIG_USE_MARGIN
    uint8_t leftMargin;
    uint8_t topMargin;
    uint8_t rightMargin;
    uint8_t bottomMargin;
#endif /* GUI_CONFIG_USE_MARGIN */
#endif /* GUI_CONFIG_USE_ALIGNMENT */
    uint8_t memToFree;
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
        FillData_s *p_fillData,
        void (*onDeleteComponent)(BaseComponent_s *p_baseToDelete));

void base_initTextComp(
        BaseComponent_s *p_base,
        FontData_s *p_fontData,
        void (*onDeleteComponent)(BaseComponent_s *p_baseToDelete));

void base_clear(BaseComponent_s *p_base);
void base_clearChildList(BaseComponent_s *p_base);
void base_clearBmp(const BaseComponent_s *p_base);
void base_addChild(BaseComponent_s *p_parentBase, BaseComponent_s *p_childBase);

void base_setXPos(void *p_component, const uint16_t xPos);
void base_setYPos(void *p_component, const uint16_t yPos);
void base_setWidth(void *p_component, const uint16_t width);
void base_setHeight(void *p_component, const uint16_t height);
void base_setPosition(void *p_component, const uint16_t xPos, const uint16_t yPos);
void base_setDimensions(void *p_component, const uint16_t width, const uint16_t height);
void base_setBmp(void *p_component, const char *p_bmpName);
void base_setBackground(void *p_component, const Color_t color);

#if GUI_CONFIG_USE_ALIGNMENT
void base_setAlignment(void *p_component, const GuiAlignment_e horizontal, const GuiAlignment_e vertical);
void base_setHorizontalAlignment(void *p_component, const GuiAlignment_e alignment);
void base_setVerticalAlignment(void *p_component, const GuiAlignment_e alignment);
#if GUI_CONFIG_USE_MARGIN
void base_setMargin(void *p_component, const uint8_t left, const uint8_t top, const uint8_t right, const uint8_t bottom);
void base_setLeftMargin(void *p_component, const uint8_t margin);
void base_setTopMargin(void *p_component, const uint8_t margin);
void base_setRightMargin(void *p_component, const uint8_t margin);
void base_setBottomMargin(void *p_component, const uint8_t margin);
#endif /* GUI_CONFIG_USE_MARGIN */
#endif /* GUI_CONFIG_USE_ALIGNMENT */

#if GUI_CONFIG_USE_ON_BEFORE_DISPLAY
void base_setOnBeforeDisplay(void *p_component, void (*onBeforeDisplay)(BaseComponent_s *p_base));
#endif /* GUI_CONFIG_USE_ON_BEFORE_DISPLAY */

#if GUI_CONFIG_USE_KEY_NAVIGATION
void base_addKeyNavigation(void *p_component, KeyNavigation_s *p_keyNavigation);
#if GUI_USE_DYNAMIC_MEMORY
void base_addNewInitKeyNavigation(BaseComponent_s *p_base);
#endif /* GUI_USE_DYNAMIC_MEMORY */
bool base_setActiveFocus(BaseComponent_s *p_base);
void base_setFocus(BaseComponent_s *p_base, const bool focus);
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

#if GUI_CONFIG_USE_TOUCH
void base_addTouch(void *p_component, Touch_s *p_touch);
#if GUI_USE_DYNAMIC_MEMORY
void base_addNewInitTouch(BaseComponent_s *p_base);
#endif /* GUI_USE_DYNAMIC_MEMORY */
#endif /* GUI_CONFIG_USE_TOUCH */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_CORE_GUI_BASECOMPONENT_H_ */


/*** end of file ***/
