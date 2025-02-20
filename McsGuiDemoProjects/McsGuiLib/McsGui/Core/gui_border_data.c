#include "gui_border_data.h"

#include <stddef.h>

#include "Utils/gui_memory.h"

#if GUI_USE_DYNAMIC_MEMORY
BorderData_s *borderdata_new(void)
{
    return gui_mem_malloc(sizeof(BorderData_s));
}

void borderdata_delete(BorderData_s *p_borderData)
{
    if (p_borderData != NULL)
    {
        gui_mem_free(p_borderData, sizeof(BorderData_s));
    }
}
#endif /* GUI_USE_DYNAMIC_MEMORY */

void borderdata_init(BorderData_s *p_borderData)
{
    p_borderData->borderColor = 0;
    p_borderData->borderThickness = 0;
    p_borderData->radius = 0;
}


/*** end of file ***/
