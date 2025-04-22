#include "gui_listview.h"

#include <stddef.h>

#include "Utils/gui_log.h"
#include "Utils/gui_memory.h"
#include "Graphics/gui_graphics.h"


/* Private function declarations */
#if GUI_CONFIG_USE_KEY_NAVIGATION
static void listview_onFocusChanged(BaseComponent_s *p_listBase);
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

static void listview_updateVisibleItems(ListView_s *p_listView);
static inline void listview_activeItemChanged(ListView_s *p_listView);
static BaseComponent_s *listview_getTouchedItem(ListView_s *p_listView, const GuiEvent_s *p_event);
static void listview_onDisplay(BaseComponent_s *p_listViewBase);


#if !GUI_USE_DYNAMIC_MEMORY
static bool staticLVMemInUse[GUI_CONFIG_LISTVIEW_BUFFER_SIZE] = {0};
static ListView_s staticLVMem[GUI_CONFIG_LISTVIEW_BUFFER_SIZE] = {0};
#endif /* GUI_USE_DYNAMIC_MEMORY */


ListView_s *listview_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(ListView_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_LISTVIEW_BUFFER_SIZE; i++)
    {
    	if (!staticLVMemInUse[i])
    	{
    		staticLVMemInUse[i] = true;

    		return &staticLVMem[i];
    	}
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No ListView_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Creates a new ListView_s component and initializes it to default values.
 * @return Pointer to the ListView_s component.
 *
 */
ListView_s *listview_newInit(void)
{
	ListView_s *p_listView = listview_new();
	listview_init(p_listView);

	return p_listView;
}


void listview_delete(BaseComponent_s *p_listViewBase)
{
    base_clear(p_listViewBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_listViewBase, sizeof(ListView_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_LISTVIEW_BUFFER_SIZE; i++)
    {
    	if (&staticLVMem[i].base == p_listViewBase)
    	{
    		staticLVMemInUse[i] = false;
    		break;
    	}
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

void listview_init(
        ListView_s *p_listView)
{
    base_initParentComp(&p_listView->base, listview_delete);
    p_listView->base.onDisplay = listview_onDisplay;

    p_listView->rowHight = 0;
    p_listView->numberOfItems = 0;
    p_listView->itemsVisible = 0;
    p_listView->previousActiveIndex = -1;
    p_listView->activeIndex = -1;
    p_listView->firstVisibleItemIndex = 0;
    p_listView->onActiveItemChanged = NULL;
    p_listView->onBeforeMoveUp = NULL;
    p_listView->onBeforeMoveDown = NULL;
    p_listView->onDisplayed = NULL;
    p_listView->base.onHandleEvent = listview_handleEvent;
    p_listView->viewWindowChanged = false;
#if GUI_CONFIG_USE_KEY_NAVIGATION
    p_listView->base.onFocusChanged = listview_onFocusChanged;
    p_listView->onFocused = NULL;
    p_listView->onFocusLost = NULL;
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */
}

void listview_initPosSize(
        ListView_s *p_listView,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height)
{
    listview_init(p_listView);
    base_setPosition(&p_listView->base, x, y);
    base_setWidth(&p_listView->base, width);
    base_setHeight(&p_listView->base, height);
}

void listview_setItemsVisible(ListView_s *p_listView, const int8_t itemsVisible)
{
    p_listView->itemsVisible = itemsVisible;
}

void listview_setRowHight(ListView_s *p_listView, const uint8_t rowHight)
{
    p_listView->rowHight = rowHight;
}

void listview_addComponent(ListView_s *p_listView, BaseComponent_s *p_itemBase)
{
	p_itemBase->p_parent = &p_listView->base;

    if (p_listView->base.p_childList == NULL)
    {
        p_listView->base.p_childList = p_itemBase;
        p_listView->numberOfItems = 1;

        listview_updateVisibleItems(p_listView);

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

void listview_addItem(ListView_s *p_listView, ListViewItem_s *p_listViewItem)
{
	p_listViewItem->base.p_parent = &p_listView->base;
	p_listViewItem->base.x = p_listView->base.x;
    p_listViewItem->base.width = p_listView->base.width;
    p_listViewItem->base.height = p_listView->rowHight;

    if (p_listView->base.p_childList == NULL)
    {
        p_listView->base.p_childList = &p_listViewItem->base;
        p_listView->numberOfItems = 1;
        p_listViewItem->index = 0;

        listview_updateVisibleItems(p_listView);

        return;
    }

    int32_t index = 0;
    BaseComponent_s *p_iterator = p_listView->base.p_childList;
    while (p_iterator->p_nextBaseComponent != NULL)
    {
        p_iterator = p_iterator->p_nextBaseComponent;
        index++;
    }

    p_iterator->p_nextBaseComponent = &p_listViewItem->base;
    p_listViewItem->index = index + 1;
    p_listView->numberOfItems += 1;

    listview_updateVisibleItems(p_listView);
}

bool listview_handleEvent(BaseComponent_s *p_listViewBase, const GuiEvent_s *p_event)
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
            base_setFocusNotifyChanged(p_listViewBase, false);
        }
    }
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

#if GUI_CONFIG_USE_TOUCH
    if (!eventHandled)
    {
        BaseComponent_s *p_touchedItem = listview_getTouchedItem(p_listView, p_event);
        if ((p_touchedItem != NULL) && (p_touchedItem->onHandleEvent != NULL))
        {
            eventHandled = p_touchedItem->onHandleEvent(p_touchedItem, p_event);
        }
    }
#endif /* GUI_CONFIG_USE_TOUCH */

    return eventHandled;
}

static BaseComponent_s *listview_getTouchedItem(ListView_s *p_listView, const GuiEvent_s *p_event)
{
    if ((p_listView == NULL) || (p_listView->numberOfItems == 0))
    {
        return NULL;
    }

    BaseComponent_s *p_iterator = p_listView->base.p_childList;
    while (p_iterator != NULL)
    {
        if (p_iterator->visible)
        {
            Touch_s touch = {0};
            touch_init_1(&touch, p_iterator->x, p_iterator->y, p_iterator->width, p_iterator->height);
            const bool isInTouchArea = touch_isInTouchArea(&touch, p_event);

            if (isInTouchArea)
            {
                return p_iterator;
            }
        }

        p_iterator = p_iterator->p_nextBaseComponent;
    }

    return NULL;
}

bool listview_moveUp(ListView_s *p_listView)
{
    if (p_listView == NULL)
    {
        return false;
    }

	if (p_listView->onBeforeMoveUp != NULL)
	{
		const bool moveUpHandled = p_listView->onBeforeMoveUp(p_listView);
		if (moveUpHandled)
		{
			return true;
		}
	}

    if ((p_listView->numberOfItems == 0) ||
        (p_listView->activeIndex <= 0))
    {
        return false;
    }

    listview_setActiveIndexNotifyChanged(p_listView, p_listView->activeIndex - 1);

    return true;
}

bool listview_moveDown(ListView_s *p_listView)
{
    if (p_listView == NULL)
    {
        return false;
    }

	if (p_listView->onBeforeMoveDown != NULL)
	{
		const bool moveDownHandled = p_listView->onBeforeMoveDown(p_listView);
		if (moveDownHandled)
		{
			return true;
		}
	}

    if ((p_listView->numberOfItems - 1) == p_listView->activeIndex)
    {

        return false;
    }

    listview_setActiveIndexNotifyChanged(p_listView, p_listView->activeIndex + 1);

    return true;
}

bool listview_getViewWindowChanged(ListView_s *p_listView)
{
    if (p_listView->viewWindowChanged)
    {
        p_listView->viewWindowChanged = false;

        return true;
    }

    return false;
}

void listview_setActiveIndex(ListView_s *p_listView, const int8_t index)
{
    if ((p_listView == NULL) || (index >= p_listView->numberOfItems))
    {
        return;
    }

    p_listView->previousActiveIndex = p_listView->activeIndex;
    p_listView->activeIndex = index;

    listview_updateVisibleItems(p_listView);
}

void listview_setActiveIndexNotifyChanged(ListView_s *p_listView, const int8_t index)
{
    listview_setActiveIndex(p_listView, index);
    listview_activeItemChanged(p_listView);
}

void listview_setOnActiveItemChanged(ListView_s *p_listView, void (*p_onActiveItemChanged)(ListView_s *p_listView))
{
    p_listView->onActiveItemChanged = p_onActiveItemChanged;
}

void listview_setOnBeforeMoveUp(ListView_s *p_listView, bool (*p_onBeforeMoveUp)(ListView_s *p_listView))
{
    p_listView->onBeforeMoveUp = p_onBeforeMoveUp;
}

void listview_setOnBeforeMoveDown(ListView_s *p_listView, bool (*p_onBeforeMoveDown)(ListView_s *p_listView))
{
    p_listView->onBeforeMoveDown = p_onBeforeMoveDown;
}

void listview_setOnDisplayed(ListView_s *p_listView, void (*p_onDisplayed)(ListView_s *p_listView))
{
    p_listView->onDisplayed = p_onDisplayed;
}

#if GUI_CONFIG_USE_KEY_NAVIGATION
void listview_setOnFocused(ListView_s *p_listView, void (*p_onFocused)(ListView_s *p_listView))
{
    p_listView->onFocused = p_onFocused;
}

void listview_setOnFocusLost(ListView_s *p_listView, void (*p_onFocusLost)(ListView_s *p_listView))
{
    p_listView->onFocusLost = p_onFocusLost;
}
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

int8_t listview_getActiveIndex(ListView_s *p_listView)
{
    return p_listView->activeIndex;
}

BaseComponent_s *listview_getActive(ListView_s *p_listView)
{
    return listview_getAtIndex(p_listView, p_listView->activeIndex);
}

BaseComponent_s *listview_getPreviousActive(ListView_s *p_listView)
{
    return listview_getAtIndex(p_listView, p_listView->previousActiveIndex);
}

BaseComponent_s *listview_getAtIndex(ListView_s *p_listView, const int8_t index)
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

#if GUI_CONFIG_USE_KEY_NAVIGATION
static void listview_onFocusChanged(BaseComponent_s *p_listBase)
{
    ListView_s *p_listView = (ListView_s *)p_listBase;

    if (p_listBase->focused)
    {
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

        p_listView->previousActiveIndex = p_listView->activeIndex;

        listview_activeItemChanged(p_listView);
    }
}
#endif /* GUI_CONFIG_USE_KEYNAVIGATION */

static void listview_updateVisibleItems(ListView_s *p_listView)
{
    if (p_listView->numberOfItems == 0)
    {
        return;
    }

    if ((p_listView->activeIndex < 0) ||
        (p_listView->numberOfItems <= p_listView->itemsVisible))
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
    else
    {
    }

    uint16_t yPos = p_listView->base.y;
    int8_t index = 0;
    int8_t lastVisibleItemIndex =
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

            BaseComponent_s *p_childIterator = p_iterator->p_childList;
            while (p_childIterator != NULL)
            {
                p_childIterator->visible = false;
                p_childIterator = p_childIterator->p_nextBaseComponent;
            }
        }
        else
        {
            p_iterator->x = p_listView->base.x;
            p_iterator->y = yPos;
            p_iterator->visible = true;

            // Update Child components y positions and visibility
            //
			BaseComponent_s *p_childIterator = p_iterator->p_childList;
			while (p_childIterator != NULL)
			{
				p_childIterator->y = yPos;
				p_childIterator->visible = true;
				p_childIterator = p_childIterator->p_nextBaseComponent;
			}

            yPos += p_listView->rowHight;
        }

        index += 1;
        p_iterator = p_iterator->p_nextBaseComponent;
    }
}

static inline void listview_activeItemChanged(ListView_s *p_listView)
{
    if (p_listView->onActiveItemChanged != NULL)
    {
        p_listView->onActiveItemChanged(p_listView);
    }
}

static void listview_onDisplay(BaseComponent_s *p_listViewBase)
{
#if GUI_CONFIG_USE_ANCHOR
    if (NULL != p_listViewBase->p_anchor)
    {
        graphics_setPosistionFromAnchor(p_listViewBase);
        listview_updateVisibleItems((ListView_s *)p_listViewBase);

#if GUI_CONFIG_USE_TOUCH
        if (NULL != p_listViewBase->p_touch)
        {
            p_listViewBase->p_touch->x = p_listViewBase->x;
            p_listViewBase->p_touch->y = p_listViewBase->y;

            if (p_listViewBase->p_touch->width == 0)
            {
                p_listViewBase->p_touch->width = p_listViewBase->width;
            }

            if (p_listViewBase->p_touch->height == 0)
            {
                p_listViewBase->p_touch->height = p_listViewBase->height;
            }
        }
#endif /* GUI_CONFIG_USE_TOUCH */
    }
#endif /* GUI_CONFIG_USE_ANCHOR */

    graphics_displayComponent(p_listViewBase);

    ListView_s *p_listView = (ListView_s*)p_listViewBase;

    if (p_listView->onDisplayed != NULL)
    {
        p_listView->onDisplayed(p_listView);
    }
}


/*** end of file ***/
