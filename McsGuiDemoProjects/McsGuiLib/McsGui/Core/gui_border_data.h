/** gui_border_data.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2025, Marijn van Stee, all rights reserved.
 */

#ifndef CORE_GUI_BORDER_DATA_H_
#define CORE_GUI_BORDER_DATA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "gui_config.h"

typedef struct border_data_s
{
    uint8_t borderThickness;
    uint8_t radius;
    Color_t borderColor;
} BorderData_s;


#if GUI_USE_DYNAMIC_MEMORY
BorderData_s *borderdata_new(void);
void borderdata_delete(BorderData_s *p_borderData);
#endif /* GUI_USE_DYNAMIC_MEMORY */

void borderdata_init(BorderData_s *p_borderData);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CORE_GUI_BORDER_DATA_H_ */
