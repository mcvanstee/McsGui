/** @file gui_filldata.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_CORE_GUI_FILLDATA_H_
#define MCSGUI_CORE_GUI_FILLDATA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "McsGui/gui_config.h"


typedef struct fill_data_s
{
    uint8_t borderThickness;
    Color_t borderColor;
} FillData_s;


#if GUI_USE_DYNAMIC_MEMORY
FillData_s *filldata_new(void);
void filldata_delete(FillData_s *p_fillData);
#endif /* GUI_USE_DYNAMIC_MEMORY */

void filldata_init(FillData_s *p_fillData);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_CORE_GUI_FILLDATA_H_ */


//*** end of file ***/
