/** @file gui_label.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_COMPONENTS_GUI_LABEL_H_
#define MCSGUI_COMPONENTS_GUI_LABEL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gui_config.h"
#include "Core/gui_basecomponent.h"


typedef struct label_s
{
    BaseComponent_s base;
} Label_s;


Label_s *label_new(void);
Label_s *label_newInit(void);

void label_delete(BaseComponent_s *p_labelBase);
void label_init(Label_s *p_label);

void label_initBmp(Label_s *p_label, const uint32_t bmpKey);

void label_initBmpPos(
        Label_s *p_label, const uint32_t bmpKey,
        const uint16_t x, const uint16_t y);

void label_initBmpPosSize(
        Label_s *p_label, const uint32_t bmpKey,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height);

void label_initBmpPosSizeBack(
        Label_s *p_label, const uint32_t bmpKey,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const Color_t background);

void label_setBmpKey(Label_s *p_label, const uint32_t bmpKey);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_LABEL_H_ */


/*** end of file ***/
