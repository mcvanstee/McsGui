/** @file gui_memory.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_UTILS_GUI_MEMORY_H_
#define MCSGUI_UTILS_GUI_MEMORY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "McsGui/gui_config.h"

#if GUI_USE_DYNAMIC_MEMORY

#include <stdlib.h>
#include <stdint.h>

void *gui_mem_malloc(size_t size);
void gui_mem_free(void *p_mem, size_t size);
uint32_t gui_mem_totalMalloced(void);
uint32_t gui_mem_totalFreed(void);
uint32_t gui_mem_inUse(void);

#endif /* GUI_USE_DYNAMIC_MEMORY */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_UTILS_GUI_MEMORY_H_ */


/*** end of file ***/
