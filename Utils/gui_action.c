#include "gui_action.h"

#include <stddef.h>

#include "Core/gui_basecomponent.h"

void gui_connectAction(
		BaseComponent_s *p_base,
		GuiAction_s *p_guiAction,
		void (*actionHandler)(BaseComponent_s *p_baseComponent, void *p_params))
{
	p_guiAction->handleAction = actionHandler;
	p_guiAction->p_base = p_base;
	p_base->p_action = p_guiAction;
}

void gui_disconnectAction(BaseComponent_s *p_base)
{
    if (p_base->p_action != NULL)
    {
    	p_base->p_action->p_base = NULL;
    	p_base->p_action->handleAction = NULL;
    	p_base->p_action = NULL;
    }
}


/*** end of file ***/
