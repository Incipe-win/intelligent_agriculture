#ifndef __TIMER_H_
#define __TIMER_H_

#include "led.h"
#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_tim.h"
#include "sys.h"

void tim2_init(u16 arr, u16 psc);
void tim3_init(u16 arr, u16 psc);
void tim4_init(u16 arr, u16 psc);

#endif // __TIMER_H_
