#include "gui_listviewitem.h"

#include <stddef.h>
#include <string.h>

#include "Utils/gui_log.h"
#include "Utils/gui_memory.h"


#if !GUI_USE_DYNAMIC_MEMORY
static bool staticLVMIMemInUse[GUI_CONFIG_LISTVIEWITEM_BUFFER_SIZE] = {0};
static ListViewItem_s staticLVMIMem[GUI_CONFIG_LISTVIEWITEM_BUFFER_SIZE] = {0};
#endif /* GUI_USE_DYNAMIC_MEMORY */

/**
 * @brief Creates a new malloced ListViewItem component.
 * @return Pointer to the malloced  memory.
 *
 * @warning The returned component is not initialized.
 */
ListViewItem_s *listviewitem_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(ListViewItem_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_LISTVIEWITEM_BUFFER_SIZE; i++)
    {
    	if (!staticLVMIMemInUse[i])
    	{
    		memset(&staticLVMIMem[i], 0, sizeof(ListViewItem_s));
    		staticLVMIMemInUse[i] = true;

    		return &staticLVMIMem[i];
    	}
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No ListViewItem_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Creates a new ListViewItem component and initializes it to default values.
 * @return Pointer to the ListViewItem component.
 *
 */
ListViewItem_s *listviewitem_newInit(void)
{
    ListViewItem_s *p_listViewItem = listviewitem_new();
    listviewitem_init(p_listViewItem);

    return p_listViewItem;
}


/**
 * @brief Delete the ListViewItem component. This function calls the gui_mem_free function to free the allocated memory.
 * @param[in] p_itemBase Pointer to the ListViewItem component to be freed.
 *
 */
void listviewitem_delete(BaseComponent_s *p_itemBase)
{
    base_clear(p_itemBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_itemBase, sizeof(ListViewItem_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_LISTVIEWITEM_BUFFER_SIZE; i++)
    {
    	if (&staticLVMIMem[i].base == p_itemBase)
    	{
    		staticLVMIMemInUse[i] = false;
    		break;
    	}
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Initialize ListViewItem component to default values.
 * @param[in] p_listViewItem Pointer to ListViewItem component.
 *
 */
void listviewitem_init(ListViewItem_s *p_listViewItem)
{
    base_initParentComp(&p_listViewItem->base, listviewitem_delete);
    p_listViewItem->index = -1;
    p_listViewItem->base.onHandleEvent = listviewitem_handleEvent;
    p_listViewItem->onPressed = NULL;
    p_listViewItem->pressed = NULL;
    p_listViewItem->onReleased = NULL;
    p_listViewItem->onPressedEvent = NULL;
    p_listViewItem->pressedEvent = NULL;
    p_listViewItem->onReleasedEvent = NULL;
}


/**
 * @brief Add a component to the ListViewItem_s.
 * @param[in] p_listViewItem Pointer to ListViewItem.
 * @param[in] p_base Pointer to the component to add to the ListViewItem
 *
 */
void listviewitem_addComponent(ListViewItem_s *p_listViewItem, void *p_component)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    if (p_listViewItem->base.p_childList == NULL)
    {
        p_listViewItem->base.p_childList = p_base;
        p_base->x = p_listViewItem->base.x;
        p_base->y = p_listViewItem->base.y;
        p_base->p_parent = &p_listViewItem->base;

        return;
    }

    BaseComponent_s *p_iterator = p_listViewItem->base.p_childList;
    while (p_iterator->p_nextBaseComponent != NULL)
    {
        p_iterator = p_iterator->p_nextBaseComponent;
    }

    p_iterator->p_nextBaseComponent = p_base;
    p_base->x = p_iterator->x + p_iterator->width;
    p_base->y = p_iterator->y;
    p_base->p_parent = &p_listViewItem->base;
}


/**
 * @brief Set the data object of the ListViewItem_s.
 * @param[in] p_listViewItem Pointer to ListViewItem.
 * @param[in] p_dataObject Pointer to the data object.
 *
 */
void listviewitem_setDataObject(ListViewItem_s *p_listViewItem, void *p_dataObject)
{
    p_listViewItem->base.p_data = p_dataObject;
}

bool listviewitem_handleEvent(BaseComponent_s *p_itemBase, const GuiEvent_s *p_event)
{
    ListViewItem_s *p_listViewItem = (ListViewItem_s *)p_itemBase;
    bool eventHandled = true;

    if ((NULL != p_listViewItem->onPressed) &&
       ((GUI_EVENT_KEY_ENTER_PRESS == p_event->event) || (GUI_EVENT_TOUCH_ON_PRESSED == p_event->event)))
    {
        p_listViewItem->onPressed(p_listViewItem);
    }
    else if ((NULL != p_listViewItem->onReleased) &&
            ((GUI_EVENT_KEY_ENTER_RELEASE == p_event->event) || (GUI_EVENT_TOUCH_ON_RELEASED == p_event->event)))
    {
        p_listViewItem->onReleased(p_listViewItem);
    }
    else if ((NULL != p_listViewItem->pressed) &&
            (GUI_EVENT_TOUCH_PRESSED == p_event->event))
    {
        p_listViewItem->pressed(p_listViewItem);
    }
    else if ((NULL != p_listViewItem->pressedEvent) &&
            (GUI_EVENT_TOUCH_PRESSED == p_event->event))
    {
        p_listViewItem->pressedEvent();
    }
    else if ((NULL != p_listViewItem->onPressedEvent) &&
            ((GUI_EVENT_KEY_ENTER_PRESS == p_event->event) || (GUI_EVENT_TOUCH_ON_PRESSED == p_event->event)))
    {
        p_listViewItem->onPressedEvent();
    }
    else if ((NULL != p_listViewItem->onReleasedEvent) &&
            ((GUI_EVENT_KEY_ENTER_RELEASE == p_event->event) || (GUI_EVENT_TOUCH_ON_RELEASED == p_event->event)))
    {
        p_listViewItem->onReleasedEvent();
    }
    else
    {
        BaseComponent_s *p_iterator = p_itemBase->p_childList;
        while (p_iterator != NULL)
        {
            if (p_iterator->onHandleEvent != NULL)
            {
                eventHandled = p_iterator->onHandleEvent(p_iterator, p_event);

                if (eventHandled)
                {
                    break;
                }
            }

            p_iterator = p_iterator->p_nextBaseComponent;
        }
    }

    return eventHandled;
}


/**
 * @brief Set the onPressed event of the ListViewItem_s.
 * @param[in] p_listViewItem Pointer to ListViewItem.
 * @param[in] p_pressed Pointer to the onPressed function.
 *
 */
void listviewitem_setOnPressed(ListViewItem_s *p_listViewItem, void (*p_pressed)(ListViewItem_s *p_listViewItem))
{
    p_listViewItem->pressed = p_pressed;
}


/**
 * @brief Set the onPressed event of the ListViewItem_s.
 * @param[in] p_listViewItem Pointer to ListViewItem.
 * @param[in] p_pressed Pointer to the onPressed function.
 *
 */
void listviewitem_setPressed(ListViewItem_s *p_listViewItem, void (*p_pressed)(ListViewItem_s *p_listViewItem))
{
    p_listViewItem->pressed = p_pressed;
}

/**
 * @brief Set the onPressed event of the ListViewItem_s.
 * @param[in] p_listViewItem Pointer to ListViewItem.
 * @param[in] p_onReleased Pointer to the onPressed function.
 *
 */
void listviewitem_setOnReleased(ListViewItem_s *p_listViewItem, void (*p_onReleased)(ListViewItem_s *p_listViewItem))
{
    p_listViewItem->onReleased = p_onReleased;
}


/**
 * @brief Set the onPressed event of the ListViewItem_s.
 * @param[in] p_listViewItem Pointer to ListViewItem.
 * @param[in] p_onPressed Pointer to the onPressed function.
 *
 */
void listviewitem_setOnPressedEvent(ListViewItem_s *p_listViewItem, void (*p_onPressed)(void))
{
    p_listViewItem->onPressedEvent = p_onPressed;
}


/**
 * @brief Set the onPressed event of the ListViewItem_s.
 * @param[in] p_listViewItem Pointer to ListViewItem.
 * @param[in] p_pressed Pointer to the onPressed function.
 *
 */
void listviewitem_setPressedEvent(ListViewItem_s *p_listViewItem, void (*p_pressed)(void))
{
    p_listViewItem->pressedEvent = p_pressed;
}


/**
 * @brief Set the onPressed event of the ListViewItem_s.
 * @param[in] p_listViewItem Pointer to ListViewItem.
 * @param[in] p_onReleased Pointer to the onPressed function.
 *
 */
void listviewitem_setOnReleasedEvent(ListViewItem_s *p_listViewItem, void (*p_onReleased)(void))
{
    p_listViewItem->onReleasedEvent = p_onReleased;
}


/*** end of file ***/
