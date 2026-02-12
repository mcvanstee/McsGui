#ifndef GUI_APP_H_
#define GUI_APP_H_

#include "fs_file_search.h"
#include "fs_font_search.h"
#include "Core/gui_log.h"
#include "gui_settings.h"
#include "gui_custom_components.h"
#include "gui_utils_unit_converter.h"


#define GUI_APP_LOG_MESSAGE_LENGTH 255
#define GUI_APP_LOG_MESSAGE_LENGTH_INC_NULL (GUI_APP_LOG_MESSAGE_LENGTH + 1)
#define CUSTOM_GUI_EVENT_MEASREMANT_READY 101
#define CUSTOM_GUI_EVENT_UPDATE_DATE_TIME 102
#define CUSTOM_GUI_EVENT_REC_NUMBER_CHANGED 103

#define CONTROL_BAR_ID 100


typedef struct
{
    GuiSettings_s settings;
    View_s view;
} GuiApplication_s;


void gui_app_start(void);
void gui_app_clearView(void);
void gui_app_drawBackground(void);
void gui_app_translate(void *p_component);
void gui_app_setVisibiltyControlBar(const bool visible);

View_s* gui_app_getView(void);
uint32_t gui_app_getTimeStamp(void);

#endif /* GUI_APP_H_ */
