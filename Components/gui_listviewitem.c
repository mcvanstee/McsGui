#include "gui_listviewitem.h"

#include <stddef.h>

#include "McsGui/Utils/gui_memory.h"


#if GUI_USE_DYNAMIC_MEMORY
/**
 * @brief Creates a new malloced ListViewItem component.
 * @return Pointer to the malloced  memory.
 *
 * @warning The returned component is not initialized.
 */
ListViewItem_s *listviewitem_new(void)
{
    ListViewItem_s *p_listViewItem = gui_mem_malloc(sizeof(ListViewItem_s));

    return p_listViewItem;
}
#endif /* GUI_USE_DYNAMIC_MEMORY */


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
    p_itemBase = NULL;
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
    p_listViewItem->base.onHandleEvent = listviewitem_handleEvent;
}


/**
 * @brief Add a component to the ListViewItem_s.
 * @param[in] p_listViewItem Pointer to ListViewItem.
 * @param[in] p_base Pointer to the component to add to the ListViewItem
 *
 */
void listviewitem_add(ListViewItem_s *p_listViewItem, void *p_component)
{
    BaseComponent_s *p_base = (BaseComponent_s *)p_component;
    if (p_listViewItem->base.p_childList == NULL)
    {
        p_listViewItem->base.p_childList = p_base;
        p_base->xPos = p_listViewItem->base.xPos;
        p_base->yPos = p_listViewItem->base.yPos;

        return;
    }

    BaseComponent_s *p_iterator = p_listViewItem->base.p_childList;
    while (p_iterator->p_nextBaseComponent != NULL)
    {
        p_iterator = p_iterator->p_nextBaseComponent;
    }

    p_iterator->p_nextBaseComponent = p_base;
    p_base->xPos = p_iterator->xPos + p_iterator->width;
    p_base->yPos = p_iterator->yPos;
}


bool listviewitem_handleEvent(BaseComponent_s *p_itemBase, const GuiEvent_s *p_event)
{
    bool eventHandled = false;

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

    return eventHandled;
}

/*** end of file ***/
