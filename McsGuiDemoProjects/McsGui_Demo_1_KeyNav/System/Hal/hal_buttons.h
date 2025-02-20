#ifndef HAL_HAL_BUTTONS_H_
#define HAL_HAL_BUTTONS_H_

#include <stdbool.h>
#include <stdint.h>

#include "stm32l4xx_hal.h"

typedef struct
{
    GPIO_TypeDef *GPIO_Port;
    uint16_t GPIO_Pin;
    bool pressed;
    bool checkDebounce;
    uint32_t debounceTime;
} HalButton_t;

void hal_btn_init(void);
void hal_btn_handler(void);
bool hal_btn_handleButtonEvent(uint16_t GPIO_Pin);

#endif /* HAL_HAL_BUTTONS_H_ */
