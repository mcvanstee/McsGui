/** @file gui_view.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_CORE_GUI_VIEW_H_
#define MCSGUI_CORE_GUI_VIEW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gui_basecomponent.h"
#include "gui_event.h"

typedef struct view_s
{
    BaseComponent_s *p_topComponentList;    // Static list
    BaseComponent_s *p_componentsList;      // Dynamic list get cleared every time view_navigateTo gets called
    BaseComponent_s *p_bottomComponentList; // Static list
    void (*beforeNavigating)(void);
    void (*afterNavigated)(void);
    void (*handleEvent)(struct view_s *p_view, GuiEvent_s *p_event);
} View_s;

void view_init(View_s *p_view);
void view_navigateTo(View_s *p_view, void (*onNavigateTo)(View_s *p_viewNavigatingTo));
void view_addTopComponent(View_s *p_view, void *p_component);
void view_addBottomComponent(View_s *p_view, void *p_component);
void view_addComponent(View_s *p_view, void *p_component);
void view_clearCompList(View_s *p_view);
void view_display(View_s *p_view);
void view_handleEvent(View_s *p_view, GuiEvent_s *p_event);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_CORE_GUI_VIEW_H_ */


/*** end of file ***/
