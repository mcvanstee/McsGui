/** @gui_item.h
 *
 *  @par COPYRIGHT NOTICE:
 *  Copyright (c) 2024, Marijn van Stee, all rights reserved.
 */

#ifndef COMPONENTS_GUI_ITEM_H_
#define COMPONENTS_GUI_ITEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gui_config.h"
#include "Core/gui_basecomponent.h"

typedef struct gui_item_s
{
    BaseComponent_s base; // Base component
} Item_s;

Item_s *item_new(void);
Item_s *item_newInit(void);

void item_delete(BaseComponent_s *p_itemBase);
void item_init(Item_s *p_item);
void item_addComponent(Item_s *p_item, void *p_component);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* COMPONENTS_GUI_ITEM_H_ */


/*** end of file ***/
