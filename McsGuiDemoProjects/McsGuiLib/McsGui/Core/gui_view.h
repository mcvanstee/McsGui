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
    void (*onBeforeNavigateTo)(struct view_s *p_view);  // Function to call before navigating to a view but after clearing the component list
    void (*onAfterNavigateTo)(struct view_s *p_view);   // Function to call after navigating to a view
    void (*onNavigateAway)(struct view_s *p_view); // Function to call before navigating away from a view but after clearing the component list
    void (*handleEvent)(struct view_s *p_view, GuiEvent_s *p_event);
} View_s;

void view_init(View_s *p_view);
void view_navigateTo(View_s *p_view, void (*createView)(View_s *p_viewNavigatingTo));
void view_beforeNavigateTo(View_s *p_view);
void view_afterNavigatedTo(View_s *p_view);
void view_navigateAway(View_s *p_view);

void view_setOnBeforeNavigateTo(View_s *p_view, void (*onBeforeNavigateTo)(View_s *p_view));
void view_setOnAfterNavigateTo(View_s *p_view, void (*onAfterNavigateTo)(View_s *p_view));
void view_setOnNavigateAway(View_s *p_view, void (*onNavigateAway)(View_s *p_view));

void view_addTopComponent(View_s *p_view, void *p_component);
void view_addBottomComponent(View_s *p_view, void *p_component);
void view_addComponent(View_s *p_view, void *p_component);

void view_clearCompList(View_s *p_view);
void view_display(View_s *p_view);
void view_handleEvent(View_s *p_view, GuiEvent_s *p_event);

void view_setHandleEvent(View_s *p_view, void (*handleEvent)(View_s *p_view, GuiEvent_s *p_event));

BaseComponent_s *view_getComponentById(View_s *p_view, uint8_t id);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_CORE_GUI_VIEW_H_ */


/*** end of file ***/
