/** @file gui_graphics.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_GRAPHICS_GUI_GRAPHICS_H_
#define MCSGUI_GRAPHICS_GUI_GRAPHICS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "McsGui/gui_config.h"
#include "McsGui/Core/gui_basecomponent.h"
#include "McsGui/Graphics/gui_graphicsinstruction.h"

void graphics_displayComponent(BaseComponent_s *p_base);
void graphics_flushDisplayUpdates(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_GRAPHICS_GUI_GRAPHICS_H_ */
