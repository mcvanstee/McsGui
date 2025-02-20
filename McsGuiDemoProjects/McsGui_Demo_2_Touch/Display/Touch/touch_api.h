#ifndef TOUCH_TOUCH_API_H_
#define TOUCH_TOUCH_API_H_

#include <stdint.h>

typedef enum
{
    TouchState_Pressed,
    TouchState_OnPressed,
    TouchState_Released,
    TouchState_OnReleased
} TouchState_e;

typedef struct
{
    uint32_t x;
    uint32_t y;
    uint32_t z;
} TouchPoint_s;

TouchState_e touch_handlePressed(TouchPoint_s *p_out_point);
void touch_setState(TouchState_e state, TouchPoint_s point);

#endif /* TOUCH_TOUCH_API_H_ */
