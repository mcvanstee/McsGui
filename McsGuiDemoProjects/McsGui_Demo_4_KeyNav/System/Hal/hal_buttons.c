#include "hal_buttons.h"

#include "main.h"
#include "nav_buttons.h"

#define HAL_BUTTON_MAX_NUM 5
#define HAL_BUTTON_DEBOUNCE_TIME_MS 5

#define HAL_BUTTON_OK_INDEX 0
#define HAL_BUTTON_UP_INDEX 1
#define HAL_BUTTON_RIGHT_INDEX 2
#define HAL_BUTTON_DOWN_INDEX 3
#define HAL_BUTTON_LEFT_INDEX 4

static void hal_btn_checkDebounce(int32_t btnIndex);
static void hal_btn_handleButtonPressed(int32_t btnIndex);
static void hal_btn_handleButtonReleased(int32_t btnIndex);

static HalButton_t m_halButtons[HAL_BUTTON_MAX_NUM] =
{
    { BTN_OK_GPIO_Port, BTN_OK_Pin, false, false, 0 },
    { BTN_UP_GPIO_Port, BTN_UP_Pin, false, false, 0 },
    { BTN_RIGHT_GPIO_Port, BTN_RIGHT_Pin, false, false, 0 },
    { BTN_DOWN_GPIO_Port, BTN_DOWN_Pin, false, false, 0 },
    { BTN_LEFT_GPIO_Port, BTN_LEFT_Pin, false, false, 0 },
};

void hal_btn_init(void)
{
    for (int32_t i = 0; i < HAL_BUTTON_MAX_NUM; i++)
    {
        m_halButtons[i].pressed = (GPIO_PIN_RESET  == HAL_GPIO_ReadPin(
                m_halButtons[i].GPIO_Port, m_halButtons[i].GPIO_Pin));
    }
}

void hal_btn_handler(void)
{
    for (int32_t i = 0; i < HAL_BUTTON_MAX_NUM; i++)
    {
        if (m_halButtons[i].pressed)
        {
            if (GPIO_PIN_SET == HAL_GPIO_ReadPin(m_halButtons[i].GPIO_Port, m_halButtons[i].GPIO_Pin))
            {
                m_halButtons[i].pressed = false;
                m_halButtons[i].checkDebounce = false;
                hal_btn_handleButtonReleased(i);
            }
        }
        else if (m_halButtons[i].checkDebounce)
        {
            hal_btn_checkDebounce(i);
        }
        else if ((!m_halButtons[i].pressed) &&
                 (GPIO_PIN_RESET == HAL_GPIO_ReadPin(m_halButtons[i].GPIO_Port, m_halButtons[i].GPIO_Pin)))
        {
            hal_btn_handleButtonEvent(m_halButtons[i].GPIO_Pin);
        }
        else
        {

        }
    }
}

bool hal_btn_handleButtonEvent(uint16_t GPIO_Pin)
{
    bool handled = true;

    if ((BTN_OK_Pin == GPIO_Pin) && (!m_halButtons[HAL_BUTTON_OK_INDEX].checkDebounce))
    {
        m_halButtons[HAL_BUTTON_OK_INDEX].checkDebounce = true;
        m_halButtons[HAL_BUTTON_OK_INDEX].debounceTime = HAL_GetTick() + HAL_BUTTON_DEBOUNCE_TIME_MS;
    }
    else if ((BTN_UP_Pin == GPIO_Pin) && (!m_halButtons[HAL_BUTTON_UP_INDEX].checkDebounce))
    {
        m_halButtons[HAL_BUTTON_UP_INDEX].checkDebounce = true;
        m_halButtons[HAL_BUTTON_UP_INDEX].debounceTime = HAL_GetTick() + HAL_BUTTON_DEBOUNCE_TIME_MS;
    }
    else if ((BTN_RIGHT_Pin == GPIO_Pin) && (!m_halButtons[HAL_BUTTON_RIGHT_INDEX].checkDebounce))
    {
        m_halButtons[HAL_BUTTON_RIGHT_INDEX].checkDebounce = true;
        m_halButtons[HAL_BUTTON_RIGHT_INDEX].debounceTime = HAL_GetTick() + HAL_BUTTON_DEBOUNCE_TIME_MS;
    }
    else if ((BTN_DOWN_Pin == GPIO_Pin) && (!m_halButtons[HAL_BUTTON_DOWN_INDEX].checkDebounce))
    {
        m_halButtons[HAL_BUTTON_DOWN_INDEX].checkDebounce = true;
        m_halButtons[HAL_BUTTON_DOWN_INDEX].debounceTime = HAL_GetTick() + HAL_BUTTON_DEBOUNCE_TIME_MS;
    }
    else if ((BTN_LEFT_Pin == GPIO_Pin) && (!m_halButtons[HAL_BUTTON_LEFT_INDEX].checkDebounce))
    {
        m_halButtons[HAL_BUTTON_LEFT_INDEX].checkDebounce = true;
        m_halButtons[HAL_BUTTON_LEFT_INDEX].debounceTime = HAL_GetTick() + HAL_BUTTON_DEBOUNCE_TIME_MS;
    }
    else
    {
        handled = false;
    }

    return handled;
}

static void hal_btn_checkDebounce(int32_t btnIndex)
{
    if (HAL_GetTick() >= m_halButtons[btnIndex].debounceTime)
    {

        if (GPIO_PIN_RESET  == HAL_GPIO_ReadPin(
                m_halButtons[btnIndex].GPIO_Port, m_halButtons[btnIndex].GPIO_Pin))
        {
            m_halButtons[btnIndex].pressed = true;
            hal_btn_handleButtonPressed(btnIndex);
        }
        else
        {
            m_halButtons[btnIndex].pressed = false;
        }

        m_halButtons[btnIndex].checkDebounce = false;
    }
}

static void hal_btn_handleButtonPressed(int32_t btnIndex)
{
    switch (btnIndex)
    {
        case HAL_BUTTON_OK_INDEX:
            nav_btn_handleEvent(NavBtnEvent_OK_Pressed);
            break;
        case HAL_BUTTON_UP_INDEX:
            nav_btn_handleEvent(NavBtnEvent_Up_Pressed);
            break;
        case HAL_BUTTON_RIGHT_INDEX:
            nav_btn_handleEvent(NavBtnEvent_Right_Pressed);
            break;
        case HAL_BUTTON_DOWN_INDEX:
            nav_btn_handleEvent(NavBtnEvent_Down_Pressed);
            break;
        case HAL_BUTTON_LEFT_INDEX:
            nav_btn_handleEvent(NavBtnEvent_Left_Pressed);
            break;
        default:
            break;
    }
}

static void hal_btn_handleButtonReleased(int32_t btnIndex)
{
    switch (btnIndex)
    {
        case HAL_BUTTON_OK_INDEX:
            nav_btn_handleEvent(NavBtnEvent_OK_Released);
            break;
        case HAL_BUTTON_UP_INDEX:
            nav_btn_handleEvent(NavBtnEvent_Up_Released);
            break;
        case HAL_BUTTON_RIGHT_INDEX:
            nav_btn_handleEvent(NavBtnEvent_Right_Released);
            break;
        case HAL_BUTTON_DOWN_INDEX:
            nav_btn_handleEvent(NavBtnEvent_Down_Released);
            break;
        case HAL_BUTTON_LEFT_INDEX:
            nav_btn_handleEvent(NavBtnEvent_Left_Released);
            break;
        default:
            break;
    }
}
