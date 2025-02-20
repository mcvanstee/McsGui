/** @file gui_action.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */
#ifndef UTILS_GUI_ACTION_H_
#define UTILS_GUI_ACTION_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct base_component_s BaseComponent_s;

typedef struct
{
	BaseComponent_s *p_base;
	void (*handleAction)(BaseComponent_s *p_base, void *p_params);
} GuiAction_s;

void gui_connectAction(
		BaseComponent_s *p_base,
		GuiAction_s *p_guiAction,
		void (*actionHandler)(BaseComponent_s *p_baseComponent, void *p_params));
void gui_disconnectAction(BaseComponent_s *p_base);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* UTILS_GUI_ACTION_H_ */


/*** end of file ***/

