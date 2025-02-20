#include "touch_api.h"

#include <stdbool.h>

static TouchState_e m_touchState = TouchState_Released;
static TouchPoint_s m_touchPoint = {0};
static bool m_stateHandled = true;


TouchState_e touch_handlePressed(TouchPoint_s *p_out_point)
{
    *p_out_point = m_touchPoint;

    if ((TouchState_Pressed == m_touchState) && !m_stateHandled)
    {
        m_stateHandled = true;

        return TouchState_OnPressed;
    }
    else if ((TouchState_Released == m_touchState) && !m_stateHandled)
    {
        m_stateHandled = true;

        return TouchState_OnReleased;
    }
    else
    {
        return m_touchState;
    }
}

void touch_setState(TouchState_e state, TouchPoint_s point)
{
    m_touchPoint = point;

    if (state != m_touchState)
    {
        m_touchState = state;
        m_stateHandled = false;
    }
}
