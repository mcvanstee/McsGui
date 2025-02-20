#ifndef SYS_TIMER_H_
#define SYS_TIMER_H_

#include <stdint.h>

void timer_init(void);
void delay_us(volatile uint32_t us);
void delay_ms(volatile uint32_t ms);

#endif /* SYS_TIMER_H_ */
