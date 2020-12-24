#include "gui_listview.h"

#include <stddef.h>

#include "McsGui/Utils/gui_memory.h"


#if GUI_USE_DYNAMIC_MEMORY
ListView_s *listview_new(void)
{
    return gui_mem_malloc(sizeof(ListView_s));
}
#endif /* GUI_USE_DYNAMIC_MEMORY */


/* Private function declarations */
#if GUI_CONFIG_USE_KEY_NAVIGATION
static void listview_onFocusChanged(BaseComponent_s *p_listBase);
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

static void listview_updateVisibleItems(ListView_s *p_listView);
static inline void listview_activeItemChanged(ListView_s *p_listView);


void listview_delete(BaseComponent_s *p_listViewBase)
{
    base_clear(p_listViewBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_listViewBase, sizeof(ListView_s));
    p_listViewBase = NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

static void listview_init(
        ListView_s *p_listView)
{
    filldata_init(&p_listView->fillData);
    base_initFillComp(&p_listView->base, &p_listView->fillData, listview_delete);

    p_listView->rowHight = 0;
    p_listView->itemsVisible = 0;
    p_listView->numberOfItems = 0;
    p_listView->previousActiveIndex = -1;
    p_listView->activeIndex = 0;
    p_listView->firstVisibleItemIndex = 0;
    p_listView->onActiveItemChanged = NULL;
    p_listView->base.onHandleEvent = listview_handleEvent;
    p_listView->base.onFocusChanged = listview_onFocusChanged;
    p_listView->viewWindowChanged = false;
#if GUI_CONFIG_USE_KEY_NAVIGATION
    p_listView->onFocused = NULL;
    p_listView->onFocusLost = NULL;
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */
}

void listview_init_1(
        ListView_s *p_listView,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height)
{
    listview_init(p_listView);
    base_setPosition(&p_listView->base, xPos, yPos);
    base_setWidth(&p_listView->base, width);
    base_setHeight(&p_listView->base, height);
}

void listview_addComponent(
        ListView_s *p_listView, BaseComponent_s *p_itemBase)
{
    if (p_listView->base.p_childList == NULL)
    {
        p_listView->base.p_childList = p_itemBase;
        p_listView->numberOfItems += 1;

        return;
    }

    BaseComponent_s *p_iterator = p_listView->base.p_childList;
    while (p_iterator->p_nextBaseComponent != NULL)
    {
        p_iterator = p_iterator->p_nextBaseComponent;
    }

    p_iterator->p_nextBaseComponent = p_itemBase;
    p_listView->numberOfItems += 1;

    listview_updateVisibleItems(p_listView);
}

void listview_addItem(
        ListView_s *p_listView, ListViewItem_s *p_listViewItem)
{
    p_listViewItem->base.width = p_listView->base.width;
    p_listViewItem->base.height = p_listView->rowHight;

    if (p_listView->base.p_childList == NULL)
    {
        p_listView->base.p_childList = &p_listViewItem->base;
        p_listView->numberOfItems += 1;

        listview_updateVisibleItems(p_listView);

        return;
    }

    BaseComponent_s *p_iterator = p_listView->base.p_childList;
    while (p_iterator->p_nextBaseComponent != NULL)
    {
        p_iterator = p_iterator->p_nextBaseComponent;
    }

    p_iterator->p_nextBaseComponent = &p_listViewItem->base;
    p_listView->numberOfItems += 1;

    listview_updateVisibleItems(p_listView);
}

bool listview_handleEvent(
        BaseComponent_s *p_listViewBase, const GuiEvent_s *p_event)
{
    bool eventHandled = false;
    ListView_s *p_listView = (ListView_s *)p_listViewBase;
    BaseComponent_s *p_activeItem = listview_getActive(p_listView);

#if GUI_CONFIG_LISTVIEW_BUTTON_BEHAVIOR == 1
    if (GUI_EVENT_KEY_ENTER_RELEASE == p_event->event &&
            p_activeItem->onHandleEvent != NULL)
    {
        eventHandled = p_activeItem->onHandleEvent(p_activeItem, p_event);
    }
    else if (GUI_EVENT_KEY_UP_RELEASE == p_event->event)
    {
        eventHandled = listview_moveUp(p_listView);
    }
    else if (GUI_EVENT_KEY_DOWN_RELEASE == p_event->event)
    {
        eventHandled = listview_moveDown(p_listView);
    }
#else
    if ((GUI_EVENT_KEY_ENTER_PRESS == p_event->event) &&
            (p_activeItem->onHandleEvent != NULL))
    {
        eventHandled = p_activeItem->onHandleEvent(p_activeItem, p_event);
    }
    else if (GUI_EVENT_KEY_UP_PRESS == p_event->event)
    {
        eventHandled = listview_moveUp(p_listView);
    }
    else if (GUI_EVENT_KEY_DOWN_PRESS == p_event->event)
    {
        eventHandled = listview_moveDown(p_listView);
    }
#endif

#if GUI_CONFIG_USE_KEY_NAVIGATION
    if (!eventHandled)
    {
        eventHandled = keynav_handleEvent(p_listViewBase->p_keyNavigation, p_event);
        if (eventHandled)
        {
            base_setFocus(p_listViewBase, false);
        }
    }
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

    return eventHandled;
}

bool listview_moveUp(
        ListView_s *p_listView)
{
    if ((p_listView->numberOfItems == 0) ||
        (p_listView->activeIndex == 0))
    {
        return false;
    }

    listview_setActive(p_listView, p_listView->activeIndex - 1);

    return true;
}

bool listview_moveDown(
        ListView_s *p_listView)
{
    if ((p_listView->numberOfItems - 1) == p_listView->activeIndex)
    {
        return false;
    }

    listview_setActive(p_listView, p_listView->activeIndex + 1);

    return true;
}

bool listview_getViewWindowChanged(
        ListView_s *p_listView)
{
    if (p_listView->viewWindowChanged)
    {
        p_listView->viewWindowChanged = false;

        return true;
    }

    return false;
}

void listview_setActive(
        ListView_s *p_listView, const int8_t index)
{
    if (index >= p_listView->numberOfItems)
    {
        return;
    }

    p_listView->previousActiveIndex = p_listView->activeIndex;
    p_listView->activeIndex = index;

    listview_updateVisibleItems(p_listView);
    listview_activeItemChanged(p_listView);
}

BaseComponent_s *listview_getActive(
        ListView_s *p_listView)
{
    return listview_getAtIndex(p_listView, p_listView->activeIndex);
}

BaseComponent_s *listview_getAtIndex(
        ListView_s *p_listView, const int8_t index)
{
    if ((index < 0) || (index >= p_listView->numberOfItems))
    {
        return NULL;
    }

    BaseComponent_s *p_iterator = p_listView->base.p_childList;

    for (int32_t itemIndex = 0; itemIndex < index; itemIndex++)
    {
        p_iterator = p_iterator->p_nextBaseComponent;

        if (p_iterator == NULL)
        {
            return NULL;
        }
    }

    return p_iterator;
}

static void listview_onFocusChanged(
        BaseComponent_s *p_listBase)
{
    ListView_s *p_listView = (ListView_s *)p_listBase;

    if (p_listBase->focused)
    {
        p_listView->activeIndex = 0;
        p_listView->previousActiveIndex = -1;

        if (p_listView->onFocused != NULL)
        {
            p_listView->onFocused(p_listView);
        }

        listview_activeItemChanged(p_listView);
    }
    else
    {
        if (p_listView->onFocusLost != NULL)
        {
            p_listView->onFocused(p_listView);
        }

        p_listView->activeIndex = -1;
        p_listView->previousActiveIndex = 0;

        listview_activeItemChanged(p_listView);

        p_listView->previousActiveIndex = -1;
    }
}

static void listview_updateVisibleItems(
        ListView_s *p_listView)
{
    if (p_listView->numberOfItems == 0)
    {
        return;
    }

    if (p_listView->numberOfItems <= p_listView->itemsVisible)
    {
        p_listView->firstVisibleItemIndex = 0;
    }
    else if (p_listView->activeIndex < p_listView->firstVisibleItemIndex)
    {
        p_listView->firstVisibleItemIndex = p_listView->activeIndex;

        p_listView->viewWindowChanged = true;
    }
    else if (p_listView->activeIndex >=
            (p_listView->firstVisibleItemIndex + p_listView->itemsVisible))
    {
        p_listView->firstVisibleItemIndex =
                (p_listView->activeIndex - p_listView->itemsVisible) + 1;

        p_listView->viewWindowChanged = true;
    }

    uint16_t yPos = p_listView->base.yPos;
    int_fast8_t index = 0;
    int_fast8_t lastVisibleItemIndex =
            (p_listView->firstVisibleItemIndex + p_listView->itemsVisible) - 1;
    BaseComponent_s *p_iterator = p_listView->base.p_childList;

    while (p_iterator != NULL)
    {
        if (index == p_listView->numberOfItems)
        {
            break;
        }

        if ((index < p_listView->firstVisibleItemIndex) ||
            (index > lastVisibleItemIndex))
        {
            p_iterator->visible = false;
        }
        else
        {
            p_iterator->yPos = yPos;
            p_iterator->visible = true;

            // Update Child components y positions
            //
            if (p_iterator->p_childList != NULL)
            {
                BaseComponent_s *p_childIterator = p_iterator->p_childList;
                while (p_childIterator != NULL)
                {
                    p_childIterator->yPos = yPos;
                    p_childIterator = p_childIterator->p_nextBaseComponent;
                }
            }

            yPos += p_listView->rowHight;
        }

        index += 1;
        p_iterator = p_iterator->p_nextBaseComponent;
    }
}

static inline void listview_activeItemChanged(
        ListView_s *p_listView)
{
    if (p_listView->onActiveItemChanged != NULL)
    {
        p_listView->onActiveItemChanged(p_listView);
    }
}


/*** end of file ***/
