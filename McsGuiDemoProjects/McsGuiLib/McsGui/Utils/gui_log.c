#include "gui_log.h"

void gui_log_error(const char *p_message)
{
    gui_log_write(GUI_LOG_LEVEL_ERROR, p_message);
}

void gui_log_warning(const char *p_message)
{
    gui_log_write(GUI_LOG_LEVEL_WARNING, p_message);
}

void gui_log_debug(const char *p_message)
{
    gui_log_write(GUI_LOG_LEVEL_DEBUG, p_message);
}

void gui_log_info(const char *p_message)
{
    gui_log_write(GUI_LOG_LEVEL_INFO, p_message);
}

/*** end of file ***/
