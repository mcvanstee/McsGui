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
void listview_delete(BaseComponent_s *p_listViewBase);
void listview_initPosSize(
        ListView_s *p_listView,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height);

void listview_setRowHight(ListView_s *p_listView, const uint8_t rowHight);
void listview_addComponent(ListView_s *p_listView, BaseComponent_s *p_itemBase);
void listview_addItem(ListView_s *p_listView, ListViewItem_s *p_listViewItem);
bool listview_handleEvent(BaseComponent_s *p_listViewBase, const GuiEvent_s *p_event);
bool listview_moveUp(ListView_s *p_listView);
bool listview_moveDown(ListView_s *p_listView);
bool listview_getViewWindowChanged(ListView_s *p_listView);
void listview_setActive(ListView_s *p_listView, const int8_t index);
BaseComponent_s *listview_getActive(ListView_s *p_listView);
BaseComponent_s *listview_getPreviousActive(ListView_s *p_listView);
BaseComponent_s *listview_getAtIndex(ListView_s *p_listView, const int8_t index);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_LISTVIEW_H_ */


/*** end of file ***/
