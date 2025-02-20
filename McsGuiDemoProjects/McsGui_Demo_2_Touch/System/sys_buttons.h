#ifndef SYS_BUTTONS_H_
#define SYS_BUTTONS_H_

#include <stdint.h>
#include <stdbool.h>

#define NUM_BUTTONS 5

#define BUTTON_LEFT_IDX 0
#define BUTTON_RIGHT_IDX 1
#define BUTTON_UP_IDX 2
#define BUTTON_DOWN_IDX 3
#define BUTTON_OK_IDX 4

typedef enum
{
    BtnState_Released = 0,
    BtnState_Pressed,
    BtnState_LongPressed,
    BtnState_OnPressed,
    BtnState_OnReleased,
    BtnState_Error,
} ButtonState_e;

void btn_init(void);

void btn_setBtnState(uint8_t idx, ButtonState_e state);

bool btn_leftBtnPressed(void);
bool btn_rightBtnPressed(void);
bool btn_upBtnPressed(void);
bool btn_downBtnPressed(void);
bool btn_okBtnPressed(void);

bool btn_leftBtnReleased(void);
bool btn_rightBtnReleased(void);
bool btn_upBtnReleased(void);
bool btn_downBtnReleased(void);
bool btn_okBtnReleased(void);

ButtonState_e btn_leftBtnState(void);
ButtonState_e btn_rightBtnState(void);
ButtonState_e btn_upBtnState(void);
ButtonState_e btn_downBtnState(void);
ButtonState_e btn_okBtnState(void);

#endif /* SYS_BUTTONS_H_ */
