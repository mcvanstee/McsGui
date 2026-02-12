#ifndef GUI_APP_H_
#define GUI_APP_H_

#include "gui_custom_components.h"
#include "gui_theme.h"
#include "Core/gui_log.h"


#define GUI_APP_LOG_MESSAGE_LENGTH 255
#define GUI_APP_LOG_MESSAGE_LENGTH_INC_NULL (GUI_APP_LOG_MESSAGE_LENGTH + 1)
#define CUSTOM_GUI_EVENT_MEASUREMENT_READY 100


typedef struct
{
    View_s view;
    Footer_s footer;
    bool updateDateTime;
} GuiApplication_s;


void gui_app_start(void);
void gui_app_drawBackground(void);
void gui_app_clearView(void);
void gui_app_translate(void *p_component);

bool gui_app_getUpdateDateTime(void);
void gui_app_setUpdateDateTime(const bool update);

View_s *gui_app_getView(void);
Footer_s *gui_app_getFooter(void);

#endif /* GUI_APP_H_ */
