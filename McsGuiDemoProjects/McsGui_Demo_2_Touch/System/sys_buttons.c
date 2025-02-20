#include "sys_buttons.h"


static ButtonState_e btn_getBtnState(uint8_t idx);

static ButtonState_e m_buttonStates[NUM_BUTTONS] = {0};
static bool m_buttonHandled[NUM_BUTTONS] = {0};


void btn_init(void)
{
    for (uint8_t i = 0; i < NUM_BUTTONS; i++)
    {
        m_buttonStates[i] = BtnState_Released;
        m_buttonHandled[i] = true;
    }
}

void btn_setBtnState(uint8_t idx, ButtonState_e state)
{
    if (idx >= NUM_BUTTONS)
    {
        return;
    }

    ButtonState_e currentState = m_buttonStates[idx];
    if (currentState != state)
    {
        m_buttonStates[idx] = state;
        m_buttonHandled[idx] = false;
    }
}

bool btn_leftBtnPressed(void)
{
    const ButtonState_e state = btn_leftBtnState();

    return (BtnState_OnPressed == state);
}

bool btn_rightBtnPressed(void)
{
    const ButtonState_e state = btn_rightBtnState();

    return (BtnState_OnPressed == state);
}

bool btn_upBtnPressed(void)
{
    const ButtonState_e state = btn_upBtnState();

    return (BtnState_OnPressed == state);
}

bool btn_downBtnPressed(void)
{
    const ButtonState_e state = btn_downBtnState();

    return (BtnState_OnPressed == state);
}

bool btn_okBtnPressed(void)
{
    const ButtonState_e state = btn_okBtnState();

    return (BtnState_OnPressed == state);
}

bool btn_leftBtnReleased(void)
{
    const ButtonState_e state = btn_leftBtnState();

    return (BtnState_OnReleased == state);
}

bool btn_rightBtnReleased(void)
{
    const ButtonState_e state = btn_rightBtnState();

    return (BtnState_OnReleased == state);
}

bool btn_upBtnReleased(void)
{
    const ButtonState_e state = btn_upBtnState();

    return (BtnState_OnReleased == state);
}

bool btn_downBtnReleased(void)
{
    const ButtonState_e state = btn_downBtnState();

    return (BtnState_OnReleased == state);
}

bool btn_okBtnReleased(void)
{
    const ButtonState_e state = btn_okBtnState();

    return (BtnState_OnReleased == state);
}

ButtonState_e btn_leftBtnState(void)
{
    return btn_getBtnState(BUTTON_LEFT_IDX);
}

ButtonState_e btn_rightBtnState(void)
{
    return btn_getBtnState(BUTTON_RIGHT_IDX);
}

ButtonState_e btn_upBtnState(void)
{
    return btn_getBtnState(BUTTON_UP_IDX);
}

ButtonState_e btn_downBtnState(void)
{
    return btn_getBtnState(BUTTON_DOWN_IDX);
}

ButtonState_e btn_okBtnState(void)
{
    return btn_getBtnState(BUTTON_OK_IDX);
}

static ButtonState_e btn_getBtnState(uint8_t idx)
{
    if (idx >= NUM_BUTTONS)
    {
        return BtnState_Error;
    }

    if ((BtnState_Pressed == m_buttonStates[idx])
            && !m_buttonHandled[idx])
    {
        m_buttonHandled[idx] = true;

        return BtnState_OnPressed;
    }
    else if ((BtnState_Released == m_buttonStates[idx])
                && !m_buttonHandled[idx])
    {
        m_buttonHandled[idx] = true;

        return BtnState_OnReleased;
    }
    else if ((BtnState_Pressed == m_buttonStates[idx])
            && m_buttonHandled[idx])
    {
        return BtnState_LongPressed;
    }
    else
    {
        return m_buttonStates[idx];
    }
}
