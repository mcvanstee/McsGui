/** @file gui_anchor.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */


#ifndef UTILS_GUI_ANCHOR_H_
#define UTILS_GUI_ANCHOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gui_config.h"

#if GUI_CONFIG_USE_ANCHOR

#include <stdint.h>

typedef struct base_component_s BaseComponent_s;

typedef enum
{
	Gui_Anchor_None,
	Gui_Anchor_Fill_Parent,
	Gui_Anchor_Center_In_Parent,
    Gui_Anchor_Horizontal_Center,
    Gui_Anchor_Vertical_Center,
	Gui_Anchor_Left,
	Gui_Anchor_Right,
	Gui_Anchor_Top,
	Gui_Anchor_Bottom,
} AnchorPosition_e;

typedef struct gui_anchor_s
{
	BaseComponent_s *p_horizontalAnchorToBase;    // Anchor to the left or right of this component
	BaseComponent_s *p_verticalAnchorToBase;      // Anchor to the top or bottom of this component
	AnchorPosition_e horizontalAnchorPosTo;
	AnchorPosition_e verticalAnchorPosTo;
	AnchorPosition_e horizontalAnchorPosition;
	AnchorPosition_e verticalAnchorPosition;
	uint16_t leftMargin;
	uint16_t rightMargin;
	uint16_t topMargin;
	uint16_t bottomMargin;
	AnchorPosition_e parentAnchor;
} GuiAnchor_s;


GuiAnchor_s *anchor_new(void);
void anchor_delete(GuiAnchor_s *p_anchor);
void anchor_init(GuiAnchor_s *p_anchor);
void anchor_setLeftAnchor(void *p_anchoredComponent, void *p_anchorToComponent, AnchorPosition_e anchorToPosition);
void anchor_setRightAnchor(void *p_anchoredComponent, void *p_anchorToComponent, AnchorPosition_e anchorToPosition);
void anchor_setTopAnchor(void *p_anchoredComponent, void *p_anchorToComponent, AnchorPosition_e anchorToPosition);
void anchor_setBottomAnchor(void *p_anchoredComponent, void *p_anchorToComponent, AnchorPosition_e anchorToPosition);
void anchor_setFillParent(void *p_anchoredComponent, void *p_anchorToComponent);
void anchor_setCenterInParent(void *p_anchoredComponent, void *p_anchorToComponent);
void anchor_setHorizontalCenter(void *p_anchoredComponent, void *p_anchorToComponent);
void anchor_setVerticalCenter(void *p_anchoredComponent, void *p_anchorToComponent);

void anchor_setLeftMargin(void *p_anchoredComponent, uint16_t margin);
void anchor_setRightMargin(void *p_anchoredComponent, uint16_t margin);
void anchor_setTopMargin(void *p_anchoredComponent, uint16_t margin);
void anchor_setBottomMargin(void *p_anchoredComponent, uint16_t margin);

#endif /* GUI_CONFIG_USE_ANCHOR */

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UTILS_GUI_ANCHOR_H_ */


/*** end of file ***/
