#include "gui_view.h"

#include <stddef.h>

#include "McsGui/Graphics/gui_graphics.h"


/* Private function declarations */
static inline void view_addComp(BaseComponent_s **p_componentList, BaseComponent_s *p_component);
static inline void view_displayList(BaseComponent_s *p_componentList);

#if GUI_CONFIG_USE_KEY_NAVIGATION
static inline bool view_handleKeyEvent(BaseComponent_s *p_componentList, const GuiEvent_s *p_event);
#endif /* GUI_CONFIG_USE_KEY_NAVIGATION */

#if GUI_CONFIG_USE_TOUCH
static inline bool view_handleTouchEvent(BaseComponent_s *p_componentList, const GuiEvent_s *p_event);
#endif /* GUI_CONFIG_USE_TOUCH */


void view_init(View_s *p_view)
{
    p_view->p_topComponentList = NULL;
    p_view->p_componentsList = NULL;
    p_view->p_bottomComponentList = NULL;
    p_view->beforeNavigating = NULL;
    p_view->afterNavigated = NULL;
    p_view->handleEvent = NULL;
}

void view_navigateTo(View_s *p_view, void (*onNavigateTo)(View_s *p_viewNavigatingTo))
{
    view_clearCompList(p_view);

    if (p_view->beforeNavigating != NULL)
    {
        p_view->beforeNavigating();
    }

    onNavigateTo(p_view);
    view_display(p_view);

    if (p_view->afterNavigated != NULL)
    {
        p_view->afterNavigated();
    }
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
        p_iterator->onDelete(p_iterator);
        p_iterator = p_iterator->p_nextBaseComponent;
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
    eventHandled = view_handleKeyEvent(p_view->p_topComponentList, p_event);

    if (!eventHandled)
    {
        eventHandled = view_handleKeyEvent(p_view->p_componentsList, p_event);
    }

    if (!eventHandled)
    {
        eventHandled = view_handleKeyEvent(p_view->p_bottomComponentList, p_event);
    }
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

#if GUI_CONFIG_USE_TOUCH
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
#endif /* GUI_CONFIG_USE_TOUCH */

    if ((!eventHandled) && (p_view->handleEvent != NULL))
    {
        p_view->handleEvent(p_view, p_event);
    }
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
        graphics_displayComponent(p_iterator);
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
    BaseComponent_s *p_iterator = p_componentList;

    while (p_iterator != NULL)
    {
        if (p_iterator->focused)
        {
            if (p_iterator->onHandleEvent != NULL)
            {
                eventHandled = p_iterator->onHandleEvent(p_iterator, p_event);
            }
            else
            {
                break;
            }
        }

        if ((!eventHandled) && (p_iterator->p_childList != NULL))
        {
            BaseComponent_s *p_childIterator = p_iterator->p_childList;
            while (p_childIterator != NULL)
            {
                if (p_childIterator->focused)
                {
                    if (p_childIterator->onHandleEvent != NULL)
                    {
                        eventHandled = p_childIterator->onHandleEvent(p_childIterator, p_event);
                    }

                    break;
                }

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
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

#if GUI_CONFIG_USE_TOUCH
static inline bool view_handleTouchEvent(BaseComponent_s *p_componentList, const GuiEvent_s *p_event)
{
    if (p_componentList == NULL)
    {
        return false;
    }

    bool eventHandled = false;
    BaseComponent_s *p_iterator = p_componentList;

    while (p_iterator != NULL)
    {
        if (touch_isInTouchArea(p_iterator->p_touch, p_event))
        {
            if (p_iterator->onHandleEvent != NULL)
            {
                eventHandled = p_iterator->onHandleEvent(p_iterator, p_event);
            }

            bool touchHandled = touch_handleEvent(p_iterator->p_touch, p_iterator, p_event);
            if (!eventHandled)
            {
                eventHandled = touchHandled;
            }

            break;
        }

        if ((!eventHandled) && (p_iterator->p_childList != NULL))
        {
            BaseComponent_s *p_childIterator = p_iterator->p_childList;
            while (p_childIterator != NULL)
            {
                if (touch_isInTouchArea(p_childIterator->p_touch, p_event))
                {
                    if (p_iterator->onHandleEvent != NULL)
                    {
                        eventHandled = p_childIterator->onHandleEvent(p_childIterator, p_event);
                    }

                    bool touchHandled = touch_handleEvent(p_childIterator->p_touch, p_childIterator, p_event);
                    if (!eventHandled)
                    {
                        eventHandled = touchHandled;
                    }

                    break;
                }

                p_childIterator = p_childIterator->p_nextBaseComponent;
            }
        }

        p_iterator = p_iterator->p_nextBaseComponent;
    }

    return eventHandled;
}
#endif /* GUI_CONFIG_USE_TOUCH */


/*** end of file ***/
