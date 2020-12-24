/** @file gui_fontdata.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_CORE_GUI_FONTDATA_H_
#define MCSGUI_CORE_GUI_FONTDATA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "McsGui/gui_config.h"


typedef struct font_data_s
{
    uint8_t font;
    uint8_t fontSize;
    uint8_t fontColor;
    uint8_t backgroundColor;
} FontData_s;


#if GUI_USE_DYNAMIC_MEMORY
FontData_s *fontdata_new(void);

void fontdata_delete(FontData_s *p_fontData);
#endif /* GUI_USE_DYNAMIC_MEMORY */

void fontdata_init(FontData_s *p_fontData);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_CORE_GUI_FONTDATA_H_ */


/*** end of file ***/
