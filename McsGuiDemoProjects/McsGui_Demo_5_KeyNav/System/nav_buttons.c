#include "nav_buttons.h"

#define NUM_NAV_BUTTONS 5

#define NAV_BUTTON_LEFT_IDX 0
#define NAV_BUTTON_RIGHT_IDX 1
#define NAV_BUTTON_UP_IDX 2
#define NAV_BUTTON_DOWN_IDX 3
#define NAV_BUTTON_OK_IDX 4

static NavButtonState_e nav_btn_getBtnStateReleased(uint8_t idx);
static NavButtonEvent_e nav_btn_getBtnStatePressed(uint8_t idx);
static void nav_btn_setBtnState(uint8_t idx, NavButtonState_e state);

static NavButtonState_e m_buttonStates[NUM_NAV_BUTTONS] = {0};
static bool m_buttonHandled[NUM_NAV_BUTTONS] = {0};


void nav_btn_init(void)
{
    for (uint8_t i = 0; i < NUM_NAV_BUTTONS; i++)
    {
        m_buttonStates[i] = NavBtnState_Released;
        m_buttonHandled[i] = true;
    }
}

void nav_btn_handleEvent(NavButtonEvent_e event)
{
    switch (event)
    {
        case NavBtnEvent_OK_Pressed:
            nav_btn_setBtnState(NAV_BUTTON_OK_IDX, NavBtnState_Pressed);
            break;
        case NavBtnEvent_OK_Released:
            nav_btn_setBtnState(NAV_BUTTON_OK_IDX, NavBtnState_Released);
            break;
        case NavBtnEvent_Up_Pressed:
            nav_btn_setBtnState(NAV_BUTTON_UP_IDX, NavBtnState_Pressed);
            break;
        case NavBtnEvent_Up_Released:
            nav_btn_setBtnState(NAV_BUTTON_UP_IDX, NavBtnState_Released);
            break;
        case NavBtnEvent_Down_Pressed:
            nav_btn_setBtnState(NAV_BUTTON_DOWN_IDX, NavBtnState_Pressed);
            break;
        case NavBtnEvent_Down_Released:
            nav_btn_setBtnState(NAV_BUTTON_DOWN_IDX, NavBtnState_Released);
            break;
        case NavBtnEvent_Left_Pressed:
            nav_btn_setBtnState(NAV_BUTTON_LEFT_IDX, NavBtnState_Pressed);
            break;
        case NavBtnEvent_Left_Released:
            nav_btn_setBtnState(NAV_BUTTON_LEFT_IDX, NavBtnState_Released);
            break;
        case NavBtnEvent_Right_Pressed:
            nav_btn_setBtnState(NAV_BUTTON_RIGHT_IDX, NavBtnState_Pressed);
            break;
        case NavBtnEvent_Right_Released:
            nav_btn_setBtnState(NAV_BUTTON_RIGHT_IDX, NavBtnState_Released);
            break;
        default:
            break;
    }
}

bool nav_btn_leftBtnPressed(void)
{
    const NavButtonState_e state = nav_btn_getBtnStatePressed(NAV_BUTTON_LEFT_IDX);

    return (NavBtnState_OnPressed == state);
}

bool nav_btn_rightBtnPressed(void)
{
    const NavButtonState_e state = nav_btn_getBtnStatePressed(NAV_BUTTON_RIGHT_IDX);

    return (NavBtnState_OnPressed == state);
}

bool nav_btn_upBtnPressed(void)
{
    const NavButtonState_e state = nav_btn_getBtnStatePressed(NAV_BUTTON_UP_IDX);

    return (NavBtnState_OnPressed == state);
}

bool nav_btn_downBtnPressed(void)
{
    const NavButtonState_e state = nav_btn_getBtnStatePressed(NAV_BUTTON_DOWN_IDX);

    return (NavBtnState_OnPressed == state);
}

bool nav_btn_okBtnPressed(void)
{
    const NavButtonState_e state = nav_btn_getBtnStatePressed(NAV_BUTTON_OK_IDX);

    return (NavBtnState_OnPressed == state);
}

bool nav_btn_leftBtnReleased(void)
{
    const NavButtonState_e state = nav_btn_getBtnStateReleased(NAV_BUTTON_LEFT_IDX);

    return (NavBtnState_OnReleased == state);
}

bool nav_btn_rightBtnReleased(void)
{
    const NavButtonState_e state = nav_btn_getBtnStateReleased(NAV_BUTTON_RIGHT_IDX);

    return (NavBtnState_OnReleased == state);
}

bool nav_btn_upBtnReleased(void)
{
    const NavButtonState_e state = nav_btn_getBtnStateReleased(NAV_BUTTON_UP_IDX);

    return (NavBtnState_OnReleased == state);
}

bool nav_btn_downBtnReleased(void)
{
    const NavButtonState_e state = nav_btn_getBtnStateReleased(NAV_BUTTON_DOWN_IDX);

    return (NavBtnState_OnReleased == state);
}

bool nav_btn_okBtnReleased(void)
{
    const NavButtonState_e state = nav_btn_getBtnStateReleased(NAV_BUTTON_OK_IDX);

    return (NavBtnState_OnReleased == state);
}

static NavButtonState_e nav_btn_getBtnStateReleased(uint8_t idx)
{
    if (idx >= NUM_NAV_BUTTONS)
    {
        return NavBtnState_Error;
    }

    if ((NavBtnState_Released == m_buttonStates[idx])
                && !m_buttonHandled[idx])
    {
        m_buttonHandled[idx] = true;

        return NavBtnState_OnReleased;
    }
    else
    {
        return m_buttonStates[idx];
    }
}

static NavButtonEvent_e nav_btn_getBtnStatePressed(uint8_t idx)
{
    if (idx >= NUM_NAV_BUTTONS)
    {
        return NavBtnState_Error;
    }

    if ((NavBtnState_Pressed == m_buttonStates[idx])
            && !m_buttonHandled[idx])
    {
        m_buttonHandled[idx] = true;

        return NavBtnState_OnPressed;
    }
    else if ((NavBtnState_Pressed == m_buttonStates[idx])
            && m_buttonHandled[idx])
    {
        return NavBtnState_LongPressed;
    }
    else
    {
        return m_buttonStates[idx];
    }
}

static void nav_btn_setBtnState(uint8_t idx, NavButtonState_e state)
{
    if (idx >= NUM_NAV_BUTTONS)
    {
        return;
    }

    NavButtonState_e currentState = m_buttonStates[idx];
    if (currentState != state)
    {
        m_buttonStates[idx] = state;
        m_buttonHandled[idx] = false;
    }
}
