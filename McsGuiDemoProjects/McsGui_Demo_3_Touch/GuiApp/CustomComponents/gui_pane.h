#ifndef CUSTOMCOMPONENTS_GUI_PANE_H_
#define CUSTOMCOMPONENTS_GUI_PANE_H_

#include "mcsgui.h"

typedef struct
{
    BaseComponent_s base;
    uint8_t radius;
    bool borderPane;
} Pane_s;

Pane_s *pane_new(void);
Pane_s *pane_newInit(void);
void pane_delete(BaseComponent_s *p_paneBase);
void pane_init(Pane_s *p_pane);
void pane_setRadius(Pane_s *p_pane, uint8_t radius);
void pane_setBorderPane(Pane_s *p_pane, bool borderPane);
void pane_addComponent(Pane_s *p_pane, void *p_component);

#endif /* CUSTOMCOMPONENTS_GUI_PANE_H_ */
