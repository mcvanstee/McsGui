#ifndef CUSTOMCOMPONENTS_GUI_PANE_H_
#define CUSTOMCOMPONENTS_GUI_PANE_H_

#include "mcsgui.h"

typedef struct
{
    BaseComponent_s base;
} Pane_s;

Pane_s *pane_new(void);
Pane_s *pane_newInit(void);

void pane_delete(BaseComponent_s *p_paneBase);
void pane_init(Pane_s *p_pane);


#endif /* CUSTOMCOMPONENTS_GUI_PANE_H_ */
