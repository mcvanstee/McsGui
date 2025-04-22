#include "gui_listview_extensions.h"

void listview_ext_activeItemChanged(ListView_s *p_listView)
{
    const bool viewWindowChanged = listview_getViewWindowChanged(p_listView);

    if (viewWindowChanged)
    {
        base_display(p_listView);

        return;
    }

    BaseComponent_s *p_previousActiveItem = listview_getPreviousActive(p_listView);

    if (p_previousActiveItem != NULL)
    {
        base_display(p_previousActiveItem);
    }

    BaseComponent_s *p_activeItem = listview_getActive(p_listView);

    if (p_activeItem != NULL)
    {
        base_display(p_activeItem);
    }
}

void listview_ext_itemPressed(ListViewItem_s *p_listViewItem)
{
    ListView_s *p_listView = (ListView_s*) p_listViewItem->base.p_parent;
    listview_setActiveIndexNotifyChanged(p_listView, p_listViewItem->index);
}
