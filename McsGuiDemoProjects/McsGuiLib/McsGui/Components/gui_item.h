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

void item_init(Item_s *p_item);
void item_initPos(Item_s *p_item, const uint16_t x, const uint16_t y);
void item_initSize(Item_s *p_item, const uint16_t width, const uint16_t height);
void item_initPosSize(Item_s *p_item, const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height);

void item_addComponent(Item_s *p_item, void *p_component);

void item_display(Item_s *p_item);
void item_setId(Item_s *p_item, const uint8_t id);
void item_setX(Item_s *p_item, const uint16_t x);
void item_setY(Item_s *p_item, const uint16_t y);
void item_setWidth(Item_s *p_item, const uint16_t width);
void item_setHeight(Item_s *p_item, const uint16_t height);
void item_setPosition(Item_s *p_item, const uint16_t x, const uint16_t y);
void item_setSize(Item_s *p_item, const uint16_t width, const uint16_t height);

void item_setVisible(Item_s *p_item, const bool visible);
void item_setBackgroundColor(Item_s *p_item, const Color_t color);
void item_setDrawBackground(Item_s *p_item, const bool drawBackground);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* COMPONENTS_GUI_ITEM_H_ */


/*** end of file ***/
