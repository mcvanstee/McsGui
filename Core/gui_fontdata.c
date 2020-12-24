#include "gui_fontdata.h"

#include <stddef.h>

#include "McsGui/Utils/gui_memory.h"


#if GUI_USE_DYNAMIC_MEMORY
FontData_s *fontdata_new(void)
{
    return gui_mem_malloc(sizeof(FontData_s));
}

void fontdata_delete(FontData_s *p_fontData)
{
    if (p_fontData != NULL)
    {
        gui_mem_free(p_fontData, sizeof(FontData_s));
    }
}
#endif /* GUI_USE_DYNAMIC_MEMORY */


void fontdata_init(FontData_s *p_fontData)
{
    p_fontData->font = 0;
    p_fontData->fontSize = 0;
    p_fontData->fontColor = 0;
    p_fontData->backgroundColor = 0;
}

/*** end of file ***/
