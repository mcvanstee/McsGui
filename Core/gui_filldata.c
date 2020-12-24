#include "gui_filldata.h"

#include <stddef.h>

#include "McsGui/Utils/gui_memory.h"


#if GUI_USE_DYNAMIC_MEMORY
FillData_s *filldata_new(void)
{
    return gui_mem_malloc(sizeof(FillData_s));
}

void filldata_delete(FillData_s *p_fillData)
{
    if (p_fillData != NULL)
    {
        gui_mem_free(p_fillData, sizeof(FillData_s));
    }
}
#endif /* GUI_USE_DYNAMIC_MEMORY */


void filldata_init(FillData_s *p_fillData)
{
    p_fillData->borderColor = 0;
    p_fillData->borderThickness = 0;
}

/*** end of file ***/
