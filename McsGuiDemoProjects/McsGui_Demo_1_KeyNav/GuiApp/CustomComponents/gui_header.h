#ifndef CUSTOMCOMPONENTS_GUI_HEADER_H_
#define CUSTOMCOMPONENTS_GUI_HEADER_H_

#include <stdbool.h>

#include "gui_theme.h"

typedef struct
{
    BaseComponent_s base;
    file_key_e title;
    char customTitle[24];
} Header_s;


void header_setTitle(file_key_e title);
void header_updateTime(const bool update);
void header_updateDateTime(const bool forceUpdate);
void header_showAlarm(const bool showAlarm);

#endif /* CUSTOMCOMPONENTS_GUI_HEADER_H_ */
