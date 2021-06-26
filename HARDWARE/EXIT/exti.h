#ifndef __EXTI_H_
#define __EXTI_H_

#include "key.h"
#include "led.h"
#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_syscfg.h"

void NVIC_Config(void);
void EXTI_Config(void);

#endif // __EXIT_H_
