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

#include "gui_config.h"
#include "Core/gui_basecomponent.h"
#include "Graphics/gui_graphicsinstruction.h"

void graphics_displayComponent(BaseComponent_s *p_base);
void graphics_flushDisplayUpdates(void);
void graphics_setSizeFromBmp(BaseComponent_s *p_base);

#if GUI_CONFIG_USE_ANCHOR
void graphics_setPosistionFromAnchor(BaseComponent_s *p_base);
#endif /* GUI_CONFIG_USE_ANCHOR */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_GRAPHICS_GUI_GRAPHICS_H_ */
