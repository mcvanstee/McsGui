#ifndef NAV_BUTTONS_H_
#define NAV_BUTTONS_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    NavBtnEvent_OK_Pressed = 0,
    NavBtnEvent_OK_Released,
    NavBtnEvent_Up_Pressed,
    NavBtnEvent_Up_Released,
    NavBtnEvent_Down_Pressed,
    NavBtnEvent_Down_Released,
    NavBtnEvent_Left_Pressed,
    NavBtnEvent_Left_Released,
    NavBtnEvent_Right_Pressed,
    NavBtnEvent_Right_Released,
} NavButtonEvent_e;

typedef enum
{
    NavBtnState_Released = 0,
    NavBtnState_Pressed,
    NavBtnState_LongPressed,
    NavBtnState_OnPressed,
    NavBtnState_OnReleased,
    NavBtnState_Error,
} NavButtonState_e;

void nav_btn_init(void);
void nav_btn_handleEvent(NavButtonEvent_e event);

bool nav_btn_leftBtnPressed(void);
bool nav_btn_rightBtnPressed(void);
bool nav_btn_upBtnPressed(void);
bool nav_btn_downBtnPressed(void);
bool nav_btn_okBtnPressed(void);

bool nav_btn_leftBtnReleased(void);
bool nav_btn_rightBtnReleased(void);
bool nav_btn_upBtnReleased(void);
bool nav_btn_downBtnReleased(void);
bool nav_btn_okBtnReleased(void);

#endif /* NAV_BUTTONS_H_ */
