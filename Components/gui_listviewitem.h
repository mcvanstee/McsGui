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

#include "McsGui/gui_config.h"
#include "McsGui/Core/gui_basecomponent.h"


typedef struct list_view_item_s
{
    BaseComponent_s base;
} ListViewItem_s;

#if GUI_USE_DYNAMIC_MEMORY
ListViewItem_s *listviewitem_new(void);
#endif /* GUI_USE_DYNAMIC_MEMORY */

void listviewitem_delete(BaseComponent_s *p_itemBase);
void listviewitem_init(ListViewItem_s *p_listViewItem);
void listviewitem_add(ListViewItem_s *p_listViewItem, void *p_component);
bool listviewitem_handleEvent(BaseComponent_s *p_itemBase, const GuiEvent_s *p_event);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_LISTVIEWITEM_H_ */


/*** end of file ***/
