/** @file gui_listviewitem.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_COMPONENTS_GUI_LISTVIEWITEM_H_
#define MCSGUI_COMPONENTS_GUI_LISTVIEWITEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gui_config.h"
#include "Core/gui_basecomponent.h"


typedef struct list_view_item_s
{
    BaseComponent_s base;
    int16_t index;
    void (*onPressed)(struct list_view_item_s *p_listViewItem);
    void (*pressed)(struct list_view_item_s *p_listViewItem);
    void (*onReleased)(struct list_view_item_s *p_listViewItem);
    void (*onPressedEvent)(void);
    void (*pressedEvent)(void);
    void (*onReleasedEvent)(void);
} ListViewItem_s;

ListViewItem_s *listviewitem_new(void);
ListViewItem_s *listviewitem_newInit(void);
void listviewitem_delete(BaseComponent_s *p_itemBase);
void listviewitem_init(ListViewItem_s *p_listViewItem);
void listviewitem_addComponent(ListViewItem_s *p_listViewItem, void *p_component);
void listviewitem_setDataObject(ListViewItem_s *p_listViewItem, void *p_dataObject);
bool listviewitem_handleEvent(BaseComponent_s *p_itemBase, const GuiEvent_s *p_event);

void listviewitem_setOnPressed(ListViewItem_s *p_listViewItem, void (*p_pressed)(ListViewItem_s *p_listViewItem));
void listviewitem_setPressed(ListViewItem_s *p_listViewItem, void (*p_pressed)(ListViewItem_s *p_listViewItem));
void listviewitem_setOnReleased(ListViewItem_s *p_listViewItem, void (*p_onReleased)(ListViewItem_s *p_listViewItem));
void listviewitem_setOnPressedEvent(ListViewItem_s *p_listViewItem, void (*p_onPressed)(void));
void listviewitem_setPressedEvent(ListViewItem_s *p_listViewItem, void (*p_pressed)(void));
void listviewitem_setOnReleasedEvent(ListViewItem_s *p_listViewItem, void (*p_onReleased)(void));


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_LISTVIEWITEM_H_ */


/*** end of file ***/
