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

#include "McsGui/gui_config.h"
#include "McsGui/Core/gui_basecomponent.h"


typedef struct label_s
{
    BaseComponent_s base;
#if !GUI_USE_DYNAMIC_MEMORY
    char bmpName[GUI_CONFIG_BITMAP_NAME_LENGTH_INC_NULL];
#endif /* GUI_USE_DYNAMIC_MEMORY */
} Label_s;


#if GUI_USE_DYNAMIC_MEMORY
Label_s *label_new(void);
#endif /* GUI_USE_DYNAMIC_MEMORY */

void label_delete(BaseComponent_s *p_labelBase);
void label_init(Label_s *p_label);
void label_init_1(
        Label_s *p_label, const char *p_bmpName,
        const uint16_t xPos, const uint16_t yPos);

void label_init_2(
        Label_s *p_label, const char *p_bmpName,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height);

void label_init_3(
        Label_s *p_label, const char *p_bmpName,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const Color_t background);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_LABEL_H_ */


/*** end of file ***/
