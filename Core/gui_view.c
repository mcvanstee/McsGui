#include "gui_view.h"

#include <stddef.h>

#include "gui_log.h"
#include "Graphics/gui_graphics.h"


/* Private function declarations */
static inline void view_addComp(BaseComponent_s **p_componentList, BaseComponent_s *p_component);
static inline void view_displayList(BaseComponent_s *p_componentList);
static BaseComponent_s *view_searchComponentById(BaseComponent_s **p_componentList, uint8_t id);
static BaseComponent_s* view_getChildById(BaseComponent_s *p_component, uint8_t id);

#if GUI_CONFIG_USE_KEY_NAVIGATION
static inline bool view_handleKeyEvent(BaseComponent_s *p_componentList, const GuiEvent_s *p_event);
static BaseComponent_s* view_getFocusedComponent(BaseComponent_s *p_componentList);
static BaseComponent_s* view_getFocusedChildComponent(BaseComponent_s *p_childList);
#endif /* GUI_CONFIG_USE_KEY_NAVIGATION */

#if GUI_CONFIG_USE_TOUCH
static inline bool view_handleTouchEvent(BaseComponent_s *p_componentList, const GuiEvent_s *p_event);
static BaseComponent_s* view_getTouchedComponent(BaseComponent_s *p_componentList, const GuiEvent_s *p_event);
static BaseComponent_s* view_getTouchedChildComponent(BaseComponent_s *p_childList, const GuiEvent_s *p_event);
#endif /* GUI_CONFIG_USE_TOUCH */
static inline bool view_handleCustomEvent(BaseComponent_s *p_componentList, const GuiEvent_s *p_event);

void view_init(View_s *p_view)
{
    p_view->p_topComponentList = NULL;
    p_view->p_componentsList = NULL;
    p_view->p_bottomComponentList = NULL;
    p_view->onBeforeNavigateTo = NULL;
    p_view->onAfterNavigateTo = NULL;
    p_view->onNavigateAway = NULL;
    p_view->handleEvent = NULL;
}

void view_navigateTo(View_s *p_view, void (*createView)(View_s *p_viewNavigatingTo))
{
    view_navigateAway(p_view);
	view_beforeNavigateTo(p_view);
	createView(p_view);
    view_display(p_view);
    view_afterNavigatedTo(p_view);
}

void view_beforeNavigateTo(View_s *p_view)
{
    view_clearCompList(p_view);

    if (p_view->onBeforeNavigateTo != NULL)
    {
        p_view->onBeforeNavigateTo(p_view);

#if GUI_CONFIG_RESET_BOFORE_NAVIGATE_TO
        p_view->onBeforeNavigateTo = NULL;
#endif /* GUI_CONFIG_RESET_BOFORE_NAVIGATE_TO */
    }
}

void view_afterNavigatedTo(View_s *p_view)
{
    if (p_view->onAfterNavigateTo != NULL)
    {
        p_view->onAfterNavigateTo(p_view);

#if GUI_CONFIG_RESET_AFTER_NAVIGATE_TO
        p_view->onAfterNavigateTo = NULL;
#endif /* GUI_CONFIG_RESET_AFTER_NAVIGATE_TO */
    }
}

void view_navigateAway(View_s *p_view)
{
    if (p_view->onNavigateAway != NULL)
    {
        p_view->onNavigateAway(p_view);

#if GUI_CONFIG_RESET_NAVIGATE_AWAY
        p_view->onNavigateAway = NULL;
#endif /* GUI_CONFIG_RESET_NAVIGATE_AWAY */
    }
}

void view_setOnBeforeNavigateTo(View_s *p_view, void (*onBeforeNavigateTo)(View_s *p_view))
{
    p_view->onBeforeNavigateTo = onBeforeNavigateTo;
}

void view_setOnAfterNavigateTo(View_s *p_view, void (*onAfterNavigateTo)(View_s *p_view))
{
    p_view->onAfterNavigateTo = onAfterNavigateTo;
}

void view_setOnNavigateAway(View_s *p_view, void (*onNavigateAway)(View_s *p_view))
{
    p_view->onNavigateAway = onNavigateAway;
}

void view_addTopComponent(View_s *p_view, void *p_component)
{
    view_addComp(&p_view->p_topComponentList, (BaseComponent_s *)p_component);
}

void view_addBottomComponent(View_s *p_view, void *p_component)
{
    view_addComp(&p_view->p_bottomComponentList, (BaseComponent_s *)p_component);
}

void view_addComponent(View_s *p_view, void *p_component)
{
    view_addComp(&p_view->p_componentsList, (BaseComponent_s *)p_component);
}

void view_clearCompList(View_s *p_view)
{
    BaseComponent_s *p_iterator = p_view->p_componentsList;
    while (p_iterator != NULL)
    {
    	BaseComponent_s *p_toDelete = p_iterator;
        p_iterator = p_iterator->p_nextBaseComponent;
        p_toDelete->onDelete(p_toDelete);
    }

    p_view->p_componentsList = NULL;
    p_view->handleEvent = NULL;
}

void view_display(View_s *p_view)
{
    view_displayList(p_view->p_topComponentList);
    view_displayList(p_view->p_componentsList);
    view_displayList(p_view->p_bottomComponentList);
}

void view_handleEvent(View_s *p_view, GuiEvent_s *p_event)
{
    bool eventHandled = false;

#if GUI_CONFIG_USE_KEY_NAVIGATION
    if ((p_event->event >= 1) && (p_event->event <= 15))
    {
        eventHandled = view_handleKeyEvent(p_view->p_topComponentList, p_event);

        if (!eventHandled)
        {
            eventHandled = view_handleKeyEvent(p_view->p_componentsList, p_event);
        }

        if (!eventHandled)
        {
            eventHandled = view_handleKeyEvent(p_view->p_bottomComponentList, p_event);
        }
    }
#endif /* GUI_CONFIG_USE_KEY_NAVIGATION */

#if GUI_CONFIG_USE_TOUCH
    if ((p_event->event >= 16) && (p_event->event <= 18))
    {
        if (!eventHandled)
        {
            eventHandled = view_handleTouchEvent(p_view->p_topComponentList, p_event);
        }

        if (!eventHandled)
        {
            eventHandled = view_handleTouchEvent(p_view->p_componentsList, p_event);
        }

        if (!eventHandled)
        {
            eventHandled = view_handleTouchEvent(p_view->p_bottomComponentList, p_event);
        }
    }
#endif /* GUI_CONFIG_USE_TOUCH */

    const bool isCustomEvent = (p_event->event >= GUI_EVENT_DEFAULT_MAX);
    if (isCustomEvent && !eventHandled)
    {
    	eventHandled = view_handleCustomEvent(p_view->p_topComponentList, p_event);
    }

    if (isCustomEvent && !eventHandled)
    {
    	eventHandled = view_handleCustomEvent(p_view->p_componentsList, p_event);
    }

    if (isCustomEvent && !eventHandled)
    {
    	eventHandled = view_handleCustomEvent(p_view->p_bottomComponentList, p_event);
    }

    if ((!eventHandled) && (p_view->handleEvent != NULL))
    {
        p_view->handleEvent(p_view, p_event);
    }
}

void view_setHandleEvent(View_s *p_view, void (*handleEvent)(View_s *p_view, GuiEvent_s *p_event))
{
	p_view->handleEvent = handleEvent;
}

BaseComponent_s *view_getComponentById(View_s *p_view, uint8_t id)
{
    if (id == 0)
    {
        gui_log_write(GUI_LOG_LEVEL_ERROR, "Invalid id 0");

        return NULL;
    }

    BaseComponent_s *p_component = view_searchComponentById(&p_view->p_componentsList, id);
    if (p_component != NULL)
    {
        return p_component;
    }

    p_component = view_searchComponentById(&p_view->p_topComponentList, id);
    if (p_component != NULL)
    {
        return p_component;
    }

    p_component = view_searchComponentById(&p_view->p_bottomComponentList, id);
    if (p_component != NULL)
    {
        return p_component;
    }

    return NULL;
}

static BaseComponent_s *view_searchComponentById(BaseComponent_s **p_componentList, uint8_t id)
{
    if (id == 0)
    {
        gui_log_write(GUI_LOG_LEVEL_ERROR, "Invalid id 0");

        return NULL;
    }

    BaseComponent_s *p_iterator = *p_componentList;

    while (p_iterator != NULL)
    {
        if (p_iterator->id == id)
        {
            return p_iterator;
        }

        BaseComponent_s *p_child = view_getChildById(p_iterator, id);
        if (p_child != NULL)
        {
            return p_child;
        }

        p_iterator = p_iterator->p_nextBaseComponent;
    }

    return NULL;
}

static BaseComponent_s* view_getChildById(BaseComponent_s *p_component, uint8_t id)
{
    BaseComponent_s *p_iterator = p_component->p_childList;

    while (p_iterator != NULL)
    {
        if (p_iterator->id == id)
        {
            return p_iterator;
        }

        BaseComponent_s *p_child = view_getChildById(p_iterator, id);
        if (p_child != NULL)
        {
            return p_child;
        }

        p_iterator = p_iterator->p_nextBaseComponent;
    }

    return NULL;
}

static inline void view_addComp(BaseComponent_s **p_componentList, BaseComponent_s *p_component)
{
    if (*p_componentList == NULL)
    {
        *p_componentList = p_component;

        return;
    }

    BaseComponent_s *p_iterator = *p_componentList;
    while (p_iterator->p_nextBaseComponent != NULL)
    {
        if (p_component == p_iterator)
        {
            gui_log_write(GUI_LOG_LEVEL_ERROR, "Component already added to view");

            return;
        }

        p_iterator = p_iterator->p_nextBaseComponent;
    }

    p_iterator->p_nextBaseComponent = p_component;
}

static inline void view_displayList(
        BaseComponent_s *p_componentList)
{
    BaseComponent_s *p_iterator = p_componentList;
    while (p_iterator != NULL)
    {
    	if (p_iterator->onDisplay != NULL)
    	{
    		p_iterator->onDisplay(p_iterator);
    	}

        p_iterator = p_iterator->p_nextBaseComponent;
    }
}

#if GUI_CONFIG_USE_KEY_NAVIGATION
static inline bool view_handleKeyEvent(BaseComponent_s *p_componentList, const GuiEvent_s *p_event)
{
    if (p_componentList == NULL)
    {
        return false;
    }

    bool eventHandled = false;

    BaseComponent_s *p_focusedComponent = view_getFocusedComponent(p_componentList);

    if (p_focusedComponent != NULL)
    {
        if (p_focusedComponent->onHandleEvent != NULL)
        {
            eventHandled = p_focusedComponent->onHandleEvent(p_focusedComponent, p_event);
        }

        if (!eventHandled && (p_focusedComponent->p_keyNavigation != NULL) &&
                keynav_handleEvent(p_focusedComponent->p_keyNavigation, p_event))
        {
            base_setFocusNotifyChanged(p_focusedComponent, false);
            eventHandled = true;
        }
    }

    return eventHandled;
}

static BaseComponent_s* view_getFocusedComponent(BaseComponent_s *p_componentList)
{
    BaseComponent_s *p_iterator = p_componentList;
    while (p_iterator != NULL)
    {
        if (p_iterator->focused)
        {
            return p_iterator;
        }

        if (p_iterator->p_childList != NULL)
        {
            BaseComponent_s *p_child = view_getFocusedChildComponent(p_iterator->p_childList);
            if (p_child != NULL)
            {
                return p_child;
            }
        }

        p_iterator = p_iterator->p_nextBaseComponent;
    }

    return NULL;
}

static BaseComponent_s* view_getFocusedChildComponent(BaseComponent_s *p_childList)
{
    BaseComponent_s *p_iterator = p_childList;
    while (p_iterator != NULL)
    {
        if (p_iterator->focused)
        {
            return p_iterator;
        }

        if (p_iterator->p_childList != NULL)
        {
            BaseComponent_s *p_child = view_getFocusedChildComponent(p_iterator->p_childList);
            if (p_child != NULL)
            {
                return p_child;
            }
        }

        p_iterator = p_iterator->p_nextBaseComponent;
    }

    return NULL;
}
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

#if GUI_CONFIG_USE_TOUCH

static BaseComponent_s* view_getTouchedComponent(BaseComponent_s *p_componentList, const GuiEvent_s *p_event)
{
    BaseComponent_s *p_iterator = p_componentList;
    while (p_iterator != NULL)
    {
        if ((p_iterator->p_touch != NULL) &&
            (p_iterator->visible) &&
            (touch_isInTouchArea(p_iterator->p_touch, p_event)))
        {
            return p_iterator;
        }

        if (p_iterator->p_childList != NULL)
        {
            BaseComponent_s *p_child = view_getTouchedChildComponent(p_iterator->p_childList, p_event);
            if (p_child != NULL)
            {
                return p_child;
            }
        }

        p_iterator = p_iterator->p_nextBaseComponent;
    }

    return NULL;
}

static BaseComponent_s* view_getTouchedChildComponent(BaseComponent_s *p_childList, const GuiEvent_s *p_event)
{
    BaseComponent_s *p_iterator = p_childList;
    while (p_iterator != NULL)
    {
        if ((p_iterator->p_touch != NULL) &&
            (p_iterator->visible) &&
            (touch_isInTouchArea(p_iterator->p_touch, p_event)))
        {
            return p_iterator;
        }

        if (p_iterator->p_childList != NULL)
        {
            BaseComponent_s *p_child = view_getTouchedChildComponent(p_iterator->p_childList, p_event);
            if (p_child != NULL)
            {
                return p_child;
            }
        }

        p_iterator = p_iterator->p_nextBaseComponent;
    }

    return NULL;
}

static inline bool view_handleTouchEvent(BaseComponent_s *p_componentList, const GuiEvent_s *p_event)
{
    if (p_componentList == NULL)
    {
        return false;
    }

    BaseComponent_s *p_component = view_getTouchedComponent(p_componentList, p_event);
    if ((p_component == NULL) ||!p_component->visible)
    {
    	return false;
    }

    bool eventHandled = false;

	if (p_component->onHandleEvent != NULL)
	{
		eventHandled = p_component->onHandleEvent(p_component, p_event);
	}

	if (!eventHandled)
	{
		const bool touchHandled = touch_handleEvent(p_component->p_touch, p_component, p_event);

		eventHandled = touchHandled;
	}

    return eventHandled;
}
#endif /* GUI_CONFIG_USE_TOUCH */

static inline bool view_handleCustomEvent(BaseComponent_s *p_componentList, const GuiEvent_s *p_event)
{
    if (p_componentList == NULL)
    {
        return false;
    }

    bool eventHandled = false;
    BaseComponent_s *p_iterator = p_componentList;

    while (p_iterator != NULL)
    {
		if (p_iterator->onHandleEvent != NULL)
		{
			eventHandled = p_iterator->onHandleEvent(p_iterator, p_event);
		}
		else
		{
			break;
		}

        if ((!eventHandled) && (p_iterator->p_childList != NULL))
        {
            BaseComponent_s *p_childIterator = p_iterator->p_childList;
            while (p_childIterator != NULL)
            {
				if (p_childIterator->onHandleEvent != NULL)
				{
					eventHandled = p_childIterator->onHandleEvent(p_childIterator, p_event);
				}

				break;

                p_childIterator = p_childIterator->p_nextBaseComponent;
            }
        }

        if (eventHandled)
        {
            break;
        }

        p_iterator = p_iterator->p_nextBaseComponent;
    }

    return eventHandled;
}

/*** end of file ***/
