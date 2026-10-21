/** @file gui_listview.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_COMPONENTS_GUI_LISTVIEW_H_
#define MCSGUI_COMPONENTS_GUI_LISTVIEW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "gui_config.h"
#include "Core/gui_basecomponent.h"
#include "gui_listviewitem.h"


typedef struct list_view_s
{
    BaseComponent_s base;
    bool viewWindowChanged;
    uint8_t rowHight;
    int8_t numberOfItems;
    int8_t itemsVisible;
    int8_t previousActiveIndex;
    int8_t activeIndex;
    int8_t firstVisibleItemIndex;
    void (*onActiveItemChanged)(struct list_view_s *p_listView);    // Callback function called when the active item is changed.
    bool (*onBeforeMoveUp)(struct list_view_s *p_listView);         // Callback function called before the ListView_s active item is moved up.
    bool (*onBeforeMoveDown)(struct list_view_s *p_listView);       // Callback function called before the ListView_s active item is moved down.
    void (*onDisplayed)(struct list_view_s *p_listView);            // Callback function called after the ListView_s onDisplay is called.
#if GUI_CONFIG_USE_KEY_NAVIGATION
    void (*onFocused)(struct list_view_s *p_listView);
    void (*onFocusLost)(struct list_view_s *p_listView);
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */
} ListView_s;

ListView_s *listview_new(void);
ListView_s *listview_newInit(void);

void listview_init(ListView_s *p_listView);
void listview_initPosSize(
        ListView_s *p_listView,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height);

void listview_setItemsVisible(ListView_s *p_listView, const int8_t itemsVisible);
void listview_setRowHight(ListView_s *p_listView, const uint8_t rowHight);

void listview_addItem(ListView_s *p_listView, ListViewItem_s *p_listViewItem);
void listview_addComponent(ListView_s *p_listView, BaseComponent_s *p_itemBase);

int8_t listview_getActiveIndex(ListView_s *p_listView);
BaseComponent_s *listview_getActive(ListView_s *p_listView);
BaseComponent_s *listview_getPreviousActive(ListView_s *p_listView);
BaseComponent_s *listview_getAtIndex(ListView_s *p_listView, const int8_t index);

bool listview_moveUp(ListView_s *p_listView);
bool listview_moveDown(ListView_s *p_listView);
bool listview_getViewWindowChanged(ListView_s *p_listView);
void listview_updateVisibleItems(ListView_s *p_listView);

void listview_setActiveIndex(ListView_s *p_listView, const int8_t index);
void listview_setActiveIndexNotifyChanged(ListView_s *p_listView, const int8_t index);
void listview_setOnActiveItemChanged(ListView_s *p_listView, void (*p_onActiveItemChanged)(ListView_s *p_listView));
void listview_setOnBeforeMoveUp(ListView_s *p_listView, bool (*p_onBeforeMoveUp)(ListView_s *p_listView));
void listview_setOnBeforeMoveDown(ListView_s *p_listView, bool (*p_onBeforeMoveDown)(ListView_s *p_listView));
void listview_setOnDisplayed(ListView_s *p_listView, void (*p_onDisplayed)(ListView_s *p_listView));
#if GUI_CONFIG_USE_KEY_NAVIGATION
void listview_setOnFocused(ListView_s *p_listView, void (*p_onFocused)(ListView_s *p_listView));
void listview_setOnFocusLost(ListView_s *p_listView, void (*p_onFocusLost)(ListView_s *p_listView));
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

void listview_setId(ListView_s *p_listView, const uint8_t id);

void listview_setX(ListView_s *p_listView, const uint16_t x);
void listview_setY(ListView_s *p_listView, const uint16_t y);
void listview_setWidth(ListView_s *p_listView, const uint16_t width);
void listview_setHeight(ListView_s *p_listView, const uint16_t height);
void listview_setPosition(ListView_s *p_listView, const uint16_t x, const uint16_t y);
void listview_setSize(ListView_s *p_listView, const uint16_t width, const uint16_t height);

void listview_setVisible(ListView_s *p_listView, const bool visible);
void listview_setBackgroundColor(ListView_s *p_listView, const Color_t color);
void listview_setDrawBackground(ListView_s *p_listView, const bool drawBackground);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_LISTVIEW_H_ */


/*** end of file ***/
