#include "sys_timer.h"

#include "stm32l4xx_hal.h"

extern TIM_HandleTypeDef htim2;

void timer_init(void)
{
    HAL_TIM_Base_Start(&htim2);
}

void delay_us(volatile uint32_t us)
{
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    while (__HAL_TIM_GET_COUNTER(&htim2) < us);
}

void delay_ms(volatile uint32_t ms)
{
    while (ms--)
    {
        delay_us(1000);
    }
}
